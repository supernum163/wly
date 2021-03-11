
# 一、下载&安装
```
# 1.安装JDK
sudo apt install -y openjdk-8-jdk
# 2.安装ssh
sudo apt install -y openssh-server
# 3.安装hadoop
wget https://mirrors.tuna.tsinghua.edu.cn/apache/hadoop/common/hadoop-3.3.0/hadoop-3.3.0.tar.gz 
tar -zxvf hadoop-3.3.0.tar.gz 
sudo mv hadoop-3.3.0 /usr/local/hadoop
# 4.安装hive
wget https://mirrors.tuna.tsinghua.edu.cn/apache/hive/hive-3.1.2/apache-hive-3.1.2-bin.tar.gz
tar -zxvf apache-hive-3.1.2-bin.tar.gz
sudo mv apache-hive-3.1.2-bin /usr/local/hive
# 5.安装mysql数据库
sudo apt install -y mysql-server mysql-client 
# 5.安装Derby数据库
wget https://mirrors.tuna.tsinghua.edu.cn/apache//db/derby/db-derby-10.14.2.0/db-derby-10.14.2.0-bin.tar.gz
tar -zxvf db-derby-10.14.2.0-bin.tar.gz
sudo mv db-derby-10.14.2.0-bin /usr/local/derby
# 6.安装Tez
wget https://mirrors.tuna.tsinghua.edu.cn/apache/tez/0.9.2/apache-tez-0.9.2-bin.tar.gz
tar -zxvf apache-tez-0.9.2-bin.tar.gz 
sudo mv apache-tez-0.9.2-bin /usr/local/tez
```

# 二、配置环境变量
- 在用户主目录的<.bashrc>文件中加入以下几行
```
# 设置环境变量 jdk
export JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk-amd64
# 设置环境变量 hadoop
export HADOOP_HOME=/usr/local/hadoop
# 设置环境变量 hive
export HIVE_HOME=/usr/local/hive
# 将上述环境变量加入path
export PATH=.:$JAVA_HOME/bin:$HADOOP_HOME/bin:$HADOOP_HOME/sbin:$HIVE_HOME/bin:$PATH

# 设置环境变量 tez
export TEZ_HOME=/usr/local/tez
# 设置 HADOOP_CLASSPATH
export HADOOP_CLASSPATH=$TEZ_HOME/*.jar:$TEZ_HOME/lib/*.jar
```

# 三、hadoop伪分布式
在路径<$HADOOP_HOME/etc/hadoop/>中修改以下文件
- 1.1、<core-site.xml>
```
<configuration>
   <property> 
      <name>fs.default.name</name> 
      <value>hdfs://localhost:9000</value> 
   </property>
</configuration>
```
- 1.2、<hdfs-site.xml>
```
<configuration>
    <property>
        <name>dfs.replication</name>
        <value>1</value>
    </property>
</configuration>
```

- 2.1、检查是否可以在不使用密码的情况下SSH到本地主机
···
ssh localhost
···

- 2.2、如果没有密码就无法SSH到本地主机，则需要执行以下命令
```
ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
chmod 0600 ~/.ssh/authorized_keys
```

- 3.1、格式化文件系统：
```
$HADOOP_HOME/bin/hdfs namenode -format
```

- 3.2、启动NameNode守护程序和DataNode守护程序：
```
$HADOOP_HOME/sbin/start-dfs.sh
```

参考：【https://hadoop.apache.org/docs/stable/hadoop-project-dist/hadoop-common/SingleCluster.html】


# 四、hive使用mysql作为metastore
- 在mysql中创建[hive]用户，并赋予全权管理数据库的权限
- 复制<$HIVE_HOME/conf/hive-env.sh.template>文件到<$HIVE_HOME/conf/hive-site.xml>，并在<hive-site.xml>中加入以下配置内容
```
<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
<property>
    <name>javax.jdo.option.ConnectionURL</name>
    <value>jdbc:mysql://localhost/hive?createDatabaseIfNotExist=true</value>
</property>
<property>
    <name>javax.jdo.option.ConnectionDriverName</name>
    <value>com.mysql.jdbc.Driver</value>
</property>
<property>
    <name>javax.jdo.option.ConnectionUserName</name>
    <value>hive</value>
</property>
<property>
    <name>javax.jdo.option.ConnectionPassword</name>
    <value>password</value>
</property>
</configuration>
```

- 初始化metabase
```
# 初始化metabase
schematool -dbType mysql -initSchema
# 启动metabase
hive --service metastore
```

参考：【https://cwiki.apache.org/confluence/display/Hive/GettingStarted】

# 五、解决 hive 启动时报错

- 错误`Exception in thread "main" java.lang.NoSuchMethodError: com.google.common.base.Preconditions.checkArgument`
- 因为guava.jar包在hadoop和hive里的版本不一致，需要用高版本覆盖低版本
```
sudo cp $HADOOP_HOME/share/hadoop/common/lib/guava-27.0-jre.jar $HIVE_HOME/lib/
sudo mv $HIVE_HOME/lib/guava-19.0.jar $HIVE_HOME/lib/guava_bk-19.0.jar 
```

- 错误`Error: FUNCTION 'NUCLEUS_ASCII' already exists. (state=X0Y68,code=30000)`
- 因为metastore_db文件夹已经存在了，删除主目录下的<metastore_db>文件夹

- 错误`return code 2 from org.apache.hadoop.hive.ql.exec.mr.MapRedTask`
- 因为没有开启Metastore
```
hive --service metastore
```

# 六、HQL
```
# 删表
drop table [ if exists ] test ;

# 建表
create table test 
  ( id tinyint, name varchar(10), dept varchar(2) ) 
  comment "test" 
  partitioned by (year int)
  row format delimited 
    fields terminated by "," 
    lines terminated by "\n" 
  stored as textfile 
  tblproperties ("skip.header.line.count" = "1")
;
# 设置表test，向表中加载数据时略过第一行 ;
alter table test set tblproperties ("skip.header.line.count" = "1") ;
# 将文件中的数据读取到表test, 注意分区时必须指定partition，且文件中的数据必须是同一分区
load data local inpath 'tmp.txt' overwrite into table test 
  partition (year = 2012)
;
# 插入数据，注意分区时必须指定partition，且开启动态分区 ;
set hive.exec.dynamic.partition=true ;
set hive.exec.dynamic.partition.mode=nonstrict ;
insert overwrite table test 
  partition (year = 2013)
  select * from tb_select1 ;
# 添加分区 ;
alter table test add partition (year = 2014) location '2014' ;  
# 删除分区 ;
alter table test drop partition (year = 2014) ;
# 修复分区 ;
alter table test partition (year = 2014) rename to partition (yoj = 2015)
# 创建索引 ;
create index IDX_test on test(id);
create index IDX_test on table test(id)
as 'org.apache.hadoop.hive.ql.index.compact.CompactIndexHandler'
with deferred rebuild
in table test ;

# 查看信息
show databases ;
show tables ;
show partitions table_name ;
show functions;
```



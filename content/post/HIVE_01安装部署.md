---
title: "Hive 安装与部署"
date: 2021-03-11
categories:
  - 进军大数据
tags:
  - 大数据
keywords:
  - 大数据
  - Hadoop
  - Hive
comments: true
thumbnailImagePosition: left
thumbnailImage: https://null.png
---

**Hive**是架设在**Hadoop**之上的数据库仓库工具。可用于处理结构化数据。本章将介绍ubuntu虚拟机下安装配置Hive的整个过程。

<!--more-->

<!-- toc -->

<br>

## 1、版本对照

| 名称    | 版本号    |
|:--------|-----------|
| Ubuntu  | 20.10     |
| JDK     | 1.8.0_282 |
| Hadoop  | 3.3.0     |
| Hive    | 3.1.2     |
| Derby   | 10.14.2.0 |
| MySQL   | 8.0.23    |


## 2、安装Java

Hadoop、Hive都依赖Java才能运行，但Java版本过高可能会使Hadoop启动报错，所以这里选择安装**JDK8**。Ubuntu中Java默认的安装在`/usr/lib/jvm/`路径下。

```sh
# 安装JDK
sudo apt install -y openjdk-8-jdk
# 设置JDK环境变量
echo export JAVA_HOME=/usr/lib/jvm/java-1.8.0-openjdk-amd64 >> .bashrc
echo export PATH=$PATH:$JAVA_HOME/bin >> .bashrc
# 使环境变量立即生效（后不赘述）
source .bashrc
```

<br>

## 3、安装配置Hadoop

- 3.1、首先[^下载Hadoop]，解压后放入**/usr/local**目录下，并配置相关环境变量。

```sh
# 安装Hadoop
wget https://mirrors.tuna.tsinghua.edu.cn/apache/hadoop/common/hadoop-3.3.0/hadoop-3.3.0.tar.gz 
tar -zxvf hadoop-3.3.0.tar.gz 
sudo mv hadoop-3.3.0 /usr/local/hadoop
# 设置Hadoop环境变量
echo export export HADOOP_HOME=/usr/local/hadoop >> .bashrc
echo export PATH=$PATH:$HADOOP_HOME/bin:$HADOOP_HOME/sbin >> .bashrc
```

- 3.2、Hadoop有独立操作、伪分布操作、完全分布操作三种运行模式。默认配置下，Hadoop运行在非分布模式，有助于调试。我们需要修改以下两个配置文件，使Hadoop在本地机器上实现伪分布模式。

```sh
# 配置主节点
sudo echo '
<configuration>
   <property> 
      <name>fs.default.name</name> 
      <value>hdfs://localhost:9000</value> 
   </property>
</configuration>
' >> $HADOOP_HOME/etc/hadoop/core-site.xml
# 配置分发节点
sudo echo '
<configuration>
    <property>
        <name>dfs.replication</name>
        <value>1</value>
    </property>
</configuration>
' >> $HADOOP_HOME/etc/hadoop/hdfs-site.xml
```

- 3.3、分布模式下的Hadoop必须依赖ssh通信，我们可以通过以下代码安装并配置ssh。

```sh
# 安装ssh、pdsh
sudo apt install -y ssh
sudo apt install -y pdsh
# 测试是否不用密码就可以连接上本地机器
ssh localhost
# 如果不能免密连接本地机器，则需要执行以下代码生成ssh密匙
ssh-keygen -t rsa -P '' -f ~/.ssh/id_rsa
cat ~/.ssh/id_rsa.pub >> ~/.ssh/authorized_keys
chmod 0600 ~/.ssh/authorized_keys
```

- 3.4、接下来我们需要测试Hadoop能否正常启动，并启动HDFS。

```sh
# 获取Hadoop版本信息
hadoop version
# 格式化HDFS（Hadoop分布式文件系统）
hdfs namenode -format
# 启动HDFS守护程序
start-dfs.sh
# 关闭HDFS守护程序
# stop-dfs.sh
```

- 3.5、至此Hadoop安装配置已经完成了，我们可以在Hadoop后台管理页面（http://localhost:9870）中查看相关信息。以下代码列举了HDFS常用命令示例。

```sh
# 在HDFS中创建目录
hdfs dfs -mkdir /input
# 将文件放入HDFS
hdfs dfs -put $HADOOP_HOME/etc/hadoop/*.xml input
# 在HDFS中运行测试程序
hadoop jar $HADOOP_HOME/share/hadoop/mapreduce/hadoop-mapreduce-examples-3.2.2.jar grep input output 'dfs[a-z.]+'
# 从HDFS中提取文件
hdfs dfs -get output ./output
# 列举HDFS中的文件
hdfs dfs -ls output
# 查看HDFS中的文件
hdfs dfs -cat output/*
```

## 4、安装配置Hive

- 4.1、首先[^下载Hive]，解压后放入**/usr/local**目录下，并配置相关环境变量。

```sh
# 安装Hive
wget https://mirrors.tuna.tsinghua.edu.cn/apache/hive/hive-3.1.2/apache-hive-3.1.2-bin.tar.gz
tar -zxvf apache-hive-3.1.2-bin.tar.gz
sudo mv apache-hive-3.1.2-bin /usr/local/hive
# 设置Hive环境变量
echo export HIVE_HOME=/usr/local/hive >> .bashrc
echo export PATH=$PATH:$HIVE_HOME/bin >> .bashrc
```

- 4.2、此时我们已经可以进入Hive，但并不能执行HQL（Hive结构化查询语句），因为还未初始化metastore。接下来我们需要选择一种数据库作为Hive的metastore。

### 4.3、使用Derby做为matastore

- 4.3.1、首先[^下载Derby]，解压后放入**/usr/local**目录下，并配置相关环境变量。

```sh
wget https://mirrors.tuna.tsinghua.edu.cn/apache//db/derby/db-derby-10.14.2.0/db-derby-10.14.2.0-bin.tar.gz
tar -zxvf db-derby-10.14.2.0-bin.tar.gz
sudo mv db-derby-10.14.2.0-bin /usr/local/derby
```

- 4.3.2、设置Derby环境变量。

```sh
echo export DERBY_HOME=/usr/local/derby >> .bashrc
echo export CLASSPATH=$CLASSPATH:$DERBY_HOME/lib/*.jar >> .bashrc
```

- 4.3.3、修改Hive配置文件。

```sh
sudo echo '
<configuration>  
  <property>  
    <name>javax.jdo.option.ConnectionURL</name>  
    <value>jdbc:derby:;databaseName=metastore_db;create=true</value>  
  </property> 
  <property>  
    <name>javax.jdo.option.ConnectionDriverName</name>  
    <value>org.apache.derby.jdbc.EmbeddedDriver</value>  
  </property> 
  <property>  
    <name>hive.metastore.local</name>  
    <value>true</value>  
  </property>  
  <property>
    <name>hive.metastore.warehouse.dir</name>  
    <value>/user/hive/warehouse</value>  
  </property>
  <property>
    <name>datanucleus.schema.autoCreateAll</name>
    <value>true</value>
  </property>
</configuration> 
' > $HIVE_HOME/conf/hive-site.xml
```

- 4.3.4、初始化metastore。

```sh
# 初始化 MySQL metastore
schematool -dbType mysql -initSchema
# 启动metastore服务
hive --service metastore
```

### 4.4、使用MySQL做为matastore

- 4.4.1、安装并以root用户进入MySQL。

```sh
# 安装MySQL
sudo apt install -y mysql-server mysql-client
# 以root用户进入MySQL（MySQL的默认root密码为空）
sudo mysql -u root -p
```
- 4.4.2、在MySQL中创建用户**hive**，并赋予其足够的权限。

```mysql
create user 'hive'@'localhost' identified by 'password' ;
grant all privileges on *.* to 'hive'@'localhost' ;
flush privileges ;
```

- 4.4.3、修改Hive配置文件。

```sh
sudo echo '
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
' > $HIVE_HOME/conf/hive-site.xml
```

- 4.4.4、初始化metastore。

```sh
# 初始化 Derby metastore
schematool -dbType mysql -initSchema
# 启动metastore服务
hive --service metastore
```

- 4.5、至此Hive已经配置完毕，我们可以通过`hive`命令进入Hive，并执行以下命令查看Hive是否正常运行。

```hive
select current_date();
show databases;
```

## 5、Hive报错解决

- [ ] 启动时报错：`Exception in thread "main" java.lang.NoSuchMethodError: com.google.common.base.Preconditions.checkArgument`
- [x] 因为guava.jar包在hadoop和hive里的版本不一致，需要用高版本覆盖低版本

```sh
sudo mv $HIVE_HOME/lib/guava-19.0.jar $HIVE_HOME/lib/guava_bk-19.0.jar 
sudo cp $HADOOP_HOME/share/hadoop/common/lib/guava-27.0-jre.jar $HIVE_HOME/lib/
```

- [ ] 初始化metastore时报错：`Error: FUNCTION 'NUCLEUS_ASCII' already exists. (state=X0Y68,code=30000)`
- [x] 因为metastore_db文件夹已经存在了，删除主目录下的**metastore_db**文件夹


[^下载Hadoop]: http://hadoop.apache.org 
[^下载Hive]: http://hive.apache.org 
[^下载Derby]: http://db.apache.org/derby/

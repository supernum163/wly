

set hive.cli.print.header=true; // 打印列名
set hive.cli.print.row.to.vertical=true; // 开启行转列功能, 前提必须开启打印列名功能
set hive.cli.print.row.to.vertical.num=1; // 设置每行显示的列数

<property>
    <!-- 是否开启锁机制 -->
    <name>hive.support.concurrency</name>
    <value>true</value>
</property>
<property>
    <!-- 是否开启动态分区 -->
    <name>hive.exec.dynamic.partition.mode</name>
    <value>nonstrict</value>
</property>
<property>
    <!-- 配置Hive事务 -->
    <name>hive.txn.manager</name>
    <value>org.apache.hadoop.hive.ql.lockmgr.DbTxnManager</value>
</property>
<property>
    <!-- 是否启用compactor模块 -->
    <name>hive.compactor.initiator.on</name>
    <value>true</value>
</property>
<property>
    <!-- compactor模块进程数量 -->
    <name>hive.compactor.worker.threads</name>
    <value>1</value>
</property>
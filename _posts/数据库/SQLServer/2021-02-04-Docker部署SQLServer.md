---
title: "数据库-SQLServer-Docker部署"
date: 2021-02-04
categories: [数据库]
tags: [数据库]
excerpt: "Docker部署SQLServer"
---

# Docker部署SQLServer

## 部署

```sh
docker run -itd -e "ACCEPT_EULA=Y" -e "SA_PASSWORD=dmjcb@13546!" -p 1433:1433 --name sqlserver2019 sqlserver
```

## 命令

### 进入

```sh
/opt/mssql-tools/bin/sqlcmd -S localhost -U SA -P "dmjcb@13546!"
```

### 显示所有数据库

```sql
SELECT Name FROM Master..SysDatabases ORDER BY Name
GO
```

![](/assets/SelfImgur/2020-10-21_11-05-13.jpg)

### 显示表

```sql
SELECT * FROM [表名]
GO
```

![](/assets/SelfImgur/2020-10-12_13-09-31.jpg)


## Python交互

### 连接

![](/assets/SelfImgur/20201012105710.png)

主机地址需写为: `ip, 端口`, 注意是`逗号`

![](/assets/SelfImgur/20201012130100.png)

```py
import pymssql

conn = pymssql.connect(
    host = IP:端口,
    user = "sa",
    password = 密码,
    database = 数据库,
    charset = 'utf8'
)

# 使用cursor()方法获取操作游标
cursor = conn.cursor()

sql = "SELECT * FROM 表"

try:
    # 执行SQL语句
    cursor.execute(sql)
    results = cursor.fetchall()
except:
    ...

# 关闭数据库连接
conn.close()
```

![](/assets/SelfImgur/20201012180210.png)
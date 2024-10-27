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
docker run -itd -e "ACCEPT_EULA=Y" -e "SA_PASSWORD=dmjcb@13546!" -p 1433:1433 --name sqlserver2019 mcr.microsoft.com/mssql/server:2019-latest
```

![](/assets/SelfImgur/20241026_135104.jpg)

## 命令

### 进入

```sh
docker exec -it sqlserver2019 bash

/opt/mssql-tools18/bin/sqlcmd -S localhost -U SA -P "dmjcb@13546!" -C
```

### 显示所有数据库

```sql
SELECT Name FROM Master..SysDatabases ORDER BY Name
go
```

![](/assets/SelfImgur/20241026_135742.jpg)

### 显示表

```sql
SELECT * FROM [表名]
go
```

## 交互

### Python

主机地址需写为: `ip, 端口`, 注意是`逗号`

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
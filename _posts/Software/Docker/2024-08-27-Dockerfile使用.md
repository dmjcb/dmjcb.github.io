---
title: "Dockerfile使用"
date: 2024-08-27
categories: [docker]
tags: [docker]
excerpt: "Dockerfile"
---

# 使用

## 指令

### from

from 用来指定构建镜像的基础镜像

每个 Dockerfile 都需要以 from 开头来定义要基于哪个镜像创建, 基础镜像可以是官方 Docker 镜像、其他开源镜像

```docker
from [image](:tag)
```
image 指定要基于的镜像名称, 例如 ubuntu、node 

tag 指定镜像的标签(版本), 不指定会默认使用 latest 版本

#### 多阶段构建

多阶段构建可在Dockerfile 中使用多个from, 方便在构建过程中从不同的基础镜像中提取特定文件或工具, 减少最终镜像体积

```docker
# 第一阶段, 构建应用程序
from node:14 AS builder
workdir /app

copy . .
run npm install && npm run build

# 第二阶段, 构建最终的生产镜像
from nginx:alpine
copy --from=builder /app/build /usr/share/nginx/html
```

#### 指定平台

```docker
from --platform=[platform] [image](:tag)
```

- 指定使用适用于 ARM 架构 Alpine Linux 镜像

```docker
from --platform=linux/arm64 alpine:latest
```

### workdir

设置工作路径

```docker
workdir [路径]
```

### run

执行指令

```docker
run [指令]
```

- 构建时执行更新源命令

```docker
run apt udpate && apt upgrade -y
```

### copy

`copy` 将构建上下文目录中源路径的文件/目录复制到镜像内目标路径/位置

```docker
copy (--from=镜像名) [源路径] [目标路径]
```

- 复制当前目录下所有文件到镜像工作路径

```sh
copy . .
```

- 复制nginx镜像中nginx.conf文件

```sh
copy --from=nginx:latest /etc/nginx/nginx.conf /nginx.conf
```

### add

复制文件功能与`copy`一致, 额外拥有拷贝网络文件及解压压缩文件功能

```docker
add [源路径(压缩文件/网络文件)] [目标路径]
```

若源路径为tar压缩文件且压缩格式为 gzip, bzip2, xz, `add` 将会自动解压缩文件到目标路径

### cmd

#### shell格式

```docker
cmd [命令]
```

- 执行Python指令

```docker
cmd python3 manage.py runserver 0.0.0.0:8000
```

#### exec格式

```docker
cmd ["execute", "arg1", "arg2", ...]
```

- 执行Python指令

```docker
cmd ["python3", "manage.py", "runserver 0.0.0.0: 8000"]
```

```mermaid
graph LR;
    X(区别)
    X --> A(cmd) --> A1(docker run时运行) --> A2(Dockerfile中只能在末尾有一条CMD指令)
    X --> B(run) --> B1(docker build时运行) --> B2(Dockerfile中可出现若干次)
```

## 构建

### 普通构建

在Dockerfile目录下执行

```sh
docker build -t [镜像名:tag] .
```

- 构建g++镜像

Dockerfile

```dockerfile
from alpine as builder
workdir /

run sed -i 's/dl-cdn.alpinelinux.org/mirrors.aliyun.com/g' /etc/apk/repositories && \
    apk update && apk add g++
```

```sh
docker build -t gpp:v1 .
```

![](/Resource/Imgur/20241116_145225.jpg)

### 多阶段构建

#### 连续构建

```docker
from 镜像名1 as 阶段名1
...
from 镜像名2 as 阶段名2
```

- 多阶段构建go语言可执行程序

App.go

```go
package main

import "fmt"
func main(){
    fmt.Printf("Hello World!");
}
```

Dockerfile

```docker
# 第一阶段
from golang:1.9-alpine as builder
workdir /go/src/github.com/go/helloworld/

run apk --no-cache add git
run go get -d -v github.com/go-sql-driver/mysql

copy App.go .

run CGO_ENABLED=0 GOOS=linux go build -a -installsuffix cgo -o App .

# 第二阶段
from alpine:latest as prod
workdir /root/

run apk --no-cache add ca-certificates

# 从第一阶段中拷贝文件
copy --from=builder /go/src/github.com/go/helloworld/App .

cmd ["./App"]
```

#### 仅构建某阶段

```sh
docker build --target=[阶段名] -t [新镜像名:tag] .
```

- 仅构建 builder 阶段镜像

```sh
from golang:1.9-alpine as builder

···

docker build --target=builder -t only_builder:v1 .
```
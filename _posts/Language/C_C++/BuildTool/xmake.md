---
title: "C_C++-构建-xmake"
date: 2024-10-14
categories: [C_C++]
tags: [C_C++]
excerpt: "XMake"
---

> - [xmake用法](https://xmake.io/#/zh-cn/about/introduction)

# xmake

## 安装

- Windows

```powershell
Invoke-Expression (Invoke-Webrequest 'https://xmake.io/psget.text' -UseBasicParsing).Content
```

- Linux

```sh
sudo add-apt-repository ppa:xmake-io/xmake
sudo apt update
sudo apt install xmake
```

## 使用

### 创建

```sh
xmake create -l [项目类型] -P ./[项目名]
```

- 创建名为hello C控制台工程

```sh
xmake create -l c -P ./hello
```

### 构建

```sh
xmake
```

```sh
cd hello
xmake
```

### 运行

```sh
xmake run [项目名]
```

### 调试


---
title: "C/C++-构建-xmake"
date: 2024-10-14
categories: [C&C++]
tags: [C&C++]
excerpt: "XMake"
---

> [xmake](https://xmake.io/#/zh-cn/about/introduction)

# xmake

## 安装

- Windows

powershell

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

创建一个名叫hello的c控制台工程

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


---
title: "awk_grep_sed"
date: 2024-09-24
categories: [OS]
tags: [OS]
excerpt: "awk_grep_sed"
---

# awk grep sed

## awk

将文件逐行读入, 以空格为默认分隔符将每行切片, 再对切开的部分进行各种分析处理

```sh
awk [参数] '{pattern action}' {文件名}
```

| 参数    | 含义                                 |
| ------- | ----------------------------------- |
| pattern | awk 在数据中查找的内容               |
| action  | 在找到匹配内容时执行的命令            |
| {}      | 用于根据特定的模式对一系列指令进行分组 |

- 查看登录的用户名

```sh
last -n 5 | awk '{print $1}'
```

![](https://raw.githubusercontent.com/dmjcb/SelfImgur/main/20220109114810.png)

## grep

```sh
grep -[参数] 匹配项
```

```mermaid
graph LR;
    F(grep参数)

    c(**-c**)
    c1(只输出匹配行的计数)

    i(**-i**)
    i1(匹配内容不区分大小写)

    h(**-h**)
    h1(查询多文件时不显示文件名)

    l(**-l**)
    l1(查询多文件时只输出包含匹配字符的文件名)

    n(**-n**)
    n1(显示匹配行及行号)

    s(**-s**)
    s1(不显示不存在或无匹配文本的错误信息)

    v(**-v**)
    v1(显示不包含匹配文本的所有行)

    w(**-w**)
    w1(精确匹配)
```

### 单查询

#### 模糊匹配

含有匹配项的字段都会匹配

```sh
grep (模式) [匹配项]
```

```sh
# 匹配结果为abc abcd abcdef
grep "abc"
```

#### 精确匹配

```sh
grep -w [匹配项]
```

```sh
# 结果为abc
grep -w "abc"
```

### 与查询

在前一个查询的结果中继续查询

```sh
grep '模式1' [匹配项] | grep '模式2'
```

- 查询3月10日16点30时间段内的ssh登录成功的情况

```sh
grep 'Mar 10 16:3' /var/log/secure | grep Accepted
```

![](https://raw.githubusercontent.com/dmjcb/SelfImgur/main/20210310175209.png)

### 或查询

```sh
grep '模式1|模式2' [匹配项] 或 

grep -E '模式1|模式2' [匹配项]
```

### 非查询

去除包含模式1的进程行, 避免影响最终数据的正确性

```sh
grep -v 模式1 [匹配项]
```

- 查询VLC进程信息时排除grep本身影响
  
```sh
ps -aux | grep vlc | grep -v grep
```

![](https://raw.githubusercontent.com/dmjcb/SelfImgur/main/20220221184345.png)

### 正则

#### 查看以pattern开头的行

```sh
grep ^pattern
```

#### 查找以pattern结尾的行

```sh
grep pattern$
```

- 查找/root/test.txt文件中含有human的句子

```sh
grep human /root/test.txt
```

![](https://raw.githubusercontent.com/dmjcb/SelfImgur/main/20210310151418.png)

- 查找/root/test.txt文件中以The开头的句子

```sh
grep ^The /root/test.txt
```

![](https://raw.githubusercontent.com/dmjcb/SelfImgur/main/20210310151535.png)

## sed

```sh
sed -参数 '起始范围, 结束范围 操作' 路径
```

```mermaid
graph LR;
    S(sed)

    subgraph 参数
        direction LR
        
        P(参数)
        n(**-n**)
        n1(忽略执行过程的输出只输出结果)

        i(**-i**)
        i1(改动将覆盖原文件, 可用-i.bak备份)
    end

    subgraph 范围
        direction LR
        D(范围)

        x(x)
        x1(选择第x行, 若为空选择全部行)

        y(x,y/x, +y)
        y1(选择x到y行, 共y - x + 1行)

        z(1~2)
        z1(选择偶数行)

        a(2~2)
        a1(选择偶数行)

        b(x, $)
        b1(从第x行到文件结尾)
    end

    subgraph 操作
        direction LR
        C(操作)

        p(p)
        p1(打印匹配内容)

        d(d)
        d1( 删除匹配内容, 此时要去掉-n参数)

        w(w)
        w1(将匹配内容写入其他地方)

        g(g)
        g1(全部替换)
    end



```

### 打印

若字符串中带有路径符号 `/`, 可以用 `#` 分隔

- 打印file.txt 1-5行
  
```sh
sed -n '1, 5 p' file.txt
```

### 添加

#### 第一行前添加

```sh
sed -i '1i内容' 路径
```

#### 最后一行行前添加

```sh
sed -i '$i内容' 路径
```

#### 最后一行行后添加

```sh
sed -i '$a内容' 路径
```

### 替换

- Ubuntu换源, 修改/etc/apt/sources.list

```sh
sed -i 's#security.ubuntu.com#mirrors.aliyun.com#g' /etc/apt/sources.list

sed -i 's#cn.archive.ubuntu.com#mirrors.aliyun.com#g' /etc/apt/sources.list
```

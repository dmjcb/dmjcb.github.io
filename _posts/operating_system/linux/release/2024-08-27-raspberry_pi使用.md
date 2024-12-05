---
title: "raspberry_pi使用"
date: 2024-08-27
categories: [linux]
tags: [linux]
excerpt: "raspberry_pi使用"
---

## 配置

### 开机连接WIFI

/boot目录下新建wpa_supplicant.conf

```sh
country=GB
ctrl_interface=DIR=/var/run/wpa_supplicant GROUP=netdev
update_config=1
network={
    ssid="WiFi名字不能有中文"
    psk="WiFi密码"
    # 替换成数字, 数字越大代表优先级越高
    priority=1
}

# 可添加多个network, 会按照priority值依次连接
```

### 修改密码

```sh
su passwd pi

# 输入新密码
```

### 换源

编辑 /etc/apt/sources.list, 用以下内容取代

```sh
deb http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ buster main non-free contrib rpi
deb-src http://mirrors.tuna.tsinghua.edu.cn/raspbian/raspbian/ buster main non-free contrib rpi
deb http://mirrors.tuna.tsinghua.edu.cn/raspberrypi/ buster main ui
```
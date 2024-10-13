#!/bin/bash

###
 # @Brief        : 
 # @Author       : dmjcb
 # @Date         : 2021-07-10 13:27:20
 # @LastEditors  : dmjcb@outlook.com
 # @LastEditTime : 2024-09-24 23:25:59
### 

# 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
init_system(){
    sudo sed -i 's#security.ubuntu.com#mirrors.aliyun.com#g' /etc/apt/sources.list
    sudo sed -i 's#cn.archive.ubuntu.com#mirrors.aliyun.com#g' /etc/apt/sources.list
    sudo sed -i 's#archive.ubuntu.com#mirrors.aliyun.com#g' /etc/apt/sources.list
    sudo apt update && sudo apt upgrade -y

    git config --global core.editor "code -w"
    # 防止中文乱码
    git config --global core.quotepath false
}

install_docker(){
    sudo apt install docker.io

    # 添加docker用户组, 将登陆用户加入到docker用户组中
    sudo usermod -aG docker $USER

    sudo newgrp docker

    sudo bash -c "cat > /etc/docker/daemon.json" <<EOF
{
	"registry-mirrors": ["https://docker.1panel.live", "https://hub.rat.dev/", "https://docker.chenby.cn", "https://docker.m.daocloud.io"]
}
EOF
    sudo systemctl daemon-reload

    sudo systemctl restart docker.service
}


# https://blog.laoyutang.cn/linux/clash.html
set_proxy(){
    url="https://cdn.woccloud.org/s/RR5AuofL98Pchv39?clash=2&extend=1"
    
    path=".config/clash/config.yaml"
    
    http_port=7890
    https_port=7891
    api_port=9090
    web_port=43999

    sudo mkdir -p "${HOME}/.config/clash"

    sudo wget ${url} -O "${HOME}/${path}"

    sudo docker run -itd                                                           \
        --name=SelfClash                                                           \
        --restart=always                                                           \
        --mount type=bind,source="${HOME}/${path}",target="/root/${path}",readonly \
        -p ${http_port}:7890                                                       \
        -p ${https_port}:7891                                                      \
        -p ${api_port}:9090                                                        \
        -p ${web_port}:8080                                                        \
        laoyutang/clash-and-dashboard:latest
}


set_icon(){
    name=""
    path=""

    sudo bash -c "cat > /usr/share/applications/${name}.desktop" <<EOF
[Desktop Entry]

Type=Application
Name=${name}
Exec=${path}.AppImage
Icon=${path}.png
StratupWMClass=${name}
EOF
}
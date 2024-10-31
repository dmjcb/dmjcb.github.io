#!/bin/bash

###
 # @Description: 
 # @Version: 1.0
 # @Author: dmjcb
 # @Email:  
 # @Date: 2022-01-17 02:05:53
 # @LastEditors: dmjcb
 # @LastEditTime: 2023-04-21 23:32:32
### 

init(){
    sudo sed -i '1iServer = http://mirrors.aliyun.com/archlinux/$repo/os/$arch' /etc/pacman.d/mirrorlist

    sudo bash -c cat >> /etc/pacman.conf << EOF
[archlinuxcn]

SigLevel = Optional TrustAll
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
EOF

    sudo pacman -Syudd

    git config --global user.name "dmjcb"
    git config --global user.email " "
    git config --global core.editor "code -w"
    # 防止中文乱码
    git config --global core.quotepath false
}


set_pinyin(){
    sudo pacman -S --noconfirm fcitx5 fcitx5-qt fcitx5-gtk fcitx5-qt4 fcitx5-chinese-addons fcitx5-configtool fcitx5-material-color fcitx5-pinyin-moegirl fcitx5-pinyin-zhwiki

    sudo bash -c cat >> /etc/profile << EOF
export XIM="fcitx"
export XIM_PROGRAM="fcitx"
export XMODIFIERS="@im=fcitx"
export GTK_IM_MODULE="fcitx"
export QT_IM_MODULE="fcitx"
EOF

    sudo echo "export LC_CTYPE=zh_CN.UTF-8" >> ~/.xinitrc
}


set_yay(){
    sudo pacman -S yay

    yay --aururl "https://aur.tuna.tsinghua.edu.cn" --save

    yay -S --noconfirm visual-studio-code-bin flameshot grub-customizer vlc
}


set_docker(){
    yay -S --noconfirm docker

    sudo groupadd docker

    sudo usermod -aG docker ${USER}

    sudo newgrp docker

    sudo bash -c "cat > /etc/docker/daemon.json" <<EOF
{
    "registry-mirrors":["https://997nddro.mirror.aliyuncs.com"]
}
EOF
    sudo systemctl start docker
}


set_node(){
    sudo yay -S nodejs npm

    npm config set registry http://mirrors.cloud.tencent.com/npm/
}


set_python(){
    pip install -i https://pypi.tuna.tsinghua.edu.cn/simple pip -U

    pip config set global.index-url https://pypi.tuna.tsinghua.edu.cn/simple

    echo "export PATH=${HOME}/anaconda3/bin:${PATH}">>~/.bashrc

    source ~/.bashrc
}







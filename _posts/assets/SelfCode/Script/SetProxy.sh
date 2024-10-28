#!/bin/bash

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

set_proxy
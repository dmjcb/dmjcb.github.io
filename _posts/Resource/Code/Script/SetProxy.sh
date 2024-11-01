#!/bin/bash

set_proxy(){
    readonly _HTTP_PORT=7890
    readonly _HTTPS_PORT=7891
    readonly _API_PORT=9090

    web_port=43999

    path=".config/clash/config.yaml"

    url="https://cdn.woccloud.org/s/RR5AuofL98Pchv39?clash=2&extend=1"

    sudo mkdir -p "${HOME}/.config/clash"

    sudo wget ${url} -O "${HOME}/${path}"

    sudo docker run -itd                                                           \
        --name=SelfClash                                                           \
        --restart=always                                                           \
        --mount type=bind,source="${HOME}/${path}",target="/root/${path}",readonly \
        -p ${_HTTP_PORT}:7890                                                      \
        -p ${_HTTPS_PORT}:7891                                                     \
        -p ${_API_PORT}:9090                                                       \
        -p ${web_port}:8080                                                        \
        laoyutang/clash-and-dashboard:latest
}

set_proxy
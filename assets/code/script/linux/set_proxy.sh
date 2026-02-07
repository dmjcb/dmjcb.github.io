#!/bin/bash

set_proxy(){
    readonly _URL="https://cdn.woccloud.org/s/RR5AuofL98Pchv39?clash=2&extend=1"
    readonly _PATH=".config/clash/config.yaml"

    readonly _HTTP_PORT=7890
    readonly _HTTPS_PORT=7891
    readonly _API_PORT=9090

    admin_port=43999

    sudo mkdir -p "${HOME}/.config/clash"

    sudo wget ${_URL} -O "${HOME}/${_PATH}"

    sudo docker run -itd                                                             \
        --name=self_clash                                                            \
        --restart=always                                                             \
        --mount type=bind,source="${HOME}/${_PATH}",target="/root/${_PATH}",readonly \
        -p ${_HTTP_PORT}:7890                                                        \
        -p ${_HTTPS_PORT}:7891                                                       \
        -p ${_API_PORT}:9090                                                         \
        -p ${admin_port}:8080                                                        \
        laoyutang/clash-and-dashboard:latest
}

set_proxy
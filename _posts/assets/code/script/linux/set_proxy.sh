#!/bin/bash

set_proxy(){
    readonly URL="https://cdn.woccloud.org/s/CF2E5P19fAsejCwf?clash=1&log-level=info"
    readonly _PATH=".config/clash"
    readonly HTTP_PORT=7890
    readonly HTTPS_PORT=7891
    readonly API_PORT=9090

    admin_port=43999

    mkdir -p "${HOME}/${_PATH}"
    wget ${URL} -O "${HOME}/${_PATH}/config.yaml"
    
    docker run -itd                                                  \
        --name=self_clash                                            \
        --restart=always                                             \
        -v ${HOME}/${_PATH}/config.yaml:/root/${_PATH}/config.yaml   \
        -p ${HTTP_PORT}:7890                                         \
        -p ${HTTPS_PORT}:7891                                        \
        -p ${API_PORT}:9090                                          \
        -p ${admin_port}:8080                                        \
        laoyutang/clash-and-dashboard:latest
}

set_proxy

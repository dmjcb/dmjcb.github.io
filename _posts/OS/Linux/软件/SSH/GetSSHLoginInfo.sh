#!/bin/bash

###
 # @Brief        : 
 # @Author       : dmjcb
 # @Date         : 2024-09-12 16:29:57
 # @LastEditors  : dmjcb@outlook.com
 # @LastEditTime : 2024-09-12 16:30:10
### 

login_name=${USER}

login_ip=${SSH_CLIENT%% *}

login_time=${date +%F%t%k:%M}

server=${ifconfig wlp2s0 | sed -n '2p' | awk '{print $2}'}

echo ${login_name} ${login_ip} ${login_time} ${server}
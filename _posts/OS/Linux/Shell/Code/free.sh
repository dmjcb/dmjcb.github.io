#! /bin/bash

###
 # @Brief        : Memory小于400M时 释放Cached的内存
 # @Author       : dmjcb
 # @Date         : 2022-07-09 23:24:40
 # @LastEditors  : dmjcb@outlook.com
 # @LastEditTime : 2024-09-22 21:39:08
### 

mem=409600

freemem=$(cat /proc/meminfo | grep "MemFree" | awk '{print $2}')
if [ ${freemem} -le ${mem} ];then
    date >> /var/log/mem.log
    free -m >> /var/log/mem.log
    sync
    sync
    echo 3 > /proc/sys/vm/drop_caches
    free -m >> /var/log/mem.log
fi
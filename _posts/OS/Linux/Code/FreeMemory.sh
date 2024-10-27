#! /bin/bash

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
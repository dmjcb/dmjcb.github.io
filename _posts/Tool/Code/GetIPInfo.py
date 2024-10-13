'''
Brief        : 
Author       : dmjcb
Date         : 2024-09-24 20:03:51
LastEditors  : dmjcb@outlook.com
LastEditTime : 2024-09-26 15:26:05
'''

import requests

ip = "172.233.157.41"

r = requests.get("http://ip-api.com/json/" + ip)

print(r.json())

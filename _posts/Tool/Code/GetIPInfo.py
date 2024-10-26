import requests

ip = "172.233.157.41"

r = requests.get("http://ip-api.com/json/" + ip)

print(r.json())

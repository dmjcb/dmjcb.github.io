from json import loads, dumps
from requests import get, put


class AutoSwitchNode:
    __IP = "192.168.3.3"
    __PORT = 9090

    def __init__(self):
        self.__url = '{0}:{1}'.format(self.__IP, self.__PORT)

    def get_proxy_name_list(self):
        d = get('http://{0}/proxies'.format(self.__url))
        d = loads(d.text)

        return d['proxies']['Proxy']['all']

    def get_proxy_delay(self, name):
        r = get('http://{0}/proxies/{1}'.format(self.__url, name))
        if r.status_code != 200:
            return -1

        r = loads(r.text)
        return r['history'][0]['delay']

    def get_all_proxy_delay(self):
        name_list = self.get_proxy_name_list()
        delay_map = {}

        for name in name_list:
            t = self.get_proxy_delay(name)
            if t > 0:
                delay_map[name] = t

        x = sorted(delay_map.items(), key=lambda x:x[1], reverse=False)
        return x

    # 切换最快节点
    def switch_fastest_proxy(self):
        d = self.get_all_proxy_delay()
        name, t = d[0]
        print(name)

        r = put('http://{0}/proxies/Proxy'.format(self.__url),
                data=dumps({'name': name}),
                headers={"Content-Type": "application/json"})
        print(r.text)
        if r.status_code == 204:
            return True

        return False

a = AutoSwitchNode()
x = a.switch_fastest_proxy()
print(x)
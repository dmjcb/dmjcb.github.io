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

    def get_fastest_proxy_delay(self):
        delay = {}
        for name in self.get_proxy_name_list():
            t = self.get_proxy_delay(name)
            if t > 0:
                delay[name] = t
        x = sorted(delay.items(), key=lambda x:x[1], reverse=False)
        return x[0]

    def switch_fastest_proxy(self):
        name, v = self.get_fastest_proxy_delay()

        r = put('http://{0}/proxies/Proxy'.format(self.__url), data=dumps({'name': name}),headers={"Content-Type": "application/json"})
        if r.status_code == 204:
            print('select: {0}, delay: {1}'.format(name, v))
        else:
            print('select error')

if __name__ == "__main__":
    auto = AutoSwitchNode()
    auto.switch_fastest_proxy()
    #http://112.126.28.203/
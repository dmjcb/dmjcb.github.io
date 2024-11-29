# 监听粘贴板, 发现内容为Snipaste截取图片地址后修改为图床地址
import pyperclip
import time
import re

def match_datetime_format(date_str):
    pattern = r'^\d{4}(0[1-9]|1[0-2])(0[1-9]|[12][0-9]|3[01])_(0[0-9]|1[0-9]|2[0-3])[0-5][0-9][0-5][0-9]$'
    return re.match(pattern, date_str)

def listen_clipboard():
    while True:
        content = pyperclip.paste()
        e = content.splitlines()
        if e:
            v = e[0]
            # 匹配图片格式为 20241110_235952.jpg
            if '.jpg' in v and match_datetime_format(v.split('.')[0]):
                v = "![](/assets/image/{0})".format(v)
                pyperclip.copy(v)
                print(v)
        else:
            print("null")

        time.sleep(1)

if __name__ == "__main__":
    listen_clipboard()
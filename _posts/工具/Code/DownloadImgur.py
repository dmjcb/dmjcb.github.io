'''
Brief        : 下载md文件中云图床文件到本地
Author       : dmjcb
Date         : 2024-09-24 20:03:51
LastEditors  : dmjcb@outlook.com
LastEditTime : 2024-09-26 15:25:22
'''

import os
import multiprocessing
from codecs import open
from urllib.request import urlretrieve

from threading import Thread


# 提取指定目录下所有md文件中的图片超链接
def get_urls(dir_path):
    urls = []
    for fpathe, dirs, fs in os.walk(dir_path):
        if ".git" not in fpathe:
            for f in fs:
                name = os.path.join(fpathe, f)
                if ".md" in name:
                    with open(name, "rb", "utf-8", errors="ignore") as text:
                        for line in text:
                            line = line.replace("\r\n", "")
                            if "https://" in line or "http://" in line:
                                x = line.find("(")
                                line = line[x + 1 : -1]
                                urls.append(line)
    return urls


def download_image(_range, urls, dir_path):
    try:
        x, y = _range
        for i in range(x, y + 1):
            if i > len(urls):
                break
            _, n = urls[i].split("img/")
            urlretrieve(urls[i], dir_path + n)
    except Exception as e:
        print(e)


if __name__ == "__main__":
    blog_path = "c:\\Users\\dmjcb\\Documents\\blog"
    image_path = "c:\\Users\\dmjcb\\Documents\\Image\\"

    urls = get_urls(blog_path)

    cpu_count = multiprocessing.cpu_count()

    t = []
    max_count = 400
    x = 0
    for i in range(cpu_count):
        y = max_count // cpu_count * (i + 1)
        t.append(Thread(target=download_image, args=((x, y), urls, image_path)))
        x = y + 1

    for i in t:
        i.start()

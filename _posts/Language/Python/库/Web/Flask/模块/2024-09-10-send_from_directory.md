---
title: "send_from_directory"
date: 2024-09-10
categories: [Python]
tags: [Python]
excerpt: "send_from_directory"
---

# send_from_directory

## 返回静态文件

```py
send_from_directory('文件目录', 文件名)
```

```py
@app.route('/<path>')
def get_image(path):
    return send_from_directory('templates', path)
```

图片路径为/templates/a.jpg, 访问127.0.0.1:5000/a.jpg即返回静态文件

![](https://raw.githubusercontent.com/dmjcb/SelfImgur/main/20211113191621.png)

![](https://raw.githubusercontent.com/dmjcb/SelfImgur/main/2021-07-06_01-44-37.jpg)
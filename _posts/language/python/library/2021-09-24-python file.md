---
title: "python file操作"
date: 2021-09-24
categories: [python]
tags: [python]
excerpt: "file"
---

## 创建

```py
import os

path = "a.txt"

f = open(path, 'w', encoding = 'utf-8')
if os.path.exists(path):
    f.close()
```

### 临时文件

tempfile.NamedTemporaryFile 函数用于创建具有特定名称的临时文件

```py
def touch_tmp_file(request):
    id = request.GET['id']
    tmp_file = tempfile.NamedTemporaryFile(prefix=id)
    return HttpResponse(f"tmp file: {tmp_file} created!", content_type='text/plain')
```

## 修改

### 写入追加

- `'w'`写入, `'a'`追加

```py
import os

path = 'a.txt'
with open(path, 'w', encoding = 'utf-8') as f:
    f.write("11111111111\n")

# 追加
with open(path, 'a', encoding = 'utf-8') as f:
    f.write("22222222222\n")
```

### 重命名
  
```py
os.rename(old_path, new_path)
```

## 移动

```py
import os
import shutil

def move_file(source_path: str, target_path: str):
    # 待移动文件不存在
    if not os.path.isfile(source_path):
        return
    path, name = os.path.split(target_path)
    if not os.path.exists(path):
        os.makedirs(path)
    # 复制文件 shutil.copyfile() 
    shutil.move(source_path,  target_path)
```

## 删除

```py
def del_file(path: str):
    if not os.path.exists(path):
        return
    os.remove(path)
```

## 显示

### 读取

```py
import os

path = 'a.txt'

with open(path, 'r', encoding = 'utf-8') as f:
    # 整体读取
    data = f.read()
    print("data = ", data)
    
with open(path, 'r', encoding = 'utf-8') as f:
    # 逐行读取
    for i in f.readlines():
        print('line = ', i)
```

### 显示文件

```py
import os

path = './'

def display_all_files(folder_path: str):
    for i in os.listdir(folder_path):
        path = os.path.join(folder_path, i)
        # 若是文件则显示
        if os.path.isfile(path):
            print(path)

display_all_files(path)
```

### 递归显示

```py
def display_all_folders(folder_path: str):
    for i in os.listdir(folder_path):
        path = os.path.join(folder_path, i)
        # 若该对象是文件夹
        if os.path.isdir(path):
            display_all_files(path)
```

## 问题

### 路径错误

Windows路径中 `\` 会被视作转义字符, 导致路径错误

若文件路径为`C:\Users\XXX\Desktop\x.txt`, 需改为

```sh
r'C:\Users\XXX\Desktop\x.txt' 

# 或
'C:\\Users\XXX\Desktop\\x.txt' 

# 或
'C:/Users/XXX/Desktop/x.txt'
```
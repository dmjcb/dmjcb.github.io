# 自动提交流程

import os
import sys
from codecs import open
from subprocess import run

# 1. 
#   SelfBlog/ git push
# 2. 
#   2.1 dmjcb.github.io/_posts
#       git pull
#   2.2dmjcb.github.io/assets/SelfImgur
#       git pull
#   2.3 replace image path
# 3. 
#   dmjcb.github.io/ git push


def __push():
    command = "git add ."
    r = run(command, shell=True, capture_output=True, text=True)
    print(r.stdout)

    command = "git commit -m " + "" + sys.argv[1] + ""
    r = run(command, shell=True, capture_output=True, text=True)
    print(r.stdout)

    command = "git push"
    r = run(command, shell=True, capture_output=True, text=True)
    print(r.stdout)


def __pull():
    command = "git pull"
    r = run(command, shell=True, capture_output=True, text=True)
    print(r.stdout)


def push_self_blog():
    dir_path = "C:\\Users\\dmjcb\\Documents\\Code\\SelfBlog"
    os.chdir(dir_path)

    __push()
    

def pull_self_blog():
    dir_path = "C:\\Users\\dmjcb\\Documents\\Code\\dmjcb.github.io\\_posts"
    os.chdir(dir_path)

    __pull()

def pull_self_imgur():
    dir_path = "C:\\Users\\dmjcb\\Documents\\Code\\dmjcb.github.io\\assets\\SelfImgur"
    os.chdir(dir_path)

    __pull()

def replace_imgage_url():
    dir_path = "C:\\Users\\dmjcb\\Documents\\Code\\dmjcb.github.io\\_posts"
    for fpathe, dirs, fs in os.walk(dir_path):
        for f in fs:
            name = os.path.join(fpathe, f)
            print(name)
            if ".md" in name:
                with open(name, "rb", "utf-8", errors="ignore") as text:
                    lines = text.readlines()
                    
                s = "https://raw.githubusercontent.com/dmjcb/SelfImgur/main/"
                with open(name, 'w', encoding='utf-8') as file:
                    for line in lines:
                        if s in line:
                            line = line.replace(s, "/assets/SelfImgur/")
                        file.write(line)


def push_blog():
    dir_path = "C:\\Users\\dmjcb\\Documents\\Code\\dmjcb.github.io"
    os.chdir(dir_path)

    __push()

replace_imgage_url()
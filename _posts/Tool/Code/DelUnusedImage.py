# 删除未使用图片
import os
from codecs import open

# 提取指定目录下所有md文件中图片超链接
def get_md_picture_url(dir_path):
    urls = []
    n = 0
    for fpathe, dirs, fs in os.walk(dir_path):
        if ".git" not in fpathe:
            for f in fs:
                name = os.path.join(fpathe, f)
                if ".md" in name:
                    with open(name, "rb", "utf-8", errors="ignore") as text:
                        for line in text:
                            line = line.replace("\r\n", "")
                            if "/assets/SelfImgur/" in line:
                                line = line[:-1]
                                urls.append(line.split('/')[-1])
                                n+=1
    return urls

def del_unused_img():
    n = 0
    md_path = "c:\\Users\\dmjcb\\Documents\\Code\\SelfBlog"
    image_path = "c:\\Users\\dmjcb\\Documents\\Code\\SelfBlog\\assets\\SelfImgur"
    
    used_urls = get_md_picture_url(md_path)

    for fpathe, dirs, fs in os.walk(image_path):
        for f in fs:
            if f not in used_urls:
                n+=1
                name = os.path.join(fpathe, f)
                os.remove(name)
            
    print(n)
if __name__ == "__main__":
    del_unused_img()

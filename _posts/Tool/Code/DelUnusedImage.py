# 删除未使用图片
import os
from codecs import open

def del_unused_img():
    # 提取指定目录下所有md文件中图片超链接
    def get_md_picture_url(dir_path):
        urls = []
        url_num = 0
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
                                    url_num += 1
        return urls

    del_num = 0
    dir_path = "c:\\Users\\dmjcb\\Documents\\Code\\SelfBlog"
    image_dir_path = dir_path + "\\assets\\SelfImgur"
    
    used_urls = get_md_picture_url(dir_path)

    for fpathe, dirs, fs in os.walk(image_dir_path):
        for f in fs:
            if f not in used_urls:
                del_num += 1
                name = os.path.join(fpathe, f)
                os.remove(name)
            
    print(del_num)
if __name__ == "__main__":
    del_unused_img()

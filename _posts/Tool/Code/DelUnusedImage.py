import os
import shutil
import codecs
import sys
import subprocess

class CleanUnusedResource:
    __SYSTEM_PATH            = "c:\\Users\\dmjcb\\Documents\\Code"
    __IMGUR_PATH             = "assets\\SelfImgur"
    
    __SELF_BLOG_NAME         = "SelfBlog"
    __SELF_IO_NAME           = "dmjcb.github.io"

    __SELF_BLOG_DIR = "{0}\\{1}".format(__SYSTEM_PATH, __SELF_BLOG_NAME)
    __SELE_IO_DIR = "{0}\\{1}".format(__SYSTEM_PATH, __SELF_IO_NAME)

    __SELF_BLOG_IMGUR_DIR   = "{0}\\{1}".format(__SELF_BLOG_DIR, __IMGUR_PATH)
    __SELF_IO_IMGUR_DIR = "{0}\\{1}".format(__SELE_IO_DIR, __IMGUR_PATH)

    used_iamge_count         = 0


    # 从SelfBlog所有.md中获取图片url, 提取图片名
    def get_used_images(self):
        used_images = []
        for fpathe, dirs, fs in os.walk(self.__SELF_BLOG_DIR):
            if ".git" not in fpathe:
                for f in fs:
                    name = os.path.join(fpathe, f)
                    if ".md" in name:
                        with codecs.open(name, "rb", "utf-8", errors="ignore") as text:
                            for line in text:
                                line = line.replace("\r\n", "")
                                # 示例, ![](/assets/SelfImgur/20241022204809.png)
                                if "/assets/SelfImgur/" in line:
                                    # 去除末尾)符号
                                    line = line[:-1]
                                    image_name = line.split('/')[-1]
                                    used_images.append(image_name)
                                    self.used_iamge_count += 1
        return used_images


    # 从SelfBlog/assets/SelfImgur中获取所有文件名与路径
    def get_self_imgur_files(self):
        files = []
        for fpathe, dirs, fs in os.walk(self.__SELF_BLOG_IMGUR_DIR):
            for f in fs:
                path = os.path.join(fpathe, f)
                files.append(f)

        return files


    # 删除SelfBlog/assets/SelfImgur中未使用的图片
    def del_self_blog_imgur_usused_files(self):
        used_files = self.get_used_images()
        del_count = 0

        for fpathe, dirs, fs in os.walk(self.__SELF_BLOG_IMGUR_DIR):
            for f in fs:     
                if f not in used_files:
                    del_count += 1
                    name = os.path.join(fpathe, f)
                    os.remove(name)

        print("SelfBlog SelfImfur del {0} imges".format(del_count))


    def copy_self_imgur_dir(self):
        src_files = os.listdir(self.__SELF_BLOG_IMGUR_DIR)
        for file_name in src_files:
            full_file_name = os.path.join(self.__SELF_BLOG_IMGUR_DIR, file_name)
            if os.path.isfile(full_file_name):
                shutil.copy(full_file_name, self.__SELF_IO_IMGUR_DIR)

    # 删除dmjcb.github.io/assets/SelfImgur中未使用的图片
    def del_io_imgur_unused_files(self):
        used_files = self.get_self_imgur_files()

        del_count = 0
        for fpathe, dirs, fs in os.walk(self.__SELF_IO_IMGUR_DIR):
            for f in fs:
                if f not in used_files:
                    name = os.path.join(fpathe, f)
                    os.remove(name)
                    del_count += 1

        print("SelfBlog SelfImfur del {0} imges".format(del_count))


    def del_and_copy_image(self):
        self.del_self_blog_imgur_usused_files()
        self.copy_self_imgur_dir()
        self.del_io_imgur_unused_files()


    def git_pipline(self):
        os.chdir(self.__SELF_BLOG_DIR)
        pipline = ["git add .", "git commit -m {0}".format(sys.argv[1])]
        for sh in pipline:
            r = subprocess.run(sh, shell=True, capture_output=True, text=True)

        os.chdir("{0}\\_posts".format(self.__SELE_IO_DIR))
        r = subprocess.run("git pull", shell=True, capture_output=True, text=True)

        os.chdir(self.__SELE_IO_DIR)
        pipline = ["git add .", "git commit -m {0}".format(sys.argv[1])]
        for sh in pipline:
            r = subprocess.run(sh, shell=True, capture_output=True, text=True)

    def run(self):
        # self.del_and_copy_image()
        self.git_pipline()


clean = CleanUnusedResource()
clean.run()
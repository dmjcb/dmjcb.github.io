import os
import shutil
import codecs
import sys
import subprocess

class AutoUploadBlog:
    __ROOT_DIR        = "c:\\Users\\dmjcb\\Documents\\Code"
    __IMGUR_DIR       = "assets\\SelfImgur"
    __CODE_DIR        = "assets\\SelfCode"

    __BLOG_DIR        = "{0}\\SelfBlog".format(__ROOT_DIR)
    __JEYLL_DIR       = "{0}\\dmjcb.github.io".format(__ROOT_DIR)

    __BLOG_IMGUR_DIR  = "{0}\\{1}".format(__BLOG_DIR, __IMGUR_DIR)
    __JEYLL_IMGUR_DIR = "{0}\\{1}".format(__JEYLL_DIR, __IMGUR_DIR)


    # 从所有.md中获取图片url
    def _get_used_images(self):
        used_images = []
        for fpathe, dirs, fs in os.walk(self.__BLOG_DIR):
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

        return used_images
    
    # 删除SelfBlog/assets/SelfImgur中未使用的图片
    def del_blog_unused_images(self):
        used_files = self._get_used_images()
        count = 0
        for path, dirs, file_list in os.walk(self.__BLOG_IMGUR_DIR):
            for f in file_list:     
                if f not in used_files:
                    count += 1
                    name = os.path.join(path, f)
                    os.remove(name)

        print("1. SelfBlog SelfImgur del {0} images".format(count))


    def copy_imgur_dir(self):
        copy_count = 0
        src_files = os.listdir(self.__BLOG_IMGUR_DIR)
        for name in src_files:
            f = os.path.join(self.__BLOG_IMGUR_DIR, name)
            if os.path.isfile(f):
                shutil.copy(f, self.__JEYLL_IMGUR_DIR)
                copy_count += 1
        
        print("2. Copy {0} images".format(copy_count))


    def _get_imgur_list(self):
            files = []
            for path, dirs, file_list in os.walk(__BLOG_IMGUR_DIR):
                for f in file_list:
                    path = os.path.join(path, f)
                    files.append(f)

        return files


    # 删除dmjcb.github.io/assets/SelfImgur中未使用的图片
    def del_jeyll_unused_images(self):
        used_files = self._get_imgur_list()

        count = 0
        for path, dirs, file_list in os.walk(self.__JEYLL_IMGUR_DIR):
            for f in file_list:
                if f not in used_files:
                    name = os.path.join(path, f)
                    os.remove(name)
                    count += 1

        print("3. dmjgb.github.io SelfImgur del {0} images".format(count))


    def update_images(self):
        self.del_blog_unused_images()
        self.copy_imgur_dir()
        self.del_jeyll_unused_images()


    def git_pipline(self):
        def __run(command):
            r = subprocess.run(command, shell=True, capture_output=True, text=True, encoding="utf8")
            print(r.stdout)
            print()
        
        def __pull():
            sh = "git pull"
            __run(sh)

        def __push():
            sh = "git add . && git commit -m {0} && git push".format(sys.argv[1])
            __run(sh)
        
        print("4. run git")

        os.chdir(self.__BLOG_DIR)
        __push()

        os.chdir("{0}\\_posts".format(self.__JEYLL_DIR))
        __pull()

        os.chdir(self.__JEYLL_DIR)
        __push()


    def run(self):
        self.update_images()

        self.git_pipline()


if __name__ == "__main__":
    upload = AutoUploadBlog()
    upload.del_blog_unused_images()
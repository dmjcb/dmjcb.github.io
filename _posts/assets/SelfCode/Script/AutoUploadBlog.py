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

    __BLOG_CODE_DIR   = "{0}\\{1}".format(__BLOG_DIR, __CODE_DIR)
    __JEYLL_CODE_DIR  = "{0}\\{1}".format(__JEYLL_DIR, __CODE_DIR)

    blog_used_images  = []

    def __init__(self):
        for f in self.get_files_ap(self.__BLOG_DIR):
            if "md" == f[-2:]:              
                urls = self.extract_imgurs_url(f)
                self.blog_used_images.extend(urls)

    def extract_file_name(self, file_path):
        f = '\\'
        if '/' in file_path:
            f = '/'
        return file_path.split(f)[-1]

    def get_files_ap(self, dir_path):
        files = []
        for path, dirs, fs in os.walk(dir_path):
            if ".git" in path:
                continue
            for f in fs:
                ap = os.path.join(path, f)
                files.append(ap)
        return files

    def extract_imgurs_url(self, md_file):
        x = []
        with codecs.open(md_file, "rb", "utf-8", errors="ignore") as text:
            for line in text:
                line = line.replace("\r\n", "")
                # example: ![](/assets/SelfImgur/20241022204809.png)
                if "/assets/SelfImgur/" in line:
                    name = self.extract_file_name(line[:-1])
                    x.append(name)
        return x

    def del_unused_images(self):
        count = 0
        for ap in self.get_files_ap(self.__BLOG_IMGUR_DIR):
            if self.extract_file_name(ap) not in self.blog_used_images:
                count += 1
                os.remove(ap)
        return count
    
    def clean_folder(self, folder_path):
        if os.path.exists(folder_path) and os.path.isdir(folder_path):
            for name in os.listdir(folder_path):
                path = os.path.join(folder_path, name)
                if os.path.isfile(path):
                    os.remove(path)
                elif os.path.isdir(path):
                    shutil.rmtree(path)
            print(f"{folder_path} already clean")

    def copy_folder(self, source_dir, target_dir):
        if os.path.exists(source_dir) and os.path.isdir(source_dir):
            shutil.copytree(source_dir, target_dir, dirs_exist_ok=True)
            print(f"{source_dir} already copy {target_dir}")

    def manage_resource(self):
        count = self.del_unused_images()
        print("SelfBlog SelfImgur del {0} images".format(count))

        self.clean_folder(self.__JEYLL_IMGUR_DIR)
        self.clean_folder(self.__JEYLL_CODE_DIR)
        self.copy_folder(self.__BLOG_IMGUR_DIR, self.__JEYLL_IMGUR_DIR)
        self.copy_folder(self.__BLOG_CODE_DIR, self.__JEYLL_CODE_DIR)

    def git_pipline(self):
        def __run(command):
            r = subprocess.run(command, shell=True, capture_output=True, text=True, encoding="utf8")
            print(r.stdout)
        
        def __pull():
            sh = "git pull"
            __run(sh)

        def __push():
            msg = sys.argv[1]
            if msg == "":
                msg = "defualt add"
            sh = "git add . && git commit -m {0} && git push".format(msg)
            __run(sh)
        
        print("4. run git")

        os.chdir(self.__BLOG_DIR)
        __push()

        os.chdir("{0}\\_posts".format(self.__JEYLL_DIR))
        __pull()

        os.chdir(self.__JEYLL_DIR)
        __push()

    def run(self):
        self.manage_resource()
        self.git_pipline()


if __name__ == "__main__":
    upload = AutoUploadBlog()
    upload.run()
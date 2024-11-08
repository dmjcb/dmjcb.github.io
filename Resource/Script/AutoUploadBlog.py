import os
import shutil
import codecs
import sys
import subprocess

class AutoUploadBlog:
    __ROOT_DIR        = "c:\\Users\\dmjcb\\Documents\\Code"

    __BLOG_DIR        = "{0}\\SelfBlog".format(__ROOT_DIR)
    __JEYLL_DIR       = "{0}\\dmjcb.github.io".format(__ROOT_DIR)

    __RESOURCE_DIR    = "Resource"

    def del_unused_images(self):
        def __extract_file_name(path):
            f = '\\'
            if '/' in path:
                f = '/'
            return path.split(f)[-1]

        def __get_files_ap(dir_path):
            files = []
            for path, dirs, fs in os.walk(dir_path):
                if ".git" in path:
                    continue
                for f in fs:
                    ap = os.path.join(path, f)
                    files.append(ap)
            return files

        def __extract_imgurs_url(md_file):
            imgs = []
            with codecs.open(md_file, "rb", "utf-8", errors="ignore") as text:
                for line in text:
                    line = line.replace("\r\n", "")
                    # example: ![](/Resource/Imgur/20241022204809.png)
                    if "/Resource/Imgur/" in line:
                        name = __extract_file_name(line[:-1])
                        imgs.append(name)
            return imgs

        # 提取md中已使用图片URL
        used_imgs = ["head.jpg", "workbench.jpg"]
        for f in __get_files_ap(self.__BLOG_DIR):
            if "md" == f[-2:]:              
                urls = __extract_imgurs_url(f)
                used_imgs.extend(urls)

        # 删除未使用图片
        imgur_dir  = "{0}\\{1}\\Imgur".format(self.__BLOG_DIR, self.__RESOURCE_DIR)
        count = 0
        for ap in __get_files_ap(imgur_dir):
            name = __extract_file_name(ap)
            if name not in used_imgs:
                count += 1
                os.remove(ap)
                    
        return count


    def run_cmd(self, command):
        r = subprocess.run(command, shell=True, capture_output=True, text=True, encoding="utf8")
        print(r.stdout)
    

    def git_push(self):
        msg = sys.argv[1]
        if msg == "":
            msg = "defualt add"

        sh = "git add . && git commit -m {0} && git push".format(msg)
        self.run_cmd(sh)


    def upload_blog(self):
        count = self.del_unused_images()
        print("blog del {0} images".format(count))

        os.chdir(self.__BLOG_DIR)
        self.git_push()
    

    def update_resource(self):
        def __clean_folder(folder_path):
            if os.path.exists(folder_path) and os.path.isdir(folder_path):
                for name in os.listdir(folder_path):
                    path = os.path.join(folder_path, name)
                    if os.path.isfile(path):
                        os.remove(path)
                    elif os.path.isdir(path):
                        shutil.rmtree(path)
                print(f"{folder_path} already clean")

        def __copy_folder(source_dir, target_dir):
            if os.path.exists(source_dir) and os.path.isdir(source_dir):
                shutil.copytree(source_dir, target_dir, dirs_exist_ok=True)
                print(f"{source_dir} already copy {target_dir}")

        SOURRC_DIR = "{0}\\_posts\\{1}".format(self.__JEYLL_DIR, self.__RESOURCE_DIR)
        TARGET_DIR = "{0}\\{1}".format(self.__JEYLL_DIR, self.__RESOURCE_DIR)

        __clean_folder(TARGET_DIR)
        __copy_folder(SOURRC_DIR, TARGET_DIR)


    def upload_jekyll(self):
        os.chdir("{0}\\_posts".format(self.__JEYLL_DIR))
        self.run_cmd("git pull")

        self.update_resource()

        os.chdir(self.__JEYLL_DIR)
        self.git_push()


if __name__ == "__main__":
    auto = AutoUploadBlog()
    auto.upload_blog()
    auto.upload_jekyll()
import os
import shutil
import codecs
import subprocess
import tempfile
from datetime import datetime


class AutoGit:
    def run_cmd(self, command):
        r = subprocess.run(command, shell=True, capture_output=True, text=True, encoding="utf8")
        print(r.stdout)
        return r.stdout
    
    def pull(self, path):
        os.chdir(path)
        self.run_cmd("git pull")

    def push(self, path, msg):
        os.chdir(path)
        self.run_cmd("git add . && git commit -m {0} && git push".format(msg))
    
    def status(self, path):
        os.chdir(path)
        r =  self.run_cmd("git status {0}".format(path))
        if "Your branch is up to date" in r and "nothing to commit, working tree clean" in r:
            return True
        return False

    def clone(self, path, address):
        os.chdir(path)
        print('clone ', path)
        self.run_cmd("git clone {0} .".format(address))


class AutoUploadBlog:
    _ROOT           = "c:\\Users\\dmjcb\\Documents\\code"
    _BLOG_DIR       = "{0}\\self_blog".format(_ROOT)
    _JEKYLL_DIR     = "{0}\\dmjcb.github.io".format(_ROOT)
    _ASSETS_DIR     = "{0}\\self_assets".format(_ROOT)
    _ASSETS_PUBLIC  = "assets\\public"

    _BLOG_ASSETS_IMAGE_DIR= "{0}\\assets\\image".format(_BLOG_DIR)

    _URL            = "https://dmjcb.github.io"
    _BLOG_PROJECT   = "git@github.com:dmjcb/self_blog.git"
    _JEKYLL_PROJECT = "git@github.com:dmjcb/dmjcb.github.io.git"
    _ASSETS_PROJECT  = "git@github.com:dmjcb/self_assets.git"

    auto_git = AutoGit()

    def clone_project(self):
        for url in (self._BLOG_PROJECT, self._JEKYLL_PROJECT, self._ASSETS_PROJECT):
            auto_git.clone(self._ROOT, url)


    def is_exist_modify(self, path):
        return not self.auto_git.status(path)


    def get_root_path(self):
        absolute_path = os.path.abspath(__file__)
        x = absolute_path
        for i in range(5):
            x = os.path.dirname(x)
        return x


    def clean_unused_images(self):
        def extract_files_ap(folder):
            aps = []
            for path, dirs, fs in os.walk(folder):
                if ".git" in path or "public" in path:
                    continue
                for f in fs:
                    aps.append(os.path.join(path, f))
            return aps  

        def get_used_images_ap(project_folder):
            def get_ap(image_name):
                return "{0}\\{1}".format(self._BLOG_ASSETS_IMAGE_DIR, image_name)

            def extract_image_ap(md_file):
                aps = []
                with codecs.open(md_file, "rb", "utf-8", errors="ignore") as t:
                    for line in t:
                        line = line.replace("\r\n", "")
                        # example: ![](/assets/image/20241022204809.png)
                        if "/assets/image/" in line:
                            name = line.split('/')[-1][:-1]
                            aps.append(get_ap(name))
                return aps

            image_ap = [get_ap("head.jpg"), get_ap("workbench.jpg")]
            md_files =  extract_files_ap(project_folder)
            for f in md_files:
                if "md" == f[-2:]:              
                    image_ap.extend(extract_image_ap(f))
            
            return image_ap
    
        used_images_ap = get_used_images_ap(self._BLOG_DIR)
        now_images_ap = extract_files_ap(self._BLOG_ASSETS_IMAGE_DIR)

        count = 0
        for ap in now_images_ap:
            if ap not in used_images_ap:
                count += 1
                print('name = ', ap)
                os.remove(ap)
        
        return count


    def upload_blog(self, msg):
        print("更新self_blog项目")

        count = self.clean_unused_images()

        assets_dir = "{0}\\assets".format(self._BLOG_DIR)
        if self.is_exist_modify(assets_dir):
            print("更新self_assets")

            def del_files_except_git(folder):
                for item in os.listdir(folder):
                    item_path = os.path.join(folder, item)
                    if item == '.git':
                        continue
                    if os.path.isfile(item_path) or os.path.islink(item_path):
                        os.unlink(item_path)
                    elif os.path.isdir(item_path):
                        shutil.rmtree(item_path)

            del_files_except_git(self._ASSETS_DIR)
            shutil.copytree(assets_dir, self._ASSETS_DIR, dirs_exist_ok=True)

            self.auto_git.push(self._ASSETS_DIR, msg)
        
        self.auto_git.push(self._BLOG_DIR, msg)


    def upload_jekyll(self, msg):
        def copy_with_ignore_git(src_dir, dst_dir):
            if os.path.exists(dst_dir):
                shutil.rmtree(dst_dir)

            def ignore_git(dir, files):
                ignore_list = {".git", "public"}
                return {name for name in files if name in ignore_list}
                
            shutil.copytree(src_dir, dst_dir, ignore=ignore_git, dirs_exist_ok=True)
        
        print("更新dmjcb.github.io项目")
        src_dir = self._BLOG_DIR   
        des_dir =  "{0}\\_posts".format(self._JEKYLL_DIR)
        copy_with_ignore_git(src_dir, des_dir)

        # 拷贝静态资源
        src_dir = "{0}\\assets\\image".format(self._BLOG_DIR)
        des_dir = "{0}\\assets\\image".format(self._JEKYLL_DIR)
        copy_with_ignore_git(src_dir, des_dir)

        self.auto_git.push(self._JEKYLL_DIR, msg)


    def change_md_to_public(self, md_name):
        def get_url(categories, file_name):
            x = categories.replace("/r", "").replace("/n", "").replace(" ", "").split(":")[-1]
            x = x[1:-2].lower().split(',')
            y = ''
            for i in x:
                y = '{0}/{1}'.format(y, i)

            title = file_name.split('-')[-1][:-3]

            url = "{0}{1}/{2}".format(self._URL, y, title)
            return url

        def find_file_absolute_path(folder, name):
            for root, dirs, files in os.walk(folder):
                if files:
                    for f in files:
                        if name in f:
                            x = os.path.abspath(os.path.join(root, f))
                            if 'public' not in x:
                                return x, f
            return None

        def get_md_content(path):
            if path == None:
                return
            with open(path, 'r', encoding='utf-8') as f:
                x = f.readlines()
            return x

        path, name = find_file_absolute_path(self._BLOG_DIR, md_name)
        lines = get_md_content(path)
        origin_url = get_url(lines[3], name)
        new_text = ['> [dmjcb个人博客](https://dmjcb.github.io/)\n', '> [原文地址]({0})\n'.format(origin_url)]
        for i, text in enumerate(lines):
            if i < 7:
                continue
            if text == '```c++\n' or text == '```cmake\n':
                text = '```c\n'
            if text == '```sh\n':
                text = '```shell\n'
            if '/assets/image' in text:
                text = text.replace('/assets/image', 'https://raw.githubusercontent.com/dmjcb/self_assets/main/image')

            new_text.append(text)

        title = lines[1].replace("/r", "").replace("/n", "").split(":")[-1]
        path = "{0}\\{1}\\{2}.md".format(self._BLOG_DIR, self._ASSETS_PUBLIC, title[2:-2])
        with open(path, 'w', encoding='utf-8') as f:
            f.writelines(new_text)


    def create_new_blog(self, name):  
        date = datetime.now().strftime("%Y-%m-%d")
        file_name = "{0}-{1}.md".format(date, name)

        lines = [
            "---\n",
            'title: "{0}"\n'.format(name),
            "date: {0}\n".format(date),
            "categories: []\n",
            "tags: []\n",
            'excerpt: "{0}"\n'.format(name),
            "---\n"
        ]

        with open(file_name, "w") as f:
            f.writelines(lines)

if __name__ == "__main__":
    auto = AutoUploadBlog()
    print(auto.get_root_path())
    index = input('1. 删除无用图片\n2. 上传blog\n3. 上传jekyll\n4. 都上传\n5. 转换博客为发行格式\n6. 创建新博客\n')
    index = int(index)
    if index == 1:
        r = auto.clean_unused_images()
        print(r)
    elif index == 2:
        msg = input('commit info: ')
        auto.upload_blog(msg)
    elif index == 3:
        msg = input('commit info: ')
        auto.upload_jekyll(msg)
    elif index == 4:
        msg = input('commit info: ')
        auto.upload_blog(msg)
        auto.upload_jekyll(msg)
    elif index == 5:
        path = input('name: ')
        auto.change_md_to_public(path)
    elif index == 6:
        name = input('name: ')
        auto.create_new_blog(name)
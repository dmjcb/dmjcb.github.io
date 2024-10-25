# 提交博客脚本

if($args[0]) {
    $commitInfo=$args[0]
}
else {
    $commitInfo="update"
}

# 1.提交博客
cd "C:\Users\dmjcb\Documents\Code\SelfBlog"
git add . 
git commit -m $args[0]
git push 

# 2.在博客框架中拉取最新博客
cd "C:\Users\dmjcb\Documents\Code\dmjcb.github.io\_posts"
git pull

# 3.更新博客中的图片
Copy-Item -Path "C:\Users\dmjcb\Documents\Code\SelfBlog\assets\SelfImgur\*" -Destination "C:\Users\dmjcb\Documents\Code\dmjcb.github.io\assets\SelfImgur\" -Force

# 4.更新博客框架
cd ..
git add . 
git commit -m $args[0]
git push

cd -Path "C:\Users\dmjcb"
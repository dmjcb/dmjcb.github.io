# 同时更新SelfBlog与.github.io

if($args[0]) {
    $commitInfo=$args[0]
}
else {
    $commitInfo="update"
}

cd "C:\Users\dmjcb\Documents\Code\SelfBlog"
git add . 
git commit -m $args[0]
git push 

cd "C:\Users\dmjcb\Documents\Code\dmjcb.github.io\_posts"
git pull

cd ..
git add . 
git commit -m $args[0]
git push

cd "C:\Users\dmjcb"
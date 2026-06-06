import re
import shutil
import subprocess
from pathlib import Path
from typing import List


class GitHelper:
    @staticmethod
    def run(args: List[str], cwd: Path) -> subprocess.CompletedProcess[str]:
        return subprocess.run(args, cwd=cwd, capture_output=True, text=True)

    def is_clean(self, repo: Path) -> bool:
        return not self.run(["git", "status", "--porcelain"], repo).stdout.strip()

    def pull_rebase_with_stash(self, repo: Path) -> bool:
        self.run(["git", "stash", "push", "-u"], repo)
        r = self.run(["git", "pull", "--rebase"], repo)
        if r.returncode:
            print("✘ git pull 失败\n", r.stderr.strip())
            return False
        self.run(["git", "stash", "pop"], repo)
        return True

    def push(self, repo: Path, msg: str, pull_first=True) -> bool:
        if pull_first and not self.pull_rebase_with_stash(repo):
            return False

        for cmd in (["git", "add", "."], ["git", "commit", "-m", msg], ["git", "push"]):
            r = self.run(cmd, repo)
            if r.returncode and "nothing to commit" not in r.stdout.lower():
                print(f"✘ {' '.join(cmd)} 失败\n", r.stderr.strip())
                return False

        print(f"✔ git push 成功 ({repo.name})")
        return True


class AutoUpload:
    def __init__(self):
        root = Path.home() / "Documents"

        self.git = GitHelper()
        self.blog = root / "self_blog"
        self.jekyll = root / "dmjcb.github.io"
        self.img = self.blog / "assets" / "image"

    def clean_unused_img(self) -> int:
        IMG_RE = re.compile(r"!\[.*?\]\(/assets/image/(.*?)\)")

        used = {self.img / n for n in {"head.jpg", "workbench.jpg"}}
        for md in self.blog.rglob("*.md"):
            used |= {self.img / m for m in IMG_RE.findall(md.read_text(errors="ignore"))}

        removed = 0
        for f in self.img.iterdir():
            if f.is_file() and not f.name.startswith("_") and f not in used:
                f.unlink()
                removed += 1
        return removed

    def upload_blog(self, msg: str) -> bool:
        removed = self.clean_unused_img()
        if removed:
            print(f"🧹 清理未使用图片: {removed}")

        result = self.git.push(self.blog, msg)
        return result

    def upload_jekyll(self, msg: str) -> None:
        shutil.rmtree(self.jekyll / "_posts", ignore_errors=True)
        shutil.copytree(self.blog, self.jekyll / "_posts", ignore=shutil.ignore_patterns(".git", "assets/image"))

        for g in (self.jekyll / "_posts").rglob(".git"):
            shutil.rmtree(g)

        shutil.rmtree(self.jekyll / "assets/image", ignore_errors=True)
        shutil.copytree(self.img, self.jekyll / "assets/image")

        result = self.git.push(self.jekyll, msg)


if __name__ == "__main__":
    auto = AutoUpload()

    print("1. 删除无用图片\n2. 上传 blog\n3. 上传 jekyll\n4. 都上传")
    c = int(input("选择: ").strip())
    if c == 1:
        print("removed:", auto.clean_unused_img())
    else:
        msg = input("commit info: ").strip()
        if c in {2, 4} and not auto.upload_blog(msg):
            exit("⛔ blog 失败")
        if c in {3, 4}:
            auto.upload_jekyll(msg)

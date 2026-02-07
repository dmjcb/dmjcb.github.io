#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <string>
#include <vector>
#include <cstdlib>


class GitHelper {
public:
    static bool run(const std::vector<std::string>& args) {
        std::string cmd;
        for (const auto& a : args) {
            cmd += a + " ";
        }
        return std::system(cmd.c_str()) == 0;
    }

    static bool is_clean(const std::filesystem::path& repo) {
        std::string cmd = "git -C \"" + repo.string() +
                          "\" status --porcelain > .git_tmp_status";
        std::system(cmd.c_str());

        std::ifstream in(".git_tmp_status");
        bool clean = in.peek() == std::ifstream::traits_type::eof();
        in.close();
        std::filesystem::remove(".git_tmp_status");
        return clean;
    }

    static bool pull_rebase_with_stash(const std::filesystem::path& repo) {
        run({"git", "-C", repo.string(), "stash", "push", "-u"});

        if (!run({"git", "-C", repo.string(), "pull", "--rebase"})) {
            std::cerr << "✘ git pull 失败\n";
            return false;
        }

        run({"git", "-C", repo.string(), "stash", "pop"});
        return true;
    }

    static bool push(const std::filesystem::path& repo,
                     const std::string& msg,
                     bool pull_first) {
        if (pull_first && !pull_rebase_with_stash(repo))
            return false;

        if (!run({"git", "-C", repo.string(), "add", "."})) {
            std::cerr << "✘ git add 失败\n";
            return false;
        }

        run({"git", "-C", repo.string(), "commit", "-m", msg});

        if (!run({"git", "-C", repo.string(), "push"})) {
            std::cerr << "✘ git push 失败\n";
            return false;
        }

        std::cout << "✔ git push 成功 (" << repo.filename().string() << ")\n";
        return true;
    }
};


class AutoUploadBlog {
public:
    AutoUploadBlog() {
        const char* home =
#ifdef _WIN32
            std::getenv("USERPROFILE");
#else
            std::getenv("HOME");
#endif
        root = std::filesystem::path(home) / "Documents" / "code";

        blog_dir = root / "self_blog";
        jekyll_dir = root / "dmjcb.github.io";
        assets_repo = root / "self_assets";
        assets_img_dir = blog_dir / "assets" / "image";
    }

    int clean_unused_img() {
        std::set<std::filesystem::path> used{
            assets_img_dir / "head.jpg",
            assets_img_dir / "workbench.jpg"
        };

        std::regex img_re(R"(!\[.*?\]\(/assets/image/(.*?)\))");

        for (auto& p : std::filesystem::recursive_directory_iterator(blog_dir)) {
            if (p.path().extension() == ".md") {
                std::ifstream in(p.path());
                std::string content((std::istreambuf_iterator<char>(in)),
                                     std::istreambuf_iterator<char>());
                std::smatch m;
                auto it = content.cbegin();
                while (std::regex_search(it, content.cend(), m, img_re)) {
                    used.insert(assets_img_dir / m[1].str());
                    it = m.suffix().first;
                }
            }
        }

        int removed = 0;
        for (auto& img : std::filesystem::directory_iterator(assets_img_dir)) {
            if (img.is_regular_file() &&
                img.path().filename().string()[0] != '_' &&
                !used.count(img.path())) {
                std::filesystem::remove(img.path());
                ++removed;
            }
        }
        return removed;
    }

    bool upload_assets(const std::string& msg) {
        for (auto& p : std::filesystem::directory_iterator(assets_repo)) {
            if (p.path().filename() != ".git")
                std::filesystem::remove_all(p.path());
        }

        std::filesystem::copy(blog_dir / "assets",
                 assets_repo,
                 std::filesystem::copy_options::recursive |
                 std::filesystem::copy_options::overwrite_existing);

        if (GitHelper::is_clean(assets_repo)) {
            std::cout << "assets 无改动，跳过\n";
            return true;
        }
        return GitHelper::push(assets_repo, msg, false);
    }

    bool upload_blog(const std::string& msg) {
        if (!upload_assets(msg))
            return false;

        int removed = clean_unused_img();
        if (removed)
            std::cout << "🧹 清理未使用图片: " << removed << "\n";

        return GitHelper::push(blog_dir, msg, true);
    }

    void upload_jekyll(const std::string& msg) {
        std::filesystem::remove_all(jekyll_dir / "_posts");
        std::filesystem::copy(blog_dir,
                 jekyll_dir / "_posts",
                 std::filesystem::copy_options::recursive |
                 std::filesystem::copy_options::overwrite_existing);

        std::filesystem::remove_all(jekyll_dir / "assets" / "image");
        std::filesystem::copy(assets_img_dir,
                 jekyll_dir / "assets" / "image",
                 std::filesystem::copy_options::recursive |
                 std::filesystem::copy_options::overwrite_existing);

        GitHelper::push(jekyll_dir, msg, true);
    }

private:
    std::filesystem::path root;
    std::filesystem::path blog_dir;
    std::filesystem::path jekyll_dir;
    std::filesystem::path assets_repo;
    std::filesystem::path assets_img_dir;
};

/* ---------------- main ---------------- */

int main() {
    AutoUploadBlog autoUpload;

    std::cout <<
        "1. 删除无用图片\n"
        "2. 上传 blog\n"
        "3. 上传 jekyll\n"
        "4. 都上传\n";

    int choice;
    std::cout << "选择: ";
    std::cin >> choice;
    std::cin.ignore();

    if (choice == 1) {
        std::cout << "removed: "
                  << autoUpload.clean_unused_img()
                  << "\n";
    } else if (choice >= 2 && choice <= 4) {
        std::string msg;
        std::cout << "commit info: ";
        std::getline(std::cin, msg);

        if (choice == 2 || choice == 4) {
            if (!autoUpload.upload_blog(msg)) {
                std::cerr << "⛔ blog 失败，流程终止\n";
                return 1;
            }
        }
        if (choice == 3 || choice == 4) {
            autoUpload.upload_jekyll(msg);
        }
    }
    return 0;
}

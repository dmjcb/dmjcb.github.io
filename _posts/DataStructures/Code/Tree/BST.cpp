/*
 * @Brief        : 二叉排序树
 * @Author       : dmjcb
 * @Date         : 2022-04-08 22:47:18
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-10-12 16:04:59
 */

#include <iostream>
#include <utility>
#include <vector>
#include <memory>

template <class T>
struct BSTNode {
    T                        mValue;
    std::shared_ptr<BSTNode> mLeftSon;
    std::shared_ptr<BSTNode> mRightSon;

    BSTNode(T value, std::shared_ptr<BSTNode> leftSon, std::shared_ptr<BSTNode> rightSon) :
        mValue(value), mLeftSon(std::move(leftSon)), mRightSon(std::move(rightSon)){}
};

template <class T>
class BinarySearchTree {
public:
    using BSTNode    = BSTNode<T>;
    using BSTNodePtr = std::shared_ptr<BSTNode>;

    explicit BinarySearchTree(const std::vector<T>& value) {
        for (auto v : value) {
            mRoot = InsertNode(mRoot, v);
        }
    }

    void Insert(const T value) {
        mRoot = InsertNode(mRoot, value);
    }

    void Print() {
        if (mRoot != nullptr) {
            PrintBST(mRoot);
        }
    }

    void Delete(const T value) {
        DeleteNode(value);
    }

protected:
    BSTNodePtr InsertNode(BSTNodePtr node, const T value) {
        if (node == nullptr) {
            node = std::make_shared<BSTNode>(value, nullptr, nullptr);
            return node;
        }
        
        if (node->mValue > value) {
            node->mLeftSon = InsertNode(node->mLeftSon, value);
        }
        
        if (node->mValue < value) {
            node->mRightSon = InsertNode(node->mRightSon, value);
        }
        return node;
    }

    BSTNodePtr SearchNode(BSTNodePtr node, const T value) {
        while (node) {
            if (node->mValue == value) {
                return node;
            }
            if (node->mValue > value) {
                node = node->mLeftSon;
            }
            if (node->mValue < value) {
                node = node->mRightSon;
            }
        }
        return nullptr;
    }

    void PrintBST(BSTNodePtr node) {
        if (node == nullptr) {
            return;
        }

        PrintBST(node->mLeftSon);

        std::cout << node->mValue << " ";

        PrintBST(node->mRightSon);
    }

    void DeleteNode(const T value) {
        if (mRoot == nullptr) {
            return;
        }

        // p为待删除节点,fp为其父节点
        BSTNodePtr p = mRoot;
        BSTNodePtr fp = nullptr;
        while (p->mValue != value) {
            fp = p;
            if (p->mValue > value) {
                p = p->mLeftSon;
            }
            if (p->mValue < value) {
                p = p->mRightSon;
            }
        }

        // 情况1:p为叶子节点, 直接删
        if (p->mLeftSon == nullptr && p->mRightSon == nullptr) {
            if (fp->mLeftSon != nullptr) {
                fp->mLeftSon = nullptr;
            }
            if (fp->mRightSon != nullptr) {
                fp->mRightSon = nullptr;
            }
            p.reset();
            return;
        }

        // 情况2:p左子树为空,则重接右子树
        if (p->mLeftSon == nullptr) {
            p->mValue = p->mRightSon->mValue;
            p->mRightSon = nullptr;
            p.reset();
            return;
        }

        // 情况3:p右子树为空,则重接左子树
        if (p->mRightSon == nullptr) {
            p->mValue = p->mLeftSon->mValue;
            p->mLeftSon = nullptr;
            p->mLeftSon.reset();
            return;
        }

        // 情况4:p左右子树均不为空时,需要找p右子树中最小节点(最左节点)q
        BSTNodePtr q = p->mRightSon;
        BSTNodePtr fq = q;

        // 循环查找左节点,就会找到最小值
        while (q->mLeftSon != nullptr) {
            fq = q;
            q = q->mLeftSon;
        }
        fq->mLeftSon = nullptr;
        // 用最小值节点代替欲删除节点
        p->mValue = q->mValue;
        q.reset();
    }

private:
    BSTNodePtr mRoot = nullptr;
};

int main(int argv, char *argc[]) {
    std::vector v = {11, 45, 9, 23, 76, 68};

    BinarySearchTree tree(v);

    std::cout << "二叉排序树的中序遍历结果: ";
    tree.Print();
    std::cout << std::endl;

    // 插入值
    int newNode = 35;
    std::cout << "插入新值:" << newNode << std::endl;
    tree.Insert(newNode);
    std::cout << "插入新值后二叉排序树的中序遍历结果: ";

    tree.Print();
    std::cout << std::endl;

    // 删除值
    int delNode = 11;
    std::cout << "删除值:" << delNode << std::endl;

    tree.Delete(delNode);
    std::cout << "删除值后二叉排序树的中序遍历结果: ";

    tree.Print();
    std::cout << std::endl;
}
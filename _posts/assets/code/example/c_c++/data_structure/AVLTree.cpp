#include <iostream>
#include <algorithm>
#include <memory>

template <typename T>
class AVLTree {
public:
    AVLTree() : mRoot(nullptr) {}
    ~AVLTree() = default;

    void InsertNode(const T& key) { 
        mRoot = Insert(mRoot, key); 
    }

    void RemoveNode(const T& key) { 
        mRoot = Remove(mRoot, key); 
    }

    void PrintInOrder() const { 
        InOrder(mRoot); 
        std::cout << std::endl; 
    }

private:
    struct Node {
        T                     mValue;
        int                   mHeight;
        std::shared_ptr<Node> mLeftChild;
        std::shared_ptr<Node> mRightChlid;

        Node(const T& value) : mValue(value), mLeftChild(nullptr), mRightChlid(nullptr), mHeight(1) {}
    };

    std::shared_ptr<Node> mRoot;

    // 获取节点高度
    int GetHeight(std::shared_ptr<Node> node) const {
        return node ? node->mHeight : 0;
    }

    // 计算平衡因子
    int GetBalanceFactor(std::shared_ptr<Node> node) const {
        return node ? GetHeight(node->mLeftChild) - GetHeight(node->mRightChlid) : 0;
    }

    // 更新节点高度
    void UpdateHeight(std::shared_ptr<Node> node) {
        node->mHeight = 1 + std::max(GetHeight(node->mLeftChild), GetHeight(node->mRightChlid));
    }

    // 左旋操作
    std::shared_ptr<Node> LeftRotatem(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> x = node->mRightChlid;
        std::shared_ptr<Node> t = x->mLeftChild;

        x->mLeftChild = node;
        node->mRightChlid = t;

        UpdateHeight(node);
        UpdateHeight(x);

        return x;
    }

    // 右旋操作
    std::shared_ptr<Node> RightRotatem(std::shared_ptr<Node> node) {
        std::shared_ptr<Node> x = node->mLeftChild;
        std::shared_ptr<Node> t = x->mRightChlid;

        x->mRightChlid = node;
        node->mLeftChild = t;

        UpdateHeight(node);
        UpdateHeight(x);

        return x;
    }

    std::shared_ptr<Node> Insert(std::shared_ptr<Node> node, const T& key) {
        if (!node) {
            return std::make_shared<Node>(key);
        }

        if (key < node->mValue) {
            node->mLeftChild = Insert(node->mLeftChild, key);
        }
        else if (key > node->mValue) {
            node->mRightChlid = Insert(node->mRightChlid, key);
        }
        else {
            return node;
        }
        UpdateHeight(node);

        return BalanceNode(node);
    }

    std::shared_ptr<Node> BalanceNode(std::shared_ptr<Node> node) {
        int balanceFactor = GetBalanceFactor(node);

        // 左重
        if (balanceFactor > 1) {
            if (GetBalanceFactor(node->mLeftChild) < 0) {
                // 左右情况
                node->mLeftChild = LeftRotatem(node->mLeftChild);
            }
            // 左左情况
            return RightRotatem(node);
        }

        // 右重
        if (balanceFactor < -1) {
            if (GetBalanceFactor(node->mRightChlid) > 0) {
                // 右左情况
                node->mRightChlid = RightRotatem(node->mRightChlid);
            }
            // 右右情况
            return LeftRotatem(node);
        }

        return node; // 已经平衡
    }

    // 查找最小值节点
    std::shared_ptr<Node> FindMinNode(std::shared_ptr<Node> node) const {
        while (node->mLeftChild) node = node->mLeftChild;
        return node;
    }

    // 删除节点
    std::shared_ptr<Node> Remove(std::shared_ptr<Node> node, const T& key) {
        if (!node) return node;

        if (key < node->mValue) {
            node->mLeftChild = Remove(node->mLeftChild, key);
        }
        else if (key > node->mValue) {
            node->mRightChlid = Remove(node->mRightChlid, key);
        }
        else {
            // 单子节点或无子节点情况
            if (!node->mLeftChild || !node->mRightChlid) {
                std::shared_ptr<Node> temp = node->mLeftChild ? node->mLeftChild : node->mRightChlid;
                // 无子节点
                if (!temp) { 
                    temp = node;
                    node = nullptr;
                }
                // 单子节点
                else { 
                    node = temp;
                }
            }
            else {
                // 有两个子节点的情况
                std::shared_ptr<Node> temp = FindMinNode(node->mRightChlid);
                node->mValue = temp->mValue;
                node->mRightChlid = Remove(node->mRightChlid, temp->mValue);
            }
        }

        if (!node) {
            return node;
        }

        UpdateHeight(node);
        return BalanceNode(node);
    }

    void InOrder(std::shared_ptr<Node> node) const {
        if (node) {
            InOrder(node->mLeftChild);
            std::cout << node->mValue << " ";
            InOrder(node->mRightChlid);
        }
    }
};

int main() {
    AVLTree<int> tree;
    tree.InsertNode(10);
    tree.InsertNode(20);
    tree.InsertNode(5);
    tree.InsertNode(4);
    tree.InsertNode(15);

    std::cout << "Inorder traversal: ";
    tree.PrintInOrder();

    tree.RemoveNode(10);
    std::cout << "After removing 10: ";
    tree.PrintInOrder();

    return 0;
}
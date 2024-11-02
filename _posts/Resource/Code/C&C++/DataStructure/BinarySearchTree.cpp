#include <iostream>
#include <utility>
#include <vector>
#include <memory>

template <class ValueType>
struct BSTNode {
    ValueType                mValue;
    std::shared_ptr<BSTNode> mLeftSon;
    std::shared_ptr<BSTNode> mRightSon;

    BSTNode(ValueType value, std::shared_ptr<BSTNode> leftSon, std::shared_ptr<BSTNode> rightSon) :
        mValue(value), mLeftSon(std::move(leftSon)), mRightSon(std::move(rightSon)) {}
};

template <class ValueType>
class BinarySearchTree {
public:
    using BSTNodePtr = std::shared_ptr<BSTNode<ValueType>>;

    explicit BinarySearchTree(const std::vector<ValueType>& value) {
        for (auto v : value) {
            mRoot = InsertNode(mRoot, v);
        }
    }

    void Insert(const ValueType value) {
        mRoot = InsertNode(mRoot, value);
    }

    void Print() {
        if (mRoot != nullptr) {
            PrintBST(mRoot);
        }
    }

    void Delete(const ValueType value) {
        DeleteNode(value);
    }

protected:
    BSTNodePtr InsertNode(BSTNodePtr& node, const ValueType value) {
        if (node == nullptr) {
            node = std::make_shared<BSTNode<ValueType>>(value, nullptr, nullptr);
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

    BSTNodePtr SearchNode(BSTNodePtr& node, const ValueType value) {
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

    void PrintBST(BSTNodePtr& node) {
        if (node == nullptr) {
            return;
        }

        PrintBST(node->mLeftSon);

        std::cout << node->mValue << " ";

        PrintBST(node->mRightSon);
    }

    void DeleteNode(const ValueType value) {
        if (mRoot == nullptr) {
            return;
        }

        BSTNodePtr delNode = mRoot;
        BSTNodePtr delFatherNode = nullptr;
        while (delNode->mValue != value) {
            delFatherNode = delNode;
            if (delNode->mValue > value) {
                delNode = delNode->mLeftSon;
            }
            if (delNode->mValue < value) {
                delNode = delNode->mRightSon;
            }
        }

        // case 1, left node
        if (delNode->mLeftSon == nullptr && delNode->mRightSon == nullptr) {
            if (delFatherNode->mLeftSon != nullptr) {
                delFatherNode->mLeftSon = nullptr;
            }
            if (delFatherNode->mRightSon != nullptr) {
                delFatherNode->mRightSon = nullptr;
            }
            delNode.reset();
            return;
        }

        // case 2, leftSon is nullptr, link right subtree
        if (delNode->mLeftSon == nullptr) {
            delNode->mValue = delNode->mRightSon->mValue;
            delNode->mRightSon = nullptr;
            delNode.reset();
            return;
        }

        // case 3, rightSon is nullptr, link left subtree
        if (delNode->mRightSon == nullptr) {
            delNode->mValue = delNode->mLeftSon->mValue;
            delNode->mLeftSon = nullptr;
            delNode->mLeftSon.reset();
            return;
        }

        // case 4,  leftSon rightSon is not nullptr, find min node in delNode's right subtree
        BSTNodePtr minNode = delNode->mRightSon;
        BSTNodePtr minFatherNode = minNode;

        // loop through the left node to find the minimum value
        while (minNode->mLeftSon != nullptr) {
            minFatherNode = minNode;
            minNode = minNode->mLeftSon;
        }
        minFatherNode->mLeftSon = nullptr;

        delNode->mValue = minNode->mValue;
        minNode.reset();
    }

private:
    BSTNodePtr mRoot = nullptr;
};

int main(int argv, char* argc[]) {
    std::vector<int> v = { 11, 45, 9, 23, 76, 68 };

    BinarySearchTree<int> tree(v);

    std::cout << "InOrderPrint: ";
    tree.Print();
    std::cout << std::endl;

    int newNode = 35;
    std::cout << "Insert new value:" << newNode << std::endl;
    tree.Insert(newNode);
    std::cout << "InOrderPrint: ";
    tree.Print();
    std::cout << std::endl;

    int delNode = 11;
    std::cout << "Delete value:" << delNode << std::endl;
    tree.Delete(delNode);
    std::cout << "InOrderPrint: ";

    tree.Print();
    std::cout << std::endl;
}
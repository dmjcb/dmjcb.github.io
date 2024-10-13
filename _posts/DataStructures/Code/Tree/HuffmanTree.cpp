/*
 * @Brief        : 哈夫曼算法实现
 * @Author       : dmjcb
 * @Date         : 2024-09-24 20:03:51
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-10-13 12:12:22
 */


#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <queue>
#include <map>

template<typename NodeType, typename WeightType>
struct Node {
    NodeType              mName;
    WeightType            mFrequency;
    std::shared_ptr<Node> mLeftChild;
    std::shared_ptr<Node> mRightChild;

    Node(NodeType name, WeightType freq):
        mName(name), mFrequency(freq), mLeftChild(nullptr), mRightChild(nullptr) {}

    Node(NodeType name, WeightType freq, std::shared_ptr<Node> left, std::shared_ptr<Node> right):
        mName(name), mFrequency(freq), mLeftChild(std::move(left)), mRightChild(std::move(right)) {}
};

template<typename NodeType, typename WeightType>
class HuffmanTree {
public:
    using Node    = Node<NodeType, WeightType>;
    using NodePtr = std::shared_ptr<Node>;

    explicit HuffmanTree(std::map<NodeType, WeightType> &table) {
        auto Compare = [](NodePtr node1, NodePtr node2) {return node1->mFrequency > node2->mFrequency;};
        std::priority_queue<NodePtr, std::vector<NodePtr>, decltype(Compare)> minHeap(Compare);

        for (const auto&[k, v] : table) {
            minHeap.push(std::make_shared<Node>(k, v));
        }

        while (minHeap.size() > 1) {
            NodePtr left = minHeap.top();
            minHeap.pop();
            NodePtr right = minHeap.top();
            minHeap.pop();

            minHeap.push(std::make_shared<Node>('\0', left->mFrequency + right->mFrequency, left, right));
        }

        NodePtr root = minHeap.top();
        BuildCodes(root, "");
    }

    ~HuffmanTree() = default;

    void BuildCodes(const NodePtr& node, const std::string& code) {
        if (!node) {
            return;
        }

        if (node->mLeftChild == nullptr && node->mRightChild == nullptr) {
            mCodeTable[node->mName] = code;
        }

        BuildCodes(node->mLeftChild, code + "0");
        BuildCodes(node->mRightChild, code + "1");
    }

    void PrintCodeTable() const {
        for (const auto& [k, v] : mCodeTable) {
            std::cout << k << ": " << v << std::endl;
        }
    }

private:
    std::map<NodeType, std::string> mCodeTable;
};

int main() {
    // 输入数据：字符与权值
    std::map<char, int> table = {{'A', 12}, {'B', 24}, {'C', 35},
        {'D', 67}, {'E', 46}, {'F', 55}
    };

    HuffmanTree huffmanTree(table);

    huffmanTree.PrintCodeTable();

    return 0;
}
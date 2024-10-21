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

    Node(NodeType name, WeightType freq, std::shared_ptr<Node> left, std::shared_ptr<Node> right) :
        mName(name), mFrequency(freq), mLeftChild(std::move(left)), mRightChild(std::move(right)) {}
};


template<typename NodeType, typename WeightType>
class HuffmanTree {
public:
    using NodePtr = std::shared_ptr<Node<NodeType, WeightType>>;

    explicit HuffmanTree(std::map<NodeType, WeightType>& table) {
        auto Compare = [](NodePtr node1, NodePtr node2) {return node1->mFrequency > node2->mFrequency; };
        std::priority_queue<NodePtr, std::vector<NodePtr>, decltype(Compare)> minHeap(Compare);

        for (auto it = table.begin(); it != table.end(); ++it) {
            minHeap.push(std::make_shared<Node<NodeType, WeightType>>(it->first, it->second, nullptr, nullptr));
        }

        while (minHeap.size() > 1) {
            NodePtr left = minHeap.top();
            minHeap.pop();

            NodePtr right = minHeap.top();
            minHeap.pop();

            minHeap.push(std::make_shared<Node<NodeType, WeightType>>('\0', left->mFrequency + right->mFrequency, left, right));
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
        for (auto it = mCodeTable.begin(); it != mCodeTable.end(); ++it) {
            std::cout << it->first << ": " << it->second << std::endl;
        }
    }

private:
    std::map<NodeType, std::string> mCodeTable;
};

int main() {
    std::map<char, int> table = {
        {'A', 12}, {'B', 24}, {'C', 35},
        {'D', 67}, {'E', 46}, {'F', 55}
    };

    HuffmanTree<char, int> tree(table);

    tree.PrintCodeTable();

    return 0;
}
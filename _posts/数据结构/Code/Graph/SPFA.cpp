/*
 * @Brief        :
 * @Author       : dmjcb
 * @Date         : 2022-02-13 19:00:24
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-10-12 16:01:21
 */

#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <utility>
#include <vector>

 // definition of line
template <class NodeType = std::string>
struct Line {
    NodeType mStartNode;
    NodeType mEndNode;
    double   mWeight;

    Line(NodeType s, NodeType e, double w) :
        mStartNode(std::move(s)), mEndNode(std::move(e)), mWeight(w) {}
};


template <class NodeType = std::string>
class SPFAAlgorithm {
public:
    explicit SPFAAlgorithm(std::vector<Line<NodeType> > lines) {
        for (const auto& line : lines) {
            mNodes.insert(line.mStartNode);
            mNodes.insert(line.mEndNode);
        }

        mLines = std::move(lines);
        for (const auto& node : mNodes) {
            mShortestPath[node] = 0x7FFFFFFF;
            mIsInQueue[node] = false;
        }
    }

    void RunSPFA(NodeType node) {
        std::queue<NodeType> queue;
        queue.push(node);
        mShortestPath[node] = 0;
        mIsInQueue[node] = true;

        NodeType startNode;
        NodeType endNode;
        while (!queue.empty()) {
            startNode = queue.front();
            queue.pop();

            mIsInQueue[startNode] = false;
            for (const auto& line : mLines) {
                if (startNode == line.mStartNode) {
                    endNode = line.mEndNode;
                    if (mShortestPath[startNode] + line.mWeight < mShortestPath[endNode]) {
                        mShortestPath[endNode] = mShortestPath[startNode] + line.mWeight;
                        if (!mIsInQueue[endNode]) {
                            queue.push(endNode);
                            mIsInQueue[endNode] = true;
                        }
                    }
                }
            }
        }
    }

    void PrintShortestPath() const {
        for (auto it = mShortestPath.begin(); it != mShortestPath.end(); ++it) {
            std::cout << it->first << " --- " << it->second << std::endl;
        }
    }

private:
    std::vector<Line<NodeType>> mLines;
    std::set<NodeType>          mNodes;
    std::map<NodeType, double>  mShortestPath;
    std::map<NodeType, bool>    mIsInQueue;
};


int main() {
    using Line = Line<>;

    std::vector<Line> lines = {
        Line("A", "B", 13), Line("A", "E", 70), Line("B", "D", 4),
        Line("B", "C", 28), Line("C", "D", 23), Line("C", "E", 15)
    };

    std::string node = "A";

    SPFAAlgorithm<> spfa = SPFAAlgorithm<std::string>(lines);
    spfa.RunSPFA(node);
    spfa.PrintShortestPath();

    return 0;
}
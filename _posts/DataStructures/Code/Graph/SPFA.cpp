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
template <class T = std::string>
struct Line {
    T      mStartNode;
    T      mEndNode;
    double mWeight;

    Line(T s, T e, double w) : mStartNode(std::move(s)), mEndNode(std::move(e)), mWeight(w) {}
};


template <class T = std::string>
class SPFAAlgorithm {
public:
    explicit SPFAAlgorithm(std::vector<Line<T> > lines) {
        std::set<T> nodes;
        for (const auto& line : lines) {
            nodes.insert(line.mStartNode);
            nodes.insert(line.mEndNode);
        }
        mNode.assign(nodes.begin(), nodes.end());

        mLines = std::move(lines);
        for (const auto& node : mNode) {
            mShortestPath[node] = 0x7FFFFFFF;
            mIsInQueue[node] = false;
        }
    }

    void RunSPFA(T node) {
        std::queue<T> queue;

        queue.push(node);
        mShortestPath[node] = 0;
        mIsInQueue[node] = true;

        T startNode;
        T endNode;
        while (!queue.empty()) {
            startNode = queue.front();
            queue.pop();

            mIsInQueue[startNode] = false;
            for (const auto& line : mLines) {
                if (startNode == line.mStartNode) {
                    endNode = line.mEndNode;
                    // 若从点node经过点x到点end的距离比node直接到end的距离短
                    if (mShortestPath[startNode] + line.mWeight < mShortestPath[endNode]) {
                        // 距离更新为点node到x的距离与x到end的距离之和
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
        for (const auto& [k, v] : mShortestPath) {
            std::cout << k << " --- " << v << std::endl;
        }
    }

private:
    std::vector<Line<T>> mLines;
    std::vector<T>       mNode;
    std::map<T, double>  mShortestPath;
    std::map<T, bool>    mIsInQueue;
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
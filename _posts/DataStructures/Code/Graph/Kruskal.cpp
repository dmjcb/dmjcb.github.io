/*
 * @Brief        :
 * @Author       : dmjcb
 * @Date         : 2024-08-27 00:16:31
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-10-12 21:02:38
 */

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>
#include <set>

template<class NodeType = std::string>
struct Line {
    NodeType mStartNode;
    NodeType mEndNode;
    double   mWeight;
    bool     mIsSelect;

    Line(NodeType s, NodeType e, double w) : 
        mStartNode(std::move(s)), mEndNode(std::move(e)), mWeight(w), mIsSelect(false) {}
};


template<class NodeType = std::string>
class DisjointSetUnion {
public:
    DisjointSetUnion() = default;

    DisjointSetUnion(std::vector<Line<NodeType>>& lines) {
        for (const auto& line : lines) {
            mNodes.insert(line.mStartNode);
            mNodes.insert(line.mEndNode);
        }

        for (const auto& node : mNodes) {
            mParent[node] = node;
            mRank[node] = 0;
        }
    };

    NodeType Find(NodeType x) {
        if (mParent[x] != x) {
            mParent[x] = Find(mParent[x]);
        }
        return mParent[x];
    }

    void Unions(NodeType x, NodeType y) {
        NodeType fx = Find(x);
        NodeType fy = Find(y);

        if (fx != fy) {
            if (mRank[fx] > mRank[fy]) {
                mParent[fy] = fx;
            }
            else if (mRank[fx] > mRank[fy]) {
                mParent[fx] = fy;
            }
            else {
                mParent[fx] = fy;
                mRank[fx]++;
            }
        }
    }

private:
    std::set<NodeType>           mNodes;
    std::map<NodeType, NodeType> mParent;
    std::map<NodeType, int>      mRank;
};


template<class NodeType = std::string>
class Graph {
public:
    Graph(std::vector<Line<NodeType>>& lines) {
        mUnions = DisjointSetUnion<NodeType>(lines);

        std::sort(lines.begin(), lines.end(), [=](const Line<NodeType>& e1, const Line<NodeType>& e2) { return e1.mWeight < e2.mWeight; });
        mLines = std::move(lines);
    }

    double GetKruskal() {
        double sum = 0;
        for (auto& line : mLines) {
            if (mUnions.Find(line.mStartNode) != mUnions.Find(line.mEndNode)) {
                sum += line.mWeight;
                line.mIsSelect = true;

                mUnions.Unions(line.mStartNode, line.mEndNode);
            }
        }
        return sum;
    }

    void PrintResult() const {
        for (const auto& line : mLines) {
            if (line.mIsSelect) {
                std::cout << "Select Line: " << line.mStartNode << "-" << line.mEndNode << std::endl;
            }
        }
    }

private:
    DisjointSetUnion<NodeType>  mUnions;
    std::vector<Line<NodeType>> mLines;
};

int main() {
    using Line = Line<>;
    using Graph = Graph<>;

    std::vector<Line> lines = {
        Line("A", "B", 1), Line("A", "C", 9), Line("A", "D", 7),
        Line("B", "D", 5), Line("B", "E", 2), Line("E", "D", 4),
        Line("E", "F", 7), Line("F", "D", 1), Line("F", "G", 3),
        Line("G", "D", 6), Line("G", "C", 2), Line("C", "D", 4),
    };

    Graph graph(lines);
    std::cout << "The minimum spanning tree mWeight = " << graph.GetKruskal() << std::endl;
    graph.PrintResult();

    return 0;
}
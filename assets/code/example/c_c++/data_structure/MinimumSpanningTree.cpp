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

    DisjointSetUnion(std::set<NodeType>& nodes) {
        mNodes = std::move(nodes);

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
class MinimumSpanningTree {
public:
    MinimumSpanningTree(std::vector<Line<NodeType>>& lines) {
        std::set<NodeType> nodes;
        for (const auto& line : lines) {
            nodes.insert(line.mStartNode);
            nodes.insert(line.mEndNode);
        }

        mDSU = DisjointSetUnion<NodeType>(nodes);

        std::sort(lines.begin(), lines.end(), [=](const Line<NodeType>& e1, const Line<NodeType>& e2) { return e1.mWeight < e2.mWeight; });
        mLines = std::move(lines);
        mMSTValue = UseKruskal();
    }

    double UseKruskal() {
        double sum = 0;
        for (auto& line : mLines) {
            if (mDSU.Find(line.mStartNode) != mDSU.Find(line.mEndNode)) {
                sum += line.mWeight;
                line.mIsSelect = true;

                mDSU.Unions(line.mStartNode, line.mEndNode);
            }
        }
        return sum;
    }

    void PrintMSTResult() const {
        std::cout << "The minimum spanning tree value = " << mMSTValue << std::endl;

        for (const auto& line : mLines) {
            if (line.mIsSelect) {
                std::cout << "Select Line: " << line.mStartNode << "-" << line.mEndNode << std::endl;
            }
        }
    }

private:
    DisjointSetUnion<NodeType>  mDSU;
    std::vector<Line<NodeType>> mLines;
    double                      mMSTValue;
};

int main() {
    std::vector<Line<>> lines = {
        Line<>("A", "B", 1), Line<>("A", "C", 9), Line<>("A", "D", 7),
        Line<>("B", "D", 5), Line<>("B", "E", 2), Line<>("E", "D", 4),
        Line<>("E", "F", 7), Line<>("F", "D", 1), Line<>("F", "G", 3),
        Line<>("G", "D", 6), Line<>("G", "C", 2), Line<>("C", "D", 4),
    };

    MinimumSpanningTree<> mst(lines);

    mst.PrintMSTResult();

    return 0;
}
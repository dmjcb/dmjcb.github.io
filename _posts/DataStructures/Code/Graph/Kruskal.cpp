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

template<class T = std::string>
struct Line {
    T      mStartNode;
    T      mEndNode;
    double mWeight;
    bool   mIsSelect;

    Line(T s, T e, double w) : mStartNode(std::move(s)), mEndNode(std::move(e)), mWeight(w), mIsSelect(false) {}
};


template<class T = std::string>
class DisjointSetUnion {
public:
    DisjointSetUnion() = default;

    DisjointSetUnion(std::vector<Line<T>>& lines) {
        for (const auto& line : lines) {
            mNodes.insert(line.mStartNode);
            mNodes.insert(line.mEndNode);
        }

        for (const auto& node : mNodes) {
            mParent[node] = node;
            mRank[node] = 0;
        }
    };

    T Find(T x) {
        if (mParent[x] != x) {
            mParent[x] = Find(mParent[x]);
        }
        return mParent[x];
    }

    void Unions(T x, T y) {
        T fx = Find(x);
        T fy = Find(y);

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
    std::map<T, T>   mParent;
    std::map<T, int> mRank;
    std::set<T>      mNodes;
};

template<class T = std::string>
class Graph {
public:
    Graph(std::vector<Line<T>>& lines) {
        mUnions = DisjointSetUnion<T>(lines);

        std::sort(lines.begin(), lines.end(), [=](const Line<T>& e1, const Line<T>& e2) { return e1.mWeight < e2.mWeight; });
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
    DisjointSetUnion<T>  mUnions;
    std::vector<Line<T>> mLines;
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
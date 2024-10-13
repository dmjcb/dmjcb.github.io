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

namespace {

template<class T = std::string>
struct Line {
    T      mStartNode;
    T      mEndNode;
    double mWeight;
    bool   mIsSelect;

    Line(T s, T e, double w) : mStartNode(std::move(s)), mEndNode(std::move(e)), mWeight(w), mIsSelect(false) {}
};


template<class T = std::string>
class Graph {
public:
    explicit Graph(std::vector<Line<T> > lines) {
        mLines = std::move(lines);

        // count the number of nodes
        std::set<T> nodes;
        for (const auto& line : mLines) {
            nodes.insert(line.mStartNode);
            nodes.insert(line.mEndNode);
        }

        // parent of each node is itself at initialization time
        for (const auto& node : nodes) {
            mParent[node] = node;
        }
    };

    T Find(T node) {
        if (mParent[node] == node) {
            return node;
        }

        T root = node;
        while (mParent[root] != root) {
            root = mParent[root];
        }

        T fatherNode = node;
        while (root != node) {
            fatherNode = mParent[node];
            mParent[node] = root;
            node = fatherNode;
        }

        return root;
    }

    void Merge(T node1, T node2) {
        mParent[Find(node1)] = Find(node2);
    }

    double GetKruskal() {
        std::sort(mLines.begin(), mLines.end(), [=](const Line<T>& e1, const Line<T>& e2) { return e1.mWeight < e2.mWeight; });

        double sum = 0;
        for (auto& line : mLines) {
            if (Find(line.mStartNode) != Find(line.mEndNode)) {
                sum += line.mWeight;
                line.mIsSelect = true;

                Merge(line.mStartNode, line.mEndNode);
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
    std::map<T, T>       mParent;
    std::vector<Line<T>> mLines;
};
}

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
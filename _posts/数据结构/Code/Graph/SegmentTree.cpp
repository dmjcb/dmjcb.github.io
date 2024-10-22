#include <iostream>
#include <vector>

template <typename T>
class SegmentTree {
private:
    std::vector<T> mTree;
    std::vector<T> mData;
    int            mSize;

    void Build(int node, int start, int end) {
        if (start == end) {
            // 叶子节点
            mTree[node] = mData[start];
        } else {
            int mid = (start + end) / 2;
            int leftNode = 2 * node + 1;
            int rightNode = 2 * node + 2;

            Build(leftNode, start, mid);
            Build(rightNode, mid + 1, end);

            mTree[node] = Merge(mTree[leftNode], mTree[rightNode]);
        }
    }

    // 查询区间 [left, right] 的值
    T QueryRange(int node, int start, int end, int left, int right) {
        if (right < start || left > end) {
            // 查询范围完全在节点范围之外
            return GetIdentity();
        }
        // 查询范围完全包含节点范围
        if (left <= start && end <= right) {
            return mTree[node];
        }

        int mid = (start + end) / 2;
        int leftNode = 2 * node + 1;
        int rightNode = 2 * node + 2;

        T leftResult = QueryRange(leftNode, start, mid, left, right);
        T rightResult = QueryRange(rightNode, mid + 1, end, left, right);

        return Merge(leftResult, rightResult);
    }

    void UpdateNode(int node, int start, int end, int idx, T value) {
        if (start == end) {
            // 叶子节点更新
            mData[idx] = value;
            mTree[node] = value;
        }
        else {
            int mid = (start + end) / 2;
            int leftNode = 2 * node + 1;
            int rightNode = 2 * node + 2;

            if (idx <= mid) {
                UpdateNode(leftNode, start, mid, idx, value);
            }
            else {
                UpdateNode(rightNode, mid + 1, end, idx, value);
            }

            mTree[node] = Merge(mTree[leftNode], mTree[rightNode]);
        }
    }

    // 返回单元操作的"单位元"值, 例如区间和则为0, 区间最小值为正无穷大等
    T GetIdentity() const {
        return T();
    }

    // 合并两个节点的值
    T Merge(const T& a, const T& b) const {
        return a + b; // 默认操作为求和, 其他操作可以按需修改
    }

public:
    SegmentTree(const std::vector<T>& inputData) {
        mData = inputData;
        mSize = mData.size();
        mTree.resize(4 * mSize);
        Build(0, 0, mSize - 1);
    }

    T Query(int left, int right) {
        return QueryRange(0, 0, mSize - 1, left, right);
    }

    void Update(int idx, T value) {
        UpdateNode(0, 0, mSize - 1, idx, value);
    }
};

int main() {
    std::vector<int> data = { 1, 3, 5, 7, 9, 11 };
    SegmentTree<int> segTree(data);

    std::cout << "Sum of range [1, 3]: " << segTree.Query(1, 3) << std::endl;

    segTree.Update(2, 10);
    std::cout << "After updating index 2 to 10, sum of range [1, 3]: " << segTree.Query(1, 3) << std::endl;

    return 0;
}
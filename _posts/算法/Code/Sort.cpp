/*
 * @Brief        :
 * @Author       : dmjcb
 * @Date         : 2022-04-15 12:42:17
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-10-12 15:47:50
 */

#include <iostream>
#include <vector>

template<class T>
void BubbleSort(std::vector<T> &v) {
    // 记录是否发生过交换
    bool isExchange;
    for (int i = 0, size = v.size(); i < size - 1; i++) {
        isExchange = false;
        for (int j = 0; j < size - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                isExchange = true;
                std::swap(v[j], v[j + 1]);
            }
        }
        // 如果此轮没有发生交换, 则说明已完成排序
        if (isExchange == false) {
            return;
        }
    }
}

template<class T>
void InsertSort(std::vector<T> &v) {
    for (int i = 1, size = v.size(); i < size; i++) {
        if (v[i - 1] > v[i]) {
            T beInserted = v[i];
            int j = i - 1;
            // 从前一个元素位置开始, 若未到表头且当前位置元素大于temp
            while (j >= 0 && beInserted < v[j]) {
                // 所有元素依次向后移动
                v[j + 1] = v[j];
                j--;
            }
            // 此处就是为插入temp留出的空(退出循环时j会多减1)
            v[j + 1] = beInserted;
        }
    }
}

template<class T>
void QuickSort(std::vector<T> &v, const int left, const int right) {
    // index表示基准下标, index左侧值均比v[index]小;右侧值均比v[index]大
    int index = left;
    // 设定基准元素, 默认基准位置为最左边位置
    T pivot = v[left];
    for (int i = left + 1; i <= right; i++) {
        if (v[i] < pivot) {
            // 基准下标右移
            index++;
            // 如果待交换位置与该位置不重合
            if (index != i) {
                std::swap(v[i], v[index]);
            }
        }
    }
    // 基准元素就位, 基准位为index
    v[left] = v[index];
    v[index] = pivot;
    if (left < right) {
        // 对左, 右侧元素也进行同样处理
        QuickSort(v, left, index - 1);
        QuickSort(v, index + 1, right);
    }
}

template<class T>
void SiftDown(std::vector<T> &v, const int start, const int end) {
    int parent = start;
    int child = 2 * parent + 1;
    // temp暂存子树根节点
    T temp = v[parent];
    // 如果左儿子编号未到终点
    while (child < end) {
        // 如果右儿子比左儿子小
        if (child + 1 < end && v[child] < v[child + 1]) {
            // child变为右儿子
            child++;
        }

        //  如果根节点比儿子节点小, 则不需要调整
        if (temp >= v[child]) {
            break;
        }

        // 否则需调整儿子和双亲的位置
        v[parent] = v[child];
        // 儿子上移变为双亲
        parent = child;
        child = 2 * child + 1;
    }
    v[parent] = temp;
}

// 堆排序函数
template<class T>
void HeapSort(std::vector<T> &v) {
    for (int i = (v.size() - 2) / 2; i >= 0; i--) {
        // 建立一个小根堆
        SiftDown<T>(v, i, v.size());
    }

    for (int i = v.size() - 1; i > 0; i--) {
        // 交换根和最后一个元素
        std::swap<T>(v[0], v[i]);
        SiftDown<T>(v, 0, i);
    }
}

int main() {
    std::vector<int> v = {8, 5, 2, 6, 9, 3, 4, 7, 1};
    HeapSort(v);

    for (auto _v: v) {
        printf("%d ", _v);
    }

    return 0;
}

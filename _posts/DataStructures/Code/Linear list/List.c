#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int          data;
    struct Node* next;
} Node;

// 初始化
Node *InitHead() {
    Node* head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    return head;
}

// 后插法建立链表
void CreateList(Node* head, const int *value, const int length) {
    head->next = NULL;
    Node* p;
    Node* r = head;
    for (int i = 0; i < length; i++) {
        p = (Node *)malloc(sizeof(Node));
        p->data = value[i];
        p->next = NULL;
        r->next = p;
        r = p;
    }
}

// 查找
void GetIndex(const Node* head, int index) {
    Node* p;
    p = head->next;
    // j为计数器,用以记录当前的位置
    int j = 1;
    // 当P不为空且未到指定位置时,指针向后移动,计数器增加
    while (p && j < index) {
        p = p->next;
        ++j;
    }
    if (!p || j > index) {
        return;
    }
    printf("%d\n", p->data);
}

// 插入
bool InsertNode(Node* head, int index, int value) {
    Node* p = head;
    // 计数器初始值为0是考虑到了空表的情况
    int j = 0;
    while (p && j < index - 1) {
        p = p->next;
        ++j;
    }
    if (!p || j > index - 1) {
        return false;
    }
    Node* s = (Node*)malloc(sizeof(Node));
    s->data = value;
    s->next = p->next;

    p->next = s;

    return true;
}

// 删除
void EraseNode(Node* head, const int index) {
    Node* p = head;
    int j = 0;
    while ((p->next) && j < index - 1) {
        p = p->next;
        j++;
    }
    if (!p || j > index - 1) {
        return;
    }
    Node* q = p->next;
    p->next = q->next;

    free(q);
}

//
void OutputList(Node* head)
{
    if (head == NULL) {
        return;
    }

    Node* p = head->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main(void) {
    Node *head = InitHead();

    const int LENGTH = 5;
    int *array = (int *)malloc(sizeof(int) * LENGTH);
    array[0] = 1;
    array[1] = 2;
    array[2] = 3;
    array[3] = 4;
    array[4] = 5;

    CreateList(head, array, LENGTH);
    OutputList(head);

    bool flag = InsertNode(head, 5, 99);
    OutputList(head);

    free(array);
    array = NULL;

    free(head);
    head = NULL;

    return 0;
}

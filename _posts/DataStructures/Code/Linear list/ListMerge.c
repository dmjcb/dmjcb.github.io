/*
 * @Brief        : 
 * @Author       : dmjcb
 * @Date         : 2024-09-26 02:58:19
 * @LastEditors  : dmjcb@outlook.com
 * @LastEditTime : 2024-10-08 23:05:05
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int          data;
    struct Node* next;
} Node, *NodeList;

NodeList InitList(NodeList head, const int *value, int length)
{
    head = (NodeList)malloc(sizeof(Node));
    head->next = NULL;

    NodeList r = head;
    for (int i = 0; i < length; i++) {
        NodeList p = (NodeList)malloc(sizeof(Node));
        p->data = *(value++);
        p->next = NULL;

        r->next = p;
        r = p;
    }

    return head;
}

void OutputList(NodeList head)
{
    NodeList p= head->next;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
}

void ConnectList(NodeList head1, NodeList head2)
{
    NodeList p1, p2;
    p1 = head1->next;
    while (p1->next)
    {
        p1 = p1->next;
    }
    p2 = head2->next;
    p1->next = p2;
    free(head2);
}

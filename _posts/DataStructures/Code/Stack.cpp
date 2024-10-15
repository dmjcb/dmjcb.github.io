#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };
    Node* mTop;

public:
    Stack() : mTop(nullptr) {}

    ~Stack() {
        while (!isEmpty()) {
            Pop();
        }
    }

    void Push(T val) {
        Node* newNode = new Node(val);
        newNode->next = mTop;
        mTop = newNode;
    }

    void Pop() {
        if (isEmpty()) {
            return;
        }

        Node* temp = mTop;
        mTop = mTop->next;
        delete temp;
    }

    T Top() const {
        if (IsEmpty()) {
            throw std::out_of_range("Stack is empty");
        }
        return mTop->data;
    }

    bool IsEmpty() const {
        return mTop == nullptr;
    }
};
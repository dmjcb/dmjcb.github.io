#include <iostream>

template <typename T>
class LinkedList {
public:
    LinkedList() : mHead(nullptr) {}

    ~LinkedList() {
        Node* current = mHead;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void Add(T val) {
        Node* newNode = new Node(val);
        if (!mHead) {
            mHead = newNode;
            return;
        }
        
        Node* temp = mHead;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void Print() {
        Node* temp = mHead;
        while (temp) {
            std::cout << temp->data << " -> ";
            temp = temp->next;
        }
        std::cout << "nullptr" << std::endl;
    }

private:
    struct Node {
        T data;
        Node* next;
        Node(T val) : data(val), next(nullptr) {}
    };

    Node* mHead;
};
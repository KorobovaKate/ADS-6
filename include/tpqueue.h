// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

struct SYM {
  char ch;
  int prior;
};

template<typename T>
class TPQueue {
 private:
    struct Node {
        T data;
        Node* next;

        explicit Node(const T& data, Node* next = nullptr)
              : data(data), next(next) {}
    };

    Node* head;
    Node* tail;

 public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push(const T& item) {
        Node* newNode = new Node(item);

        if (!head || item.prior > head->data.prior) {
            newNode->next = head;
            head = newNode;
            if (!tail) tail = head;
            return;
        }

        Node* current = head;
        while (current->next && current->next->data.prior >= item.prior) {
        current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;

        if (!newNode->next) {
            tail = newNode;
        }
    }

    T pop() {
        if (empty()) {
          throw std::underflow_error("TPQueue is empty");
        }
        Node* temp = head;
        T data = head->data;
        head = head->next;
        if (!head) {
          tail = nullptr;
        }
        delete temp;
        return data;
    }

    bool empty() const { return head == nullptr; }
};
#endif  // INCLUDE_TPQUEUE_H_

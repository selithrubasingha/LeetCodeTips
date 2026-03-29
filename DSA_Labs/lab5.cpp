#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class SinglyLinkedListNode {
    public:
        int data;
        SinglyLinkedListNode* next;

        SinglyLinkedListNode(int data) {
            this->data = data;
            this->next = nullptr;
        }
};

class SinglyLinkedList {
    public:
        SinglyLinkedListNode* head;
        SinglyLinkedListNode* tail;

        SinglyLinkedList() {
            this->head = nullptr;
            this->tail = nullptr;
        }

        void insert_node(int data){
            SinglyLinkedListNode *node = new SinglyLinkedListNode(data);

            if (!this->head) {
                this->head = node;
            } else {
                this->tail->next = node;
            }
        }

    };
//
// Created by MIthul Nallaka on 11/9/21.
//
#include "iostream"
using namespace std;

template <class T>
struct Node {
    Node* parent = this;
    Node* child = this;
    Node* left = this;
    Node* right = this;
    Node* sibling = this;
    T key;
    int degree = 0;

    Node<T>(Node* parent, Node* child, Node* left, Node* right, T key) {
        this->parent = parent;
        this->child = child;
        this->left = left;
        this->right = right;
        this->key = key;
    }
};

template <class T>
class FibHeap {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    Node<T>* min = nullptr;
    int n;
public:

    FibHeap() {
        this->n = 0;
        this->min = nullptr;
    }

    T peekKey() {
        return this->min->key;
    }

    void insert(T k) {
        Node<T>* newNode =  new Node<T>(nullptr, nullptr, nullptr, nullptr, k);

        if (this->head == nullptr) {
            this->min = newNode;
            this->head = newNode;
            this->tail = newNode;
            newNode->left = newNode;
            newNode->right = newNode;
        } else {
            this->tail->right = newNode;
            newNode->left = this->tail;
            newNode->right = this->head;
            this->tail = newNode;
            this->head->left = this->tail;
            if (newNode->key < this->min->key) {
                this->min = newNode;
            }
        }

        this->n++;
    }

    void merge(FibHeap<T> &H2) {
        this->tail->right = H2.head;
        this->head->left = H2.tail;
        H2.head->left = this->tail;
        if (this->min->key > H2.min->key) {
            this->min = H2.min;
        }
        this->tail = H2.tail;
        this->n += H2.n;
    }

    void extractMin() {
        auto heapMin = this->min;
        if (heapMin != nullptr) {
            auto currNode = heapMin->child;
            while (currNode != nullptr) {
                this->tail->right = currNode;
                currNode->parent = nullptr;
                currNode->left = this->tail;
                currNode->right = this->head;
                this->tail = currNode;
                currNode->degree--;
                currNode = currNode->right;
            }
            heapMin->left->right = heapMin->right;
            heapMin->right->left = heapMin->left;
            if (heapMin == heapMin->right) {
                this->min = nullptr;
            } else {
                this->min = heapMin->right;
                this->consolidate();
            }
            this->n--;
        }
    }

    void consolidate() {

    }
};


int main() {
    FibHeap<int> heap = FibHeap<int>();
    heap.insert(5);
    heap.insert(6);
    heap.insert(7);
    FibHeap<int> heap2 = FibHeap<int>();
    heap2.insert(1);
    heap2.insert(2);
    heap2.insert(3);
    heap.merge(heap2);
    cout << "end";
}
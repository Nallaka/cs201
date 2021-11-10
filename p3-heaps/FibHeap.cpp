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
        Node<T>* currNodeH2 = H2->head;
        while (currNodeH2 != H2.tail) {
            this->tail->right = currNodeH2;
            currNodeH2->left = this->tail;
            this->tail = currNodeH2;
        }
    }
};


int main() {
    FibHeap<int> heap = FibHeap<int>();
    heap.insert(5);
    heap.insert(6);
    heap.insert(7);
    heap.insert(2);
    cout << "end";
}
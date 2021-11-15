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
        H2.tail->right = this->head;
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
        Node<T>* A[] = new Node<T>*[50];
        for (int i = 0; i < 50; i++) {
            A[i] = nullptr;
        }
        auto currNode = this->head;
        while (currNode->right != this->head) {
            auto x = currNode;
            int d = x->degree;
            while (A[d] != nullptr) {
                auto y = A[d];
                if (x->key > y->key) {
                    auto temp = x;
                    x = y;
                    y = temp;
                }
                this->fibHeapLink(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
            currNode = currNode->right;
        }
        this->min = nullptr;
        for (int i = 0; i < 50; i++) {
            if (A[i] != nullptr) {
                if (this->min == nullptr) {
                    this->head = A[i];
                    this->tail = A[i];
                    this->head->left = A[i];
                    this->head->right = A[i];
                    this->min = A[i];
                } else {
                    this->tail->right = A[i];
                    A[i]->left = this->tail;
                    A[i]->right = this->head;
                    this->tail = A[i];
                    if (A[i]->key < this->min->key) {
                        this->min = A[i];
                    }
                }
            }
        }

    }

    void fibHeapLink(Node<T>* y, Node<T>* x) {
        y->right->left = y->left;
        y->left->right = y->right;
        y->sibling = x->child;
        x->child = y;
        y->parent = x;
        x->degree++;
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
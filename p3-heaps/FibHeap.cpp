//
// Created by MIthul Nallaka on 11/9/21.
//
#include "iostream"
using namespace std;

template <class T>
struct Node {
    Node* parent = nullptr;
    Node* child = nullptr;
    Node* left = this;
    Node* right = this;
    Node* sibling = nullptr;
    T key;
    int degree = 0;

    Node<T>(Node* parent, Node* child, Node* left, Node* right, T key) {
        this->parent = parent;
        this->child = child;
        this->left = left;
        this->right = right;
        this->key = key;
    }

    Node<T>(T key) {
        this->key = key;
    }

    ~Node() {
        this->parent = nullptr;
        this->child = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->sibling = nullptr;
        this->key = nullptr;
        this->degree = nullptr;
    }
};

template <class T>
class FibHeap {
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    Node<T>* min = nullptr;
    int n = 0;
public:

    FibHeap() {
        this->n = 0;
        this->min = nullptr;
    }

    FibHeap(T k[], int s) {
        for (int i = 0; i < s; i++) {
            this->insert(k[i]);
        }

        this->consolidate();
    }

    ~FibHeap() {
        this->head = nullptr;
        this->tail = nullptr;
        this->min = nullptr;
    }

    FibHeap<T>(const FibHeap<T> &other) {
        auto x = other.head;

        auto prevNode = new Node<T>(x->key);
        prevNode->degree = x->degree;
        this->head = prevNode;
        this->tail = this->head;
        this->n = other.n;

        if (other.head == other.min) {
            this->min = prevNode;
        }

        this->copy(x, prevNode);
        x = x->right;

        while (x != other.head) {
            auto newNode = new Node<T>(x->key);
            newNode->degree = x->degree;
            if (other.min == x) {
                this->min = newNode;
            }
            prevNode->right = newNode;
            newNode->left = prevNode;
            newNode->right = this->head;
            this->tail = newNode;
            this->head->left = this->tail;
            this->copy(x, newNode);

            prevNode = prevNode->right;
            x = x->right;
        }
    }

    FibHeap& operator=(const FibHeap<T> &other) {
        auto x = other.head;

        auto prevNode = new Node<T>(x->key);
        prevNode->degree = x->degree;
        this->head = prevNode;
        this->tail = this->head;
        this->n = other.n;

        if (other.head == other.min) {
            this->min = prevNode;
        }

        this->copy(x, prevNode);
        x = x->right;

        while (x != other.head) {
            auto newNode = new Node<T>(x->key);
            newNode->degree = x->degree;
            if (other.min == x) {
                this->min = newNode;
            }
            prevNode->right = newNode;
            newNode->left = prevNode;
            newNode->right = this->head;
            this->tail = newNode;
            this->head->left = this->tail;
            this->copy(x, newNode);

            prevNode = prevNode->right;
            x = x->right;
        }

        return *this;
    }

    void copyNode(Node<T> &x, Node<T> &root) {
        auto newNode = new Node<T>(x.child->key);
    }

    void copy(Node<T> *x, Node<T> *n) {
        if (x->child != nullptr) {
            auto newNode = new Node<T>(x->child->key);
            newNode->degree = x->child->degree;
            newNode->parent = n;
            n->child = newNode;
            copy(x->child, n->child);
        }
        if (x->sibling != nullptr) {
            auto newNode = new Node<T>(x->sibling->key);
            newNode->degree = x->sibling->degree;
            n->sibling = newNode;
            copy(x->sibling, n->sibling);
        }
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

    T extractMin() {
        auto z = this->min;
        if (z != nullptr) {
            auto x = z->child;
            while (x != nullptr) {
                this->tail->right = x;
                this->head->left = x;
                x->left = this->tail;
                x->right = this->head;
                this->tail = x;
                x->parent = nullptr;
                auto temp = x;
                x = x->sibling;
                temp->sibling = nullptr;
            }

            if (this->min == this->head) {
                this->head = this->head->right;
            }

            if (this->min == this->tail) {
                this->tail = this->tail->left;
            }

            z->left->right = z->right;
            z->right->left = z->left;

            if (z == z->right) {
                this->min = nullptr;
                this->head = nullptr;
                this->tail = nullptr;
            } else {
                this->min = z->right;
                this->consolidate();
            }

            this->n--;
            return z->key;
        } else {
            return T();
        }
    }

    void consolidate() {
        Node<T> *A[50];
        for (auto & i : A) {
            i = nullptr;
        }

        auto w = this->head;

        do {
            auto x = w;
            int d = x->degree;
            auto y = A[d];
            while(A[d] != nullptr) {
                y = A[d];
                if (x->key > y->key) {
                    auto *temp = x;
                    x = y;
                    y = temp;
                }
                fibHeapLink(y, x);
                A[d] = nullptr;
                d++;
            }
            A[d] = x;
            if (x->right == x) {
                w = x->right;
            } else {
                w = w->right;
            }

        } while(w != this->head);

        this->min = nullptr;

        for (Node<T>  *i : A) {
            if (i != nullptr) {
                if (this->min == nullptr) {
                    this->head = i;
                    this->tail = i;
                    this->head->right = this->head;
                    this->head->left = this->head;
                    this->head->parent = nullptr;
                    this->min = i;
                } else {
                    this->tail->right = i;
                    this->head->left = i;
                    i->left = this->tail;
                    i->right = this->head;
                    this->tail = i;

                    if (i->key < this->min->key) {
                        this->min = i;
                    }
                }
            }
        }
    }

    void fibHeapLink(Node<T>* y, Node<T>* x) {
        y->left->right = y->right;
        y->right->left = y->left;
        y->parent = x;
        y->sibling = x->child;
        x->child = y;
        x->degree++;

        if (this->head == y) {
            this->head = y->right;
            this->tail->right = this->head;
        }

        if (this->tail == y) {
            this->tail = y->left;
            this->head->left = this->tail;
        }

    }

    void printKey() {
        auto x = this->head;

        do {
            cout << "B" << x->degree << endl;
            inorder(*x);

            cout << endl << endl;

            x = x->right;
        } while (x != this->head);
    }

    void inorder(Node<T> &x) {
        T key = x.key;
        cout << x.key << " ";

        if(x.child != nullptr) {
            inorder(*x.child);
        }
        Node<T>* sibling = x.sibling;

        if (sibling != nullptr){
            inorder(*sibling);
        }
    }
};
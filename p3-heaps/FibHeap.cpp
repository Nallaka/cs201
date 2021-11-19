//
// Created by MIthul Nallaka on 11/9/21.
//
#include "iostream"
#include "Heap.cpp"
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

    FibHeap& operator=(FibHeap<T> other) {

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
            } else {
                this->min = z->right;
                this->consolidate();
            }

            this->n--;
        }

        return z->key;
        /*auto heapMin = this->min;
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
        }*/
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
            w = x->right;
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
/*        auto currNode = this->head;
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
        }*/

    }

    void fibHeapLink(Node<T>* y, Node<T>* x) {
        /*if (this->head == y) {
            this->head = y->right;
            this->tail->right = this->head;
        }

        if (this->tail == y) {
            this->tail = y->left;
            this->head->left = this->tail;
        }*/
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

        /*y->right->left = y->left;
        y->left->right = y->right;
        y->sibling = x->child;
        x->child = y;
        y->parent = x;
        x->degree++;*/
    }

    void printKey() {
        auto x = this->head;

        do {
            cout << "B" << x->degree << endl;
            inorder(*x);
            //TODO: Print children Inorder include endl

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


int main() {

    // From the FibHeap lab where we did several operations on this set
    // Feel free to check output with your own hand-drawn trees

    int ints[] = {6, 2, 10, 7, 5, 1, 11, 9, 3, 4, 8};
    FibHeap<int> fhInt(ints, 11);

    // B0
    // 8
    //
    // B1
    // 3 4
    //
    // B3
    // 1 2 7 10 6 9 11 5

    cout << "8.1" << endl;
    fhInt.printKey();
    cout << endl;

    // B1
    // 5 8
    //
    // B3
    // 2 3 9 11 4 7 10 6

    cout << "8.2" << endl;
    fhInt.extractMin();
    fhInt.printKey();
    cout << endl;

    // B2
    // 6 7 10 22
    //
    // B3
    // 3 5 15 19 8 9 11 4

    cout << "8.3" << endl;
    fhInt.insert(15);
    fhInt.insert(19);
    fhInt.insert(22);
    fhInt.extractMin();
    fhInt.printKey();
    cout << endl;

    // B0
    // 4
    //
    // B1
    // 9 11
    //
    // B3
    // 5 6 7 10 22 15 19 8

    cout << "8.4" << endl;
    fhInt.extractMin();
    fhInt.printKey();
    cout << endl;

}
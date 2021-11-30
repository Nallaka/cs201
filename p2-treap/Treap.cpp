#include <iostream>

using namespace std;

template<class T>
struct TreapNode {
    T key;
    float priority;
    TreapNode *left, *right, *parent;
    int subtreeSize;

    explicit TreapNode(T k) {
        key = k;
        priority = (float) rand() / RAND_MAX;
        left = nullptr;
        right = nullptr;
        subtreeSize = 1;
    }

    explicit TreapNode(T k, float p) {
        key = k;
        priority = p;
        left = nullptr;
        right = nullptr;
        subtreeSize = 1;
    }
};

template<class T>
class Treap {
public:
    TreapNode<T> *root;
    int s;

    Treap() {
        root = nullptr;
        s = 0;
    }

    Treap(T k[], float p[], int size) {
        root = nullptr;
        this->s = 0;

        for (int i = 0; i < size; i++) {
            this->insert(k[i], p[i]);
        }
    }

    Treap(const Treap &original) {
        root = nodeCopy(original.root);
    }

    Treap<T>& operator=(const Treap &original) {
        root = nodeCopy(original.root);
        return *this;
    }

    TreapNode<T> *nodeCopy(TreapNode<T> *original) {
        if (original == nullptr) {
            return nullptr;
        }

        TreapNode<T> *newNode = new TreapNode<T>(original->key, original->priority);
        newNode->left = nodeCopy(original->left);
        newNode->right = nodeCopy(original->right);

        return newNode;
    }

    void rotateRight(TreapNode<T> *&x) {
        TreapNode<T> *y = x->left;

        TreapNode<T> *r = y->left;
        TreapNode<T> *g = y->right;
        TreapNode<T> *b = x->right;

        y->subtreeSize = x->subtreeSize;
        x->subtreeSize = (y->right ? y->right->subtreeSize : 0) + (x->right ? x->right->subtreeSize : 0) + 1;
        x->left = g;
        y->right = x;

        x = y;
    }

/*    void rotateRight(TreapNode<T> *&x) {
        TreapNode<T> *y = x->left;
        x->left = y->right;

        if (y->right != nullptr) {
            this->root->right->parent = x;
        }

        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        y->right = x;
        x->parent = y;
    }*/

    void rotateLeft(TreapNode<T> *&y) {
        TreapNode<T> *x = y->right;

        TreapNode<T> *r = y->left;
        TreapNode<T> *g = x->left;
        TreapNode<T> *b = x->right;

        x->subtreeSize = y->subtreeSize;
        y->subtreeSize = (x->left ? x->left->subtreeSize : 0) + (y->left ? y->left->subtreeSize : 0) + 1;
        x->left = y;
        y->right = g;

        y = x;

    }

/*    void rotateLeft(TreapNode<T> *&x) {
        TreapNode<T> *y = x->right;
        x->right = y->left;

        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }

        x->parent = y;
        y->left = x;

    }*/

    void insert(T k) {
        this->s++;
        insertNode(this->root, k);
        /*this->size++;
        if (this->root == nullptr) {
            this->root = new TreapNode<T>(k);
            return;
        }

        if (k < this->root->key) {
            insertNode(this->root->left, k);
        } else if (k > this->root->key) {
            insertNode(this->root->right, k);
        }

        if (this->root->left != nullptr && this->root->left->priority < this->root->priority) {
            rotateRight(this->root);
        }

        if (this->root->right != nullptr && this->root->right->priority < this->root->priority) {
            rotateLeft(this->root);
        }*/
    }

    void insertNode(TreapNode<T> *&node, T k) {
        if (node == nullptr) {
            node = new TreapNode<T>(k);
            //node->parent = parent;
            return;
        }
        node->subtreeSize++;
        if (k < node->key) {
            insertNode(node->left, k);
        } else if (k > node->key) {
            insertNode(node->right, k);
        }

        /*auto *z = new TreapNode<T>(k);

        TreapNode<T> *y = nullptr;
        TreapNode<T> *x = this->root;

        while (x != nullptr) {
            y = x;
            if (node->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nullptr) {
            this->root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }*/

        if (node->left != nullptr && node->left->priority < node->priority) {
            rotateRight(node);
        }

        if (node->right != nullptr && node->right->priority < node->priority) {
            rotateLeft(node);
        }
    }

    void insert(T k, float p) {
        this->s++;
        insertNode(this->root, k, p);
        /*this->size++;
        if (this->root == nullptr) {
            this->root = new TreapNode<T>(k, p);
            return;
        }

        if (k < this->root->key) {
            insertNode(this->root->left, k, p);
        } else if (k > this->root->key) {
            insertNode(this->root->right, k, p);
        }

        if (this->root->left != nullptr && this->root->left->priority < this->root->priority) {
            rotateRight(this->root);
        }

        if (this->root->right != nullptr && this->root->right->priority < this->root->priority) {
            rotateLeft(this->root);
        }*/
    }

    void insertNode(TreapNode<T> *&node, T k, float p) {
        if (node == nullptr) {
            node = new TreapNode<T>(k, p);
            return;
        }

        node->subtreeSize++;
        if (k < node->key) {
            insertNode(node->left, k, p);
        } else if (k > node->key) {
            insertNode(node->right, k, p);
        }
        /*TreapNode<T> *z = new TreapNode<T>(k, p);

        TreapNode<T> *y = nullptr;
        TreapNode<T> *x = this->root;

        while (x != nullptr) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;

        if (y == nullptr) {
            this->root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
*/

        if (node->left != nullptr && node->left->priority < node->priority) {
            rotateRight(node);
        }

        if (node->right != nullptr && node->right->priority < node->priority) {
            rotateLeft(node);
        }
    }

    float search(T k) {
        return searchH(this->root, k);
        /*if (this->root == nullptr) {
            return -1.0;
        }
        if (this->root->key == k) {
            return this->root->priority;
        }

        if (k < this->root->key) {
            return searchH(this->root->left, k);
        } else if (k > this->root->key) {
            return searchH(this->root->right, k);
        }

        return -1.0;*/
    }

    float searchH(TreapNode<T> *&node, T k) {
        if (node == nullptr) {
            return -1;
        }
        if (node->key == k) {
            return node->priority;
        }

        if (k < node->key) {
            return searchH(node->left, k);
        } else if (k > node->key) {
            return searchH(node->right, k);
        }

        return -1;
    }

    void preorder() {
        preorderH(this->root);
        /*if (this->root == nullptr) {
            return;
        }

        cout << this->root->key << " ";

        preorderH(this->root->left);
        preorderH(this->root->right);*/

        cout << endl;
    }

    void preorderH(TreapNode<T> *&node) {
        if (node == nullptr) {
            return;
        }

        cout << node->key << " ";

        preorderH(node->left);
        preorderH(node->right);
    }

    void inorder() {
        inorderH(this->root);
        /*if (this->root == nullptr) {
            return;
        }

        inorderH(this->root->left);
        cout << this->root->key << " ";
        inorderH(this->root->right);*/
        cout << endl;
    }

    void inorderH(TreapNode<T> *&node) {
        if (node == nullptr) {
            return;
        }

        inorderH(node->left);
        cout << node->key << " ";
        inorderH(node->right);
    }

    void postorder() {
        postorderH(this->root);
        /*if (this->root == nullptr) {
            return;
        }

        postorderH(this->root->left);
        postorderH(this->root->right);

        cout << this->root->key << " ";*/
        cout << endl;
    }

    void postorderH(TreapNode<T> *&node) {
        if (node == nullptr) {
            return;
        }

        postorderH(node->left);
        postorderH(node->right);

        cout << node->key << " ";
    }

    int remove(T k) {
        if (this->search(k) != -1){
            removeH(this->root, k);
            this->s--;
            return 1;
        }

        return 0;
    }

    bool removeH(TreapNode<T> *&node, T k) {
        if (node == nullptr) {
            return false;
        }

        if (k < node->key) {
            node->subtreeSize--;
            return removeH(node->left, k);
        }

        if (k > node->key) {
            node->subtreeSize--;
            return removeH(node->right, k);
        }

        if (!node->left && !node->right) {
            delete node;
            node = nullptr;
        } else if (!node->left || !node->right) {
            TreapNode<T>* child = (node->left) ?  node->left : node->right;

            TreapNode<T>* oldNode = node;

            node = child;

            delete oldNode;
            oldNode = nullptr;
        } else {
            if (node->left->priority > node->right->priority) {
                node->subtreeSize--;
                rotateLeft(node);
                removeH(node->left, k);
            } else {
                node->subtreeSize--;
                rotateRight(node);
                removeH(node->right, k);
            }
        }

        return true;
    }

    int rank(T k) {
        if (this->search(k) != -1) {
            return rankH(this->root, k);
        }

        return 0;

    }

    int rankH(TreapNode<T> *&node, T k) {
        /*if (node == nullptr) {
            return 0;
        }*/
        if (k < node->key) {
            return rankH(node->left, k);
        } else if (k > node->key) {
            return 1 + (node->left ? node->left->subtreeSize : 0) + rankH(node->right, k);
        } else {
            return (node->left ? node->left->subtreeSize : 0) + 1;
        }
    }

    T select(int pos) {
        if (pos != 0) {
            return selectH(this->root, pos - 1)->key;
        }

        return selectH(this->root, pos)->key;
    }

    TreapNode<T>* selectH(TreapNode<T> *&node, int pos) {
        if (node == nullptr) {
            return nullptr;
        }
        int t = (node->left ? node->left->subtreeSize : 0);
        if (t > pos) {
            return selectH(node->left, pos);
        } else if (t < pos) {
            return selectH(node->right, pos - t - 1);
        } else {
            return node;
        }

        return node;
    }

    T successor(T k) {
        int pos = rank(k);
        T help = pos > this->root->subtreeSize ? select(pos) : select(pos + 1);
        return help;
    }

    T predecessor(T k) {
        int pos = rank(k);
        T help = pos < 1 ? select(pos) : select(pos - 1);
        return help;
    }

    int size() {
        return this->s;
    }
};

template<class T>
void printNode(TreapNode<T> *&node) {
    cout << "Key: " << node->key << " Priority: " << node->priority << " Left: " << node->left << " Right: "
         << node->right << endl;
}


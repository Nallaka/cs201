//
// Created by MIthul Nallaka on 11/9/21.
//
#include "CDA.cpp"
template<class T>
class Heap{
private:
    CDA<T> data;
    int size = 0;

public:
    Heap() {
        this->data = CDA<T>();
    }

    Heap(T k[], int s) {
        this->data = CDA<T>();
        this->size = 0;

        for (int i = 0; i < s; i++) {
            data.AddEnd(k[i]);
            this->size++;
        }

        int start = (this->size / 2) - 1;
        for (int i = start; i >= 0; i--) {
            minHeapify(i);
        }
        //minHeapifyBottomUp((this->size-1 / 2) - 1);
    }

    T peekKey() {
        return data[0];
    }

    T extractMin() {
        if (this->size < 1) {
            cout << "Heap underflow error" << endl;
            return T();
        }

        T min = data[0];
        data[0] = data[this->size-1];
        this->size--;
        this->data.DelEnd();
        minHeapify(0);
        return min;
    }

    void printKey() {
        for (int i = 0; i < this->size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    T parent(int i) {
        return (i-1)/2;
    }

    T left(int i) {
        return 2*i + 1;
    }

    T right(int i) {
        return 2*i + 2;
    }

    void minHeapify(int i) {
        int left = this->left(i);
        int right = this->right(i);
        int smallest = 0;

        if (left < this->size && data[left] < data[i]) {
            smallest = left;
        } else {
            smallest = i;
        }

        if (right < this->size  && data[right] < data[smallest]) {
            smallest = right;
        }

        if (smallest != i) {
            T temp = data[i];
            data[i] = data[smallest];
            data[smallest] = temp;
            minHeapify(smallest);
        }
    }

    void minHeapifyBottomUp(int i) {
        int parent = this->parent(i);
        if (parent >= 0) {
            if (data[i] < data[parent]) {
                T temp = data[i];
                data[i] = data[parent];
                data[parent] = temp;
                minHeapifyBottomUp(parent);
            }
        }
    }

    void insert(T k) {
        this->size++;
        this->data.AddEnd(k);
        this->minHeapifyBottomUp(this->size-1);
    }

    void buildMinHeap() {
        for (int i = (this->size-1) / 2; i >= 0 ; i--) {
            minHeapify(i);
        }
    }
};

int main() {
    string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
    int B[10] = {10,9,8,7,6,5,4,3,2,1};

    Heap<int> T1, T2(B,10);

    T2.printKey();
    //Should output  1 2 4 3 6 5 8 10 7 9

    for(int i=0; i<10; i++) T1.insert(B[i]);

    T1.printKey();
    // Should output 1 2 5 4 3 9 6 10 7 8

    cout << T2.peekKey() << endl;
    //Should output 1

    cout << T1.extractMin() << endl;
    //Should output 1

    T1.printKey();
    //Should output 2 3 5 4 8 9 6 10 7

}

//
// Created by mithu on 9/11/2021.
//
#include <iostream>

using namespace std;

#include <array>

template<class T>
class CDA {
public:
    CDA();

    CDA(int s);

    CDA(int s, T init);

    ~CDA();

    T &operator[](int i);

    void AddEnd(T v);

    void AddFront(T v);

    void DelEnd();

    void DelFront();

    int Length();

    int Capacity();

    T Select(int k);

    void Sort();

    int Search(T e);

    int BinSearch(T e);

    void current();

private:
    int size;
    int capacity;
    T *arr;

    int frontIndex;
    int endIndex;

    void grow();

    void shrink();
};


template<class T>
CDA<T>::CDA() {
    this->size = 0;
    this->capacity = 1;
    arr = new T[this->capacity];
    frontIndex = 0;
    endIndex = 0;
}

template<class T>
CDA<T>::CDA(int s) {
    this->size = s;
    this->capacity = s;
    arr = new T[this->capacity];
    frontIndex = 0;
    endIndex = size - 1;
}

template<class T>
CDA<T>::CDA(int s, T init) {

}

template<class T>
CDA<T>::~CDA() {
    delete[] arr;
}

template<class T>
void CDA<T>::grow() {
    T *new_arr;

    int new_capacity = this->capacity * 2;

    new_arr = new T[new_capacity];

    for (int i = 0; i < new_capacity; i++) {
        new_arr[i] = this->arr[i];
    }

    capacity = new_capacity;
    arr = new_arr;
    frontIndex = 0;
    endIndex = frontIndex + size - 1;
}

template<class T>
void CDA<T>::shrink() {
    T *new_arr;

    int new_capacity = this->capacity / 2;

    new_arr = new T[new_capacity];

    for (int i = 0; i < new_capacity; i++) {
        new_arr[i] = this->arr[i];
    }

    capacity = new_capacity;
    arr = new_arr;
    frontIndex = 0;
    endIndex = frontIndex + size - 1;
}

template<class T>
T &CDA<T>::operator[](int i) {
    if (i < 0 || i >= this->size) {
        cout << "Index out of bounds." << endl;
        return arr[0];
    } else if (i < capacity) {
        return arr[(frontIndex + i) % capacity];
    }
}

template<class T>
void CDA<T>::AddEnd(T v) {
    if (size >= capacity) {
        this->grow();
    }

    endIndex = (endIndex + 1) % capacity;
    arr[endIndex] = v;
    size++;
}

template<class T>
void CDA<T>::AddFront(T v) {
    if (size >= capacity) {
        this->grow();
    }

    frontIndex = (frontIndex + capacity - 1) % capacity;
    size++;
    arr[frontIndex] = v;
}

template<class T>
void CDA<T>::DelEnd() {
    if (size == 0) return;

    endIndex = (endIndex - 1) % capacity;
    size--;

    if (size <= capacity / 4) {
        this->shrink();
    }
}

template<class T>
void CDA<T>::DelFront() {
    if (size == 0) return;

    frontIndex = (frontIndex + 1) % capacity;
    size--;

    if (size <= capacity / 4) {
        this->shrink();
    }
}

template<class T>
int CDA<T>::Length() {
    return this->size;
}

template<class T>
int CDA<T>::Capacity() {
    return this->capacity;
}

template<class T>
T CDA<T>::Select(int k) {
    return nullptr;
}

template<class T>
void CDA<T>::Sort() {

}

template<class T>
int CDA<T>::Search(T e) {
    return 0;
}

template<class T>
int CDA<T>::BinSearch(T e) {
    return 0;
}

template<class T>
void CDA<T>::current() {
    cout << "Current Capacity: " << capacity << " Current Size: " << size << " Current Front: " << frontIndex
         << " Current End: " << endIndex << endl;
}

void foo(CDA<int> x) {
    for (int i = 0; i < x.Length() / 2; i++)
        x[i] = x[x.Length() / 2 + i];
    // X => "6 7 8 9 10 15 19 6 7 8 9 10 15 19 11"
    for (int i = 0; i < x.Length(); i++) cout << x[i] << " ";
    cout << endl;
}

int main() {
    CDA<float> C(10);
    for (int i=0; i< C.Length();i++) C[i] = i;
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    // C => "0 1 2 3 4 5 6 7 8 9"
    C.DelFront();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    // C => "1 2 3 4 5 6 7 8 9"
    C.DelEnd();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    // C => "1 2 3 4 5 6 7 8"
    C.AddEnd(100.0);
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    // C => "1 2 3 4 5 6 7 8 100"
    C.AddEnd(101.0);
    C.current();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    // C => "1 2 3 4 5 6 7 8 100 101"
    C.DelEnd();
    C.current();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    C.DelFront();
    C.current();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    C.AddFront(-100.0);
    C.current();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    C.AddFront(-200.0);
    C.current();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    // C => "-200 -100 2 3 4 5 6 7 8 100"
    C.AddFront(-200.0);
    C.current();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    C.DelEnd();
    C.DelEnd();
    C.DelEnd();
    C.DelEnd();
    C.DelEnd();
    C.DelEnd();
    C.current();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
    C.DelEnd();
    C.current();
    for (int i=0; i< C.Length();i++) cout << C[i] << " ";  cout << endl;
}
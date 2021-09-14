//
// Created by mithu on 9/11/2021.
//

#include "CDA.h"
#include <iostream>

using namespace std;

template<class T>
CDA<T>::CDA() {
    this->size = 0;
    this->capacity = 1;
    arr = new T[this->size];
}

template<class T>
CDA<T>::CDA(int s) {
    this->size = s;
    this->capacity = s;
    *arr = new T[this->size];
}

template<class T>
CDA<T>::CDA(int s, T init) {

}

template<class T>
CDA<T>::~CDA() {
    delete this->size;
    delete this->capacity;
    delete[] *arr;
}

template<class T>
T &CDA<T>::operator[](int i) {
    if (i < 0 || i > this->size-1) {
        cout << "Index out of bounds.";
        return nullptr;
    }
}

template<class T>
void CDA<T>::AddEnd(T v) {

}

template<class T>
void CDA<T>::AddFront(T v) {

}

template<class T>
void CDA<T>::DelEnd() {

}

template<class T>
void CDA<T>::DelFront() {

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

int main() {
    auto *arr = new CDA<int>();
    cout << arr->Length() << endl;
    cout << arr->Capacity();
    arr[2];
    return 0;
}

//
// Created by mithu on 9/11/2021.
//

#ifndef CS201_CDA_H
#define CS201_CDA_H


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

private:
    int size;
    int capacity;
    T *arr;

    int head;
    int tail;
};


#endif //CS201_CDA_H

//
// Created by MIthul Nallaka on 11/9/21.
//

//
// Created by mithu on 9/11/2021.
//
#include <iostream>

using namespace std;

template<class T>
class CDA {
public:
    CDA();

    CDA(int s);

    CDA(int s, T init);

    ~CDA();

    T &operator[](int i);

    void operator=(const CDA<T> &);

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

    int *from;
    int *to;
    int top;

    int frontIndex;
    int endIndex;

    bool known_init = false;
    T init_val;

    void grow();

    void shrink();

    T out_of_bounds;

    int binarySearch(T *arr, int l, int r, T x);
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
    known_init = true;
    init_val = init;
    this->size = s;
    this->capacity = s;
    arr = new T[this->capacity];
    from = new int[capacity];
    to = new int[capacity];
    top = 0;
    frontIndex = 0;
    endIndex = size - 1;
}

template<class T>
CDA<T>::~CDA() {
    delete[] arr;
    /*if (!known_init) {
        delete[] from;
        delete[] to;
    }*/
}

template<class T>
void CDA<T>::grow() {
    T *new_arr;

    int new_capacity = this->capacity * 2;

    new_arr = new T[new_capacity];

    // cout << "endl" << " new array" << endl;
    for (int i = 0; i < size; i++) {
        new_arr[i] = this->arr[(frontIndex + i) % capacity];
        // cout << new_arr[i] << " ";
    }
    // cout << endl << endl;
    capacity = new_capacity;
    arr = new_arr;
    frontIndex = 0;
    endIndex = frontIndex + size - 1;
    known_init = false;
}

template<class T>
void CDA<T>::shrink() {
    int new_capacity = this->capacity / 2;
    if (new_capacity >= 4) {
        T *new_arr;

        new_arr = new T[new_capacity];

        for (int i = 0; i < new_capacity; i++) {
            new_arr[i] = this->arr[i];
        }

        capacity = new_capacity;
        arr = new_arr;
        frontIndex = 0;
        endIndex = frontIndex + size - 1;
        known_init = false;
    }
}

template<class T>
T &CDA<T>::operator[](int i) {
    if (i < 0 || i >= this->size) {
        cout << "Index out of bounds." << endl;
        return out_of_bounds;
    } else if (known_init) {
        int n = (frontIndex + i) % capacity;

        if (from[n] < top && to[from[n]] == n)
            return arr[n];
        else {
            from[n] = top;
            to[top] = n;
            arr[n] = init_val;
            top++;

            return arr[n];
        }
    } else if (i < capacity) {
        return arr[(frontIndex + i) % capacity];
    }
    return out_of_bounds;
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
int CDA<T>::Search(T e) {
    for (int i = 0; i < this->Length(); i++) {
        if (this->operator[](i) == e) {
            return i;
        }
    }
    return -1;
}

template<class T>
int CDA<T>::binarySearch(T* array, int l, int r, T x)
{
    int m = l + (r - l) / 2;
    while (l <= r) {
        m = l + (r - l) / 2;

        // Check if x is present at mid
        if (array[m] == x)
            return m;

        // If x greater, ignore left half
        if (array[m] < x)
            l = m + 1;

            // If x is smaller, ignore right half
        else
            r = m - 1;
    }

    if (x < array[m+1]) {
        return ~(m+1);
    }
    return ~size;
}


template<class T>
int CDA<T>::BinSearch(T e) {
    T array[size];
    for (int i = 0; i < size; i++) {
        array[i] = this->operator[](i);
        //cout << array[i] << " ";
    }

    return binarySearch(array, 0, size-1, e);
}

template<class T>
void CDA<T>::current() {
    cout << "Current Capacity: " << capacity << " Current Size: " << size << " Current Front: " << frontIndex
         << " Current End: " << endIndex << endl;
}

template<class T>
void CDA<T>::operator=(const CDA<T> &old) {
    size = old.size;
    capacity = old.capacity;
    arr = new T[capacity];
    *arr = *old.arr;

    for (int i = 0; i < capacity; i++) {
        arr[i] = old.arr[i];
    }


    from = old.from;
    to = old.to;
    top = old.top;

    frontIndex = old.frontIndex;
    endIndex = old.endIndex;

    known_init = old.known_init;

    init_val = old.init_val;
    out_of_bounds = old.out_of_bounds;


}

template<class T>
void merge(T *array, int l, int m, int r) {
    int i, j, k, nl, nr;
    //size of left and right sub-arrays
    nl = m - l + 1;
    nr = r - m;
    int larr[nl], rarr[nr];
    //fill left and right sub-arrays
    for (i = 0; i < nl; i++)
        larr[i] = array[l + i];
    for (j = 0; j < nr; j++)
        rarr[j] = array[m + 1 + j];
    i = 0;
    j = 0;
    k = l;
    //marge temp arrays to real array
    while (i < nl && j < nr) {
        if (larr[i] <= rarr[j]) {
            array[k] = larr[i];
            i++;
        } else {
            array[k] = rarr[j];
            j++;
        }
        k++;
    }
    while (i < nl) {       //extra element in left array
        array[k] = larr[i];
        i++;
        k++;
    }
    while (j < nr) {     //extra element in right array
        array[k] = rarr[j];
        j++;
        k++;
    }
}

template<class T>
void mergeSort(T *array, int l, int r) {
    int m;
    if (l < r) {
        int m = l + (r - l) / 2;
        // Sort first and second arrays
        mergeSort(array, l, m);
        mergeSort(array, m + 1, r);
        merge(array, l, m, r);
    }
}

template<class T>
void CDA<T>::Sort() {
    T sortedArray[this->size];

    for (int i = 0; i < size; i++) {
        sortedArray[i] = arr[(frontIndex + i) % capacity];
        //cout << sortedArray[i] << " ";
    }
    //cout << endl;

    mergeSort(sortedArray, 0, size - 1);

    //cout << sortedArray;
    for (int i = 0; i < size; i++) {
        //cout << sortedArray[i] << " ";
        this->operator[](i) = sortedArray[i];
    }
}

template<class T>
int partition(T arr[], int l, int r) {
    T x = arr[r], i = l;
    for (int j = l; j <= r - 1; j++) {
        if (arr[j] <= x) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

template<class T>
T kthSmallest(T *arr, int l, int r, int k) {
    // If k is smaller than number of
    // elements in array
    if (k > 0 && k <= r - l + 1) {

        // Partition the array around last
        // element and get position of pivot
        // element in sorted array
        int index = partition(arr, l, r);

        // If position is same as k
        if (index - l == k - 1)
            return arr[index];

        // If position is more, recur
        // for left subarray
        if (index - l > k - 1)
            return kthSmallest(arr, l, index - 1, k);

        // Else recur for right subarray
        return kthSmallest(arr, index + 1, r,
                           k - index + l - 1);
    }

    // If k is more than number of
    // elements in array
    return 2147483647;
}

template<class T>
T CDA<T>::Select(int k) {
    T array[size];
    for (int i = 0; i < size; i++) {
        array[i] = this->operator[](i);
        //cout << array[i] << " ";
    }
    return kthSmallest(array, 0, size - 1, k);
}



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

    ~Heap() {
        this->size= 0;
    }

    Heap<T>(const Heap<T> &other) {
        this->size = other.size;
        this->data = other.data;
    }

    Heap<T>& operator=(Heap<T> other) {
        this->size = other.size;
        this->data = other.data;

        return *this;
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

    int parent(int i) {
        return (i-1)/2;
    }

    int left(int i) {
        return 2*i + 1;
    }

    int right(int i) {
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
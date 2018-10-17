//
// Created by berg on 13/10/18.
//

#include<iostream>
#include<climits>
using namespace std;

void swap(int *x, int *y);

class MinHeap {
    int *heap;
    int capacity;
    int currentSize;
public:
    MinHeap(int capacity);

    void MinHeapify(int );

    int parent(int i) { return (i - 1) / 2; }

    int left(int i) { return (2 * i + 1); }

    int right(int i) { return (2 * i + 2); }

    int extractMin();

    void decreaseKey(int i, int newValue);

    int getMin() { return heap[0]; }

    void deleteKey(int i);

    void insertKey(int key);
};

MinHeap::MinHeap(int capacity) {
    currentSize = 0;
    this->capacity = capacity;
    heap = new int[capacity];
}

void MinHeap::insertKey(int key) {
    if (currentSize == capacity) {
        cout << " Could not insertKey\n";
        return;
    }

    currentSize++;
    int i = currentSize - 1;
    heap[i] = key;

    while (i != 0 && heap[parent(i)] > heap[i]) {
       swap(&heap[i], &heap[parent(i)]);
       i = parent(i);
    }
}

void MinHeap::decreaseKey(int i, int newValue) {
    heap[i] = newValue;
    while (i != 0 && heap[parent(i)] > heap[i]) {
       swap(&heap[i], &heap[parent(i)]);
       i = parent(i);
    }
}

int MinHeap::extractMin() {
    if (currentSize <= 0) return INT_MAX;

    if (currentSize == 1) {
        currentSize--;
        return heap[0];
    }

    int root = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    MinHeapify(0);

    return root;
}


void MinHeap::deleteKey(int i) {
    decreaseKey(i, INT_MIN);
    extractMin();
}

void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < currentSize && heap[l] < heap[i]) smallest = l;
    if (r < currentSize && heap[r] < heap[smallest]) smallest = r;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        MinHeapify(smallest);
    }
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

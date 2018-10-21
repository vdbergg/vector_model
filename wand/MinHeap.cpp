//
// Created by berg on 13/10/18.
//

#include<iostream>
#include<climits>
#include "MinHeap.h"

using namespace std;

MinHeap::MinHeap(int capacity) {
    currentSize = 0;
    this->capacity = capacity;
    heap = new HeapPayload[capacity];
}

bool MinHeap::insertKey(HeapPayload key) {
    if (currentSize == capacity) return false;

    currentSize++;
    int i = currentSize - 1;
    heap[i] = key;

    while (i != 0 && heap[parent(i)].score > heap[i].score) {
       swap(&heap[i], &heap[parent(i)]);
       i = parent(i);
    }

    return true;
}

void MinHeap::decreaseKey(int i, HeapPayload newValue) {
    heap[i] = newValue;
    while (i != 0 && heap[parent(i)].score > heap[i].score) {
       swap(&heap[i], &heap[parent(i)]);
       i = parent(i);
    }
}

HeapPayload MinHeap::extractMin() {
    if (currentSize <= 0) {
        HeapPayload heapPayload;
        heapPayload.score = -1;
        heapPayload.docId = -1;

        return heapPayload;
    };

    if (currentSize == 1) {
        currentSize--;
        return heap[0];
    }

    HeapPayload root = heap[0];
    heap[0] = heap[currentSize - 1];
    currentSize--;
    MinHeapify(0);

    return root;
}


void MinHeap::deleteKey(int i) {
    HeapPayload heapPayload;
    heapPayload.docId = heap[i].docId;
    heapPayload.score = INT_MIN;
    decreaseKey(i, heapPayload);
    extractMin();
}

void MinHeap::MinHeapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;

    if (l < currentSize && heap[l].score < heap[i].score) smallest = l;
    if (r < currentSize && heap[r].score < heap[smallest].score) smallest = r;

    if (smallest != i) {
        swap(&heap[i], &heap[smallest]);
        MinHeapify(smallest);
    }
}

void swap(HeapPayload *x, HeapPayload *y) {
    HeapPayload temp = *x;
    *x = *y;
    *y = temp;
}

//
// Created by berg on 20/10/18.
//

#ifndef VECTOR_MODEL_MINHEAP_H
#define VECTOR_MODEL_MINHEAP_H

#endif //VECTOR_MODEL_MINHEAP_H

struct HeapPayload {
    int docId;
    double score;
};

void swap(HeapPayload *x, HeapPayload *y);

class MinHeap {
    HeapPayload *heap;
    int capacity;
    int currentSize;
public:
    MinHeap(int capacity);

    void MinHeapify(int );

    int parent(int i) { return (i - 1) / 2; }

    int left(int i) { return (2 * i + 1); }

    int right(int i) { return (2 * i + 2); }

    HeapPayload extractMin();

    void decreaseKey(int i, HeapPayload newValue);

    HeapPayload getMin() { return heap[0]; }

    void deleteKey(int i);

    bool insertKey(HeapPayload key);
};

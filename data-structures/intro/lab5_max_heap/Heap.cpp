#include <iostream>
#include "Heap.h"

Heap::Heap() { // constructor
    numItems = 0;
}

void Heap::enqueue(PrintJob* data){ // takes care of allocating heap data
    if(numItems < MAX_HEAP_SIZE){
        arr[numItems] = data;
        ++numItems;
        moveUp(numItems-1); // sorts heap to follow Max heap rules
    }
}

void Heap::dequeue(){ // takes care of moving the heap around to follow Max heap regulations
    if(numItems == 1) { // base case
        --numItems;
    }
    else if(numItems > 1) { // moves data around
        swap (arr[0], arr[numItems-1]);
        --numItems;
        trickleDown(0);
    }
}

void Heap::print(){ // prints node with highest priority
    if(highest() == nullptr){
        cout << "No items in priority queue"<< endl;
    }
    else {
        cout << "Priority: " << highest()->getPriority() << ", Job Number: "<< highest()-> getJobNumber() << ", Number of Pages: " << highest() -> getPages() << endl;
    }
}

PrintJob* Heap::highest(){ // returns the root node (aka the highest priority node)
    if(numItems > 0){
        return arr[0];
    }
    else {
        return nullptr;
    }
}

void Heap::trickleDown(int index){ //algorithm for dequeing root node or other nodes

    int child = 2 * index + 1;
    int value = arr[index] -> getPriority();

    while (child < numItems) {
        int maxValue = value;
        int maxIndex;
        for (int i = 0; i < 2 && i + child < numItems; ++i) { // finds the highest priority value
            if (arr[i + child] -> getPriority() > maxValue) {
                maxValue = arr[i + child] -> getPriority();
                maxIndex = i + child;
            }
        }
        if (maxValue == value) {
            return;
        }
        else {
            swap(arr[index], arr[maxIndex]);
            index = maxIndex;
            child = 2 * index + 1;
        }
    }
}

void Heap::moveUp(int index) { // additional helper function that helps move heap around when enqueing
    int parentIndex = 0;
    while (index > 0) {
        parentIndex = (index - 1) / 2;
        if (arr[index] -> getPriority() <= arr[parentIndex] -> getPriority()){
            return;
        }
        else{
            swap(arr[index],arr[parentIndex]);
            index = parentIndex;
        }
    }
}
#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

const int MAX_SIZE = 20;

template<typename T>

class stack {
    public: 
        stack() : _size(0){} // inline argument constructor creates empty stack
        void push(T val); // puts data in front of the stack
        void pop(); // removes last element from the array 
        void pop_two(); // removes last two elements from array 
        T top(); // returns the value at the top of the stack
        bool empty(); // returns true if no data is in the stack. Otherwise, returns false. 
    private:
        T _data[MAX_SIZE]; // new array
        int _size;
};

template<typename T>
void stack<T>::push(T val) {
    int index = _size;
    if (_size >= MAX_SIZE) { // overflow exception check
        throw overflow_error("Called push on full stack.");
    }

    _data[index++] = val; // allocates value passed in to the array. 
    ++_size;
}

template<typename T>
void stack<T>::pop(){
    if (empty()) { // out of range exception if the stack is empty. 
        throw out_of_range("Called pop on empty stack.");
    }

    --_size;
}

template<typename T>
void stack<T>::pop_two() {
    if (empty()) { // out of range exception if the array is empty 
        throw out_of_range("Called pop_two on empty stack.");
    }

    if (_size == 1) { // out of range exception if array size is 1
        throw out_of_range("Called pop_two on a stack of size 1.");
    }

    _size -= 2;
}

template<typename T>
T stack<T>::top() {
    if (empty()) { // undrflow exception if the stack is empty
        throw underflow_error("Called top on empty stack.");
    }

    return _data[_size - 1]; // top of stack
}

template<typename T>
bool stack<T>::empty(){
    if (_size == 0) { 
        return true;
    }

    return false; 
}
#endif
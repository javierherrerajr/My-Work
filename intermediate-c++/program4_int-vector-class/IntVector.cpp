#include <iostream>
#include <stdexcept>
using namespace std; 

#include "IntVector.h"

IntVector::IntVector(unsigned capacity, int value) {
    _capacity = capacity; 
    _size = capacity; 
    if (_capacity == 0) {
        _data = nullptr; 
    }

    else {
        _data = new int [_size]; 

        for (unsigned int i = 0; i < _size; ++i) {
            _data[i] = value;
        }
    }
}

IntVector::~IntVector() {
    delete[] _data; 
}

unsigned IntVector::size() const {
    return _size; 
}

unsigned IntVector::capacity() const {
    return _capacity; 
}

bool IntVector::empty() const {
    if (_size == 0) {
        return true; 
    }

    else {
        return false; 
    }
}

const int & IntVector::at(unsigned index) const {
    if ((index > _size - 1) || (empty() == true)) {
        throw out_of_range("IntVector::at_range_check");
    }

    return _data[index]; 
}

int & IntVector::at(unsigned index) {
    if ((index > _size - 1) || (empty() == true)) {
        throw out_of_range("IntVector::at_range_check");
    }

    return _data[index]; 
}

void IntVector::insert(unsigned index, int value) {
    if (index > _size) {
        throw out_of_range("IntVector::insert_range_check");   
    }

    if (_size == _capacity) {
        expand();  
    }
    
    ++_size; 
    if (index == _size - 1) {
        _data[_size - 1] = value; 
    }

    else {
        for (unsigned int i = _size - 1; i > index; --i) {
            _data[i] = _data[i - 1]; 
        }

        _data[index] = value; 
    }
}

void IntVector::erase(unsigned index) {
    if ((index > _size) || (index == _size)) {
        throw out_of_range("IntVector::erase_range_check");   
    }

    else {
        for (unsigned int i = index; i + 1 < _size ; ++i) {
            _data[i] = _data[i + 1]; 
        }
    }

    --_size;
}

const int & IntVector::front() const {
    return _data[0]; 
}

int & IntVector::front() {
    return _data[0]; 
}

const int & IntVector::back() const {
    return _data[_size - 1]; 
}

int & IntVector::back() {
    return _data[_size - 1]; 
}

void IntVector::assign(unsigned n, int value) {
    if (n > _capacity) {
        if (n - _capacity > _capacity) {
            expand(n - _capacity); 
        }

        else {
            expand(); 
        }
    }

    _size = n; 

    for (unsigned int i = 0; i < _size; ++i) {
        _data[i] = value; 
    }
}

void IntVector::push_back(int value) {
    if ((_size == _capacity) || (_size > _capacity)) {
        expand(); 
        _size += 1; 
        _data[_size - 1] = value; 
    }

    else { 
        _size += 1; 
        _data[_size - 1] = value; 
    }
}

void IntVector::pop_back() {
    _size -= 1; 
}

void IntVector::clear() {
    _size = 0;  
}

void IntVector::resize(unsigned size, int value) {
    if (size <= _size){
        _size = size;
    }
    else if (size > _size && size <= _capacity){
        for (unsigned int i = _size; i < size; ++i){
            _data[i] = value;
        }
        _size = size;
    }
    else {
        if (size > (_size * 2)){
            expand(size - _capacity);
            for (unsigned int i = _size; i < size; ++i){
                _data[i] = value;
            }
            _size = size;
        }
        else{
            expand();
            for (unsigned int i = _size; i < size; ++i){
                _data[i] = value;
            }
            _size = size;
        }
    }
}

void IntVector::reserve(unsigned n) {
    if (n > _capacity) {
        _capacity = n; 
    }
}

void IntVector::expand() {
    int *temp = new int[_capacity * 2];

    if (_capacity == 0) {
        _data = new int [1]; 
        _capacity = 1; 
    }

    else {
        _capacity *= 2; 

        for (unsigned int i = 0; i < _size; ++i) {
            temp[i] = _data[i];  
        }
    }

    delete[] _data; 
    _data = temp; 
}

void IntVector::expand(unsigned amount) {
        _capacity += amount; 
        int *temp = new int [_capacity]; 

        for (unsigned int i = 0; i < _size; ++i) {
            temp[i] = _data[i];  
        }

        delete[] _data; 
        _data = temp; 
}
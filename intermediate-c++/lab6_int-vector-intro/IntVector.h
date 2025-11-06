#include <iostream>
using namespace std; 

class IntVector {
    public: 
        IntVector(unsigned capacity = 0, int value = 0); 
        ~IntVector(); 
        unsigned size() const; 
        unsigned capacity() const; 
        bool empty() const; 
        const int & at(unsigned index) const; 
        const int & front() const; 
        const int & back() const; 
    private: 
        unsigned _size; //size of IntVector
        unsigned _capacity; //must always be >= _size
        int *_data; //address of dynamically-allocated array
};
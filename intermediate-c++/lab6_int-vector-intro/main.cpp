#include <iostream>
using namespace std; 

#include "IntVector.h"

int main () {
    IntVector test1; //Default constructor testing
    cout << "size: " << test1.size() << endl; //tests default size should be 0
    cout << "capacity: " << test1.capacity() << endl; //tests default capacity should be 0
    cout << "is empty? :" << test1.empty() << endl; //tests default if it's empty (should be true)

    IntVector* data = new IntVector(10, 4); //testing with parameters and deconstructor function
    cout << "size: " << data->size() << endl; //tests for size should be > 0
    cout << "capacity: " << data->capacity() << endl; //tests for capacity should be > 0
    cout << "is empty?: " << data->empty() << endl; //tests if vector is empty should be false
    cout << "is index valid: " << data->at(5) << endl; //tests if index is valid should output 4
    cout << "front: " << data->front() << endl; //tests to output front value
    cout << "back: " << data->back() << endl; //tests to output back value

    delete[] data; //tests deconstructor (test statement is in deconstrutor function)

    IntVector* data2 = new IntVector(10, 3); 
    cout << data2->at(13) << endl; //tests for index out of range error should be out of range

    return 0; 
}
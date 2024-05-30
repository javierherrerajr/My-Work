#include <iostream>
using namespace std; 

#include "IntVector.h"

int main () {
    IntVector test1; //Default constructor testing
    cout << "size: " << test1.size() << endl; //tests default size should be 0
    cout << "capacity: " << test1.capacity() << endl; //tests default capacity should be 0
    cout << "is empty? :" << test1.empty() << endl; //tests default if it's empty (should be true)
    cout << "insert: "; test1.insert(0, 12); cout << endl; //tests for empty vector
    cout << "erase: "; test1.erase(0); cout << endl; //tests for empty vector
    cout << "front: " << test1.front() << endl; //test for empty vector should output error
    cout << "back: " << test1.back() << endl; //test for empty vector should be error
    cout << "push_back: "; test1.push_back(40); cout << endl; //test for empty vector should add element to vector
    cout << "clear: "; test1.clear(); cout << endl; //test should empty vecotr if not empty already; 
    cout << "resize: "; test1.resize(20, 76); cout << endl; //should resize vector to given values

    IntVector* data = new IntVector(10, 4); //testing with parameters and deconstructor function
    cout << "size: " << data->size() << endl; //tests for size should be > 0
    cout << "capacity: " << data->capacity() << endl; //tests for capacity should be > 0
    cout << "is empty?: " << data->empty() << endl; //tests if vector is empty should be false
    cout << "is index valid: " << data->at(5) << endl; //tests if index is valid should output 4
    cout << "front: " << data->front() << endl; //tests to output front value
    cout << "back: " << data->back() << endl; //tests to output back value
    cout << "insert: "; data->insert(5, 75); cout << endl; //should insert value 75 at 5
    cout << "erase: "; data->erase(3); cout << endl; //should erase specific index
    cout << "assign: "; data->assign(20, 3); cout << endl; //should assign all new elements to 3
    cout << "pop_back: "; data->pop_back(); cout << endl; //Should remove 4 from the back of vector
    cout << "resize: "; data->resize(15, 4); cout << endl; //Should resize vecotr and make all elements 4
    cout << "reserve: "; data->reserve(4); cout << endl; //Should make sure capacity is 4 minimum

   delete[] data; //tests deconstructor (test statement is in deconstrutor function)

    IntVector* data2 = new IntVector(10, 3); 
    cout << data2->at(13) << endl; //tests for index out of range error should be out of range
    delete[] data2;

    return 0; 
}
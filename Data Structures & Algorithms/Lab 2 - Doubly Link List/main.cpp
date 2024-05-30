#include "IntList.h"

int main() {
    cout << "Testing doubly linked list class..." << endl;
    cout << "Creating a new IntList, myList." << endl;

    IntList *myList = new IntList();
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out nothing at all): " << *myList << endl;
    cout << "Printing myList backwards (should print out nothing at all): ";
    myList->printReverse();
    cout << endl << endl;

    cout << "Pushing 1 to the front of the list..." << endl;
    myList->push_front(1);
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out just a 1): " << *myList << endl;
    cout << "Printing myList backwards (should print out just a 1): ";
    myList->printReverse();
    cout << endl << endl;

    cout << "Pushing 2 to the back of the list..." << endl;
    myList->push_back(2);
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out 1 2): " << *myList << endl;
    cout << "Printing myList backwards (should print out 2 1): ";
    myList->printReverse();
    cout << endl << endl;

    cout << "Pushing 0 to the front of the list..." << endl;
    myList->push_front(0);
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out 0 1 2 3): " << *myList << endl;
    cout << "Printing myList backwards (should print out 3 2 1 0): ";
    myList->printReverse();
    cout << endl << endl;

    cout << "Popping front..." << endl;
    myList->pop_front();
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out 1 2 3 4): " << *myList << endl;
    cout << "Printing myList backwards (should print out 4 3 2 1): ";
    myList->printReverse();
    cout << endl << endl;
    
    cout << "Popping back..." << endl;
    myList->pop_back();
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out 1 2 3): " << *myList << endl;
    cout << "Printing myList backwards (should print out 3 2 1): ";
    myList->printReverse();
    cout << endl << endl;

    cout << "Popping front..." << endl;
    myList->pop_front();
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out 2 3): " << *myList << endl;
    cout << "Printing myList backwards (should print out 3 2): ";
    myList->printReverse();
    cout << endl << endl;
    
    cout << "Popping back..." << endl;
    myList->pop_back();
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out 2): " << *myList << endl;
    cout << "Printing myList backwards (should print out 2): ";
    myList->printReverse();
    cout << endl << endl;

    cout << "Popping front..." << endl;
    myList->pop_front();
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out nothing): " << *myList << endl;
    cout << "Printing myList backwards (should print out nothing): ";
    myList->printReverse();
    cout << endl << endl;
    
    cout << "Popping back..." << endl;
    myList->pop_back();
    cout << "empty() returns " << myList->empty() << endl;
    cout << "Printing myList in order (should print out nothing): " << *myList << endl;
    cout << "Printing myList backwards (should print out nothing): ";
    myList->printReverse();
    cout << endl << endl;

    cout << "Calling destructor..." << endl;
    delete myList;

    return 0;
}
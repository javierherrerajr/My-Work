#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned int min = index;
    for (unsigned int i = index; i < vals.size(); ++i) {
        if (vals.at(i) < vals.at(min)) {
            min = i;
        }
    }
    return min;
}

template<typename T>
void selection_sort(vector<T> &vals) {
     for (unsigned i = 0; i + 1 < vals.size(); ++i)
    {
        unsigned minIndex = min_index(vals, i);
        T temp = vals.at(i);
        vals.at(i) = vals.at(minIndex);
        vals.at(minIndex) = temp;
    }
}

template<typename T>
T getElement(vector<T> vals, int index) {
    int size = vals.size();
    if (index >= size || index < 0) {
        throw out_of_range("out of range exception occured");

    }
    return vals.at(index);
}

int main(){
    vector<int>* intVector = new vector<int>();
    intVector->push_back(9);
    intVector->push_back(333);
    intVector->push_back(7);
    intVector->push_back(10);
    intVector->push_back(42);

    selection_sort(*intVector);

    vector<char>* charVector = new vector<char>();
    charVector->push_back('a');
    charVector->push_back('w');
    charVector->push_back('1');
    charVector->push_back('*');
    charVector->push_back('A');

    selection_sort(*charVector);

    vector<string>* stringVector = new vector<string>();
    stringVector->push_back("bananas");
    stringVector->push_back("apple");
    stringVector->push_back("watermelon");
    stringVector->push_back("kiwi");
    stringVector->push_back("Apple");

    selection_sort(*stringVector);

    
    //Part B
     srand(time(0));
     vector<char> vals = createVector();
     char curChar;
     int index;
     int numOfRuns = 10;
     while(--numOfRuns >= 0){
        try {
         cout << "Enter a number: " << endl;
         cin >> index;
         curChar = getElement(vals,index);
         cout << "Element located at " << index << ": is " << curChar << endl;
        }
        catch (out_of_range& excpt) {
        cout << "Out of range exception occurred." << endl;
        }
    }

    return 0;
}
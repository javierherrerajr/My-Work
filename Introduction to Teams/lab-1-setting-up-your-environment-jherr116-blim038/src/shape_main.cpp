#include <iostream>
#include <string>
#include <stdexcept>
#include "../header/rectangle.hpp"
#include "../header/triangle.hpp"

using namespace std; 

int main () {
    char userInput;
    int height; 
    int width;
    int base;

    cout << "Choose a (r)ectangle or (t)riangle:" << endl; 
    cin >> userInput;

    try {
        if (userInput == 'r') {
            cout << "What's the height?" << endl;
            cin >> height; 

            if (height < 0) {
                throw out_of_range("Enter a positive number");
            }

            cout << "What's the width?" << endl;
            cin >> width; 
                
            if (width < 0) {
                throw out_of_range("Enter a positive number");
            }

            Rectangle userShape; 
            userShape.set_height(height);
            userShape.set_width(width);
            cout << "Rectangle area: " << userShape.area() << endl;
        }

        else if (userInput == 't') {
            cout << "What's the height?" << endl;
            cin >> height;
                    
            if (height < 0) {
                throw out_of_range("Enter a positivie number");
            }

            cout << "What's the base" << endl; 
            cin >> base;

            if (base < 0) {
                throw out_of_range("Enter a positive number");
            }

            Triangle userShape;
            userShape.set_base(base);
            userShape.set_height(height);
            cout << "Triangle area: " << userShape.area() << endl;
        }

        else {
            cout << "Enter r(rectangle) or t(triangle)" << endl; 
        }
    }

    catch (out_of_range& e) {
        cout << e.what() << endl;
    }

    return 0; 
}
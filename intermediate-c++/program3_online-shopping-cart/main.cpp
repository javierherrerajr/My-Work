#include <iostream>
#include <string>
using namespace std;

#include "ShoppingCart.h"

void printMenu(ShoppingCart &options) {
    char choice; 
    string customerItemName; 
    string customerItemDescription; 
    int customerItemPrice; 
    int customerItemQuantity; 

    do {
        cout << "MENU" << endl; 
        cout << "a - Add item to cart" << endl; 
        cout << "d - Remove item from cart" << endl; 
        cout << "c - Change item quantity" << endl; 
        cout << "i - Output items' descriptions" << endl; 
        cout << "o - Output shopping cart" << endl; 
        cout << "q - Quit" << endl; 
        cout << endl; 
        cout << "Choose an option: " << endl;  

        cin >> choice; 

        while ((choice != 'a') && (choice != 'd') && (choice != 'c') && (choice != 'i') && (choice != 'o') && (choice != 'q')) {
        cout << "Choose an option: " << endl; 
        cin >> choice; 
    }

        
        if (choice == 'a') {
            cin.ignore();
            cout << endl; 
            cout << "ADD ITEM TO CART" << endl; 
            cout << "Enter the item name: " << endl; 
            getline(cin, customerItemName); 
            cout << "Enter the item description: " << endl; 
            getline(cin, customerItemDescription); 
            cout << "Enter the item price: " << endl; 
            cin >> customerItemPrice;
            cout << "Enter the item quantity: " << endl; 
            cin >> customerItemQuantity; 
            cout << endl; 

            ItemToPurchase customerItem(customerItemName, customerItemDescription, customerItemPrice, customerItemQuantity); 
            options.addItem(customerItem); 
        }

        if (choice == 'd') {
            cin.ignore(); 
            cout << endl; 
            cout << "REMOVE ITEM FROM CART" << endl; 
            cout << "Enter name of item to remove: " << endl; 
            getline(cin, customerItemName); 

            options.removeItem(customerItemName);  
        }

        if (choice =='c') {
            cin.ignore(); 
            cout << endl; 
            cout << "CHANGE ITEM QUANTITY" << endl; 
            cout << "Enter the item name: " << endl; 
            getline(cin, customerItemName); 
            cout << "Enter the new quantity: " << endl; 
            cin >> customerItemQuantity; 

            ItemToPurchase customerItem; 
            customerItem.setName(customerItemName);
            customerItem.setQuantity(customerItemQuantity);
            options.modifyItem(customerItem); 
        }

        if (choice == 'i') {
            cin.ignore(); 
            cout << endl; 
            cout << "OUTPUT ITEMS' DESCRIPTIONS" << endl; 
            options.printDescriptions(); 
        }

        if (choice == 'o') {
            cin.ignore(); 
            cout << endl; 
            cout << "OUTPUT SHOPPING CART" << endl; 
            options.printTotal(); 
        }

    
    } while (choice != 'q'); 
}

int main() {
    string name; //customer name
    string date; //current date

    cout << "Enter customer's name: " << endl; 
    getline(cin, name);
    cout << "Enter today's date: " << endl; 
    getline(cin, date); 
    cout << endl; 
    cout << "Customer name: " << name << endl; 
    cout << "Today's date: " << date << endl; 
    cout << endl; 

    ShoppingCart customer(name, date); 
    printMenu(customer); 
}
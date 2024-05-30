#include "ShoppingCart.h"

ShoppingCart::ShoppingCart() {
    _customerName = "none"; 
    _currentDate = "January 1, 2016"; 
}

ShoppingCart::ShoppingCart(string name, string date) {
    _customerName = name; 
    _currentDate = date; 
}

string ShoppingCart::customerName()const {
    return _customerName; 
}

string ShoppingCart::date()const {
    return _currentDate; 
}

void ShoppingCart::addItem(ItemToPurchase &item) { 
    _cartItems.push_back(item); 
}

void ShoppingCart::removeItem(string &itemName) {
    bool item = false; 
    for (unsigned int i = 0; i < _cartItems.size(); ++i) {
        if (itemName == _cartItems.at(i).name()) {
            _cartItems.erase(_cartItems.begin() + i); 
            item = true; 
        }
    }

    if (!item) {
        cout << "Item not found in cart. Nothing removed." << endl; 
    }

    cout << endl; 
}

void ShoppingCart::modifyItem(ItemToPurchase &modify) {
    bool modified = false; 
    for (unsigned int i = 0; i < _cartItems.size(); ++i) {
        if (modify.name() == _cartItems.at(i).name()) {
            _cartItems.at(i).setQuantity(modify.quantity());
            modified = true;  
        }
    }

    if (!modified) {
        cout << "Item not found in cart. Nothing modified." << endl; 
    }

    cout << endl; 
}

int ShoppingCart::numItemsInCart()const {
    int sum = 0;
    unsigned i; 

    for (i = 0; i < _cartItems.size(); ++i) {
        sum += _cartItems.at(i).quantity();  
    }

    return sum; 
}

int ShoppingCart::costOfCart()const {
    int total = 0; 
    unsigned i; 

    for (i = 0; i < _cartItems.size(); ++i) {
        total += (_cartItems.at(i).price() * _cartItems.at(i).quantity()); 
    }

    return total; 
}

void ShoppingCart::printTotal()const {
    cout << customerName() << "'s Shopping Cart - " << date() << endl; 
    cout << "Number of Items: " << numItemsInCart() << endl; 
    cout << endl;

    if (_cartItems.empty()) {
        cout << "SHOPPING CART IS EMPTY" << endl; 
    }

    else {
        unsigned i = 0; 
        for (i = 0; i < _cartItems.size(); ++i) {
            cout << _cartItems.at(i).name() << " " << _cartItems.at(i).quantity() << " @ $" << _cartItems.at(i).price() << " = $" << _cartItems.at(i).price() * _cartItems.at(i).quantity() << endl; 
        }
    }
        cout << endl; 
        cout << "Total: $" << costOfCart() << endl; 
        cout << endl; 
}

void ShoppingCart::printDescriptions()const {
    unsigned i = 0; 

    cout << customerName() << "'s Shopping Cart - " << date() << endl; 
    cout << endl; 
    cout << "Item Descriptions" << endl; 

    for (i = 0; i < _cartItems.size(); ++i) {
        cout << _cartItems.at(i).name() << ": " << _cartItems.at(i).description() << endl; 
    }

    cout << endl; 
}
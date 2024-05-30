#ifndef CART_H
#define CART_H
#include <iostream>
#include <vector>
#include <string>
using namespace std; 

#include "ItemToPurchase.h"

class ShoppingCart {
    public:
        ShoppingCart(); //Default constructor (sets customer name to "none," current date to "Jnauary 1, 2016,")
        ShoppingCart(string name, string date); //Default constructor (sets customer name and date = name and date)
        string customerName()const; //Returns customer's name
        string date()const; //Returns current date
        void addItem(ItemToPurchase &item); //adds itmes to certItems vector
        void removeItem(string &itemName); //removes items from cartItems vector (if item cannot be found, output "Item not found in cart. Nothing removed." - use find fucntion for vectors)
        void modifyItem(ItemToPurchase &modify); //modifies an item's description, price, and/or quantity (if item name is found in cart vector, check for default values - if no default values, modify; if item cannot be found, output "Item not found in cart. Nothing modified. ")
        int numItemsInCart()const; //Returns quantity of all items in cart vector. (use for loop and access quantity from ItemToPurchase file)
        int costOfCart()const; //Returns total cost for whole cart (initialize sum and return sum)
        void printTotal()const; //Outputs the total of the objects in the cart vector (if cart is empty, output "SHOPPING CART IS EMPTY.")
        void printDescriptions()const; //Outputs the descripitons of each item in cart vector. 
    private: 
        string _customerName; //Customer name
        string _currentDate; //Current date
        vector<ItemToPurchase> _cartItems; //Stores the items the customer wants (use private member "name" in ItemtoPurchase class)
};
#endif
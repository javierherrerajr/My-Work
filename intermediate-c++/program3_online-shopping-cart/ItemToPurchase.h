#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <string>
using namespace std; 

class ItemToPurchase {
    public: 
        ItemToPurchase(); //Default constructor (name and description set to "none"; price and quantity set to 0)
        ItemToPurchase(string itemName, string itemDescription, int itemPrice, int itemQuantity); //Default constructor with parameters (set private class members equal to parameters)
        void setName(string itemName); //Sets Item name
        void setDescription(string itemDescription); //Sets Item description
        void setPrice(int itemPrice); //Sets Item price
        void setQuantity(int itemQuantity); //Sets Item quantity
        string name()const; //Returns the name of Item
        string description()const; //Returns the description of Item
        int price()const; //Returns price of Item
        int quantity()const; //Returns quantity of Item
        void printItemCost()const; //Outputs item cost
        void printItemDescription()const; // Outputs item descripiton
    private: 
        string _name; //Item name
        string _description; //Item description
        int _price; //Item price
        int _quantity; //Item quantity
};
#endif
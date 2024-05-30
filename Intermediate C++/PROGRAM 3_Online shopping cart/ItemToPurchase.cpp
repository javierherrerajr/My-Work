#include "ItemToPurchase.h"

ItemToPurchase::ItemToPurchase() {
    _name = "none";
    _description = "none"; 
    _price = 0; 
    _quantity = 0; 
}

ItemToPurchase::ItemToPurchase(string itemName, string itemDescription, int itemPrice, int ItemQuantity) {
    _name = itemName; 
    _description = itemDescription; 
    _price = itemPrice; 
    _quantity = ItemQuantity; 
}

void ItemToPurchase::setName(string itemName) {
    _name = itemName; 
}

void ItemToPurchase::setDescription(string itemDescription) {
    _description = itemDescription; 
}

void ItemToPurchase::setPrice(int itemPrice) {
    _price = itemPrice;
}

void ItemToPurchase::setQuantity(int itemQunatity) {
    _quantity = itemQunatity; 
}

string ItemToPurchase::name()const {
    return _name; 
}

string ItemToPurchase::description()const {
    return _description; 
}

int ItemToPurchase::price()const {
    return _price; 
}

int ItemToPurchase::quantity()const {
    return _quantity; 
}

void ItemToPurchase::printItemCost()const {
    cout << name() << " " << quantity() << " @ $" << price() << " = $" << _quantity * _price << endl; 
}

void ItemToPurchase::printItemDescription()const {
    cout << name() << ": " << description() << endl;
}
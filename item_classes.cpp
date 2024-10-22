#include "classes.h"

using namespace std;

// Item class

Item::Item(string name, enum categories category, int quantity, string from_date, string to_date) {
    this->name = name;
    this->category = category;
    this->quantity = quantity;
    this->from_date = from_date;
    this->to_date = to_date;
}

string Item::getName() {
    return this->name;
}

enum categories Item::getCategory() {
    return this->category;
}

int Item::getQuantity() {
    return this->quantity;
}

string Item::getFromDate() {
    return this->from_date;
}

string Item::getToDate() {
    return this->to_date;
}

void Item::updateQuantity(int quantity) {
    this->quantity = quantity;
}

void Item::updateFromDate(string from_date) {
    // TODO: Check if from_date is valid and before to_date
    this->from_date = from_date;
}

void Item::updateToDate(string to_date) {
    // TODO: Check if to_date is valid and after from_date
    this->to_date = to_date;
}

void Item::printItem() {
    cout << this->name << endl;
    cout << this->category;
    cout << "Quantity: " << this->quantity << endl;
    cout << "Availibility: " << this->from_date << " to " << "To: " << this->to_date << endl;
}

// Listing class

Listing::Listing(string name, enum categories category, int quantity, int price, string from_date, string to_date, enum conditions condition): 
    Item(name, category, quantity, from_date, to_date) {
        this->price = price;
        this->condition = condition;
    }

enum conditions Listing::getCondition() {
    return this->condition;
}

void Listing::updateCondition(enum conditions condition) {
    this->condition = condition;
}

void Listing::printItem() {
    cout << this->name << endl;
    cout << this->category;
    cout << "Condition: " << this->condition << endl;
    cout << "Quantity: " << this->quantity << endl;
    cout << "Availibility: " << this->from_date << " to " << "To: " << this->to_date << endl;
    cout << "Price: " << this->price << endl;
}

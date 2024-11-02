#include "classes.h"

using namespace std;

// This file contains both the item_class and the listing_class.

// Item class

Item::Item(string &name, enum categories category, int &quantity, string &from_date, string &to_date, User *owner) :
    name(name), category(category), quantity(quantity), from_date(from_date), to_date(to_date),
    owner(owner), borrower(nullptr) {}

string Item::getName() const {
    return this->name;
}

User* Item::getOwner() const {
    return this->owner;
}

User* Item::getBorrower() const {
    return this->borrower;
}

enum categories Item::getCategory() const {
    return this->category;
}

int Item::getQuantity() const {
    return this->quantity;
}

string Item::getFromDate() const {
    return this->from_date;
}

string Item::getToDate() const {
    return this->to_date;
}

void Item::updateQuantity(int new_quantity) {
    this->quantity = new_quantity;
}

void Item::updateFromDate(string new_from_date) {
    // TODO: Check if new_from_date is valid and before to_date
    this->from_date = new_from_date;
}

void Item::updateToDate(string new_to_date) {
    // TODO: Check if new_to_date is valid and after from_date
    this->to_date = new_to_date;
}

void Item::printItem() {
    cout << this->name << endl;
    cout << this->category;
    cout << "Quantity: " << this->quantity << endl;
    cout << "Availability: " << this->from_date << " to " << "To: " << this->to_date << endl;
}

// Listing class

Listing::Listing(string name, enum categories category, int quantity, int price,
        string from_date, string to_date, enum conditions condition):
        Item(name, category, quantity, from_date, to_date, nullptr),
    price(price), condition(condition), available(true) {}

enum conditions Listing::getCondition() {
    return this->condition;
}

void Listing::updateCondition(enum conditions new_condition) {
    this->condition = new_condition;
}

bool Listing::isAvailable() const {
    return this->available;
}

void Listing::bookItem() {
    available = true;
}

void Listing::freeItem() {
    available = false;
}

void Listing::printItem() {
    cout << this->name << endl;
    cout << this->category;
    cout << "Condition: " << this->condition << endl;
    cout << "Quantity: " << this->quantity << endl;
    cout << "Availibility: " << this->from_date << " to " << "To: " << this->to_date << endl;
    cout << "Price: " << this->price << endl;
}

#include "classes.h"

using namespace std;

// Item class

Item::Item(int itemID, std::string name, enum categories category, enum conditions condition, int quantity,
           std::string from_date, std::string to_date)
    : itemID(itemID), name(name), category(category), condition(condition), quantity(quantity),
      from_date(from_date), to_date(to_date) {}

int Item::getItemID() const {
    return this->itemID;
}

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

enum conditions Item::getCondition() const {
    return this->condition;
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

Listing::Listing(Item* item_listed, int item_price, enum conditions item_condition)
    : item_listed(item_listed), item_price(item_price), item_condition(item_condition) {}

bool Listing::isAvailable() const {
    return this->item_available;
}

Item* Listing::getItem() const {
    return this->item_listed;
}

void Listing::bookItem() {
    // Might need some more work
    this->item_available = false;
}

void Listing::freeItem() {
    // Might need some more work
    this->item_available = true;
}

void Listing::printListing() {
    this->item_listed->printItem();
    cout << "Price: " << this->item_price << endl;
    cout << "Condition: " << this->item_condition << endl;
}


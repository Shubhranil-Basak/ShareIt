#include "classes.h"

#include <string>
#include <regex>
#include <stdexcept>

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

// Dates should be of the form "DD-MM-YYYY"

// Function to validate the date format and extract day, month, year
bool isValidDate(const string& date, int &day, int &month, int &year) {
    // Check if date matches the "DD-MM-YYYY" format
    regex date_pattern(R"(^(\d{2})-(\d{2})-(\d{4})$)");
    smatch match;
    
    if (regex_match(date, match, date_pattern)) {
        day = stoi(match[1]);
        month = stoi(match[2]);
        year = stoi(match[3]);
        
        // Basic validation for day, month, and year ranges
        if (year >= 1900 && year <= 4000 && month >= 1 && month <= 12) { // hoping this is used till the year 4000 XD
            // Check day validity based on month
            if ((day >= 1 && day <= 31) && (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)) {
                return true;
            } else if ((day >= 1 && day <= 30) && (month == 4 || month == 6 || month == 9 || month == 11)) {
                return true;
            } else if ((day >= 1 && day <= 28) && (month == 2)) {
                return true;
            } else if (day == 29 && month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
                return true; // Leap year check
            }
        }
    }
    return false;
}

// Function to compare two dates (returns -1 if date1 < date2, 0 if equal, 1 if date1 > date2)
int compareDates(const string& date1, const string& date2) {
    int day1, month1, year1, day2, month2, year2;
    isValidDate(date1, day1, month1, year1);
    isValidDate(date2, day2, month2, year2);

    if (year1 != year2) return year1 < year2 ? -1 : 1;
    if (month1 != month2) return month1 < month2 ? -1 : 1;
    if (day1 != day2) return day1 < day2 ? -1 : 1;
    
    return 0;
}

void Item::updateFromDate(string new_from_date) {
    int day, month, year;
    
    if (!isValidDate(new_from_date, day, month, year)) {
        throw invalid_argument("Invalid from_date format. Please use 'DD-MM-YYYY'.");
    }
    
    // Check if the new_from_date is before the current to_date
    if (!to_date.empty() && compareDates(new_from_date, to_date) > 0) {
        throw invalid_argument("from_date cannot be after to_date.");
    }

    this->from_date = new_from_date;
}

void Item::updateToDate(string new_to_date) {
    int day, month, year;
    
    if (!isValidDate(new_to_date, day, month, year)) {
        throw invalid_argument("Invalid to_date format. Please use 'DD-MM-YYYY'.");
    }
    
    // Check if the new_to_date is after the current from_date
    if (!from_date.empty() && compareDates(new_to_date, from_date) < 0) {
        throw invalid_argument("to_date cannot be before from_date.");
    }

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

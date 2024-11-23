#include "classes.h"

using namespace std;

Notification::Notification(string from_username, string to_username, Listing *listing_referred,
                           enum notificationTypes type) :
        from_username(from_username), to_username(to_username), listing_referred(listing_referred),
        type(type) {}

string Notification::getToUsername() const {
    return to_username;
}

string Notification::getFromUsername() const {
    return from_username;
}

Listing *Notification::getListing() const {
    return listing_referred;
}

enum notificationTypes Notification::getType() const {
    return type;
}

void Notification::printNotification() {
    if (type == requestOwnerToBorrowItem) {
        cout << "User " << from_username << " has requested to borrow " << listing_referred->getName() << "." << endl;
    }
    else if (type == acceptBorrower) {
        cout << "User " << from_username << " has accepted your request to borrow " << listing_referred->getName() << "." << endl;
    }
    else if (type == rejectBorrower) {
        cout << "User " << from_username << " has rejected your request to borrow " << listing_referred->getName() << "." << endl;
    }
}

void Notification::printActions() const {
    if (type == requestOwnerToBorrowItem) {
        cout << "yes: accept the requester to borrow " << this->listing_referred->getName() << endl;
        cout << "no: reject the requester to borrow " << this->listing_referred->getName() << endl;
    }
    else if (type == acceptBorrower) {
        cout << "no actions available." << endl;
    }
    else if (type == rejectBorrower) {
        cout << "no actions available." << endl;
    }
}

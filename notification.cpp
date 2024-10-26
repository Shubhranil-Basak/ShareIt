#include "classes.h"

using namespace std;

Notification::Notification(std::string &from_username, std::string &to_username, Item *item_referred,
                           std::string &type) :
                           from_username(from_username), to_username(to_username), item_referred(item_referred),
                           type(type) {}

void Notification::printNotification() {
    if (type == "request") {
        cout << "User " << from_username << " has requested to borrow " << item_referred->getName() << "." << endl;
    }
    else if (type == "accept") {
        cout << "User " << from_username << " has accepted your request to borrow " << item_referred->getName() << "." << endl;
    }
    else if (type == "reject") {
        cout << "User " << from_username << " has rejected your request to borrow " << item_referred->getName() << "." << endl;
    }
}

#include "classes.h"

using namespace std;

User::User(string &username, string &password):
    username(username), password(password), coins(100) {}

bool User::authenticate(string &entered_username, string &entered_password) const {
    return this->username == entered_username && this->password == entered_password;
}

string User::getUsername() const {
    return this->username;
}

void User::listItem(Listing* listing) {
    this->listings.push_back(listing);
}

void User::removeListing(Listing* listing) {
    Listing* listing_to_del = nullptr;
    for (int i = 0; i < this->listings.size(); i++) {
        if (this->listings[i] == listing) {
            listing_to_del = this->listings[i];
            this->listings.erase(this->listings.begin() + i);
            break;
        }
    }
    delete listing_to_del;
    listing_to_del = nullptr;
}

void User::requestItem(Item* requested_item) {
    this->requested_items.push_back(requested_item);
}

void User::removeRequest(string &name) {
    Item* item_to_del = nullptr;
    for (int i = 0; i < this->requested_items.size(); i++) {
        if (this->requested_items[i]->getName() == name) {
            item_to_del = this->requested_items[i];
            this->requested_items.erase(this->requested_items.begin() + i);
            break;
        }
    }
    delete item_to_del;
    item_to_del = nullptr;
}

void User::borrowItem(Item *item) {
    borrowed_items.push_back(item);
}

void User::printNotifications() const {
    cout << "Notifications (Total: " << this->notifications.size() << ")" << endl;
    cout << separator << endl;
    for (Notification* notification: this->notifications) {
        notification->printNotification();
        cout << separator << endl;
    }
}

void User::acceptCoins(int coins_given) {
    this->coins += coins_given;
}

bool User::spendCoins(int coins_to_spend) {
    if (coins_to_spend > coins)
        return false;
    coins -= coins_to_spend;
    return true;
}

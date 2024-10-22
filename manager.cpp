#include "classes.h"

using namespace std;

Manager::Manager() {}

void Manager::registerUser(string username, string password) {
    User* new_user = new User(username, password);
    this->users.push_back(new_user);
}

bool Manager::login(string username, string password) {
    for (User* user: this->users) {
        if (user->authenticate(username, password)) {
            this->current_user = user;
            this->logged_in = true;
            cout << "Successfully logged in as " << username << "." << endl;
            return true;
        }
    }
    cout << "Invalid login credentials." << endl;
    return false;
}

void Manager::logout() {
    this->current_user = nullptr;
    this->logged_in = false;
    cout << "Logged out." << endl;
}

void Manager::printListings() {
    cout << "Listings (Total: " << this->listings.size() << ")" << endl;
    cout << separator << endl;
    for (Listing* listing: this->listings) {
        listing->printItem();
        cout << separator << endl;
    }
}

void Manager::printNotifications() {
    current_user->printNotifications();
}

void Manager::addListing(string name, string category, int quantity, int price, string from_date, string to_date, string condition) {
    // TODO: verify if the dates are valid, quantity and price are positive, and category and condition are valid
    
    Listing* new_listing = new Listing(name, stringToCategory(category), quantity, price, from_date, to_date, stringToCondition(condition));
    this->listings.push_back(new_listing);
    this->current_user->listItem(new_listing);
    cout << "Item " << name << " added listing." << endl;
}

void Manager::removeListing(string name) {
    Listing* listing_to_del = nullptr;
    for (int i = 0; i < this->listings.size(); i++) {
        if (this->listings[i]->getName() == name) {
            listing_to_del = this->listings[i];
            this->listings.erase(this->listings.begin() + i);
            break;
        }
    }
    if (listing_to_del == nullptr) {
        cout << "Item " << name << " not listed." << endl;
    } else {
        this->current_user->removeListing(listing_to_del);  // Takes care of deleting the listing object as well
        listing_to_del = nullptr;
        cout << "Item " << name << " removed listing." << endl;
    }
}

void Manager::addRequest(string name, string category, int quantity, string from_date, string to_date) {
    // TODO: verify if the dates are valid, quantity are positive, and category and condition are valid
    
    Item* new_request = new Item(name, stringToCategory(category), quantity, from_date, to_date);
    this->current_user->requestItem(new_request);
    // TODO: search for a listing that matches the request and notify the owner
}

void Manager::removeRequest(string name) {
    this->current_user->removeRequest(name);
}

vector<Listing*> Manager::searchListings(Item* item) {
    vector<Listing*> search_results;
    for (Listing* listing: this->listings) {
        if (listing->getName() == item->getName() && listing->getCategory() == item->getCategory() && listing->getQuantity() >= item->getQuantity()) {
            // TODO: check if the dates overlap
            search_results.push_back(listing);
        }
    }
    return search_results;
}


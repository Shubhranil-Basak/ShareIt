#include "classes.h"

using namespace std;

Manager::Manager() {
    this->logged_in = false;
    this->num_items = 0;
}

void Manager::registerUser(string username, string password) {
    for (User* existing_user: users) {
        if (existing_user->getUsername() == username) {
            cout << "user with username '" << username << "' already exists. Try another username." << endl;
            break;
        }
    }
    User* new_user = new User(username, password);
    this->users.push_back(new_user);
    cout << "New user '" << username << "' is created! Login to access account.";
}

bool Manager::login(string &username, string &password) {
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

void Manager::printListings() const {
    cout << "Listings (Total: " << this->listings.size() << ")" << endl;
    cout << separator << endl;
    for (Listing* listing: this->listings) {
        if (listing->isAvailable()) {
            listing->printListing();
            cout << separator << endl;
        }
    }
}

void Manager::printNotifications() const {
    current_user->printNotifications();
}

void Manager::addListing(string name, string category, int quantity, int price,
                         string from_date, string to_date, string condition) {
    // TODO: verify if the dates are valid, quantity and price are positive, and category and condition are valid
    Item* new_item = new Item(this->num_items, name, stringToCategory(category),
                              stringToCondition(condition), quantity, from_date, to_date);
    this->num_items++;
    Listing* new_listing = new Listing(new_item, price, stringToCondition(condition));
    this->listings.push_back(new_listing);
    this->current_user->listItem(new_listing);
    cout << "Item " << name << " added listing." << endl;
}

void Manager::removeListing(string &name) {
    Listing* listing_to_del = nullptr;
    for (int i = 0; i < this->listings.size(); i++) {
        if (this->listings[i]->getItem()->getName() == name) {
            listing_to_del = this->listings[i];
            this->listings.erase(this->listings.begin() + i);
            break;
        }
    }
    if (listing_to_del == nullptr) {
        cout << "Item " << name << " has not been listed." << endl;
    } else {
        this->current_user->removeListing(listing_to_del);  // Takes care of deleting the listing object as well
        listing_to_del = nullptr;
        cout << "Item " << name << " has been removed." << endl;
    }
}

void
Manager::addRequest(string name, string category, string condition, int quantity, string from_date, string to_date) {
    // TODO: verify if the dates are valid, quantity are positive, and category and condition are valid
    
    Item* new_request = new Item(-1, name, stringToCategory(category), stringToCondition(condition),
                                 quantity, from_date, to_date);
    this->current_user->requestItem(new_request);
    // TODO: search for a listing that matches the request and notify the owner
}

void Manager::removeRequest(string name) {
    this->current_user->removeRequest(name);
}

vector<Listing*> Manager::searchListings(Item* item) {
    vector<Listing*> search_results;
    for (Listing* listing: this->listings) {
        if (listing->getItem()->getName() == item->getName() && listing->getItem()->getCategory() == item->getCategory() &&
        listing->getItem()->getQuantity() >= item->getQuantity()) {
            // TODO: check if the dates overlap
            search_results.push_back(listing);
        }
    }
    return search_results;
}

void Manager::borrowItem(Listing *item_to_borrow) {
    User* item_owner = item_to_borrow->getItem()->getOwner();
    current_user->borrowItem(reinterpret_cast<Item *>(item_to_borrow));
    item_to_borrow->bookItem();
}

void Manager::shareCoins(string &receiving_username, int coins_to_share) {
    // Assumed that a valid coins_to_share amount is given a.k.a 0 < coins_to_share <= user->coins
    for (User* user: users) {
        if (user->getUsername() == receiving_username) {
            current_user->spendCoins(coins_to_share);
            user->acceptCoins(coins_to_share);
            break;
        }
    }
    cout << "Transaction failed: user '" << receiving_username << "' doesn't exist." << endl;
}

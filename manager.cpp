#include "classes.h"

using namespace std;

void Manager::registerUser(string username, string password) {
    for (User* existing_user: users) {
        if (existing_user->getUsername() == username) {
            cout << "user with username '" << username << "' already exists. Try another username." << endl;
            break;
        }
    }
    User* new_user = new User(username, password);
    this->users.push_back(new_user);
    cout << "New user '" << username << "' is created! ";
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
            listing->printItem();
            cout << separator << endl;
        }
    }
}

void Manager::printNotifications() const {
    current_user->printNotifications();
}

void Manager::printNotificationActions(int notification_number) const {
    current_user->getNotification(notification_number - 1)->printActions();
}

void Manager::addListing(string name, string category, int quantity, int price,
                         string from_date, string to_date, string condition) {
    conditions condition_enum = stringToCondition(condition);
    categories category_enum = stringToCategory(category);
    if (condition_enum == INVALID) {
        cout << "Invalid condition. Please use 'excellent', 'good', 'fair', or 'poor'." << endl;
        return;
    }
    if (!areValidateDates(from_date, to_date)) {
        return;
    }
    if (quantity <= 0) {
        cout << "Quantity must be positive." << endl;
        return;
    }
    if (price <= 0) {
        cout << "Price must be positive." << endl;
        return;
    }

    Item* new_item = new Item(name, category_enum, quantity, from_date, to_date, current_user);
    Listing* new_listing = new Listing(new_item, price, condition_enum);
    this->listings.push_back(new_listing);
    this->current_user->listItem(new_listing);
    cout << "Item " << name << " added listing." << endl;

    notifyRequestersAboutNewListing(new_listing);
}

void Manager::removeListing(string &name) {
    Listing* listing_to_del = nullptr;
    for (int i = 0; i < this->listings.size(); i++) {
        if (this->listings[i]->getName() == name) {
            listing_to_del = this->listings[i];
            if (!listing_to_del->isAvailable()) {
                cout << "Item " << name << " is currently borrowed. Cannot remove listing." << endl;
                return;
            }
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
    categories category_enum = stringToCategory(category);
    if (!areValidateDates(from_date, to_date)) {
        return;
    }
    if (quantity <= 0) {
        cout << "Quantity must be positive." << endl;
        return;
    }

    Item* new_request = new Item(name, category_enum, quantity, from_date, to_date,
                                 nullptr, current_user);
    this->current_user->requestItem(new_request);
    requests.push_back(new_request);

    notifyRequesterOfNewRequest(new_request);
}

void Manager::removeRequest(string name) {
    this->current_user->removeRequest(name);
}

void Manager::printRequests() const {
    cout << "Requests (Total: " << this->current_user->getRequestedItems().size() << ")" << endl;
    cout << separator << endl;
    for (Item* item: this->current_user->getRequestedItems()) {
        item->printItem();
        cout << separator << endl;
    }
}

void Manager::printBorrowedItems() const {
    current_user->printBorrowedItems();
}

vector<Listing*> Manager::searchListingsForRequest(Item* request) {
    vector<Listing*> search_results;
    for (Listing* listing: this->listings) {
        if (listing->isAvailable() &&     // Item is available
            listing->getName() == request->getName() &&     // Item name matches
            listing->getCategory() == request->getCategory() &&     // Item category matches
            listing->getQuantity() >= request->getQuantity() &&     // Item quantity is enough
            compareDates(listing->getItem()->getFromDate(), request->getFromDate()) <= 0 &&    // From date is before or equal
            compareDates(listing->getItem()->getToDate(), request->getToDate()) >= 0    // To date is after or equal
            )
        {
            search_results.push_back(listing);
        }
    }
    return search_results;
}

vector<Item*> Manager::searchRequestsForListing(Listing *listing) {
    vector<Item*> search_results;
    for (Item *request: this->requests) {
        if (listing->getName() == request->getName() &&     // Item name matches
            listing->getCategory() == request->getCategory() &&     // Item category matches
            listing->getQuantity() >= request->getQuantity() &&     // Item quantity is enough
            compareDates(listing->getItem()->getFromDate(), request->getFromDate()) <= 0 &&    // From date is before or equal
            compareDates(listing->getItem()->getToDate(), request->getToDate()) >= 0    // To date is after or equal
            )
        {
            search_results.push_back(request);
        }
    }
    return search_results;
}

// when a new listing is made, we get a list of requests that match the listing and notify the requesters
// when a new request is made, we make a list of listings that match the request and notify the requesters
// once requester accepts the request, we notify the owner of the listing
// once the owner of the listing accepts, requester borrows the item
// once the requester returns the item, the owner gets the item back

bool Manager::notifyUser(Notification *notificationToSend) {
    for (User* user: users) {
        if (user->getUsername() == notificationToSend->getToUsername()) {
            user->addNotification(notificationToSend);
            return true;
        }
    }
    return false;
}

void Manager::notifyRequestersAboutNewListing(Listing *new_listing) {
    vector<Item*> search_results = searchRequestsForListing(new_listing);
    for (Item *request: search_results) {
        Notification *notification = new Notification(new_listing->getOwner()->getUsername(), request->getOwner()->getUsername(),
                                                 new_listing, requestOwnerToBorrowItem);
        notifyUser(notification);
    }
}

void Manager::notifyRequesterOfNewRequest(Item *new_request) {
    vector<Listing*> search_results = searchListingsForRequest(new_request);
    cout << "Found " << search_results.size() << " listings that match the request." << endl;
    string from_username = new_request->getBorrower()->getUsername();
    for (Listing *listing: search_results) {
        cout << "Notifying " << listing->getOwner()->getUsername() << " about the request." << endl;
        string owner_username = listing->getOwner()->getUsername();
        Notification *notification = new Notification(from_username, owner_username, listing,
                                                      requestOwnerToBorrowItem);
        notifyUser(notification);
    }
}

void Manager::replyToNotification(int notification_number, string &action) {
    Notification *notification = current_user->getNotification(notification_number - 1);
    if (notification->getType() != requestOwnerToBorrowItem) {
        return;
    }
    // notification is a request from borrower to owner to borrow an item
    if (action == "yes") {
        // accept the requester
        Listing *listing = notification->getListing();
        User* borrower;
        for (User* user: users) {
            if (user->getUsername() == notification->getFromUsername()) {
                borrower = user;
                break;
            }
        }
        if (listing->isAvailable()) {
            borrowItem(listing, borrower);
            Notification *reply_notification = new Notification(current_user->getUsername(), notification->getFromUsername(),listing,acceptBorrower);
            notifyUser(reply_notification);
        } else {
            cout << "Item is no longer available." << endl;
        }
    } else if (action == "no") {
        // reject the requester
        Notification *reply_notification = new Notification(current_user->getUsername(), notification->getFromUsername(),
                                                            notification->getListing(), rejectBorrower);
        notifyUser(reply_notification);
    }
}


void Manager::borrowItem(Listing *item_to_borrow, User *borrower) {
//    User* item_owner = item_to_borrow->getOwner();
    item_to_borrow->bookItem();
    borrower->borrowItem(item_to_borrow->getItem());
    borrower->spendCoins(item_to_borrow->getPrice());
    current_user->acceptCoins(item_to_borrow->getPrice());
    cout << "Item borrowed successfully." << endl;
}

void Manager::shareCoins(string &receiving_username, int coins_to_share) {
    // Assumed that a valid coins_to_share amount is given a.k.a 0 < coins_to_share <= user->coins
    bool shared = false;
    for (User* user: users) {
        if (user->getUsername() == receiving_username) {
            current_user->spendCoins(coins_to_share);
            user->acceptCoins(coins_to_share);
            shared = true;
            cout << "Coins shared successfully." << endl;
            break;
        }
    }
    if (!shared)
        cout << "Transaction failed: user '" << receiving_username << "' doesn't exist." << endl;
}

int Manager::getBalance() const {
    return current_user->getCoinBalance();
}

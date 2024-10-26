#include <bits/stdc++.h>

using namespace std;

const string separator = "------------------------------------------------------------";
enum conditions {excellent, good, fair, poor};
enum categories {electronics, furniture, clothing, books, sports, other};

enum categories stringToCategory(string &category);
string categoryToString(enum categories category);
enum conditions stringToCondition(string &condition);
string conditionToString(enum conditions condition);

class User;

class Item {
private:
    int itemID;
    string name;
    User* owner;
    User* borrower;
    enum categories category;
    enum conditions condition;
    int quantity;
    string from_date;
    string to_date;

public:
    Item(int itemID, string name, enum categories category, enum conditions condition, int quantity,
            string from_date, string to_date);
    int getItemID() const;
    string getName() const;
    User* getOwner() const;
    User* getBorrower() const;
    enum categories getCategory() const;
    enum conditions getCondition() const;
    int getQuantity() const;
    string getFromDate() const;
    string getToDate() const;

    void updateQuantity(int new_quantity);
    void updateFromDate(string new_from_date);
    void updateToDate(string new_to_date);

    void printItem();
};

class Listing {
private:
    Item* item_listed;
    bool item_available;
    int item_price;
    enum conditions item_condition;

public:
    Listing(Item* item_listed, int item_price, enum conditions item_condition);
    bool isAvailable() const;
    Item* getItem() const;
    void bookItem();
    void freeItem();
    void printListing();
};


class Notification {
private:
    Notification(string from_username, string to_username, Item *item_referred, string type);

    string from_username;
    string to_username;
    Item* item_referred;
    string type;

public:
    Notification(string &from_username, string &to_username, Item* item_referred, string &type);
    void printNotification();
};

class User {
private:
    string username;
    string password;
    int coins;
    vector<Item*> requested_items;
    vector<Listing*> listings;
    vector<Item*> currently_borrowed_items;
    vector<Notification*> notifications;

public:
    User(string &username, string &password);  // Create a user with 100 coins

    bool authenticate(string &entered_username, string &entered_password) const;
        // returns true if entered_username and entered_password are correct
    string getUsername() const;

    void listItem(Listing* listing);
    void removeListing(Listing* listing);
    
    void requestItem(Item* requested_item);
    void removeRequest(string &name);
    void borrowItem(Item* item);
    void returnItem(Item* item);

    void printNotifications() const;

    void acceptCoins(int coins_given);
    bool spendCoins(int coins_to_spend);
};

class Manager {
private:
    vector<User*> users;
    User* current_user;
    vector<Listing*> listings;
    int num_items;

public:
    bool logged_in;  // True if a user is logged in

    Manager();

    void registerUser(string username, string password);  // Adds a new user to the users vector
    bool login(string &username, string &password);  // updates current_user if valid username and password
    void logout();  // sets current_user to NULL

    void printListings() const;
    void printNotifications() const;

    void addListing(string name, string category, int quantity, int price,
                    string from_date, string to_date, string condition);
    void removeListing(string &name);
    void addRequest(string name, string category, string condition, int quantity, string from_date, string to_date);
        // Adds a new request to the current_user's requested_items vector. It also searches through the listings vector of all users to find the item
    void removeRequest(string name);

    vector<Listing*> searchListings(Item* item);  // Returns a vector of items that match the search criteria
    vector<Listing*> filterListings(string condition, pair<int, int> price_range, string category);
        // Returns a vector of items that match the filter criteria
    void borrowItem(Listing *item_to_borrow);
        // Adds the item to the current_user's borrowed_items vector and removes it from the owner's listings vector

    void shareCoins(string &receiving_username, int coins_to_share);
        // Transfers coins_to_share from the current_user to the receiving_user
};

// TODO: Make a itemID attribute
// TODO: requestCoins method
// TODO: Make a show requests method
// TODO: Make a search listing/item by itemID (useful when notification arrives)
// TODO: Negotiation system, maybe later on

#include <bits/stdc++.h>

using namespace std;

const string separator = "------------------------------------------------------------";
enum conditions {excellent, good, fair, poor};
enum categories {electronics, furniture, clothing, books, sports, other};

enum categories stringToCategory(string &category);
string categoryToString(enum categories category);
enum conditions stringToCondition(string &condition);
string conditionToString(enum conditions condition);

class Notification {
private:
    string from_username;
    string to_username;
    string message;
    string date;
    string time;
    bool isRead;

public:
    Notification(string &from_username, string &to_username, string &message, string &date, string &time);
    void markAsRead();
    string getFromUsername() const;
    string getToUsername() const;
    string getMessage() const;
    string getDate() const;
    string getTime() const;
    bool getIsRead() const;
    // void offerAcceptance();
    void printNotification();
};

class User;

class Item {
protected:
    string name;
    User* owner;
    User* borrower;
    // bool fulfilled;
    enum categories category;
    int quantity;
    string from_date; // date should be of the form "DD-MM-YYYY"
    string to_date;

public:
    Item(string &name, enum categories category, int &quantity, string &from_date, string &to_date, User *owner);
    string getName() const;
    User* getOwner() const;
    User* getBorrower() const;
    enum categories getCategory() const;
    int getQuantity() const;
    string getFromDate() const;
    string getToDate() const;

    void updateQuantity(int new_quantity);
    void updateFromDate(string new_from_date);
    void updateToDate(string new_to_date);

    virtual void printItem();
};

class Listing: public Item {
private:
    bool available;
    int price;
    enum conditions condition;

public:
    Listing(string name, enum categories category, int quantity, int price,
            string from_date, string to_date, enum conditions condition);
    enum conditions getCondition();
    void updateCondition(enum conditions new_condition);
    bool isAvailable() const;
    void bookItem();
    void freeItem();
    void printItem() override;
};

// class Request: public Item{
// public:
//     void printItem();
// };


class User {
private:
    string username;
    string password;
    int coins;
    vector<Item*> requested_items;
    vector<Listing*> listings;
    vector<Item*> borrowed_items;
    vector<Notification*> notifications;

public:
    User(string &username, string &password);  // Create a user with 100 coins

    bool authenticate(string &entered_username, string &entered_password) const  // returns true if entered_username and entered_password are correct
    {
        return username == entered_username && password == entered_password;
    }
    string getUsername() const;

    void listItem(Listing* listing);
    void removeListing(Listing* listing);
    
    void requestItem(Item* requested_item);
    void removeRequest(string &name);
    void borrowItem(Item* item);

    void printNotifications() const;

    void acceptCoins(int coins_given);
    bool spendCoins(int coins_to_spend);
};

class Manager {
private:
    vector<User*> users;
    User* current_user{};
    vector<Listing*> listings;

public:
    Manager() = default;

    bool logged_in = false;  // True if a user is logged in

    void registerUser(string username, string password)  // Adds a new user to the users vector
    {
        users.push_back(new User(username, password));
    }

    bool login(string &username, string &password)  // updates current_user if valid username and password
    {
        for (auto &user : users) {
            if (user->authenticate(username, password)) {
                current_user = user;
                logged_in = true;
                return true;
            }
        }
        return false;
    }

    void logout()  // sets current_user to NULL
    {
        current_user = NULL;
        logged_in = false;
    }

    void printListings() const;
    void printNotifications() const;

    void addListing(string name, string category, int quantity, int price,
                    string from_date, string to_date, string condition);
    void removeListing(string &name);
    void addRequest(string name, string category, int quantity, string from_date, string to_date);
        // Adds a new request to the current_user's requested_items vector. It also searches through the listings vector of all users to find the item
    void removeRequest(string name);

    vector<Listing*> searchListings(Item* item);  // Returns a vector of items that match the search criteria
    void borrowItem(Listing *item_to_borrow);  // Adds the item to the current_user's borrowed_items vector and removes it from the owner's listings vector

    void shareCoins(string &receiving_username, int coins_to_share);  // Transfers coins_to_share from the current_user to the receiving_user
};

// TODO: Make a itemID attribute
// TODO: requestCoins method
// TODO: Make a show requests method
// TODO: Make a search listing/item by itemID (useful when notification arrives)
// TODO: Negotiation system, maybe later on

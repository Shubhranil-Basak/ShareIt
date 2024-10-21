#include <bits/stdc++.h>

using namespace std;

enum conditions {excellent, good, fair, poor};
enum categories {electronics, furniture, clothing, books, sports, other};

class Notification {
private:
    string from_username;
    string to_username;
    string message;
    string date;
    string time;
    bool isRead;

public:
    Notification(string from_username, string to_username, string message, string date, string time);
    void markAsRead();
    string getFromUsername();
    string getToUsername();
    string getMessage();
    string getDate();
    string getTime();
    bool getIsRead();

    void printNotification();
};

class Item {
protected:
    string name;
    enum categories category;
    int quantity;
    string from_date;
    string to_date;
    enum conditions condition;

public:
    Item(string name, string category, int quantity, string from_date, string to_date, enum conditions condition);

    string getName();
    enum categories getCategory();
    int getQuantity();
    string getFromDate();
    string getToDate();
    enum conditions getCondition();

    void updateQuantity(int quantity);
    void updateFromDate(string from_date);
    void updateToDate(string to_date);
    void updateCondition(enum conditions condition);

    virtual void printItem();
};

class Listing: public Item {
private:
    float price;

public:
    void printItem();
};

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
    User(string username, string password);  // Create a user with 100 coins

    bool authenticate(string username, string password);  // returns true if username and password are correct

    void listItem(string name, enum categories category, int quantity, float price, string from_date, string to_date, enum conditions condition);
    void removeListing(string name);
    
    void requestItem(string name, enum categories category, int quantity, string from_date, string to_date, enum conditions condition);
    void removeRequest(string name);
};

class Manager {
private:
    vector<User*> users;
    User* current_user;

public:
    void registerUser(string username, string password);  // Adds a new user to the users vector
    void login(string username, string password);  // updates current_user if valid username and password
    void logout();  // sets current_user to NULL

    void printListings();
    void printNotifications();

    void addListing(string name, enum categories category, int quantity, float price, string from_date, string to_date, enum conditions condition);
    void removeListing(string name);
    void addRequest(string name, enum categories category, int quantity, string from_date, string to_date, enum conditions condition);
        // Adds a new request to the current_user's requested_items vector. It also searches through the listings vector of all users to find the item
    void removeRequest(string name);

    vector<Item*> searchItems(Item* item);  // Returns a vector of items that match the search criteria
    void borrowItem(Item* item);  // Adds the item to the current_user's borrowed_items vector and removes it from the owner's listings vector

    void shareCoins(User* recieving_user, int coins);  // Transfers coins from the current_user to the recieving_user
};


// TODO: Negotiation system

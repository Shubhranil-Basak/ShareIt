#include <bits/stdc++.h>

using namespace std;

const string separator = "------------------------------------------------------------";
enum conditions {excellent, good, fair, poor};
enum categories {electronics, furniture, clothing, books, sports, other};

enum categories stringToCategory(string category);
string categoryToString(enum categories category);
enum conditions stringToCondition(string condition);
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
    Notification(string from_username, string to_username, string message, string date, string time);
    void markAsRead();
    string getFromUsername();
    string getToUsername();
    string getMessage();
    string getDate();
    string getTime();
    bool getIsRead();
    // void offerAcceptance();
    void printNotification();
};

class User;

class Item {
protected:
    string name;
    User* owner;
    // User* borrower;
    // bool fulfilled;
    enum categories category;
    int quantity;
    string from_date;
    string to_date;

public:
    Item(string name, enum categories category, int quantity, string from_date, string to_date);
    // string ownerDetails();
    // string borrowerDetails();
    string getName();
    enum categories getCategory();
    int getQuantity();
    string getFromDate();
    string getToDate();

    void updateQuantity(int quantity);
    void updateFromDate(string from_date);
    void updateToDate(string to_date);

    virtual void printItem();
};

class Listing: public Item {
private:
    int price;
    enum conditions condition;

public:
    Listing(string name, enum categories category, int quantity, int price, string from_date, string to_date, enum conditions condition);
    enum conditions getCondition();
    void updateCondition(enum conditions condition);
    void printItem();
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
    User(string username, string password);  // Create a user with 100 coins

    bool authenticate(string username, string password);  // returns true if username and password are correct

    void listItem(Listing* listing);
    void removeListing(Listing* listing);
    
    void requestItem(Item* requested_item);
    void removeRequest(string name);

    void printNotifications();
};

class Manager {
private:
    vector<User*> users;
    User* current_user;
    vector<Listing*> listings;

public:
    bool logged_in;  // True if a user is logged in

    void registerUser(string username, string password);  // Adds a new user to the users vector
    bool login(string username, string password);  // updates current_user if valid username and password
    void logout();  // sets current_user to NULL

    void printListings();
    void printNotifications();

    void addListing(string name, string category, int quantity, int price, string from_date, string to_date, string condition);
    void removeListing(string name);
    void addRequest(string name, string category, int quantity, string from_date, string to_date);
        // Adds a new request to the current_user's requested_items vector. It also searches through the listings vector of all users to find the item
    void removeRequest(string name);

    vector<Listing*> searchListings(Item* item);  // Returns a vector of items that match the search criteria
    void borrowItem(Item* item);  // Adds the item to the current_user's borrowed_items vector and removes it from the owner's listings vector

    void shareCoins(User* recieving_user, int coins);  // Transfers coins from the current_user to the recieving_user
};


// TODO: Negotiation system, maybe later on

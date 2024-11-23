#include "classes.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    Manager manager;
    string command;
    string username, password, action, name, category, condition, from_date, to_date;
    int quantity, notification_number;
    while (true) {
        cout << ">> ";
        cin >> command;
        if (command == "help") {
            // print all available commands
            cout << "Commands available:" << endl;
            if (!manager.logged_in) {
                cout << "login -> To login into your account" << endl;
                cout << "logout -> To log out of your account" << endl;
                cout << "register -> To create a new account" << endl;
            }
            else {
                cout << "print listings -> To print all the available listings currently" << endl;
                cout << "print notifications -> To print all available notifications" << endl;
                cout << "add listing -> To add a new listing to the platform" << endl;
                cout << "remove listing -> To remove an existing listing from the platform" << endl;
                cout << "request item -> To send a request for an item" << endl;
                cout << "show requests -> To show all current requests" << endl;
                cout << "remove request -> To remove a request from the platform" << endl;
                cout << "send coins -> To send coins to a friend" << endl;
                cout << "request coins -> To request coins from a friend" << endl;
            }
        }
        if (command == "exit") {
            break;
        }
        if (!manager.logged_in) {
            if (command == "login") {
                // login logic
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                manager.login(username, password);
            }
            else if (command == "logout")  {
                // logout logic
                manager.logout();
            }
            else if (command == "register") {
                // register logic
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                manager.registerUser(username, password);
                manager.login(username, password);
            }
            else {
                cout << "Invalid command!" << endl;
            }
        }
        else {
            if (command == "print listings") {
                // print all listings
                manager.printListings();
            }
            else if (command == "print notifications") {
                // print all notifications
                manager.printNotifications();
                cout << "\nDo you want to take any actions on the notifications? (yes/no): ";
                cin >> action;
                if (action == "no") {
                    continue;
                }
                cout << "Enter the notification number you want to take action on: ";
                cin >> notification_number;
                manager.printNotificationActions(notification_number);
                cout << "Enter the action you want to take: ";
                cin >> action;
                manager.replyToNotification(notification_number, action);
            }
            else if (command == "add listing") {
                // add a new listing
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter category: ";
                cin >> category;
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter from date: ";
                cin >> from_date;
                cout << "Enter to date: ";
                cin >> to_date;
                cout << "Enter condition: ";
                cin >> condition;
                manager.addListing(name, category, quantity, 0, from_date, to_date, condition);
            }
            else if (command == "remove listing") {
                // remove a listing
                cout << "Enter item name: ";
                cin >> name;
                manager.removeListing(name);
            }
            else if (command == "request item") {
                // request an item
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter category: ";
                cin >> category;
                cout << "Enter quantity: ";
                cin >> quantity;
                cout << "Enter from date: ";
                cin >> from_date;
                cout << "Enter to date: ";
                cin >> to_date;
                manager.addRequest(name, category, quantity, from_date, to_date);
            }
            else if (command == "show requests") {
                // show all requests
                manager.printRequests();
            }
            else if (command == "remove request") {
                // remove a request
                cout << "Enter item name: ";
                cin >> name;
                manager.removeRequest(name);
            }
            else if (command == "send coins") {
                // send coins to a friend
                cout << "Enter receiving username: ";
                cin >> username;
                cout << "Enter coins to send: ";
                cin >> quantity;
                manager.shareCoins(username, quantity);
            }
            else {
                cout << "Invalid command!" << endl;
            }
        }
    }

    return 0;
}
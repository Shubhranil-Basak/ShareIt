#include "classes.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    Manager manager;
    string command;
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
        if (!manager.logged_in) {
            if (command == "login") {
                // login logic
            }
            else if (command == "logout")  {
                // logout logic
            }
            else if (command == "register") {
                // register logic
            }
            else {
                cout << "Invalid command!" << endl;
            }
        }
        else {
            if (command == "print listings") {
                // print all listings
            }
            else if (command == "print notifications") {
                // print all notifications
            }
            else if (command == "add listing") {
                // add a new listing
            }
            else if (command == "remove listing") {
                // remove a listing
            }
            else if (command == "request item") {
                // request an item
            }
            else if (command == "show requests") {
                // show all requests
            }
            else if (command == "remove request") {
                // remove a request
            }
            else if (command == "send coins") {
                // send coins to a friend
            }
            else if (command == "request coins") {
                // request coins from a friend
            }
            else {
                cout << "Invalid command!" << endl;
            }
        }
    }

    return 0;
}
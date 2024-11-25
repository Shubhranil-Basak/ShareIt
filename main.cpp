#include "classes.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    Manager manager;
    string command;
    string username, password, action, name, category, condition, from_date, to_date;
    int quantity, price, notification_number, num_notifications;

    cout << "\nWelcome to the Inventory Management System!\n";
    cout << "Type 'help' to see available commands or 'exit' to quit.\n";
    cout << "-------------------------------------------------------\n";

    while (true) {
        cout << "\n>> ";
        getline(cin, command);

        if (command == "help") {
            // Define the commands and descriptions
            vector<pair<string, string>> commands;

            if (!manager.logged_in) {
                commands = {
                        {"login", "Log into your account"},
                        {"logout", "Log out of your account"},
                        {"register", "Create a new account"}
                };
            } else {
                commands = {
                        {"print listings", "View all available listings"},
                        {"print notifications", "View your notifications"},
                        {"add listing", "Add a new listing"},
                        {"remove listing", "Remove an existing listing"},
                        {"request item", "Request an item"},
                        {"show requests", "View all current requests"},
                        {"remove request", "Remove a request"},
                        {"show borrowed items", "View all borrowed items"},
                        {"get balance", "Get your current balance"},
                        {"send coins", "Send coins to another user"}
                };
            }

            // Print the table header
            cout << "\n------------------------- Commands Available -------------------------\n";
            cout << left << setw(20) << "Command" << setw(50) << "Description" << endl;
            cout << string(70, '-') << endl;

            // Print the table rows
            for (const auto& [cmd, desc] : commands) {
                cout << left << setw(20) << cmd << setw(50) << desc << endl;
            }

            cout << string(70, '-') << endl;
        } else if (command == "exit") {
            cout << "Exiting the program. Goodbye!\n";
            break;
        } else if (!manager.logged_in) {
            if (command == "login") {
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                manager.login(username, password);
            } else if (command == "logout") {
                cout << "You are not logged in.\n";
            } else if (command == "register") {
                cout << "Enter username: ";
                getline(cin, username);
                cout << "Enter password: ";
                getline(cin, password);
                manager.registerUser(username, password);
            } else {
                cout << "Invalid command! Type 'help' to see available commands.\n";
            }
        } else {
            if (command == "logout") {
                manager.logout();
            } else if (command == "print listings") {
                manager.printListings();
            } else if (command == "print notifications") {
                manager.printNotifications();
                num_notifications = manager.getNumberOfNotifications();
                if (num_notifications == 0)
                    continue;

                cout << "\nWould you like to take any action on notifications? (yes/no): ";
                getline(cin, action);
                if (action == "no") continue;

                cout << "Enter the notification number to act on: ";
                getline(cin, command);  // Using command temporarily for input
                notification_number = stoi(command);
                if (notification_number < 1 || notification_number > num_notifications) {
                    cout << "Invalid notification number.\n";
                    continue;
                }
                manager.printNotificationActions(notification_number);

                cout << "Enter the action to take: ";
                getline(cin, action);
                manager.replyToNotification(notification_number, action);
            } else if (command == "add listing") {
                cout << "Enter item name: ";
                getline(cin, name);
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter quantity: ";
                getline(cin, command); // Using command temporarily for input
                quantity = stoi(command);
                cout << "Enter from date (DD-MM-YYYY): ";
                getline(cin, from_date);
                cout << "Enter to date (DD-MM-YYYY): ";
                getline(cin, to_date);
                cout << "Enter condition: ";
                getline(cin, condition);
                cout << "Enter price: ";
                getline(cin, command); // Using command temporarily for input
                price = stoi(command);
                manager.addListing(name, category, quantity, price, from_date, to_date, condition);
            } else if (command == "remove listing") {
                cout << "Enter item name to remove: ";
                getline(cin, name);
                manager.removeListing(name);
            } else if (command == "request item") {
                cout << "Enter item name: ";
                getline(cin, name);
                cout << "Enter category: ";
                getline(cin, category);
                cout << "Enter quantity: ";
                getline(cin, command); // Using command temporarily for input
                quantity = stoi(command);
                cout << "Enter from date (DD-MM-YYYY): ";
                getline(cin, from_date);
                cout << "Enter to date (DD-MM-YYYY): ";
                getline(cin, to_date);
                manager.addRequest(name, category, quantity, from_date, to_date);
            } else if (command == "show requests") {
                manager.printRequests();
            } else if (command == "show borrowed items") {
                manager.printBorrowedItems();
            } else if (command == "remove request") {
                cout << "Enter item name to remove request for: ";
                getline(cin, name);
                manager.removeRequest(name);
            } else if (command == "send coins") {
                cout << "Enter recipient's username: ";
                getline(cin, username);
                cout << "Enter number of coins to send: ";
                getline(cin, command); // Using command temporarily for input
                quantity = stoi(command);
                manager.shareCoins(username, quantity);
            } else if (command == "get balance") {
                cout << "Your current balance is: " << manager.getBalance() << endl;
            } else {
                cout << "Invalid command! Type 'help' to see available commands.\n";
            }
        }
    }

    return 0;
}

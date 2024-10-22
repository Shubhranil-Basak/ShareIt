#include "classes.h"

using namespace std;

Notification::Notification(string from_username, string to_username, string message, string date, string time) {
    this->from_username = from_username;
    this->to_username = to_username;
    this->message = message;
    this->date = date;
    this->time = time;
    this->isRead = false;
}

void Notification::markAsRead() {
    this->isRead = true;
}

string Notification::getFromUsername() {
    return this->from_username;
}

string Notification::getToUsername() {
    return this->to_username;
}

string Notification::getMessage() {
    return this->message;
}

string Notification::getDate() {
    return this->date;
}

string Notification::getTime() {
    return this->time;
}

bool Notification::getIsRead() {
    return this->isRead;
}

void Notification::printNotification() {
    this->markAsRead();
    cout << "From: " << this->from_username << "     |     " << "To: " << this->to_username 
            << "     |     " << this->date << " " << this->time << endl;
    cout << separator << endl;
    cout << "Message: " << this->message << endl;
}

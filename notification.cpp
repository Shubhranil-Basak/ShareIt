#include "classes.h"

using namespace std;

Notification::Notification(string &from_username, string &to_username, string &message, string &date, string &time) :
    from_username(from_username), to_username(to_username), message(message), date(date), time(time), isRead(false) {}


void Notification::markAsRead() {
    this->isRead = true;
}

string Notification::getFromUsername() const {
    return this->from_username;
}

string Notification::getToUsername() const {
    return this->to_username;
}

string Notification::getMessage() const {
    return this->message;
}

string Notification::getDate() const {
    return this->date;
}

string Notification::getTime() const {
    return this->time;
}

bool Notification::getIsRead() const {
    return this->isRead;
}

void Notification::printNotification() {
    this->markAsRead();
    cout << "From: " << this->from_username << "     |     " << "To: " << this->to_username 
            << "     |     " << this->date << " " << this->time << endl;
    cout << separator << endl;
    cout << "Message: " << this->message << endl;
}

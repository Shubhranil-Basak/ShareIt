#include "classes.h"

using namespace std;

enum categories stringToCategory(string &category) {
    if (category == "electronics") {
        return electronics;
    } else if (category == "furniture") {
        return furniture;
    } else if (category == "clothing") {
        return clothing;
    } else if (category == "books") {
        return books;
    } else if (category == "sports") {
        return sports;
    } else {
        return other;
    }
}

string categoryToString(enum categories category) {
    switch (category) {
        case electronics:
            return "electronics";
        case furniture:
            return "furniture";
        case clothing:
            return "clothing";
        case books:
            return "books";
        case sports:
            return "sports";
        default:
            return "other";
    }
}

enum conditions stringToCondition(string &condition) {
    if (condition == "excellent") {
        return excellent;
    } else if (condition == "good") {
        return good;
    } else if (condition == "fair") {
        return fair;
    } else {
        return poor;
    }
}

string conditionToString(enum conditions condition) {
    switch (condition) {
        case excellent:
            return "excellent";
        case good:
            return "good";
        case fair:
            return "fair";
        default:
            return "poor";
    }
}

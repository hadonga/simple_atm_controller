#include "bank.h"

using namespace std;

Account::Account() {}

Account::Account(string accountNumber, string accountInfo, int balance) {
    this->accountNumber = accountNumber;
    this->accountInfo = accountInfo;
    this->balance = balance;
}

Account::~Account() {}

string Account::getAccountNumber() const { return this->accountNumber; }

string Account::getAccountInfo() const { return this->accountInfo; }

int Account::getBalance() const { return this->balance; }

void Account::setBalance(int balance) { this->balance = balance; }

int Account::depositBalance(int money) {
    this->balance += money;
    return this->balance;
}

int Account::withdrawBalance(int money) {
    if (this->balance < money) {
        return -1;
    }
    this->balance -= money;
    return this->balance;
}

User::User() {}

User::User(string cardNumber, string userName, int pinNumber) {
    this->cardNumber = cardNumber;
    this->userName = userName;
    this->pinNumber = pinNumber;
    this->wrongCount = 0;
}

User::~User() {}

string User::getCardNumber() const { return this->cardNumber; }

string User::getUserName() const { return this->userName; }

int User::getPinNumber() const { return this->pinNumber; }

int User::getWrongCount() const { return this->wrongCount; }

vector<Account> User::getAccounts() const { return this->accounts; }

Account* User::getAccount(int idx) { return &(this->accounts[idx]); }

void User::addWrongCount() { this->wrongCount++; }

void User::resetWrongCount() { this->wrongCount = 0; }

void User::setAccounts(vector<Account> accounts) { this->accounts = accounts; }

void User::addAccount(Account a) { accounts.push_back(a); }

bool User::isValidCardNumber(string cardNumber) {
    bool isValid = (cardNumber.length() == 19);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            char cur = cardNumber[5 * i + j];
            isValid &= ('0' <= cur && cur <= '9');
        }
    }

    for (int i = 0; i < 3; i++) {
        char cur = cardNumber[5 * i + 4];
        isValid &= (cur == '-');
    }

    return isValid;
}

bool User::isValidPinNumber(int pinNumber) {
    return (pinNumber / 1000 != 0) && (pinNumber / (int)1e6 == 0);
}

map<string, User> getUsers() {
    map<string, User> users;

    User a("1111-2222-3333-4444", "James", 1234);
    vector<Account> aAccounts;
    aAccounts.push_back({"111111-22-333333", "Saving Account", 500});
    aAccounts.push_back({"444444-55-666666", "Checking Account", 600});
    a.setAccounts(aAccounts);

    User b("1234-5678-9012-3456", "Julia", 1425);
    vector<Account> bAccounts;
    bAccounts.push_back({"526043-98-482192", "Saving Account", 0});
    bAccounts.push_back({"295061-15-192348", "Checking Account", 600});
    b.setAccounts(aAccounts);

    users[a.getCardNumber()] = a;
    users[b.getCardNumber()] = b;

    return users;
}
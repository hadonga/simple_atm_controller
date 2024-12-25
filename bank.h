#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Account {
    string accountNumber;
    string accountInfo;
    int balance;

   public:
    Account();
    Account(string accountNumber, string accountInfo, int balance);
    ~Account();
    string getAccountNumber() const;
    string getAccountInfo() const;
    int getBalance() const;
    void setBalance(int balance);
    int depositBalance(int money);
    int withdrawBalance(int money);
};

class User {
    string cardNumber, userName;
    int pinNumber, wrongCount;
    vector<Account> accounts;

   public:
    User();
    User(string cardNumber, string userName, int pinNumber);
    ~User();
    string getCardNumber() const;
    string getUserName() const;
    int getPinNumber() const;
    int getWrongCount() const;
    vector<Account> getAccounts() const;
    Account* getAccount(int idx);
    void addWrongCount();
    void resetWrongCount();
    void setAccounts(vector<Account> accounts);
    void addAccount(Account a);
    static bool isValidCardNumber(string cardNumber);
    static bool isValidPinNumber(int pinNumber);
};

map<string, User> getUsers();

int insertCard(map<string, User>& users, User** user);
int checkPinNumber(User* user);
int selectAccount(User* user, Account** account);
int bank(Account* account);

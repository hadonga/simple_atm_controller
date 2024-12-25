#include "atmController.h"

#define EXIT 0
#define CARDINSERTION 1
#define CHECKINGPINNUMBER 2
#define ACCOUNTSELECTION 3
#define BANKING 4

int insertCard(map<string, User>& users, User** user) {
    cout << "\nInsert your card (####-####-####-####)\n";
    string cardNumber;
    cin >> cardNumber;
    cout << "... processing\n";

    if (!User::isValidCardNumber(cardNumber)) {
        cout << "Invalid card number!\n";
        return CARDINSERTION;
    }

    if (!users.count(cardNumber)) {
        cout << "You are not our user\n";
        return CARDINSERTION;
    }

    *user = &users[cardNumber];
    cout << "Welcome " << (*user)->getUserName() << "\n";
    return CHECKINGPINNUMBER;
}

int checkPinNumber(User* user) {
    cout << "\nType your pin number (4-6 length)\n";
    int pinNumber;
    cin >> pinNumber;

    if (!User::isValidPinNumber(pinNumber) ||
        user->getPinNumber() != pinNumber) {
        string warning = (!User::isValidPinNumber(pinNumber))
                             ? "Invalid pin number\n"
                             : "Wrong pin number\n";
        cout << warning;
        user->addWrongCount();
        return CHECKINGPINNUMBER;
    }

    user->resetWrongCount();
    cout << "Welcome " << user->getUserName() << "!\n";

    return ACCOUNTSELECTION;
}

int selectAccount(User* user, Account** account) {
    cout << "\nSelect the account you want\n";

    vector<Account> accounts = user->getAccounts();
    for (int i = 0; i < accounts.size(); i++) {
        cout << i + 1 << ". " << accounts[i].getAccountInfo() << '\n';
    }
    cout << "0. Exit\n\n";

    int accountIdx;
    cin >> accountIdx;

    if (accountIdx == EXIT) {
        return EXIT;
    }

    if (accountIdx < 1 || accounts.size() < accountIdx) {
        cout << "Invalid input\n";
        return ACCOUNTSELECTION;
    }

    *account = user->getAccount(accountIdx - 1);
    if (account != NULL) {
        cout << "You select " << (*account)->getAccountInfo() << '\n';
        return BANKING;
    }
    cout << "ERROR" << '\n';
    return ACCOUNTSELECTION;
}

int bank(Account* account) {
    cout << "\nWith " << account->getAccountInfo() << ", you can\n";
    vector<string> options{"See the balance", "Deposit", "Withdraw",
                           "Go to the previous page"};

    for (int i = 0; i < options.size(); i++) {
        cout << i + 1 << ". " << options[i] << '\n';
    }
    cout << "0. Exit\n\n";

    enum Option {
        Exit = 0,
        Balance = 1,
        Deposit = 2,
        Withdrawal = 3,
        AccountSelection = 4
    };
    int optionIdx, money;
    cin >> optionIdx;

    switch (optionIdx) {
        case Exit:
            return EXIT;
        case Balance:
            cout << "Your balance is $" << account->getBalance() << '\n';
            break;
        case Deposit:
            cout << "\nHow much would you like to deposit\n";
            cin >> money;
            account->depositBalance(money);
            cout << "\nYour balance becomes $" << account->getBalance()
                 << " from $" << account->getBalance() - money << '\n';
            break;
        case Withdrawal:
            cout << "\nHow much would you like to withdraw\n";
            cin >> money;
            if (account->withdrawBalance(money) == -1) {
                cout << "\nYour balance is $" << account->getBalance()
                     << ", less than $" << money << '\n';
            } else {
                cout << "\nYour balance becomes $" << account->getBalance()
                     << " from $" << account->getBalance() + money << '\n';
            }
            break;
        case AccountSelection:
            return ACCOUNTSELECTION;
    }

    return BANKING;
}

void run(map<string, User>& users) {
    int process = CARDINSERTION;
    User* user = NULL;
    Account* account = NULL;

    while (process != EXIT) {
        switch (process) {
            case CARDINSERTION:
                process = insertCard(users, &user);
                break;

            case CHECKINGPINNUMBER:
                process = checkPinNumber(user);
                break;

            case ACCOUNTSELECTION:
                process = selectAccount(user, &account);
                break;

            case BANKING:
                process = bank(account);
                break;
        }
    }
    cout << "See you next time!\n";
}

int main() {
    // disables the syncronization between the C and C++ standard streams
    ios_base::sync_with_stdio(false);

    map<string, User> users = getUsers();
    run(users);

    return 0;
}
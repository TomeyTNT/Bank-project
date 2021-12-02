#include "Account.h"
#include <iostream>
#include <string>
#include <vector>

Account::Account(){
    name = "";
    id = 0;
    balance = 0;
}

std::vector<Account> Account::accountDatabase;

void Account::addAccount(Account account){
    accountDatabase.push_back(account);
}

std::string Account::getName() const{
    return name;
}

int Account::getId() const{
    return id;
}

double Account::getBalance() const{
    return balance;
}

void Account::setName(std::string userName){
    name = userName;
}

void Account::setID(int newId){
    if (newId < 1)
        throw "\n\t\t\t\t  ~ ID cannot be zero or negative ~";

    for (int i = 0; i < accountDatabase.size(); i++)
        if (newId == accountDatabase[i].getId())
            throw "\n\t\t\t\t~ Entered ID is already in use ~";

    id = newId;
}

void Account::setBalance(double newBalance){
    if (newBalance < 0)
        throw "\n\t\t\t\t  ~ Balance cannot be negative ~";

    balance = newBalance;
}

void Account::withdraw(double amount){
    if (amount < 0)
        throw "\n\t\t\t\t  ~ Withdrawal amount cannot be negative ~";

    balance -= amount;
}

void Account::deposit(double amount){
    if (amount < 0)
        throw "\n\t\t\t\t  ~ Amount for deposit cannot be negative ~";

    balance += amount;
}
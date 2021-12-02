#include <iostream>
#include "Account.h"
#include <string>

void printMenu(){
    std::cout << "\n" << R"(
                                   Please select one of the following options:

                                     1. Create an account
                                     2. Check balance
                                     3. Withdraw
                                     4. Deposit
                                     5. Account summary
                                     6. Make a transaction
                                     7. Exit
                    )" << "\n\t\t\t\t--> ";
}

// get a valid input
template<typename Type>
void getInput(Type &value){
    while (true){
        std::cin >> value;
        if (std::cin.fail()){
            std::cin.clear();
            std::cin.ignore(100, '\n');
            std::cout << "\n\t\t\t\t\t~ Invalid input ~"
            << "\n\t\t\t\t--> Enter again: ";
        }
        else {
            std::cin.ignore();
            return;
        }
    }
}

// find account in account database and return index of that account
int findAccount (int id){
    for (int i = 0; i < Account::accountDatabase.size(); i++)
        if (id == Account::accountDatabase[i].getId()) return i;

    return -1;
}

void createAccount (){
    Account newAccount;
    std::cout << "\n\t\t\t\t--> Please enter your name: ";
    std::string name;
    std::cin.ignore();
    std::getline(std::cin, name);
    newAccount.setName(name);
    std::cout << "\n\t\t\t\t--> Please enter your ID: ";
    int id;
    getInput(id);
    newAccount.setID(id);
    std::cout << "\n\t\t\t\t--> Please enter your balance: ";
    double balance;
    getInput(balance);
    newAccount.setBalance(balance);
    // add account to the database
    newAccount.addAccount(newAccount);
    std::cout << "\n\t\t\t\t~ Your account has been successfully created ~\n";
}

void MenuSelection(){

    int option = 1, account, id;
    while (option != 7){

      try{
        switch (option){
            case 1: createAccount();break;

            // check balance
            case 2:{
                    std::cout << "\n\t\t\t\t--> Please enter your ID: ";
                    getInput(id);
                    account = findAccount(id);
                    if (account == -1) std::cout << "\n\t\t\t\t~ ID does not match any in the database ~\n";
                    else std::cout << "\n\t\t\t\t--> Your balance: " << Account::accountDatabase[account].getBalance();
                    } break;

            // withdraw money
            case 3:{
                    std::cout << "\n\t\t\t\t--> Enter amount to withdraw: ";
                    double withdrawalAmount;
                    getInput(withdrawalAmount);
                    std::cout << "\n\t\t\t\t--> Please enter your ID: ";
                    getInput(id);
                    account = findAccount(id);
                         if (account == -1) std::cout << "\n\t\t\t\t~ ID does not match any in the database ~\n";
                         else {
                            if (Account::accountDatabase[account].getBalance() >= withdrawalAmount){
                                Account::accountDatabase[account].withdraw(withdrawalAmount);
                                std::cout << "\n\t\t\t\t~ Amount successfully withdrawn ~\n";
                            }
                            else std::cout << "\n\t\t\t~ Withdrawal not successful - check the state of balance ~\n";
                         }
                    } break;

            // deposit money
            case 4:{
                    std::cout << "\n\t\t\t\t--> Enter amount to deposit: ";
                    double depositAmount;
                    getInput(depositAmount);
                    std::cout << "\n\t\t\t\t--> Please enter your ID: ";
                    getInput(id);
                    account = findAccount(id);
                    if (account == -1) std::cout << "\n\t\t\t\t~ ID does not match any in the database ~\n";
                    else {
                            Account::accountDatabase[account].deposit(depositAmount);
                            std::cout << "\n\t\t\t\t-->~ Amount successfully deposited ~\n";
                    }
                    } break;

            // print account summary
            case 5:{
                    std::cout << "\n\t\t\t\t--> Please enter your ID: ";
                    getInput(id);
                    account = findAccount(id);
                    if (account == -1) std::cout << "\n\t\t\t\t~ ID does not match any in the database ~\n";
                    else std::cout << "\n\n\t\t\t\t~ ACCOUNT SUMMARY ~\n"
                                   << "\n\t\t\t\t--> Name: " << Account::accountDatabase[account].getName()
                                   << "\n\t\t\t\t--> ID: " << Account::accountDatabase[account].getId()
                                   << "\n\t\t\t\t--> Balance: " << Account::accountDatabase[account].getBalance() << "\n";

                    } break;

            // make a transaction
            case 6:{
                    std::cout << "\n\t\t\t\t--> Do you wish to withdraw or deposit? (w/d): ";
                    char choice;
                    std::cin >> choice;
                    std::cout << "\n\t\t\t\t--> Enter transaction amount: ";
                    double amount;
                    getInput(amount);
                    std::cout << "\n\t\t\t\t--> Please enter your ID: ";
                    getInput(id);
                    account = findAccount(id);
                    if (account == -1) std::cout << "\n\t\t\t\t~ ID does not match any in the database ~\n";
                    else {
                         std::cout << "\n\t\t\t\t--> Please enter ID of the transaction account: ";
                         getInput(id);
                         int secondAccount = findAccount(id);
                         if (secondAccount == -1) std::cout << "\n\t\t\t\t~ ID does not match any in the database ~\n";
                         else {
                              bool transactionPerformed = false;
                              if (tolower(choice) == 'w' && Account::accountDatabase[secondAccount].getBalance() >= amount){
                                  Account::accountDatabase[secondAccount].withdraw(amount);
                                  Account::accountDatabase[account].deposit(amount);
                                  transactionPerformed = true;
                              }
                              else if (tolower(choice) == 'd' && Account::accountDatabase[account].getBalance() >= amount){
                                  Account::accountDatabase[secondAccount].deposit(amount);
                                  Account::accountDatabase[account].withdraw(amount);
                                  transactionPerformed = true;
                              }
                              if (!transactionPerformed) std::cout << "\n\t\t\t\t~ Transaction not successful ~\n";
                              else std::cout << "\n\t\t\t\t~ Transaction successfully completed ~\n";
                            }
                     }
                    }
            }
         }
         catch (const char* msg){
                std::cerr << msg;
         }
         printMenu();
         getInput(option);
         while (option < 1 || option > 7){
            std::cout << "\n\t\t\t\t--> Please enter a valid option (1-7): ";
            getInput(option);
         }
    }

    std::cout << R"(
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                            ~ G O O D  B Y E  B R O T H E R  ~

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                    )";
}

int main(){
    std::cout << R"(
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                     ~ W E L C O M E   T O   T H E   B A N K  B R O T H E R ~

^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


                    )";
    MenuSelection();
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount {
    string accountNumber;
    string name;
    double balance;

public:
    BankAccount(string accNo = "", string n = "", double b = 0.0) {
        accountNumber = accNo;
        name = n;
        balance = b;
    }

    void createAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Initial Balance: ";
        cin >> balance;
        saveToFile();
        cout << "Account created successfully!\n";
    }

    void deposit(double amount) {
        balance += amount;
        saveToFile();
        cout << "Deposited " << amount << " successfully.\n";
    }

    void withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient balance!\n";
        } else {
            balance -= amount;
            saveToFile();
            cout << "Withdrawn " << amount << " successfully.\n";
        }
    }

    void displayBalance() {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
    }

    void saveToFile() {
        ofstream file("bankdata.txt", ios::out);
        file << accountNumber << endl;
        file << name << endl;
        file << balance << endl;
        file.close();
    }

    bool loadFromFile() {
        ifstream file("bankdata.txt");
        if (!file) return false;
        getline(file, accountNumber);
        getline(file, name);
        file >> balance;
        file.close();
        return true;
    }
};

int main() {
    BankAccount account;
    int choice;
    double amount;

    if (!account.loadFromFile()) {
        cout << "No account found. Please create one.\n";
        account.createAccount();
    }

    do {
        cout << "\n--- Bank Management System ---\n";
        cout << "1. Deposit\n";
        cout << "2. Withdraw\n";
        cout << "3. Balance Inquiry\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter amount to deposit: ";
            cin >> amount;
            account.deposit(amount);
            break;
        case 2:
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            account.withdraw(amount);
            break;
        case 3:
            account.displayBalance();
            break;
        case 4:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}

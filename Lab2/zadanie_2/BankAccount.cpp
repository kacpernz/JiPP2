#include "BankAccount.hpp"
#include <iostream>

int BankAccount::nextId = 1;

BankAccount::BankAccount(std::string owner, double balance) 
    : owner(owner), balance(balance), id(nextId++) {
}

void BankAccount::deposit(double amount) {
    if (amount > 0.0) {
        balance += amount;
    }
}

void BankAccount::withdraw(double amount) {
    if (amount > 0.0 && amount <= balance) {
        balance -= amount;
    } else {
        std::cout << "Odmowa: Brak srodkow na koncie!" << std::endl;
    }
}

double BankAccount::getBalance() const {
    return balance;
}

int BankAccount::getId() const {
    return id;
}

void BankAccount::print() const {
    std::cout << "Wlasciciel: " << owner 
              << ", Saldo: " << balance 
              << ", ID: " << id << std::endl;
}
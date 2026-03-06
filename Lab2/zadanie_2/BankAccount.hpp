#ifndef BankAccount_HPP
#define BankAccount_HPP

#include <string>

class BankAccount
{
private:
    std::string owner;
    double balance;
    int id;
    static int nextId;

public:
    BankAccount(std::string owner, double balance);
    void deposit(double amount);
    void withdraw(double amount);
    double getBalance() const;
    int getId() const;
    void print() const;
};

#endif // BankAccount_HPP
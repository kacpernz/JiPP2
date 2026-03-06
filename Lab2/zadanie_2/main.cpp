#include "BankAccount.hpp"
#include <iostream>

int main()
{
    BankAccount account("Jan Kowalski", 1000.0);

    account.print();

    std::cout << "\nWplata 500 zl...\n";
    account.deposit(500.0);
    account.print();

    std::cout << "\nWyplata 200 zl...\n";
    account.withdraw(200.0);
    account.print();

    return 0;
}
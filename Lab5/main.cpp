#include <iostream>
#include "Ksiegarnia.hpp"

int main() {
    Book book1{"Teoria pozwol im", 25.00};
    Book book2{"Atomowe nawyki", 30.50};

    Order myOrder;

    myOrder += book1; 
    myOrder += {book1, 2}; 
    myOrder += book2;

    std::cout << "Wartosc zamowienia (bez dostawy): " 
              << myOrder.calculate_total_price() << " PLN\n";
              
    std::cout << "Wartosc zamowienia (z dostawa 12 PLN): " 
              << myOrder.calculate_total_price(12.0) << " PLN\n";

    return 0;
}
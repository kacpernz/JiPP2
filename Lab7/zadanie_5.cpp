#include <iostream>
#include <variant>
#include <string>

int main() {
    std::variant<int, std::string> v;

    v = 42;
    
    std::visit([](const auto& arg) { 
        std::cout << "Obecna wartosc: " << arg << "\n"; 
    }, v);

    v = "Nowoczesny C++";
    
    std::visit([](const auto& arg) { 
        std::cout << "Obecna wartosc: " << arg << "\n"; 
    }, v);

    return 0;
}

#include <iostream>
#include <string>
#include <optional>

std::optional<std::string> describe(int x) {
    if (x < 0) {
        return std::nullopt;
    }
    
    auto check_parity = [](int n) {
        return (n % 2 == 0) ? "even" : "odd";
    };
    
    return check_parity(x);
}

int main() {
    int test_values[] = {4, 7, -2};

    for (int val : test_values) {
        auto result = describe(val);
        
        std::cout << "Wartosc " << val << ": ";
        if (result) {
            std::cout << *result << "\n";
        } else {
            std::cout << "nullopt\n";
        }
    }

    return 0;
}

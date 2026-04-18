#include <iostream>
#include <vector>
#include <optional>

std::optional<int> find_even(const std::vector<int>& v) {
    for (int n : v) {
        if (n % 2 == 0) {
            return n;
        }
    }
    return std::nullopt;
}

int main() {
    std::vector<int> v = {1, 3, 5, 4, 7};

    auto res = find_even(v);
    
    if (res) {
        std::cout << *res << "\n";
    }

    return 0;
}

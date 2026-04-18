#include <iostream>
#include <vector>
#include <algorithm> 

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    int sum = 0;
    
    for (auto element : v) {
        sum += element;
    }
    
    std::cout << "Suma elementów: " << sum << "\n";

    int even_count = 0;

    std::for_each(v.begin(), v.end(), [&even_count](int n) {
        if (n % 2 == 0) {
            even_count++;
        }
    });

    std::cout << "Liczba elementów parzystych: " << even_count << "\n";

    return 0;
}

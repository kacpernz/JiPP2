#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    
    int counter1 = 0;
    std::for_each(v.begin(), v.end(), [&counter1](int n) {
        counter1++;
    });
    std::cout << "Capture przez referencje: " << counter1 << "\n";

    int counter2 = 0;
    std::for_each(v.begin(), v.end(), [counter2](int n) mutable {
        counter2++;
    });
    std::cout << "Capture przez wartosc: " << counter2 << "\n";

    return 0;
}

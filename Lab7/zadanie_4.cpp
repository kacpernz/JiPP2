#include <iostream>
#include <utility>

struct Point {
    int x, y;
};

std::pair<int, int> get_coordinates() {
    return {100, 200};
}

int main() {
    Point p{10, 20};
    
    auto [x, y] = p;
    
    std::cout << "Point x: " << x << ", y: " << y << "\n";

    auto [pair_x, pair_y] = get_coordinates();
    
    std::cout << "Pair x: " << pair_x << ", y: " << pair_y << "\n";

    return 0;
}

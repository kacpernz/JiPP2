#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>

// Zad 1 
template<typename T>
T maxValue(T a, T b) {
    return (a > b) ? a : b;
}

// Zad 2 
template<typename T>
void swapValues(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

// Zad 3 
template<typename T>
void printArray(T arr[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << "\n";
}

// Zad 4
template<typename T>
class Box {
private:
    T value;
public:
    Box(T v) : value(v) {}
    void set(T v) { value = v; }
    T get() const { return value; }
    void print() const { std::cout << value << "\n"; }
};

// Zad 5 
template<typename T>
class Pair {
private:
    T first;
    T second;
public:
    Pair(T a, T b) : first(a), second(b) {}
    T sum() const { return first + second; }
};

/*
 Odpowiedź do Zadania 5:
 Tak, sum() zadziała dla std::string.
 Szablony podstawiają dany typ w miejsce T, więc w tym przypadku 
 wywołany zostanie po prostu operator '+' dla dwóch stringów.
 Klasa std::string ma przeciążony ten operator, który odpowiada 
 za łączenie (konkatenację) napisów, więc kod skompiluje się 
 i wykona bez problemu.
 */


 // Zad 6
template<typename T>
class Vector2D {
public:
    T x;
    T y;
    Vector2D(T x, T y) : x(x), y(y) {}
    T lengthSquared() const {
        return (x * x) + (y * y);
    }
};

template<typename T>
T dotProduct(const Vector2D<T>& a, const Vector2D<T>& b) {
    return (a.x * b.x) + (a.y * b.y);
}

// Zad 7 
template<typename T>
void printVector(const std::vector<T>& v) {
    for (const auto& element : v) {
        std::cout << element << " ";
    }
    std::cout << "\n";
}

int main() {
    // Testy Zad 1
    std::cout << "-- Zad 1 --\n";
    std::cout << maxValue(5, 10) << "\n";
    std::cout << maxValue(2.5, 4.5) << "\n";
    std::cout << maxValue('a', 'z') << "\n";
    std::cout << maxValue<double>(5, 7.5) << "\n"; 

    // Testy Zad 2
    std::cout << "\n-- Zad 2 --\n";
    int i1 = 1, i2 = 2;
    swapValues(i1, i2);
    std::cout << "int: " << i1 << " " << i2 << "\n";

    float f1 = 1.5f, f2 = 2.5f;
    swapValues(f1, f2);
    std::cout << "float: " << f1 << " " << f2 << "\n";

    std::string s1 = "Ala", s2 = "Kot";
    swapValues(s1, s2);
    std::cout << "string: " << s1 << " " << s2 << "\n";

    // Testy Zad 3
    std::cout << "\n-- Zad 3 --\n";
    int arrInt[] = {1, 2, 3, 4, 5};
    printArray(arrInt, 5);
    std::string arrStr[] = {"A", "B", "C"};
    printArray(arrStr, 3);

    // Testy Zad 4
    std::cout << "\n-- Zad 4 --\n";
    Box<int> intBox(100);
    intBox.print();
    intBox.set(200);
    std::cout << intBox.get() << "\n";

    Box<std::string> strBox("Test");
    strBox.print();

    // Testy Zad 5
    std::cout << "\n-- Zad 5 --\n";
    Pair<int> pInt(10, 20);
    std::cout << "Suma int: " << pInt.sum() << "\n";
    Pair<std::string> pStr("Hello ", "World");
    std::cout << "Suma string: " << pStr.sum() << "\n";

    // Testy Zad 6
    std::cout << "\n-- Zad 6 --\n";
    Vector2D<int> v1(3, 4);
    Vector2D<int> v2(1, 2);
    std::cout << "lengthSquared v1: " << v1.lengthSquared() << "\n";
    std::cout << "dotProduct: " << dotProduct(v1, v2) << "\n";

    // Testy Zad 7
    std::cout << "\n-- Zad 7 --\n";
    std::vector<int> vecInt = {10, 20, 30};
    std::vector<std::string> vecStr = {"Jeden", "Dwa", "Trzy"};
    printVector(vecInt);
    printVector(vecStr);

    // Testy Zad 8
    std::cout << "\n-- Zad 8 --\n";
    std::vector<int> v = {7, 2, 9, 1, 5, 2};
    
    std::sort(v.begin(), v.end());
    std::cout << "Posortowane: ";
    printVector(v);

    auto maxIt = std::max_element(v.begin(), v.end());
    std::cout << "Najwiekszy element: " << *maxIt << "\n";

    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "Suma: " << sum << "\n";

    return 0;
}
#include <iostream>
#include <memory>

int* create_bad() {
    return new int(42);
}

std::unique_ptr<int> create_good() {
    return std::make_unique<int>(42);
}

void use_smart_pointer(std::unique_ptr<int> ptr) {
    std::cout << *ptr << "\n";
}

int main() {
    int* raw_ptr = create_bad();
    std::cout << *raw_ptr << "\n";
    delete raw_ptr; 

    std::unique_ptr<int> smart_ptr = create_good();
    
    use_smart_pointer(std::move(smart_ptr));

    return 0;
}

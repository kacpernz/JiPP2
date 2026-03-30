#pragma once
#include <vector>
#include <string>

struct Book {
    std::string title;
    double price;
};

struct OrderItem {
    Book book;
    int quantity;
};

class Order {
private:
    std::vector<OrderItem> items;

public:
    Order& operator+=(const Book& book);
    Order& operator+=(const OrderItem& orderItem);
    double calculate_total_price(double delivery_cost = 0.0) const; 
};
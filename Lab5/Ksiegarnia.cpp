#include "Ksiegarnia.hpp"

Order& Order::operator+=(const Book& book) {
    for (auto& item : items) {
        if (item.book.title == book.title) {
            item.quantity++;
            return *this;
        }
    }
    items.push_back({book, 1});
    return *this;
}

Order& Order::operator+=(const OrderItem& orderItem) {
    for (auto& item : items) {
        if (item.book.title == orderItem.book.title) {
            item.quantity += orderItem.quantity;
            return *this;
        }
    }
    items.push_back(orderItem);
    return *this;
}

double Order::calculate_total_price(double delivery_cost) const {
    double total = 0.0;
    for (const auto& item : items) {
        total += item.book.price * item.quantity;
    }
    return total + delivery_cost;
}
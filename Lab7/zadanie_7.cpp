#include <iostream>
#include <vector>
#include <algorithm>
#include <compare>

struct Student {
    int grade;

    auto operator<=>(const Student&) const = default;
};

int main() {
    std::vector<Student> students = {{4}, {2}, {5}, {1}, {3}};

    std::sort(students.begin(), students.end());

    for (const auto& student : students) {
        std::cout << student.grade << " ";
    }
    std::cout << "\n";

    return 0;
}

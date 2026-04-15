#pragma once
#include <memory>
#include <vector>

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Circle : public Shape {
private:
    double radius;
public:
    explicit Circle(double r = 0.0);
    double area() const override;
    double getRadius() const;
};

class Rectangle : public Shape {
private:
    double width;
    double height;
public:
    Rectangle(double w = 0.0, double h = 0.0);
    double area() const override;
    double getWidth() const;
    double getHeight() const;
};

class Triangle : public Shape {
private:
    double base;
    double height;
public:
    Triangle(double b = 0.0, double h = 0.0);
    double area() const override;
    double getBase() const;
    double getHeight() const;
};

class Group : public Shape {
private:
    std::vector<std::unique_ptr<Shape>> shapes;
public:
    Group() = default;
    void addShape(std::unique_ptr<Shape> shape);
    double area() const override; // Suma pól w grupie
    const std::vector<std::unique_ptr<Shape>>& getShapes() const;
};
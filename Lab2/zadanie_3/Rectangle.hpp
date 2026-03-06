#ifndef Rectangle_HPP
#define Rectangle_HPP

class Rectangle {
    private:
        double width;
        double height;

    public:
        Rectangle(double width, double height);
        double area() const;
        double perimeter() const;
        bool isSquare() const;
        void scale(double factor);
        static Rectangle createSquare(double sideLength);
};

#endif // Rectangle_HPP
#include <iostream>
#include <variant>

struct Circle {
    double radius;
    double area() const { return 3.14159 * radius * radius; }
};

struct Rectangle {
    double width, height;
    double area() const { return width * height; }
};

using Shape = std::variant<Circle, Rectangle>;

class ShapeCalculator {
public:
    /*
        We defined computeArea as a static method of the ShapeCalculator class. 
        Because the method does not depend on any specific instance of the class, we can make it static.
    */
    static double computeArea(const Shape& shape) {
        /*
            We use std::visit to apply a lambda function to the shape variant. 
            The lambda function takes a const reference to the current state of the variant and returns the area of the shape.
            The lambda function uses std::visit to call the area method of the current state.
        */
        return std::visit([](const auto& s) {
            return s.area();
        }, shape);
    }
};

int main() {
    Shape circle = Circle{5.0};
    Shape rectangle = Rectangle{4.0, 3.0};

    std::cout << "Circle area: " << ShapeCalculator::computeArea(circle) << std::endl;
    std::cout << "Rectangle area: " << ShapeCalculator::computeArea(rectangle) << std::endl;

    return 0;
}

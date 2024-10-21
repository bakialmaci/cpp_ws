#include <iostream>
#include <variant>

class NumberHolder {
public:
    std::variant<int, float> value;

    NumberHolder(int i) : value(i) {}
    NumberHolder(float f) : value(f) {}

    // The print function is also marked as const, which means it does not modify the object's state.
    void print() const {
        if (std::holds_alternative<int>(value)) {
            std::cout << "Integer value:" << std::get<int>(value) << std::endl;
        } else if (std::holds_alternative<float>(value)) {
            std::cout << "Float value:" << std::get<float>(value) << std::endl;
        }
    }
};

int main() {
    NumberHolder intHolder(42);
    NumberHolder floatHolder(3.14f);

    intHolder.print();
    floatHolder.print();

    return 0;
}

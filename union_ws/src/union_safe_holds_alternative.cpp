/*
std::variant is a type-safe union that can store values of different types in a single object.
This snippet demonstrates how to use std::variant to create an Entry struct that can store either an int or a float value.
The print_entry function uses std::holds_alternative and std::get to print the value stored in the Entry.
The main function creates two Entry objects, one with an int value and the other with a float value, and calls print_entry to print their values.
The std::variant type ensures that you can safely store either an int or a float value in the same object.
By using std::holds_alternative and std::get, you can check the type of the stored value and access it safely.
This approach is more type-safe and robust than using a traditional union with an enum to track the type.
Advantages:
- std::variant is a type-safe union that ensures you access the correct type of value.
- It allows you to store values of different types in a single object.
- std::holds_alternative and std::get provide a safe way to check and access the stored value.
Disadvantages:
- It may require additional boilerplate code to handle different types stored in the variant.
Recommendation:
- Use std::variant when you need to store values of different types in a single object.
- Use std::holds_alternative and std::get to safely check and access the stored value.
- Consider the trade-offs between type safety and complexity when choosing between std::variant and traditional unions.
*/

#include <iostream>
#include <variant>
using namespace std;

// std::variant: Can safely store both int and float
struct Entry {
    variant<int, float> v;  // Can store either int or float values
};

// Function to print the value stored in Entry
void print_entry(const Entry& e) {
    if (holds_alternative<int>(e.v)) {  // If v holds an int
        cout << "Integer value: " << get<int>(e.v) << endl;
    } else if (holds_alternative<float>(e.v)) {  // If v holds a float
        cout << "Float value: " << get<float>(e.v) << endl;
    }
}

int main() {
    // The first Entry holds an integer value
    Entry e1;
    e1.v = 42;  // Assigning an int to v

    // The second Entry holds a float value
    Entry e2;
    e2.v = 3.14f;  // Assigning a float to v

    print_entry(e1);
    print_entry(e2);

    // Even if we try to change the type with std::variant, safety is ensured
    e1.v = 2.71f;  // Now assigning a float to v
    print_entry(e1);  // Automatically prints the float

    return 0;
}

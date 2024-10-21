/*
std::visit is a powerful tool that allows you to apply a lambda function to the value stored in a std::variant.
This snippet demonstrates how to use std::visit to print the value stored in a variant.
The Entry struct contains a variant that can store either an int or a float value.
The print_entry_with_visit function uses std::visit to apply a lambda function that prints the value of the variant.
The main function creates two Entry objects, one with an int value and the other with a float value, and calls print_entry_with_visit to print their values.
The lambda function inside std::visit uses auto&& arg to deduce the type of the stored value and prints it.
This approach is more concise and elegant than using if-else statements or switch-case blocks to handle different types stored in a variant.
It is also type-safe and ensures that you handle all possible types correctly.
By using std::visit, you can handle all possible types stored in a variant in a single function, making your code more maintainable and readable.
Advantages:
- std::visit is a more concise and elegant way to handle the values stored in a variant.
- It allows you to handle all possible types in a single lambda function.
- It is type-safe and ensures that you handle all possible types correctly.
Disadvantages:
- It may be more complex to understand for beginners who are not familiar with lambdas and std::visit.
- It requires a good understanding of C++ templates and type deduction to write the lambda function correctly.
- It may not be as efficient as direct access to the stored value in some cases.
Recommendation:
- Use std::visit when you need to handle all possible types stored in a variant in a single function.
- Use std::visit when you want to write concise and elegant code that is type-safe and easy to maintain.
- Use direct access to the stored value when performance is critical and you know the exact type stored in the variant.
- Consider the trade-offs between readability, maintainability, and performance when choosing between std::visit and direct access.
*/
#include <iostream>
#include <variant>

using namespace std;

// A struct holding a variant of int or float
struct Entry {
    variant<int, float> v;  // Can hold either int or float
};

// Function that uses std::visit to print the value of Entry
void print_entry_with_visit(const Entry& e) {
    std::visit([](auto&& arg) {  // Use a lambda to handle all types
        cout << "Value: " << arg << endl;
    }, e.v);
}

int main() {
    // First Entry stores an integer
    Entry e1;
    e1.v = 42;

    // Second Entry stores a float
    Entry e2;
    e2.v = 3.14f;

    // Print using std::visit approach
    print_entry_with_visit(e1);
    print_entry_with_visit(e2);

    return 0;
}

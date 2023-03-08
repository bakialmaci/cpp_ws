#include <iostream>

#define LOG(x) std::cout << x << std::endl

int main() 
{
    // lambda function that prints "Hello World!"
    auto greet = []() {
    LOG("Hello World!");
    };

    // lambda function that takes two integers and prints their sum
    auto add = [] (int a, int b) {
    LOG(a + b);
    };

    // lambda function with explicit return type 'double'
    auto operation = []  (int a, int b,  std::string op) -> double {
    if (op == "sum")
        return a + b;
    else if (op == "avg")
        return (a + b) / 2.0;
    else
        return 0;
    };

    // call lambda function
    greet();
    add(2, 3);
    LOG(operation(4, 3, "sum"));

    return 0;
}
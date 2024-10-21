#include <iostream>
#include "main_meta.hpp"

int main() {
    // Derleme Zamanı Fibonacci Hesaplaması
    constexpr int fib5 = fibonacci(5);
    std::cout << "Fibonacci of 5 is: " << fib5 << std::endl;

    // Tür Kontrolü - Derleme Zamanında Türlere Göre Davranış
    std::cout << "Checking type of int:\n";
    check_type<int>();

    std::cout << "Checking type of double:\n";
    check_type<double>();

    std::cout << "Checking type of std::string:\n";
    check_type<std::string>();

    // Derleme Zamanı Faktöriyel Hesaplaması
    std::cout << "Factorial of 5 is: " << Factorial<5>::value << std::endl;

    // Derleme Zamanı İndeks Yazdırma
    std::cout << "Printing indices for index sequence of 5:\n";
    print_indices(std::make_index_sequence<5>{});

    return 0;
}

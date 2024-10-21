#ifndef META_FUNCTIONS_HPP
#define META_FUNCTIONS_HPP

#include <iostream>
#include <type_traits>
#include <utility>  // Required for std::index_sequence and std::make_index_sequence

// Constexpr Fibonacci (Compile-time Fibonacci calculation)
constexpr int fibonacci(int n) {
    return (n <= 1) ? n : fibonacci(n - 1) + fibonacci(n - 2);
}

// Compile-time Type Checking with Type Traits
template<typename T>
void check_type() {
    if constexpr (std::is_integral<T>::value) {
        std::cout << "Type is an integral type.\n";
    } else if constexpr (std::is_floating_point<T>::value) {
        std::cout << "Type is a floating-point type.\n";
    } else {
        std::cout << "Type is something else.\n";
    }
}

// Factorial computation using template metaprogramming (Compile-time Factorial)
template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N - 1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// Print a list of compile-time indices using integer sequences
template<std::size_t... Is>
void print_indices(std::index_sequence<Is...>) {
    ((std::cout << Is << " "), ...);  // Fold expression to print all indices
    std::cout << '\n';
}

#endif

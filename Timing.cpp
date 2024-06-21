// Timing.cpp: Defines the entry point for the console application.
#include <chrono>
#include "functions.h"

using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;

template <typename Func>
long long TimeFunc(Func f) {
    auto begin = steady_clock::now();
    f();
    auto end = steady_clock::now();

    return duration_cast<seconds>(end - begin).count();
}

long fibonacci(unsigned n) {
    // the nth fibonacci number
    if (n < 2) {
        return n; // starts 0, 1, ...
    }
    return fibonacci(n - 2) + fibonacci(n - 1);
}

long Fib20() {
    return fibonacci(20);
}

int timing() {
    int fib40;
    auto seconds = TimeFunc([&]() {fib40 = fibonacci(40); });
    double thirty;
    seconds = TimeFunc([&]() {thirty = 10.0 + 20.0; });
    seconds = TimeFunc(Fib20);

    //This is not a function
    //seconds = TimeFunc(42);

    return 0;
}
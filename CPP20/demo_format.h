#include <iostream>
#include <format>
#include <chrono>

void demo_format()
{
    std::cout << "*** C++20: FORMAT ***" << std::endl;
    std::string s = std::format("Hello CPP {} Team!", 20);
    std::cout << s << std::endl;

    int number = 42;
    // double pi = 3.14159;
    // C++20:
    double pi = std::numbers::pi;

    int large_number = 123456789;

    // Format integers
    std::cout << std::format("Default integer: {}\n", number);
    std::cout << std::format("Hexadecimal: {:#x}\n", number);
    std::cout << std::format("Binary: {:#b}\n", number);
    std::cout << std::format("Octal: {:#o}\n", number);

    // Format floating-point numbers
    std::cout << std::format("Default floating-point: {}\n", pi);
    std::cout << std::format("Fixed-point: {:.2f}\n", pi);
    std::cout << std::format("Scientific: {:.2e}\n", pi);

    auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    std::string msg = "The current time is";
    std::cout << std::format("{0}: {1:%Y-%m-%d %H:%M:%S}", msg, now) << std::endl;
}
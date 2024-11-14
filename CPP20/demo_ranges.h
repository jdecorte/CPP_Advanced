#include <iostream>
#include <ranges>
#include <vector>
#include <algorithm>

void demo_ranges()
{
    std::cout << "*** C++20: RANGES/VIEWS ***" << std::endl;
    // VIEWS
    using std::views::filter,
          std::views::transform,
          std::views::reverse;

    // Some data for us to work on
    std::vector<int> numbers = { 6, 5, 4, 3, 2, 1 };

    // Lambda function that will provide filtering
    auto is_even = [](int n) { return n % 2 == 0; };

    // Process our dataset
    auto results = numbers | filter(is_even)
                   | transform([](int n) { return ++n; })
                   | reverse;

    // Use lazy evaluation to print out the results
    auto print = [](int n) { std::cout << n << " "; };

    // C++17
    std::for_each(results.begin(), results.end(), print);
    std::cout << std::endl;

    // C++20
    std::ranges::for_each(results, print);
    std::cout << std::endl;
}
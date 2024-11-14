#include <iostream>
#include <array>
#include <ranges>
#include <algorithm>

class DemoLambdas
{
public:
    void run()
    {
        std::array<int, 5> numbers = { 1, 2, 3, 4, 5 };
        auto add = [=,this](int n) { sum += n; };  // implicitly capture of this is deprecated in C++20, capture all local variables by value
        std::ranges::for_each(numbers, add);
        std::cout << "Sum: " << sum << std::endl;       
    }

private:
    int sum{0};
};

void demo_lambdas()
{
    std::cout << "*** C++20: LAMBDAS ***" << std::endl;
    DemoLambdas demo;
    demo.run();
}
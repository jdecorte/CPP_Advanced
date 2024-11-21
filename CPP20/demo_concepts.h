// fig15_05.cpp
// Constrained multiply function template that allows 
// only integers and floating-point values.
#include <concepts>
#include <iostream>

// C++17
template<typename T>
T multiply0(T first, T second) {return first * second;}

// C++20 concept that constrains the template parameter to
template<typename T>
   requires std::integral<T> || std::floating_point<T>
T multiply1(T first, T second) {return first * second;}

// C++20 custom concept that constrains the template parameter
template<typename T>
concept Numeric = std::integral<T> || std::floating_point<T>;

auto multiply2(Numeric auto first, Numeric auto second) {return first * second;}

void demo_concepts() {

   std::cout << "C++17:\n Product of 5 and 3: " << multiply0(5, 3)
   << "\n Product of 7.25 and 2.0: " << multiply0(7.25, 2.0) << "\n";

   std::cout << "C++20:\n Product of 5 and 3: " << multiply1(5, 3)
      << "\n Product of 7.25 and 2.0: " << multiply1(7.25, 2.0) << "\n";

   std::cout << "C++20 abbreviated function template:\n Product of 5 and 3: " << multiply2(5, 3)
      << "\n Product of 7.25 and 2.0: " << multiply2(7.25, 2.0) << "\n";

   std::string s1{"hi"};
   std::string s2{"bye"};
   // int s1{5};
   // int s2{3};
   // auto result{multiply0(s1, s2)};
}

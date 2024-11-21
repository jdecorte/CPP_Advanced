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
T multiply(T first, T second) {return first * second;}

void demo_concepts() {

   std::cout << "C++17: Product of 5 and 3: " << multiply0(5, 3)
   << "\nProduct of 7.25 and 2.0: " << multiply0(7.25, 2.0) << "\n";

   std::cout << "C++20: Product of 5 and 3: " << multiply(5, 3)
      << "\nProduct of 7.25 and 2.0: " << multiply(7.25, 2.0) << "\n";

   std::string s1{"hi"};
   std::string s2{"bye"};
   // int s1{5};
   // int s2{3};
   auto result{multiply0(s1, s2)};
}


/**************************************************************************
 * (C) Copyright 1992-2022 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 **************************************************************************/

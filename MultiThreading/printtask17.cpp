// Fig. 17.4: printtask.cpp
// C++17
// Concurrently executing tasks with std::jthreads.
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <thread>
#include <vector>
#include <sstream>
#include "printtask.h"

int main() {
   std::cout << "MAIN STARTS\n";
   std::cout << "MAIN ID=" << id() << std::endl;
   // set up random-number generation 
   std::random_device rd;
   std::default_random_engine engine{rd()}; 
   std::uniform_int_distribution ints{0, 5000};

   std::vector<std::thread> threads; // stores the jthreads

   std::cout << "STARTING THREADS\n";

   // start two jthreads
   for (int i{1}; i < 3; ++i) {
      std::chrono::milliseconds sleepTime{ints(engine)};
      std::ostringstream name_os;
      name_os << "Task " << i;
      std::string name = name_os.str();
      // create a thread that calls printTask, passing name and sleepTime
      // as arguments and store the jthread, so it is not destructed until
      // the vector goes out of scope at the end of main; each jthread's
      // destructor automatically joins the jthread
      threads.push_back(std::thread{printTask, name, sleepTime});
   }
   std::cout << "\nTHREADS STARTED\n";
   std::cout << "\nMAIN ENDS\n";

   for (auto& t : threads) 
   {
      t.join();
   }
}



/************************************************************************
 * (C) Copyright 1992-2022 by Deitel & Associates, Inc. and             *
 * Pearson Education, Inc. All Rights Reserved.                         *
 *                                                                      *
 * DISCLAIMER: The authors and publisher of this book have used their   *
 * best efforts in preparing the book. These efforts include the        *
 * development, research, and testing of the theories and programs      *
 * to determine their effectiveness. The authors and publisher make     *
 * no warranty of any kind, expressed or implied, with regard to these  *
 * programs or to the documentation contained in these books. The       *
 * authors and publisher shall not be liable in any event for           *
 * incidental or consequential damages in connection with, or arising   *
 * out of, the furnishing, performance, or use of these programs.       *
 ***********************************************************************/


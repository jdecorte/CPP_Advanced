/// Fig. 17.7: SynchronizedBuffer.h 
// SynchronizedBuffer maintains synchronized access to a shared mutable
// integer that is accessed by a producer thread and a consumer thread.
#include <condition_variable>  
#include <mutex>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std::string_literals;

class SynchronizedBuffer {
public:
   // place value into m_buffer
   void put(int value) {
      // critical section that requires a lock to modify shared data
      {
         // lock on m_mutex to be able to write to m_buffer
         std::unique_lock dataLock{m_mutex};

         if (m_occupied) {
            std::cout << 
               "Producer tries to write.\n" << m_buffer << '\t' << m_occupied << '\n'
               << "Buffer full. Producer waits." << '\n';

            // wait on condition variable m_cv; the lambda in the second
            // argument ensures that if the thread gets the processor
            // before m_occupied is false, the thread continues waiting
            m_cv.wait(dataLock, [&]() {return !m_occupied; });
         }

         // write to m_buffer
         m_buffer = value;
         m_occupied = true;

         std::cout << std::left << std::setw(40) << ("Producer writes " + std::to_string(value))
          << m_buffer << "\t\t" << m_occupied << "\n\n";
      } // dataLock's destructor releases the lock on m_mutex 

      // if consumer is waiting, notify it that it can now read
      m_cv.notify_one();
   }

   // return value from m_buffer
   int get() {
      int value; // will store the value returned by get

      // critical section that requires a lock to modify shared data
      {
         // lock on m_mutex to be able to read from m_buffer
         std::unique_lock dataLock{m_mutex};

         if (!m_occupied) {
            std::cout << "Consumer tries to read.\n"
            << std::left << std::setw(40) << "Buffer empty. Consumer waits."
            << m_buffer << "\t\t" << m_occupied << "\n\n";

            // wait on condition variable m_cv; the lambda in the second 
            // argument ensures that if the thread gets the processor
            // before m_occupied is true, the thread continues waiting
            m_cv.wait(dataLock, [&]() {return m_occupied; });
         }

         value = m_buffer;
         m_occupied = false;

         std::cout << std::left << std::setw(40) << ("Consumer reads " + std::to_string(m_buffer))
          << m_buffer << "\t\t" << m_occupied << "\n"
          << std::string(64, '-') << "\n";
      } // dataLock's destructor releases the lock on m_mutex 

      // if producer is waiting, notify it that it can now write
      m_cv.notify_one();

      return value;
   }
private:
   int m_buffer{-1}; // shared by producer and consumer threads
   bool m_occupied{false};
   std::condition_variable m_cv;
   std::mutex m_mutex;
};


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


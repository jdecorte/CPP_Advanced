/// Fig. 17.7: SynchronizedBuffer.h 
// SynchronizedBuffer maintains synchronized access to a shared mutable
// integer that is accessed by a producer thread and a consumer thread.
#pragma once
#include <condition_variable> 
#include <format> 
#include <mutex>
#include <iostream>
#include <string>

using namespace std::string_literals;

class SynchronizedBuffer {
public:
   // place value into m_buffer
   void put(int value) {
      // critical section that requires a lock to modify shared data
      {
         // lock on m_mutex to be able to write to m_buffer
         // unique_lock is used here because we will be waiting on a condition
         std::unique_lock dataLock{m_mutex};

         if (m_occupied) {
            std::cout << std::format(
               "Producer tries to write.\n{:<40}{}\t\t{}\n\n",
               "Buffer full. Producer waits.", m_buffer, m_occupied);

            // wait on condition variable m_cv; the lambda in the second
            // argument ensures that if the thread gets the processor
            // before m_occupied is false, the thread continues waiting
            // lock is released and reacquired when the thread is notified and m_occupied is false
            m_cv.wait(dataLock, [&]() {return !m_occupied; });
         }

         // write to m_buffer
         m_buffer = value;
         m_occupied = true;

         std::cout << std::format("{:<40}{}\t\t{}\n\n",
            "Producer writes "s + std::to_string(value),
            m_buffer, m_occupied);
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
            std::cout << std::format(
               "Consumer tries to read.\n{:<40}{}\t\t{}\n\n",
               "Buffer empty. Consumer waits.", m_buffer, m_occupied);

            // wait on condition variable m_cv; the lambda in the second 
            // argument ensures that if the thread gets the processor
            // before m_occupied is true, the thread continues waiting
            m_cv.wait(dataLock, [&]() {return m_occupied; });
         }

         value = m_buffer;
         m_occupied = false;

         std::cout << std::format("{:<40}{}\t\t{}\n{}\n",
            "Consumer reads "s + std::to_string(m_buffer),
            m_buffer, m_occupied, std::string(64, '-'));
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


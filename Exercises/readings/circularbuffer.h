// Fig. 17.9: CircularBuffer.h
// Synchronizing access to a shared three-element circular buffer.
#include <array> 
#include <condition_variable> 
#include <mutex>
#include <iostream>
#include <string>
#include <string_view>

using namespace std::string_literals;

template <typename T>
class CircularBuffer {
public:
   const static int BufferSize = 10;
   // place value into m_buffer
   void put(T value) {
      // critical section that requires a lock to modify shared data
      {
         // lock on m_mutex to be able to write to m_buffer
         std::unique_lock dataLock{m_mutex};

         // if no empty locations, wait on condition variable m_cv  
         if (m_occupiedCells == m_buffer.size()) {
            std::cout << "Buffer is full. Producer waits.\n\n";

            // wait on the condition variable; the lambda argument 
            // ensures that if the thread gets the processor before
            // the m_buffer has open cells, the thread continues waiting
            /*
            The dataLock is passed to m_cv.wait to ensure that the thread is properly synchronized when it waits for the condition variable. Here's a step-by-step explanation:

Lock Acquisition: Before calling m_cv.wait, the dataLock (which is a std::unique_lock object) is acquired. This lock ensures that the current thread has exclusive access to the shared resource (m_buffer in this case).

Wait on Condition Variable: When m_cv.wait(dataLock, ...) is called, the following happens:

The dataLock is released, allowing other threads to acquire the lock and modify the shared resource.
The current thread is put into a waiting state and added to the list of threads waiting on the condition variable m_cv.
Condition Check: The lambda function passed as the second argument to m_cv.wait is used to check the condition. If the condition is not met (i.e., m_occupiedCells < m_buffer.size() is false), the thread continues to wait.

Reacquire Lock: Once the condition is met and the thread is awakened, m_cv.wait reacquires the dataLock before returning. This ensures that the thread has exclusive access to the shared resource again before proceeding.

By passing dataLock to m_cv.wait, you ensure that the thread is properly synchronized and that the shared resource is protected from concurrent access by multiple threads. This prevents race conditions and ensures the correct behavior of the circular buffer.
            */
            m_cv.wait(dataLock,
               [&] {return m_occupiedCells < m_buffer.size(); });
         }

         m_buffer[m_writeIndex] = value; // write to m_buffer
         ++m_occupiedCells; // one more m_buffer cell is occupied
         m_writeIndex = (m_writeIndex + 1) % m_buffer.size();
      } // dataLock's destructor releases the lock on m_mutex here

      m_cv.notify_all(); // notify threads waiting to read from m_buffer
   }

   // return value from m_buffer
   T get() {
      T readValue; // will temporarily hold the next value read 

      // critical section that requires a lock to modify shared data
      {
         // lock on m_mutex to be able to write to m_buffer
         std::unique_lock dataLock{m_mutex};

         // if no data to read, place thread in waiting state
         if (m_occupiedCells == 0) {
            std::cout << "Buffer is empty. Consumer waits.\n\n";

            // wait on the condition variable; the lambda argument 
            // ensures that if the thread gets the processor before
            // there is data in the m_buffer, the thread continues waiting
            m_cv.wait(dataLock, [&]() {return m_occupiedCells > 0; });
         }

         readValue = m_buffer[m_readIndex]; // read value from m_buffer
         m_readIndex = (m_readIndex + 1) % m_buffer.size();
         --m_occupiedCells; // one fewer m_buffer cells is occupied
      } // dataLock's destructor releases the lock on m_mutex here

      m_cv.notify_all(); // notify threads waiting to write to m_buffer
      return readValue;
   }

private:
   std::condition_variable m_cv;
   std::mutex m_mutex;

   std::array<T, BufferSize> m_buffer; // shared m_buffer
   int m_occupiedCells{0}; // count number of buffers used
   int m_writeIndex{0}; // index of next element to write to
   int m_readIndex{0}; // index of next element to read
};

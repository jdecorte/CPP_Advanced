/*
The program below reads a text file with a sequence of "telegrams" (originating from a Belgian digital meter for gas and electricity, each telegram corresponds to
a reading of the meter at a certain time) 
and processes the data to extract the values of the OBIS codes specified in the map obiscodes_used. The processed data is saved to a CSV file "readings_processed.csv".

Redesign this program to use the known design patterns and best practices.
- Use the SOLID principles
- Use the C++ Core Guidelines
- The program should be easy to read and maintain
- The program should be easy to test
- The program should be easy to extend: for example, 
   - it should be easy to add a new input channel iso a text file (e.g. a USB port)
   - it should be easy to add a new output channel (e.g. a JSON file or a database)
   - the choice for the type of input or output channel should be made at runtime

- Add functionality 
   - design in such a way that lines are read, processed and written one by one, so you can add a sleep after each line to simulate real-time processing
   - provide JSON as second output format to test your design using the cereal header only library
   - add error handling and logging
   - design in such a way that the program can be run in multi-threaded mode, where the reading, processing and writing of telegrams are done in parallel
   - now also count the number of telegrams in the input and compare it to the processed telegrams. Show these numbers. 
   
- Use a static code analyzer like cppcheck to check and improve the code quality.

- Think about the original version vs. the redesigned version. 
   - Which design patterns, design principles, C++20 features, ... did you use?
   - What are the advantages and disadvantages of the redesigned version?
   - Would it be adopted by your team members? Why (not)?
*/

#include <iostream>
#include <source_location>
#include <thread>

#include "dataprocessor.h"
#include "circularbuffer.h"

using namespace std;

Logger& logger = Logger::get();

int main(int argc, char const *argv[]) 
{
   try
   {
      if (argc < 3)
      {
         throw std::invalid_argument(ExceptionMsg("Usage: readings <input> <output>", source_location::current().file_name(), std::source_location::current().line(), ""));
      }

      InputProcessorPtr iproc = InputProcessorFactory::get(argv[1]); 
      OutputProcessorPtr oproc = OutputProcessorFactory::get(argv[2]);

      DataProcessor& dataProcessor = DataProcessor::get(iproc, oproc);

      CircularBuffer<string> inputbuffer;
      CircularBuffer<Telegram> outputbuffer;
      // loop over the telegrams and process them  
      // string rawTelegram;
      // Telegram telegram;

      // while ((rawTelegram = iproc->readTelegram()) != "")
      // {   
      //    telegram = dataProcessor.processTelegram(rawTelegram);
      //    oproc->writeTelegram(telegram);
      //    // std::this_thread::sleep_for(10s); // sleep for 10 seconds
      // }

      Telegram dummyTelegram;
      dummyTelegram.push_back({"END", ""});

      auto read = [&inputbuffer, &iproc]()
      {
         cout << "Starting reader\n";
         string rawTelegram;
         int count = 0;

         while ((rawTelegram = iproc->readTelegram()) != "")
         {
            string msg = "Read: " + to_string(++count) + "\n";
            cout << msg;
            inputbuffer.put(rawTelegram);
         }
         inputbuffer.put("END"); // signal end of input
      };

      auto process = [&inputbuffer, &outputbuffer, &dataProcessor,&dummyTelegram]()
      {
         cout << "Starting processor\n";
         string rawTelegram;
         Telegram telegram;
         int count = 0;

         while ((rawTelegram = inputbuffer.get()) != "END")
         {
            string msg = "Process: " + to_string(++count) + "\n";
            cout << msg;
            telegram = dataProcessor.processTelegram(rawTelegram);
            if (telegram.size() > 0) // skip empty telegrams
               outputbuffer.put(telegram);
         }
         outputbuffer.put(dummyTelegram); // signal end of output
      };

      auto write = [&outputbuffer, &oproc]()
      {
         cout << "Starting writer\n";
         Telegram telegram;
         int count = 0;

         telegram = outputbuffer.get();
         while (telegram[0].name != "END")  // dummy telegram signals end of output
         {
            string msg = "Write: " + to_string(++count) + "\n";
            cout << msg;
            oproc->writeTelegram(telegram);
            telegram = outputbuffer.get();
         }
      };
      
      std::thread reader{read};
      std::thread processor{process};
      std::thread writer{write};

      reader.join();
      processor.join();
      writer.join();

      cout << "Number of telegrams read: " << iproc->getCount() << "\n";
      cout << "Number of telegrams processed: " << dataProcessor.getCount() << "\n";

      iproc->close();
      oproc->close();      
   }
   catch(const std::exception& e)
   {
      logger << e.what();
      return 1;
   }

   return 0;
}
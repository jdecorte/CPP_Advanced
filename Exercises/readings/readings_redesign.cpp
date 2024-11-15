// readings_redesing.cpp
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
   
- Use a static code analyzer like cppcheck to check and improve the code quality.

- Think about the original version vs. the redesigned version. 
   - Which design patterns, design principles, modern features, ... did you use?
   - What are the advantages and disadvantages of the redesigned version?
   - Would it be adopted by your team members? Why (not)?
*/

#include <iostream>
#include <source_location>
#include <thread>

#include "dataprocessor.h"

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
      // loop over the telegrams and process them  
      string rawTelegram;
      Telegram telegram;

      logger << "Processing data  ................";

      while ((rawTelegram = iproc->readTelegram()) != "")
      {   
         telegram = dataProcessor.processTelegram(rawTelegram);
         oproc->writeTelegram(telegram);
         // std::this_thread::sleep_for(10s); // sleep for 10 seconds
      }
      oproc->close();      
      iproc->close();
      logger << "Data processed.";
   }
   catch(const std::exception& e)
   {
      logger << e.what();
      return 1;
   }

   return 0;
}
/*
The program below reads a text file with a sequence of "telegrams" (originating from a Belgian digital meter for gas and electricity, each telegram corresponds to
a reading of the meter at a certain time) 
and processes the data to extract the values of the OBIS codes specified in the map obiscodes_used. The processed data is saved to a CSV file "readings_processed.csv".

Redesign this program to the known design patterns and best practices.
- Use the SOLID principles
- Use Modern C++ features
- Use the C++ Core Guidelines
- The program should be easy to read and maintain
- The program should be easy to test
- The program should be easy to extend: for example, 
   - it should be easy to add a new input channel iso a text file (e.g. a database or a metering device)
   - it should be easy to add a new output channel (e.g. a JSON file or a database)
   - the choice for the type of input or output channel should be made at runtime (find a way to do this)

- Add functionality 
   - design in such a way that lines are read, processed and written one by one, so you can add a sleep after each line to simulate real-time processing
   - provide JSON as second output format to test your design using the cereal header only library
   - add error handling and logging
   
- Use a static code analyzer like cppcheck to check and improve the code quality.

- Think about the original version vs. the redesigned version. 
   - Which design patterns, design principles, modern C++ features, ... did you use?
   - What are the advantages and disadvantages of the redesigned version?
   - Would it be adopted by your team members? Why (not)?
*/

#include <iostream>
#include <fstream>
#include <rapidcsv/rapidcsv.h> 
#include <vector>
#include <map>

using namespace std;

// OBIS codes mapping
/*
    {"0-0:1.0.0", "Timestamp"},
    {"0-0:96.3.10", "Switch electricity"},
    {"0-1:24.4.0", "Switch gas"},
    {"0-0:96.1.1", "Meter serial electricity"},
    {"0-1:96.1.1", "Meter serial gas"},
    {"0-0:96.14.0", "Current rate (1=day,2=night)"},
    {"1-0:1.8.1", "Rate 1 (day) - total consumption"},  // total consumption day
    {"1-0:1.8.2", "Rate 2 (night) - total consumption"}, // total consumption night
    {"1-0:2.8.1", "Rate 1 (day) - total production"},   // total injection day
    {"1-0:2.8.2", "Rate 2 (night) - total production"}, // total injection night
    {"1-0:21.7.0", "L1 consumption"},
    {"1-0:41.7.0", "L2 consumption"},
    {"1-0:61.7.0", "L3 consumption"},
    {"1-0:1.6.0", "Positive active maximum demand (A+) total [kW]"},  // peak power
    {"1-0:1.7.0", "All phases consumption"},  // actual consumption
    {"1-0:22.7.0", "L1 production"},
    {"1-0:42.7.0", "L2 production"},
    {"1-0:62.7.0", "L3 production"},
    {"1-0:2.7.0", "All phases production"},  // actual injection
    {"1-0:32.7.0", "L1 voltage"},
    {"1-0:52.7.0", "L2 voltage"},
    {"1-0:72.7.0", "L3 voltage"},
    {"1-0:31.7.0", "L1 current"},
    {"1-0:51.7.0", "L2 current"},
    {"1-0:71.7.0", "L3 current"},
    {"0-1:24.2.3", "Gas consumption"} // total gas consumption
*/

std::map<std::string, std::string> obiscodes_used = 
{
    {"0-0:1.0.0", "timestamp"},
    {"1-0:1.8.1", "total_consumption_day"},  
    {"1-0:1.8.2", "total_consumption_night"}, 
    {"1-0:2.8.1", "total_injection_day"},   
    {"1-0:2.8.2", "total_injection_night"}, 
    {"1-0:1.6.0", "peak_power"},  
    {"1-0:1.7.0", "actual_consumption"},  
    {"1-0:2.7.0", "actual_injection"},  
    {"0-1:24.2.3", "total_gas_consumption"}
};

string removeZero(string str) 
{ 
    // Count leading zeros 
    int i = 0; 
    while (str[i] == '0') 
        i++; 
  
    // The erase function removes i characters 
    // from given index (0 here) 
    str.erase(0, i); 
  
    return str; 
} 

#include <cerrno>
#include <cstring>


int main() 
{
   try
   {
      // input
      ifstream file("readings.txt");

      cout << "Processing data..." << endl;
      
      // output header row
      string csv;
      for (auto const& x : obiscodes_used) 
      {
         csv += x.second + ",";            
      }
      csv[csv.size()-1] = '\n';
      
      // process data
      string telegram;

      map<string,string> values;

      while (getline(file, telegram))
      {
         string output;
         if (telegram.size() != 1298) // Invalid telegram size          
            continue;  
         for (auto const& c : obiscodes_used)
         {
            size_t pos = telegram.find(c.first);
            if (pos != std::string::npos)
            {
               int pos1 = telegram.find("(", pos);
               int pos2;
               if (c.second == "timestamp")
               {
                  pos2 = telegram.find(")", pos1);
                  // remove the last character ("S") from the timestamp  
                  values[c.second] = telegram.substr(pos1+1, pos2 - pos1 - 2);  
               }
               else
               {
                  pos2 = telegram.find("*", pos1);
                  if (c.second == "total_gas_consumption" || c.second == "peak_power")
                  {
                     pos1 = telegram.find("(", pos1+1);
                  }
                  values[c.second] = removeZero(telegram.substr(pos1+1, pos2 - pos1 - 1));
               }
            }
            else
            {
               values[c.second] = "";
            }
            output += values[c.second] + ",";    
            values.clear();     
         }
         output[output.size()-1] = '\n';
         csv += output;
      }
      file.close();

      stringstream sstream(csv);
      rapidcsv::Document doc(sstream, rapidcsv::LabelParams(0, 0));
      doc.Save("readings_processed.csv");
   }
   catch(const std::exception& e)
   {
      cerr << e.what() << '\n';
      return 1;
   }
   return 0;
}
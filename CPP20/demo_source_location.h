#pragma once
#include <iostream>
#include <source_location>

using namespace std;

void log_with_macros(const char* message, const char* file = __FILE__, int line = __LINE__) 
{
    std::cout << "Log (macros): \n" << message << " [file: " << file << ", line: " << line << "]" << std::endl << std::endl;
}

void log_with_source_location(const char* message, const std::source_location& location = std::source_location::current())
{
    std::cout << "Log (source_location):\n " << message
              << " [file: " << location.file_name()
              << ", line: " << location.line()
              << ", function: " << location.function_name() << "]" << std::endl;
}

void demo_source_location()
{
    std::cout << "*** C++20: SOURCE_LOCATION ***" << std::endl;
    log_with_macros("Hello from macros");
    log_with_source_location("Hello from source_location");
}

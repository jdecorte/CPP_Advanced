#ifndef APP_H
#define APP_H

#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <format>
#include <gsl/assert>
#include <chrono>

struct TelegramElement
{
    std::string name; // timestamp, total_consumption_day, total_consumption_night, total_injection_day, total_injection_night, peak_power, actual_consumption, actual_injection, total_gas_consumption
    std::string value;
};

using Telegram = std::vector<TelegramElement>;

// OBIS codes mapping
// see https://www.promotic.eu/en/pmdoc/Subsystems/Comm/PmDrivers/IEC62056_OBIS.htm#:~:text=The%20OBIS%20code%20identifies%20the,variant%20is%20the%20EDIS%20code
// for a full description of the OBIS codes

const std::vector<std::pair<std::string, std::string>> obiscodes = // vector preserves order of insertion (unlike map)
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

std::string ExceptionMsg(const std::string& msg, const std::string& sourceFile, const int& sourceLine, const std::string& what);

class Logger
{
public:
    static Logger& get()
    {
        static Logger instance;
        return instance;
    }

    Logger& operator<<(const std::string& msg)
    {
        auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
        // C++20 ONLY
        // Convert to local time zone
        // auto local_time = std::chrono::zoned_time{std::chrono::current_zone(), now};    

        // std::cout << fmt::format("{0:%Y-%m-%d %H:%M:%S} - {1}", local_time, msg) << std::endl;

        std::cout << msg << std::endl;
        return *this;
    }
};

#endif // APP_H
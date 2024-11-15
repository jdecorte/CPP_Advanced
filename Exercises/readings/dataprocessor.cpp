#include "dataprocessor.h"

using namespace std;

DataProcessor& DataProcessor::get(const InputProcessorPtr& iproc, const OutputProcessorPtr& oproc) // singleton pattern
{
    static DataProcessor dataprocessor(iproc, oproc);
    return dataprocessor;
}

bool DataProcessor::checkTelegram(const std::string& telegram) const noexcept
{
    // Can be extended to check the checksum of the telegram
    return telegram.size() == 1298;
}

Telegram DataProcessor::processTelegram(const std::string& rawTelegram) noexcept
{
    Telegram telegram;

    if (!checkTelegram(rawTelegram)) // Invalid telegram size
        return telegram; // empty telegram

    ++count;

    for (auto const& c : obiscodes)
    {
        size_t pos = rawTelegram.find(c.first);
        if (pos != std::string::npos)
        {
            int pos1 = rawTelegram.find("(", pos);
            int pos2;
            if (c.second == "timestamp")
            {
                pos2 = rawTelegram.find(")", pos1);
                // remove the last character ("S") from the timestamp
                TelegramElement te{c.second, rawTelegram.substr(pos1+1, pos2 - pos1 - 2)};
                telegram.push_back(te);
            }
            else
            {
                pos2 = rawTelegram.find("*", pos1);
                if (c.second == "total_gas_consumption" || c.second == "peak_power")
                {
                    pos1 = rawTelegram.find("(", pos1+1);
                }
                TelegramElement te{c.second, removeLeadingZeros(rawTelegram.substr(pos1+1, pos2 - pos1 - 1))};
                telegram.push_back(te);
            }
        }
    }
    return telegram;
}

std::string DataProcessor::removeLeadingZeros(std::string str) const noexcept
{
    // Count leading zeros
    int i = 0;
    while (str[i] == '0')
        i++;

    // The erase function removes i characters
    // from given index (0 here)
    str.erase(0, i);

    return str;
}   // namespace std




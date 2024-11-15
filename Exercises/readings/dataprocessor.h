#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include "inputprocessor.h"
#include "outputprocessor.h"

#include "app.h"

class DataProcessor 
{
public:
    ~DataProcessor() {};

    static DataProcessor& get(const InputProcessorPtr&, const OutputProcessorPtr&); // singleton pattern
    Telegram processTelegram(const std::string& rawTelegram) noexcept;
    int getCount() const noexcept {return count;}

protected:
    DataProcessor(const InputProcessorPtr& iproc, const OutputProcessorPtr& oproc): inputProcessor(std::move(iproc)), outputProcessor(std::move(oproc)) {};

private:

    bool checkTelegram(const std::string& telegram) const noexcept;
    std::string removeLeadingZeros(std::string str) const noexcept;

    const int telegramSize = 1298;
    int count = 0;
    InputProcessorPtr inputProcessor;
    OutputProcessorPtr outputProcessor;
};
#endif // DATAPROCESSOR_H
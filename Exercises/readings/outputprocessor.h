#ifndef OUTPUTPROCESSOR_H
#define OUTPUTPROCESSOR_H

#include <sstream>
#include <fstream>
#include <memory>
#include <map>
#include <rapidcsv/rapidcsv.h> 

#include "app.h"

class OutputProcessor 
{
public:
    virtual ~OutputProcessor() {}
    virtual void writeTelegram(const Telegram& telegram) = 0;
    virtual void close() = 0;
protected:
    OutputProcessor() {} // creation only through factory
private:
    virtual void open() = 0;
};

using OutputProcessorPtr = std::shared_ptr<OutputProcessor>;

class OutputProcessorFactory
{
public:
   static std::map<std::string, OutputProcessorPtr> outputProcessors;   
   static OutputProcessorPtr get(const std::string& type);
};

// Concrete classes for output processors

class CSVOutputProcessor : public OutputProcessor
{
protected:
    CSVOutputProcessor() {open();}
    friend class OutputProcessorFactory;  
public:
    void writeTelegram(const Telegram& telegram) override; 
    void close() override; 

private:
    void open() override;
    // std::string csv;
    std::stringstream csvstream;
    const std::string filename = "readings_processed.csv";
    std::unique_ptr<rapidcsv::Document> doc;
};

class JSONOutputProcessor : public OutputProcessor
{
protected:
    JSONOutputProcessor() {open();}
    friend class OutputProcessorFactory;  
public:
    void writeTelegram(const Telegram& telegram) override; 
    void close() override; 

protected:
    std::fstream file;

private:
    void open() override;
    std::stringstream csvstream;
    const std::string filename = "readings_processed.json";
};

#endif // OUTPUTPROCESSOR_H
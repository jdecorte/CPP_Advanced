// inputprocessor.cpp
#include <filesystem>
#include <source_location>

#include "inputprocessor.h"

void FileInputProcessor::close() 
{
    file.close();
} 

std::map<std::string, InputProcessorPtr> InputProcessorFactory::inputProcessors = {};  // initialize static member

InputProcessorPtr InputProcessorFactory::get(const std::string& type) // ensure only one instance of each input processor (singleton pattern)
{
    if (type == "file")
    {
        if (!inputProcessors.contains(type))  // C++20
        {
            inputProcessors[type] = std::shared_ptr<FileInputProcessor>(new FileInputProcessor()); // make_shared not possible due to protected constructor
        }
        return inputProcessors[type];
    }
    else
    {
        throw std::invalid_argument(ExceptionMsg("Invalid input channel: " + type,  std::source_location::current().file_name(), std::source_location::current().line(), ""));
    }
}

// FileInputProcessor implementation

void FileInputProcessor::open() 
{
    if (!std::filesystem::exists(filename))
    {
        throw std::runtime_error(ExceptionMsg("File does not exist: " + filename,  std::source_location::current().file_name(), std::source_location::current().line(), ""));
    }
    else
    {
        file.open(filename);
    }
}

std::string FileInputProcessor::readTelegram() 
{
    if (getline(file, telegram))
    {
        ++count;
        return telegram;
    }
    else
        return "";   
}


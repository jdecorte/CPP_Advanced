#include <source_location>
#include <filesystem>

#include "cereal/archives/json.hpp"
#include "cereal/types/vector.hpp"
#include "outputprocessor.h"

using namespace std;
   
std::map<std::string, OutputProcessorPtr> OutputProcessorFactory::outputProcessors = {};  // initialize static member

OutputProcessorPtr OutputProcessorFactory::get(const std::string& type) // ensure only one instance of each output processor (singleton pattern)
{
    if (type == "csv")
    {
        if (!outputProcessors.contains(type))  // C++20
        {
            outputProcessors[type] = std::shared_ptr<CSVOutputProcessor>(new CSVOutputProcessor()); // make_shared not possible due to protected constructor
        }
    }
    else if (type == "json")
    {
        if (!outputProcessors.contains(type))  // C++20
        {
            outputProcessors[type] = std::shared_ptr<JSONOutputProcessor>(new JSONOutputProcessor()); // make_shared not possible due to protected constructor
        }
    }
    else
    {
        throw std::runtime_error(ExceptionMsg(std::string("OutputProcessorFactory::get() unknown type: ") + type,  std::source_location::current().file_name(), std::source_location::current().line(),""));
    }
    return outputProcessors[type];
}

void CSVOutputProcessor::open()  
{
    try
    {
        string csv;
        if (!std::filesystem::exists(filename))
        {
            ofstream file(filename); // create file (if it does not exist), rapidcsv::Document does not create file
        }
        doc = std::make_unique<rapidcsv::Document>(filename);
        for (auto const& x : obiscodes)  
        {
            csv += x.second + ",";
        }
        csv[csv.size()-1] = '\n';
        csvstream << csv;

    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(ExceptionMsg("Error opening file: " + filename,  std::source_location::current().file_name(), std::source_location::current().line(), e.what()));
    }
};

void CSVOutputProcessor::writeTelegram(const Telegram& telegram)  
{
    // add telegram to csvstream
    string csv;
    std::ranges::for_each(telegram, [&csv,this](const auto& x) {csv.append(x.value + ",");});
    csvstream << csv.substr(0,csv.size()-2) << std::endl; // replace last , by \n
}

void CSVOutputProcessor::close()  
{
    try
    {
        doc = std::make_unique<rapidcsv::Document>(csvstream, rapidcsv::LabelParams(0, 0));
        doc->Save(filename);
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(ExceptionMsg("Error saving file: " + filename,  std::source_location::current().file_name(), std::source_location::current().line(), e.what()));
    }   
}

template <typename Archive> // template function for serialization of TelegramElement in cereal JSON format
void serialize(Archive& archive, TelegramElement& te)
{
    archive(cereal::make_nvp(te.name, te.value));
}

void JSONOutputProcessor::open()  
{
    try
    {
        file.open(filename,ios::out);
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error(ExceptionMsg("Error opening file: " + filename,  std::source_location::current().file_name(), std::source_location::current().line(), e.what()));
    }
}

void JSONOutputProcessor::writeTelegram(const Telegram& telegram)  
{
    stringstream s;
    // add serialized telegram to json file
    {
        cereal::JSONOutputArchive archive{s};
        archive(cereal::make_nvp("telegram", telegram)); // serialize records
    } // archive out-of-scope to ensure flush
    string jsonLijnen = s.str();
    file << jsonLijnen << std::endl;
}

void JSONOutputProcessor::close()  
{
    try
    {
        file.close();
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Error saving file: " + filename + " at " + std::source_location::current().file_name() + ":" + std::to_string(std::source_location::current().line()) + " " + e.what());
    }   
};
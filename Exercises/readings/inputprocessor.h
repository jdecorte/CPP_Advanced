#ifndef INPUTPROCESSOR_H
#define INPUTPROCESSOR_H

#include <fstream>
#include <memory>
#include <map>
#include "app.h"

class InputProcessor
{
public:
   virtual ~InputProcessor() {} 
   virtual void open() = 0;
   virtual std::string readTelegram() = 0;
   virtual void close() = 0;  
   int getCount() const noexcept {return count;}
protected:
   InputProcessor() {} // creation only through factory
   int count = 0;
};

using InputProcessorPtr = std::shared_ptr<InputProcessor>;

class InputProcessorFactory
{
public:
   static std::map<std::string, InputProcessorPtr> inputProcessors;   
   static InputProcessorPtr get(const std::string& type);
};

// Concrete classes for input processors

class FileInputProcessor : public InputProcessor
{
protected:
   FileInputProcessor() {open();} // creation only through factory
   friend class InputProcessorFactory;  
public:
   void open() override;
   std::string readTelegram() override;
   void close() override;

private:
   const std::string filename = "readings.txt";
   std::ifstream file;
   std::string telegram;
};

#endif // INPUTPROCESSOR_H

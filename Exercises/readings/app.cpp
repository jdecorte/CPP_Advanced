#include "app.h"

std::string ExceptionMsg(const std::string& msg, const std::string& sourceFile, const int& sourceLine, const std::string& what)
{
    return msg + " at " + sourceFile + ": line " + std::to_string(sourceLine) + " " + what;
}
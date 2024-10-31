#ifndef LIST_H
#define LIST_H

#include <sstream>

enum class OutputFormat
{
    markdown,
    html
};

struct ListStrategy
{
    virtual void start(std::ostringstream& oss) {}; // Interface Segregation Principle
    virtual void add_list_item(std::ostringstream& oss,const std::string& item)=0;
    virtual void end(std::ostringstream& oss) {};   // Interface Segregation Principle
};

struct HtmlListStrategy : ListStrategy
{
    void start(std::ostringstream& oss) override
    {
        oss << "<ul>\n";
    }
    void end(std::ostringstream& oss) override
    {
        oss << "</ul>\n";
    }
    void add_list_item(std::ostringstream& oss, const std::string& item) override
    {
        oss << " <li>" << item << "</li>\n";
    }
};

struct MarkdownListStrategy : ListStrategy
{
    void add_list_item(std::ostringstream& oss,const std::string& item) override
    {
        oss << " * " << item << "\n";
    }
};

#endif // LIST_H

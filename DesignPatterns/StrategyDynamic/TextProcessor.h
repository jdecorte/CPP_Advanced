#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <vector>
#include <memory>
#include "list.h"
using namespace std;

struct TextProcessor
{
    void append_list(const vector<string>& items)
    {
        list_strategy->start(oss);
        for (const auto& item : items)
            list_strategy->add_list_item(oss, item);
        list_strategy->end(oss);
    }
    string str() {return oss.str();}
    void set_output_format(const OutputFormat format)
    {
        switch(format)
        {
        case OutputFormat::markdown:
            list_strategy = make_unique<MarkdownListStrategy>();
            break;
        case OutputFormat::html:
            list_strategy = make_unique<HtmlListStrategy>();
            break;
        }
    }
private:
    ostringstream oss;
    unique_ptr<ListStrategy> list_strategy;
};
#endif // TEXTPROCESSOR_H

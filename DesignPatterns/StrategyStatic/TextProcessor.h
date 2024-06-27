#ifndef TEXTPROCESSOR_H
#define TEXTPROCESSOR_H

#include <vector>
#include <memory>
#include <sstream>
using namespace std;

template <typename LS>
struct TextProcessor
{
    void append_list(const vector<string> items)
    {
        list_strategy.start(oss);
        for (auto& item : items)
            list_strategy.add_list_item(oss, item);
        list_strategy.end(oss);
    }
    string str() {return oss.str();}
private:
    ostringstream oss;
    LS list_strategy; // strategy instantiated here
};
#endif // TEXTPROCESSOR_H

#include <iostream>
#include <cstring>
#include "TextProcessor.h"

using namespace std;

int main(int argc, const char *argv[])
{
    OutputFormat of;
    if (argc < 2)
        of = OutputFormat::html;
    else
        if (!strcmp(argv[1],"markdown"))
            of = OutputFormat::markdown;
        else
            of = OutputFormat::html;

    TextProcessor tp;
    tp.set_output_format(of);
    tp.append_list({"tractor", "combine harvester", "soil cultivator"});

    cout << tp.str() << endl;
    return 0;
}

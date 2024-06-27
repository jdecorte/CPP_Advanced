#include <iostream>
#include <cstring>
#include "TextProcessor.h"
#include "list.h"

using namespace std;

int main()
{
    // markdown
    TextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list({"tractor", "combine harvester", "soil cultivator"});
    cout << tpm.str() << endl;

    // html
    TextProcessor<HtmlListStrategy> tph;
    tph.append_list({"tractor", "combine harvester", "soil cultivator"});
    cout << tph.str() << endl;

    return 0;
}

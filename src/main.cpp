#include <vector>
#include <string>

#include "application.h"

int main(int argc, char *argv[])
{
    using namespace std;
    using namespace bitrix_tools;

    auto args = vector<string>();
    for (int i = 0; i < argc; ++i)
    {
        args.push_back(string(argv[i]));
    }

    return Application{args}.run();
}
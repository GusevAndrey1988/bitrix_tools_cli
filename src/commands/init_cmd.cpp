#include "commands/init_cmd.h"

#include <iostream>

namespace bitrix_tools
{
    InitCmd::InitCmd(const Config &config) : Command(config)
    {
    }

    void InitCmd::execute()
    {
        std::cout << "run init cmd" << std::endl;
    }
}

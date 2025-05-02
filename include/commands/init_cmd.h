#pragma once

#include "command.h"
#include "config.h"

#include <string>
#include <filesystem>

namespace bitrix_tools
{
    class InitCmd : public Command
    {
    public:
        explicit InitCmd(const Config &config);

        void execute() override;
    };
}

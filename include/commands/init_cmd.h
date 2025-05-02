#pragma once

#include "command.h"
#include "command_factory.h"
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

    class InitCmdFactory : public CommandFactory
    {
    public:
        explicit InitCmdFactory(const Config &config);

        Command::CommandPtr create() override;

    private:
        std::filesystem::path path_to_template_;
    };
}

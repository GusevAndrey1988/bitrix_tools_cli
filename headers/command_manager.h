#pragma once

#include <map>
#include <string>
#include <memory>

#include "command_factory.h"

namespace bitrix_tools
{
    class CommandManager
    {
    public:
        using CommandFactoryMap = std::map<std::string,
                                        CommandFactory::CommandFactoryPtr>;

        void registerFactory(const std::string &command_name,
                            CommandFactory::CommandFactoryPtr factory);

        /**
         * @return true if the command was executed, false otherwise
         */
        bool execute(const std::string &command_name);

    private:
        CommandFactoryMap command_factory_map_;
    }; 
}

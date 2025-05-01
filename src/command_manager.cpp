#include "command_manager.h"

#include <stdexcept>

namespace bitrix_tools
{
    void CommandManager::registerFactory(const std::string &command_name,
                                         CommandFactory::CommandFactoryPtr factory)
    {
        if (command_factory_map_.find(command_name) != command_factory_map_.end())
        {
            throw std::runtime_error("Command already registered");
        }
        command_factory_map_[command_name] = factory;
    }

    bool CommandManager::execute(const std::string &command_name)
    {
        auto factory_iter = command_factory_map_.find(command_name);
        if (factory_iter == command_factory_map_.end())
        {
            return false;
        }

        Command::CommandPtr command = factory_iter->second->create();
        command->execute();

        return true;
    }
}

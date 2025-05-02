#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>

#include "application.h"

#include "config.h"

#include "command_manager.h"

#include "commands/init_cmd.h"

#include "json_parser.h"

namespace bitrix_tools
{
    Application::Application(const std::vector<std::string> &args)
        : config_(Config(args, JsonParser{})), args_(args)
    {
    }

    int Application::run()
    {
        using namespace std;
        using namespace bitrix_tools;

        if (!bitrixToolsJsonFileExists())
        {
            cout
                << "Файл "
                << "\"" << config_.getBitrixToolsJsonFileName() << "\""
                << " не найден. Выполните команду init."
                << endl;

            return EXIT_SUCCESS;
        }

        shared_ptr<CommandManager> command_manager = make_shared<CommandManager>();

        // todo: переименовать headers -> include
        // todo: добавить шаблонизатор
        // todo: реализовать команду init

        command_manager->registerFactory("init", CommandFactory::CommandFactoryPtr(new InitCmdFactory(config_)));

        if (args_.size() > 1)
        {
            string command = args_[1];

            if (command_manager->execute(command))
            {
            }
        }

        return EXIT_SUCCESS;
    }

    bool Application::bitrixToolsJsonFileExists() const
    {
        using namespace std;

        auto bitrix_tools_json_status = filesystem::status(
            config_.getRootPath() + config_.getBitrixToolsJsonFileName());

        return bitrix_tools_json_status.type() != filesystem::file_type::not_found;
    }
}

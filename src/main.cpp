#include <iostream>
#include <filesystem>
#include <exception>
#include <vector>
#include <string>

#include "config.h"
#include "command_manager.h"

#include "commands/init_cmd.h"

int main(int argc, char *argv[])
{
    using namespace std;

    auto args = vector<string>();
    for (int i = 0; i < argc; ++i) {
        args.push_back(string(argv[i]));
    }

    Config config = Config(args);

    auto bitrix_tools_json_status = filesystem::status(
        config.getRootPath() + config.getBitrixToolsJsonFileName());

    if (bitrix_tools_json_status.type() == filesystem::file_type::not_found) {
        cout
            << "Файл \""
            << config.getBitrixToolsJsonFileName()
            << "\" не найден. Выполните команду init."
            << endl;
    }

    shared_ptr<CommandManager> command_manager = make_shared<CommandManager>();

    // todo: реализовать команду init
    // todo: добавить namespaces
    // todo: добавить класс Application
    // ...

    command_manager->registerFactory("init", CommandFactory::CommandFactoryPtr(new InitCmdFactory(config)));

    if (args.size() > 1) {
        string command = args[1];

        if (command_manager->execute(command)) {
            return EXIT_SUCCESS;
        }

        return EXIT_SUCCESS;
    }
}
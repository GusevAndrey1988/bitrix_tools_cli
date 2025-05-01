#include <iostream>
#include <filesystem>
#include <exception>
#include <vector>
#include <string>

#include "config.h"
#include "command_manager.h"

#include "commands/create_default_config_cmd.h"
#include "commands/generate_component_cmd.h"

std::filesystem::path get_data_path();
std::filesystem::path get_templates_path();

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

    // todo: добавить зависимость Config в Command
    // todo: реализовать команду init
    // todo: добавить namespaces
    // todo: добавить класс Application
    // ...

    const filesystem::path template_name = "default-config.json.template";
    const auto path_to_template = get_templates_path() /= template_name;
    command_manager->registerFactory("init", CommandFactory::CommandFactoryPtr(
            new CreateDefaultConfigCmdFactory(path_to_template)));

    command_manager->registerFactory("make:component", CommandFactory::CommandFactoryPtr(
            new GenerateComponentCmdFactory(get_templates_path() /= "component")));

    string command = argv[1];

    if (command_manager->execute(command)) {
        return EXIT_SUCCESS;
    }
}

std::filesystem::path get_data_path()
{
    const std::filesystem::path app_data_path =
            std::filesystem::read_symlink("/proc/self/exe").parent_path() /= "data";
        
    if (std::filesystem::is_directory("/etc/bitrix_tools_cli")) {
        return "/etc/bitrix_tools_cli";
    } else if (std::filesystem::is_directory("/opt/bitrix_tools_cli")) {
        return "/opt/bitrix_tools_cli";
    } else if (std::filesystem::is_directory(app_data_path)) {
        return app_data_path;
    }

    throw std::runtime_error("Не найдена папка с данными");
}

std::filesystem::path get_templates_path()
{
    const auto path_to_templates = get_data_path() /= "templates";
    if (!std::filesystem::is_directory(path_to_templates)) {
        throw std::runtime_error("Не найдена папка с шаблонами");
    }

    return path_to_templates;
}

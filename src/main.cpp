#include <iostream>
#include <filesystem>
#include <exception>

#include "command_manager.h"

#include "commands/create_default_config_cmd.h"

std::filesystem::path get_data_path();
std::filesystem::path get_templates_path();

void print_help();

int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_help();
        return EXIT_SUCCESS;
    }

    const std::filesystem::path template_name = "default_config.template";
    const auto path_to_template = get_templates_path() /= template_name;

    std::shared_ptr<CommandManager> command_manager = std::make_shared<CommandManager>();
    command_manager->registerFactory("default-config", CommandFactory::CommandFactoryPtr(
            new CreateDefaultConfigCmdFactory(path_to_template)));

    std::string command = argv[1];

    if (command_manager->execute(command)) {
        return EXIT_SUCCESS;
    }

    if (command == "make:component") {
        std::cout << "make:component" << std::endl;
    } else if (command == "make:module") {
        std::cout << "make:module" << std::endl;
    } else {
        std::cout << "Неизвестная команда" << std::endl;
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

void print_help()
{
    std::cout << "default-config\t" 
            << "Создаёт файл конфигурации по умолчанию" << std::endl;

    std::cout << "make:component\t"
            << "Генерация компонента" << std::endl;

    std::cout << "make:module\t" <<"Генерация модуля" << std::endl;
}
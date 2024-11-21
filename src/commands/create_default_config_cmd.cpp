#include "commands/create_default_config_cmd.h"
#include "template.h"

#include <filesystem>
#include <iostream>

CreateDefaultConfigCmd::CreateDefaultConfigCmd(const std::filesystem::path &path_to_template)
    : path_to_template_(path_to_template)
{
    if (!path_to_template.has_filename()) {
        throw std::runtime_error("Неверный путь к шаблону");
    }

    if (!std::filesystem::is_regular_file(getPathToTemplate())) {
        throw std::runtime_error("Не найден шаблон");
    }
}

void CreateDefaultConfigCmd::execute()
{
    // TODO: check bitrix folder exists
    std::filesystem::copy_file(getPathToTemplate(), std::filesystem::current_path() /=
            Template::makeFileNameFromTemplatePath(getPathToTemplate()));
}

std::filesystem::path CreateDefaultConfigCmd::getPathToTemplate() const
{
    return path_to_template_;
}

CreateDefaultConfigCmdFactory::CreateDefaultConfigCmdFactory(std::filesystem::path path_to_template)
    : path_to_template_(path_to_template)
{
}

Command::CommandPtr CreateDefaultConfigCmdFactory::create()
{
    return Command::CommandPtr(new CreateDefaultConfigCmd(path_to_template_));
}

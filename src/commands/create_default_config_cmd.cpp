#include "commands/create_default_config_cmd.h"

#include <filesystem>
#include <iostream>

const std::string CreateDefaultConfigCmd::FILE_NAME = "default_config.json";

CreateDefaultConfigCmd::CreateDefaultConfigCmd(const std::filesystem::path &path_to_template)
    : path_to_template_(path_to_template)
{
}

void CreateDefaultConfigCmd::execute()
{
    if (!std::filesystem::is_regular_file(getPathToTemplate())) {
        throw std::runtime_error("Не найден шаблон");
    }

    std::filesystem::copy_file(getPathToTemplate(),
            std::filesystem::current_path() /= FILE_NAME);
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

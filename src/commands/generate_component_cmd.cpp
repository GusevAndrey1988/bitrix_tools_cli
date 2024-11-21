#include "commands/generate_component_cmd.h"

#include <stdexcept>
#include <list>
#include <algorithm>

GenerateComponentCmd::GenerateComponentCmd(
        const std::filesystem::path &path_to_component_template)
            : path_to_component_template_(path_to_component_template)
{
    if (!std::filesystem::is_directory(path_to_component_template_)) {
        throw std::runtime_error("Неверный путь к директории с шаблонами");
    }

    if (!std::filesystem::exists(path_to_component_template_)) {
        throw std::runtime_error("Директории с шаблонами не существует");
    }
}

void GenerateComponentCmd::execute()
{
    std::list<std::string> pathToTemplateFiles;

    for (const auto &entry : std::filesystem::recursive_directory_iterator(
            getPathToComponentTemplate())) {
        if (!entry.is_regular_file()) {
            continue;
        }

        pathToTemplateFiles.push_back(entry.path());
    }

    //TODO: copy files to destination folder
}

std::filesystem::path GenerateComponentCmd::getPathToComponentTemplate() const
{
    return path_to_component_template_;
}


GenerateComponentCmdFactory::GenerateComponentCmdFactory(
        const std::filesystem::path &path_to_component_template)
            : path_to_component_template_(path_to_component_template)
{
}

Command::CommandPtr GenerateComponentCmdFactory::create()
{
    return Command::CommandPtr(new GenerateComponentCmd(path_to_component_template_));
}
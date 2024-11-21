#pragma once

#include "command.h"
#include "command_factory.h"

#include <filesystem>

class GenerateComponentCmd : public Command {
    public:
        explicit GenerateComponentCmd(const std::filesystem::path &path_to_component_template);

        void execute() override;

    private:
        std::filesystem::path path_to_component_template_;

        std::filesystem::path getPathToComponentTemplate() const;
};

class GenerateComponentCmdFactory : public CommandFactory {
    public:
        explicit GenerateComponentCmdFactory(
                const std::filesystem::path &path_to_component_template);

        Command::CommandPtr create() override;

    private:
        std::filesystem::path path_to_component_template_;
};
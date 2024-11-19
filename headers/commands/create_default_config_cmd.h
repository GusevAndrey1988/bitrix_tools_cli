#pragma once

#include "command.h"
#include "command_factory.h"

#include <string>
#include <filesystem>

class CreateDefaultConfigCmd : public Command {
    public:
        CreateDefaultConfigCmd(const std::filesystem::path &path_to_template);

        void execute() override;

    private:
        static const std::string FILE_NAME;

        std::filesystem::path path_to_template_;

        std::filesystem::path getPathToTemplate() const;
};

class CreateDefaultConfigCmdFactory : public CommandFactory {
    public:
        explicit CreateDefaultConfigCmdFactory(std::filesystem::path path_to_template);

        Command::CommandPtr create() override;

    private:
        std::filesystem::path path_to_template_;
};
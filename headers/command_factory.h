#pragma once

#include <memory>

#include "command.h"

class CommandFactory {
    public:
        using CommandFactoryPtr = std::shared_ptr<CommandFactory>;

        virtual ~CommandFactory() = default;

        virtual Command::CommandPtr create() = 0;
};
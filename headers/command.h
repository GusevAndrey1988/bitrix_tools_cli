#pragma once

#include <memory>

class Command {
    public:
        using CommandPtr = std::unique_ptr<Command>;

        virtual ~Command() = default;

        virtual void execute() = 0;
};
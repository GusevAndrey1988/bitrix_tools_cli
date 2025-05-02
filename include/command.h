#pragma once

#include <memory>

#include "config.h"

namespace bitrix_tools
{
    class Command
    {
    public:
        using CommandPtr = std::unique_ptr<Command>;

        explicit Command(const Config &config);

        virtual ~Command() = default;

        virtual void execute() = 0;

    protected:
        const Config &getConfig() const;

    private:
        const Config &config_;
    };
}

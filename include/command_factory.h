#pragma once

#include <memory>

#include "command.h"
#include "config.h"

namespace bitrix_tools
{
    class CommandFactory
    {
    public:
        using CommandFactoryPtr = std::shared_ptr<CommandFactory>;

        CommandFactory(const Config &config);

        virtual ~CommandFactory() = default;

        virtual Command::CommandPtr create() = 0;

    protected:
        const Config &getConfig() const;

    private:
        const Config &config_;
    };
}

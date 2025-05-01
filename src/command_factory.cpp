#include "command_factory.h"

namespace bitrix_tools
{
    CommandFactory::CommandFactory(const Config &config) : config_(config)
    {
    }

    const Config &CommandFactory::getConfig() const
    {
        return config_;
    }
}

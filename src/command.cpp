#include "command.h"

namespace bitrix_tools
{
    Command::Command(const Config &config) : config_(config)
    {
    }

    const Config &Command::getConfig() const
    {
        return config_;
    }
}

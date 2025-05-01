#include "command.h"

Command::Command(const Config &config) : config_(config)
{
}

const Config& Command::getConfig() const
{
    return config_;
}

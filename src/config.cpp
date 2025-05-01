#include "config.h"
#include <iostream>
#include <filesystem>

namespace bitrix_tools
{
    Config::Config(const std::vector<std::string> &args)
    {
        app_path_ = args[0];
    }

    const std::string Config::getRootPath() const
    {
        return std::filesystem::path(app_path_).remove_filename();
    }

    const std::string Config::getConfigPath() const
    {
        return getRootPath() + "config/";
    }

    const std::string Config::getTemplatesPath() const
    {
        return getRootPath() + "data/";
    }

    const std::string Config::getBitrixToolsJsonFileName() const
    {
        return "bitrix-tools.json";
    }

    const std::string Config::getPathToBitrixToolsJson() const
    {
        return getTemplatesPath() + getBitrixToolsJsonFileName();
    }
}

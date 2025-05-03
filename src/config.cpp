#include "config.h"
#include <iostream>
#include <filesystem>

namespace bitrix_tools
{
    const std::string Config::MAIN_CONFIG_FILE_NAME = "config.json";
    const std::string Config::BITRIX_TOOLS_JSON_FILE_NAME = "bitrix-tools.json";

    Config::Config(int argc, const char *argv[], const JsonParser &json_parser)
        : json_parser_{json_parser}
    {
        app_path_ = argv[0];
    }

    std::string Config::getRootPath() const
    {
        return std::filesystem::path(app_path_).remove_filename();
    }

    std::string Config::getConfigPath() const
    {
        // todo
        return "./config/";
    }

    std::string Config::getTemplatesPath() const
    {
        // todo
        return "./data/";
    }

    std::string Config::getBitrixToolsJsonFileName() const
    {
        return BITRIX_TOOLS_JSON_FILE_NAME;
    }

    std::string Config::getPathToBitrixToolsJson() const
    {
        return getTemplatesPath() + getBitrixToolsJsonFileName();
    }

    void Config::parseJson()
    {
        props_ = json_parser_.parse(getConfigPath() + MAIN_CONFIG_FILE_NAME);
    }

    std::string Config::getPathToModuleDir(const WorkLocation &location, const std::string &vendor) const
    {
        return getRootPath() + work_location_to_string(location) + "/modules/" + vendor + "/";
    }

    std::string Config::getPathToComponentDir(const WorkLocation &location, const std::string &vendor) const
    {
        return getRootPath() + work_location_to_string(location) + "/components/" + vendor + "/";
    }

    std::string Config::getPathToJsExtensionDir(const WorkLocation &location, const std::string &vendor) const
    {
        return getRootPath() + work_location_to_string(location) + "/js/" + vendor + "/";
    }

    std::string Config::getDefaultVendorName() const
    {
        auto vendor = props_.find("default_vendor");
        if (vendor == props_.end())
        {
            return "vendor";
        }
        return vendor->second;
    }

    WorkLocation Config::getDefaultModuleLocation() const
    {
        auto module_location = props_.find("default_module_location");
        if (module_location == props_.end())
        {
            return WorkLocation::LOCAL;
        }
        return string_to_work_location(module_location->second);
    }

    WorkLocation Config::getDefaultComponentLocation() const
    {
        auto module_location = props_.find("default_component_location");
        if (module_location == props_.end())
        {
            return WorkLocation::LOCAL;
        }
        return string_to_work_location(module_location->second);
    }

    WorkLocation Config::getDefaultJsExtensionLocation() const
    {
        auto js_extension_location = props_.find("default_js_extension_location");
        if (js_extension_location == props_.end())
        {
            return WorkLocation::LOCAL;
        }
        return string_to_work_location(js_extension_location->second);
    }
}

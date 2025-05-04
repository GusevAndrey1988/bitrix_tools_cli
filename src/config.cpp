#include "config.h"

#include <iostream>
#include <fstream>
#include <filesystem>

namespace bitrix_tools
{
    namespace j = nlohmann;

    const std::string Config::MAIN_CONFIG_FILE_NAME = "config.json";
    const std::string Config::BITRIX_TOOLS_JSON_FILE_NAME = "bitrix-tools.json";

    Config::Config(int argc, const char *argv[])
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
        std::ifstream f{getConfigPath() + MAIN_CONFIG_FILE_NAME};
        if (!f.is_open())
        {
            throw std::runtime_error{"Файл настроек не найден"};
        }

        config_json_ = j::json::parse(f);
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
        return findJsonStringValueThenMapIt("default_vendor", std::string{"vendor"});
    }

    WorkLocation Config::getDefaultModuleLocation() const
    {
        return findJsonStringValueThenMapIt<WorkLocation>("default_module_location", 
            WorkLocation::LOCAL, string_to_work_location);
    }

    WorkLocation Config::getDefaultComponentLocation() const
    {
        return findJsonStringValueThenMapIt<WorkLocation>("default_component_location", 
            WorkLocation::LOCAL, string_to_work_location);
    }

    WorkLocation Config::getDefaultJsExtensionLocation() const
    {
        return findJsonStringValueThenMapIt<WorkLocation>("default_js_extension_location", 
            WorkLocation::LOCAL, string_to_work_location);
    }
}

#pragma once

#include <string>
#include <vector>

#include "json_parser.h"
#include "work_location.h"

namespace bitrix_tools
{
    class Config
    {
    public:
        explicit Config(const std::vector<std::string> &args, const JsonParser &json_parser);

        Config(const Config &) = delete;

        Config& operator=(const Config &) = delete;

        std::string getRootPath() const;
        std::string getConfigPath() const;
        std::string getTemplatesPath() const;

        std::string getBitrixToolsJsonFileName() const;
        std::string getPathToBitrixToolsJson() const;

        std::string getPathToModuleDir(const WorkLocation &location, const std::string &vendor) const;
        std::string getPathToComponentDir(const WorkLocation &location, const std::string &vendor) const;
        std::string getPathToJsExtensionDir(const WorkLocation &location, const std::string &vendor) const;

        std::string getDefaultVendorName() const;
        WorkLocation getDefaultModuleLocation() const;
        WorkLocation getDefaultComponentLocation() const;
        WorkLocation getDefaultJsExtensionLocation() const;

    private:
        void parseJson();

        std::string app_path_;
        const JsonParser json_parser_;
        JsonParser::PropsMap props_;

        static const std::string MAIN_CONFIG_FILE_NAME;
        static const std::string BITRIX_TOOLS_JSON_FILE_NAME;
    };
}

#pragma once

#include <string>
#include <vector>
#include <functional>

#include <nlohmann/json.hpp>

#include "work_location.h"

#include "variables.h"

namespace bitrix_tools
{
    class Config
    {
    public:
        explicit Config(int argc, const char *argv[]);

        Config(const Config &) = default;

        Config& operator=(const Config &) = delete;

        std::string getBinaryPath() const;
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
        static std::filesystem::path getApplicationEtcDir()
        {
            return APPLICATION_ETC_DIR;
        }

        void parseJson();

        template<typename T>
        T findJsonStringValueThenMapIt(const std::string &key, const T &def = T(),
            std::function<T(const std::string&)> f = [](const std::string& v) { return T(v); }) const
        {
            auto value = config_json_.find(key);
            if (value == config_json_.end() || !value.value().is_string())
            {
                return def;
            }

            return f(value.value().get<std::string>());
        }

        std::string app_path_;
        nlohmann::json config_json_;

        static const std::string MAIN_CONFIG_FILE_NAME;
        static const std::string BITRIX_TOOLS_JSON_FILE_NAME;
    };
}

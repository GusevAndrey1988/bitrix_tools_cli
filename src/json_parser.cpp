#include "json_parser.h"

#include <fstream>
#include <exception>

#include <nlohmann/json.hpp>

namespace bitrix_tools
{
    JsonParser::JsonParser(const std::string &path_to_file) : props_({})
    {
        using namespace nlohmann;

        std::ifstream bitrix_tools_config_json{path_to_file};

        if (!bitrix_tools_config_json.is_open())
        {
            throw std::runtime_error{"Файл настроек приложения не найден"};
        }

        json config = json::parse(bitrix_tools_config_json);

        for (auto prop : config.items())
        {
            props_.insert({prop.key(), prop.value().dump()});
        }
    }

    const JsonParser::PropsMap &JsonParser::getProps() const
    {
        return props_;
    }
}
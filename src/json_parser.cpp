#include "json_parser.h"

#include <fstream>
#include <exception>

#include <nlohmann/json.hpp>

namespace bitrix_tools
{
    JsonParser::JsonParser()
    {
    }

    JsonParser::PropsMap JsonParser::parse(const std::string &path_to_file) const
    {
        using namespace nlohmann;

        std::ifstream bitrix_tools_config_json{path_to_file};

        if (!bitrix_tools_config_json.is_open())
        {
            throw std::runtime_error{"Файл настроек приложения не найден"};
        }

        json config = json::parse(bitrix_tools_config_json);

        PropsMap props{};

        for (auto prop : config.items())
        {
            props.insert({prop.key(), prop.value().dump()});
        }

        return props;
    }
}
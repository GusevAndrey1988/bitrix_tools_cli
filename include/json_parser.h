#pragma once

#include <string>
#include <unordered_map>

namespace bitrix_tools
{
    class JsonParser
    {
    public:
        using PropsMap = std::unordered_map<std::string, const std::string>;

        explicit JsonParser();

        PropsMap parse(const std::string &path_to_file) const;

        JsonParser(const JsonParser &) = default;

        JsonParser& operator=(const JsonParser &) = delete;
    };
}
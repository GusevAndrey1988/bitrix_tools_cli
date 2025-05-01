#pragma once

#include <string>
#include <unordered_map>

namespace bitrix_tools
{
    class JsonParser
    {
    public:
        using PropsMap = std::unordered_map<std::string, const std::string>;

        explicit JsonParser(const std::string &path_to_file);

        JsonParser(const JsonParser &) = delete;
        JsonParser& operator=(const JsonParser &) = delete;

        const PropsMap& getProps() const;
    
    private:
        PropsMap props_;
    };
}
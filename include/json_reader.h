#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include "template_property_value.h"

namespace bitrix_tools
{
    class JsonReader
    {
    public:
        explicit JsonReader(const std::string path_to_file);

        JsonReader(const JsonReader &) = delete;

        JsonReader& operator=(const JsonReader &) = delete;

        TemplatePropertyValueMapPtr values() const;

    private:
        TemplatePropertyValueMapPtr value_map_;

        TemplatePropertyValue convert_recursive(const nlohmann::json &v);
    };
}
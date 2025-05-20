#include "json_reader.h"

#include <fstream>
#include <stdexcept>

namespace bitrix_tools
{
    JsonReader::JsonReader(const std::string path_to_file)
        : value_map_{new TemplatePropertyValueMap{}}
    {
        std::ifstream in{path_to_file};
        if (!in.is_open())
        {
            throw std::runtime_error{"Файл json не найден: " + path_to_file};
        }

        nlohmann::json json = nlohmann::json::parse(in);

        for (auto &&e : json.items())
        {
            auto &&k = e.key();
            auto &&v = e.value();

            value_map_->insert({k, convert_recursive(v)});
        }
    }

    TemplatePropertyValueMapPtr JsonReader::values() const
    {
        return value_map_;
    }

    TemplatePropertyValue JsonReader::convert_recursive(const nlohmann::json &v)
    {
        if (v.is_null())
        {
            return TemplatePropertyValue{TemplatePropertyValue::EmptyValue{}};
        }
        else if (v.is_number_integer())
        {
            return TemplatePropertyValue{v.get<int>()};
        }
        else if (v.is_number_float())
        {
            return TemplatePropertyValue{v.get<double>()};
        }
        else if (v.is_string())
        {
            return TemplatePropertyValue{v.get<std::string>()};
        }
        else if (v.is_array())
        {
            TemplatePropertyValueListPtr list{new TemplatePropertyValueList{}};

            for (auto &&vv : v)
            {
                list->emplace_back(convert_recursive(vv));    
            }

            return list;
        }
        else if (v.is_object())
        {
            TemplatePropertyValueMapPtr map{new TemplatePropertyValueMap{}};
            for (auto && vv : v.items())
            {
                map->insert({vv.key(), convert_recursive(vv.value())});
            }

            return map;
        }

        return TemplatePropertyValue{TemplatePropertyValue::EmptyValue{}};
    }
}

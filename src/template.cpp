#include "template.h"

#include <stdexcept>
#include <filesystem>

namespace bitrix_tools
{
    namespace j = jinja2;

    Template::Template(const std::string &path_to_template,
        const TemplatePropertyValueMap &props) : props_{props}
    { 
        template_file_.open(path_to_template);
        if (!template_file_.is_open())
        {
            throw std::runtime_error{"Файл шаблона не найден"};
        }
    }

    bool Template::saveTo(const std::string &file_name, bool override)
    {
        j::Template tpl{};
        tpl.Load(template_file_);

        j::ValuesMap vm;

        auto result = tpl.RenderAsString(Template::propsToJinjaProps(props_));
        if (result.has_value())
        {
            if (std::filesystem::exists(file_name) && !override)
            {
                return false;
            }

            std::ofstream out{file_name};
            if (!out.is_open())
            {
                throw std::runtime_error{"Не удалось записать файл: " + file_name};
            }

            out.write(result.value().c_str(), result.value().size());
        }
        else
        {
            throw std::runtime_error{result.error().ToString()};
        }

        return true;
    }

    j::ValuesMap Template::propsToJinjaProps(const TemplatePropertyValueMap &props)
    {
        j::ValuesMap vm;

        for (const auto &value : props)
        {
           vm.insert({value.first, Template::valueToJinjaValue(value.second)});
        }

        return vm;
    }

    j::Value Template::valueToJinjaValue(const TemplatePropertyValue &value)
    {
        if (value.isEmpty())
        {
            return j::Value(j::EmptyValue{});
        }

        if (value.isBool())
        {
            return j::Value(value.asBool());
        }

        if (value.isDouble())
        {
            return j::Value(value.asDouble());
        }

        if (value.isInteger())
        {
            return j::Value(value.asInteger());
        }

        if (value.isString())
        {
            return j::Value(value.asString());
        }

        if (value.isList())
        {
            const auto &list = value.asList();
            j::ValuesList vl{};
            std::transform(list.begin(), list.end(),
                std::back_insert_iterator(vl), Template::valueToJinjaValue);

            return vl;
        }

        if (value.isMap())
        {
            const auto &map = value.asMap();
            j::ValuesMap vm{};
            std::transform(map.begin(), map.end(),
                std::inserter(vm, vm.begin()), [](const std::pair<std::string, TemplatePropertyValue> &p) {
                    return std::make_pair(p.first, Template::valueToJinjaValue(p.second));
                });

            return vm;
        }

        throw std::runtime_error{"Неизвестный тип значения"};
    }
}
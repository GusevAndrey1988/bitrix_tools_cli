#pragma once

#include <string>
#include <fstream>

#include <jinja2cpp/template.h>

#include "template_property_value.h"

namespace bitrix_tools
{
    class Template
    {
    public:
        explicit Template(const std::string &path_to_template,
            const TemplatePropertyValue::TemplatePropertyValueMap &props);

        bool saveTo(const std::string &file_name, bool override = false);

    private:
        static jinja2::ValuesMap propsToJinjaProps(const TemplatePropertyValue::TemplatePropertyValueMap &props);
        static jinja2::Value valueToJinjaValue(const TemplatePropertyValue &value);

        std::ifstream template_file_;
        TemplatePropertyValue::TemplatePropertyValueMap props_;
    };
}
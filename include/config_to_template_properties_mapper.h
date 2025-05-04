#pragma once

#include "config.h"
#include "template_property_value.h"

namespace bitrix_tools
{
    class ConfigToTemplatePropertiesMapper
    {
    public:
        static TemplatePropertyValue::TemplatePropertyValueMapPtr map(const Config &config);
    };
}
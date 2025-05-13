#pragma once

#include "config.h"
#include "template_property_value.h"

namespace bitrix_tools
{
    class ConfigPropertyMapper
    {
    public:
        explicit ConfigPropertyMapper(const Config &config);
         
        ConfigPropertyMapper(const ConfigPropertyMapper &) = delete;
        ConfigPropertyMapper& operator=(const ConfigPropertyMapper &) = delete;

        const TemplatePropertyValue::TemplatePropertyValueMapPtr get() const;

    private:
        TemplatePropertyValue::TemplatePropertyValueMapPtr value_map_;
    };
}
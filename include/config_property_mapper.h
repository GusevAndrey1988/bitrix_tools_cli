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

        const TemplatePropertyValueMapPtr get() const;

    private:
        TemplatePropertyValueMapPtr value_map_;
    };
}
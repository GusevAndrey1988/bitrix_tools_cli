#include "config_property_mapper.h"

namespace bitrix_tools
{
    ConfigPropertyMapper::ConfigPropertyMapper(const Config &config):
        value_map_{new TemplatePropertyValueMap{}}
    {
        value_map_->insert({"default_vendor", config.getDefaultVendorName()});
        value_map_->insert({"default_module_location", work_location_to_string(config.getDefaultModuleLocation())});
        value_map_->insert({"default_component_location", work_location_to_string(config.getDefaultComponentLocation())});
        value_map_->insert({"default_js_extension_location", work_location_to_string(config.getDefaultJsExtensionLocation())});
    }

    const TemplatePropertyValueMapPtr ConfigPropertyMapper::get() const
    {
        return value_map_;
    }
}
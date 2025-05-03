#include "config_to_template_properties_mapper.h"

namespace bitrix_tools
{
    TemplatePropertyValueMap ConfigToTemplatePropertiesMapper::map(const Config &config)
    {
        TemplatePropertyValueMap vm{};
        
        vm.insert({"default_vendor", config.getDefaultVendorName()});
        vm.insert({"default_module_location", work_location_to_string(config.getDefaultModuleLocation())});
        vm.insert({"default_component_location", work_location_to_string(config.getDefaultComponentLocation())});
        vm.insert({"default_js_extension_location", work_location_to_string(config.getDefaultJsExtensionLocation())});

        return vm;
    }
}
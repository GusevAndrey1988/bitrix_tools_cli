#include "commands/init_cmd.h"

#include <iostream>

#include "template.h"
#include "config_to_template_properties_mapper.h"

namespace bitrix_tools
{
    InitCmd::InitCmd(const Config &config) : Command(config)
    {
    }

    void InitCmd::execute()
    {
        const Config cfg = getConfig();

        const std::string path_to_tpl = cfg.getTemplatesPath() + cfg.getBitrixToolsJsonFileName() + ".j2";

        TemplatePropertyValueMap vm = ConfigToTemplatePropertiesMapper::map(cfg);
        Template tpl{path_to_tpl, vm};

        if (tpl.saveTo(cfg.getRootPath() + cfg.getBitrixToolsJsonFileName()))
        {
            std::cout << "Успешно" << std::endl;
        }
        else
        {
            std::cout << "Файл " << cfg.getBitrixToolsJsonFileName() << " уже существует" << std::endl;
        }
    }
}

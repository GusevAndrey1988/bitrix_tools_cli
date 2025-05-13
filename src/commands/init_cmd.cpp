#include "commands/init_cmd.h"

#include <iostream>

#include "template.h"
#include "config_property_mapper.h"

namespace bitrix_tools
{
    InitCmd::InitCmd(const Config &config) : Command(config)
    {
    }

    void InitCmd::execute()
    {
        const Config cfg = getConfig();

        const std::string path_to_tpl = cfg.getTemplatesPath() + cfg.getBitrixToolsJsonFileName() + ".j2";

        ConfigPropertyMapper props{cfg};
        Template tpl{path_to_tpl, props.get()};

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

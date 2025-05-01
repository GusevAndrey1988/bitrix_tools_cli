#pragma once

#include <string>
#include <vector>

#include "config.h"

namespace bitrix_tools
{
    class Application
    {
    public:
        explicit Application(const std::vector<std::string> &args);

        int run();
    
    private:
        bool bitrixToolsJsonFileExists() const;

        const std::vector<std::string> &args_;
        const Config config_;
    };
}

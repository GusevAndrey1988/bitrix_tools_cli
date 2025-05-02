#pragma once

#include <string>
#include <vector>
#include <memory>

#include <boost/program_options/variables_map.hpp>
#include <boost/program_options/options_description.hpp>

#include "config.h"

namespace bitrix_tools
{
    class Application
    {
    public:
        explicit Application(int argc, const char *argv[]);

        Application(const Application &) = delete;
        Application& operator=(const Application &) = delete;

        int run();
    
    private:
        bool bitrixToolsJsonFileExists() const;

        struct CmdLine
        {
            CmdLine(const std::string &caption);
            
            boost::program_options::options_description description;
            boost::program_options::variables_map variables;
        } cmd_line_;

        void initCmdLine();
        void parseCmdLine();

        const int argc_;
        const char **argv_;

        const Config config_;
    };

    constexpr char CMD_HELP[] = "help";
    constexpr char CMD_INIT[] = "init";
}
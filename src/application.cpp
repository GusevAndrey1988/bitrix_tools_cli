#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <filesystem>
#include <algorithm>
#include <boost/program_options.hpp>

#include "application.h"
#include "commands/init_cmd.h"
#include "json_parser.h"

namespace bitrix_tools
{
    namespace po = boost::program_options;

    Application::Application(int argc, const char *argv[])
        : cmd_line_{"Доступные опции"}, argc_{argc}, argv_{argv}, config_{Config(argc, argv, JsonParser{})}
    {
    }

    int Application::run()
    {
        using namespace std;
        using namespace bitrix_tools;

        initCmdLine();

        try
        {
            parseCmdLine();
        }
        catch (const boost::wrapexcept<boost::program_options::unknown_option> &e)
        {
            cout << "Неизвестная опция: " << e.get_option_name() << endl;
            return EXIT_FAILURE;
        }

        if (cmd_line_.variables.count(CMD_HELP))
        {
            cout << cmd_line_.description << endl;
        }

        if (cmd_line_.variables.count(CMD_INIT))
        {
            InitCmd cmd(config_);
            cmd.execute();
        }

        if (!bitrixToolsJsonFileExists())
        {
            cout
                << "Файл "
                << "\"" << config_.getBitrixToolsJsonFileName() << "\""
                << " не найден. Выполните команду --init."
                << endl;

            return EXIT_SUCCESS;
        }

        return EXIT_SUCCESS;
    }

    bool Application::bitrixToolsJsonFileExists() const
    {
        using namespace std;

        auto bitrix_tools_json_status = filesystem::status(
            config_.getRootPath() + config_.getBitrixToolsJsonFileName());

        return bitrix_tools_json_status.type() != filesystem::file_type::not_found;
    }

    void Application::initCmdLine()
    {
        cmd_line_.description.add_options()
            (CMD_HELP, "выводит подсказку")
            (CMD_INIT, (std::string{
                "создаёт файл "
                + config_.getBitrixToolsJsonFileName()
                + " в текущем каталоге"}.c_str()));
    }

    void Application::parseCmdLine()
    {
        po::store(po::parse_command_line(argc_, argv_, cmd_line_.description), cmd_line_.variables);
        po::notify(cmd_line_.variables);
    }

    Application::CmdLine::CmdLine(const std::string &caption) : description{caption}
    {
    }
}

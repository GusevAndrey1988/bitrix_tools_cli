#include "commands/init_cmd.h"

#include <iostream>

InitCmd::InitCmd(const Config &config) : Command(config)
{
}

void InitCmd::execute()
{
    std::cout << "run init cmd" << std::endl;
}

InitCmdFactory::InitCmdFactory(const Config &config) : CommandFactory(config)
{
}

Command::CommandPtr InitCmdFactory::create()
{
    return Command::CommandPtr(new InitCmd(getConfig()));
}
#include <gtest/gtest.h>
#include <filesystem>
#include <regex>

#include "tools/tools.h"
#include "commands/init_cmd.h"

TEST(InitCommandTest, RunTest)
{
    using namespace bitrix_tools;

    const char *args[] = { "./" };

    std::filesystem::current_path("./test");

    Config cfg{sizeof(args) / sizeof(void*), args};

    suppress_stdout([&cfg]() {
        InitCmd cmd{cfg};
        cmd.execute();
    });

    EXPECT_TRUE(std::filesystem::exists(cfg.getBitrixToolsJsonFileName()));

    std::string file_content = read_whole_file(cfg.getBitrixToolsJsonFileName());

    EXPECT_TRUE(std::regex_search(file_content, std::regex{"modules"}));
    EXPECT_TRUE(std::regex_search(file_content, std::regex{"components"}));
    EXPECT_TRUE(std::regex_search(file_content, std::regex{"js-extensions"}));

    std::filesystem::remove(cfg.getBitrixToolsJsonFileName());
}
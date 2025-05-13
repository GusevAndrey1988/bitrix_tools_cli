#include "config.h"

#include <gtest/gtest.h>
#include <filesystem>

TEST(ConfigTest, CheckPaths)
{
    using namespace bitrix_tools;

    const char *args[] = { "./" };

    Config cfg{sizeof(args) / sizeof(void*), args};

    EXPECT_EQ(cfg.getRootPath(), std::filesystem::current_path().string() + "/");
    EXPECT_EQ(cfg.getBinaryPath(), "./");
    EXPECT_EQ(cfg.getTemplatesPath(), "./../resources/templates/");
    EXPECT_EQ(cfg.getConfigPath(), "./../resources/config/");
}
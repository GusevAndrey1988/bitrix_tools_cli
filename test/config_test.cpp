#include "config.h"

#include <gtest/gtest.h>
#include <filesystem>

TEST(ConfigTest, BasicTest)
{
    using namespace bitrix_tools;

    const char *args[] = { "./" };

    Config cfg{1, args};

    EXPECT_EQ(cfg.getRootPath(), std::filesystem::current_path().string() + "/");
    EXPECT_EQ(cfg.getBinaryPath(), "./");
    EXPECT_EQ(cfg.getTemplatesPath(), "./../resources/templates/");
}
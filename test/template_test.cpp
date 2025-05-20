#include <gtest/gtest.h>
#include <regex>
#include <filesystem>

#include "tools/tools.h"

#include "template.h"

TEST(TemplateTest, BaseTest)
{
    using namespace bitrix_tools;

    TemplatePropertyValueMapPtr props{new TemplatePropertyValueMap{}};

    props->insert({
        {"prop1", std::string{"Hello"}},
        {"prop2", std::string{"World"}},
    });

    TemplatePropertyValueListPtr listProp1Value{new TemplatePropertyValueList{{
        std::string{"One"},
        std::string{"Two"},
        std::string{"Three"},
    }}};
    props->insert({"listProp1", listProp1Value});

    TemplatePropertyValueMapPtr mapProp1Value{new TemplatePropertyValueMap{}};
    mapProp1Value->insert({
        {"key1", std::string{"one"}},
        {"key2", std::string{"two"}},
        {"key3", std::string{"three"}},
    });
    props->insert({"mapProp1", mapProp1Value});

    Template tpl{"./test_data/template.php.j2", props};

    std::string tpl_file_name{"./tpl.php"};
    tpl.saveTo(tpl_file_name, true);

    auto fileData = read_whole_file(tpl_file_name);

    EXPECT_TRUE(std::regex_search(fileData, std::regex{"\\$message = 'Hello World';"}));
    EXPECT_TRUE(std::regex_search(fileData, std::regex{"\\<div\\>ONE-TWO-THREE\\</div\\>"}));
    EXPECT_TRUE(std::regex_search(fileData, std::regex{
        "\\<li\\>one\\</li\\>\\s*\\<li\\>two\\</li\\>\\s*\\<li\\>three\\</li\\>"
    }));

    std::filesystem::remove(tpl_file_name);
}
#include <gtest/gtest.h>

#include "json_reader.h"

namespace
{
    bool compare_recursive(
        const bitrix_tools::TemplatePropertyValue &l,
        const bitrix_tools::TemplatePropertyValue &r
    );

    TEST(JsonTest, BaseTest)
    {
        using namespace bitrix_tools;

        JsonReader r{"./test_data/json.json"};

        auto values = r.values();

        auto &&null_value = values->find("null");
        if (null_value != values->end())
        {
            EXPECT_TRUE(null_value->second.isEmpty());
        }
        else
        {
            FAIL();
        }

        auto &&int_value = values->find("int");
        if (int_value != values->end())
        {
            EXPECT_EQ(int_value->second.asInteger(), 12);
        }
        else
        {
            FAIL();
        }

        auto &&double_value = values->find("double");
        if (double_value != values->end())
        {
            EXPECT_EQ(double_value->second.asDouble(), 12.12);
        }
        else
        {
            FAIL();
        }

        auto &&string_value = values->find("string");
        if (string_value != values->end())
        {
            EXPECT_EQ(string_value->second.asString(), "hello");
        }
        else
        {
            FAIL();
        }

        TemplatePropertyValueListPtr expected_arr{new TemplatePropertyValueList({
            TemplatePropertyValue{1},
            TemplatePropertyValue{1.1},
            TemplatePropertyValue{std::string{"hello"}},
            TemplatePropertyValueListPtr{new TemplatePropertyValueList({
                TemplatePropertyValue{1},
                TemplatePropertyValue{2},
                TemplatePropertyValue{3},
            })},
            TemplatePropertyValueMapPtr{new TemplatePropertyValueMap{{
                {"a", TemplatePropertyValue{1}},
                {"a", TemplatePropertyValue{2}},
            }}}
        })};

        auto &&arr_value = values->find("arr");
        if (arr_value != values->end())
        {
            EXPECT_TRUE(compare_recursive(arr_value->second, expected_arr));
        }
        else
        {
            FAIL();
        }

        TemplatePropertyValueMapPtr expected_obj{new TemplatePropertyValueMap{{
            {"obj", TemplatePropertyValueMapPtr{new TemplatePropertyValueMap{
                {"a", TemplatePropertyValue{std::string{"hello"}}},
                {"b", TemplatePropertyValue{std::string{"world"}}},
            }}},
            {"arr", TemplatePropertyValueListPtr{new TemplatePropertyValueList({
                TemplatePropertyValue{1},
                TemplatePropertyValue{2},
                TemplatePropertyValue{3},
            })}},
            {"double", TemplatePropertyValue{100.100}}
        }}};

        auto &&obj_value = values->find("obj");
        if (obj_value != values->end())
        {
            EXPECT_TRUE(compare_recursive(obj_value->second, expected_obj));
        }
        else
        {
            FAIL();
        }
    }

    bool compare_recursive(
        const bitrix_tools::TemplatePropertyValue &l,
        const bitrix_tools::TemplatePropertyValue &r
    ) {
        if (!l.hasSameType(r))
        {
            return false;
        }

        if (l.isEmpty()) {
            return r.isEmpty();
        }

        if (l.isBool())
        {
            return l.asBool() == r.asBool();
        }

        if (l.isInteger())
        {
            return l.asInteger() == r.asInteger();
        }

        if (l.isDouble())
        {
            return l.asDouble() == r.asDouble();
        }

        if (l.isString())
        {
            return l.asString() == r.asString();
        }

        if (l.isList())
        {
            auto &&l1 = l.asList();
            auto &&l2 = r.asList();

            if (l1->size() != l2->size())
            {
                return false;
            }

            for (
                auto &&i1 = l1->begin(), &&i2 = l2->begin();
                i1 != l1->end() || i2 != l2->end();
                ++i1, ++i2
            )
            {
                return compare_recursive(*i1, *i2);
            }
        }

        if (l.isMap())
        {
            auto &&m1 = l.asMap();
            auto &&m2 = r.asMap();

            if (m1->size() != m2->size())
            {
                return false;
            }

            for (auto &&it = m1->begin(); it != m1->end(); ++it)
            {
                auto &&found_item = m2->find(it->first);
                if (found_item == m2->end())
                {
                    return false;
                }

                if (!compare_recursive(it->second, found_item->second))
                {
                    return false;
                }
            }

            return true;
        }

        return false;
    }
}
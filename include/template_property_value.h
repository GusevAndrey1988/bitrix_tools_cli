#pragma once

#include <variant>
#include <string>
#include <unordered_map>
#include <vector>

namespace bitrix_tools
{
    class TemplatePropertyValue
    {
    public:
        using TemplatePropertyValueMap = std::unordered_map<std::string, TemplatePropertyValue>;
        using TemplatePropertyValueList = std::vector<TemplatePropertyValue>;

        struct EmptyValue {};

        using ValueData = std::variant<
            EmptyValue,
            bool,
            std::string,
            int,
            double,
            TemplatePropertyValueMap,
            TemplatePropertyValueList
        >;

        TemplatePropertyValue(bool value);

        TemplatePropertyValue(const std::string &value);

        TemplatePropertyValue(int value);

        TemplatePropertyValue(double value);

        TemplatePropertyValue(const TemplatePropertyValueMap &value);

        TemplatePropertyValue(const TemplatePropertyValueList &value);

        bool isEmpty() const;

        bool isBool() const;
        bool asBool() const;

        bool isString() const;
        const std::string& asString() const;

        bool isInteger() const;
        int asInteger() const;

        bool isDouble() const;
        double asDouble() const;

        bool isMap() const;
        const TemplatePropertyValueMap& asMap() const;

        bool isList() const;
        const TemplatePropertyValueList& asList() const;

    private:
        ValueData value_;
    };
}
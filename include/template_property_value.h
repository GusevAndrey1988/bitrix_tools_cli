#pragma once

#include <variant>
#include <string>
#include <unordered_map>
#include <vector>
#include <memory>

namespace bitrix_tools
{
    class TemplatePropertyValue
    {
    public:
        using TemplatePropertyValueMap = std::unordered_map<std::string, TemplatePropertyValue>;
        using TemplatePropertyValueMapPtr = std::shared_ptr<TemplatePropertyValueMap>;

        using TemplatePropertyValueList = std::vector<TemplatePropertyValue>;
        using TemplatePropertyValueListPtr = std::shared_ptr<TemplatePropertyValueList>;


        struct EmptyValue {};

        using ValueData = std::variant<
            EmptyValue,
            bool,
            std::string,
            int,
            double,
            TemplatePropertyValueMapPtr,
            TemplatePropertyValueListPtr
        >;

        TemplatePropertyValue(bool value);

        TemplatePropertyValue(const std::string &value);

        TemplatePropertyValue(int value);

        TemplatePropertyValue(double value);

        TemplatePropertyValue(TemplatePropertyValueMapPtr value);

        TemplatePropertyValue(TemplatePropertyValueListPtr value);

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
        TemplatePropertyValueMapPtr asMap() const;

        bool isList() const;
        TemplatePropertyValueListPtr asList() const;

    private:
        ValueData value_;
    };
}
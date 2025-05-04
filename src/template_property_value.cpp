#include "template_property_value.h"

namespace bitrix_tools
{
    TemplatePropertyValue::TemplatePropertyValue(bool value) : value_{value}
    {
    }

    TemplatePropertyValue::TemplatePropertyValue(const std::string &value) : value_{value}
    {
    }

    TemplatePropertyValue::TemplatePropertyValue(int value) : value_{value}
    {
    }

    TemplatePropertyValue::TemplatePropertyValue(double value) : value_{value}
    {
    }

    TemplatePropertyValue::TemplatePropertyValue(TemplatePropertyValueMapPtr value)
        : value_{value}
    {
    }

    TemplatePropertyValue::TemplatePropertyValue(TemplatePropertyValueListPtr value)
        : value_{value}
    {
    }

    bool TemplatePropertyValue::isEmpty() const
    {
        return std::holds_alternative<EmptyValue>(value_);
    }

    bool TemplatePropertyValue::isBool() const
    {
        return std::holds_alternative<bool>(value_);
    }

    bool TemplatePropertyValue::asBool() const
    {
        return std::get<bool>(value_);
    }

    bool TemplatePropertyValue::isString() const
    {
        return std::holds_alternative<std::string>(value_);
    }

    const std::string& TemplatePropertyValue::asString() const
    {
        return std::get<std::string>(value_);
    }

    bool TemplatePropertyValue::isInteger() const
    {
        return std::holds_alternative<int>(value_);
    }

    int TemplatePropertyValue::asInteger() const
    {
        return std::get<int>(value_);
    }

    bool TemplatePropertyValue::isDouble() const
    {
        return std::holds_alternative<double>(value_);
    }

    double TemplatePropertyValue::asDouble() const
    {
        return std::get<double>(value_);
    }

    bool TemplatePropertyValue::isMap() const
    {
        return std::holds_alternative<TemplatePropertyValue::TemplatePropertyValueMapPtr>(value_);
    }

    TemplatePropertyValue::TemplatePropertyValueMapPtr TemplatePropertyValue::asMap() const
    {
        return std::get<TemplatePropertyValueMapPtr>(value_);
    }

    bool TemplatePropertyValue::isList() const
    {
        return std::holds_alternative<TemplatePropertyValue::TemplatePropertyValueListPtr>(value_);
    }

    TemplatePropertyValue::TemplatePropertyValueListPtr TemplatePropertyValue::asList() const
    {
        return std::get<TemplatePropertyValue::TemplatePropertyValueListPtr>(value_);
    }
}
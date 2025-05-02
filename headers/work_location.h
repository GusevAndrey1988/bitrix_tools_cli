#pragma once

#include <string>

namespace bitrix_tools
{
    enum class WorkLocation {
        BITRIX,
        LOCAL
    };

    std::string work_location_to_string(const WorkLocation &location);
    WorkLocation string_to_work_location(const std::string &location);
}
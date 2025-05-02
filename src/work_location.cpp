#include "work_location.h"

#include <stdexcept>

namespace bitrix_tools
{
    std::string work_location_to_string(const WorkLocation &location)
    {
        switch (location)
        {
        case WorkLocation::BITRIX:
            return "bitrix";

        case WorkLocation::LOCAL:
            return "local";
        
        default:
            /** nop */
            break;
        }

        throw std::runtime_error{"Неизвестный тип расположения"};
    }

    WorkLocation string_to_work_location(const std::string &location)
    {
        if (location == "bitrix") {
            return WorkLocation::BITRIX;
        }

        if (location == "local") {
            return WorkLocation::LOCAL;
        }

        throw std::runtime_error{"Неизвестный тип расположения"};
    }
}
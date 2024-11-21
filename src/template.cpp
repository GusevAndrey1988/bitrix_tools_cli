#include "template.h"

const std::string Template::TEMPLATE_EXTENSION = ".template";

std::filesystem::path Template::makeFileNameFromTemplatePath(
        const std::filesystem::path &templatePath)
{
    std::string fileName = templatePath.filename();
    fileName.erase(fileName.find(TEMPLATE_EXTENSION));

    return fileName;
}
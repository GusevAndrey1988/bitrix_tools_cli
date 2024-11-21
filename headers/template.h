#pragma once

#include <filesystem>

class Template {
    public:
        static std::filesystem::path makeFileNameFromTemplatePath(
                const std::filesystem::path &templatePath);
    
    private:
        static const std::string TEMPLATE_EXTENSION;
};
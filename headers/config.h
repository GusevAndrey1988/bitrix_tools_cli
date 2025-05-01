#pragma once

#include <string>
#include <vector>

class Config {
    public:
        Config(const Config&) = delete;
    
        explicit Config(const std::vector<std::string> &args);

        Config operator=(const Config&) = delete;

        const std::string getRootPath() const;
        const std::string getConfigPath() const;
        const std::string getTemplatesPath() const;

        const std::string getBitrixToolsJsonFileName() const;
        const std::string getPathToBitrixToolsJson() const;

    private:
        std::string app_path_;

};
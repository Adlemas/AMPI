#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <filesystem>
#include <unistd.h>
#include <typeinfo>

#include "../json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;

class FileManager
{
private:
    class Config
    {
    private:
        json Settings = {
            /**
             * Build type - "interpreter" (default) | "compile"
             */
            {"build-type", "interpreter"},
            /**
             * Index - "main.ampi" (default) | "anyname.ampi"
             */
            {"index", "main.ampi"},
            /**
             * Destination - "./" (default) | "path/to/compile"
             */
            {"destination", "./"},
            /**
             * Comments enabled - "false" (default) | "true"
             */
            {"comments_enabled", "true"},
            /**
             * Target - "binary" (default) | "java" | "python" | "nodejs" | "c++"
             */
            {"target", "binary"}};

    public:
        void setProperty(std::string name, std::string value);

        json getSettings();
    };

    std::string path;
    std::string configPath;
    Config config;

    inline bool exists(std::string destination);

    json parseJson(std::string stringify);

    void writeFile(std::string path, std::string content);

public:
    void setPath(std::string path);

    std::string join(std::string normal, std::string additional);

    std::string getPath();

    bool hasConfigFile();

    bool readConfigFile();

    bool initProject();

    json getSettings();
};
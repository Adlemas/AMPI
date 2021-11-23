#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include <filesystem>
#include <unistd.h>
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

    std::string join(std::string normal, std::string additional);

    inline bool exists(std::string destination);

    json parseJson(std::string stringify);

    void writeFile(std::string path, std::string content)
    {
        std::ofstream file;
        file.open(path);
        file << content;
        file.close();
    };

public:
    void setPath(std::string path);

    std::string getPath();

    bool hasConfigFile();

    void readConfigFile();

    void initProject();
};
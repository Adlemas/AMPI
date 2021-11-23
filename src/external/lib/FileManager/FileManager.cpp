#include "../FileManager.h"

std::string FileManager::join(std::string normal, std::string additional)
{
    if (normal[normal.size() - 1] == '/' || normal[normal.size() - 1] == '\\')
        return (normal + additional);
    else
        return (normal + "/" + additional);
};

inline bool FileManager::exists(std::string destination)
{
    struct stat buffer;
    return (stat(destination.c_str(), &buffer) == 0);
};

void FileManager::setPath(std::string path)
{
    this->path = path;
    this->configPath = this->join(path, "config.json");
};

std::string FileManager::getPath()
{
    return this->path;
};

bool FileManager::hasConfigFile()
{
    return (this->exists(this->join(this->path, "config.json")));
};

void FileManager::readConfigFile()
{
    std::ifstream f;
    f.open(this->configPath.c_str(), std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Failed to open config file: " << this->configPath << std::endl;
        return;
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    json CONFIG = this->parseJson(buffer.str());

    // iterate the array
    for (const auto &property : CONFIG.items())
    {
        std::string key = property.key();
        std::string value = CONFIG.value(key, "");
        this->config.setProperty(key, value);
    }

    std::cout << "  Configuration file initialized!" << std::endl;

    // std::cout << this->config.getSettings().dump(4) << std::endl;
};

json FileManager::Config::getSettings()
{
    return this->Settings;
}

json FileManager::parseJson(std::string stringify)
{
    json j_complete = json::parse(stringify);
    return j_complete;
};

void FileManager::Config::setProperty(std::string name, std::string value)
{
    Settings[name] = value;
}

void FileManager::initProject()
{
    std::cout << "Initing new project at \"" << this->path << "\"..." << std::endl;
    std::cout << "Creating project configuration file at \"" << this->configPath << "\"..." << std::endl;
    this->writeFile(this->configPath, this->config.getSettings().dump(4));
    std::cout << "Project configuration file was created successfully!" << std::endl;
    std::cout << "Creating main ampi file at \"" << this->join(this->path, this->config.getSettings()["index"]) << "\"..." << std::endl;
    this->writeFile(this->join(this->path, this->config.getSettings()["index"]), "/**\n * AMPI: CrossPlatform Programming Language.\n */\nterminal.log(\"Hello world!\");");
};
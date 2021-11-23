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

bool FileManager::readConfigFile()
{
    std::ifstream f;
    f.open(this->configPath.c_str(), std::ios::in | std::ios::binary);
    if (!f.is_open())
    {
        std::cerr << "Failed to open config file: " << this->configPath << std::endl;
        return false;
    }

    std::stringstream buffer;
    buffer << f.rdbuf();
    json CONFIG = this->parseJson(buffer.str());

    for (const auto &property : CONFIG.items())
    {
        std::string key = property.key();
        try
        {
            std::string value = CONFIG.value(key, "");
            if (value.size() > 0)
                this->config.setProperty(key, value);
        }
        catch (nlohmann::detail::type_error)
        {
            std::cout << "Config property error.\n  Property \"" << key << "\" must be a string." << std::endl;
            return false;
        }
    }

    return true;
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

void FileManager::writeFile(std::string path, std::string content)
{
    std::ofstream file;
    file.open(path);
    file << content;
    file.close();
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
    this->initProjectPropertyes();
};

void FileManager::initProjectPropertyes(){

};
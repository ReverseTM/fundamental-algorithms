#include "json_implementation.h"

Json_implementation::Json_implementation(const std::string &path)
{
    nlohmann::json obj_json;
    std::fstream json_file;

    json_file.open(path);
    json_file >> obj_json;
    json_file.close();

    for (int i = 0; i < obj_json["configs"].size(); i++)
    {
        _configuration[obj_json["configs"][i]["target"]] = obj_json["configs"][i]["severity"];
    }
}

Logger* Json_implementation::create() const
{
    return new Logger_implementation(_configuration);
}

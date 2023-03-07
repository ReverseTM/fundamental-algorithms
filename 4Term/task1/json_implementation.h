#ifndef JSON_IMPLEMENTATION_H
#define JSON_IMPLEMENTATION_H
#include <fstream>
#include "logger_implementation.h"
#include "json.h"

class Json_implementation final : public Json
{
private:
    std::map<std::string, Logger::severity> _configuration;

public:
    Json_implementation(const std::string &path);

    Logger* create() const override;
};

#endif //JSON_IMPLEMENTATION_H

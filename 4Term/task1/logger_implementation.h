#ifndef LOGGER_IMPLEMENTATION
#define LOGGER_IMPLEMENTATION
#include "builder_implementation.h"
#include "json_implementation.h"

class Logger_implementation final : public Logger
{
    friend class Builder_implementation;
    friend class Json_implementation;

private:
    std::map<std::string, std::pair<std::ofstream*, Logger::severity>> _logger_streams;

    static std::map<Logger::severity, std::string> _str_severity;

    static std::map<std::string, std::pair<std::ofstream*, size_t>> _all_streams;

    Logger_implementation(std::map<std::string, Logger::severity> const &);

public:
    Logger const *log(const std::string &message, severity severity_level) const override;

    ~Logger_implementation();

    Logger_implementation(Logger_implementation const &) = delete;

    Logger_implementation& operator=(Logger_implementation const &) = delete;
};

#endif //LOGGER_IMPLEMENTATION
#ifndef LOGGER_IMPLEMENTATION
#define LOGGER_IMPLEMENTATION
#include "builder_implementation.h"
#include "json_implementation.h"

class logger_implementation final : public logger
{
    friend class builder_implementation;
    friend class json_implementation;

private:
    std::map<std::string, std::pair<std::ofstream*, logger::severity>> _logger_streams;

    static std::map<logger::severity, std::string> _str_severity;

    static std::map<std::string, std::pair<std::ofstream*, size_t>> _all_streams;

    logger_implementation(std::map<std::string, logger::severity> const &);

public:
    logger const *log(const std::string &message, severity severity_level) const override;

    ~logger_implementation();

    logger_implementation(logger_implementation const &) = delete;

    logger_implementation& operator=(logger_implementation const &) = delete;
};

#endif //LOGGER_IMPLEMENTATION
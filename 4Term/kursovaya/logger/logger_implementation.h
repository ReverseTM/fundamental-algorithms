#ifndef LOGGER_IMPLEMENTATION
#define LOGGER_IMPLEMENTATION
#include "builder_implementation.h"
#include "json_implementation.h"
#include <sstream>

class logger_implementation final : public logger
{
    friend class builder_implementation;
    friend class json_implementation;

public:

    explicit logger_implementation(std::map<std::string, logger::severity> const &);

private:

    std::map<std::string, std::pair<std::ofstream*, logger::severity>> _logger_streams;

    static std::map<std::string, std::pair<std::ofstream*, size_t>> _all_streams;


private:

     static std::string current_time();

     static std::string severity_to_string(logger::severity);

public:

    logger const *log(const std::string &message, severity level) const override;

    ~logger_implementation() override;

    logger_implementation(logger_implementation const &) = delete;

    logger_implementation& operator=(logger_implementation const &) = delete;

    logger_implementation(logger_implementation &&) = delete;

    logger_implementation & operator=(logger_implementation &&) = delete;
};

#endif //LOGGER_IMPLEMENTATION
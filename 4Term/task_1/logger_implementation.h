#ifndef LOGGER_IMPLEMENTATION
#define LOGGER_IMPLEMENTATION
#include <iostream>
#include "builder_implementation.h"

class logger_implementation final : public logger
{
    friend class builder_implementation;

private:
    std::map<std::string, std::pair<std::ofstream*, logger::severity>> _logger_streams;

    static std::map<std::string, std::pair<std::ofstream*, size_t>> _all_streams;

    logger_implementation(std::map<std::string, logger::severity> const &);

public:
    logger const *log(const std::string &, severity) const override;

    ~logger_implementation();

    logger_implementation(logger_implementation const &) = delete;

    logger_implementation& operator=(logger_implementation const &) = delete;
};

#endif //LOGGER_IMPLEMENTATION
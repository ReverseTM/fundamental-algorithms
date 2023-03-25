#ifndef LOGGER_IMPLEMENTATION
#define LOGGER_IMPLEMENTATION
#include "builder_implementation.h"
#include "json_implementation.h"

class logger_implementation final : public fund_alg::logger
{
    friend class builder_implementation;
    friend class json_implementation;

private:

    std::map<std::string, std::pair<std::ofstream*, fund_alg::logger::severity>> _logger_streams;

    static std::map<std::string, std::pair<std::ofstream*, size_t>> _all_streams;

    logger_implementation(std::map<std::string, fund_alg::logger::severity> const &);

private:

     static std::string current_time();

     static std::string severity_to_string(fund_alg::logger::severity);

public:

    fund_alg::logger const *log(const std::string &message, severity level) const override;

    ~logger_implementation();

    logger_implementation(logger_implementation const &) = delete;

    logger_implementation& operator=(logger_implementation const &) = delete;
};

#endif //LOGGER_IMPLEMENTATION
#include "logger_holder.h"

const logger_holder * logger_holder::log_with_guard(const std::string &message, fund_alg::logger::severity severity_level) const
{
    auto * logger = get_logger();

    if (logger != nullptr)
    {
        logger->log(message, severity_level);
    }

    return this;
}

const logger_holder * logger_holder::trace_with_guard(std::string const &message) const
{
    return log_with_guard(message, fund_alg::logger::severity::trace);
}

const logger_holder * logger_holder::debug_with_guard(std::string const &message) const
{
    return log_with_guard(message, fund_alg::logger::severity::debug);
}

const logger_holder * logger_holder::information_with_guard(std::string const &message) const
{
    return log_with_guard(message, fund_alg::logger::severity::information);
}

const logger_holder * logger_holder::warning_with_guard(std::string const &message) const
{
    return log_with_guard(message, fund_alg::logger::severity::warning);
}

const logger_holder * logger_holder::error_with_guard(std::string const &message) const
{
    return log_with_guard(message, fund_alg::logger::severity::error);
}

const logger_holder * logger_holder::critical_with_guard(std::string const &message) const
{
    return log_with_guard(message, fund_alg::logger::severity::critical);
}
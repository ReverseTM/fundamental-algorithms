#include "logger_holder.h"

const logger_holder * logger_holder::trace_with_guard(std::string const &message) const
{
    auto * logger = get_logger();

    if (logger != nullptr)
    {
        logger->log(message, fund_alg::logger::severity::trace);
    }

    return this;
}

const logger_holder * logger_holder::debug_with_guard(std::string const &message) const
{
    auto * logger = get_logger();

    if (logger != nullptr)
    {
        logger->log(message, fund_alg::logger::severity::debug);
    }

    return this;
}

const logger_holder * logger_holder::information_with_guard(std::string const &message) const
{
    auto * logger = get_logger();

    if (logger != nullptr)
    {
        logger->log(message, fund_alg::logger::severity::information);
    }

    return this;
}

const logger_holder * logger_holder::warning_with_guard(std::string const &message) const
{
    auto * logger = get_logger();

    if (logger != nullptr)
    {
        logger->log(message, fund_alg::logger::severity::warning);
    }

    return this;
}

const logger_holder * logger_holder::error_with_guard(std::string const &message) const
{
    auto * logger = get_logger();

    if (logger != nullptr)
    {
        logger->log(message, fund_alg::logger::severity::error);
    }

    return this;
}

const logger_holder * logger_holder::critical_with_guard(std::string const &message) const
{
    auto * logger = get_logger();

    if (logger != nullptr)
    {
        logger->log(message, fund_alg::logger::severity::critical);
    }

    return this;
}
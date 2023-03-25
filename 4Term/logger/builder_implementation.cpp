#include "builder_implementation.h"
#include "logger_implementation.h"

builder* builder_implementation::add_stream(std::string const &target, fund_alg::logger::severity level)
{
    _settings[target] = level;
    return this;
}

fund_alg::logger* builder_implementation::build() const
{
    return new logger_implementation(_settings);
}
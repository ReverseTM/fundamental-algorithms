#include "builder_implementation.h"
#include "logger_implementation.h"

builder* builder_implementation::add_stream(std::string const &target, logger::severity level)
{
    _settings[target] = level;
    return this;
}

logger* builder_implementation::build() const
{
    return new logger_implementation(_settings);
}
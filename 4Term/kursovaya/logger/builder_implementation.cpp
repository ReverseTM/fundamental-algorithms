#include "builder_implementation.h"
#include "logger_implementation.h"

builder* builder_implementation::add_stream(std::string const &target, logger::severity level)
{
    if (target.empty())
    {
        throw std::invalid_argument("empty file path");
    }

    _settings[target] = level;
    return this;
}

std::shared_ptr<logger> builder_implementation::build() const
{
    return std::make_shared<logger_implementation>(_settings);
}
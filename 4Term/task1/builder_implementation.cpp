#include "builder_implementation.h"
#include "logger_implementation.h"

Builder* Builder_implementation::add_stream(std::string const &target, Logger::severity level)
{
    _settings[target] = level;
    return this;
}

Logger* Builder_implementation::build() const
{
    return new Logger_implementation(_settings);
}
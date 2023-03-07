#include <iostream>
#include <ctime>
#include "logger_implementation.h"

std::map<std::string, std::pair<std::ofstream *, size_t>> Logger_implementation::_all_streams =
        std::map<std::string, std::pair<std::ofstream *, size_t>>();

std::map<Logger::severity, std::string> Logger_implementation::_str_severity = {
        {Logger::severity::trace, "trace"},
        {Logger::severity::debug, "debug"},
        {Logger::severity::information, "information"},
        {Logger::severity::warning, "warning"},
        {Logger::severity::error, "error"},
        {Logger::severity::critical, "critical"},
};

Logger_implementation::Logger_implementation(std::map<std::string, Logger::severity> const &targets)
{
    for (auto & [target, severity_level] : targets)
    {
        std::ofstream *stream = nullptr;
        auto current_stream = _all_streams.find(target);

        if (current_stream == _all_streams.end())
        {
            if (target != "console")
            {
                stream = new std::ofstream;
                stream->open(target);
            }

            _all_streams[target] = std::make_pair(stream, 1);
        }
        else
        {
            stream = current_stream->second.first;
            current_stream->second.second++;
        }

        _logger_streams[target] = std::make_pair(stream, severity_level);
    }
}

Logger_implementation::~Logger_implementation()
{
    for (auto & [target, stream_info] : _logger_streams)
    {
        auto current_stream = _all_streams.find(target);

        if(--(current_stream->second.second) == 0)
        {
            if (current_stream->second.first != nullptr)
            {
                current_stream->second.first->flush();
                current_stream->second.first->close();
                delete current_stream->second.first;
            }

            _all_streams.erase(current_stream);
        }
    }
}

Logger const *Logger_implementation::log(const std::string &message, Logger::severity severity_level) const
{
    for (auto & [target, stream_info] : _logger_streams)
    {
        if (stream_info.second > severity_level)
        {
            continue;
        }
        else
        {
            time_t t = time(nullptr);
            tm *now = localtime(&t);

            char current_time[64];
            strftime(current_time, sizeof(current_time), "%d/%m/%Y %X", now);

            if (stream_info.first == nullptr)
            {
                std::cout << "[" << current_time << "]" << "[" << Logger_implementation::_str_severity[severity_level] << "] " << message << std::endl;
            }
            else
            {
                (*(stream_info.first)) << "[" << current_time << "]" << "[" << Logger_implementation::_str_severity[severity_level] << "] " << message << std::endl;
            }
        }
    }
    return this;
}
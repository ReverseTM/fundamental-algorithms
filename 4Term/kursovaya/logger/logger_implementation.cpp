#include <iostream>
#include <ctime>
#include "logger_implementation.h"

std::map<std::string, std::pair<std::ofstream *, size_t>> logger_implementation::_all_streams =
        std::map<std::string, std::pair<std::ofstream *, size_t>>();

std::string logger_implementation::current_time()
{
    time_t t = time(nullptr);
    tm *now = localtime(&t);

    char current_time[64];
    strftime(current_time, sizeof(current_time), "%d/%m/%Y %X", now);

    return current_time;
}

std::string logger_implementation::severity_to_string(logger::severity severity_level)
{
    switch (severity_level)
    {
        case logger::severity::trace:
            return "TRACE";
        case logger::severity::debug:
            return "DEBUG";
        case logger::severity::information:
            return "INFORMATION";
        case logger::severity::warning:
            return "WARNING";
        case logger::severity::error:
            return "ERROR";
        case logger::severity::critical:
            return "CRITICAL";
    }
}

logger_implementation::logger_implementation(std::map<std::string, logger::severity> const &targets)
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

logger_implementation::~logger_implementation()
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

logger const *logger_implementation::log(const std::string &message, logger::severity severity_level) const
{
    for (auto & [target, stream_info] : _logger_streams)
    {
        if (stream_info.second > severity_level)
        {
            continue;
        }
        else
        {
            if (stream_info.first == nullptr)
            {
                std::cout << "[" << severity_to_string(severity_level) << "]" << "[" << current_time() << "] " << message << std::endl;
            }
            else
            {
                (*(stream_info.first)) << "[" << severity_to_string(severity_level) << "]" << "[" << current_time() << "] " << message << std::endl;
            }
        }
    }
    return this;
}
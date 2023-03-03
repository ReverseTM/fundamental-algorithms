#include <iostream>
#include <fstream>
#include "logger_implementation.h"

std::map<std::string, std::pair<std::ofstream *, size_t> > logger_implementation::_all_streams =
    std::map<std::string, std::pair<std::ofstream *, size_t>>();

logger_implementation::logger_implementation(std::map<std::string, logger::severity> const &targets)
{
    for (auto & [target, severity_level] : targets)
    {
        std::ofstream *stream = nullptr;
        auto current_stream = _all_streams.find(target);

        if (current_stream == _all_streams.end()) // такой поток не найден
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
            stream = current_stream->second.first; //присваеваем поток, который нашли
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

logger const *logger_implementation::log(const std::string & to_log, logger::severity severity_level) const
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
                std::cout << "[TODO: severity]" << "[TODO: datetime] " << to_log << std::endl;
            }
            else
            {
                (*stream_info.first) << "[TODO: severity]" << "[TODO: datetime] " << to_log << std::endl;
            }
        }
    }
    return this;
}
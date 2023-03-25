#include "memory.h"
#include "../logger/logger.h"
#include <sstream>

memory::memory_exception::memory_exception(const std::string &msg)
    : _msg(msg) {}

const char *memory::memory_exception::what() const noexcept
{
    return _msg.c_str();
}

std::string memory::address_to_string(const void* const address)
{
    return std::string { (std::stringstream () << address).str() };
}

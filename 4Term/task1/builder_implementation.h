#ifndef BUILDER_IMPLEMENTATION
#define BUILDER_IMPLEMENTATION
#include <iostream>
#include "builder.h"

class builder_implementation final : public builder
{
private:
    std::map<std::string, logger::severity> _settings;
    
public:
    builder* add_stream(std::string const &, logger::severity) override;

    logger* build() const override;
}; 

#endif //BUILDER_IMPLEMENTATION
#ifndef BUILDER_IMPLEMENTATION
#define BUILDER_IMPLEMENTATION
#include "builder.h"

class builder_implementation final : public builder
{
private:
    std::map<std::string, logger::severity> _settings;

public:
    builder* add_stream(std::string const &target, logger::severity level) override;

    logger* build() const override;
};

#endif //BUILDER_IMPLEMENTATION
#ifndef BUILDER_IMPLEMENTATION
#define BUILDER_IMPLEMENTATION
#include "builder.h"

class Builder_implementation final : public Builder
{
private:
    std::map<std::string, Logger::severity> _settings;

public:
    Builder* add_stream(std::string const &target, Logger::severity level) override;

    Logger* build() const override;
};

#endif //BUILDER_IMPLEMENTATION
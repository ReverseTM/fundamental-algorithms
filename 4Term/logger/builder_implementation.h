#ifndef BUILDER_IMPLEMENTATION
#define BUILDER_IMPLEMENTATION
#include <map>
#include "builder.h"

class builder_implementation final : public builder
{

private:

    std::map<std::string, fund_alg::logger::severity> _settings;

public:
    builder* add_stream(std::string const &target, fund_alg::logger::severity level) override;

    std::shared_ptr<fund_alg::logger> build() const override;
};

#endif //BUILDER_IMPLEMENTATION
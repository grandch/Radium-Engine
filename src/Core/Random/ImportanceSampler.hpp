#pragma once

#include <Core/Random/UniformGenerator.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API ImportanceSampler {
    virtual ImportanceSampler() = 0;
    virtual ~ImportanceSampler() = 0;
};

} // namespace Random
} // namespace Core
} // namespace Ra
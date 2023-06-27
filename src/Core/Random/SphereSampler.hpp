#pragma once

#include <Core/Random/ImportanceSampler.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API SphereSampler : public ImportanceSampler {
    virtual SphereSampler() = 0;
    virtual ~SphereSampler() = 0;

    virtual Vector2 getPoint( UniformGenerator* generator ) = 0;
    virtual Vector3 getDir( UniformGenerator* generator ) = 0;

    virtual Scalar pdf( Vector3 dir ) = 0;
    virtual Scalar pdf( Vector2 point ) = 0;
};

} // namespace Random
} // namespace Core
} // namespace Ra
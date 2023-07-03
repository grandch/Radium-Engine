#pragma once

#include <Core/Random/UniformGenerator.hpp>
#include <Core/Types.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API SphereSampler
{
  public:
    SphereSampler() {};
    ~SphereSampler() {};

    virtual std::pair<Vector2, Scalar> getPoint( UniformGenerator* generator ) = 0;
    virtual std::pair<Vector3, Scalar> getDir( UniformGenerator* generator )   = 0;

    virtual Scalar pdf( Vector3 dir, Vector3 normal ) = 0;
    virtual Scalar pdf( Vector2 point )               = 0;
};

} // namespace Random
} // namespace Core
} // namespace Ra

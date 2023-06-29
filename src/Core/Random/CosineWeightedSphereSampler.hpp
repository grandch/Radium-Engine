#pragma once

#include <Core/Random/SphereSampler.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API CosineWeightedSphereSampler : public SphereSampler {
  public:
    CosineWeightedSphereSampler() {};
    ~CosineWeightedSphereSampler() {};

    std::pair<Vector2, Scalar> getPoint( UniformGenerator* generator ) override;
    std::pair<Vector3, Scalar> getDir( UniformGenerator* generator ) override;

    Scalar pdf( Vector3 dir, Vector3 normal ) override;
    Scalar pdf( Vector2 point ) override;
};

} // namespace Random
} // namespace Core
} // namespace Ra
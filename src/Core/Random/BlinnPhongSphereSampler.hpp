#pragma once

#include <Core/Random/CosineWeightedSphereSampler.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API BlinnPhongSphereSampler : public CosineWeightedSphereSampler {
  public:
    BlinnPhongSphereSampler() {};
    ~BlinnPhongSphereSampler() {};

    std::pair<Vector2, Scalar> getPoint( UniformGenerator* generator, Scalar roughness );
    std::pair<Vector3, Scalar> getDir( UniformGenerator* generator, Scalar roughness );

    Scalar pdf( Vector3 dir, Vector3 normal, Scalar roughness );
    Scalar pdf( Vector2 point, Scalar roughness );
};

} // namespace Random
} // namespace Core
} // namespace Ra
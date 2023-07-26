#pragma once

#include <Core/Random/CosineWeightedSphereSampler.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API BlinnPhongSphereSampler : public CosineWeightedSphereSampler
{
  public:
    BlinnPhongSphereSampler() {};
    ~BlinnPhongSphereSampler() {};

    static std::pair<Vector3, Scalar> getDir( UniformGenerator* generator, Scalar roughness );

    static Scalar pdf( Vector3 dir, Vector3 normal, Scalar roughness );

    static Vector3 reflect( Vector3 inDir, Vector3 normal );
};

} // namespace Random
} // namespace Core
} // namespace Ra

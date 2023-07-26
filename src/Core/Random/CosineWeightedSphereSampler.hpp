#pragma once

#include <Core/Random/SphereSampler.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API CosineWeightedSphereSampler : public SphereSampler<CosineWeightedSphereSampler>
{
  public:
    CosineWeightedSphereSampler() {};
    ~CosineWeightedSphereSampler() {};

    static std::pair<Vector3, Scalar> getDirImplem( UniformGenerator* generator );

    static Scalar pdfImplem( Vector3 dir, Vector3 normal );
};

} // namespace Random
} // namespace Core
} // namespace Ra

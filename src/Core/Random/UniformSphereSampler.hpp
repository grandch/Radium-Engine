#pragma once

#include <Core/Random/SphereSampler.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API UniformSphereSampler : public SphereSampler<UniformSphereSampler>
{
  public:
    UniformSphereSampler() {};
    ~UniformSphereSampler() {};

    static std::pair<Vector2, Scalar> getPointImplem( UniformGenerator* generator );
    static std::pair<Vector3, Scalar> getDirImplem( UniformGenerator* generator );

    static Scalar pdfImplem( Vector3 dir, Vector3 normal );
    static Scalar pdfImplem( Vector2 point );
};

} // namespace Random
} // namespace Core
} // namespace Ra

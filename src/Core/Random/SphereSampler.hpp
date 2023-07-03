#pragma once

#include <Core/Random/UniformGenerator.hpp>
#include <Core/Types.hpp>

namespace Ra {
namespace Core {
namespace Random {

template <class T>
class RA_CORE_API SphereSampler
{
  public:
    SphereSampler() {};
    ~SphereSampler() {};

    static std::pair<Vector2, Scalar> getPoint( UniformGenerator* generator ) {
        T::getPointImplem( generator );
    }
    static std::pair<Vector3, Scalar> getDir( UniformGenerator* generator ) {
        T::getDirImplem( generator );
    }

    static Scalar pdf( Vector3 dir, Vector3 normal ) { T::pdfImplem( dir, normal ); }
    static Scalar pdf( Vector2 point ) { T::pdfImplem( point ); }
};

} // namespace Random
} // namespace Core
} // namespace Ra

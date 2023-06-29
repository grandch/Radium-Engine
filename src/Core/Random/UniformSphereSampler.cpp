#include "UniformSphereSampler.hpp"

namespace Ra {
namespace Core {
namespace Random {

std::pair<Vector2, Scalar> Ra::Core::Random::UniformSphereSampler::getPoint( UniformGenerator* generator ) {
    Vector2 u = generator->get2D();
    return {{u[0], 2 * Math::Pi * u[1]}, 1 / 2 * Math::Pi};
}

std::pair<Vector3, Scalar> Ra::Core::Random::UniformSphereSampler::getDir( UniformGenerator* generator ) {
    Vector3 dir;
    Vector2 u = generator->get2D();

    Scalar cosTheta = u[0];
    Scalar sinTheta = 1 - u[0];
    Scalar phi      = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos( phi );
    dir[1] = sinTheta * std::sin( phi );
    dir[2] = cosTheta;

    return {dir, 1 / 2 * Math::Pi};
}

} // namespace Random
} // namespace Core
} // namespace Ra
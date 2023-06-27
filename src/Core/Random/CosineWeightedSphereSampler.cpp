#include "CosineWeightedSphereSampler.hpp"

std::pair<Vector2, Scalar> Ra::Core::Random::CosineWeightedSphereSampler::getPoint( UniformGenerator* generator ) {
    Vector2 u = generator->get2D();
    return {{std::sqrt( u[0] ), 2 * Math::Pi * u[1]}, u[0] / Math::Pi};
}

std::pair<Vector3, Scalar> Ra::Core::Random::CosineWeightedSphereSampler::getDir( UniformGenerator* generator ) {
    Vector3 dir;
    Vector2 u = generator->get2D();

    Scalar cosTheta = std::sqrt( u[0] );
    Scalar sinTheta = std::sqrt( 1 - u[0] );
    Scalar phi      = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos( phi );
    dir[1] = sinTheta * std::sin( phi );
    dir[2] = cosTheta;

    return {dir, u[0] / Math::Pi};
}
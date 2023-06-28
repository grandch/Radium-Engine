#include "BlinnPhongSphereSampler.hpp"

std::pair<Vector2, Scalar>
Ra::Core::Random::BlinnPhongSphereSampler::getPoint( UniformGenerator* generator, Scalar roughness ) {
    return {{std::pow( u[0], 1_ra / ( roughness + 2 ) ), 2 * Math::Pi * u[1]}, ( roughness + 2 ) * std::pow( u[0], roughness ) / 2 * Math::Pi};
}

std::pair<Vector3, Scalar>
Ra::Core::Random::BlinnPhongSphereSampler::getDir( UniformGenerator* generator, Scalar roughness ) {
    Vector3 dir;
    Vector2 u = generator->get2D();

    Scalar cosTheta = std::pow( u[0], 1_ra / ( roughness + 2 ) );
    Scalar sinTheta = 1 - u[0];
    Scalar phi      = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos( phi );
    dir[1] = sinTheta * std::sin( phi );
    dir[2] = cosTheta;

    return { dir, ( roughness + 2 ) * std::pow( u[0], roughness ) / 2 * Math::Pi };
}

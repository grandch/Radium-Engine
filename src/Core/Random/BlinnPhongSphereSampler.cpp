#include <Core/Random/BlinnPhongSphereSampler.hpp>

#include <Core/Math/Math.hpp>

namespace Ra {
namespace Core {
namespace Random {

std::pair<Vector2, Scalar>
Ra::Core::Random::BlinnPhongSphereSampler::getPoint( UniformGenerator* generator,
                                                     Scalar roughness ) {
    Vector2 u = generator->get2D();
    return { { std::pow( u[0], 1_ra / ( roughness + 2 ) ), 2 * Math::Pi * u[1] },
             ( roughness + 2 ) * std::pow( u[0], roughness ) / 2 * Math::Pi };
}

std::pair<Vector3, Scalar>
Ra::Core::Random::BlinnPhongSphereSampler::getDir( UniformGenerator* generator, Scalar roughness ) {
    Vector3 dir;
    Vector2 u = generator->get2D();

    Scalar cosTheta = std::cos( std::pow( u[0], 1_ra / ( roughness + 2 ) ) );
    Scalar sinTheta = std::cos( Math::Pi / 2_ra - std::pow( u[0], 1_ra / ( roughness + 2 ) ) );
    Scalar phi      = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos( phi );
    dir[1] = sinTheta * std::sin( phi );
    dir[2] = cosTheta;

    return { dir, ( roughness + 2 ) * std::pow( u[0], roughness ) / 2 * Math::Pi };
}

Scalar BlinnPhongSphereSampler::pdf( Vector3 dir, Vector3 normal, Scalar roughness ) {
    dir.normalize();
    return ( roughness + 2 ) * std::pow( dir.dot( normal ), roughness ) / 2 * Math::Pi;
}

Scalar BlinnPhongSphereSampler::pdf( Vector2 point, Scalar roughness ) {
    return ( roughness + 2 ) * std::pow( point[0], roughness ) / 2 * Math::Pi;
}

} // namespace Random
} // namespace Core
} // namespace Ra

#include <Core/Random/BlinnPhongSphereSampler.hpp>

#include <Core/Math/Math.hpp>

namespace Ra {
namespace Core {
namespace Random {

std::pair<Vector3, Scalar>
Ra::Core::Random::BlinnPhongSphereSampler::getDir( UniformGenerator* generator, Scalar shininess ) {
    Vector3 dir;
    Vector2 u = generator->get2D();

    Scalar cosTheta = std::pow( 1_ra - u[0], 1_ra / ( shininess + 2 ) );
    Scalar sinTheta = std::sqrt( 1_ra - cosTheta * cosTheta );
    Scalar phi      = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos( phi );
    dir[1] = sinTheta * std::sin( phi );
    dir[2] = cosTheta;

    return { dir, ( shininess + 2 ) * std::pow( 1_ra - u[0], shininess ) / ( 2 * Math::Pi ) };
}

Scalar BlinnPhongSphereSampler::pdf( Vector3 dir, Vector3 normal, Scalar shininess ) {
    dir.normalize();
    return ( shininess + 2 ) * std::pow( dir.dot( normal ), shininess ) / ( 2 * Math::Pi );
}

Vector3 BlinnPhongSphereSampler::reflect( Vector3 inDir, Vector3 normal ) {
    return -inDir + 2 * inDir.dot( normal ) * normal;
}

} // namespace Random
} // namespace Core
} // namespace Ra

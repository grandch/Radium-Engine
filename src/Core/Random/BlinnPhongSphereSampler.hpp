#pragma once

#include <Core/Random/SphereSampler.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API BlinnPhongSphereSampler : public SphereSampler {
    BlinnPhongSphereSampler();
    ~BlinnPhongSphereSampler();

    static std::pair<Vector2, Scalar> getPoint( UniformGenerator* generator, Scalar roughness ) override;
    static std::pair<Vector3, Scalar> getDir( UniformGenerator* generator, Scalar roughness ) override;
};

} // namespace Random
} // namespace Core
} // namespace Ra
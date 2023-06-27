#pragma once

#include <Core/Random/SphereSampler.hpp>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API UniformSphereSampler : public SphereSampler {
    UniformSphereSampler();
    ~UniformSphereSampler();

    static std::pair<Vector2, Scalar> getPoint( UniformGenerator* generator ) override;
    static std::pair<Vector3, Scalar> getDir( UniformGenerator* generator ) override;
};

} // namespace Random
} // namespace Core
} // namespace Ra
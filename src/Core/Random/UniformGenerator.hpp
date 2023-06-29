#pragma once

#include <Core/Types.hpp>

#include <random>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API UniformGenerator {
  public:
    UniformGenerator() {};
    ~UniformGenerator() {};

    virtual Scalar get1D() = 0;
    
    virtual Vector2 get2D();
    virtual Vector3 get3D();
    virtual VectorN getXD(int dim);

    std::uniform_real_distribution<Scalar> m_unifDistributionRand { 0, 1 };
};

} // namespace Random
} // namespace Core
} // namespace Ra
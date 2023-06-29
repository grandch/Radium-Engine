#pragma once

#include <Core/Random/UniformGenerator.hpp>

#include <ctime>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API MersenneTwisterGenerator : public UniformGenerator {
  public:
    MersenneTwisterGenerator();
    ~MersenneTwisterGenerator();

    Scalar get1D() override;

    std::mt19937 m_randomEngine;
};

} // namespace Random
} // namespace Core
} // namespace Ra
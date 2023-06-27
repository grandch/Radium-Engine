#pragma once

#include <Core/Random/UniformGenerator.hpp>

#include <ctime>

namespace Ra {
namespace Core {
namespace Random {

class RA_CORE_API MersenneTwisterGenerator : public UniformGenerator {
    MersenneTwisterGenerator();
    ~MersenneTwisterGenerator();

    Scalar get1D();

    static std::mt19937 m_randomEngine = std::mt19937( std::time( nullptr ) );
};

std::mt19937 MersenneTwisterGenerator::m_randomEngine = std::mt19937( std::time( nullptr ) );

} // namespace Random
} // namespace Core
} // namespace Ra
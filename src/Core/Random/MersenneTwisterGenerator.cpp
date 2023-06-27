#include "MersenneTwisterGenerator.hpp"

Ra::Core::Random::MersenneTwisterGenerator::UniformGenerator() {}

Ra::Core::Random::MersenneTwisterGenerator::~MersenneTwisterGenerator() {}

Scalar Ra::Core::Random::MersenneTwisterGenerator::get1D() {
    return m_unifDistributionRand( m_randomEngine );
}
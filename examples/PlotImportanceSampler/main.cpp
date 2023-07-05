#include <Core/Random/BlinnPhongSphereSampler.hpp>
#include <Core/Random/CosineWeightedSphereSampler.hpp>
#include <Core/Random/MersenneTwisterGenerator.hpp>
#include <Core/Random/UniformSphereSampler.hpp>

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

int main( int /*argc*/, char** /*argv*/ ) {
    using namespace Ra::Core;
    using json = nlohmann::json;

    Random::MersenneTwisterGenerator generator = Random::MersenneTwisterGenerator();

    std::vector<Vector3> uSamplesDir, cSamplesDir, bSamplesDir01, bSamplesDir05, bSamplesDir09;
    // std::vector<Vector2> uSamplesPoint, cSamplesPoint, bSamplesPoint, lbSamplesPoint,
    //     bpSamplesPoint;

    for ( int i = 0; i < 500; i++ ) {
        uSamplesDir.push_back( Random::UniformSphereSampler::getDir( &generator ).first );
        cSamplesDir.push_back( Random::CosineWeightedSphereSampler::getDir( &generator ).first );
        bSamplesDir01.push_back( Random::BlinnPhongSphereSampler::getDir( &generator, 0.1 ).first );
        bSamplesDir05.push_back( Random::BlinnPhongSphereSampler::getDir( &generator, 0.5 ).first );
        bSamplesDir09.push_back( Random::BlinnPhongSphereSampler::getDir( &generator, 0.9 ).first );

        // uSamplesPoint.push_back( Random::UniformSphereSampler::getPoint( &generator ).first );
        // cSamplesPoint.push_back(
        //     Random::CosineWeightedSphereSampler::getPoint( &generator ).first );
        // bSamplesPoint.push_back( Random::BlinnPhongSphereSampler::getPoint( &generator, 0.7
        // ).first );
    }

    json j = { { "UniformSampleDir", uSamplesDir },
               { "CosineWeightedSampleDir", cSamplesDir },
               { "BlinnPhongSampleDir r=0.1", bSamplesDir01 },
               { "BlinnPhongSampleDir r=0.5", bSamplesDir05 },
               { "BlinnPhongSampleDir r=0.9", bSamplesDir09 } };
    //    { "UniformSamplePoint", uSamplesPoint },
    //    { "CosineWeightedSamplePoint", cSamplesPoint },
    //    { "BlinnPhongSamplePoint", bSamplesPoint }

    std::ofstream o( "samples.json" );

    o << std::setw( 4 ) << j << std::endl;

    o.close();

    return 0;
}

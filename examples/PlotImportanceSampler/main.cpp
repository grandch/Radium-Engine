#include <Core/Material/BlinnPhongMaterialModel.hpp>
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

    std::vector<Vector3> uSamplesDir, cSamplesDir, bSamplesDir4, bSamplesDir16, bSamplesDir64,
        bSamplesDir128, bpmat, lambmat;

    Material::BlinnPhongMaterialModel bpmaterial = Material::BlinnPhongMaterialModel();

    for ( int i = 0; i < 500; i++ ) {
        // uSamplesDir.push_back( Random::UniformSphereSampler::getDir( &generator ).first );
        // cSamplesDir.push_back( Random::CosineWeightedSphereSampler::getDir( &generator ).first );
        // bSamplesDir4.push_back( Random::BlinnPhongSphereSampler::getDir( &generator, 4 ).first );
        // bSamplesDir16.push_back( Random::BlinnPhongSphereSampler::getDir( &generator, 16 ).first
        // ); bSamplesDir64.push_back( Random::BlinnPhongSphereSampler::getDir( &generator, 64
        // ).first ); bSamplesDir128.push_back(
        //     Random::BlinnPhongSphereSampler::getDir( &generator, 128 ).first );

        bpmaterial.m_ns = 4;
        auto sample =
            bpmaterial.sample( { -1, 0, 1 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0 } );
        if ( sample.has_value() ) bSamplesDir4.push_back( sample.value().first );

        bpmaterial.m_ns = 16;
        sample = bpmaterial.sample( { -1, 0, 1 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0 } );
        if ( sample.has_value() ) bSamplesDir16.push_back( sample.value().first );

        bpmaterial.m_ns = 64;
        sample = bpmaterial.sample( { -1, 0, 1 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0 } );
        if ( sample.has_value() ) bSamplesDir64.push_back( sample.value().first );

        bpmaterial.m_ns = 128;
        sample = bpmaterial.sample( { -1, 0, 1 }, { 0, 0, 1 }, { 0, 1, 0 }, { 1, 0, 0 }, { 0, 0 } );
        if ( sample.has_value() ) bSamplesDir128.push_back( sample.value().first );
    }

    json j = { //{ "UniformSampleDir", uSamplesDir },
               //{ "CosineWeightedSampleDir", cSamplesDir },
               { "BlinnPhongSampleDir 4", bSamplesDir4 },
               { "BlinnPhongSampleDir 16", bSamplesDir16 },
               { "BlinnPhongSampleDir 64", bSamplesDir64 },
               { "BlinnPhongSampleDir 128", bSamplesDir128 } };
    //    {"BlinnPhongMaterial", bpmat}};
    //    { "UniformSamplePoint", uSamplesPoint },
    //    { "CosineWeightedSamplePoint", cSamplesPoint },
    //    { "BlinnPhongSamplePoint", bSamplesPoint }

    std::ofstream o( "samples.json" );

    o << std::setw( 4 ) << j << std::endl;

    o.close();

    return 0;
}

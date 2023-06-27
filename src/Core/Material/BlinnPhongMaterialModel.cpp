#include <Core/Material/BlinnPhongMaterialModel.hpp>
#include <Core/Math/LinearAlgebra.hpp>
#include <Core/Utils/Log.hpp>

#include <algorithm>

namespace Ra {
namespace Core {
namespace Material {
void BlinnPhongMaterialModel::displayInfo() const {
    using namespace Core::Utils; // log
    auto print = []( bool ok, const std::string& name, const auto& value ) {
        if ( ok ) { LOG( logINFO ) << name << value; }
        else { LOG( logINFO ) << name << "NO"; }
    };

    LOG( logINFO ) << "======== MATERIAL INFO ========";
    print( true, " Type           : ", getType() );
    print( true, " Kd             : ", m_kd.transpose() );
    print( true, " Ks             : ", m_ks.transpose() );
    print( true, " Ns             : ", m_ns );
    print( true, " Opacity        : ", m_alpha );
    print( hasDiffuseTexture(), " Kd Texture     : ", m_texDiffuse );
    print( hasSpecularTexture(), " Ks Texture     : ", m_texSpecular );
    print( hasShininessTexture(), " Ns Texture     : ", m_texShininess );
    print( hasNormalTexture(), " Normal Texture : ", m_texNormal );
    print( hasOpacityTexture(), " Alpha Texture  : ", m_texOpacity );
}
Utils::Color Material::BlinnPhongMaterialModel::evalBSDF( Vector3 w_i,
                                                          Vector3 w_o,
                                                          Vector3 normal,
                                                          Vector2 uv ) {
    // diffuse lambertien component
    Utils::Color diffuse = m_kd / M_PI;

    // Blinn-Phong specular component
    Vector3 halfway = w_i + w_o;
    halfway.normalize();
    Scalar specularIntensity =
        ( m_ns + 2.0f ) / ( 2.0f * M_PI ) * std::pow( normal.dot( halfway ), m_ns );
    Utils::Color specular = m_ks * specularIntensity;

    // Combine the diffuse and specular components
    Utils::Color bsdf = diffuse + specular;
}

std::optional<std::pair<Vector3, Scalar>>
BlinnPhongMaterialModel::sample( Vector3 inDir, Vector3 normal, Vector2 u ) {
    Vector3 halfway, tangent, bitangent;

    Math::coordinateSystem( normal, &tangent, &bitangent );

    Vector3 rgbToLuminance { 0.2126_ra, 0.7152_ra, 0.0722_ra };
    Scalar dIntensity   = m_kd.rgb().dot( rgbToLuminance );
    Scalar sIntensity   = m_ks.rgb().dot( rgbToLuminance );
    Scalar diffSpecNorm = std::max( 1_ra, dIntensity + sIntensity );

    dIntensity /= diffSpecNorm;
    sIntensity /= diffSpecNorm;

    Random::MersenneTwisterGenerator generator = Random::MersenneTwisterGenerator();
    Scalar distrib = generator.get1D();

    Scalar roughness = getRoughness();

    // diffuse part
    if ( distrib < dIntensity ) {
        std::pair<Vector3, Scalar> smpl = Random::CosineWeightedSphereSampler::getDir(&generator);
        Vector3 wi(
            smpl.first.dot( tangent ), smpl.first.dot( bitangent ), smpl.first.dot( normal ) );
        std::pair<Vector3, Scalar> result { wi, smpl.second };
        return result;
    }
    else if ( distrib < dIntensity + sIntensity ) { // specular part
        std::pair<Vector3, Scalar> smpl = Math::sampleSpecular( u, roughness );
        Vector3 wi(
            smpl.first.dot( tangent ), smpl.first.dot( bitangent ), smpl.first.dot( normal ) );
        std::pair<Vector3, Scalar> result { wi, smpl.second };
        return result;
    }
    else { // no next dir
        return {};
    }
}

Scalar BlinnPhongMaterialModel::PDF( Vector3 inDir, Vector3 outDir, Vector3 normal ) {
    Vector3 rgbToLuminance { 0.2126_ra, 0.7152_ra, 0.0722_ra };
    Scalar dIntensity   = m_kd.rgb().dot( rgbToLuminance );
    Scalar sIntensity   = m_ks.rgb().dot( rgbToLuminance );
    Scalar diffSpecNorm = std::max( 1_ra, dIntensity + sIntensity );

    dIntensity /= diffSpecNorm;
    sIntensity /= diffSpecNorm;

    return std::clamp( dIntensity * Math::cosineWeightedPDF( outDir, normal ) +
                           sIntensity * Math::specularPDF( outDir, normal, getRoughness() ),
                       0_ra,
                       1_ra );
}

Scalar BlinnPhongMaterialModel::getRoughness() {
    Scalar ns = m_ns;
    if ( ns > 1 ) { ns /= 128_ra; }
    Scalar r = std::clamp( 1 - ns, 0.04_ra, 0.96_ra );
    return 1 - m_ns;
}

std::mt19937* BlinnPhongMaterialModel::getRandomEngine() {

    return &m_randomEngine;
}

} // namespace Material
} // namespace Core
} // namespace Ra

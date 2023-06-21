#include <Core/Material/BlinnPhongMaterialModel.hpp>
#include <Core/Utils/Log.hpp>

#include "BlinnPhongMaterialModel.hpp"
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

    coordinateSystem( normal, &tangent, &bitangent );

    Vector3 rgbToLuminance { 0.2126_ra, 0.7152_ra, 0.0722_ra };
    Scalar dIntensity   = m_kd.rgb().dot( rgbToLuminance );
    Scalar sIntensity   = m_ks.rgb().dot( rgbToLuminance );
    Scalar diffSpecNorm = std::max( 1_ra, dIntensity + sIntensity );

    dIntensity /= diffSpecNorm;
    sIntensity /= diffSpecNorm;

    std::uniform_real_distribution<Scalar> unifDistributionRand { 0, 1 };
    Scalar distrib = unifDistributionRand( m_randomEngine );

    Scalar roughness = getRoughness();

    // diffuse part
    if ( distrib < dIntensity ) {
        std::pair<Vector3, Scalar> smpl = sampleHemisphereCosineWeighted( u );
        Vector3 wi(
            smpl.first.dot( tangent ), smpl.first.dot( bitangent ), smpl.first.dot( normal ) );
        std::pair<Vector3, Scalar> result { wi, smpl.second };
        return result;
    }
    else if ( distrib < dIntensity + sIntensity ) { // specular part
        std::pair<Vector3, Scalar> smpl = sampleSpecular( u, roughness );
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

    return std::clamp( dIntensity * cosineWeightedPDF( outDir, normal ) +
                           sIntensity * specularPDF( outDir, normal ),
                       0_ra,
                       1_ra );
}

std::pair<Vector3, Scalar> BlinnPhongMaterialModel::sampleSpecular( Vector2 u, Scalar roughness ) {
    Vector3 dir;

    Scalar cosTheta = std::pow( u[0], 1_ra / ( roughness + 2 ) );
    Scalar sinTheta = 1 - u[0];
    Scalar phi      = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos( phi );
    dir[1] = sinTheta * std::sin( phi );
    dir[2] = cosTheta;

    return { dir, ( roughness + 2 ) * std::pow( u[0], roughness ) / 2 * Math::Pi };
}

Scalar BlinnPhongMaterialModel::specularPDF( Vector3 dir, Vector3 normal, Scalar roughness ) {
    Scalar cosTheta = normal.dot( dir );
    return ( roughness + 2 ) * std::pow( cosTheta, roughness ) / 2 * Math::Pi;
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

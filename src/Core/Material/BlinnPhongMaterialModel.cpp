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
Utils::Color Material::BlinnPhongMaterialModel::evalBSDF( Vector3f w_i,
                                                          Vector3f w_o,
                                                          Vector3f normal,
                                                          Vector2f uv ) {
    // diffuse lambertien component
    Utils::Color diffuse = m_kd / M_PI;

    // Blinn-Phong specular component
    Vector3f halfway = w_i + w_o;
    halfway.normalize();
    Scalar specularIntensity = (m_ns + 2.0f) / (2.0f * M_PI) * std::pow(normal.dot(halfway), m_ns);
    Utils::Color specular = m_ks * specularIntensity;

    // Combine the diffuse and specular components
    Utils::Color bsdf = diffuse + specular;
}

std::optional<std::pair<Vector3f, Scalar>>
BlinnPhongMaterialModel::sample( Vector3f inDir, Vector3f normal, Vector2f u ) {
    /*
    compute intensity of diffuse and specular
    compute norm (max(1, Idiffuse + Ispecular))
    normalize Idiffuse and Ispecular
    */

    Vector3f nextDir, halfway;

    Scalar dIntensity = (m_kd.x() + m_kd.y() + m_kd.z()) / 3.f;
    Scalar sIntensity = (m_ks.x() + m_ks.y() + m_ks.z()) / 3.f;
    Scalar diffSpecNorm = std::max(1.f, dIntensity + sIntensity);

    dIntensity /= diffSpecNorm;
    sIntensity /= diffSpecNorm;

    std::uniform_real_distribution<Scalar> unifDistributionRand{0, 1};
    Scalar distrib = unifDistributionRand(m_randomEngine);

    // diffuse part
    if(distrib < dIntensity) {
        nextDir = sampleHemisphereCosineWeighted(u);
        std::pair<Vector3f, Scalar> result {nextDir, cosineWeightedPDF(nextDir, normal)};
        return result;
    } else if(distrib > dIntensity && distrib < dIntensity + sIntensity) { // specular part
        nextDir = sampleSpecular(inDir, u);
        // compute specular pdf
        std::pair<Vector3f, Scalar> result;
        return result;
    } else { // no next dir
        return {};
    }
}

Scalar BlinnPhongMaterialModel::PDF( Vector3f inDir, Vector3f outDir, Vector3f normal ) {
    Scalar dIntensity = (m_kd.x() + m_kd.y() + m_kd.z()) / 3.f;
    Scalar sIntensity = (m_ks.x() + m_ks.y() + m_ks.z()) / 3.f;
    Scalar diffSpecNorm = std::max(1.f, dIntensity + sIntensity);

    dIntensity /= diffSpecNorm;
    sIntensity /= diffSpecNorm;

    return std::clamp(dIntensity * cosineWeightedPDF(outDir, normal) + sIntensity * specularPDF(outDir, normal), Scalar(0), Scalar(1));
}

Scalar BlinnPhongMaterialModel::specularPDF( Vector3f dir, Vector3f normal ) {
    Scalar cosTheta = normal.dot(dir);
    Scalar result = ((m_ns + 1) / (2.0f * M_PI)) * std::pow(cosTheta, m_ns);

    return result;
}

std::minstd_rand BlinnPhongMaterialModel::getRandomEngine() {

    return m_randomEngine;
}

} // namespace Material
} // namespace Core
} // namespace Ra

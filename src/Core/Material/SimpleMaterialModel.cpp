#include <Core/Material/SimpleMaterialModel.hpp>

#include <Core/Utils/Log.hpp>
#include "SimpleMaterialModel.hpp"

namespace Ra {
namespace Core {
namespace Material {

void SimpleMaterialModel::displayInfo() const {
    using namespace Core::Utils; // log
    auto print = []( bool ok, const std::string& name, const auto& value ) {
        if ( ok ) { LOG( logINFO ) << name << value; }
        else { LOG( logINFO ) << name << "NO"; }
    };

    LOG( logINFO ) << "======== MATERIAL INFO ========";
    print( true, " Type           : ", getType() );
    print( true, " Kd             : ", m_kd.transpose() );
    print( true, " Opacity        : ", m_alpha );
    print( hasDiffuseTexture(), " Kd Texture     : ", m_texDiffuse );
    print( hasOpacityTexture(), " Alpha Texture  : ", m_texOpacity );
}

void LambertianMaterialModel::displayInfo() const {
    using namespace Core::Utils; // log
    auto print = []( bool ok, const std::string& name, const auto& value ) {
        if ( ok ) { LOG( logINFO ) << name << value; }
        else { LOG( logINFO ) << name << "NO"; }
    };

    LOG( logINFO ) << "======== MATERIAL INFO ========";
    print( true, " Type           : ", getType() );
    print( true, " Kd             : ", m_kd.transpose() );
    print( true, " Opacity        : ", m_alpha );
    print( hasDiffuseTexture(), " Kd Texture     : ", m_texDiffuse );
    print( hasNormalTexture(), " Normal Texture : ", m_texNormal );
    print( hasOpacityTexture(), " Alpha Texture  : ", m_texOpacity );
}

Utils::Color Material::LambertianMaterialModel::evalBSDF( Vector3f w_i,
                                                          Vector3f w_o,
                                                          Vector3f normal,
                                                          Vector2f uv ) {
    if(w_i.dot(normal) <= 0 || w_o.dot(normal) <= 0) {
        return Utils::Color::Black();
    }

    return m_kd * ( 1 / M_PI );
}

std::optional<std::pair<Vector3f, Scalar>> LambertianMaterialModel::sample( Vector3f inDir, Vector3f normal, Vector2f u ) {
    // create local to normal coordinate system
    Vector3f tangent, bitangent, point;
    coordinateSystem(normal, &tangent, &bitangent);

    // sample point on hemisphere with cosine-weighted distribution
    point = sampleHemisphereCosineWeighted(u);

    // transform sampled point from local to world coodinate system
    Vector3 wi(point.dot(tangent), point.dot(bitangent), point.dot(normal));
    std::pair<Vector3f, Scalar> result {wi, PDF(inDir, wi, normal)};

    return result;
}

Scalar LambertianMaterialModel::PDF( Vector3f inDir, Vector3f outDir, Vector3f normal ) {
    return cosineWeightedPDF(outDir, normal);
}

} // namespace Material
} // namespace Core
} // namespace Ra

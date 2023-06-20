#include <Core/Material/MaterialModel.hpp>
#include <Core/Utils/Log.hpp>
#include "MaterialModel.hpp"

namespace Ra {
namespace Core {
namespace Material {
void MaterialModel::displayInfo() const {
    using namespace Core::Utils; // log
    LOG( logERROR ) << "MaterialModel : unknown material type : " << m_materialType;
}

Utils::Color MaterialModel::evalBSDF( Vector3f w_i, Vector3f w_o, Vector3f normal, Vector2f uv ) {
    return Utils::Color();
}

std::optional<std::pair<Vector3f, Scalar>> MaterialModel::sample( Vector3f inDir, Vector3f normal, Vector2f u ) {
    return {};
}

Scalar MaterialModel::PDF( Vector3f inDir, Vector3f outDir, Vector3f normal ) {
    return 0.0f;
}

void MaterialModel::coordinateSystem( Vector3f normal, Vector3f* tangent, Vector3f* bitangent ) {
    if (std::abs(normal[0]) > std::abs(normal[1])) {
        Scalar invLen = 1 / std::sqrt(normal[0] * normal[0] + normal[2] * normal[2]);
        *tangent = Vector3f(-normal[2] * invLen, 0, normal[0] * invLen);
    } else {
        Scalar invLen = 1 / std::sqrt(normal[1] * normal[1] + normal[2] * normal[2]);
        *tangent = Vector3f(0, normal[2] * invLen, -normal[1] * invLen);
    }
    *bitangent = normal.cross(*tangent);
}

std::pair<Vector3f, Scalar> MaterialModel::sampleHemisphereCosineWeighted( Vector2f u ) {
    Vector3f dir;
    
    Scalar cosTheta = std::sqrt(u[0]);
    Scalar sinTheta = std::sqrt(1-u[0]);
    Scalar phi = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos(phi);
    dir[1] = sinTheta * std::sin(phi);
    dir[2] = cosTheta;
    
    return {dir, cosTheta/Math::Pi};
}

std::pair<Vector3f, Scalar> MaterialModel::sampleHemisphere( Vector2 u ) {
    Vector3f dir;
    
    Scalar cosTheta = u[0];
    Scalar sinTheta = 1-u[0];
    Scalar phi = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos(phi);
    dir[1] = sinTheta * std::sin(phi);
    dir[2] = cosTheta;
    
    return {dir, 1_ra/(2_ra*Math::Pi)};
}

Scalar MaterialModel::cosineWeightedPDF( Vector3f dir, Vector3f normal ) {
    dir.normalize();

    Scalar cosTheta = dir.dot(normal);

    return cosTheta / M_PI;
}

} // namespace Material
} // namespace Core
} // namespace Ra

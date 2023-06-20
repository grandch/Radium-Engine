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

Utils::Color MaterialModel::evalBSDF( Vector3 w_i, Vector3 w_o, Vector3 normal, Vector2 uv ) {
    return Utils::Color();
}

std::optional<std::pair<Vector3, Scalar>> MaterialModel::sample( Vector3 inDir, Vector3 normal, Vector2 u ) {
    return {};
}

Scalar MaterialModel::PDF( Vector3 inDir, Vector3 outDir, Vector3 normal ) {
    return 0.0f;
}

void MaterialModel::coordinateSystem( Vector3 normal, Vector3* tangent, Vector3* bitangent ) {
    if (std::abs(normal[0]) > std::abs(normal[1])) {
        Scalar invLen = 1 / std::sqrt(normal[0] * normal[0] + normal[2] * normal[2]);
        *tangent = Vector3(-normal[2] * invLen, 0, normal[0] * invLen);
    } else {
        Scalar invLen = 1 / std::sqrt(normal[1] * normal[1] + normal[2] * normal[2]);
        *tangent = Vector3(0, normal[2] * invLen, -normal[1] * invLen);
    }
    *bitangent = normal.cross(*tangent);
}

std::pair<Vector3, Scalar> MaterialModel::sampleHemisphereCosineWeighted( Vector2 u ) {
    Vector3 dir;
    
    Scalar cosTheta = std::sqrt(u[0]);
    Scalar sinTheta = std::sqrt(1-u[0]);
    Scalar phi = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos(phi);
    dir[1] = sinTheta * std::sin(phi);
    dir[2] = cosTheta;
    
    return {dir, cosTheta/Math::Pi};
}

std::pair<Vector3, Scalar> MaterialModel::sampleHemisphere( Vector2 u ) {
    Vector3 dir;
    
    Scalar cosTheta = u[0];
    Scalar sinTheta = 1-u[0];
    Scalar phi = 2 * Math::Pi * u[1];

    dir[0] = sinTheta * std::cos(phi);
    dir[1] = sinTheta * std::sin(phi);
    dir[2] = cosTheta;
    
    return {dir, 1_ra/(2_ra*Math::Pi)};
}

Scalar MaterialModel::cosineWeightedPDF( Vector3 dir, Vector3 normal ) {
    dir.normalize();

    Scalar cosTheta = dir.dot(normal);

    return cosTheta / M_PI;
}

} // namespace Material
} // namespace Core
} // namespace Ra

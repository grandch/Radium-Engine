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

Vector3f MaterialModel::sampleSpecular(Vector3f inDir, Vector2f u) {
    Vector3f nextDir, halfway;

    halfway = sampleHemisphereCosineWeighted(u);
    nextDir = inDir - 2.0f * inDir.dot(halfway) * halfway;

    return nextDir;
}

Vector3f MaterialModel::sampleHemisphereCosineWeighted( Vector2f u ) {
    Vector3f point;
    
    Scalar r = std::sqrt(u[0]);
    Scalar phi = 2 * M_PI * u[1];

    point[0] = r * std::cos(phi);
    point[1] = r * std::sin(phi);
    point[2] = std::sqrt(std::max(0.f, 1 - point[0]*point[0] - point[1]*point[1]));
    
    return point;
}

Vector3f MaterialModel::sampleHemisphere( Vector3f normal ) {
    Vector3f vec = Vector3f::Random(3,1);
    vec /= vec.norm();

    if(vec.dot(normal) > 0) {
        return vec;
    }
    
    return -vec;
}

Scalar MaterialModel::cosineWeightedPDF( Vector3f dir, Vector3f normal ) {
    dir.normalize();

    Scalar cosTheta = dir.dot(normal);

    return cosTheta / M_PI;
}

} // namespace Material
} // namespace Core
} // namespace Ra

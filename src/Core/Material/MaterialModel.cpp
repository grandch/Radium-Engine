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

std::optional<Vector3f> MaterialModel::sample( Vector3f inDir, Vector3f normal, Vector2f u ) {
    return std::optional<Vector3f>();
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

Vector3f MaterialModel::randomInHemisphere( Vector3f normal ) {
    Vector3f vec = Vector3f::Random(3,1);
    vec /= vec.norm();

    if(vec.dot(normal) > 0) {
        return vec;
    }
    
    return -vec;
}

} // namespace Material
} // namespace Core
} // namespace Ra

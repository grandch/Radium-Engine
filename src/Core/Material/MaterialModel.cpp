#include "MaterialModel.hpp"
#include <Core/Material/MaterialModel.hpp>
#include <Core/Utils/Log.hpp>

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

std::optional<std::pair<Vector3, Scalar>>
MaterialModel::sample( Vector3 inDir, Vector3 normal, Vector2 u ) {
    return {};
}

Scalar MaterialModel::PDF( Vector3 inDir, Vector3 outDir, Vector3 normal ) {
    return 0.0_ra;
}

} // namespace Material
} // namespace Core
} // namespace Ra

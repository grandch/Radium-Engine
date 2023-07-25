#pragma once

#include <Core/Material/SimpleMaterialModel.hpp>
#include <Core/Random/BlinnPhongSphereSampler.hpp>
#include <Core/Random/UniformGenerator.hpp>
#include <Core/Utils/Color.hpp>

#include <ctime>

namespace Ra {
namespace Core {
namespace Material {

// RADIUM SUPPORTED MATERIALS
class RA_CORE_API BlinnPhongMaterialModel : public SimpleMaterialModel
{
  public:
    explicit BlinnPhongMaterialModel( const std::string& name = "" ) :
        SimpleMaterialModel( name, "BlinnPhong" ) {}

    explicit BlinnPhongMaterialModel( Core::Random::UniformGenerator* generator,
                                      const std::string& name = "" ) :
        SimpleMaterialModel( name, "BlinnPhong", generator ) {}

    ~BlinnPhongMaterialModel() override = default;

    /// DEBUG
    void displayInfo() const override;

    /// QUERY

    bool hasSpecularTexture() const { return m_hasTexSpecular; }

    bool hasShininessTexture() const { return m_hasTexShininess; }

    bool hasNormalTexture() const { return m_hasTexNormal; }

    Utils::Color evalBSDF( Vector3 w_i, Vector3 w_o, Vector3 normal, Vector2 uv ) override;
    std::optional<std::pair<Vector3, Scalar>>
    sample( Vector3 inDir, Vector3 normal, Vector3 tangent, Vector3 bitangent, Vector2 u ) override;
    Scalar PDF( Vector3 inDir, Vector3 outDir, Vector3 normal ) override;

    /// DATA MEMBERS
    Core::Utils::Color m_ks { 0.3_ra, 0.3_ra, 0.3_ra };
    Scalar m_ns { 64_ra };
    std::string m_texSpecular;
    std::string m_texShininess;
    std::string m_texNormal;
    bool m_hasTexSpecular { false };
    bool m_hasTexShininess { false };
    bool m_hasTexNormal { false };
};

} // namespace Material
} // namespace Core
} // namespace Ra

#pragma once

#include <Core/Material/MaterialModel.hpp>
#include <Core/Random/CosineWeightedSphereSampler.hpp>
#include <Core/Random/MersenneTwisterGenerator.hpp>
#include <Core/Random/UniformGenerator.hpp>
#include <Core/Utils/Color.hpp>

namespace Ra {
namespace Core {
namespace Material {

// RADIUM SUPPORTED MATERIALS
class RA_CORE_API SimpleMaterialModel : public MaterialModel
{
  protected:
    SimpleMaterialModel( const std::string& name, const std::string type ) :
        m_generator( new Core::Random::MersenneTwisterGenerator() ), MaterialModel( name, type ) {}

    SimpleMaterialModel( const std::string& name,
                         const std::string type,
                         Core::Random::UniformGenerator* generator ) :
        MaterialModel( name, type ) {
        *m_generator = *generator;
    }

  public:
    explicit SimpleMaterialModel( const std::string& name = "" ) : MaterialModel( name, "Plain" ) {}
    ~SimpleMaterialModel() override = default;

    /// DEBUG
    void displayInfo() const override;

    /// QUERY
    bool hasDiffuseTexture() const { return m_hasTexDiffuse; }
    bool hasOpacityTexture() const { return m_hasTexOpacity; }

    Utils::Color evalBSDF( Vector3 w_i, Vector3 w_o, Vector3 normal, Vector2 uv ) override;
    std::optional<std::pair<Vector3, Scalar>>
    sample( Vector3 inDir, Vector3 normal, Vector3 tangent, Vector3 bitangent, Vector2 u ) override;
    Scalar PDF( Vector3 inDir, Vector3 outDir, Vector3 normal ) override;

    /// DATA MEMBERS
    Core::Utils::Color m_kd { 0.9_ra, 0.9_ra, 0.9_ra };
    Scalar m_alpha { 1_ra };
    std::string m_texDiffuse;
    std::string m_texOpacity;
    bool m_hasTexDiffuse { false };
    bool m_hasTexOpacity { false };

    Core::Random::UniformGenerator* m_generator;
};

class RA_CORE_API LambertianMaterialModel : public SimpleMaterialModel
{
  public:
    explicit LambertianMaterialModel( const std::string& name = "" ) :
        m_sampler( Core::Random::CosineWeightedSphereSampler() ),
        SimpleMaterialModel( name, "Lambertian" ) {}

    explicit LambertianMaterialModel( Core::Random::UniformGenerator* generator,
                                      const std::string& name = "" ) :
        m_sampler( Core::Random::CosineWeightedSphereSampler() ),
        SimpleMaterialModel( name, "Lambertian", generator ) {}

    ~LambertianMaterialModel() override = default;

    /// DEBUG
    void displayInfo() const override;

    /// QUERY
    bool hasNormalTexture() const { return m_hasTexNormal; }

    Utils::Color evalBSDF( Vector3 w_i, Vector3 w_o, Vector3 normal, Vector2 uv ) override;
    std::optional<std::pair<Vector3, Scalar>>
    sample( Vector3 inDir, Vector3 normal, Vector3 tangent, Vector3 bitangent, Vector2 u ) override;
    Scalar PDF( Vector3 inDir, Vector3 outDir, Vector3 normal ) override;

    /// DATA MEMBERS
    std::string m_texNormal;
    bool m_hasTexNormal { false };

    Core::Random::CosineWeightedSphereSampler m_sampler;
};

} // namespace Material
} // namespace Core
} // namespace Ra

#pragma once
#include <string>
#include <memory>
#include <optional>

#include <Core/RaCore.hpp>

#include <Core/Utils/Observable.hpp>

#include <Core/Utils/Color.hpp>
#include <Core/Types.hpp>

namespace Ra {
namespace Core {
namespace Material {

/** @brief represent material model, loaded by a file loader.
 *
 */
class RA_CORE_API MaterialModel : public Utils::ObservableVoid
{
  public:
    /// MATERIAL DATA
    MaterialModel( const std::string& name = "", const std::string& type = "AbstractMaterial" );
    virtual ~MaterialModel() { detachAll(); };

    /// NAME
    inline const std::string& getName() const { return m_name; }
    inline void setName( const std::string& name ) { m_name = name; }

    /// TYPE
    inline std::string getType() const { return m_materialType; }
    inline void setType( const std::string& type ) { m_materialType = type; }

    /// DEBUG
    virtual void displayInfo() const;

    virtual Utils::Color evalBSDF(Vector3f w_i, Vector3f w_o, Vector3f normal, Vector2f uv);
    virtual std::optional<std::pair<Vector3f, Scalar>> sample(Vector3f inDir, Vector3f normal, Vector2f u);
    virtual Scalar PDF(Vector3f inDir, Vector3f outDir, Vector3f normal);

    void coordinateSystem(Vector3f normal, Vector3f* tangent, Vector3f* bitangent);

    Vector3f sampleSpecular(Vector3f inDir, Vector2f u);
    Vector3f sampleHemisphereCosineWeighted(Vector2f u);
    Vector3f sampleHemisphere(Vector3f normal);

    Scalar cosineWeightedPDF(Vector3f dir, Vector3f normal);

  private:
    std::string m_materialType;
    std::string m_name;
};

/**
 * \brief Convenient alias for material usage
 */

using MaterialModelPtr = std::shared_ptr<MaterialModel>;

inline MaterialModel::MaterialModel( const std::string& name, const std::string& type ) :
    m_materialType { type }, m_name { name } {}

} // namespace Material
} // namespace Core
} // namespace Ra

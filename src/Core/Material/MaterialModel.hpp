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

    virtual Utils::Color evalBSDF(Vector3 w_i, Vector3 w_o, Vector3 normal, Vector2 uv);
    virtual std::optional<std::pair<Vector3, Scalar>> sample(Vector3 inDir, Vector3 normal, Vector2 u);
    virtual Scalar PDF(Vector3 inDir, Vector3 outDir, Vector3 normal);

    void coordinateSystem(Vector3 normal, Vector3* tangent, Vector3* bitangent);

    std::pair<Vector3, Scalar> sampleHemisphereCosineWeighted(Vector2 u);
    std::pair<Vector3, Scalar> sampleHemisphere(Vector2 u);

    Scalar cosineWeightedPDF(Vector3 dir, Vector3 normal);

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

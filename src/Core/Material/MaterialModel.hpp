#pragma once
#include <memory>
#include <optional>
#include <string>

#include <Core/RaCore.hpp>

#include <Core/Utils/Observable.hpp>

#include <Core/Types.hpp>
#include <Core/Utils/Color.hpp>

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

    /** Compute BSDF value for a set of directions and texture coordinates.
     *  w_i : incident direction, w_o : outgoing direction, normal : geometric normal direction.
     *  w_i, w_o and normal are in world space.
     */
    virtual Utils::Color evalBSDF( Vector3 w_i, Vector3 w_o, Vector3 normal, Vector2 uv ) = 0;
    virtual std::optional<std::pair<Vector3, Scalar>>
    sample( Vector3 inDir, Vector3 normal, Vector2 u ) = 0;
    virtual Scalar PDF( Vector3 inDir, Vector3 outDir, Vector3 normal ) = 0;

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

#include <Core/Math/Math.hpp>
#include <Core/Random/BlinnPhongSphereSampler.hpp>
#include <Core/Random/CosineWeightedSphereSampler.hpp>
#include <Core/Random/UniformGenerator.hpp>
#include <Core/Random/UniformSphereSampler.hpp>
#include <Core/Types.hpp>

#include <catch2/catch.hpp>

using namespace Ra::Core;

/// @brief Fake random generator class to test the samplers
class FakeGenerator : public Random::UniformGenerator
{
  public:
    FakeGenerator() {};
    ~FakeGenerator() {};

    Scalar get1D() override { return m_1D; }

    Vector2 get2D() override { return m_2D; }

    Vector3 get3D() override { return m_3D; }

    VectorN getXD( int dim ) override { return m_XD; }

    void set1D( Scalar s ) { m_1D = s; }
    void set2D( Vector2 v ) { m_2D = v; }
    void set3D( Vector3 v ) { m_3D = v; }
    void setXD( VectorN v ) { m_XD = v; }

  private:
    Scalar m_1D;
    Vector2 m_2D;
    Vector3 m_3D;
    VectorN m_XD;
};

TEST_CASE( "Core/Random/UniformSphereSampler" ) {
    auto fg = FakeGenerator();
    SECTION( "getDir" ) {
        fg.set2D( { 0_ra, 0_ra } );
        auto p    = Random::UniformSphereSampler::getDir( &fg );
        Vector3 d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 1_ra ) );

        fg.set2D( { 1_ra, 1_ra } );
        p = Random::UniformSphereSampler::getDir( &fg );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0.84147_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.5403_ra, 1000_ra ) );

        fg.set2D( { 0.5_ra, 0.5_ra } );
        p = Random::UniformSphereSampler::getDir( &fg );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), -0.48_ra, 1000_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.88_ra ) );
    }

    SECTION( "pdf" ) {
        Vector3 normal, dir;
        Scalar usspdf;

        normal = { 0_ra, 0_ra, 1_ra };
        dir    = { 0_ra, 0_ra, 1_ra };
        usspdf = Random::UniformSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 1 / ( 2 * Math::Pi ) ) );

        dir    = { 0_ra, 1_ra, 0_ra };
        usspdf = Random::UniformSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 1 / ( 2 * Math::Pi ) ) );

        dir    = { 1_ra, 0_ra, 0_ra };
        usspdf = Random::UniformSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 1 / ( 2 * Math::Pi ) ) );
    }
}

TEST_CASE( "Core/Random/CosineWeightedSphereSampler" ) {
    auto fg = FakeGenerator();
    SECTION( "getDir" ) {
        fg.set2D( { 0_ra, 0_ra } );
        auto p    = Random::CosineWeightedSphereSampler::getDir( &fg );
        Vector3 d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 1_ra ) );

        fg.set2D( { 1_ra, 1_ra } );
        p = Random::CosineWeightedSphereSampler::getDir( &fg );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0.84147_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.54_ra, 1000_ra ) );

        fg.set2D( { 0.5_ra, 0.5_ra } );
        p = Random::CosineWeightedSphereSampler::getDir( &fg );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), -0.65_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.76_ra ) );
    }

    SECTION( "pdf" ) {
        Vector3 normal, dir;
        Scalar usspdf;

        normal = { 0_ra, 0_ra, 1_ra };
        dir    = { 0_ra, 0_ra, 1_ra };
        usspdf = Random::CosineWeightedSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 1 / Math::Pi ) );

        dir    = { 0_ra, 1_ra, 0_ra };
        usspdf = Random::CosineWeightedSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 0_ra ) );

        dir    = { 1_ra, 0_ra, 0_ra };
        usspdf = Random::CosineWeightedSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 0_ra ) );
    }
}

TEST_CASE( "Core/Random/BlinnPhongSphereSampler" ) {
    auto fg = FakeGenerator();
    SECTION( "getDir" ) {
        fg.set2D( { 0_ra, 0_ra } );
        auto p    = Random::BlinnPhongSphereSampler::getDir( &fg, 8 );
        Vector3 d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 1_ra ) );

        fg.set2D( { 1_ra, 1_ra } );
        p = Random::BlinnPhongSphereSampler::getDir( &fg, 32 );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 1_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0_ra ) );

        fg.set2D( { 0.5_ra, 0.5_ra } );
        p = Random::BlinnPhongSphereSampler::getDir( &fg, 128 );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), -0.1_ra, 1000_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.99_ra ) );
    }

    SECTION( "pdf" ) {
        Vector3 normal;
        Scalar usspdf;

        normal = { 0_ra, 0_ra, 1_ra };
        usspdf = Random::BlinnPhongSphereSampler::pdf(
            { 0_ra, 0_ra, 1_ra },
            Random::BlinnPhongSphereSampler::reflect( { 0_ra, 0_ra, 1_ra }, normal ),
            normal,
            8_ra );
        REQUIRE( Math::areApproxEqual( usspdf, 1.59155_ra ) );

        usspdf = Random::BlinnPhongSphereSampler::pdf(
            { 0_ra, 1_ra, 0_ra }, { 0.02_ra, -0.97_ra, 0.01_ra }, normal, 4_ra );
        REQUIRE( Math::areApproxEqual( usspdf, 0.038187_ra ) );

        usspdf = Random::BlinnPhongSphereSampler::pdf(
            { 1_ra, 0_ra, 0.5_ra }, { -1.01_ra, 0.03_ra, 0.49_ra }, normal, 32_ra );
        REQUIRE( Math::areApproxEqual( usspdf, 5.33004_ra, 1000_ra ) );
    }

    SECTION( "reflect" ) {
        Vector3 normal = { 0_ra, 0_ra, 1_ra };

        Vector3 reflected =
            Random::BlinnPhongSphereSampler::reflect( { 0_ra, 0_ra, -1_ra }, normal );
        REQUIRE( Math::areApproxEqual( reflected.x(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.z(), -1_ra, 1000_ra ) );

        reflected = Random::BlinnPhongSphereSampler::reflect( { 1_ra, 0_ra, 0_ra }, normal );
        REQUIRE( Math::areApproxEqual( reflected.x(), -1_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.z(), 0_ra ) );

        reflected = Random::BlinnPhongSphereSampler::reflect( { 0.5_ra, 0.5_ra, -0.5_ra }, normal );
        REQUIRE( Math::areApproxEqual( reflected.x(), -0.5_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.y(), -0.5_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.z(), -0.5_ra ) );
    }
}

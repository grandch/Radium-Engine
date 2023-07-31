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
        fg.set2D( { 0, 0 } );
        auto p    = Random::UniformSphereSampler::getDir( &fg );
        Vector3 d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 1_ra ) );

        fg.set2D( { 1, 1 } );
        p = Random::UniformSphereSampler::getDir( &fg );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0.84147_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.5403_ra ) );

        fg.set2D( { 0.5, 0.5 } );
        p = Random::UniformSphereSampler::getDir( &fg );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), -0.48_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.88_ra ) );
    }

    SECTION( "pdf" ) {
        Vector3 normal, dir;
        Scalar usspdf;

        normal = { 0, 0, 1 };
        dir    = { 0, 0, 1 };
        usspdf = Random::UniformSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 1 / ( 2 * Math::Pi ) ) );

        dir    = { 0, 1, 0 };
        usspdf = Random::UniformSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 1 / ( 2 * Math::Pi ) ) );

        dir    = { 1, 0, 0 };
        usspdf = Random::UniformSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 1 / ( 2 * Math::Pi ) ) );
    }
}

TEST_CASE( "Core/Random/CosineWeightedSphereSampler" ) {
    auto fg = FakeGenerator();
    SECTION( "getDir" ) {
        fg.set2D( { 0, 0 } );
        auto p    = Random::CosineWeightedSphereSampler::getDir( &fg );
        Vector3 d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 1_ra ) );

        fg.set2D( { 1, 1 } );
        p = Random::CosineWeightedSphereSampler::getDir( &fg );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0.84147_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.54_ra ) );

        fg.set2D( { 0.5, 0.5 } );
        p = Random::CosineWeightedSphereSampler::getDir( &fg );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), -0.65_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.76_ra ) );
    }

    SECTION( "pdf" ) {
        Vector3 normal, dir;
        Scalar usspdf;

        normal = { 0, 0, 1 };
        dir    = { 0, 0, 1 };
        usspdf = Random::CosineWeightedSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 1 / Math::Pi ) );

        dir    = { 0, 1, 0 };
        usspdf = Random::CosineWeightedSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 0_ra ) );

        dir    = { 1, 0, 0 };
        usspdf = Random::CosineWeightedSphereSampler::pdf( dir, normal );
        REQUIRE( Math::areApproxEqual( usspdf, 0_ra ) );
    }
}

TEST_CASE( "Core/Random/BlinnPhongSphereSampler" ) {
    auto fg = FakeGenerator();
    SECTION( "getDir" ) {
        fg.set2D( { 0, 0 } );
        auto p    = Random::BlinnPhongSphereSampler::getDir( &fg, 8 );
        Vector3 d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 1_ra ) );

        fg.set2D( { 1, 1 } );
        p = Random::BlinnPhongSphereSampler::getDir( &fg, 32 );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), 1_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0_ra ) );

        fg.set2D( { 0.5, 0.5 } );
        p = Random::BlinnPhongSphereSampler::getDir( &fg, 128 );
        d = p.first;
        REQUIRE( Math::areApproxEqual( d.x(), -0.1_ra ) );
        REQUIRE( Math::areApproxEqual( d.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( d.z(), 0.99_ra ) );
    }

    SECTION( "pdf" ) {
        Vector3 normal;
        Scalar usspdf;

        normal = { 0, 0, 1 };
        usspdf = Random::BlinnPhongSphereSampler::pdf(
            { 0, 0, 1 },
            Random::BlinnPhongSphereSampler::reflect( { 0, 0, 1 }, normal ),
            normal,
            8 );
        REQUIRE( Math::areApproxEqual( usspdf, 1.59155_ra ) );

        usspdf =
            Random::BlinnPhongSphereSampler::pdf( { 0, 1, 0 }, { 0.02, -0.97, 0.01 }, normal, 4 );
        REQUIRE( Math::areApproxEqual( usspdf, 0.038187_ra ) );

        usspdf = Random::BlinnPhongSphereSampler::pdf(
            { 1, 0, 0.5 }, { -1.01, 0.03, 0.49 }, normal, 32 );
        REQUIRE( Math::areApproxEqual( usspdf, 5.33004_ra ) );
    }

    SECTION( "reflect" ) {
        Vector3 normal = { 0, 0, 1 };

        Vector3 reflected = Random::BlinnPhongSphereSampler::reflect( { 0, 0, -1 }, normal );
        REQUIRE( Math::areApproxEqual( reflected.x(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.z(), 1_ra ) );

        reflected = Random::BlinnPhongSphereSampler::reflect( { 1, 0, 0 }, normal );
        REQUIRE( Math::areApproxEqual( reflected.x(), -1_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.y(), 0_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.z(), 0_ra ) );

        reflected = Random::BlinnPhongSphereSampler::reflect( { 0.5, 0.5, -0.5 }, normal );
        REQUIRE( Math::areApproxEqual( reflected.x(), -0.5_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.y(), -0.5_ra ) );
        REQUIRE( Math::areApproxEqual( reflected.z(), -0.5_ra ) );
    }
}

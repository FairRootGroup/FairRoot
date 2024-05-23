/********************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairGeoAssembly.h"
#include "FairGeoBasicShape.h"
#include "FairGeoBrik.h"
#include "FairGeoCone.h"
#include "FairGeoCons.h"
#include "FairGeoEltu.h"
#include "FairGeoPcon.h"
#include "FairGeoPgon.h"
#include "FairGeoSphe.h"
#include "FairGeoTorus.h"
#include "FairGeoTrap.h"
#include "FairGeoTrd1.h"
#include "FairGeoTube.h"
#include "FairGeoTubs.h"
#include "FairGeoVolume.h"
#include "checks_FairGeoBasicShape.h"
#include "generate_TestInput.h"

#include <string>
#include <vector>

using fairroot::tests::check_FairGeoShape_Construction;
using fairroot::tests::check_FairGeoShape_ReadWrite;

TEST_CASE("FairGeoBasicShape")
{
    FairGeoBasicShape shape;

    check_FairGeoShape_Construction(shape, std::string{""}, 0, nullptr);
}

TEST_CASE("FairGeoAssembly")
{
    FairGeoAssembly shape;
    std::unique_ptr<TArrayD> paramArray(new TArrayD(0));
    check_FairGeoShape_Construction(shape, std::string{"ASSEMBLY"}, 0, paramArray.get());
}

TEST_CASE("FairGeoBrik")
{
    // The box is defined by 3 parameters (cartesian coordinates) for each of
    // the 8 corners of the box
    // The data to generate the necessary input file is organized in three
    // parameter vectors with 8 values each. All parameter vectors are stored
    // into another vector
    Int_t numPoints{8};
    Int_t numParams{3};
    std::vector<float> x{1., 1., -1., -1., 1., 1., -1., -1.};
    std::vector<float> y{-1., 1., 1., -1., -1., 1., 1., -1.};
    std::vector<float> z{-1., -1., -1., -1., 1., 1., 1., 1.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoBrik shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"BOX "}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"BOX"}, numPoints, parameters);
}

TEST_CASE("FairGeoCone")
{
    // The cone is defined by by the coordinates (x,y,z) where
    // the cone begins and the inner and outer radius at that point,
    // as well as the same information for the point where the cone ends.
    // The parameters are groups as four points
    // Point 1: x, y, z coordinate of the center of the circle at the beginning of the cone
    // Point 2: inner and outer radius at the beginning of the cone
    // Point 3: x, y, z coordinate of the center of the circle at the end of the cone
    // Point 4: inner and outer radius at the end of the cone
    // The third values of point 2 and 4 are not used and exist for technical
    // reasons
    Int_t numPoints{4};
    Int_t numParams{5};
    std::vector<float> x{0., 1., 0., 2.};
    std::vector<float> y{0., 2., 0., 3.};
    std::vector<float> z{0., 654., 20., -765.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoCone shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"CONE"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"CONE"}, numPoints, parameters);
}

TEST_CASE("FairGeoCons")
{
    // A cons is a cone having only a range in phi (from phi1 to phi2).
    // The parameters are grouped as five points
    // Point 1: x, y, z coordinate of the center of the circle at the beginning of the cons
    // Point 2: inner and outer radius at the beginning of the cons
    // Point 3: x, y, z coordinate of the center of the circle at the end of the cons
    // Point 4: inner and outer radius at the end of the cons
    // Point 5: starting angle PHI1 and ending angle PHI2 of the segment
    // The third values of point 2, 4 nad 5 are not used and exist for technical
    // reasons
    Int_t numPoints{5};
    Int_t numParams{7};
    std::vector<float> x{0., 1., 0., 2., 0.};
    std::vector<float> y{0., 2., 0., 3., 180.};
    std::vector<float> z{0., 654., 20., -765., -111.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoCons shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"CONS"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"CONS"}, numPoints, parameters);
}

TEST_CASE("FairGeoEltu")
{
    // An eltu is an elliptical tube defined by coordinates at the beginning
    // and the end of the eltu and the the two semi-axes P1 and P2.
    // Point 1: x, y, z coordinate of the center of the ellipsoid at the beginning of the eltu
    // Point 2: semi-axis P1 along x and semi-axis P2 along y
    // point 3: x, y, z coordinate of the center of the ellipsoid at the end of the eltu
    // The third values of point 1 is not used and exist for technical reasons
    Int_t numPoints{3};
    Int_t numParams{3};
    std::vector<float> x{0., 1., 0.};
    std::vector<float> y{0., 2., 0.};
    std::vector<float> z{0., 654., 20.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoEltu shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"ELTU"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"ELTU"}, numPoints, parameters);
}

TEST_CASE("FairGeoPcon")
{
    // A polycone (PCON) is represented by a sequence of tubes/cones,
    // glued together at defined Z planes.
    // Point 1: number of planes perpendicular to the z-axis where the section is given
    // Point 2: azimuthal angleat which the volume begins and opening angle of the volume
    // Point 2-(2+Point 1) : z coordinate of the section
    //                       inner radius at position z
    //                       outer radius at position z
    // The second and third value of point 1 and the third value of point 2
    // are not needed
    // e.g
    // 4        // number of values
    // 0. 360.   // unsegmented tube or cone
    // -2000.000 0.000 80.000
    // -300.000 0.000 80.000
    // 0.000 0.000 11.000
    // 200.000 0.000 11.000
    Int_t numPoints{6};
    std::vector<float> x{4., 0., -2000., -300., 0., 200.};
    std::vector<float> y{0., 360., 0., 0., 0., 0.};
    std::vector<float> z{0., -1., 80., 80., 11., 11.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoPcon shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    // At construction the number of points and parameters are 0
    // The values are updated when reading the shape information
    std::unique_ptr<TArrayD> paramArray(nullptr);
    check_FairGeoShape_Construction(shape, std::string{"PCON"}, 0, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"PCON"}, numPoints, parameters);
}

TEST_CASE("FairGeoPgon")
{
    // PGON are defined in the same way as PCON, the difference being just that the segments
    // between consecutive Z planes are regular polygons.
    // Point 1: number of planes perpendicular to the z-axis where the section is given
    // Point 2: azimuthal angle at which the volume begins
    //          opening angle of the volume
    //          number of sides of the cross section between the phi limits
    //          (in how many sides the opening angle is subdiveded)
    // Point 2-(2+Point 1) : z coordinate of the section
    //                       inner radius at position z
    //                       outer radius at position z
    // he second and third value of point 1 are not needed
    // e.g.
    // 3
    // 11.25 360. 16
    //  0. 480. 880.
    //  400. 480. 880.
    //  800. 480. 497.
    Int_t numPoints{5};
    std::vector<float> x{3., 11.25, 0., 400., 800.};
    std::vector<float> y{0., 360., 480., 480., 480.};
    std::vector<float> z{0., 16., 880., 880., 497.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoPgon shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    // At construction the number of points and parameters are 0
    // The values are updated when reading the shape information
    std::unique_ptr<TArrayD> paramArray(nullptr);
    check_FairGeoShape_Construction(shape, std::string{"PGON"}, 0, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"PGON"}, numPoints, parameters);
}

TEST_CASE("FairGeoSphe")
{
    // A Sphere (SPHE) are not just balls having internal and external radii,
    // but also sectors of a sphere having defined theta and phi ranges.
    // Point 1: inner and outer radius of the shell
    // Point2: starting and ending polar angles of the shell
    // Point 3: starting and ending azimuthal angles of the shell
    Int_t numPoints{3};
    Int_t numParams{6};
    std::vector<float> val1{2., 0., 0.};
    std::vector<float> val2{3., 180., 180.};
    std::vector<std::vector<float>> parameters{val1, val2};

    FairGeoSphe shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"SPHE"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"SPHE"}, numPoints, parameters);
}

TEST_CASE("FairGeoTorus")
{
    // The torus is defined by its axial radius, its inner and outer radius.
    // It also can have only a range in phi.
    // Point 1: axial radius
    // Point 2: inner radius
    // Point 3: outer radius
    // Point 4: starting phi
    // Point 5: phi extent
    Int_t numPoints{5};
    Int_t numParams{5};
    std::vector<float> val{10., 1., 2., 0., 180.};
    std::vector<std::vector<float>> parameters{val};

    FairGeoTorus shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"TORUS"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"TORUS"}, numPoints, parameters);
}

TEST_CASE("FairGeoTrap")
{
    // A trap is a general trapezoid.
    // A general trapezoid is one for which the faces perpendicular to z are trapezes
    // but their centers are not necessary at the same x, y coordinates.
    // This shapes has 8 corners described by the x, y, z coordinates.
    // The corners are counted clockwise starting at the lower left corner of
    // the bottom plane. The intrinsic coordinate system of a TRAP is different
    // from the one in Geant. The y-axis points from the smaller side in x-direction
    // to the larger one. A TRAP not rotated in a Box has the same intrinsic coordinate
    // system as the BOX. In Geant the y- and x-axis point in the opposite directions.
    Int_t numPoints{8};
    Int_t numParams{11};
    std::vector<float> x{700., 700., -700., -700., 700., 700., -700., -700.};
    std::vector<float> y{-540., 190., 190., -540., -540., 860., 860., -540.};
    std::vector<float> z{160., 160., 160., 160., 272., 272., 272., 272.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoTrap shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"TRAP"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"TRAP"}, numPoints, parameters);
}

TEST_CASE("FairGeoTrd1")
{
    // A trd1 is a trapezoid with only X varying with Z.
    // This shapes has 8 corners described by the x, y, z coordinates.
    // The intrinsic coordinate system of a TRD1 is the same as for a TRAP.
    // That's different from the definition in Geant.
    // e.g.
    // 60.490  -302.500     2.474
    // 372.600   470.000     2.474
    // -372.600   470.000     2.474
    // -60.490  -302.500     2.474
    //  60.490  -302.500     2.550
    // 372.600   470.000     2.550
    // -372.600   470.000     2.550
    // -60.490  -302.500     2.550
    Int_t numPoints{8};
    Int_t numParams{4};

    std::vector<float> x{60.49, 372.6, -372.6, -60.49, 60.49, 372.6, -372.6, -60.49};
    std::vector<float> y{-302.5, 470., 470., -302.5, -302.5, 470., 470., -302.5};
    std::vector<float> z{2.474, 2.474, 2.474, 2.474, 2.55, 2.55, 2.55, 2.55};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoTrd1 shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"TRD1"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"TRD1"}, numPoints, parameters);
}

TEST_CASE("FairGeoTube")
{
    // A tube is a cylindrical tube defined by coordinates at the beginning
    // and the end of the tube, and the inner and outer radius of the tube.
    // Point 1: x, y, z coordinate of the center of the tube at the beginning of the eltu
    // Point 2: inner and outer radius of the tube
    // Point 3: x, y, z coordinate of the center of the tube at the end of the tube
    // The third value of point 1 is not used and exist for technical reasons
    Int_t numPoints{3};
    Int_t numParams{3};
    std::vector<float> x{0., 1., 0.};
    std::vector<float> y{0., 2., 0.};
    std::vector<float> z{0., 654., 20.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoTube shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"TUBE"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"TUBE"}, numPoints, parameters);
}

TEST_CASE("FairGeoTubs")
{
    // A tubs is a tube having a range in phi. It is defined by coordinates at the beginning
    // and the end of the tubs, the inner and outer radius and the starting
    // and ending angles of the segment.
    // Point 1: x, y, z coordinate of the center of the circle at the beginning of the tubs
    // Point 2: inner and outer radius of the tubs
    // point 3: x, y, z coordinate of the center of the circle at the end of the tubs
    // Point 4: starting and ending angle of the segment
    // The third values of point 2 and point 4 are not used and exist for technical reasons
    Int_t numPoints{4};
    Int_t numParams{5};
    std::vector<float> x{0., 1., 0., 0.};
    std::vector<float> y{0., 2., 0., 180.};
    std::vector<float> z{0., 654., 20., -357.};
    std::vector<std::vector<float>> parameters{x, y, z};

    FairGeoTubs shape;
    FairGeoVolume volume;

    // Check if the constructor works as expected
    std::unique_ptr<TArrayD> paramArray{new TArrayD(numParams)};
    check_FairGeoShape_Construction(shape, std::string{"TUBS"}, numPoints, paramArray.get());

    // Check reading and writing from volume/shape parameters
    check_FairGeoShape_ReadWrite(shape, volume, std::string{"TUBS"}, numPoints, parameters);
}

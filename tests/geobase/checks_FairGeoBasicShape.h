/********************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairGeoBasicShape.h"
#include "FairGeoRotation.h"
#include "FairGeoTransform.h"
#include "FairGeoVector.h"
#include "FairGeoVolume.h"
#include "generate_TestInput.h"

#include <TArrayD.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cstdio>
#include <string>

using Catch::Matchers::WithinRel;

#ifndef TESTS_GEOBASE_CHECKS_FAIRGEOBASICSHAPE_H
#define TESTS_GEOBASE_CHECKS_FAIRGEOBASICSHAPE_H

namespace fairroot::tests
{

auto check_FairGeoTransform(FairGeoTransform& _trans)
{
    const FairGeoRotation& rot = _trans.getRotMatrix();
    CHECK(rot.isUnitMatrix());

    const FairGeoVector& vec = _trans.getTransVector();
    CHECK_THAT(vec.getValues(0), WithinRel(0., 0.001));
    CHECK_THAT(vec.getValues(1), WithinRel(0., 0.001));
    CHECK_THAT(vec.getValues(2), WithinRel(0., 0.001));

    const FairGeoVector& vec_cm = _trans.getTranslation();
    CHECK_THAT(vec_cm.getValues(0), WithinRel(0., 0.001));
    CHECK_THAT(vec_cm.getValues(1), WithinRel(0., 0.001));
    CHECK_THAT(vec_cm.getValues(2), WithinRel(0., 0.001));
}

auto check_FairGeoShape_Construction(FairGeoBasicShape& shape,
                                     std::string name,
                                     int numPoints,
                                     //                                     int numParams,
                                     const TArrayD* _param)
{

    const int numParams = (_param ? _param->GetSize() : 0);

    SECTION("construction")
    {
        // Check that members are correctly set by constructor
        CHECK(shape.GetName() == name);
        CHECK(shape.getNumPoints() == numPoints);
        CHECK(shape.getNumParam() == numParams);

        TArrayD* param = shape.getParam();
        if (!_param) {
            CHECK(param == _param);
        } else {
            REQUIRE(param->GetSize() == _param->GetSize());
            for (int i = 0; i < numParams; ++i) {
                CHECK(param->GetAt(i) == _param->GetAt(i));
            }
        }

        FairGeoTransform* centerPos = shape.getCenterPosition();
        REQUIRE(centerPos);
        check_FairGeoTransform(*centerPos);

        FairGeoTransform* voluPos = shape.getVoluPosition();
        REQUIRE(voluPos);
        check_FairGeoTransform(*voluPos);
    }
}

auto check_FairGeoShape_ReadWrite(FairGeoBasicShape& shape,
                                  FairGeoVolume& volume,
                                  std::string shapeName,
                                  int numPoints,
                                  std::vector<std::vector<float>>& parameters)
{
    // generate temporary file with parameters below describing the shape defined by the shapeName
    // with the respective coordinates
    // The name of the temporary file is returned
    std::string fileName = fairroot::tests::generateVolumeParameter(shapeName, parameters);

    // open the file with the shape/volume parameters
    // read the content from file and close the file
    std::fstream geoFile(fileName, std::ios::in);
    shape.readPoints(&geoFile, &volume);
    geoFile.close();

    CHECK(volume.getNumPoints() == numPoints);
    for (int i = 0; i < numPoints; ++i) {
        FairGeoVector* test = volume.getPoint(i);
        REQUIRE(test);
        if ("BOX" == shapeName || "TRAP" == shapeName || "TRD1" == shapeName) {
            CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
            CHECK_THAT(test->Y(), Catch::Matchers::WithinRel(parameters.at(1).at(i), 0.001f));
            CHECK_THAT(test->Z(), Catch::Matchers::WithinRel(parameters.at(2).at(i), 0.001f));
        } else if ("CONE" == shapeName || "CONS" == shapeName || "ELTU" == shapeName || "TUBE" == shapeName
                   || "TUBS" == shapeName) {
            if (0 == i || 2 == i) {
                CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
                CHECK_THAT(test->Y(), Catch::Matchers::WithinRel(parameters.at(1).at(i), 0.001f));
                CHECK_THAT(test->Z(), Catch::Matchers::WithinRel(parameters.at(2).at(i), 0.001f));
            } else {
                CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
                CHECK_THAT(test->Y(), Catch::Matchers::WithinRel(parameters.at(1).at(i), 0.001f));
            }
        } else if ("TORUS" == shapeName) {
            CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
        } else if ("SPHE" == shapeName) {
            CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
            CHECK_THAT(test->Y(), Catch::Matchers::WithinRel(parameters.at(1).at(i), 0.001f));
        } else if ("PCON" == shapeName) {
            if (0 == i) {
                CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
            } else if (1 == i) {
                CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
                CHECK_THAT(test->Y(), Catch::Matchers::WithinRel(parameters.at(1).at(i), 0.001f));
            } else {
                CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
                CHECK_THAT(test->Y(), Catch::Matchers::WithinRel(parameters.at(1).at(i), 0.001f));
                CHECK_THAT(test->Z(), Catch::Matchers::WithinRel(parameters.at(2).at(i), 0.001f));
            }
        } else if ("PGON" == shapeName) {
            if (0 == i) {
                CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
            } else {
                CHECK_THAT(test->X(), Catch::Matchers::WithinRel(parameters.at(0).at(i), 0.001f));
                CHECK_THAT(test->Y(), Catch::Matchers::WithinRel(parameters.at(1).at(i), 0.001f));
                CHECK_THAT(test->Z(), Catch::Matchers::WithinRel(parameters.at(2).at(i), 0.001f));
            }
        }
    }

    // Use the print function to generate the screen output
    // Currently I don't know how to test this
    // Probably not very important since the functionality isn't
    // really used
    shape.printPoints(&volume);
    shape.printParam();

    // Write the parmaters to an output file
    std::string testFileName = fairroot::tests::generateTempFileName();
    std::fstream testFile{};
    testFile.open(testFileName, std::ios::out);
    shape.writePoints(&testFile, &volume);
    testFile.close();

    // Check if the two files are identical
    CHECK(fairroot::tests::compareFiles(fileName, testFileName));

    // Remove the temporary files
    //    std::cout << shapeName << ": " << fileName.c_str() << "\n";
    CHECK(std::remove(fileName.c_str()) == 0);
    CHECK(std::remove(testFileName.c_str()) == 0);
}

}   // namespace fairroot::tests

#endif

/********************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairGeoSet.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <fmt/core.h>
#include <string>

#ifndef TESTS_GEOBASE_CHECKS_FAIRGEOSET_H
#define TESTS_GEOBASE_CHECKS_FAIRGEOSET_H

namespace fairroot::tests
{

auto checkGeoSetNamingConventions(FairGeoSet& geo, const std::string& prefix, int modules)
{
    SECTION("construction")
    {
        // Check that members are correctly set by constructor
        REQUIRE(geo.GetName() == prefix);
        REQUIRE(geo.getMaxModules() == modules);
    }

    SECTION("name generation")
    {
        auto index = GENERATE(take(100, random(1, 1000)));
        const auto name = fmt::format("{}{}", prefix, index + 1);

        REQUIRE(geo.getModuleName(index) == name);
        REQUIRE(geo.getEleName(index) == name);
    }

    SECTION("name parsing")
    {
        auto index = GENERATE(take(100, random(1, 1000)));
        const auto name = fmt::format("{}{}", prefix, index + 1);

        REQUIRE(geo.getModNumInMod(name) == index);
    }
}

}   // namespace fairroot::tests

#endif

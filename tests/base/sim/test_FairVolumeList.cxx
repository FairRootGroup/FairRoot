/********************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <FairVolume.h>
#include <FairVolumeList.h>
#include <TString.h>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <string_view>

static auto MakeVolume(std::string_view name)
{
    return std::make_unique<FairVolume>(TString{name});
}

TEST_CASE("FairVolumeList")
{
    FairVolumeList volumes;

    SECTION("is a set")
    {
        auto a = MakeVolume("a");
        auto* a_ptr = a.get();

        REQUIRE(volumes.addVolume(std::move(a)));
        REQUIRE(volumes.addVolume(MakeVolume("b")));
        REQUIRE(volumes.addVolume(MakeVolume("a")) == nullptr);

        REQUIRE(volumes.getEntries() == 2);
        REQUIRE(volumes.getVolume("a") == a_ptr);
    }

    SECTION("handles reading a non-existent volume")
    {
        REQUIRE(volumes.getVolume("z") == nullptr);
        REQUIRE(volumes.getVolumeId("z") == FairVolumeList::fgkNotFound);
    }

    SECTION("adding volumes returns added vol or nullptr")
    {
        auto a = MakeVolume("a");
        auto* a_ptr = a.get();

        REQUIRE(volumes.addVolume(std::move(a)) == a_ptr);
        REQUIRE(volumes.addVolume(MakeVolume("a")) == nullptr);
    }
}

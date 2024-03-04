/********************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include <FairVolume.h>
#include <FairVolumeList.h>
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <string_view>

static auto MakeVolume(std::string_view name)
{
    return std::make_unique<FairVolume>(name.data());
}

TEST_CASE("FairVolumeList")
{
    FairVolumeList vlist;

    SECTION("is a set")
    {
        auto a = MakeVolume("a");
        auto* a_ptr = a.get();
        auto a_name = TString(a->GetName());

        vlist.addVolume(a.release());
        vlist.addVolume(MakeVolume("b").release());
        vlist.addVolume(MakeVolume("a").release());

        REQUIRE(vlist.getEntries() == 2);
        REQUIRE(vlist.getVolume(&a_name) == a_ptr);
    }

    SECTION("handles reading a non-existent volume")
    {
        TString z = "z";

        REQUIRE(vlist.getVolume(&z) == nullptr);
        REQUIRE(vlist.getVolumeId(&z) == FairVolumeList::fgkNotFound);
    }
}

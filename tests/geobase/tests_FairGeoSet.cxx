/********************************************************************************
 *   Copyright (C) 2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH     *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairGeoBrik.h"
#include "FairGeoMedia.h"
#include "FairGeoMedium.h"
#include "FairGeoShapes.h"
#include "FairTestGeo.h"
#include "checks_FairGeoSet.h"

#include <TList.h>
#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators_all.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#ifndef TESTS_GEOBASE_FAIRGEOSET_H
#define TESTS_GEOBASE_FAIRGEOSET_H

TEST_CASE("FairTestGeo")
{
    /*
        std::ostringstream os;

        os << "//----------------------------------------------------------\n";
        os << "air                3  14.01  16.  39.95  7.  8.  18.  1.205e-3  .755  .231.014\n";
        os << "                   0  1  30.  .001\n";
        os << "silicon            1  28.0855 14.0 2.33\n";
        os << "                   1  1  20.  .001\n";
        os << "                   0";
        std::istringstream mediafile( os.str() );
    */

    std::fstream mediafile{"data/testmedia.geo", std::ios::in};

    std::fstream geofile{"data/testdet_brick.geo", std::ios::in};

    REQUIRE(geofile.is_open());
    REQUIRE(mediafile.is_open());

    INFO("Media and geo files open");

    FairGeoMedia media;
    media.read(mediafile);

    INFO("Media file read");

    auto volu = std::make_unique<FairGeoNode>();
    // FairGeoNode* volu = new FairGeoNode();
    volu->SetName("cave");
    volu->setVolumeType(kFairGeoTopNode);
    volu->setActive();
    volu->setShape(new FairGeoBrik());

    if (auto air = media.getMedium("air"); air) {
        volu->setMedium(air);
    } else {
        auto generic = std::make_unique<FairGeoMedium>();
        volu->setMedium(generic.get());
        media.addMedium(generic.release());
    }

    volu->setPoint(0, 20000., -20000., -20000.);
    volu->setPoint(1, 20000., 20000., -20000.);
    volu->setPoint(2, -20000., 20000., -20000.);
    volu->setPoint(3, -20000., -20000., -20000.);
    volu->setPoint(4, 20000., -20000., 20000.);
    volu->setPoint(5, 20000., 20000., 20000.);
    volu->setPoint(6, -20000., 20000., 20000.);
    volu->setPoint(7, -20000., -20000., 20000.);

    auto masterNodes = std::make_unique<TList>();
    masterNodes->Add(new FairGeoNode(*volu));

    INFO("Master volume created");

    FairTestGeo geo;
    geo.setMasterNodes(masterNodes.get());
    geo.setShapes(new FairGeoShapes());

    //    fairroot::tests::checkGeoSetNamingConventions(geo, "testdet", 10);

    geo.read(geofile, &media);

    geo.print();

    geofile.close();
    mediafile.close();
}
#endif

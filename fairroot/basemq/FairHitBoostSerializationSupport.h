/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRHIT_BOOST_SERIALIZATION_SUPPORT_H
#define FAIRHIT_BOOST_SERIALIZATION_SUPPORT_H

#include <FairHit.h>
#include <FairTimeStampBoostSerializationSupport.h>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost::serialization {

template<class Archive>
void load(Archive& ar, FairHit& hit, const unsigned int)
{
    ar& base_object<FairTimeStamp>(hit);

    Int_t detectorID = 0;
    ar& detectorID;
    hit.SetDetectorID(detectorID);

    Int_t refIndex = 0;
    ar& refIndex;
    hit.SetRefIndex(refIndex);

    Double_t x = 0., y = 0., z = 0.;
    ar& x;
    ar& y;
    ar& z;
    hit.SetXYZ(x, y, z);

    Double_t dx = 0., dy = 0., dz = 0.;
    ar& dx;
    ar& dy;
    ar& dz;
    hit.SetDxyz(dx, dy, dz);
}

template<class Archive>
void save(Archive& ar, FairHit const& hit, const unsigned int)
{
    ar& base_object<FairTimeStamp>(hit);
    ar& hit.GetDetectorID();
    ar& hit.GetRefIndex();
    ar& hit.GetX();
    ar& hit.GetY();
    ar& hit.GetZ();
    ar& hit.GetDx();
    ar& hit.GetDy();
    ar& hit.GetDz();
}

}   // namespace boost::serialization

BOOST_SERIALIZATION_SPLIT_FREE(FairHit)

#endif   // FAIRHIT_BOOST_SERIALIZATION_SUPPORT_H

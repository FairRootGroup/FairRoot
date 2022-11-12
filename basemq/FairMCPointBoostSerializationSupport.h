/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMCPOINT_BOOST_SERIALIZATION_SUPPORT_H
#define FAIRMCPOINT_BOOST_SERIALIZATION_SUPPORT_H

#include <FairMCPoint.h>
// #include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost::serialization {

template<class Archive>
void load(Archive& ar, FairMCPoint& mcPoint, const unsigned int)
{
    // ar & boost::serialization::base_object<FairMultiLinkedData>(*this);

    Int_t trackID = 0;
    ar& trackID;
    mcPoint.SetTrackID(trackID);

    Int_t eventID = 0;
    ar& eventID;
    mcPoint.SetEventID(eventID);

    Int_t detectorID = 0;
    ar& detectorID;
    mcPoint.SetDetectorID(detectorID);

    Double_t x = 0., y = 0., z = 0.;
    ar& x;
    ar& y;
    ar& z;
    mcPoint.SetXYZ(x, y, z);

    Double_t px = 0., py = 0., pz = 0.;
    ar& px;
    ar& py;
    ar& pz;
    mcPoint.SetMomentum(TVector3(px, py, pz));

    Double_t time = 0.;
    ar& time;
    mcPoint.SetTime(time);

    Double_t length = 0.;
    ar& length;
    mcPoint.SetLength(length);

    Double_t energyLoss = 0.;
    ar& energyLoss;
    mcPoint.SetLength(energyLoss);
}

template<class Archive>
void save(Archive& ar, FairMCPoint const& mcPoint, const unsigned int)
{
    // ar & boost::serialization::base_object<FairMultiLinkedData>(*this);
    ar& mcPoint.GetTrackID();
    ar& mcPoint.GetEventID();
    ar& mcPoint.GetDetectorID();
    ar& mcPoint.GetX();
    ar& mcPoint.GetY();
    ar& mcPoint.GetZ();
    ar& mcPoint.GetPx();
    ar& mcPoint.GetPy();
    ar& mcPoint.GetPz();
    ar& mcPoint.GetTime();
    ar& mcPoint.GetLength();
    ar& mcPoint.GetEnergyLoss();
}

}   // namespace boost::serialization

BOOST_SERIALIZATION_SPLIT_FREE(FairMCPoint)

#endif   // FAIRMCPOINT_BOOST_SERIALIZATION_SUPPORT_H

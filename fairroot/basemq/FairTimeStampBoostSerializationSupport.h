/********************************************************************************
 *    Copyright (C) 2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRTIMESTAMP_BOOST_SERIALIZATION_SUPPORT_H
#define FAIRTIMESTAMP_BOOST_SERIALIZATION_SUPPORT_H

#include <FairTimeStamp.h>
// #include <boost/serialization/base_object.hpp>
#include <boost/serialization/split_free.hpp>

namespace boost::serialization {

template<class Archive>
void load(Archive& ar, FairTimeStamp& time, const unsigned int)
{
    // ar & boost::serialization::base_object<FairMultiLinkedData>(time);

    Double_t timeStamp = 0.;
    ar& timeStamp;
    time.SetTimeStamp(timeStamp);

    Double_t timeStampError = 0.;
    ar& timeStampError;
    time.SetTimeStampError(timeStampError);
}

template<class Archive>
void save(Archive& ar, FairTimeStamp const& time, const unsigned int)
{
    // ar & boost::serialization::base_object<FairMultiLinkedData>(time);
    ar& time.GetTimeStamp();
    ar& time.GetTimeStampError();
}

}   // namespace boost::serialization

BOOST_SERIALIZATION_SPLIT_FREE(FairTimeStamp)

#endif   // FAIRTIMESTAMP_BOOST_SERIALIZATION_SUPPORT_H

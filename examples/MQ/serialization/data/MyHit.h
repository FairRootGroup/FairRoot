/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   MyHit.h
 * Author: winckler
 *
 * Created on November 24, 2014, 1:40 PM
 */

#ifndef MYHITDATA_H
#define MYHITDATA_H

#include "FairHit.h"   // for FairHit

#include <FairHitBoostSerializationSupport.h>
#include <Rtypes.h>   // for MyHit::Class, etc

namespace boost {
namespace serialization {
class access;
}
}   // namespace boost
#include <boost/serialization/base_object.hpp>

class TVector3;

class MyHit : public FairHit
{
  public:
    /** Default constructor **/
    MyHit();

    /** Constructor **/
    MyHit(Int_t detID, Int_t mcindex, const TVector3& pos, const TVector3& dpos);
    MyHit(Int_t detID,
          Int_t mcindex,
          const TVector3& pos,
          const TVector3& dpos,
          Double_t timeStamp,
          Double_t timeStampError);

    /** Destructor **/
    virtual ~MyHit();

    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
    friend class boost::serialization::access;

    ClassDef(MyHit, 1);
};

#endif /* MYHITDATA_H */

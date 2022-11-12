/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORHIT_H_
#define FAIRTESTDETECTORHIT_H_

#include "FairHit.h"   // for FairHit

#include <FairHitBoostSerializationSupport.h>
#include <Rtypes.h>   // for FairTestDetectorHit::Class, etc
#include <boost/serialization/base_object.hpp>
namespace boost {
namespace serialization {
class access;
}
}   // namespace boost

class TVector3;

class FairTestDetectorHit : public FairHit
{
  public:
    /** Default constructor **/
    FairTestDetectorHit();

    /** Constructor **/
    FairTestDetectorHit(Int_t detID, Int_t mcindex, const TVector3& pos, const TVector3& dpos);

    /** Destructor **/
    virtual ~FairTestDetectorHit();

    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
    friend class boost::serialization::access;

    ClassDef(FairTestDetectorHit, 1);
};

#endif /* FAIRTESTDETECTORHIT_H_ */

/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTPROPHIT_H_
#define FAIRTUTPROPHIT_H_

#include "FairHit.h"   // for FairHit

#include <Rtypes.h>   // for FairTutPropHit::Class, etc
#include <boost/serialization/base_object.hpp>
namespace boost {
namespace serialization {
class access;
}
}   // namespace boost

class TVector3;

class FairTutPropHit : public FairHit
{
  public:
    /** Default constructor **/
    FairTutPropHit();

    /** Constructor **/
    FairTutPropHit(int detID,
                   int mcindex,
                   const TVector3& pos,
                   const TVector3& dpos,
                   int trackID,
                   int pdgCode,
                   double charge,
                   const TVector3& mom,
                   const TVector3& dmom);

    /** Destructor **/
    virtual ~FairTutPropHit();

    int GetTrackID() { return fTrackID; }
    int GetPdgCode() { return fPdgCode; }
    double GetCharge() { return fCharge; }
    double GetPx() { return fPx; }
    double GetPy() { return fPy; }
    double GetPz() { return fPz; }
    double GetDPx() { return fDPx; }
    double GetDPy() { return fDPy; }
    double GetDPz() { return fDPz; }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
        ar& fTrackID;
        ar& fPdgCode;
        ar& fCharge;
        ar& fPx;
        ar& fPy;
        ar& fPz;
        ar& fDPx;
        ar& fDPy;
        ar& fDPz;
    }

  private:
    friend class boost::serialization::access;

    // magic detector that knows track ids and momenta
    int fTrackID;
    int fPdgCode;
    double fCharge;
    double fPx, fPy, fPz;
    double fDPx, fDPy, fDPz;

    ClassDef(FairTutPropHit, 1);
};

#endif /* FAIRTUTPROPHIT_H_ */

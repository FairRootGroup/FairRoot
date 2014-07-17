/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORHIT_H_
#define FAIRTESTDETECTORHIT_H_

#include "FairHit.h" // for FairHit

#include "Rtypes.h" // for FairTestDetectorHit::Class, etc

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class TVector3;

class FairTestDetectorHit : public FairHit
{
  public:
    /** Default constructor **/
    FairTestDetectorHit();

    /** Constructor **/
    FairTestDetectorHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);

    /** Destructor **/
    virtual ~FairTestDetectorHit();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;

#endif // for BOOST serialization

    ClassDef(FairTestDetectorHit, 1);
};

#endif /* FAIRTESTDETECTORHIT_H_ */

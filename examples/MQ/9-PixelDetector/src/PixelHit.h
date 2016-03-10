/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELHIT_H_
#define PIXELHIT_H_

#include "FairHit.h"     // for FairHit
#include "Rtypes.h"      // for PixelHit::Class, ClassDef, PixelHit::Streamer
#include "RtypesCore.h"  // for Int_t
class TVector3;  // lines 27-27

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class TVector3;

class PixelHit : public FairHit
{
  public:
    /** Default constructor **/
    PixelHit();

    /** Constructor **/
    PixelHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);

    /** Destructor **/
    virtual ~PixelHit();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    ClassDef(PixelHit, 1);
};

#endif /* PIXELHIT_H_ */

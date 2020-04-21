/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
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

#include "FairHit.h"   // for FairHit

#include <Rtypes.h>   // for PixelHit::Class, ClassDef, PixelHit::Streamer

class TVector3;

namespace boost {
namespace serialization {
class access;
}
}   // namespace boost
#include <boost/serialization/base_object.hpp>

class PixelHit : public FairHit
{
  public:
    /** Default constructor **/
    PixelHit();

    /** Constructor **/
    PixelHit(Int_t detID, Int_t mcindex, const TVector3& pos, const TVector3& dpos);

    /** Destructor **/
    virtual ~PixelHit();

    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
    friend class boost::serialization::access;

    ClassDef(PixelHit, 1);
};

#endif /* PIXELHIT_H_ */

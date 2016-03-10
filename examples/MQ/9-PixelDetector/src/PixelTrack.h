/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelTrack.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELTRACK_H_
#define PIXELTRACK_H_

#include "FairTimeStamp.h"  // for FairTimeStamp
#include "Rtypes.h"         // for PixelTrack::Class, ClassDef, PixelTrack::...

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__


class PixelTrack : public FairTimeStamp
{
  public:
    /** Default constructor **/
    PixelTrack();

    /** Constructor **/
    PixelTrack(Double_t x0 , Double_t ax , Double_t y0 , Double_t ay ,
	       Double_t x0e, Double_t axe, Double_t y0e, Double_t aye);


    void SetX0   (Double_t x0)  {fX0 = x0;};
    void SetAX   (Double_t ax)  {fAX = ax;};
    void SetY0   (Double_t y0)  {fY0 = y0;};
    void SetAY   (Double_t ay)  {fAY = ay;};
    void SetX0Err(Double_t x0e) {fX0Err = x0e;};
    void SetAXErr(Double_t axe) {fAXErr = axe;};
    void SetY0Err(Double_t y0e) {fY0Err = y0e;};
    void SetAYERr(Double_t aye) {fAYErr = aye;};

    Double_t GetX0   () {return fX0;};
    Double_t GetAX   () {return fAX;};
    Double_t GetY0   () {return fY0;};
    Double_t GetAY   () {return fAY;};
    Double_t GetX0Err() {return fX0Err;};
    Double_t GetAXErr() {return fAXErr;};
    Double_t GetY0Err() {return fY0Err;};
    Double_t GetAYErr() {return fAYErr;};

    void  AddHitIndex(Int_t hitIndex) {fHitIndices.push_back(hitIndex);};
    Int_t GetNofHits ()               {return fHitIndices.size();};
    Int_t GetHitIndex(Int_t ihit)     {return fHitIndices.at(ihit);};

    /** Destructor **/
    virtual ~PixelTrack();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar& boost::serialization::base_object<FairTimeStamp>(*this);
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    Double_t fX0;
    Double_t fAX;
    Double_t fY0;
    Double_t fAY;
    Double_t fX0Err;
    Double_t fAXErr;
    Double_t fY0Err;
    Double_t fAYErr;

    std::vector<Int_t> fHitIndices;

    ClassDef(PixelTrack, 1);
};

#endif /* PIXELTRACK_H_ */

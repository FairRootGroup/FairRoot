/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelDigi.h
 *
 *  Created on: 10.02.2016
 *      Author: M. Al-Turany
 */

#ifndef PixelDigi_H_
#define PixelDigi_H_

#include "FairTimeStamp.h" // for FairTimeStamp
#include "Rtypes.h"        // for Int_t, etc

#include <iostream>        // for operator<<, basic_ostream, etc

class PixelDigi : public FairTimeStamp
{
 public:
    PixelDigi();
    /**
     *\param index position of PixelPoint in TClonesArray
     *\param detID detector ID (from/for PixelPoint/Hit)
     *\param SensorID Sensor ID from digitization scheme
     *\param feID front end ID
     *\param charge deposited charge in electrons
    **/
    
    PixelDigi(Int_t index, Int_t detID, Int_t SensorID, Int_t feID, Double_t charge, Double_t timestamp = -1);
    virtual ~PixelDigi();
    
    void SetIndex(Int_t in){index = in;};
    void SetDetId(Int_t det){detID=det;};
    void SetSenserID(Int_t Sen){SensorID=Sen;};
    void SetfeID(Int_t fe){feID=fe;};
    void SetCharge(Double_t ch){charge = ch;};
              
    Int_t GetIndex(Int_t i){return index;};
    Int_t GetDetId(){return detID;};
    Int_t GetSenserID(){return SensorID;};
    Int_t GetfeID(){return feID;};
    Double_t GetCharge(){return charge;};
    
  private:
    Int_t index;
    Int_t detID;
    Int_t SensorID;
    Int_t feID;
    Double_t charge;
              
              
    ClassDef(PixelDigi, 1);
};

#endif /* PixelDigi_H_ */

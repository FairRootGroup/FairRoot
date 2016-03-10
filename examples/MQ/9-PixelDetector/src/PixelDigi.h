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

#include "FairTimeStamp.h"  // for FairTimeStamp
#include "Rtypes.h"         // for PixelDigi::Class, ClassDef, PixelDigi::St...
#include "RtypesCore.h"     // for Int_t, Double_t


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
    
    PixelDigi(Int_t index, Int_t detID, Int_t feID, Int_t col, Int_t row, Double_t charge, Double_t timestamp = -1);
    virtual ~PixelDigi();
    
    void SetIndex(Int_t in){fPointIndex = in;};
    void SetDetectorID(Int_t det){fDetectorID=det;};
    void SetFeID(Int_t fe){fFeID=fe;};
    void SetCharge(Double_t ch){fCharge = ch;};
    void SetCol(Int_t col){fCol = col;};
    void SetRow(Int_t row){fRow = row;};              

    Int_t GetIndex(){return fPointIndex;};
    Int_t GetDetectorID(){return fDetectorID;};
    Int_t GetFeID(){return fFeID;};
    Double_t GetCharge(){return fCharge;};
    Int_t GetCol(){return fCol;};
    Int_t GetRow(){return fRow;};    

  private:
    Int_t fPointIndex;
    Int_t fDetectorID;
    Int_t fFeID;
    Double_t fCharge;
    Int_t fCol;
    Int_t fRow;              
              
    ClassDef(PixelDigi, 1);
};

#endif /* PixelDigi_H_ */

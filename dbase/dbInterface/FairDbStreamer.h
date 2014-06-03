/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBSTREAMER_H
#define FAIRDBSTREAMER_H

#include "TObject.h"                    // for TObject
#include "TString.h"                    // for TObject
#include "Rtypes.h"                     // for UInt_t, Int_t, etc
#include <stddef.h>                     // for NULL
#include <cassert>                      // for assert
#include <string>                       // for string


#include "FairDb.h"


class FairDbStreamer : public TObject
{
  public:

    // Constructors and destructors.
    FairDbStreamer();
    FairDbStreamer(const TObject* obj,  FairDb::DataTypes type=FairDb::kBinary);

    FairDbStreamer(const Int_t* iarr, Int_t size, FairDb::DataTypes type=FairDb::kInt);
    FairDbStreamer(const UInt_t* iarr, Int_t size, FairDb::DataTypes type=FairDb::kInt);
    FairDbStreamer(const Short_t* iarr, Int_t size, FairDb::DataTypes type=FairDb::kInt);
    FairDbStreamer(const UShort_t* iarr, Int_t size, FairDb::DataTypes type=FairDb::kInt);
    FairDbStreamer(const Bool_t* iarr, Int_t size, FairDb::DataTypes type=FairDb::kInt);
    FairDbStreamer(const Float_t* iarr, Int_t size, FairDb::DataTypes type=FairDb::kInt);
    FairDbStreamer(const Double_t* iarr, Int_t size, FairDb::DataTypes type=FairDb::kInt);

    FairDbStreamer(const FairDbStreamer& from);
    FairDbStreamer& operator=(const FairDbStreamer&);
    virtual ~FairDbStreamer();

    // Meta-Data: String Encryption on Server Side
    const TString  AsString() const { return fString;};
    void SetString(TString aStr) { fString=aStr;}
    Int_t GetSize() {return fSize;}
    FairDb::DataTypes GetDataType() { return fType;}

    // Fill functions for arrays & objects
    void Fill(Int_t* arr);
    void Fill(UInt_t* arr);
    void Fill(Short_t* arr);
    void Fill(UShort_t* arr);
    void Fill(Bool_t* arr);
    void Fill(Float_t* arr);
    void Fill(Double_t* arr);
    void Fill(TObject* obj);


  private:
    TString fString; //!
    Int_t   fSize; //!
    FairDb::DataTypes fType; //!

    ClassDef(FairDbStreamer,0)   // FairDbStreamer for a specific database table.

};


#endif  // FAIRDBSTREAMER_H

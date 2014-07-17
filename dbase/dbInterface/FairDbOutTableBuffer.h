/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBOUTABLEBUFFER_H
#define FAIRDBOUTABLEBUFFER_H

#include "FairDbTableBuffer.h"            // for FairDbTableBuffer

#include "FairDb.h"                     // for DataTypes

#include "Rtypes.h"                     // for Bool_t, Char_t, etc

#include <string>

class FairDbTableMetaData;
class ValTimeStamp;
class FairDbStreamer;

class FairDbOutTableBuffer : public FairDbTableBuffer
{

  public:
    FairDbOutTableBuffer(const FairDbTableMetaData* metaData);
    virtual ~FairDbOutTableBuffer();

    Bool_t HasGoodData() const { return ! fBadData && IsComplete(); }
    const std::string& GetCSV() const { return fCSV; }
    Bool_t IsComplete() const { return CurColNum() == NumCols()+1; }

    FairDbOutTableBuffer& operator<<(Bool_t src);
    FairDbOutTableBuffer& operator<<(Char_t src);
    FairDbOutTableBuffer& operator<<(const Char_t* src);
    FairDbOutTableBuffer& operator<<(Short_t src);
    FairDbOutTableBuffer& operator<<(UShort_t src);
    FairDbOutTableBuffer& operator<<(Int_t src);
    FairDbOutTableBuffer& operator<<(UInt_t src);
    FairDbOutTableBuffer& operator<<(Float_t src);
    FairDbOutTableBuffer& operator<<(Double_t src);
    FairDbOutTableBuffer& operator<<(const std::string& src);
    FairDbOutTableBuffer& operator<<(const ValTimeStamp& src);
    FairDbOutTableBuffer& operator<<(const FairDbStreamer& src);

    void Clear() { fBadData = kFALSE; fCSV.erase(); ClearCurCol();}
    void Store(const std::string& str);
    Bool_t StoreDefaultIfInvalid(FairDb::DataTypes type);

  private:

    Bool_t fBadData;
    std::string fCSV;

    ClassDef(FairDbOutTableBuffer,0)  //Output buffer for a single table row

};


#endif  // FAIRDBOUTABLEBUFFER_H

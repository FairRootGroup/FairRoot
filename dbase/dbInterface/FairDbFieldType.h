/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBFIELDTYPE_H
#define FAIRDBFIELDTYPE_H

#include "FairDb.h"                     // for DataTypes::kInt, etc
#include "Rtypes.h"                     // for Int_t, Bool_t, UInt_t, etc
#include <string>                       // for string

class FairDbFieldType
{
  public:

    enum PrecisionLimits { kMaxTinyInt       = 4,
                           kMaxSmallInt      = 6,
                           kMaxInt           = 11,
                           kMaxChar          = 3,
                           kMaxOracleFloat   = 32,
                           kMaxMySQLVarchar  = 255,
                           kMaxOracleVarchar = 4000,
                           kMaxMySQLText     = 65535
                         };

    FairDbFieldType(Int_t type = FairDb::kInt);
    FairDbFieldType(Int_t type,
                    Int_t size,
                    const char* typeName);
    FairDbFieldType(const FairDbFieldType& from);
    FairDbFieldType(const std::string& sql,
                    Int_t size);
    virtual ~FairDbFieldType();


    std::string AsString() const;
    std::string AsSQLString(FairDb::DbTypes dbType = FairDb::kMySQL) const;
    std::string UndefinedValue() const;
    UInt_t GetConcept() const { return fConcept; }
    UInt_t GetSize() const { return fSize; }
    UInt_t GetType() const { return fType; }
    Bool_t IsCompatible(const FairDbFieldType& other) const;
    Bool_t IsEquivalent(const FairDbFieldType& other) const {return IsCompatible(other);}
    Bool_t IsEqual(const FairDbFieldType& other) const
    { return fType == other.fType; }
    Bool_t IsSmaller(const FairDbFieldType& other) const
    { return fSize < other.fSize; }
    Bool_t IsSigned() const          { return fConcept ==  FairDb::kInt; }


    void SetUnsigned() {if (this->IsSigned()) {++fConcept; ++fType;}}

  private:

    void Init(Int_t type, Int_t size = -1);

    unsigned int fConcept;
    unsigned int fSize;
    unsigned int fType;

    ClassDef(FairDbFieldType,0)        // Column field types.

};

#endif  // FAIRDBFIELDTYPE_H


#ifndef FAIRDBFIELDTYPE_H
#define FAIRDBFIELDTYPE_H


#include <string>
using std::string;

#include "FairDb.h"

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

// Constructors and destructors.
    FairDbFieldType(Int_t type = FairDb::kInt);
    FairDbFieldType(Int_t type,
                    Int_t size,
                    const char* typeName);
    FairDbFieldType(const FairDbFieldType& from);
    FairDbFieldType(const string& sql,
                    Int_t size);
    virtual ~FairDbFieldType();


    string AsString() const;
    string AsSQLString(FairDb::DbTypes dbType = FairDb::kMySQL) const;
    string UndefinedValue() const;
    UInt_t GetConcept() const { return fConcept; }
    UInt_t GetSize() const { return fSize; }
    UInt_t GetType() const { return fType; }
    Bool_t IsCompatible(const FairDbFieldType& other) const;
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

    ClassDef(FairDbFieldType,0)        // Table column field types.

};

#endif  // FAIRDBFIELDTYPE_H

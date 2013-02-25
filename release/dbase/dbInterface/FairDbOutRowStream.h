#ifndef FAIRDBOUTROWSTREAM_H
#define FAIRDBOUTROWSTREAM_H

#include <string>

#include "FairDb.h"
#include "FairDbRowStream.h"

class FairDbTableMetaData;
class ValTimeStamp;
class FairDbValidityRec;

class FairDbOutRowStream : public FairDbRowStream
{

//  friend class FairDbConfigSet; //To allow it to use private Store method

  public:

    FairDbOutRowStream(const FairDbTableMetaData* metaData);
    virtual ~FairDbOutRowStream();

    Bool_t HasGoodData() const { return ! fBadData && IsComplete(); }
    const string& GetCSV() const { return fCSV; }
    Bool_t IsComplete() const { return CurColNum() == NumCols()+1; }

    FairDbOutRowStream& operator<<(Bool_t src);
    FairDbOutRowStream& operator<<(Char_t src);
    FairDbOutRowStream& operator<<(const Char_t* src);
    FairDbOutRowStream& operator<<(Short_t src);
    FairDbOutRowStream& operator<<(UShort_t src);
    FairDbOutRowStream& operator<<(Int_t src);
    FairDbOutRowStream& operator<<(UInt_t src);
    FairDbOutRowStream& operator<<(Float_t src);
    FairDbOutRowStream& operator<<(Double_t src);
    FairDbOutRowStream& operator<<(const string& src);
    FairDbOutRowStream& operator<<(const ValTimeStamp& src);

    void Clear() { fBadData = kFALSE; fCSV.erase(); ClearCurCol();}
    void Store(const string& str);
    Bool_t StoreDefaultIfInvalid(FairDb::DataTypes type);

  private:

    Bool_t fBadData;
    string fCSV;

    ClassDef(FairDbOutRowStream,0)  //Output stream for single table row

};


#endif  // FAIRDBOUTROWSTREAM_H

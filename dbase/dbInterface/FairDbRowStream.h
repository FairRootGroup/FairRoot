#ifndef FAIRDBROWSTREAM_H
#define FAIRDBROWSTREAM_H

#include "Rtypes.h"                     // for UInt_t, Bool_t, etc

#include <string>                       // for string

class FairDbFieldType;
class FairDbTableMetaData;

class FairDbRowStream
{

  public:

    FairDbRowStream(const FairDbTableMetaData* metaData);
    virtual ~FairDbRowStream();

    virtual
    const FairDbFieldType& ColFieldType(UInt_t col) const;
    virtual       std::string ColName(UInt_t col) const;
    virtual
    const FairDbFieldType& CurColFieldType() const;
    virtual       std::string CurColName() const;
    virtual       UInt_t CurColNum() const { return fCurCol;}
    Bool_t HasRowCounter() const { return fHasRowCounter; }
    virtual       UInt_t NumCols() const;
    virtual       std::string TableName() const;
    virtual       std::string TableNameTc() const;
    virtual const FairDbTableMetaData*
    MetaData() const { return fMetaData; }


    virtual    void DecrementCurCol() {
      fCurCol = (fCurCol <= 1) ? 1 : fCurCol -1;
    }

    virtual    void IncrementCurCol() { ++fCurCol; }

  protected:

    virtual    void ClearCurCol() { fCurCol = 1; }

  private:

    UShort_t fCurCol;
    Bool_t fHasRowCounter;
    const FairDbTableMetaData* fMetaData;

    FairDbRowStream(const FairDbRowStream&);
    FairDbRowStream operator=(const FairDbRowStream&);

    ClassDef(FairDbRowStream,0)     // I/O of a table row.

};


#endif  // FAIRDBROWSTREAM_H

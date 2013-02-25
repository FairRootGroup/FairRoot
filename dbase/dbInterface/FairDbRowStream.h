#ifndef FAIRDBROWSTREAM_H
#define FAIRDBROWSTREAM_H

#include <string>

#include "FairDbFieldType.h"

class FairDbTableMetaData;

class FairDbRowStream
{

  public:

// Constructors and destructors.
    FairDbRowStream(const FairDbTableMetaData* metaData);
    virtual ~FairDbRowStream();

    virtual
    const FairDbFieldType& ColFieldType(UInt_t col) const;
    virtual       string ColName(UInt_t col) const;
    virtual
    const FairDbFieldType& CurColFieldType() const;
    virtual       string CurColName() const;
    virtual       UInt_t CurColNum() const { return fCurCol;}
    Bool_t HasRowCounter() const { return fHasRowCounter; }
    virtual       UInt_t NumCols() const;
    virtual       string TableName() const;
    virtual       string TableNameTc() const;
    virtual const FairDbTableMetaData*
    MetaData() const { return fMetaData; }
    // State changing member functions

    virtual    void DecrementCurCol() {
      fCurCol = (fCurCol <= 1) ? 1 : fCurCol -1;
    }
    // Allow IncrementCurCol to step off end (to catch attempt to read
    // too much data)
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

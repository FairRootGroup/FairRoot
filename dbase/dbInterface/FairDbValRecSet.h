#ifndef FAIRDBVALRECSET
#define FAIRDBVALRECSET


#include <map>
#include <string>

class FairDbResult;
class FairDbValidityRec;

class FairDbValRecSet
{

  public:

// Constructors and destructors.
    FairDbValRecSet(const string& tableName,UInt_t dbNo,UInt_t seqNo=0);
    virtual ~FairDbValRecSet();

// State testing member functions
    UInt_t GetDbNo() const { return fDbNo; }
    UInt_t GetNumRows() const;
    const string GetTableName() const;
    const FairDbValidityRec* GetTableRow(UInt_t rowNum) const;
    const FairDbValidityRec* GetTableRowBySeqNo(UInt_t seqNo) const;

// State changing member functions

  private:

// Data members

//// Database number used to fill
    UInt_t fDbNo;

/// Result holding table of FairDbValidityRec
    FairDbResult* fResult;

/// Lookup SeqNo -> FairDbValidityRec
/// lazy creation - see GetTableRowBySeqNo
    mutable map<UInt_t,const FairDbValidityRec*>fSeqNoToRec;

    FairDbValRecSet(const FairDbValRecSet&);
    FairDbValRecSet operator=(const FairDbValRecSet&);

    ClassDef(FairDbValRecSet,0)     //  A set of FairDbValidityRecs

};


#endif  // FAIRDBVALRECSET

#ifndef FAIRDBTABLEROW_H
#define FAIRDBTABLEROW_H

#include "TObject.h"
#include <string>
#include <cassert>

class FairDbOutRowStream;
class FairDbResult;
class FairDbResultSet;
class FairDbTableProxy;
class FairDbValidityRec;

class FairDbTableRow : public TObject
{

  public:

// Constructors and destructors.
    FairDbTableRow();
    FairDbTableRow(const FairDbTableRow& from);
    virtual ~FairDbTableRow();

// State testing member functions
    virtual       Bool_t CanL2Cache() const { return kFALSE; }
    virtual        Int_t GetAggregateNo() const { return -1; }
    FairDbResult* GetOwner() const { return fOwner; }
    virtual FairDbTableRow* CreateTableRow() const =0;
    virtual       UInt_t GetIndex(UInt_t defIndex) const {return defIndex;}

// State modifying member functions
    void SetOwner(FairDbResult* owner) {fOwner = owner;}

// I/O  member functions
    virtual void Fill(FairDbResultSet& rs,
                      const FairDbValidityRec* vrec) =0;
    virtual void Store(FairDbOutRowStream& /* ors */,
                       const FairDbValidityRec* /* vrec */) const { assert(0); }

  private:

// Data members

/// The owning FairDbResult, if any.
    FairDbResult* fOwner;

    ClassDef(FairDbTableRow,0)   // FairDbTableRow for a specific database table.

};


#endif  // FAIRDBTABLEROW_H

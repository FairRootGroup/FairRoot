#ifndef FAIRDBTABLEROW_H
#define FAIRDBTABLEROW_H

#include <string>
#include <cassert>
#include "TObject.h"
#include "ValContext.h"
#include "ValRange.h"

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

    FairDbResult* GetOwner() const { return fOwner; }
    virtual FairDbTableRow* CreateTableRow() const {return NULL;};
    virtual       UInt_t GetIndex(UInt_t defIndex) const {return defIndex;}

    // State modifying member functions
    void SetOwner(FairDbResult* owner) {fOwner = owner;}

    // I/O  member functions
    virtual void Fill(FairDbResultSet& rs,
                      const FairDbValidityRec* vrec) {assert(0);};
    virtual void Store(FairDbOutRowStream& /* ors */,
                       const FairDbValidityRec* /* vrec */) const { assert(0); }

    // Validity frame functions
    virtual  Int_t GetAggregateNo() const { return -1; }
    virtual  Int_t GetVersion() const { return  fVersion; }
    void  SetVersion(Int_t vers) { fVersion=vers; }

    // Getters that support Data Transmission Fidelity tests.
    virtual ValContext GetContextDTF(UInt_t rid) { return ValContext();}
    virtual string GetTableDescr(const char* alternateName = 0) {return NULL;}
    // <DB> add ons GlobalSeqNo
    virtual UInt_t GetSeqNoDTF() { return 999999990; }

    virtual ValRange GetRangeDTF(UInt_t rid) {
      ValContext context = GetContextDTF(rid);
      ValTimeStamp tsStart = context.GetTimeStamp();

      return ValRange(context.GetDetector(),
                      context.GetSimFlag(),
                      tsStart,
                      ValTimeStamp::GetEOT(),
                      "Data Transmission Fidelity.");
    }

    //
    ValTimeStamp             GetTimeStart() const { return fTimeStart; }
    ValTimeStamp             GetTimeEnd()   const { return fTimeEnd; }
    Detector::Detector_t     GetDetector()  const { return fDetType; }
    SimFlag::SimFlag_t       GetSimFlag()   const { return fSimType; }


  protected:
    Int_t fVersion;
    //
    ValTimeStamp             fTimeStart;
    ValTimeStamp             fTimeEnd;
    Detector::Detector_t     fDetType;
    SimFlag::SimFlag_t       fSimType;


  private:
/// The owning FairDbResult, if any.
    FairDbResult* fOwner;

    ClassDef(FairDbTableRow,0)   // FairDbTableRow for a specific database table.

};


#endif  // FAIRDBTABLEROW_H

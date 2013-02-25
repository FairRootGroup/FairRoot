#ifndef FAIRDBVALIDITYRECBUILDER_H
#define FAIRDBVALIDITYRECBUILDER_H
#include <string>
#include <map>
#include <vector>

#include "FairDb.h"
#include "FairDbValidityRec.h"
#include "ValContext.h"


class FairDbProxy;

class FairDbValidityRecBuilder
{


  public:

// Typedefs and enums

    enum { kMAX_AGGREGATE_NO = 1000 };

// Constructors and destructors
    FairDbValidityRecBuilder(const FairDbProxy& proxy,
                             const ValContext& vc,
                             const FairDb::Task& task,
                             Int_t selectDbNo = -1,
                             Bool_t findFullTimeWindow = true);
    FairDbValidityRecBuilder(const FairDbProxy& proxy,
                             const string& context,
                             const FairDb::Task& task);
    FairDbValidityRecBuilder(const FairDbValidityRec& vr,
                             const std::string tableName);

    virtual ~FairDbValidityRecBuilder();

// State testing member functions
    std::string GetL2CacheName() const;
    FairDb::Task GetTask() const { return fTask; }
    UInt_t GetNumValidityRec() const {
      return fVRecs.size();
    }
///             Get index of AggNo or -1 if missing.
    Int_t IndexOfAggno(Int_t aggNo) const;
    Bool_t IsExtendedContext() const {
      return fIsExtendedContext;
    }
    const FairDbValidityRec& GetValidityRec(Int_t rowNo) const;
    const FairDbValidityRec& GetValidityRecFromAggNo(Int_t aggNo) const {
      return this->GetValidityRec(this->IndexOfAggno(aggNo));
    }
    const FairDbValidityRec& GetValidityRecFromSeqNo(UInt_t SeqNo) const;
    Bool_t NonAggregated() const {
      return  ! this->IsExtendedContext()
              && this->GetNumValidityRec() == 1;
    }

// State changing member functions


  private:

// State changing member functions

    UInt_t AddNewAgg(const FairDbValidityRec& vrec,Int_t aggNo);
    UInt_t AddNewGap(Int_t aggNo);

    void MakeGapRec(const ValContext& vc,
                    const string& tableName,
                    Bool_t findFullTimeWindow = true);


    FairDbValidityRec fGap;     // Default (gap) validity record
    Bool_t fIsExtendedContext;
    FairDb::Task fTask;    // Query task

    std::vector<FairDbValidityRec> fVRecs;
    std::map<Int_t,UInt_t>  fAggNoToIndex;


    ClassDef(FairDbValidityRecBuilder,0) // Creator of eff. ValidityRecs

};


#endif  // FAIRDBVALIDITYRECBUILDER_H

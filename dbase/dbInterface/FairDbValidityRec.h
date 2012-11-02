#ifndef FAIRDBVALIDITYREC_H
#define FAIRDBVALIDITYREC_H

#include "FairDb.h"
#include "FairDbTableRow.h"
#include "ValRange.h"
#include "ValTimeStamp.h"

#include <iosfwd>
#include <string>

class FairDbBinaryFile;
class FairDbTableProxy;
class FairDbValidityRec;

ostream& operator<<(ostream& s, const FairDbValidityRec& vRec);

class FairDbValidityRec : public FairDbTableRow
{


  public:

// Constructors and destructors.
    FairDbValidityRec(Int_t dbNo = -1, Bool_t isGap = kTRUE);
    FairDbValidityRec(const FairDbValidityRec& from);
    FairDbValidityRec(const ValRange& range,
                      FairDb::Task task,
                      Int_t aggNo,
                      UInt_t seqNo,
                      Int_t dbNo = -1,
                      Bool_t isGap = kFALSE,
                      ValTimeStamp time = ValTimeStamp());

    virtual ~FairDbValidityRec();

// State testing member functions

    virtual FairDbTableRow* CreateTableRow() const {
      return new FairDbValidityRec;
    }
    Int_t GetAggregateNo() const { return fAggregateNo; }
    ValTimeStamp GetCreationDate() const { return fCreationDate; }
    UInt_t GetDbNo() const { return fDbNo; }
    ValTimeStamp GetInsertDate() const { return fInsertDate; }
    FairDb::Task GetTask() const { return fTask; }
    std::string GetL2CacheName() const;
    UInt_t GetSeqNo() const { return fSeqNo; }
    const FairDbTableProxy* GetTableProxy() const { return fTableProxy; }
    const ValRange& GetValRange() const { return fValRange;}
    Bool_t HasExpired(const FairDbValidityRec& other) const;
    Bool_t HasExpired(const ValContext& vc,
                      const FairDb::Task& task) const;
    Bool_t IsCompatible(const ValContext& vc,
                        const FairDb::Task& task) const;
    Bool_t IsGap() const { return fIsGap; }

    static     std::string GetL2CacheName(UInt_t seqLo, UInt_t seqHi, ValTimeStamp ts);

// State changing member functions
    void AndTimeWindow(const ValTimeStamp& start,
                       const ValTimeStamp& end);
    void SetAggregateNo(Int_t aggNo) { fAggregateNo = aggNo; }
    void SetDbNo(Int_t dbNo) { fDbNo = dbNo; }
    void SetTableProxy(const FairDbTableProxy* tp) { fTableProxy = tp; }
    void SetTimeWindow(const ValTimeStamp& start,
                       const ValTimeStamp& end);
    void SetValRange(const ValRange& range) { fValRange=range;}
    void Trim(const ValTimeStamp& queryTime,
              const FairDbValidityRec& other);

// I/O  member functions
    virtual void Fill(FairDbResultSet& rs,
                      const FairDbValidityRec* vrec);
    virtual void Store(FairDbOutRowStream& ors,
                       const FairDbValidityRec* vrec) const;
    void Streamer(FairDbBinaryFile& file);

  private:
    Int_t fAggregateNo;
    ValTimeStamp fCreationDate;
    Int_t fDbNo;
    ValTimeStamp fInsertDate;
    Bool_t fIsGap;
    FairDb::Task fTask;
    Int_t fSeqNo;
    const FairDbTableProxy* fTableProxy;
    ValRange fValRange;

    //    FairDbValidityRec& operator=(const FairDbValidityRec& from);

    ClassDef(FairDbValidityRec,0)  // Validity range table row.

};


#endif  // DBIVALIDITYREC_H

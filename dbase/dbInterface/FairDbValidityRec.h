#ifndef FAIRDBVALIDITYREC_H
#define FAIRDBVALIDITYREC_H

#include "FairDbTableRow.h"

#include "FairDb.h"                      // for Version
#include "ValRange.h"                    // for ValRange
#include "ValTimeStamp.h"                // for ValTimeStamp

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, UInt_t, etc

#include <iosfwd>                       // for ostream
#include <string>                       // for string

class FairDbBinaryFile;
class FairDbTableProxy;
class FairDbOutRowStream;
class FairDbResultSet;
class ValContext;

class FairDbValidityRec : public FairDbTableRow
{


  public:

// Constructors and destructors.
    FairDbValidityRec(Int_t dbNo = -1, Bool_t isGap = kTRUE);
    FairDbValidityRec(const FairDbValidityRec& from);
    FairDbValidityRec(const ValRange& range,
                      FairDb::Version task,
                      Int_t aggNo,
                      UInt_t seqNo,
                      Int_t dbNo = -1,
                      Bool_t isGap = kFALSE,
                      ValTimeStamp time = ValTimeStamp());

    FairDbValidityRec& operator=(const FairDbValidityRec& from);

    virtual ~FairDbValidityRec();

// State testing member functions

    virtual FairDbTableRow* CreateTableRow() const {
      return new FairDbValidityRec;
    }
    Int_t GetAggregateNo() const { return fAggregateNo; }
    ValTimeStamp GetCreationDate() const { return fCreationDate; }
    UInt_t GetDbNo() const { return fDbNo; }
    ValTimeStamp GetInsertDate() const { return fInsertDate; }
    FairDb::Version GetVersion() const { return fVersion; }
    std::string GetL2CacheName() const;
    UInt_t GetSeqNo() const { return fSeqNo; }
    const FairDbTableProxy* GetTableProxy() const { return fTableProxy; }
    const ValRange& GetValRange() const { return fValRange;}
    Bool_t HasExpired(const FairDbValidityRec& other) const;
    Bool_t HasExpired(const ValContext& vc,
                      const FairDb::Version& task) const;
    Bool_t IsCompatible(const ValContext& vc,
                        const FairDb::Version& task) const;
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
    FairDb::Version fVersion;
    Int_t fSeqNo;
    const FairDbTableProxy* fTableProxy;
    ValRange fValRange;



    ClassDef(FairDbValidityRec,0)  // Validity range table row.

};

ostream& operator<<(ostream& s, const FairDbValidityRec& vRec);


#endif  // DBIVALIDITYREC_H

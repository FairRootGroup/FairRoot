#ifndef FAIRDBRESULTPTR_H
#define FAIRDBRESULTPTR_H

#include <map>
#include <string>
using std::string;

#include "FairDb.h"
#include "FairDbResult.h"
#include "FairDbValidityRec.h"
#include "ValContext.h"

class FairDbResult;
class FairDbResultKey;
class FairDbSqlContext;
class FairDbTableProxy;

template <class T> class FairDbResultPtr
{

  public:

// Constructors and destructors.
    FairDbResultPtr();
    FairDbResultPtr(const FairDbResultPtr& that);
    FairDbResultPtr(const ValContext& vc,
                    FairDb::Task task = FairDb::kDefaultTask,
                    FairDb::AbortTest abortTest = FairDb::kTableMissing,
                    Bool_t findFullTimeWindow = true);
    FairDbResultPtr(const string& tableName,
                    const ValContext& vc,
                    FairDb::Task task = FairDb::kDefaultTask,
                    FairDb::AbortTest abortTest = FairDb::kTableMissing,
                    Bool_t findFullTimeWindow = true);
    FairDbResultPtr(const string& tableName,
                    const FairDbSqlContext& context,
                    const FairDb::Task& task = FairDb::kAnyTask,
                    const string& data = "",
                    const string& fillOpts = "",
                    FairDb::AbortTest abortTest = FairDb::kTableMissing);
    FairDbResultPtr(const string& tableName,
                    const FairDbValidityRec& vrec,
                    FairDb::AbortTest abortTest = FairDb::kTableMissing);
    FairDbResultPtr(const string& tableName,
                    UInt_t seqNo,
                    UInt_t dbNo,
                    FairDb::AbortTest abortTest = FairDb::kTableMissing);
    virtual ~FairDbResultPtr();


// State testing member functions
    const FairDbResultKey* GetKey() const;
    UInt_t GetNumRows() const;
    const FairDbResult* GetResult() const { return fResult; }
    Int_t GetResultID() const;
    const T* GetRow(UInt_t rowNum) const;
    const T* GetRowByIndex(UInt_t index) const;
    const FairDbValidityRec* GetValidityRec(const FairDbTableRow* row=0) const;
    FairDbTableProxy& TableProxy() const;
    Bool_t ResultsFromDb() const;

    static FairDbTableProxy& GetTableProxy();
    static FairDbTableProxy& GetTableProxy(const string& tableName);

// State changing member functions
    UInt_t NextQuery(Bool_t forwards = kTRUE);
    UInt_t NewQuery(ValContext vc,
                    FairDb::Task task=0,
                    Bool_t findFullTimeWindow = true);
    UInt_t NewQuery(const FairDbSqlContext& context,
                    const FairDb::Task& task = 0,
                    const string& data = "",
                    const string& fillOpts = "");
    UInt_t NewQuery(const FairDbValidityRec& vrec);
    UInt_t NewQuery(UInt_t seqNo,UInt_t dbNo);


  private:
    void Disconnect();
    void SetContext(const FairDbValidityRec& vrec);
    Bool_t ApplyAbortTest();

    FairDbResultPtr& operator=(const FairDbResultPtr&);

    FairDb::AbortTest fAbortTest;
    FairDbTableProxy& fTableProxy;
    const FairDbResult* fResult;
    Detector::Detector_t fDetType;
    SimFlag::SimFlag_t fSimType;

#ifndef __CINT__ //  Hide map from CINT; it complains about missing Streamer() etc.
    static std::map<string,FairDbTableProxy*> fgNameToProxy;
#endif  // __CINT__      
    static             FairDbTableProxy* fgTableProxy;

    ClassDefT(FairDbResultPtr<T>,0)  // ResultPtr for specific database table.

};
ClassDefT2(FairDbResultPtr,T)

#endif  // FAIRDBRESULT_H

#ifndef FAIRDBMULTCONNECTOR_H
#define FAIRDBMULTCONNECTOR_H

#include <map>
#include <ostream>
using std::ostream;
#include <string>
using std::string;
#include <vector>
using std::vector;

#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif

#include "FairDbConnection.h"
#include "FairDbStatement.h"

class TSQL_Statement;

class FairDbMultConnector
{
    friend ostream& operator<<(ostream& s, const FairDbMultConnector& cascader);

  public:


    enum Status { kFailed, kClosed, kOpen };

    FairDbStatement* CreateStatement(UInt_t dbNo) const;

/// Return associated FairDbConnection. FairDbMultConnector retains ownership.
    const FairDbConnection*
    GetConnection(UInt_t dbNo) const;
    FairDbConnection*
    GetConnection(UInt_t dbNo) ;

    string GetDbName(UInt_t dbNo) const;
    Int_t GetDbNo(const string& dbName) const;
    Int_t GetStatus(UInt_t dbNo) const {
      if ( dbNo >= GetNumDb() || ! fConnections[dbNo]  ) { return kFailed; }
      return fConnections[dbNo]->IsClosed() ? kClosed : kOpen;
    }
    string GetStatusAsString(UInt_t dbNo) const ;
    string GetURL(UInt_t dbNo) const {
      return ( dbNo < GetNumDb() ) ? fConnections[dbNo]-> GetUrl(): "";
    }
    Bool_t IsTemporaryTable(const string& tableName,
                            Int_t dbNo) const;
// Cascade-wide getters.

    Int_t AllocateSeqNo(const string& tableName,
                        Int_t requireGlobal = 0,
                        Int_t dbNo = 0) const;
    Int_t GetAuthorisingDbNo() const { return fGlobalSeqNoDbNo; }
    UInt_t GetNumDb() const {return fConnections.size();}
    Int_t  GetTableDbNo(const string& tableName, Int_t selectDbNo = -1) const;
    Bool_t TableExists(const string& tableName, Int_t selectDbNo = -1) const {
      return this->GetTableDbNo(tableName,selectDbNo) >= 0;
    }


    Int_t CreateTemporaryTable(const string& tableName,
                               const string& tableDescr);
    void HoldConnections();
    void ReleaseConnections();
    void SetPermanent(UInt_t dbNo, Bool_t permanent = true);
    // Constructors and destructors.
    FairDbMultConnector();
    virtual ~FairDbMultConnector();
    FairDbMultConnector(const FairDbMultConnector& conn);

    void SetAuthorisingEntry(Int_t entry) {fGlobalSeqNoDbNo = entry;}

  protected:

  private:

    Int_t ReserveNextSeqNo(const string& tableName,
                           Bool_t isGlobal,
                           UInt_t dbNo) const;


    Int_t fGlobalSeqNoDbNo;
    vector<FairDbConnection*> fConnections;
    std::map<string,Int_t> fTemporaryTables;



    class BLock
    {

      public:
        BLock(FairDbStatement* stmtDB, const string& seqnoTable, const string& dataTable);
        ~BLock();

        Bool_t IsBLocked() const { return fLocked; }

      private:

        BLock(const BLock&);
        BLock operator=(const BLock&);

        void SetBLock(Bool_t setting = kTRUE);

        FairDbStatement* fStmt;            // Statement to be used to issue lock
        string fSeqnoTableName;  // The SEQNO table that is locked
        string fDataTableName;   // The data table that is locked
        Bool_t fLocked;          // Lock status

    };



    ClassDef(FairDbMultConnector,0)     // A priority list of Db connections

};

#endif  //


#include <cassert>
#include <fstream>

#include "FairDbWriter.h"
#include "FairDbMultConnector.h"
#include "FairDbOutRowStream.h"
#include "FairDbResPtr.h"
#include "FairDbSqlValPacket.h"
#include "FairDbTableProxy.h"


//templateClassImpUnique(FairDbWriter,T)
ClassImpT(FairDbWriter,T)

//.....................................................................

template<class T>
FairDbWriter<T>::FairDbWriter() :
fAggregateNo(-2),
fDbNo(0),
fPacket(new FairDbSqlValPacket),
fRequireGlobalSeqno(0),
fTableProxy(&FairDbWriter<T>::GetTableProxy()),
fTableName(fTableProxy->GetTableName()),
fUseOverlayCreationDate(kFALSE),
fValidRec(0),
fLogEntry(fTableName)
{

}
//.....................................................................

template<class T>
FairDbWriter<T>::FairDbWriter(const ValRange& vr,
                        Int_t aggNo,
                        FairDb::Task task,
                        ValTimeStamp creationDate,
                        UInt_t dbNo,
                        const std::string& logComment,
                        const std::string& tableName) :
fAggregateNo(aggNo),
fDbNo(dbNo),
fPacket(new FairDbSqlValPacket),
fRequireGlobalSeqno(0),
fTableProxy(&FairDbWriter<T>::GetTableProxy(tableName)),
fTableName(fTableProxy->GetTableName()),
fUseOverlayCreationDate(creationDate == ValTimeStamp(0,0)),
fValidRec(0),
fLogEntry(fTableName,logComment,vr.GetDetectorMask(),vr.GetSimMask(),task)
{

  Open(vr,aggNo,task,creationDate,dbNo,logComment);

}

//.....................................................................

template<class T>
FairDbWriter<T>::FairDbWriter(const ValRange& vr,
                        Int_t aggNo,
                        FairDb::Task task,
                        ValTimeStamp creationDate,
                        const std::string& dbName,
                        const std::string& logComment,
                        const std::string& tableName) :
fAggregateNo(aggNo),
fDbNo(),
fPacket(new FairDbSqlValPacket),
fRequireGlobalSeqno(0),
fTableProxy(&FairDbWriter<T>::GetTableProxy(tableName)),
fTableName(fTableProxy->GetTableName()),
fUseOverlayCreationDate(creationDate == ValTimeStamp(0,0)),
fValidRec(0),
fLogEntry(fTableName,logComment,vr.GetDetectorMask(),vr.GetSimMask(),task)
{

  Open(vr,aggNo,task,creationDate,dbName,logComment);

}

//.....................................................................

template<class T>
FairDbWriter<T>::FairDbWriter(const FairDbValidityRec& vrec,
                        UInt_t dbNo,
                        const std::string& logComment) :
fAggregateNo(0),
fDbNo(dbNo),
fPacket(new FairDbSqlValPacket),
fRequireGlobalSeqno(0),
fTableProxy(0),
fTableName(),
fUseOverlayCreationDate(kFALSE),
fValidRec(new FairDbValidityRec(vrec)),
fLogEntry(fTableName,logComment,vrec.GetValRange().GetDetectorMask(),
          vrec.GetValRange().GetSimMask(),vrec.GetTask())
{

  T pet;
  this->Open(vrec,dbNo,logComment);

}

//.....................................................................

template<class T>
FairDbWriter<T>::FairDbWriter(const FairDbValidityRec& vrec,
                        const std::string& dbName,
                        const std::string& logComment) :
fAggregateNo(0),
fDbNo(),
fPacket(new FairDbSqlValPacket),
fRequireGlobalSeqno(0),
fTableProxy(0),
fTableName(),
fUseOverlayCreationDate(kFALSE),
fValidRec(new FairDbValidityRec(vrec)),
fLogEntry(fTableName,logComment,vrec.GetValRange().GetDetectorMask(),
          vrec.GetValRange().GetSimMask(),vrec.GetTask())
{
  T pet;
  
  this->Open(vrec,dbName,logComment);

}

//.....................................................................

template<class T>
FairDbWriter<T>::~FairDbWriter() {

  Reset();
  delete fPacket;
  fPacket = 0;
  delete fValidRec;
  fValidRec = 0;

}


//.....................................................................

template<class T>
FairDbWriter<T>& FairDbWriter<T>::operator<<(const T& row) {


  if ( ! this->IsOpen() ) return *this;

  Int_t AggNoRow =  row.GetAggregateNo();
  if (  fAggregateNo != AggNoRow ) {
    
    cout  << "Cannot store row data for table  " 
      	<< fTableName
      	<< ", current set has aggregate no.: " << fAggregateNo 
      	<< ", but it has: " << AggNoRow
      	<< " \n  closing FairDbWriter" << endl;
    this->Abort();
    return *this;
  }
  if ( ! fPacket->AddDataRow(*fTableProxy,fValidRec,row) ) {
    cout << "Closing FairDbWriter due to above error." << endl;
    this->Abort();
  }
     
  return *this;

}

//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::CanOutput(Bool_t reportErrors) const {
//
//
//  Purpose:  Return true if open and ready to receive/output  data. 

  if ( ! this->IsOpen(reportErrors) ) return kFALSE;

  if ( this->NeedsLogEntry() && ! fLogEntry.HasReason() ) {
    if ( reportErrors ) cout
      << "Cannot output validity set for table " 
      << fTableName
      << ", writing to Master DB but no log comment has been supplied." << endl;
    return kFALSE;
  }

  UInt_t nstmts = fPacket->GetNumSqlStmts();

  if ( nstmts == 0 ) {
    // not even a VLD insert
    if ( reportErrors ) 
      cout << "Cannot output validity set for table " 
      << fTableName
      << ", no data has been written." << endl;
    return kFALSE;
  }

  if ( nstmts == 1 ) {
    // if VLD insert present but no data rows, just issue a stern warning
    // as it may be intended to obscure now invalid data
    string stmt = fPacket->GetStmt(0);
    bool isvldentry = 
      (stmt.find("INSERT INTO") != string::npos ) &&
      (stmt.find("VLD VALUES")  != string::npos);
    if ( isvldentry ) {
      if ( reportErrors ) 
        cout << "VAL entry but no data for " 
             << fTableName << endl;
    }
    else {
      // this should never, ever happen ... but let's be paranoid
      if ( reportErrors ) {
         
        cout  << "Cannot output validity set for table " 
          	<< fTableName
         	 << ", (no VLD info) no data has been written." << endl;
        fPacket->Print();
      }
      return kFALSE;
    }
  }

  return kTRUE;
}


//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::Close(const char* fileSpec) {

  Bool_t ok = kFALSE;
  
// Skip output unless good data to output.

  if ( CanOutput() ) {

//  Find the next free sequence number.  It must be global if writing to a
//  to a file, otherwise it can be local if DB isn't authorising.
    int seqNoType = fileSpec ? 1 : fRequireGlobalSeqno;
    Int_t seqNo = fTableProxy->GetMultConnector().AllocateSeqNo(fTableName,seqNoType,fDbNo);
    if ( seqNo <= 0 ) {
      
      cout  << "Cannot get sequence number for table " 
        	<< fTableName << endl;
    }
    
    else {

//  Use overlay creation date if required.
      if ( fUseOverlayCreationDate &&  fValidRec 
	  ) fPacket->SetCreationDate(fTableProxy->QueryOverlayCreationDate(*fValidRec,fDbNo));

//  Set SEQNO and perform I/O.
      fPacket->SetSeqNo(seqNo);
      if ( fileSpec ) {
        ofstream fs(fileSpec,ios_base::app);
        if ( ! fs ) cout << "Unable to open " << fileSpec << endl;
        else        ok = fPacket->Write(fs,true);
      }
      else {
        ok = fPacket->Store(fDbNo);
      }

//  Record update if I/O successful and required.
      if ( ok && this->WritingToMaster() ) {
       if ( this->NeedsLogEntry() || fLogEntry.HasReason() )
	ok = fLogEntry.Write(fDbNo,seqNo);
      }
    }
  } 
  
//  Clear out ready for any further I/O.

  fPacket->Clear();

  return ok;
}
//.....................................................................

template<class T>
void FairDbWriter<T>::CompleteOpen(UInt_t dbNo,
                                const std::string& logComment) {


  fDbNo = dbNo;
  if ( (int) fDbNo < 0 ) {
    cout << "Bad database name/number selected. " << endl;
    this->Reset();
    return;
  }

  fAggregateNo = fValidRec->GetAggregateNo();
  fTableName   = fTableProxy->GetTableName(),

// Recreate validity packet.
  fPacket->Recreate(fTableName,
                    fValidRec->GetValRange(),
                    fAggregateNo,
                    fValidRec->GetTask(),
                    fValidRec->GetCreationDate());

// Recreate log entry.
  const ValRange&  vr = fValidRec->GetValRange();
  fLogEntry.Recreate(fTableName,
                     logComment,
                     vr.GetDetectorMask(),
                     vr.GetSimMask(),
                     fValidRec->GetTask());

}

//.....................................................................

template<class T>
FairDbTableProxy& FairDbWriter<T>::GetTableProxy() {

  return FairDbResultPtr<T>::GetTableProxy();
}

//.....................................................................

template<class T>
FairDbTableProxy& FairDbWriter<T>::GetTableProxy(
                                           const std::string& tableName){

  return FairDbResultPtr<T>::GetTableProxy(tableName);

}
//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::IsOpen(Bool_t reportErrors) const {

  if ( ! FairDbTableProxyRegistry::IsActive()  ) {
    if ( reportErrors ) 
      cout << "Cannot use FairDbWriter, the DB has been shutdown." << endl;
  }
  else if (    !fValidRec
            ||  fPacket->GetNumSqlStmts() < 1 ) {
    if ( reportErrors ) 
      cout << "Cannot do I/O on FairDbWriter for " 
           << fTableName
           <<", it is currently closed." << endl;
  }
  else return kTRUE;

  return kFALSE;

}
//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::NeedsLogEntry() const {

  // Some tables are created automatically so don't require entries.
  string tableName(fTableName);
  if (    tableName.substr(0,7)  == "BEAMMON"
       || tableName.substr(0,3)  == "CAL"
       || tableName.substr(0,9)  == "DBU" ) return kFALSE;

  // All other tables need entries if writing to a Master database.

  return this->WritingToMaster();

}

//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::Open (const ValRange& vr,
                           Int_t aggNo,
                           FairDb::Task task,
                           ValTimeStamp creationDate,
                           UInt_t dbNo,
                           const std::string& logComment) {

  bool ok = true;

  if ( ! FairDbTableProxyRegistry::IsActive() ) return kFALSE;
  if ( this->CanOutput(kFALSE) ) ok = Close();

// Test for special creation date.
  fUseOverlayCreationDate = creationDate == ValTimeStamp(0,0);

//  Create a validity record.
  delete fValidRec;
  fValidRec = new FairDbValidityRec(vr,task,aggNo,0,0,kFALSE,creationDate);

// Get a proxy.
  fTableProxy = &FairDbWriter<T>::GetTableProxy(fTableName); 

// Complete opening.
  this->CompleteOpen(dbNo,logComment);
  return ok;

}
//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::Open (const ValRange& vr,
                           Int_t aggNo,
                           FairDb::Task task,
                           ValTimeStamp creationDate,
                           const string& dbName,
                           const std::string& logComment) {

  this->SetDbName(dbName);
  return this->Open(vr,
                    aggNo,
                    task,
                    creationDate,
                    fDbNo,
                    logComment);

}

//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::Open(const FairDbValidityRec& vrec,
                          UInt_t dbNo,
                          const std::string& logComment) {


  bool ok = true;

  if ( ! FairDbTableProxyRegistry::IsActive() ) return kFALSE;
  if ( this->CanOutput(kFALSE) ) ok = Close();

  
// Check that vrec is associated with the right table, but waive
// test for FairDbConfigSet so that it can be used with any.
  const FairDbTableProxy& proxyDefault = FairDbWriter<T>::GetTableProxy();
  const FairDbTableProxy& proxyVrec    = *vrec.GetTableProxy();
  if (    proxyDefault.GetTableName() != "DBICONFIGSET"
       &&    proxyVrec.GetTableName() != proxyDefault.GetTableName() ) {
     
    cout   << "Unable to create FairDbWriter from query:" << endl
       	<< vrec
       	<< " was filled by " << proxyVrec.GetTableName() 
       	<< " not by " << proxyDefault.GetTableName() << endl;
    this->Reset();
    return false;
  }
  else { 
//  Have to cast away const - FairDbWriter needs a modifiable FairDbTableProxy.
    fTableProxy = const_cast<FairDbTableProxy*>(&proxyVrec);
  }

  fUseOverlayCreationDate = vrec.GetCreationDate() == ValTimeStamp(0,0);

  delete fValidRec;
  fValidRec = new FairDbValidityRec(vrec);

// Complete opening.
  this->CompleteOpen(dbNo,logComment);
  return ok;

}

//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::Open(const FairDbValidityRec& vrec,
                          const string& dbName,
                          const std::string& logComment) {


  this->SetDbName(dbName);
  return this->Open(vrec,
                    fDbNo,
                    logComment);

}

//.....................................................................

template<class T>
void FairDbWriter<T>::Reset() {

  fAggregateNo = 0;
  fDbNo        = 0;
  fPacket->Clear();
  fTableProxy  = &FairDbWriter<T>::GetTableProxy();
  fTableName   = fTableProxy->GetTableName();

  delete fValidRec;
  fValidRec    = 0;

}
//.....................................................................

template<class T>
void FairDbWriter<T>::SetDbName(const string& dbName) {


  if ( dbName == "" ) {
    fDbNo = 0;
  }
  else {
    fDbNo =  FairDbTableProxyRegistry::Instance().GetMultConnector().GetDbNo(dbName);
  }
}

//.....................................................................

template<class T>
void FairDbWriter<T>::SetLogComment(const std::string& reason) {

  fLogEntry.SetReason(reason);

}

//.....................................................................

template<class T>
FairDbTableProxy& FairDbWriter<T>::TableProxy() const  {

  assert( FairDbTableProxyRegistry::IsActive() );
  return *fTableProxy;
}

//.....................................................................

template<class T>
Bool_t FairDbWriter<T>::WritingToMaster() const {

  FairDbMultConnector& cascader = FairDbTableProxyRegistry::Instance().GetMultConnector();
  return  (    fDbNo == (UInt_t) cascader.GetAuthorisingDbNo()
            && ! cascader.IsTemporaryTable(fTableName,fDbNo));

}


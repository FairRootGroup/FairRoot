
#include <cassert>
#include <fstream>

#include "FairDbWriter.h"
#include "FairDbConnectionPool.h"
#include "FairDbOutRowStream.h"
#include "FairDbReader.h"
#include "FairDbSqlValidityData.h"
#include "FairDbTableInterface.h"
#include "FairDbLogService.h"

using std::cout;
using std::endl;

//templateClassImpUnique(FairDbWriter,T)
ClassImpT(FairDbWriter,T)


template<class T>
FairDbWriter<T>::FairDbWriter() :
  fAggregateNo(-2),
  fDbNo(0),
  fPacket(new FairDbSqlValidityData),
  fRequireGlobalSeqno(0),
  fTableInterface(&FairDbWriter<T>::GetTableInterface()),
  fTableName(fTableInterface->GetTableName()),
  fUseOverlayCreationDate(kFALSE),
  fValidRec(0),
  fLogEntry(fTableName)
{

}


template<class T>
FairDbWriter<T>::FairDbWriter(const ValInterval& vr,
                              Int_t aggNo,
                              FairDb::Version task,
                              ValTimeStamp creationDate,
                              UInt_t dbNo,
                              const std::string& logComment,
                              const std::string& tableName) :
  fAggregateNo(aggNo),
  fDbNo(dbNo),
  fPacket(new FairDbSqlValidityData),
  fRequireGlobalSeqno(0),
  fTableInterface(&FairDbWriter<T>::GetTableInterface(tableName)),
  fTableName(fTableInterface->GetTableName()),
  fUseOverlayCreationDate(creationDate == ValTimeStamp(0,0)),
  fValidRec(0),
  fLogEntry(fTableName,logComment,vr.GetDetectorMask(),vr.GetSimMask(),task)
{
  //cout << " -I- FairDbWriter Open() called " << endl;
  Open(vr,aggNo,task,creationDate,dbNo,logComment);
}


template<class T>
FairDbWriter<T>::FairDbWriter(const ValInterval& vr,
                              Int_t aggNo,
                              FairDb::Version task,
                              ValTimeStamp creationDate,
                              const std::string& dbName,
                              const std::string& logComment,
                              const std::string& tableName) :
  fAggregateNo(aggNo),
  fDbNo(),
  fPacket(new FairDbSqlValidityData),
  fRequireGlobalSeqno(0),
  fTableInterface(&FairDbWriter<T>::GetTableInterface(tableName)),
  fTableName(fTableInterface->GetTableName()),
  fUseOverlayCreationDate(creationDate == ValTimeStamp(0,0)),
  fValidRec(0),
  fLogEntry(fTableName,logComment,vr.GetDetectorMask(),vr.GetSimMask(),task)
{

  Open(vr,aggNo,task,creationDate,dbName,logComment);

}


template<class T>
FairDbWriter<T>::FairDbWriter(const FairDbValRecord& vrec,
                              UInt_t dbNo,
                              const std::string& logComment) :
  fAggregateNo(0),
  fDbNo(dbNo),
  fPacket(new FairDbSqlValidityData),
  fRequireGlobalSeqno(0),
  fTableInterface(0),
  fTableName(),
  fUseOverlayCreationDate(kFALSE),
  fValidRec(new FairDbValRecord(vrec)),
  fLogEntry(fTableName,logComment,vrec.GetValInterval().GetDetectorMask(),
            vrec.GetValInterval().GetSimMask(),vrec.GetVersion())
{

  T pet;
  this->Open(vrec,dbNo,logComment);

}


template<class T>
FairDbWriter<T>::FairDbWriter(const FairDbValRecord& vrec,
                              const std::string& dbName,
                              const std::string& logComment) :
  fAggregateNo(0),
  fDbNo(),
  fPacket(new FairDbSqlValidityData),
  fRequireGlobalSeqno(0),
  fTableInterface(0),
  fTableName(),
  fUseOverlayCreationDate(kFALSE),
  fValidRec(new FairDbValRecord(vrec)),
  fLogEntry(fTableName,logComment,vrec.GetValInterval().GetDetectorMask(),
            vrec.GetValInterval().GetSimMask(),vrec.GetVersion())
{
  T pet;

  this->Open(vrec,dbName,logComment);

}


template<class T>
FairDbWriter<T>::~FairDbWriter()
{

  Reset();
  delete fPacket;
  fPacket = 0;
  delete fValidRec;
  fValidRec = 0;

}



template<class T>
FairDbWriter<T>& FairDbWriter<T>::operator<<(const T& row)
{

  //cout << "Writer ---> 1" << endl;

  if ( ! this->IsOpen() ) { return *this; }

  Int_t AggNoRow =  row.GetAggregateNo();
  if (  fAggregateNo != AggNoRow ) {

    DBLOG("FairDb",FairDbLog::kError) << "Cannot store row data for table  "
                                      << fTableName
                                      << ", current set has aggregate no.: " << fAggregateNo
                                      << ", but it has: " << AggNoRow
                                      << " \n  closing FairDbWriter" << endl;
    this->Abort();
    return *this;
  }

//cout << "Writer ---> 2" << endl;

  if ( ! fPacket->AddDataRow(*fTableInterface,fValidRec,row) ) {
    DBLOG("FairDb",FairDbLog::kError)  << "Closing FairDbWriter due to above error." << endl;
    this->Abort();
  }

//cout << "Writer ---> 3" << endl;
  return *this;

}


template<class T>
Bool_t FairDbWriter<T>::CanOutput(Bool_t reportErrors) const
{


  if ( ! this->IsOpen(reportErrors) ) { return kFALSE; }

  if ( this->NeedsLogEntry() && ! fLogEntry.HasReason() ) {
    if ( reportErrors ) {
      DBLOG("FairDb",FairDbLog::kError)
          << "Cannot output validity set for table "
          << fTableName
          << ", writing to Master DB but no log comment has been supplied." << endl;
    }
    return kFALSE;
  }

  UInt_t nstmts = fPacket->GetNumSqlStmts();

  if ( nstmts == 0 ) {
    // not even a VLD insert
    if ( reportErrors ) {
      DBLOG("FairDb",FairDbLog::kError) << "Cannot output validity set for table "
                                        << fTableName
                                        << ", no data has been written." << endl;
    }
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
      if ( reportErrors ) {
        DBLOG("FairDb",FairDbLog::kWarning) << "VAL entry but no data for "
                                            << fTableName << endl;
      }
    } else {
      // this should never, ever happen ... but let's be paranoid
      if ( reportErrors ) {
        DBLOG("FairDb",FairDbLog::kError)
            << "Cannot output validity set for table "
            << fTableName
            << ", (no VLD info) no data has been written." << endl;
        fPacket->Print();
      }
      return kFALSE;
    }
  }

  return kTRUE;
}



template<class T>
Bool_t FairDbWriter<T>::Close(const char* fileSpec)
{

  Bool_t ok = kFALSE;


  if ( CanOutput() ) {


    int seqNoType = fileSpec ? 1 : fRequireGlobalSeqno;
    Int_t seqNo = fTableInterface->GetConnectionPool().AllocateSeqNo(fTableName,seqNoType,fDbNo);
    if ( seqNo <= 0 ) {

      DBLOG("FairDb",FairDbLog::kError)   << "Cannot get sequence number for table "
                                          << fTableName << endl;
    }

    else {

      if ( fUseOverlayCreationDate &&  fValidRec
         ) { fPacket->SetCreationDate(fTableInterface->QueryOverlayCreationDate(*fValidRec,fDbNo)); }

      fPacket->SetSeqNo(seqNo);
      if ( fileSpec ) {
        ofstream fs(fileSpec,ios_base::app);
        if ( ! fs ) {  DBLOG("FairDb",FairDbLog::kError)   << "Unable to open " << fileSpec << endl; }
        else { ok = fPacket->Write(fs,true); }
      } else {
        ok = fPacket->Store(fDbNo);
      }

      if ( ok && this->WritingToMaster() ) {
        if ( this->NeedsLogEntry() || fLogEntry.HasReason() ) {
          ok = fLogEntry.Write(fDbNo,seqNo);
        }
      }
    }
  }


  fPacket->Clear();

  return ok;
}

template<class T>
void FairDbWriter<T>::CompleteOpen(UInt_t dbNo,
                                   const std::string& logComment)
{

  fDbNo = dbNo;
  if ( (int) fDbNo < 0 ) {
    DBLOG("FairDb",FairDbLog::kError)   << "Bad database name/number selected. " << endl;
    this->Reset();
    return;
  }

  fAggregateNo = fValidRec->GetAggregateNo();
  fTableName   = fTableInterface->GetTableName(),

// Recreate validity packet.
  fPacket->Recreate(fTableName,
                    fValidRec->GetValInterval(),
                    fAggregateNo,
                    fValidRec->GetVersion(),
                    fValidRec->GetCreationDate());

// Recreate log entry.
  const ValInterval&  vr = fValidRec->GetValInterval();
  fLogEntry.Recreate(fTableName,
                     logComment,
                     vr.GetDetectorMask(),
                     vr.GetSimMask(),
                     fValidRec->GetVersion());

}



template<class T>
FairDbTableInterface& FairDbWriter<T>::GetTableInterface()
{

  return FairDbReader<T>::GetTableInterface();
}



template<class T>
FairDbTableInterface& FairDbWriter<T>::GetTableInterface(
  const std::string& tableName)
{
  return FairDbReader<T>::GetTableInterface(tableName);
}


template<class T>
Bool_t FairDbWriter<T>::IsOpen(Bool_t reportErrors) const
{

  if ( ! FairDbTableInterfaceStore::IsActive()  ) {
    if ( reportErrors ) {
      DBLOG("FairDb",FairDbLog::kError)   << "Cannot use FairDbWriter, the DB has been shutdown." << endl;
    }
  } else if (    !fValidRec
                 ||  fPacket->GetNumSqlStmts() < 1 ) {
    if ( reportErrors ) {
      DBLOG("FairDb",FairDbLog::kError)   << "Cannot do I/O on FairDbWriter for "
                                          << fTableName
                                          <<", it is currently closed." << endl;
    }
  } else { return kTRUE; }

  return kFALSE;

}


template<class T>
Bool_t FairDbWriter<T>::NeedsLogEntry() const
{

  // Some tables are created automatically so don't require entries.
  string tableName(fTableName);
  if (    tableName.substr(0,7)  == "BEAMMON"
          || tableName.substr(0,3)  == "CAL"
          || tableName.substr(0,9)  == "DBU" ) { return kFALSE; }

  // All other tables need entries if writing to a Master database.

  return this->WritingToMaster();

}



template<class T>
Bool_t FairDbWriter<T>::Open (const ValInterval& vr,
                              Int_t aggNo,
                              FairDb::Version task,
                              ValTimeStamp creationDate,
                              UInt_t dbNo,
                              const std::string& logComment)
{

  bool ok = true;

  if ( ! FairDbTableInterfaceStore::IsActive() ) { return kFALSE; }
  if ( this->CanOutput(kFALSE) ) { ok = Close(); }


  fUseOverlayCreationDate = creationDate == ValTimeStamp(0,0);


  delete fValidRec;
  fValidRec = new FairDbValRecord(vr,task,aggNo,0,0,kFALSE,creationDate);


  fTableInterface = &FairDbWriter<T>::GetTableInterface(fTableName);


  this->CompleteOpen(dbNo,logComment);
  return ok;

}


template<class T>
Bool_t FairDbWriter<T>::Open (const ValInterval& vr,
                              Int_t aggNo,
                              FairDb::Version task,
                              ValTimeStamp creationDate,
                              const string& dbName,
                              const std::string& logComment)
{

  this->SetDbName(dbName);
  return this->Open(vr,
                    aggNo,
                    task,
                    creationDate,
                    fDbNo,
                    logComment);

}



template<class T>
Bool_t FairDbWriter<T>::Open(const FairDbValRecord& vrec,
                             UInt_t dbNo,
                             const std::string& logComment)
{


  bool ok = true;

  if ( ! FairDbTableInterfaceStore::IsActive() ) { return kFALSE; }
  if ( this->CanOutput(kFALSE) ) { ok = Close(); }


  const FairDbTableInterface& proxyDefault = FairDbWriter<T>::GetTableInterface();
  const FairDbTableInterface& proxyVrec    = *vrec.GetTableInterface();
  if (    proxyDefault.GetTableName() != "FAIRDBCONFIGDATA"
          &&    proxyVrec.GetTableName() != proxyDefault.GetTableName() ) {

    DBLOG("FairDb",FairDbLog::kError)     << "Unable to create FairDbWriter from query:" << endl
                                          << vrec
                                          << " was filled by " << proxyVrec.GetTableName()
                                          << " not by " << proxyDefault.GetTableName() << endl;
    this->Reset();
    return false;
  } else {

    fTableInterface = const_cast<FairDbTableInterface*>(&proxyVrec);
  }

  fUseOverlayCreationDate = vrec.GetCreationDate() == ValTimeStamp(0,0);

  delete fValidRec;
  fValidRec = new FairDbValRecord(vrec);


  this->CompleteOpen(dbNo,logComment);
  return ok;

}



template<class T>
Bool_t FairDbWriter<T>::Open(const FairDbValRecord& vrec,
                             const string& dbName,
                             const std::string& logComment)
{


  this->SetDbName(dbName);
  return this->Open(vrec,
                    fDbNo,
                    logComment);

}



template<class T>
void FairDbWriter<T>::Reset()
{

  fAggregateNo = 0;
  fDbNo        = 0;
  fPacket->Clear();
  fTableInterface  = &FairDbWriter<T>::GetTableInterface();
  fTableName   = fTableInterface->GetTableName();

  delete fValidRec;
  fValidRec    = 0;

}


template<class T>
void FairDbWriter<T>::SetDbName(const string& dbName)
{


  if ( dbName == "" ) {
    fDbNo = 0;
  } else {
    fDbNo =  FairDbTableInterfaceStore::Instance().GetConnectionPool().GetDbNo(dbName);
  }
}



template<class T>
void FairDbWriter<T>::SetLogComment(const std::string& reason)
{

  fLogEntry.SetReason(reason);

}


template<class T>
FairDbTableInterface& FairDbWriter<T>::TableInterface() const
{

  assert( FairDbTableInterfaceStore::IsActive() );
  return *fTableInterface;
}


template<class T>
Bool_t FairDbWriter<T>::WritingToMaster() const
{

  FairDbConnectionPool& cascader = FairDbTableInterfaceStore::Instance().GetConnectionPool();
  return  (    fDbNo == (UInt_t) cascader.GetAuthorisingDbNo()
               && ! cascader.IsTemporaryTable(fTableName,fDbNo));

}



#include <iostream>
#include <sstream>

#include "TString.h"
#include "TSystem.h"
#include "TUrl.h"

#include "FairDbLogEntry.h"

#include "FairDb.h"
#include "FairDbMultConnector.h"
#include "FairDbOutRowStream.h"
#include "FairDbResPtr.h"
#include "FairDbWriter.h"
#include "FairDbResult.h"
#include "FairDbTableProxy.h"
#include "FairDbTableProxyRegistry.h"
#include "FairDbValidityRec.h"


ClassImp(FairDbLogEntry)



#include "FairDbResPtr.tpl"
template class  FairDbResultPtr<FairDbLogEntry>;

#include "FairDbWriter.tpl"
template  class  FairDbWriter<FairDbLogEntry>;


FairDbLogEntry::FairDbLogEntry(const string& tableName, /* = "" */
                               const string& reason,    /* = "" */
                               Int_t detMask,           /* = full mask */
                               Int_t simMask,           /* = full mask */
                               FairDb::Task task,          /* = 0  */
                               Int_t logSeqNoMin,       /* = 0  */
                               Int_t logSeqNoMax,       /* = 0  */
                               Int_t logNumSeqNo):      /* = 0  */
  FairDbTableRow(),
  fDbNo(0),
  fSeqNo(0),
  fLogTableName(tableName),
  fLogDetMask(detMask),
  fLogSimMask(simMask),
  fLogTask(task),
  fLogSeqNoMin(logSeqNoMin),
  fLogSeqNoMax(logSeqNoMax),
  fLogNumSeqNo(logNumSeqNo),
  fUpdateTime(),
  fUserName("unknown user"),
  fProcessName(gProgName),
  fHostName(gSystem->HostName()),
  fServerName(),
  fReason()
{

  if ( fLogSeqNoMax == 0 ) { fLogSeqNoMax = logSeqNoMin; }
  if ( fLogNumSeqNo == 0 && logSeqNoMin != 0
     ) { fLogNumSeqNo = fLogSeqNoMax - fLogSeqNoMin +1; }

  this->SetServerName();
  this->SetReason(reason);

  // Try to get username from the environment.
  const char* userName =  gSystem->Getenv("USER");
  if ( ! userName ) { userName =  gSystem->Getenv("USERNAME"); }
  if ( ! userName ) { userName =  gSystem->Getenv("LOGNAME"); }
  if ( userName ) { fUserName = userName; }

}
//.....................................................................

FairDbLogEntry::~FairDbLogEntry()
{

}
//.....................................................................

std::ostream& operator<<(ostream& s, const FairDbLogEntry& logEntry)
{

  s << "FairDbLogEntry: Table  " << logEntry.GetLogTableName();
  if ( logEntry.GetLogSeqNoMin() ==  logEntry.GetLogSeqNoMax() ) {
    s << " SEQNO: " << logEntry.GetLogSeqNoMin();
  } else
    s << " SEQNO min: " << logEntry.GetLogSeqNoMin()
      << " SEQNO max: " << logEntry.GetLogSeqNoMax()
      << " No. SEQNOs: " << logEntry.GetLogNumSeqNo();
  s << " DetectorMask: " << logEntry.GetDetectorMask()
    << " SimMask: " << logEntry.GetSimMask()
    << " Task: " << logEntry.GetTask()
    << "\n Updated on " << logEntry.GetUpdateTime().AsString("s")
    << " by " << logEntry.GetUserName()
    << " running " << logEntry.GetProcessName()
    << " on " << logEntry.GetHostName()
    << " connected to " << logEntry.GetServerName()
    << "\n Reason for update:-\n " << logEntry.GetReason() << endl;

  return s;

}

void FairDbLogEntry::Fill(FairDbResultSet& rs,
                          const FairDbValidityRec* vrec)
{
  rs >> fLogTableName
     >> fLogSeqNoMin
     >> fLogSeqNoMax
     >> fLogNumSeqNo
     >> fUserName
     >> fProcessName
     >> fHostName
     >> fServerName
     >> fReason;
  fLogDetMask = fLogSimMask = fLogTask = 0;
  if ( vrec ) {
    fLogDetMask = vrec->GetValRange().GetDetectorMask();
    fLogSimMask = vrec->GetValRange().GetSimMask();
    fLogTask    = vrec->GetTask();
    fUpdateTime = vrec->GetValRange().GetTimeStart();
  }
}


void FairDbLogEntry::Recreate(const string& tableName, /* = "" */
                              const string& reason,    /* = "" */
                              Int_t detMask,           /* = full mask */
                              Int_t simMask,           /* = full mask */
                              FairDb::Task task,          /* = 0  */
                              Int_t logSeqNoMin,       /* = 0  */
                              Int_t logSeqNoMax,       /* = 0  */
                              Int_t logNumSeqNo)       /* = 0  */
{
  if (    fSeqNo > 0
          && ( tableName    == ""                       || tableName   == fLogTableName )
          && ( detMask      == Detector::FullMask()     || detMask     == fLogDetMask )
          && ( simMask      == SimFlag::FullMask()      || simMask     == fLogSimMask )
          && ( task         == 0                        || task        == fLogTask )
          && ( logSeqNoMin  == 0                        || logSeqNoMin ==  fLogSeqNoMin)
          && ( logSeqNoMax  == 0                        || logSeqNoMax == fLogSeqNoMax )
          && ( logNumSeqNo  == 0                        || logNumSeqNo == fLogNumSeqNo )
     ) {
    if ( reason != "" ) { this->SetReason(reason); }
    return;
  }


  fDbNo = 0;
  fSeqNo =0;
  fLogTableName = tableName;
  fLogDetMask = detMask;
  fLogSimMask = simMask;
  fLogTask = task;
  fLogSeqNoMin = logSeqNoMin;
  fLogSeqNoMax = logSeqNoMax;
  fLogNumSeqNo = logNumSeqNo;
  this->SetReason(reason);

}


void FairDbLogEntry::SetReason(const string& reason)
{

  fReason = reason;

  // If fReason starts '@' treat remainder as file name
  // to be read into fReason.
  if ( fReason.size() && fReason[0] == '@' ) {
    string fileName(fReason,1);
    fReason.clear();
    ifstream reasonFile(fileName.c_str());
    if ( ! reasonFile.is_open() ) {
      cout << "Cannot read \"Reason File\" " << fileName << endl;
    } else {
      string line;
      while ( ! reasonFile.eof() ) {
        getline(reasonFile,line);
        if (    line.substr(0,11) == "FIXUP-FILE:"
                || line.substr(0,10) == "BROADCAST:" ) {
          continue;
        }
        if ( fReason.size() ) { fReason += '\n'; }
        fReason += line;
      }
      reasonFile.close();
    }
  }
}


void FairDbLogEntry::SetServerName()
{

  string urlStr = FairDbTableProxyRegistry::Instance().GetMultConnector().GetURL(fDbNo);
  TUrl url(urlStr.c_str());
  fServerName = url.GetHost();

}
//.....................................................................

void FairDbLogEntry::Store(FairDbOutRowStream& ors,
                           const FairDbValidityRec* /* vrec */) const
{

  ors << fLogTableName
      << fLogSeqNoMin
      << fLogSeqNoMax
      << fLogNumSeqNo
      << fUserName
      << fProcessName
      << fHostName
      << fServerName
      << fReason;
}

//.....................................................................

Bool_t FairDbLogEntry::Write(UInt_t dbNo,
                             Int_t logSeqNo)     /* =0 */
{

  if ( logSeqNo > 0 ) {
    if ( fLogNumSeqNo == 0 ) {
      fLogSeqNoMin = logSeqNo;
      fLogSeqNoMax = logSeqNo;
    }
    if ( logSeqNo < fLogSeqNoMin ) { fLogSeqNoMin = logSeqNo; }
    if ( logSeqNo > fLogSeqNoMax ) { fLogSeqNoMax = logSeqNo; }
    ++fLogNumSeqNo;
  }

  if ( ! this->HasReason() || fLogNumSeqNo == 0) {
    cout << "Cannot write LogEntry - no reason and/or no SEQNOs defined "
         << endl;
    return kFALSE;
  }

  if ( fSeqNo != 0 && dbNo != fDbNo ) {
    cout << "Cannot write LogEntry - attempting to switch from database"
         << fDbNo << " to " << dbNo << endl;
    return kFALSE;
  }

  fDbNo = dbNo;
  FairDbTableProxy& tblProxy = FairDbTableProxyRegistry::Instance()
                               .GetTableProxy("DBILOGENTRY",this);
  bool replace = true;

  // Allocate SEQNO before first write.
  if ( fSeqNo == 0 ) {
    replace = false;
    int seqNo = tblProxy.GetMultConnector().AllocateSeqNo("DBILOGENTRY",0,fDbNo);
    if ( seqNo <= 0 ) {
      cout    << "Cannot get sequence number for table DBILOGENTRY" << endl;
      return kFALSE;
    }
    fSeqNo = seqNo;
  }

  // Construct a FairDbValidityRec.
  ValRange     vr(fLogDetMask,fLogSimMask,fUpdateTime,fUpdateTime,"FairDbLogEntry");
  FairDbValidityRec vrec(vr,fLogTask,-1,0);

  // Now build and output FairDbSqlValPacket.
  FairDbSqlValPacket packet;
  packet.Recreate("DBILOGENTRY",
                  vrec.GetValRange(),
                  -1,
                  vrec.GetTask(),
                  vrec.GetCreationDate());
  packet.AddDataRow(tblProxy,0,*this);
  packet.SetSeqNo(fSeqNo);
  return packet.Store(fDbNo,replace);
  ;
}

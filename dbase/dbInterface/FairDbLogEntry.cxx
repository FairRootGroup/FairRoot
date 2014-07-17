/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbLogEntry.h"

#include "FairDb.h"                     // for Version
#include "FairDbLogService.h"
#include "FairDbConnectionPool.h"        // for FairDbConnectionPool
#include "FairDbOutTableBuffer.h"         // for FairDbOutTableBuffer
#include "FairDbReader.h"               // for FairDbReader
#include "FairDbResult.h"               // for FairDbResultPool
#include "FairDbSqlValidityData.h"         // for FairDbSqlValidityData
#include "FairDbTableInterface.h"           // for FairDbTableInterface
#include "FairDbTableInterfaceStore.h"   // for FairDbTableInterfaceStore
#include "FairDbValRecord.h"          // for FairDbValRecord
#include "FairDbWriter.h"               // for FairDbWriter
#include "ValInterval.h"                   // for ValInterval

#include "TSystem.h"                    // for TSystem, gSystem, gProgName
#include "TUrl.h"                       // for TUrl

#include <iostream>                     // for operator<<, basic_ostream, etc

ClassImp(FairDbLogEntry)



#include "FairDbReader.tpl"
template class  FairDbReader<FairDbLogEntry>;

#include "FairDbWriter.tpl"   // IWYU pragma: keep
template  class  FairDbWriter<FairDbLogEntry>;


FairDbLogEntry::FairDbLogEntry(const string& tableName,
                               const string& reason,
                               Int_t detMask,
                               Int_t simMask,
                               FairDb::Version task,
                               Int_t logSeqNoMin,
                               Int_t logSeqNoMax,
                               Int_t logNumSeqNo):
  FairDbObjTableMap(),
  fDbNo(0),
  fSeqNo(0),
  fLogTableName(tableName),
  fLogDetMask(detMask),
  fLogSimMask(simMask),
  fLogVersion(task),
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

  // Add process id to unique identifier
  char buff[50];
  sprintf(buff,"%s_%i",fProcessName.c_str(),getpid());
  fProcessName=buff;
}

FairDbLogEntry::~FairDbLogEntry()
{

}


std::ostream& operator<<(ostream& s, const FairDbLogEntry& logEntry)
{

  s << "-I- FairDbLogEntry: Table  " << logEntry.GetLogTableName();
  if ( logEntry.GetLogSeqNoMin() ==  logEntry.GetLogSeqNoMax() ) {
    s << " SEQNO: " << logEntry.GetLogSeqNoMin();
  } else
    s << " SEQNO min: " << logEntry.GetLogSeqNoMin()
      << " SEQNO max: " << logEntry.GetLogSeqNoMax()
      << " No. SEQNOs: " << logEntry.GetLogNumSeqNo();
  s << " DetectorID: " << logEntry.GetDetectorMask()
    << " DataID: " << logEntry.GetSimMask()
    << " Version: " << logEntry.GetVersion()
    << "\n Updated on: " << logEntry.GetUpdateTime().AsString("s")
    << " by: " << logEntry.GetUserName()
    << " running process: " << logEntry.GetProcessName()
    << " on host: " << logEntry.GetHostName()
    << " connected to server: " << logEntry.GetServerName()
    << "\n Reason for update:\n " << logEntry.GetReason() << endl;

  return s;

}

void FairDbLogEntry::Fill(FairDbResultPool& rs,
                          const FairDbValRecord* vrec)
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
  fLogDetMask = fLogSimMask = fLogVersion = 0;
  if ( vrec ) {
    fLogDetMask = vrec->GetValInterval().GetDetectorMask();
    fLogSimMask = vrec->GetValInterval().GetSimMask();
    fLogVersion    = vrec->GetVersion();
    fUpdateTime = vrec->GetValInterval().GetTimeStart();
  }
}


void FairDbLogEntry::Recreate(const string& tableName,
                              const string& reason,
                              Int_t detMask,
                              Int_t simMask,
                              FairDb::Version task,
                              Int_t logSeqNoMin,
                              Int_t logSeqNoMax,
                              Int_t logNumSeqNo)
{
  if (    fSeqNo > 0
          && ( tableName    == ""                       || tableName   == fLogTableName )
          && ( detMask      == Detector::FullMask()     || detMask     == fLogDetMask )
          && ( simMask      == DataType::FullMask()      || simMask     == fLogSimMask )
          && ( task         == 0                        || task        == fLogVersion )
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
  fLogVersion = task;
  fLogSeqNoMin = logSeqNoMin;
  fLogSeqNoMax = logSeqNoMax;
  fLogNumSeqNo = logNumSeqNo;
  this->SetReason(reason);

}


void FairDbLogEntry::SetReason(const string& reason)
{

  fReason = reason;

  if ( fReason.size() && fReason[0] == '@' ) {
    string fileName(fReason,1);
    fReason.clear();
    ifstream reasonFile(fileName.c_str());
    if ( ! reasonFile.is_open() ) {
      DBLOG("FairDb",FairDbLog::kError)  << "Cannot read \"Reason from File\" " << fileName << endl;
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

  string urlStr = FairDbTableInterfaceStore::Instance().GetConnectionPool().GetURL(fDbNo);
  TUrl url(urlStr.c_str());
  fServerName = url.GetHost();

}
void FairDbLogEntry::Store(FairDbOutTableBuffer& ors,
                           const FairDbValRecord* ) const
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


Bool_t FairDbLogEntry::Write(UInt_t dbNo,
                             Int_t logSeqNo)
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
    DBLOG("FairDb",FairDbLog::kError) << "Cannot write LogEntry: no reason and/or no SEQNOs defined "
                                      << endl;
    return kFALSE;
  }

  if ( fSeqNo != 0 && dbNo != fDbNo ) {
    DBLOG("FairDb",FairDbLog::kError)  << "Cannot write LogEntry: attempting to switch from database"
                                       << fDbNo << " to " << dbNo << endl;
    return kFALSE;
  }

  fDbNo = dbNo;
  FairDbTableInterface& tblProxy = FairDbTableInterfaceStore::Instance()
                                   .GetTableInterface("FAIRDBLOGENTRY",this);
  bool replace = true;

  // Allocate SEQNO before first write.
  if ( fSeqNo == 0 ) {
    replace = false;
    int seqNo = tblProxy.GetConnectionPool().AllocateSeqNo("FAIRDBLOGENTRY",0,fDbNo);
    if ( seqNo <= 0 ) {
      DBLOG("FairDb",FairDbLog::kError)  << "Cannot get Seq_Id for table FAIRDBLOGENTRY" << endl;
      return kFALSE;
    }
    fSeqNo = seqNo;
  }

  // Construct a FairDbValRecord.
  ValInterval     vr(fLogDetMask,fLogSimMask,fUpdateTime,fUpdateTime,"FairDbLogEntry");
  FairDbValRecord vrec(vr,fLogVersion,-1,0);

  // Now build and output FairDbSqlValidityData.
  FairDbSqlValidityData packet;
  packet.Recreate("FAIRDBLOGENTRY",
                  vrec.GetValInterval(),
                  -1,
                  vrec.GetVersion(),
                  vrec.GetCreationDate());
  packet.AddDataRow(tblProxy,0,*this);
  packet.SetSeqNo(fSeqNo);
  return packet.Store(fDbNo,replace);
  ;
}

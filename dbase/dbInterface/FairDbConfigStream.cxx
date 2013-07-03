#include "FairDbConfigStream.h"
#include "FairDbLogService.h"
#include "FairDbFieldType.h"            // for FairDbFieldType
#include "FairDbMultConnector.h"        // for FairDbMultConnector
#include "FairDbTableProxy.h"           // for FairDbTableProxy
#include "FairDbTableProxyRegistry.h"   // for FairDbTableProxyRegistry
#include "FairDbWriter.h"               // for FairDbWriter
#include "FairRegistry.h"               // for FairRegistry
#include "SimFlag.h"                    // for ESimFlag::kData
#include "ValRange.h"                   // for ValRange
#include "ValTimeStamp.h"               // for ValTimeStamp
#include "db_detector_def.h"            // for Detector, etc

#include <iostream>                     // for operator<<, basic_ostream, etc
#include <sstream>                      // IWYU pragma: keep 
// for ostringstream, istringstream
using std::cout;
using std::endl;
using std::string;
using std::ostringstream;
using std::istringstream;

ClassImp(FairDbConfigStream)


ValContext  FairDbConfigStream::fgDefaultContext(Detector::kCal,
    SimFlag::kData,
    ValTimeStamp() );


FairDbConfigStream::FairDbConfigStream() :
  fCFSet(0),
  fCFSetTable(),
  fCFSetModified(),
  fVRec(),
  fConfigName(),
  fSoftwName()
{
}

//.....................................................................

FairDbConfigStream::FairDbConfigStream(const string& SoftName,
                                       const std::string& ConfigName,
                                       ValContext vc,
                                       FairDb::Version task,
                                       const std::string& tableName) :
  fCFSet(0),
  fCFSetTable(tableName,vc,task),
  fCFSetModified(),
  fVRec(),
  fConfigName(ConfigName),
  fSoftwName(SoftName)
{
  int rowNum = fCFSetTable.GetNumRows()-1;
  while ( rowNum >= 0 ) {
    fCFSet = fCFSetTable.GetRow(rowNum);
    if (    fCFSet->GetParamValue(0) == fSoftwName
            && fCFSet->GetParamValue(1) == fConfigName ) {
      fVRec = *fCFSetTable.GetValidityRec(fCFSet);
      DBLOG("FairDb",FairDbLog::kInfo)  << "FairDbConfigStream for " << fSoftwName
                                        << "," << fConfigName
                                        << " has Validity Record: " << fVRec
                                        << " and Composite no.: " << fCFSet->GetAggregateNo()
                                        << endl;
      return;
    }
    --rowNum;
  }


  fCFSet = 0;

  fVRec.SetDbNo(0);
  fVRec.SetTableProxy(&FairDbResultPtr<FairDbConfigSet>::GetTableProxy(tableName));
  ValTimeStamp start(1970,1,1,0,0,0);
  ValTimeStamp   end(2038,1,1,0,0,0);
  ValRange vr(127,127,start,end,"FairDbConfigStream");
  fVRec.SetValRange(vr);
  DBLOG("FairDb",FairDbLog::kInfo)  << "FairDbConfigStream for " << fSoftwName
                                    << "," << fConfigName
                                    << " has no existing entry; creating a Validity Record: " << fVRec << endl;

}


FairDbConfigStream::~FairDbConfigStream()
{

}



ostream& operator<<(ostream& os, const FairDbConfigStream& cfStream)
{
  const FairDbConfigSet* cfSet = cfStream.GetConfigSet();
  if ( cfSet ) { os << "FairDbConfigSet contains: " << *cfSet << endl; }
  else { os << "FairDbConfigSet is empty! " << endl; }
  return os;
}


const FairDbConfigStream& FairDbConfigStream::operator>>(FairRegistry* reg)
{
  if ( ! reg ) { return *this; }
  Bool_t keysLocked   = reg->KeysLocked();
  Bool_t valuesLocked = reg->ValuesLocked();
  reg->UnLockKeys();
  reg->UnLockValues();
  reg->Clear();

  if ( fCFSet ) {
    UInt_t numParams = fCFSet->GetNumParams();

    if ( numParams == 3 && fCFSet->GetParamName(2) == "CONFIG_DATA" ) {
      istringstream is(fCFSet->GetParamValue(2));
      reg->ReadStream(is);
    } else {
      MAXDBLOG("FairDb",FairDbLog::kError,20) << "Attempting to fill FairRegistry  from a table with "
                                              << numParams << " columns (should be 3) using column named "
                                              << fCFSet->GetParamName(2) << " (should be CONFIG_DATA)." << endl;
    }
  }
  if ( keysLocked   ) { reg->LockKeys(); }
  if ( valuesLocked ) { reg->LockValues(); }
  return *this;
}

FairDbConfigStream& FairDbConfigStream::operator<<(const FairRegistry* reg)
{

  if ( fSoftwName == "" ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "Cannot fill with  (<<): No software name defined." << endl;
    return *this;
  }

  FairDbFieldType stringType(FairDb::kString);

  ostringstream os;
  reg->PrintStream(os);
  fCFSetModified.Clear();
  fCFSetModified.PushBack("SOFTW_NAME", fSoftwName,  stringType);
  fCFSetModified.PushBack("CONFIG_NAME",fConfigName, stringType);
  fCFSetModified.PushBack("CONFIG_DATA",os.str(),    stringType);
  if ( fVRec.GetAggregateNo() > 0 ) { fCFSetModified.SetAggregateNo( fVRec.GetAggregateNo()); }
  fCFSet =  &fCFSetModified;
  return *this;

}



Bool_t FairDbConfigStream::Write(UInt_t dbNo,
                                 const std::string& logComment,
                                 Bool_t localTest )
{

  if ( ! fCFSet ) {
    MAXDBLOG("FairDb",FairDbLog::kError,20) << "No configuration data to write out." << endl;
    return false;
  }

  int requireGlobal = localTest ? -1 : 1;
  if ( fVRec.GetAggregateNo() < 0 ) {
    FairDbMultConnector& cas = FairDbTableProxyRegistry::Instance().GetMultConnector();
    Int_t aggNo = cas.AllocateSeqNo(fVRec.GetTableProxy()->GetTableName(),requireGlobal,dbNo);
    if ( aggNo <= FairDb::kMAXLOCALSEQNO && ! localTest ) {
      DBLOG("FairDb",FairDbLog::kWarning) << "Cannot write out configuration data: no authorising entry in cascade." << endl;
      return false;
    }
    fVRec.SetAggregateNo(aggNo);
    fCFSetModified.SetAggregateNo(aggNo);
    DBLOG("FairDb",FairDbLog::kInfo) << "Aggregate number: " << aggNo
                                     << " allocated to entry " << fSoftwName
                                     << "," << fConfigName
                                     << " in table " << fVRec.GetTableProxy()->GetTableName() << endl;
  }
  FairDbWriter<FairDbConfigSet> writer(fVRec,dbNo,logComment);
  writer.SetRequireGlobalSeqno(requireGlobal);
  writer.SetOverlayCreationDate();
  writer << *fCFSet;
  return writer.Close();

}



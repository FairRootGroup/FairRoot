
#include <sstream>

#include "FairDbConf.h"
#include "FairDbMultConnector.h"
#include "FairDbConfigStream.h"
#include "FairDbFieldType.h"
#include "FairDbTableProxy.h"
#include "FairDbTableProxyRegistry.h"
#include "FairDbWriter.h"
#include "FairRegistry.h"

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
                                       FairDb::Task task,
                                       const std::string& tableName) :
  fCFSet(0),
  fCFSetTable(tableName,vc,task),
  fCFSetModified(),
  fVRec(),
  fConfigName(ConfigName),
  fSoftwName(SoftName)
{

  // Search for row matching software and configuration names.
  int rowNum = fCFSetTable.GetNumRows()-1;
  while ( rowNum >= 0 ) {
    fCFSet = fCFSetTable.GetRow(rowNum);
    if (    fCFSet->GetParamValue(0) == fSoftwName
            && fCFSet->GetParamValue(1) == fConfigName ) {
      fVRec = *fCFSetTable.GetValidityRec(fCFSet);
      cout << "FairDbConfigStream for " << fSoftwName
           << "," << fConfigName
           << " has validity rec: " << fVRec
           << " and aggregate no.: " << fCFSet->GetAggregateNo()
           << endl;
      return;
    }
    --rowNum;
  }

  // Cannot find matching row, leave configuration data as null
  // and set up a validity rec that can be used if creating a
  // new row.

  fCFSet = 0;

  fVRec.SetDbNo(0);
  fVRec.SetTableProxy(&FairDbResultPtr<FairDbConfigSet>::GetTableProxy(tableName));
  ValTimeStamp start(1970,1,1,0,0,0);
  ValTimeStamp   end(2038,1,1,0,0,0);
  ValRange vr(127,127,start,end,"FairDbConfigStream");
  fVRec.SetValRange(vr);
  cout << "FairDbConfigStream for " << fSoftwName
       << "," << fConfigName
       << " has no existing entry; creating validity rec: " << fVRec << endl;

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

//  Record the current state of reg and then clear it.

  Bool_t keysLocked   = reg->KeysLocked();
  Bool_t valuesLocked = reg->ValuesLocked();
  reg->UnLockKeys();
  reg->UnLockValues();
  reg->Clear();

//  Use the owned FairDbConfigSet to fill reg.

  if ( fCFSet ) {
    UInt_t numParams = fCFSet->GetNumParams();

//  Handle configuration tables.

    if ( numParams == 3 && fCFSet->GetParamName(2) == "CONFIG_DATA" ) {
      istringstream is(fCFSet->GetParamValue(2));
      reg->ReadStream(is);
    } else {
      cout<< "Attempting to fill FairRegistry  from a table with "
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
    cout << "Cannot fill (<<): No software name defined." << endl;
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
    cout << "No configuration data to write out." << endl;
    return false;
  }

  // If no aggregate number has been asigned so far, but fCFSet non-zero, then must
  // be creating a new software/config combination with the data in fCFSetModified.
  // Use a global seqno number (or local if localTest) to define a unique aggregate number.
  int requireGlobal = localTest ? -1 : 1;
  if ( fVRec.GetAggregateNo() < 0 ) {
    FairDbMultConnector& cas = FairDbTableProxyRegistry::Instance().GetMultConnector();
    Int_t aggNo = cas.AllocateSeqNo(fVRec.GetTableProxy()->GetTableName(),requireGlobal,dbNo);
    if ( aggNo <= FairDb::kMAXLOCALSEQNO && ! localTest ) {
      cout << "Cannot write out configuration data: no authorising entry in cascade." << endl;
      return false;
    }
    fVRec.SetAggregateNo(aggNo);
    fCFSetModified.SetAggregateNo(aggNo);
    cout << "Aggregate number: " << aggNo
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



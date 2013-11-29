#include <cassert>
#include "FairDbLogService.h"
#include "FairDbResult.h"
#include "FairDbReader.h"
#include "FairDbExtSqlContent.h"
#include "FairDbTableInterface.h"
#include "FairDbTableInterfaceStore.h"
#include "FairDbStopWatchManager.h"
#include "ValTimeStamp.h"

#include <cstdlib>

using std::cout;
using std::endl;
using std::string;
using std::ios_base;
using std::map;

ClassImpT(FairDbReader,T)


template<class T>
map<string,FairDbTableInterface*>  FairDbReader<T>::fgNameToProxy;

template<class T>
FairDbTableInterface* FairDbReader<T>::fgTableInterface = 0;

// CHECK ME (NEMORY)
//template<class T>
//std::vector<T*>  FairDbReader<T>::fListOfT;

template<class T>
FairDbReader<T>::FairDbReader() :
  fAbortTest(FairDb::kDisabled),
  fTableInterface(FairDbReader<T>::GetTableInterface()),
  fResult(0),
  fDetType(Detector::kUnknown),
  fSimType(DataType::kUnknown )
{
  T pet;
}


template<class T>
FairDbReader<T>::FairDbReader(const FairDbReader& that) :
  fAbortTest(that.fAbortTest),
  fTableInterface(that.fTableInterface),
  fResult(that.fResult),
  fDetType(that.fDetType),
  fSimType(that.fSimType)
{

  T pet;
  if ( fResult ) { fResult->Connect(); }

}


template<class T>
FairDbReader<T>::FairDbReader(const ValCondition& vc,
                              FairDb::Version task,
                              FairDb::AbortTest abortTest,
                              Bool_t findFullTimeWindow) :
  fAbortTest(abortTest),
  fTableInterface(FairDbReader<T>::GetTableInterface()),
  fResult(0),
  fDetType(vc.GetDetector()),
  fSimType(vc.GetDataType())
{
  T pet;
  NewQuery(vc, task, findFullTimeWindow);

}

template<class T>
FairDbReader<T>::FairDbReader(const string& tableName,
                              const ValCondition& vc,
                              FairDb::Version task,
                              FairDb::AbortTest abortTest,
                              Bool_t findFullTimeWindow) :
  fAbortTest(abortTest),
  fTableInterface(FairDbReader<T>::GetTableInterface(tableName)),
  fResult(0),
  fDetType(vc.GetDetector()),
  fSimType(vc.GetDataType())
{
  NewQuery(vc, task, findFullTimeWindow);

}

template<class T>
FairDbReader<T>::FairDbReader(const string& tableName,
                              const FairDbExtSqlContent& context,
                              const FairDb::Version& task,
                              const string& data,
                              const string& fillOpts,
                              FairDb::AbortTest abortTest) :
  fAbortTest(abortTest),
  fTableInterface(FairDbReader<T>::GetTableInterface(tableName)),
  fResult(0),
  fDetType(context.GetDetector()),
  fSimType(context.GetDataType())
{

  T pet;

  NewQuery(context,task,data,fillOpts);

}


template<class T>
FairDbReader<T>::FairDbReader(const string& tableName,
                              const FairDbValRecord& vrec,
                              FairDb::AbortTest abortTest) :
  fAbortTest(abortTest),
  fTableInterface(FairDbReader<T>::GetTableInterface(tableName)),
  fResult(0),
  fDetType(),
  fSimType()
{

  this->SetContext(vrec);
  T pet;
  NewQuery(vrec);

}

template<class T>
FairDbReader<T>::FairDbReader(const string& tableName,
                              UInt_t seqNo,
                              UInt_t dbNo,
                              FairDb::AbortTest abortTest) :
  fAbortTest(abortTest),
  fTableInterface(FairDbReader<T>::GetTableInterface(tableName)),
  fResult(0),
  fDetType(),
  fSimType()
{

  T pet;
  NewQuery(seqNo,dbNo);

}

template<class T>
FairDbReader<T>::~FairDbReader()
{
  Disconnect();
}



template<class T>
UInt_t FairDbReader<T>::Activate(const ValCondition& vc,
                                 FairDb::Version task,
                                 FairDb::AbortTest abortTest,
                                 Bool_t findFullTimeWindow)

{
  fAbortTest=abortTest;
  fDetType=vc.GetDetector();
  fSimType=vc.GetDataType();

  T pet;
  return NewQuery(vc, task, findFullTimeWindow);
}



template<class T>
Bool_t FairDbReader<T>::ApplyAbortTest()
{

  if (    fAbortTest == FairDb::kDisabled
          || this->GetNumRows() > 0 ) { return kFALSE; }

  bool tableExists = fTableInterface.TableExists();

  if ( ! tableExists ) {
    DBLOG("FairDb",FairDbLog::kFatal)  << "Fatal Error: Table "
                                       << fTableInterface.GetTableName() << " does not exist"
                                       << endl;
    return kTRUE;
  }
  if ( fAbortTest == FairDb::kDataMissing) {
    DBLOG("FairDb",FairDbLog::kFatal)  << "Fatal Error: no data found in existing Table  "
                                       << fTableInterface.GetTableName() << endl;
    return kTRUE;
  }

  return kFALSE;
}

template<class T>
void FairDbReader<T>::Disconnect()
{

  if ( fResult && FairDbTableInterfaceStore::IsActive() ) {
    fResult->Disconnect();
  }
  fResult = 0;

}

template<class T>
const FairDbResultKey* FairDbReader<T>::GetKey() const
{

  return fResult ? fResult->GetKey() : FairDbResultKey::GetEmptyKey();

}

template<class T>
Int_t FairDbReader<T>::GetResultID() const
{
  return fResult ? fResult->GetID() : 0;

}

template<class T>
FairDbTableInterface& FairDbReader<T>::GetTableInterface()
{

  if ( ! fgTableInterface ) {
    T pet;
    fgTableInterface = &FairDbTableInterfaceStore::Instance()
                       .GetTableInterface(pet.GetName(),&pet);
  }
  return *fgTableInterface;
}


template<class T>
FairDbTableInterface& FairDbReader<T>::GetTableInterface(const string& tableName)
{

// CHECK ME <DB> here is an issue with memory management of heap
// base instanciated container ... to be further studied.

//  cout <<"-I- FairDbReader:: BEGIN GET TABLE PROXY **************** " << endl;
//  cout << "-I- FairDbReader:: GetTableInterface tablename: " <<  tableName << endl;

// CHECK ME !
//cout << "-I- FairDbReader (-) object ************* " << endl;
//  fListOfT.clear();

// Check for request for default table.
  if ( tableName == "" ) { return  FairDbReader::GetTableInterface(); }

// See if we have seen this name before.
  map<string,FairDbTableInterface*>::const_iterator itr
  = fgNameToProxy.find(tableName);
  if ( itr != fgNameToProxy.end() ) { return *( (*itr).second ); }

// No, so ask the Registry for it and save it for next time.

//  cout << "-I- FairDbReader (+) object ************  " << endl;
  T* pet = new T();

// CHECK ME !
//  fListOfT.push_back(pet);


  FairDbTableInterface* proxy = &FairDbTableInterfaceStore::Instance()
                                .GetTableInterface(tableName,pet);
  fgNameToProxy[tableName] = proxy;

  //cout << "-I- FairDbReader****************** end of GETTABLEINTERFACE ****** " <<endl;
  return *proxy;
}


template<class T>
UInt_t FairDbReader<T>::GetNumRows() const
{
  return ( fResult && FairDbTableInterfaceStore::IsActive() )
         ? fResult->GetNumRows() : 0;

}

template<class T>
const T* FairDbReader<T>::GetRow(UInt_t rowNum) const
{

  return ( fResult && FairDbTableInterfaceStore::IsActive() ) ?
         dynamic_cast<const T*>(fResult->GetObjTableMap(rowNum))
         : 0;
}

template<class T>
const T* FairDbReader<T>::GetRowByIndex(UInt_t index) const
{

  return ( fResult && FairDbTableInterfaceStore::IsActive() ) ?
         dynamic_cast<const T*>(fResult->GetObjTableMapByIndex(index))
         : 0;
}


template<class T>
const FairDbValRecord* FairDbReader<T>::GetValidityRec(
  const FairDbObjTableMap* row) const
{

  return ( fResult && FairDbTableInterfaceStore::IsActive() )
         ? &(fResult->GetValidityRec(row)) : 0 ;

}


template<class T>
UInt_t FairDbReader<T>::NextQuery(Bool_t forwards)
{

// Door stops.
  static ValTimeStamp startOfTime(0,0);
  static ValTimeStamp endOfTime(0x7FFFFFFF,0);

  if ( ! fResult ) { return 0; }

  DBLOG("FairDb",FairDbLog::kInfo)   << "\n\nStarting next query: direction "
                                     << ( forwards ?  "forwards" : "backwards" ) << "\n" << endl;

  const FairDbValRecord& vrec = fResult->GetValidityRec();
  const ValInterval& vrnge      = vrec.GetValInterval();

  // If we are heading towards the final boundary, just return the same query.
  if (   forwards && vrnge.GetTimeEnd()   == endOfTime ) { return fResult->GetNumRows(); }
  if ( ! forwards && vrnge.GetTimeStart() == startOfTime ) { return fResult->GetNumRows(); }

  // Step across boundary and construct new context.
  // The end time limit is exclusive, so stepping to the end
  // does cross the boundary
  time_t ts = forwards ? vrnge.GetTimeEnd().GetSec()
              : vrnge.GetTimeStart().GetSec() - 1;
  ValCondition vc(fDetType,fSimType,ValTimeStamp(ts,0));

  return this->NewQuery(vc,vrec.GetVersion(), true);

}

template<class T>
UInt_t FairDbReader<T>::NewQuery(ValCondition vc,
                                 FairDb::Version task,
                                 Bool_t findFullTimeWindow)
{

  if ( ! FairDbTableInterfaceStore::IsActive() ) {
    fResult = 0;
    return 0;
  }
  fDetType = vc.GetDetector();
  fSimType = vc.GetDataType();

  DBLOG("FairDb",FairDbLog::kInfo)<< "\n\nStarting context query: "
                                  << vc  << " data_id: " << task << "\n" << endl;

  FairDbStopWatchManager::gStopWatchManager.RecBegin(fTableInterface.GetTableName(), sizeof(T));
  Disconnect();
  fResult = fTableInterface.Query(vc,task,findFullTimeWindow);
  fResult->Connect();
  FairDbStopWatchManager::gStopWatchManager.RecEnd(fResult->GetNumRows());

  if ( this->ApplyAbortTest() ) {
    DBLOG("FairDb",FairDbLog::kFatal) << "while applying validity context query for "
                                      << vc.AsString() << " with data_id: " << task << endl;
    abort();
  }
  DBLOG("FairDb",FairDbLog::kInfo)  << "\nContext Query completed: "
                                    << vc  << " version: " << task
                                    << "Fetched:  " << fResult->GetNumRows() << " rows\n" << endl;
  return fResult->GetNumRows();

}


template<class T>
UInt_t FairDbReader<T>::NewQuery(const FairDbExtSqlContent& context,
                                 const FairDb::Version& task,
                                 const string& data,
                                 const string& fillOpts)
{

  if ( ! FairDbTableInterfaceStore::IsActive() ) {
    fResult = 0;
    return 0;
  }
  fDetType = context.GetDetector();
  fSimType = context.GetDataType();

  DBLOG("FairDb",FairDbLog::kInfo) << "\n\nStarting extended context query: "
                                   << context.GetString()  << " data_id: " << task
                                   << " data " << data << " fillOpts " << fillOpts << "\n" <<endl;

  FairDbStopWatchManager::gStopWatchManager.RecBegin(fTableInterface.GetTableName(), sizeof(T));
  Disconnect();
  fResult = fTableInterface.Query(context.GetString(),task,data,fillOpts);
  fResult->Connect();
  FairDbStopWatchManager::gStopWatchManager.RecEnd(fResult->GetNumRows());
  if ( this->ApplyAbortTest() ) {
    DBLOG("FairDb",FairDbLog::kFatal) << "while applying extended context query for "
                                      <<  context.c_str()<< " with data_id: " << task
                                      << " secondary query SQL: " << data
                                      << "  and fill options: " << fillOpts << endl;
    abort();
  }

  DBLOG("FairDb",FairDbLog::kInfo) << "\n\nCompleted extended context query: "
                                   << context.GetString()  << " data_id " << task
                                   << " data " << data << " fillOpts" << fillOpts
                                   << " Found:  " << fResult->GetNumRows() << " rows\n" << endl;

  return fResult->GetNumRows();

}

template<class T>
UInt_t FairDbReader<T>::NewQuery(const FairDbValRecord& vrec)
{

  if ( ! FairDbTableInterfaceStore::IsActive() ) {
    fResult = 0;
    return 0;
  }
  DBLOG("FairDb",FairDbLog::kInfo) << "\n\nStarting FairDbValRecord query: "
                                   << vrec << "\n" << endl;

  this->SetContext(vrec);
  FairDbStopWatchManager::gStopWatchManager.RecBegin(fTableInterface.GetTableName(), sizeof(T));
  Disconnect();

  fResult = fTableInterface.Query(vrec,kFALSE);
  fResult->Connect();
  FairDbStopWatchManager::gStopWatchManager.RecEnd(fResult->GetNumRows());
  if ( this->ApplyAbortTest() ) {
    DBLOG("FairDb",FairDbLog::kFatal) << "while applying validity rec query for "
                                      << vrec << endl;
    abort();
  }
  DBLOG("FairDb",FairDbLog::kInfo) << "\n\nCompletedFairDbValRecord query: "
                                   << vrec
                                   << " Found:  " << fResult->GetNumRows() << " rows\n"  << endl;

  return fResult->GetNumRows();

}



template<class T>
UInt_t FairDbReader<T>::NewQuery(UInt_t seqNo,UInt_t dbNo)
{

  if ( ! FairDbTableInterfaceStore::IsActive() ) {
    fResult = 0;
    return 0;
  }
  DBLOG("FairDb",FairDbLog::kInfo) << "\n\nStarting SeqNo query: "
                                   << seqNo << "\n" << endl;

  FairDbStopWatchManager::gStopWatchManager.RecBegin(fTableInterface.GetTableName(), sizeof(T));
  Disconnect();
  fResult = fTableInterface.Query(seqNo,dbNo);
  fResult->Connect();
  FairDbStopWatchManager::gStopWatchManager.RecEnd(fResult->GetNumRows());
  if ( this->ApplyAbortTest() ) {

    DBLOG("FairDb",FairDbLog::kFatal) << "while applying SEQNO query for "
                                      << seqNo << " on database " << dbNo << endl;

    abort();
  }
  this->SetContext(fResult->GetValidityRec());

  DBLOG("FairDb",FairDbLog::kInfo) << "\n\nCompleted SeqNo query: "
                                   << seqNo
                                   << " Found:  " << fResult->GetNumRows() << " rows\n" << endl;

  return fResult->GetNumRows();
}



template<class T>
Bool_t FairDbReader<T>::ResultsFromDb() const
{
  return fResult ? fResult->ResultsFromDb() : kFALSE;
}

template<class T>
void FairDbReader<T>::SetContext(const FairDbValRecord& vrec)
{

  const ValInterval& vrng = vrec.GetValInterval();
  Int_t detMask        = vrng.GetDetectorMask();
  Int_t simMask        = vrng.GetSimMask();

  fDetType = Detector::kUnknown;
  fDetType = Detector::GetDetType(detMask);

  fSimType = DataType::kUnknown;
  if      ( simMask & DataType::kData) { fSimType = DataType::kData; }
  else if ( simMask & DataType::kMC) { fSimType = DataType::kMC; }

}

template<class T>
FairDbTableInterface& FairDbReader<T>::TableInterface() const
{
  assert( FairDbTableInterfaceStore::IsActive() );
  return fTableInterface;
}


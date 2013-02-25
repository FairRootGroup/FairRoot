#include <cassert>

#include "FairDbResult.h"
#include "FairDbResPtr.h"
#include "FairDbSqlContext.h"
#include "FairDbTableProxy.h" //!!registry!!
#include "FairDbTableProxyRegistry.h" //!!registry!!
#include "FairDbTimerManager.h"
#include "ValTimeStamp.h"

#include <cstdlib>

ClassImpT(FairDbResultPtr,T)


template<class T>
map<string,FairDbTableProxy*>  FairDbResultPtr<T>::fgNameToProxy;

template<class T>
FairDbTableProxy* FairDbResultPtr<T>::fgTableProxy = 0;


template<class T>
FairDbResultPtr<T>::FairDbResultPtr() :
fAbortTest(FairDb::kDisabled),
fTableProxy(FairDbResultPtr<T>::GetTableProxy()),
fResult(0),
fDetType(Detector::kUnknown),
fSimType(SimFlag::kUnknown )
{
  T pet;
}
//.....................................................................

template<class T>
FairDbResultPtr<T>::FairDbResultPtr(const FairDbResultPtr& that) :
fAbortTest(that.fAbortTest),
fTableProxy(that.fTableProxy),
fResult(that.fResult),
fDetType(that.fDetType),
fSimType(that.fSimType)
{

  T pet;
  if ( fResult ) fResult->Connect();

}

//.....................................................................

template<class T>
FairDbResultPtr<T>::FairDbResultPtr(const ValContext& vc, 
                              FairDb::Task task,
                              FairDb::AbortTest abortTest,
                              Bool_t findFullTimeWindow) :
fAbortTest(abortTest),
fTableProxy(FairDbResultPtr<T>::GetTableProxy()),
fResult(0),
fDetType(vc.GetDetector()),
fSimType(vc.GetSimFlag())
{
  T pet;
  NewQuery(vc, task, findFullTimeWindow);

}

template<class T>
FairDbResultPtr<T>::FairDbResultPtr(const string& tableName,
                              const ValContext& vc, 
                              FairDb::Task task,
                              FairDb::AbortTest abortTest,
                              Bool_t findFullTimeWindow) :
fAbortTest(abortTest),
fTableProxy(FairDbResultPtr<T>::GetTableProxy(tableName)),
fResult(0),
fDetType(vc.GetDetector()),
fSimType(vc.GetSimFlag())
{
  NewQuery(vc, task, findFullTimeWindow);

}
template<class T>
FairDbResultPtr<T>::FairDbResultPtr(const string& tableName,
                              const FairDbSqlContext& context,
			      const FairDb::Task& task, 
                              const string& data,
                              const string& fillOpts,
                              FairDb::AbortTest abortTest) :
fAbortTest(abortTest),
fTableProxy(FairDbResultPtr<T>::GetTableProxy(tableName)),
fResult(0),
fDetType(context.GetDetector()),
fSimType(context.GetSimFlag())
{

  T pet;

  NewQuery(context,task,data,fillOpts);

}


template<class T>
FairDbResultPtr<T>::FairDbResultPtr(const string& tableName,
                              const FairDbValidityRec& vrec,
                              FairDb::AbortTest abortTest) :
fAbortTest(abortTest),
fTableProxy(FairDbResultPtr<T>::GetTableProxy(tableName)),
fResult(0),
fDetType(),
fSimType()
{

  this->SetContext(vrec);
  T pet;
  NewQuery(vrec);

}

template<class T>
FairDbResultPtr<T>::FairDbResultPtr(const string& tableName,
                              UInt_t seqNo,
                              UInt_t dbNo,
                              FairDb::AbortTest abortTest) :
fAbortTest(abortTest),
fTableProxy(FairDbResultPtr<T>::GetTableProxy(tableName)),
fResult(0),
fDetType(),
fSimType()
{
  
  T pet;
  NewQuery(seqNo,dbNo);

}
template<class T>
FairDbResultPtr<T>::~FairDbResultPtr() {
  Disconnect();

}
template<class T>
Bool_t FairDbResultPtr<T>::ApplyAbortTest() {

  if (    fAbortTest == FairDb::kDisabled
       || this->GetNumRows() > 0 ) return kFALSE;

  bool tableExists = fTableProxy.TableExists();

  if ( ! tableExists ) {
    cout << "Fatal error: table "
                           << fTableProxy.GetTableName() << " does not exist"
			   << endl;
    return kTRUE;
  }
  if ( fAbortTest == FairDb::kDataMissing) {
    cout << "Fatal error: no data found in existing table  "
                           << fTableProxy.GetTableName() << endl;
    return kTRUE;
  }

  return kFALSE;
}

template<class T>
void FairDbResultPtr<T>::Disconnect() {

  if ( fResult && FairDbTableProxyRegistry::IsActive() ) {
    fResult->Disconnect();
  }
  fResult = 0;

}

template<class T>
const FairDbResultKey* FairDbResultPtr<T>::GetKey() const {

  return fResult ? fResult->GetKey() : FairDbResultKey::GetEmptyKey();

}

template<class T>
Int_t FairDbResultPtr<T>::GetResultID() const {
  return fResult ? fResult->GetID() : 0;

}

template<class T>
FairDbTableProxy& FairDbResultPtr<T>::GetTableProxy() {

  if ( ! fgTableProxy ) {
    T pet;
    fgTableProxy = &FairDbTableProxyRegistry::Instance()
                                     .GetTableProxy(pet.GetName(),&pet);
  }
  return *fgTableProxy;
}


template<class T>
FairDbTableProxy& FairDbResultPtr<T>::GetTableProxy(const string& tableName){


// Check for request for default table.
  if ( tableName == "" ) return  FairDbResultPtr::GetTableProxy();

// See if we have seen this name before.
  map<string,FairDbTableProxy*>::const_iterator itr
                                        = fgNameToProxy.find(tableName);
  if ( itr != fgNameToProxy.end() ) return *( (*itr).second );
  
// No, so ask the Registry for it and save it for next time.
 T pet;
 FairDbTableProxy* proxy = &FairDbTableProxyRegistry::Instance()
                                      .GetTableProxy(tableName,&pet);
  fgNameToProxy[tableName] = proxy;
  return *proxy;
}


template<class T>
UInt_t FairDbResultPtr<T>::GetNumRows() const {
  return ( fResult && FairDbTableProxyRegistry::IsActive() ) 
          ? fResult->GetNumRows() : 0;

}

template<class T>
const T* FairDbResultPtr<T>::GetRow(UInt_t rowNum) const {

  return ( fResult && FairDbTableProxyRegistry::IsActive() ) ?
      dynamic_cast<const T*>(fResult->GetTableRow(rowNum))
    : 0;
}

template<class T>
const T* FairDbResultPtr<T>::GetRowByIndex(UInt_t index) const {

  return ( fResult && FairDbTableProxyRegistry::IsActive() ) ?
      dynamic_cast<const T*>(fResult->GetTableRowByIndex(index))
    : 0;
}


template<class T>
const FairDbValidityRec* FairDbResultPtr<T>::GetValidityRec(
                              const FairDbTableRow* row) const {

  return ( fResult && FairDbTableProxyRegistry::IsActive() )
      ? &(fResult->GetValidityRec(row)) : 0 ;
 
}


template<class T>
UInt_t FairDbResultPtr<T>::NextQuery(Bool_t forwards) {

// Door stops.
  static ValTimeStamp startOfTime(0,0);
  static ValTimeStamp endOfTime(0x7FFFFFFF,0);

  if ( ! fResult ) return 0;

  cout  << "\n\nStarting next query: direction "
        << ( forwards ?  "forwards" : "backwards" ) << "\n" << endl;

  const FairDbValidityRec& vrec = fResult->GetValidityRec();
  const ValRange& vrnge      = vrec.GetValRange();

  // If we are heading towards the final boundary, just return the same query.
  if (   forwards && vrnge.GetTimeEnd()   == endOfTime )   return fResult->GetNumRows();
  if ( ! forwards && vrnge.GetTimeStart() == startOfTime ) return fResult->GetNumRows();

  // Step across boundary and construct new context.
  // The end time limit is exclusive, so stepping to the end
  // does cross the boundary
  time_t ts = forwards ? vrnge.GetTimeEnd().GetSec()
                       : vrnge.GetTimeStart().GetSec() - 1;
  ValContext vc(fDetType,fSimType,ValTimeStamp(ts,0));

  return this->NewQuery(vc,vrec.GetTask(), true);

}

template<class T>
UInt_t FairDbResultPtr<T>::NewQuery(ValContext vc, 
                                 FairDb::Task task,
                                 Bool_t findFullTimeWindow) {

  if ( ! FairDbTableProxyRegistry::IsActive() ) {
    fResult = 0;
    return 0;
  }
  fDetType = vc.GetDetector();
  fSimType = vc.GetSimFlag();

  cout << "\n\nStarting context query: "
                             << vc  << " task " << task << "\n" << endl;

  FairDbTimerManager::gTimerManager.RecBegin(fTableProxy.GetTableName(), sizeof(T));
  Disconnect();
  fResult = fTableProxy.Query(vc,task,findFullTimeWindow);
  fResult->Connect();
  FairDbTimerManager::gTimerManager.RecEnd(fResult->GetNumRows());

  if ( this->ApplyAbortTest() ) {
    cout << "while applying validity context query for "
			   << vc.AsString() << " with task " << task << endl;
    abort();
  }
  cout  << "\nCompleted context query: "
                             << vc  << " task " << task 
                             << " Found:  " << fResult->GetNumRows() << " rows\n" << endl;
  return fResult->GetNumRows();

}
//.....................................................................

template<class T>
UInt_t FairDbResultPtr<T>::NewQuery(const FairDbSqlContext& context,
			         const FairDb::Task& task, 
                                 const string& data,
                                 const string& fillOpts) {

  if ( ! FairDbTableProxyRegistry::IsActive() ) {
    fResult = 0;
    return 0;
  }
  fDetType = context.GetDetector();
  fSimType = context.GetSimFlag();

  cout << "\n\nStarting extended context query: "
                             << context.GetString()  << " task " << task 
                             << " data " << data << " fillOpts " << fillOpts << "\n" <<endl;

  FairDbTimerManager::gTimerManager.RecBegin(fTableProxy.GetTableName(), sizeof(T));
  Disconnect();
  fResult = fTableProxy.Query(context.GetString(),task,data,fillOpts);
  fResult->Connect();
  FairDbTimerManager::gTimerManager.RecEnd(fResult->GetNumRows());
  if ( this->ApplyAbortTest() ) {
    cout << "while applying extended context query for "
			   <<  context.c_str()<< " with task " << task 
			   << " secondary query SQL: " << data
			   << "  and fill options: " << fillOpts << endl;
    abort();
  }

  cout  << "\n\nCompleted extended context query: "
                             << context.GetString()  << " task " << task 
                             << " data " << data << " fillOpts" << fillOpts 
                             << " Found:  " << fResult->GetNumRows() << " rows\n" << endl;

  return fResult->GetNumRows();

}

template<class T>
UInt_t FairDbResultPtr<T>::NewQuery(const FairDbValidityRec& vrec) {

  if ( ! FairDbTableProxyRegistry::IsActive() ) {
    fResult = 0;
    return 0;
  }
  cout << "\n\nStarting FairDbValidityRec query: "
                             << vrec << "\n" << endl;

  this->SetContext(vrec);
  FairDbTimerManager::gTimerManager.RecBegin(fTableProxy.GetTableName(), sizeof(T));
  Disconnect();

// Play safe and don't allow result to be used; it's validity may not
// have been trimmed by neighbouring records.
  fResult = fTableProxy.Query(vrec,kFALSE);
  fResult->Connect();
  FairDbTimerManager::gTimerManager.RecEnd(fResult->GetNumRows());
  if ( this->ApplyAbortTest() ) {
    cout << "while applying validity rec query for "
			   << vrec << endl;
    abort();
  }
  cout << "\n\nCompletedFairDbValidityRec query: "
                             << vrec 
                             << " Found:  " << fResult->GetNumRows() << " rows\n"  << endl;
  return fResult->GetNumRows();

}
//.....................................................................

template<class T>
UInt_t FairDbResultPtr<T>::NewQuery(UInt_t seqNo,UInt_t dbNo) {

  if ( ! FairDbTableProxyRegistry::IsActive() ) {
    fResult = 0;
    return 0;
  }
  cout << "\n\nStarting SeqNo query: "
       << seqNo << "\n" << endl;
  FairDbTimerManager::gTimerManager.RecBegin(fTableProxy.GetTableName(), sizeof(T));
  Disconnect();
  fResult = fTableProxy.Query(seqNo,dbNo);
  fResult->Connect();
  FairDbTimerManager::gTimerManager.RecEnd(fResult->GetNumRows());
  if ( this->ApplyAbortTest() ) {
     cout << "while applying SEQNO query for "
			   << seqNo << " on database " << dbNo << endl;
    abort();
  }
  this->SetContext(fResult->GetValidityRec());
  cout << "\n\nCompleted SeqNo query: "
                             << seqNo
                             << " Found:  " << fResult->GetNumRows() << " rows\n" << endl;
  return fResult->GetNumRows();

}

//.....................................................................

template<class T>
Bool_t FairDbResultPtr<T>::ResultsFromDb() const {

  return fResult ? fResult->ResultsFromDb() : kFALSE;

}

template<class T>
void FairDbResultPtr<T>::SetContext(const FairDbValidityRec& vrec) {

  const ValRange& vrng = vrec.GetValRange();
  Int_t detMask        = vrng.GetDetectorMask();
  Int_t simMask        = vrng.GetSimMask();

  fDetType = Detector::kUnknown;
  if      ( detMask & Detector::kCal )            fDetType = Detector::kCal;
  else if ( detMask & Detector::kCalCrystal)      fDetType = Detector::kCalCrystal;
  else if ( detMask & Detector::kDch)             fDetType = Detector::kDch;
  else if ( detMask & Detector::kGfi)             fDetType = Detector::kGfi;
  else if ( detMask & Detector::kLand)            fDetType = Detector::kLand;
  else if ( detMask & Detector::kMtof)            fDetType = Detector::kMtof;
  else if ( detMask & Detector::kTof)             fDetType = Detector::kTof;
  else if ( detMask & Detector::kTracker)         fDetType = Detector::kTracker;

  fSimType = SimFlag::kUnknown;
  if      ( simMask & SimFlag::kData)        fSimType = SimFlag::kData;
  else if ( simMask & SimFlag::kMC)          fSimType = SimFlag::kMC;

}

//.....................................................................

template<class T>
FairDbTableProxy& FairDbResultPtr<T>::TableProxy() const  {

  assert( FairDbTableProxyRegistry::IsActive() );
  return fTableProxy; 
}


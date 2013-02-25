
#include "Detector.h"
#include "SimFlag.h"
#include "FairDbProxy.h"
#include "FairDbResult.h"
#include "FairDbSimFlagAssociation.h"
#include "FairDbValidityRec.h"
#include "FairDbValidityRecBuilder.h"
#include "ValContext.h"

ClassImp(FairDbValidityRecBuilder)

FairDbValidityRecBuilder::FairDbValidityRecBuilder(const FairDbProxy& proxy,
    const ValContext& vc,
    const FairDb::Task& task,
    Int_t selectDbNo     /* Default: -1 */,
    Bool_t findFullTimeWindow /* Default: true*/
                                                  )
  : fGap(),
    fIsExtendedContext(kFALSE),
    fTask(task),
    fVRecs(),
    fAggNoToIndex()
{

  Detector::Detector_t     det(vc.GetDetector());
  SimFlag::SimFlag_t       sim(vc.GetSimFlag());
  ValTimeStamp             ts(vc.GetTimeStamp());
  SimFlag::SimFlag_t       simTry(sim);
  const string& tableName = proxy.GetTableName();
  Int_t sumTimeWindows = 0;
  Int_t numTimeWindows = 0;


  this->MakeGapRec(vc, tableName, findFullTimeWindow);

//  Force aggregate -1 into first slot.
  this->AddNewGap(-1);

  const ValTimeStamp curVTS = vc.GetTimeStamp();

// Check to see if table exists.

  unsigned int numVRecIn = 0;

  if ( ! proxy.TableExists() ) {

    cout     << "FairDbValidityRecBuilder::Query for table:"
             << proxy.GetTableName()
             << ", table does not exist!" << endl;
  }

  else {

//  Loop over all databases in cascade until valid data found.

    UInt_t numDb     = proxy.GetNumDb();
    Bool_t foundData = kFALSE;

    for ( UInt_t dbNo = 0; dbNo < numDb && ! foundData; ++dbNo ) {

      // Skip if cascade entry does not have this table or selection in force and not the required one.
      if ( ! proxy.TableExists(dbNo) ) { continue; }
      if ( selectDbNo >= 0 && selectDbNo != (int) dbNo ) { continue; }

//    Loop over all associated SimFlags.

      FairDbSimFlagAssociation::SimList_t simList
      = FairDbSimFlagAssociation::Instance().Get(sim);

      FairDbSimFlagAssociation::SimList_t::iterator listItr    = simList.begin();
      FairDbSimFlagAssociation::SimList_t::iterator listItrEnd = simList.end();
      while ( listItr !=  listItrEnd && ! foundData ) {

        simTry = *listItr;
        ++listItr;
        ValContext vcTry(det,simTry,ts);

//      Apply validity query and build result set.

        FairDbResultSet* rs = proxy.QueryValidity(vcTry,fTask,dbNo);

//      Build a result from the result set and drop result set.

        FairDbValidityRec tr;
        FairDbResultNonAgg result(rs,&tr,0,kFALSE);
        delete rs;

//      Loop over all entries in FairDbResult and, for each Aggregate,
//      find effective validity range of best, or of gap if none.

//      Set earliest creation date to infinite past - the right value if in a gap.
        ValTimeStamp earliestCreate(0);
        UInt_t numRows = result.GetNumRows();
        for (UInt_t row = 0; row < numRows; ++row) {
          const FairDbValidityRec* vr = dynamic_cast<const FairDbValidityRec*>(
                                          result.GetTableRow(row));

          Int_t aggNo = vr->GetAggregateNo();

//        If starting a new aggregate prime it as a gap.
          Int_t index = this->IndexOfAggno(aggNo);
          if ( index < 0 ) { index = this->AddNewGap(aggNo); }

//        Trim the validity record for the current aggregate
//        number by this record and see if we have found valid
//        data yet.

          FairDbValidityRec& curRec = fVRecs[index];
          curRec.Trim(curVTS, *vr);
          if ( ! curRec.IsGap() ) {
            foundData = kTRUE;

//          Fill in entry's database number - its not stored in the
//          database table!
            curRec.SetDbNo(dbNo);
          }

//        Find the earliest non-gap creation date that is used
          if (     curRec.GetSeqNo() ==   vr->GetSeqNo()
                   &&  (    earliestCreate > vr->GetCreationDate()
                            || earliestCreate.GetSec() == 0 )
             ) { earliestCreate = vr->GetCreationDate(); }

//        Count the number used and sum the time windows
          ++numVRecIn;
          const ValRange range = vr->GetValRange();
          Int_t timeInterval =   range.GetTimeEnd().GetSec()
                                 - range.GetTimeStart().GetSec();
          if ( timeInterval < 5 ) {

            cout  << "Detected suspiciously small validity time interval in \n"
                  << "table " << tableName << " validity rec " << *vr << endl;
          }
          sumTimeWindows += timeInterval;
          ++numTimeWindows;
        }

//      If finding findFullTimeWindow then find bounding limits
//      for the cascade and sim flag and trim all validity records
//      and the default (gap) validity record.
        if ( findFullTimeWindow ) {
          ValTimeStamp start, end;
          proxy.FindTimeBoundaries(vcTry,fTask,dbNo,earliestCreate,start,end);
          cout  << "Trimming validity records to "
                << start << " .. " << end << endl;
          std::vector<FairDbValidityRec>::iterator itr(fVRecs.begin()), itrEnd(fVRecs.end());
          for( ; itr != itrEnd; ++itr ) { itr->AndTimeWindow(start,end); }
          fGap.AndTimeWindow(start,end);
        }
      }

    }
  }

//  If the query found no records in any database then
//  the tables will still have something - the aggno = -1 gap

// If the associated SimFlag is different to the original request make
// sure that all the FairDbValidityRec are valid for the request.
  if ( sim != simTry ) {
    cout << "Imposing SimFlag of " << sim << " on FairDbValidityRecs which matched " << simTry << endl;
    for ( unsigned int irec = 0; irec < GetNumValidityRec(); ++irec ) {
      FairDbValidityRec& vrec = const_cast<FairDbValidityRec&>(GetValidityRec(irec));
      const ValRange& vr(vrec.GetValRange());
      ValRange vr_mod(vr.GetDetectorMask(),sim,vr.GetTimeStart(),vr.GetTimeEnd(),vr.GetDataSource());
      vrec.SetValRange(vr_mod);
    }
  }

  cout << "FairDbValidityRecBuilder:" << endl
       << " Query: " << vc.AsString() << endl
       << " using associated SimFlag: " << SimFlag::AsString(simTry)
       << " for " << SimFlag::AsString(sim)
       << " found " << numVRecIn
       << " vrecs in database, for " << fVRecs.size()
       << " aggregates:-." << endl;

  for ( unsigned int irec = 0; irec < GetNumValidityRec(); ++irec ) {
    const FairDbValidityRec& vrec = GetValidityRec(irec);
    if ( vrec.GetAggregateNo() != -2 ) {
      cout << " " << irec << " " << GetValidityRec(irec) << endl;
    }
  }



// Adjust the time gate if grossly wrong.
  if ( numTimeWindows > 0 ) {
    Int_t timeGateCalc = 3 * fVRecs.size() * sumTimeWindows/numTimeWindows;
    // Limit to 100 days and allow for overflow.
    if ( timeGateCalc > 100*24*60*60 || timeGateCalc < 0
       ) { timeGateCalc = 100*24*60*60; }
    Int_t timeGateCurr = FairDb::GetTimeGate(tableName);
    if (    timeGateCurr < timeGateCalc/10
            || timeGateCurr > timeGateCalc*10
       ) {
      FairDb::SetTimeGate(tableName,timeGateCalc);
      if ( timeGateCalc != FairDb::GetTimeGate(tableName) ) {

        cout << "The ignored time gate setting was calculated with the following data:-"
             << "\n   Context: " << vc << " task " << task  << " findFullTimeWindow " << findFullTimeWindow
             << "\n   Number of vrecs " << numTimeWindows
             << " total time (secs) of all vrecs " << sumTimeWindows
             << " Number of aggregates " << fVRecs.size() << endl;
      }
    }
  }

  return;

}

FairDbValidityRecBuilder::FairDbValidityRecBuilder(const FairDbProxy& proxy,
    const string& context,
    const FairDb::Task& task)
  : fGap(),
    fIsExtendedContext(kTRUE),
    fTask(task),
    fVRecs(),
    fAggNoToIndex()
{

  cout << "Creating FairDbValidityRecBuilder"
       << " for extended context " << context << endl;

// Prime fVRecs with a gap that will not be used but makes the result
// look like an aggregated result.

  cout<< "Initialising with gap record " << fGap << endl;
  this->AddNewGap(-1);

// Check to see if table exists.

  unsigned int numVRecIn = 0;

  if ( ! proxy.TableExists() ) {
    cout << "FairDbValidityRecBuilder::Query for table:"
         << proxy.GetTableName()
         << ", table does not exist!" << endl;
  }

  else if ( context == "" ) {
    cout     << "FairDbValidityRecBuilder::Null query for table:"
             << proxy.GetTableName() << endl;
  }

  else {

//  Loop over all databases in cascade until valid data found.

    UInt_t numDb     = proxy.GetNumDb();
    Bool_t foundData = kFALSE;

    for ( UInt_t dbNo = 0; dbNo < numDb && ! foundData; ++dbNo ) {

//    Apply validity query and build result set.

      FairDbResultSet* rs = proxy.QueryValidity(context,fTask,dbNo);

//    Build a result from the result set and drop result set.

      FairDbValidityRec tr;
      FairDbResultNonAgg result(rs,&tr,0,kFALSE);
      delete rs;

//    Loop over all entries in FairDbResult and add them all to set.

      UInt_t numRows = result.GetNumRows();
      for (UInt_t row = 0; row < numRows; ++row) {
        const FairDbValidityRec* vr = dynamic_cast<const FairDbValidityRec*>(
                                        result.GetTableRow(row));

//      Cannot use AddNewAgg - aggregate numbers may be duplicated.
        Int_t index = fVRecs.size();
        fVRecs.push_back(FairDbValidityRec(*vr));
        fAggNoToIndex[vr->GetAggregateNo()] = index;
        foundData = kTRUE;

//      Fill in entry's database number - its not stored in the
//      database table!
        fVRecs[index].SetDbNo(dbNo);

//      Count the number used.
        ++numVRecIn;
      }
    }
  }

  cout << "FairDbValidityRecBuilder:" << endl
       << " Extended context query: " << context << endl
       << " found " << numVRecIn
       << " vrecs in database, for " << fVRecs.size()
       << " records:-." << endl;

  for ( unsigned int irec = 0; irec < GetNumValidityRec(); ++irec ) {
    cout << " " << irec << " " << GetValidityRec(irec) << endl;
  }
  return;



}

//.....................................................................

FairDbValidityRecBuilder::FairDbValidityRecBuilder(const FairDbValidityRec& vr,
    const std::string tableName)
  : fGap(),
    fIsExtendedContext(kFALSE),
    fTask(vr.GetTask()),
    fVRecs(),
    fAggNoToIndex()
{

  const ValRange&          vrange(vr.GetValRange());
  // This is the only way I can find to handle Detector and SimFlag!
  ValContext vc( (Detector::Detector_t) vrange.GetDetectorMask(),
                 (SimFlag::SimFlag_t) vrange.GetSimMask(),
                 vrange.GetTimeStart());
  this->MakeGapRec(vc,tableName);
  this->AddNewAgg(vr,vr.GetAggregateNo());

}
//.....................................................................

FairDbValidityRecBuilder::~FairDbValidityRecBuilder()
{

}


std::string FairDbValidityRecBuilder::GetL2CacheName() const
{
  if ( this->IsExtendedContext() ) { return ""; }

  UInt_t seqLo = 0;
  UInt_t seqHi = 0;
  ValTimeStamp ts;
  std::vector<FairDbValidityRec>::const_iterator itr = fVRecs.begin();
  std::vector<FairDbValidityRec>::const_iterator end = fVRecs.end();

  for (; itr != end; ++itr) {
    const FairDbValidityRec& vr = *itr;
    if ( ! vr.IsGap() ) {
      if ( seqLo == 0 ) {
        seqLo = vr.GetSeqNo();
        seqHi = vr.GetSeqNo();
        ts    = vr.GetCreationDate();
      } else {
        if ( seqLo < vr.GetSeqNo() ) { seqLo = vr.GetSeqNo(); }
        if ( seqHi > vr.GetSeqNo() ) { seqHi = vr.GetSeqNo(); }
        if ( ts    < vr.GetCreationDate() ) { ts    = vr.GetCreationDate(); }
      }
    }
  }

  if ( seqLo == 0 ) { return ""; }

  return FairDbValidityRec::GetL2CacheName(seqLo,seqHi,ts);

}

//.....................................................................

UInt_t FairDbValidityRecBuilder::AddNewAgg(const FairDbValidityRec& vrec,Int_t aggNo)
{

  //  Make sure it really doesn't exist.
  int index = this->IndexOfAggno(aggNo);
  if ( index >=0 ) { return index; }

  // It doesn't so add it.
  index = fVRecs.size();
  fVRecs.push_back(vrec);
  fAggNoToIndex[aggNo] = index;
  return index;

}

//.....................................................................

UInt_t FairDbValidityRecBuilder::AddNewGap(Int_t aggNo)
{

  UInt_t index = this->AddNewAgg(fGap,aggNo);
  fVRecs[index].SetAggregateNo(aggNo);
  return index;

}

//.....................................................................

const FairDbValidityRec&
FairDbValidityRecBuilder::GetValidityRec(Int_t rowNo) const
{

  return (rowNo < 0 || rowNo >= (int) fVRecs.size()) ? fGap : fVRecs[rowNo];
}

//.....................................................................

const FairDbValidityRec&
FairDbValidityRecBuilder::GetValidityRecFromSeqNo(UInt_t SeqNo) const
{

  std::vector<FairDbValidityRec>::const_iterator itr = fVRecs.begin();
  std::vector<FairDbValidityRec>::const_iterator end = fVRecs.end();

  for (; itr != end; ++itr) if ( itr->GetSeqNo() == SeqNo ) { return *itr; }
  return fGap;
}

//.....................................................................

Int_t FairDbValidityRecBuilder::IndexOfAggno(Int_t aggNo) const
{
  std::map<Int_t,UInt_t>::const_iterator itr = fAggNoToIndex.find(aggNo);
  if ( itr == fAggNoToIndex.end() ) { return -1; }
  return itr->second;

}

//.....................................................................

void FairDbValidityRecBuilder::MakeGapRec(const ValContext& vc,
    const string& tableName,
    Bool_t findFullTimeWindow)
{

  Int_t timeGate = FairDb::GetTimeGate(tableName);
  time_t contextSec = vc.GetTimeStamp().GetSec() - timeGate;
  ValTimeStamp startGate(contextSec,0);
  contextSec += 2*timeGate;
  ValTimeStamp endGate(contextSec,0);
  if ( findFullTimeWindow ) {
    startGate = ValTimeStamp(0,0);
    endGate   = ValTimeStamp(0x7FFFFFFF,0);
  }
  ValRange gapVR(vc.GetDetector(), vc.GetSimFlag(), startGate, endGate, "Gap");
  fGap =  FairDbValidityRec(gapVR, fTask, -2, 0, 0, kTRUE);

}


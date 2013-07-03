#include "FairDbValidityRecBuilder.h"
#include "FairDbLogService.h"
#include "FairDbProxy.h"                // for FairDbProxy
#include "FairDbResult.h"               // for FairDbResultNonAgg, etc
#include "FairDbSimFlagAssociation.h"   // for FairDbSimFlagAssociation, etc
#include "FairDbTableRow.h"             // for FairDbTableRow
#include "FairDbValidityRec.h"          // for FairDbValidityRec, etc
#include "SimFlag.h"                    // for AsString, SimFlag_t
#include "ValContext.h"                 // for ValContext, operator<<
#include "ValRange.h"                   // for ValRange
#include "ValTimeStamp.h"               // for ValTimeStamp, operator<<, etc
#include "db_detector_def.h"            // for Detector, etc

#include "Riosfwd.h"                    // for ostream

#include <sys/select.h>                 // for time_t
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <list>                         // for _List_iterator, etc
#include <utility>                      // for pair

using std::cout;
using std::endl;
using std::string;

ClassImp(FairDbValidityRecBuilder)

FairDbValidityRecBuilder::FairDbValidityRecBuilder(const FairDbProxy& proxy,
    const ValContext& vc,
    const FairDb::Version& task,
    Int_t selectDbNo,
    Bool_t findFullTimeWindow
                                                  )
  : fGap(),
    fIsExtendedContext(kFALSE),
    fVersion(task),
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

  this->AddNewGap(-1);

  const ValTimeStamp curVTS = vc.GetTimeStamp();


  unsigned int numVRecIn = 0;

  if ( ! proxy.TableExists() ) {

    DBLOG("FairDb",FairDbLog::kInfo) << "FairDbValidityRecBuilder::Query for table:"
                                     << proxy.GetTableName()
                                     << ", table does not exist!" << endl;
  }

  else {

//  Loop over all databases
    UInt_t numDb     = proxy.GetNumDb();
    Bool_t foundData = kFALSE;

    for ( UInt_t dbNo = 0; dbNo < numDb && ! foundData; ++dbNo ) {

      if ( ! proxy.TableExists(dbNo) ) { continue; }
      if ( selectDbNo >= 0 && selectDbNo != (int) dbNo ) { continue; }

      FairDbSimFlagAssociation::SimList_t simList
      = FairDbSimFlagAssociation::Instance().Get(sim);

      FairDbSimFlagAssociation::SimList_t::iterator listItr    = simList.begin();
      FairDbSimFlagAssociation::SimList_t::iterator listItrEnd = simList.end();
      while ( listItr !=  listItrEnd && ! foundData ) {

        simTry = *listItr;
        ++listItr;
        ValContext vcTry(det,simTry,ts);


        FairDbResultSet* rs = proxy.QueryValidity(vcTry,fVersion,dbNo);

        FairDbValidityRec tr;
        FairDbResultNonAgg result(rs,&tr,0,kFALSE);
        delete rs;

        ValTimeStamp earliestCreate(0);
        UInt_t numRows = result.GetNumRows();
        for (UInt_t row = 0; row < numRows; ++row) {
          const FairDbValidityRec* vr = dynamic_cast<const FairDbValidityRec*>(
                                          result.GetTableRow(row));

          Int_t aggNo = vr->GetAggregateNo();
          Int_t index = this->IndexOfAggno(aggNo);
          if ( index < 0 ) { index = this->AddNewGap(aggNo); }


          FairDbValidityRec& curRec = fVRecs[index];
          curRec.Trim(curVTS, *vr);
          if ( ! curRec.IsGap() ) {
            foundData = kTRUE;
            curRec.SetDbNo(dbNo);
          }

          if (     curRec.GetSeqNo() ==   vr->GetSeqNo()
                   &&  (    earliestCreate > vr->GetCreationDate()
                            || earliestCreate.GetSec() == 0 )
             ) { earliestCreate = vr->GetCreationDate(); }

          ++numVRecIn;
          const ValRange range = vr->GetValRange();
          Int_t timeInterval =   range.GetTimeEnd().GetSec()
                                 - range.GetTimeStart().GetSec();
          if ( timeInterval < 5 ) {

            DBLOG("FairDb",FairDbLog::kWarning) << "Detected suspiciously small validity time interval in \n"
                                                << "table " << tableName << " validity rec " << *vr << endl;
          }
          sumTimeWindows += timeInterval;
          ++numTimeWindows;
        }

        if ( findFullTimeWindow ) {
          ValTimeStamp start, end;
          proxy.FindTimeBoundaries(vcTry,fVersion,dbNo,earliestCreate,start,end);
          DBLOG("FairDb",FairDbLog::kInfo) << "Trimming validity records to "
                                           << start << " .. " << end << endl;
          std::vector<FairDbValidityRec>::iterator itr(fVRecs.begin()), itrEnd(fVRecs.end());
          for( ; itr != itrEnd; ++itr ) { itr->AndTimeWindow(start,end); }
          fGap.AndTimeWindow(start,end);
        }
      }

    }
  }

  if ( sim != simTry ) {
    DBLOG("FairDb",FairDbLog::kInfo) << "Imposing SimFlag of " << sim << " on FairDbValidityRecs which matched " << simTry << endl;
    for ( unsigned int irec = 0; irec < GetNumValidityRec(); ++irec ) {
      FairDbValidityRec& vrec = const_cast<FairDbValidityRec&>(GetValidityRec(irec));
      const ValRange& vr(vrec.GetValRange());
      ValRange vr_mod(vr.GetDetectorMask(),sim,vr.GetTimeStart(),vr.GetTimeEnd(),vr.GetDataSource());
      vrec.SetValRange(vr_mod);
    }
  }

  DBLOG("FairDb",FairDbLog::kInfo)  << "FairDbValidityRecBuilder:" << endl
                                    << " Query: " << vc.AsString() << endl
                                    << " using associated SimFlag: " << SimFlag::AsString(simTry)
                                    << " for " << SimFlag::AsString(sim)
                                    << " found " << numVRecIn
                                    << " vrecs in database, for " << fVRecs.size()
                                    << " composites:-." << endl;

  for ( unsigned int irec = 0; irec < GetNumValidityRec(); ++irec ) {
    const FairDbValidityRec& vrec = GetValidityRec(irec);
    if ( vrec.GetAggregateNo() != -2 ) {
      DBLOG("FairDb",FairDbLog::kInfo) << " " << irec << " " << GetValidityRec(irec) << endl;
    }
  }


  if ( numTimeWindows > 0 ) {
    Int_t timeGateCalc = 3 * fVRecs.size() * sumTimeWindows/numTimeWindows;
    if ( timeGateCalc > 100*24*60*60 || timeGateCalc < 0
       ) { timeGateCalc = 100*24*60*60; }
    Int_t timeGateCurr = FairDb::GetTimeGate(tableName);
    if (    timeGateCurr < timeGateCalc/10
            || timeGateCurr > timeGateCalc*10
       ) {
      FairDb::SetTimeGate(tableName,timeGateCalc);
      if ( timeGateCalc != FairDb::GetTimeGate(tableName) ) {

        DBLOG("FairDb",FairDbLog::kInfo) << "The ignored time gate setting was calculated with the following data:-"
                                         << "\n   Context: " << vc << " task " << task  << " findFullTimeWindow " << findFullTimeWindow
                                         << "\n   Number of vrecs " << numTimeWindows
                                         << " total time (secs) of all vrecs " << sumTimeWindows
                                         << " Number of composites " << fVRecs.size() << endl;
      }
    }
  }

  return;

}

FairDbValidityRecBuilder::FairDbValidityRecBuilder(const FairDbProxy& proxy,
    const string& context,
    const FairDb::Version& task)
  : fGap(),
    fIsExtendedContext(kTRUE),
    fVersion(task),
    fVRecs(),
    fAggNoToIndex()
{

  DBLOG("FairDb",FairDbLog::kInfo) << "Creating FairDbValidityRecBuilder"
                                   << " for extended context " << context << endl;

  DBLOG("FairDb",FairDbLog::kInfo) << "Initialising with gap record " << fGap << endl;
  this->AddNewGap(-1);

  unsigned int numVRecIn = 0;

  if ( ! proxy.TableExists() ) {
    DBLOG("FairDb",FairDbLog::kInfo)
        << "FairDbValidityRecBuilder::Query for table:"
        << proxy.GetTableName()
        << ", table does not exist!" << endl;
  }

  else if ( context == "" ) {
    DBLOG("FairDb",FairDbLog::kInfo)      << "FairDbValidityRecBuilder::Null query for table:"
                                          << proxy.GetTableName() << endl;
  }

  else {

//  Loop over all databases
    UInt_t numDb     = proxy.GetNumDb();
    Bool_t foundData = kFALSE;

    for ( UInt_t dbNo = 0; dbNo < numDb && ! foundData; ++dbNo ) {
      FairDbResultSet* rs = proxy.QueryValidity(context,fVersion,dbNo);

      FairDbValidityRec tr;
      FairDbResultNonAgg result(rs,&tr,0,kFALSE);
      delete rs;

      UInt_t numRows = result.GetNumRows();
      for (UInt_t row = 0; row < numRows; ++row) {
        const FairDbValidityRec* vr = dynamic_cast<const FairDbValidityRec*>(
                                        result.GetTableRow(row));
        Int_t index = fVRecs.size();
        fVRecs.push_back(FairDbValidityRec(*vr));
        fAggNoToIndex[vr->GetAggregateNo()] = index;
        foundData = kTRUE;

        fVRecs[index].SetDbNo(dbNo);

        ++numVRecIn;
      }
    }
  }

  DBLOG("FairDb",FairDbLog::kInfo) << "FairDbValidityRecBuilder:" << endl
                                   << " Extended context query: " << context << endl
                                   << " found " << numVRecIn
                                   << " vrecs in database, for " << fVRecs.size()
                                   << " records:-." << endl;

  for ( unsigned int irec = 0; irec < GetNumValidityRec(); ++irec ) {
    DBLOG("FairDb",FairDbLog::kInfo) << " " << irec << " " << GetValidityRec(irec) << endl;
  }
  return;



}

//.....................................................................

FairDbValidityRecBuilder::FairDbValidityRecBuilder(const FairDbValidityRec& vr,
    const std::string tableName)
  : fGap(),
    fIsExtendedContext(kFALSE),
    fVersion(vr.GetVersion()),
    fVRecs(),
    fAggNoToIndex()
{

  const ValRange&          vrange(vr.GetValRange());

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



UInt_t FairDbValidityRecBuilder::AddNewAgg(const FairDbValidityRec& vrec,Int_t aggNo)
{

  int index = this->IndexOfAggno(aggNo);
  if ( index >=0 ) { return index; }

  index = fVRecs.size();
  fVRecs.push_back(vrec);
  fAggNoToIndex[aggNo] = index;
  return index;

}



UInt_t FairDbValidityRecBuilder::AddNewGap(Int_t aggNo)
{
  UInt_t index = this->AddNewAgg(fGap,aggNo);
  fVRecs[index].SetAggregateNo(aggNo);
  return index;
}



const FairDbValidityRec&
FairDbValidityRecBuilder::GetValidityRec(Int_t rowNo) const
{

  return (rowNo < 0 || rowNo >= (int) fVRecs.size()) ? fGap : fVRecs[rowNo];
}



const FairDbValidityRec&
FairDbValidityRecBuilder::GetValidityRecFromSeqNo(UInt_t SeqNo) const
{

  std::vector<FairDbValidityRec>::const_iterator itr = fVRecs.begin();
  std::vector<FairDbValidityRec>::const_iterator end = fVRecs.end();

  for (; itr != end; ++itr) if ( itr->GetSeqNo() == SeqNo ) { return *itr; }
  return fGap;
}


Int_t FairDbValidityRecBuilder::IndexOfAggno(Int_t aggNo) const
{
  std::map<Int_t,UInt_t>::const_iterator itr = fAggNoToIndex.find(aggNo);
  if ( itr == fAggNoToIndex.end() ) { return -1; }
  return itr->second;

}


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
  fGap =  FairDbValidityRec(gapVR, fVersion, -2, 0, 0, kTRUE);

}


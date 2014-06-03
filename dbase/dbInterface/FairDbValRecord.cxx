/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairDbValRecord.h"
#include "FairDbLogService.h"
#include "FairDbBufferFile.h"           // for FairDbBufferFile
#include "FairDbOutTableBuffer.h"         // for FairDbOutTableBuffer
#include "FairDbReader.h"               // for string, FairDbReader
#include "FairDbResult.h"               // for FairDbResultPool
#include "ValCondition.h"                 // for ValCondition
#include "ValInterval.h"                   // for ValInterval
#include "ValTimeStamp.h"               // for ValTimeStamp, operator>, etc

#include "TString.h"                    // for operator<<

#include <iostream>                     // for operator<<, basic_ostream, etc

using std::ostringstream;
using std::hex;

ClassImp(FairDbValRecord)


#include "FairDbReader.tpl"
template class  FairDbReader<FairDbValRecord>;


ostream& operator<<(ostream& os, const FairDbValRecord& vRec)
{

  const ValInterval&           range(vRec.GetValInterval());

  ostringstream os2;
  os2 << "-I- FairDbValRecord:: SeqNo: " << vRec.GetSeqNo()
      << "  ComboNo: " << vRec.GetAggregateNo()
      << "  DbId: " << vRec.GetDbNo();
  if ( vRec.IsGap() ) { os2 << " (gap)"; }
  os2  << "  ValInterval: |"
       << hex  << "0x"  << range.GetDetectorMask() << "|"
       << "0x" << range.GetSimMask() << "|"
       << " " << range.GetTimeStart().AsString("s") << " .. "
       << range.GetTimeEnd().AsString("s")
       << " from: " << range.GetDataSource();
  os << os2.str();
  return os;

}


void FairDbValRecord::AndTimeWindow(const ValTimeStamp& startOther,
                                    const ValTimeStamp& endOther)
{

  ValTimeStamp start = fValInterval.GetTimeStart();
  ValTimeStamp end   = fValInterval.GetTimeEnd();

  SetTimeWindow( start > startOther ? start : startOther,
                 end   < endOther   ? end   : endOther );
}



FairDbValRecord::FairDbValRecord(Int_t dbNo,Bool_t isGap)
  : FairDbObjTableMap(),
    fAggregateNo(-2),
    fCreationDate(),
    fDbNo(dbNo),
    fInsertDate(),
    fIsGap(isGap),
    fVersion(0),
    fSeqNo(0),
    fTableInterface(0),
    fValInterval()
{
}


FairDbValRecord::FairDbValRecord(const FairDbValRecord& from)
  : FairDbObjTableMap(from),
    fAggregateNo(from.fAggregateNo),
    fCreationDate(from.fCreationDate),
    fDbNo(from.fDbNo),
    fInsertDate(from.fInsertDate),
    fIsGap(from.fIsGap),
    fVersion(from.fVersion),
    fSeqNo(from.fSeqNo),
    fTableInterface(from.fTableInterface),
    fValInterval(from.fValInterval)

{
  *this = from;
}


FairDbValRecord::FairDbValRecord(const ValInterval& range,
                                 FairDb::Version task,
                                 Int_t aggNo,
                                 UInt_t seqNo,
                                 Int_t dbNo,
                                 Bool_t isGap,
                                 ValTimeStamp time) :
  fAggregateNo(aggNo),
  fCreationDate(time),
  fDbNo(dbNo),
  fInsertDate(),
  fIsGap(isGap),
  fVersion(task),
  fSeqNo(seqNo),
  fTableInterface(0),
  fValInterval(range)
{

}


FairDbValRecord& FairDbValRecord::operator=(const FairDbValRecord& from)
{
  if (this == &from) { return *this; }

  FairDbObjTableMap::operator=(from);
  fAggregateNo=from.fAggregateNo;
  fCreationDate=from.fCreationDate;
  fDbNo=from.fDbNo;
  fInsertDate=from.fInsertDate;
  fIsGap=from.fIsGap;
  fVersion=from.fVersion;
  fSeqNo=from.fSeqNo;
  fTableInterface=from.fTableInterface;
  fValInterval=from.fValInterval;

  return *this;
}



FairDbValRecord::~FairDbValRecord()
{

}


void FairDbValRecord::Fill(FairDbResultPool& rs,
                           const FairDbValRecord* /* vrec */)
{

  ValTimeStamp start, end;
  Int_t detMask, simMask;


  fTableInterface = rs.GetTableInterface();
  fDbNo       = rs.GetDbNo();


  rs >> fSeqNo >> start >> end >> detMask >> simMask >> fVersion
     >> fAggregateNo    >> fCreationDate  >> fInsertDate;

  fIsGap = kFALSE;

  ValInterval vr(detMask, simMask, start, end, "Added Conditions:");
  fValInterval = vr;

  DBLOG("FairDb",FairDbLog::kInfo)
      << "FairDbValRecordord for row: " << rs.CurRowNum()
      << ": " << fValInterval.AsString()
      << " seq_id: " << fSeqNo
      << " combo_id: "  << fAggregateNo
      << " version_id: " << fVersion <<  endl;
}


std::string FairDbValRecord::GetCacheName() const
{
  return FairDbValRecord::GetCacheName(this->GetSeqNo(),
                                       this->GetSeqNo(),
                                       this->GetCreationDate());

}

std::string FairDbValRecord::GetCacheName(UInt_t seqLo,
    UInt_t seqHi,
    ValTimeStamp ts)
{

  ostringstream oss;
  oss << seqLo << "_";
  if ( seqLo != seqHi ) { oss << seqHi << "_"; }
  oss << ts.AsString("s");
  std::string str(oss.str());
  int i = str.size();
  while ( i-- ) if ( str[i] == ' ' ) { str[i] = '_'; }
  return str;

}


Bool_t FairDbValRecord::HasExpired(const FairDbValRecord& other) const
{

  const ValInterval& otherVR =other.GetValInterval();

  return
    (       other.GetVersion() == fVersion
            && ( otherVR.GetDetectorMask() & fValInterval.GetDetectorMask() )
            && ( otherVR.GetSimMask()      & fValInterval.GetSimMask() )
            && (    otherVR.GetTimeStart() >= fValInterval.GetTimeEnd()
                    || otherVR.GetTimeEnd()   <= fValInterval.GetTimeStart() )
    );

}


Bool_t FairDbValRecord::HasExpired(const ValCondition& vc,
                                   const FairDb::Version& task) const
{

  ValTimeStamp    ts = vc.GetTimeStamp();
  const ValInterval& vr = this->GetValInterval();

  return
    (       task             == this->GetVersion()
            && ( vc.GetDetector() &  vr.GetDetectorMask() )
            && ( vc.GetDataType()  &  vr.GetSimMask() )
            && (    ts            >= vr.GetTimeEnd()
                    || ts            <  vr.GetTimeStart() )
    );

}



Bool_t FairDbValRecord::IsCompatible(const ValCondition& vc,
                                     const FairDb::Version& task) const
{

  DBLOG("FairDb",FairDbLog::kInfo) << " FairDbValRecord::IsCompatible? -> Version:"
                                   << task << "," << fVersion
                                   << " Compatible: " << fValInterval.IsCompatible(vc) << endl
                                   << " Interval: " << fValInterval.AsString() << endl
                                   << " Context: " << vc.AsString() << endl;

  return task == fVersion  && fValInterval.IsCompatible(vc);

}

void FairDbValRecord::SetTimeWindow(const ValTimeStamp& start,
                                    const ValTimeStamp& end)
{
  ValInterval  range(fValInterval.GetDetectorMask(),
                     fValInterval.GetSimMask(),
                     start,
                     end,
                     fValInterval.GetDataSource() );
  fValInterval = range;

}


void FairDbValRecord::Store(FairDbOutTableBuffer& ors,
                            const FairDbValRecord* /* vrec */) const
{

  ors << fSeqNo
      << fValInterval.GetTimeStart()
      << fValInterval.GetTimeEnd()
      << fValInterval.GetDetectorMask()
      << fValInterval.GetSimMask()
      << fVersion
      << fAggregateNo
      << fCreationDate
      << fInsertDate;
}

void FairDbValRecord::Streamer(FairDbBufferFile& file)
{

  if ( file.IsReading() ) {
    file >> fAggregateNo
         >> fCreationDate
         >> fDbNo
         >> fInsertDate
         >> fIsGap
         >> fVersion
         >> fSeqNo
         >> fValInterval;
    fTableInterface = 0;
  } else if ( file.IsWriting() ) {
    file << fAggregateNo
         << fCreationDate
         << fDbNo
         << fInsertDate
         << fIsGap
         << fVersion
         << fSeqNo
         << fValInterval;
  }
}


void FairDbValRecord::Trim(const ValTimeStamp& queryTime,
                           const FairDbValRecord& other)
{

  if ( fAggregateNo != other.fAggregateNo || other.IsGap() ) { return; }

  if ( ! IsGap() ) { return; }

  ValTimeStamp start      = fValInterval.GetTimeStart();
  ValTimeStamp end        = fValInterval.GetTimeEnd();
  ValTimeStamp startOther = other.GetValInterval().GetTimeStart();
  ValTimeStamp endOther   = other.GetValInterval().GetTimeEnd();

  if ( startOther <= queryTime && endOther > queryTime ) {
    if ( start < startOther ) { start = startOther; }
    if ( end   > endOther   ) { end   = endOther; }
    *this = other;
    SetTimeWindow(start,end);
  }

  else {

    if ( endOther <= queryTime ) {
      if ( start < endOther   ) { SetTimeWindow(endOther,end); }
    } else if ( startOther > queryTime ) {
      if ( end   > startOther ) { SetTimeWindow(start, startOther); }
    }
  }

}


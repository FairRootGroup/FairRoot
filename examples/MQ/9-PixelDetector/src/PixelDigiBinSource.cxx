/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//
//  PixelDigiBinSource.cxx
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//
#include "PixelDigiBinSource.h"
#include "PixelDigi.h"
#include "PixelEventHeader.h"

#include "FairLogger.h"
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairRootManager.h"

#include "TClonesArray.h"
#include "TString.h"

using std::map;
using std::set;


//_____________________________________________________________________________
PixelDigiBinSource::PixelDigiBinSource(TString inputFileName)
  : FairSource()
  , fEventHeader(NULL)
  , fDigis(NULL)
  , fNDigis(0)
  , fTNofEvents(0)
  , fTNofDigis(0)
  , fInputFileName(inputFileName)
  , fInputFile()
  , fCurrentEntryNo(0)
  , fRunId(0)
  , fMCEntryNo(0)
  , fPartNo(0)
{
  LOG(DEBUG) << "PixelDigiBinSource created------------" << FairLogger::endl;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
PixelDigiBinSource::~PixelDigiBinSource()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t PixelDigiBinSource::Init()
{

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();

  LOG(INFO) << "PixelDigiBinSource::Init" << FairLogger::endl;
  if ( ! ioman ) LOG(FATAL) << "No FairRootManager" << FairLogger::endl;

  // Register output array StsDigi
  fDigis = new TClonesArray("PixelDigi",10000);
  ioman->Register("PixelDigis", "Pixel", fDigis, kFALSE);

  fEventHeader = new PixelEventHeader();
  fEventHeader->SetName("EventHeader.");
  ioman->Register("EventHeader.","EvtHeader", fEventHeader, kFALSE);

  fInputFile.open(fInputFileName.Data(),std::fstream::in|std::fstream::binary);
  
  if ( !fInputFile.is_open() ) {
    LOG(FATAL) << "PixelDigiBinSource::Init() fInputFile \"" << fInputFileName.Data() << "\" could not be open!" << FairLogger::endl;
    return kFALSE;
  }

  return kTRUE;
   
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t PixelDigiBinSource::ReadEvent(UInt_t i)
{
  if (fDigis) fDigis->Clear();
  fNDigis = 0;

  if ( !fInputFile ) {
    return 1;
  }

  if ( i == 0 ) { 
    fInputFile.clear();
    fInputFile.seekg(0, std::ios::beg);
  }

  fCurrentEntryNo = i;

  std::string buffer;
  LOG(DEBUG) << "PixelDigiBinSource::ReadEvent() Begin of (" << fDigis->GetEntries() << ")" << FairLogger::endl;

  Int_t head[4]; // runId, MCEntryNo, PartNo, NofDigis
  fInputFile.read((char*)head,sizeof(head));

  if ( fInputFile.eof() ) {
    LOG(INFO) << "End of file reached!" << FairLogger::endl;
    return 1;
  }
  
  Int_t dataSize = 4; // detId, feId, col, row
  
  const Int_t constNofData = head[3]*dataSize;
  short int dataCont[constNofData];
  fInputFile.read((char*)dataCont,sizeof(dataCont));
  
  fRunId     = head[0];
  fMCEntryNo = head[1];
  fPartNo    = head[2];
  fEventHeader->SetRunId(fRunId);
  fEventHeader->SetMCEntryNumber(fMCEntryNo);
  fEventHeader->SetPartNo(fPartNo);

  for ( Int_t idata = 0 ; idata < head[3] ; idata++ ) {
    LOG(DEBUG) << "    --/" << idata << "/-->    " 
	       << dataCont[idata*dataSize+0] << " / " 
	       << dataCont[idata*dataSize+1] << " / " 
	       << dataCont[idata*dataSize+2] << " / " 
	       << dataCont[idata*dataSize+3] << " / " 
	       << " 0." << FairLogger::endl;
    new ((*fDigis)[fNDigis]) PixelDigi(-1,
				       (Int_t)dataCont[idata*dataSize+0],
				       (Int_t)dataCont[idata*dataSize+1],
				       (Int_t)dataCont[idata*dataSize+2],
				       (Int_t)dataCont[idata*dataSize+3],
				       0.,0.);
    fNDigis++;
  }
  LOG(DEBUG) << "PixelDigiBinSource::ReadEvent() End of" << FairLogger::endl;
  
  if ( !fInputFile ) {
    return 1;
  }
  
  return 0;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t   PixelDigiBinSource::ActivateObject(TObject** obj, const char* BrName) {
  if ( strcmp(BrName,"PixelDigis") ) 
    *obj = (TObject*)fDigis; 
  else if ( strcmp(BrName,"EventHeader.") )
    *obj = (TObject*)fEventHeader;
  else
    return kFALSE;
  
  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void PixelDigiBinSource::Close()
{
  fInputFile.close();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void PixelDigiBinSource::Reset()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t  PixelDigiBinSource::CheckMaxEventNo(Int_t /*EvtEnd*/)
{
  return -1;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void PixelDigiBinSource::FillEventHeader(FairEventHeader* feh) 
{
  ((PixelEventHeader*)feh)->SetRunId(fRunId);
  ((PixelEventHeader*)feh)->SetMCEntryNumber(fMCEntryNo);
  ((PixelEventHeader*)feh)->SetPartNo(fPartNo);
}
//_____________________________________________________________________________

ClassImp(PixelDigiBinSource)


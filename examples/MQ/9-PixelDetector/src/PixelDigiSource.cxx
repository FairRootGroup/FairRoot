/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//
//  PixelDigiSource.cxx
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//
#include "PixelDigiSource.h"
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
PixelDigiSource::PixelDigiSource(TString inputFileName)
  : FairSource()
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
  LOG(DEBUG) << "PixelDigiSource created------------" << FairLogger::endl;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
PixelDigiSource::~PixelDigiSource()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t PixelDigiSource::Init()
{

  // Get input array 
  FairRootManager* ioman = FairRootManager::Instance();

  LOG(INFO) << "PixelDigiSource::Init" << FairLogger::endl;
  if ( ! ioman ) LOG(FATAL) << "No FairRootManager" << FairLogger::endl;

  // Register output array StsDigi
  fDigis = new TClonesArray("PixelDigi",10000);
  ioman->Register("PixelDigis", "Pixel", fDigis, kTRUE);

  fInputFile.open(fInputFileName.Data(),std::fstream::in);
  
  if ( !fInputFile.is_open() ) {
    LOG(FATAL) << "PixelDigiSource::Init() fInputFile \"" << fInputFileName.Data() << "\" could not be open!" << FairLogger::endl;
    return kFALSE;
  }

  return kTRUE;
   
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t PixelDigiSource::InitMQ()
{

  // Get input array 
  // Register output array StsDigi
  fDigis = new TClonesArray("PixelDigi",10000);
  fDigis->SetName("PixelDigis");

  fInputFile.open(fInputFileName.Data(),std::fstream::in);
  
  if ( !fInputFile.is_open() ) {
    LOG(FATAL) << "PixelDigiSource::Init() fInputFile \"" << fInputFileName.Data() << "\" could not be open!" << FairLogger::endl;
    return kFALSE;
  }

  return kTRUE;
   
}
//_____________________________________________________________________________

//_____________________________________________________________________________
int ReadIntFromString(std::string wholestr, std::string pattern) {
  std::string tempstr = wholestr;
  tempstr.replace(0,tempstr.find(pattern)+pattern.length(),"");
  tempstr.replace(0,tempstr.find('=')+1,"");
  return atoi(tempstr.c_str());
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t PixelDigiSource::ReadEvent(UInt_t i)
{
  if (fDigis) fDigis->Delete();
  fNDigis = 0;

  if ( i == 0 ) { 
    fInputFile.clear();
    fInputFile.seekg(0, std::ios::beg);
  }

  fCurrentEntryNo = i;

  std::string buffer;
  LOG(DEBUG) << "PixelDigiSource::ReadEvent() Begin of (" << fDigis->GetEntries() << ")" << FairLogger::endl;
  do {
    getline(fInputFile,buffer);
    LOG(DEBUG) << "read from file: \"" << buffer << "\"" << FairLogger::endl;
    if ( buffer.find("EVENT BEGIN") == 0 ) {
      fRunId     = ReadIntFromString(buffer,"RUNID");
      fMCEntryNo = ReadIntFromString(buffer,"MCENTRYNO");
      fPartNo    = ReadIntFromString(buffer,"PARTNO");
      LOG(DEBUG) << "GOT NEW EVENT " << fMCEntryNo << " (part " << fPartNo << ") with run id = " << fRunId << FairLogger::endl;
    }
    if ( buffer.find("EVENT") == 0 ) continue;
    Int_t detId     = atoi(buffer.c_str());
    buffer.erase(0,buffer.find(' ')+1);
    Int_t feId      = atoi(buffer.c_str());
    buffer.erase(0,buffer.find(' ')+1);
    Int_t col       = atoi(buffer.c_str());
    buffer.erase(0,buffer.find(' ')+1);
    Int_t row       = atoi(buffer.c_str());
    buffer.erase(0,buffer.find(' ')+1);
    Double_t charge = atof(buffer.c_str());
    LOG(DEBUG) << "    --/" << fNDigis << "/-->    " << detId << " / " << feId << " / " << col << " / " << row << " / " << charge << FairLogger::endl;
    new ((*fDigis)[fNDigis]) PixelDigi(-1,detId,feId,col,row,charge,0.);
    fNDigis++;
  }
  while ( fInputFile && buffer.compare("EVENT END") );
  LOG(DEBUG) << "PixelDigiSource::ReadEvent() End of" << FairLogger::endl;

  if ( !fInputFile ) {
    return 1;
  }
 
  return 0;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t   PixelDigiSource::ActivateObject(TObject** obj, const char* BrName) {
  *obj = (TObject*)fDigis; 
  
  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void PixelDigiSource::Close()
{
  fInputFile.close();
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void PixelDigiSource::Reset()
{
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Int_t  PixelDigiSource::CheckMaxEventNo(Int_t /*EvtEnd*/)
{
  return -1;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void PixelDigiSource::FillEventHeader(FairEventHeader* feh) 
{
  ((PixelEventHeader*)feh)->SetRunId(fRunId);
  ((PixelEventHeader*)feh)->SetMCEntryNumber(fMCEntryNo);
  ((PixelEventHeader*)feh)->SetPartNo(fPartNo);
}
//_____________________________________________________________________________

ClassImp(PixelDigiSource)


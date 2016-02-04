/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           FairLmdSource                           -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------
#include <iostream>
using namespace std;

#include "TList.h"
#include "TObjString.h"
#include "TRegexp.h"
#include "TSystemDirectory.h"
#include "TSystem.h"

#include "FairLmdSource.h"
#include "FairLogger.h"

FairLmdSource::FairLmdSource()
  : FairMbsSource(),
    fCurrentFile(0),
	fNEvent(0),
    fCurrentEvent(0),
    fFileNames(new TList()),
    fxInputChannel(NULL),
    fxEvent(NULL),
    fxBuffer(NULL),
    fxEventData(NULL),
    fxSubEvent(NULL),
    fxInfoHeader(NULL)
{
}


FairLmdSource::FairLmdSource(const FairLmdSource& source)
  : FairMbsSource(source),
    fCurrentFile(source.GetCurrentFile()),
	fNEvent(0),
    fCurrentEvent(0),
    fFileNames(new TList()),
    fxInputChannel(NULL),
    fxEvent(NULL),
    fxBuffer(NULL),
    fxEventData(NULL),
    fxSubEvent(NULL),
    fxInfoHeader(NULL)
{
}


FairLmdSource::~FairLmdSource()
{
  fFileNames->Delete();
  delete fFileNames;
}


void FairLmdSource::AddFile(TString fileName)
{
  FileStat_t buf;
  if(1 == gSystem->GetPathInfo(fileName.Data(), buf))
  {
    LOG(WARNING) << "FairLmdSource: not found: " << fileName << FairLogger::endl;
    return;
  }

  TObjString* str = new TObjString(fileName);
  fFileNames->Add(str);
}


void FairLmdSource::AddPath(TString dir, TString wildCard)
{
  FileStat_t buf;
  if(1 == gSystem->GetPathInfo(dir.Data(), buf))
  {
    LOG(WARNING) << "FairLmdSource: not found: " << dir << FairLogger::endl;
    return;
  }

  TRegexp *re = new TRegexp(wildCard.Data(), kTRUE);
  TSystemDirectory *sdir = new TSystemDirectory("dir", dir.Data());
  TString dname(dir);
  if(! dname.EndsWith("/"))
  {
      dname += "/";
  }
  TList *list = sdir->GetListOfFiles();

  TIterator *iter = list->MakeIterator();
  TSystemFile *file;
  TString name;
  while(NULL != (file = static_cast<TSystemFile*>(iter->Next())))
  {
    name = file->GetName();
    if(name.Contains(*re))
    {
      name = dname + name;
      AddFile(name);
    }
  }

  list->Delete();
}


Bool_t FairLmdSource::Init()
{
  if(fFileNames->GetSize() == 0) {
    return kFALSE;
  }

  TString name = (static_cast<TObjString*>(fFileNames->At(fCurrentFile)))->GetString();
  if(! OpenNextFile(name)) {
    return kFALSE;
  }

  fCurrentFile += 1;

 // Init Counters
  fNEvent=fCurrentEvent=0;

  return kTRUE;
}


Bool_t FairLmdSource::OpenNextFile(TString fileName)
{
  Int_t inputMode = GETEVT__FILE;
  fxInputChannel = new s_evt_channel;
  void* headptr = &fxInfoHeader;
  INTS4 status;

  LOG(INFO) << "File " << fileName << " will be opened." << FairLogger::endl;

  status = f_evt_get_open(inputMode,
                          const_cast<char*>(fileName.Data()),
                          fxInputChannel,
                          static_cast<Char_t**>(headptr),
                          1,
                          1);

  if(status) {
     LOG(ERROR) << "File " << fileName << " opening failed." << FairLogger::endl;
    return kFALSE;
  }

  LOG(INFO) << "File " << fileName << " opened." << FairLogger::endl;

  // Decode File Header
  //Bool_t result = Unpack((Int_t*)fxInfoHeader, sizeof(s_filhe), -4, -4, -4, -4, -4);
  Unpack(reinterpret_cast<Int_t*>(fxInfoHeader), sizeof(s_filhe), -4, -4, -4, -4, -4);

  return kTRUE;
}


Int_t FairLmdSource::ReadEvent(UInt_t)
{
  void* evtptr = &fxEvent;
  void* buffptr = &fxBuffer;

  Int_t status = f_evt_get_event(fxInputChannel, static_cast<INTS4**>(evtptr),static_cast<INTS4**>(buffptr));
  //Int_t fuEventCounter = fxEvent->l_count;
  //Int_t fCurrentMbsEventNo = fuEventCounter;

  if(GETEVT__SUCCESS != status) {

    LOG(INFO) << "FairMbsStreamSource::ReadEvent()"
              << FairLogger::endl;

    CHARS* sErrorString = NULL;
    f_evt_error(status, sErrorString , 0);

    if(fCurrentFile >= fFileNames->GetSize()) {
      return 1;
    }

    if(GETEVT__NOMORE == status) {
      Close();
    }

    TString name = (static_cast<TObjString*>(fFileNames->At(fCurrentFile)))->GetString();
    if(! OpenNextFile(name)) {
      return 1;
    } else {
      fCurrentFile += 1;
      return ReadEvent();
    }
  }

 //Store Start Times
  if (fCurrentEvent==0 ) 
      Unpack(reinterpret_cast<Int_t*>(fxBuffer), sizeof(s_bufhe), -4, -4, -4, -4, -4);


  // Decode event header
  Bool_t result = kFALSE;
  /*Bool_t result = */Unpack(reinterpret_cast<Int_t*>(fxEvent), sizeof(s_ve10_1), -2, -2, -2, -2, -2);

  Int_t nrSubEvts = f_evt_get_subevent(fxEvent, 0, NULL, NULL, NULL);
  Int_t sebuflength;
  Short_t setype;
  Short_t sesubtype;
  Short_t seprocid;
  Short_t sesubcrate;
  Short_t secontrol;

  LOG(DEBUG2)<< "FairLmdSource::ReadEvent => Found " << nrSubEvts << " Sub-event "
             << FairLogger::endl;
  //if (fCurrentEvent%10000==0)
  //cout << " -I- LMD_ANA:  evt# " <<  fCurrentEvent << "  n_subevt# " << nrSubEvts << " evt processed# " << fNEvent <<  " : " << fxEvent->l_count << endl;


//  Int_t* SubEventDataPtr = new Int_t;
  for(Int_t i = 1; i <= nrSubEvts; i++) {
    void* SubEvtptr = &fxSubEvent;
    void* EvtDataptr = &fxEventData;
    Int_t nrlongwords;
    status = f_evt_get_subevent(fxEvent, i, static_cast<Int_t**>(SubEvtptr), static_cast<Int_t**>(EvtDataptr), &nrlongwords);
    if(status) {
      return 1;
    }
    sebuflength = nrlongwords;
    setype = fxSubEvent->i_type;
    sesubtype = fxSubEvent->i_subtype;
    seprocid = fxSubEvent->i_procid;
    sesubcrate = fxSubEvent->h_subcrate;
    secontrol = fxSubEvent->h_control;

    //cout << setype << "  " << sesubtype << "  " << seprocid << "  " << sesubcrate << "  " << secontrol << endl;

    if(Unpack(fxEventData, sebuflength,
              setype, sesubtype,
              seprocid, sesubcrate, secontrol)) {
      result = kTRUE;
    }
  }

  // Increment evt counters.
  fNEvent++;
  fCurrentEvent++;
 
  if(! result)
  {
    return 2;
  }

 return 0;
}


void FairLmdSource::Close()
{
  f_evt_get_close(fxInputChannel);
  Unpack(reinterpret_cast<Int_t*>(fxBuffer), sizeof(s_bufhe), -4, -4, -4, -4, -4);  
  fCurrentEvent=0;
}


ClassImp(FairLmdSource)



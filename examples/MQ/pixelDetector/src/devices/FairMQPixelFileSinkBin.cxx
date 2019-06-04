/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelFileSinkBin.cxx
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQPixelFileSinkBin.h"
#include "FairMQLogger.h"

#include "TVector3.h"

#include "PixelPayload.h"
#include "PixelHit.h"

using namespace std;

FairMQPixelFileSinkBin::FairMQPixelFileSinkBin()
  : FairMQDevice()
  , fInputChannelName("data-in")
  , fAckChannelName("")
  , fFileName()
  , fTreeName()
 
  , fBranchNames()
  , fClassNames()
  , fFileOption()
  , fFlowMode(false)
  , fWrite(false)

  , fOutFile(NULL)
  , fTree(NULL)
  , fNObjects(0)
  , fOutputObjects(new TObject*[1000])
  , fFolder(NULL)
{
}

void FairMQPixelFileSinkBin::Init()
{
  fFileName          = fConfig->GetValue<std::string>             ("file-name");
  fClassNames        = fConfig->GetValue<std::vector<std::string>>("class-name");
  fBranchNames       = fConfig->GetValue<std::vector<std::string>>("branch-name");
  fInputChannelName  = fConfig->GetValue<std::string>             ("in-channel");
  fAckChannelName    = fConfig->GetValue<std::string>             ("ack-channel");

  LOG(info) << "SHOULD CREATE THE FILE AND TREE";
  fFileOption = "RECREATE";
  fTreeName = "cbmsim";  

  fOutFile = TFile::Open(fFileName.c_str(),fFileOption.c_str());
  
  fTree = new TTree(fTreeName.c_str(), "/cbmout");

  fFolder = new TFolder("cbmout", "Main Output Folder");
  TFolder* foldEventHeader = fFolder->AddFolder("EvtHeader","EvtHeader");
  TFolder* foldPixel       = fFolder->AddFolder("Pixel","Pixel");
  
  TList* BranchNameList = new TList();
  
  for ( fNObjects = 0 ; fNObjects < fBranchNames.size() ; fNObjects++ ) {
    if      ( fClassNames[fNObjects].find("TClonesArray(") == 0 ) {
      fClassNames   [fNObjects] = fClassNames[fNObjects].substr(13,fClassNames[fNObjects].length()-12-2);
      fOutputObjects            [fNObjects] = new    TClonesArray(fClassNames[fNObjects].c_str());
      fTree->Branch(fBranchNames[fNObjects].c_str(),"TClonesArray", &fOutputObjects[fNObjects]);
      foldPixel->Add(fOutputObjects[fNObjects]);
      BranchNameList->AddLast(new TObjString(fBranchNames[fNObjects].c_str()));
    }
    else if ( fClassNames[fNObjects].find("FairEventHeader") == 0 ) {
      fOutputObjects            [fNObjects] = new    FairEventHeader();
      fTree->Branch(fBranchNames[fNObjects].c_str(),"FairEventHeader", &fOutputObjects[fNObjects]);
      foldEventHeader->Add(fOutputObjects[fNObjects]);
      BranchNameList->AddLast(new TObjString(fBranchNames[fNObjects].c_str()));
    }
    else {
      LOG(error) << "!!! Unknown output object \"" << fClassNames[fNObjects] << "\" !!!";
    }
  }  

  fFolder->Write();
  BranchNameList->Write("BranchList", TObject::kSingleKey);
  BranchNameList->Delete();
  delete BranchNameList;
  
  OnData(fInputChannelName, &FairMQPixelFileSinkBin::StoreData);
}

bool FairMQPixelFileSinkBin::StoreData(FairMQParts& parts, int /*index*/)
{
  if ( parts.Size() == 0 ) return true; // probably impossible, but still check
  
  // expecting even number of parts in the form: header,data,header,data,header,data and so on...
  int nPPE = 2; // nof parts per event

  if ( parts.Size()%nPPE >= 1 )
    LOG(info) << "received " << parts.Size() << " parts, will ignore last part!!!";

  for ( int ievent = 0 ; ievent < parts.Size()/nPPE ; ievent++ ) {

    // the first part should be the event header
    PixelPayload::EventHeader* payloadE = static_cast<PixelPayload::EventHeader*>(parts.At(nPPE*ievent)->GetData());
    // LOG(debug) << "GOT EVENT " << payloadE->fMCEntryNo << " OF RUN " << payloadE->fRunId << " (part " << payloadE->fPartNo << ")";
  
    for ( unsigned int ibr = 0 ; ibr < fBranchNames.size() ; ibr++ )
      {
        if ( "EventHeader." == fBranchNames[ibr] )
          {
            ((FairEventHeader*)fOutputObjects[ibr])->SetRunId        (payloadE->fRunId);
            ((FairEventHeader*)fOutputObjects[ibr])->SetMCEntryNumber(payloadE->fMCEntryNo);
          }
      }

    // the second part should the TClonesArray with necessary data... now assuming Digi
    PixelPayload::Hit* payloadH = static_cast<PixelPayload::Hit*>(parts.At(nPPE*ievent+1)->GetData());
    int hitArraySize = parts.At(nPPE*ievent+1)->GetSize();
    int nofHits      = hitArraySize / sizeof(PixelPayload::Hit);

    for ( unsigned int ibr = 0 ; ibr < fBranchNames.size() ; ibr++ )
      {
        if ( "PixelHits" == fBranchNames[ibr] )
          {
            ((TClonesArray*)fOutputObjects[ibr])->Clear();
            for ( int ihit = 0 ; ihit < nofHits ; ihit++ )
              {
                TVector3 pos   (payloadH[ihit].posX, payloadH[ihit].posY, payloadH[ihit].posZ);
                TVector3 posErr(payloadH[ihit].dposX,payloadH[ihit].dposY,payloadH[ihit].dposZ);
                new ((*((TClonesArray*)fOutputObjects[ibr]))[ihit]) PixelHit(payloadH[ihit].fDetectorID,-1,pos,posErr);
                //		      new ((*fHits)[fNHits]) PixelHit(detId,currentDigi->GetIndex(),pos,posErr);
              }
          }
      }

    fTree->Fill();
  }
  
  if ( fAckChannelName != "" ) {
    unique_ptr<FairMQMessage> msg(NewMessage());
    Send(msg, fAckChannelName);
  }
  return true;
}

FairMQPixelFileSinkBin::~FairMQPixelFileSinkBin()
{ 
  if (fTree)
    {
      fTree->Write();
      delete fTree;
    }

  if (fOutFile)
    {
      if (fOutFile->IsOpen())
        fOutFile->Close();
      delete fOutFile;
    }
}

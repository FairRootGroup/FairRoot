/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9FileSinkBin.cxx
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQEx9FileSinkBin.h"
#include "FairMQLogger.h"

#include "TMessage.h"
#include "TVector3.h"

#include "PixelPayload.h"
#include "PixelHit.h"

using namespace std;

// special class to expose protected TMessage constructor
class Ex9TMessage : public TMessage
{
  public:
  Ex9TMessage(void* buf, Int_t len)
    : TMessage(buf, len)
  {
    ResetBit(kIsOwner);
  }
};

FairMQEx9FileSinkBin::FairMQEx9FileSinkBin()
  : FairMQDevice()
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

void FairMQEx9FileSinkBin::Init()
{
  LOG(INFO) << "SHOULD CREATE THE FILE AND TREE";
  //  fFileName = "/Users/karabowi/fairroot/pixel9_dev/FairRoot/examples/MQ/9-PixelDetector/macros/tmpOut.root";
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
      LOG(ERROR) << "!!! Unknown output object \"" << fClassNames[fNObjects] << "\" !!!";
    }
  }  

  fFolder->Write();
  BranchNameList->Write("BranchList", TObject::kSingleKey);
  BranchNameList->Delete();
  delete BranchNameList;
  
}

void FairMQEx9FileSinkBin::Run()
{
  while (CheckCurrentState(RUNNING))
    {
      FairMQParts parts;
      
      if (Receive(parts, "data-in") >= 0)
	{

          if ( parts.Size() == 0 ) continue; // probably impossible, but still check
	  
          // the first part should be the event header
	  PixelPayload::EventHeader* payloadE = static_cast<PixelPayload::EventHeader*>(parts.At(0)->GetData());
          LOG(TRACE) << "GOT EVENT " << payloadE->fMCEntryNo << " OF RUN " << payloadE->fRunId << " (part " << payloadE->fPartNo << ")";
	  
	  for ( unsigned int ibr = 0 ; ibr < fBranchNames.size() ; ibr++ ) 
	    {
	      if ( strcmp("EventHeader.",fBranchNames[ibr].c_str()) == 0 ) 
		{
		  ((FairEventHeader*)fOutputObjects[ibr])->SetRunId        (payloadE->fRunId);
		  ((FairEventHeader*)fOutputObjects[ibr])->SetMCEntryNumber(payloadE->fMCEntryNo);
		}
	    }

	  // the second part should the TClonesArray with necessary data... now assuming Digi
	  PixelPayload::Hit* payloadH = static_cast<PixelPayload::Hit*>(parts.At(1)->GetData());
	  int hitArraySize = parts.At(1)->GetSize();
	  int nofHits      = hitArraySize / sizeof(PixelPayload::Hit);

	  for ( unsigned int ibr = 0 ; ibr < fBranchNames.size() ; ibr++ ) 
	    {
	      if ( strcmp("PixelHits",fBranchNames[ibr].c_str()) == 0 ) 
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
      else 
	{
	  LOG(INFO) << "oops!";
	}
    }
}

void FairMQEx9FileSinkBin::SetProperty(const int key, const std::string& value)
{
    switch (key)
    {
        case OutputFileName :
	  SetOutputFileName(value);
            break;

        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}

void FairMQEx9FileSinkBin::SetProperty(const int key, const int value)
{
    FairMQDevice::SetProperty(key, value);
}

std::string FairMQEx9FileSinkBin::GetProperty(const int key, const std::string& default_)
{
    switch (key)
    {
        case OutputFileName :
	  return GetOutputFileName();

        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}

int FairMQEx9FileSinkBin::GetProperty(const int key, const int value)
{
    return FairMQDevice::GetProperty(key, value);
}

FairMQEx9FileSinkBin::~FairMQEx9FileSinkBin()
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

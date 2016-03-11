/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQEx9FileSink.cxx
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "FairMQEx9FileSink.h"
#include "FairMQLogger.h"

#include "TMessage.h"

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

FairMQEx9FileSink::FairMQEx9FileSink()
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

void FairMQEx9FileSink::Init()
{
  LOG(INFO) << "SHOULD CREATE THE FILE AND TREE";
  //  fFileName = "/Users/karabowi/fairroot/pixel9_dev/FairRoot/examples/MQ/9-PixelDetector/macros/tmpOut.root";
  fFileOption = "RECREATE";
  fTreeName = "cbmsim";  

  // fBranchNames.push_back("EventHeader.");
  // fClassNames .push_back("FairEventHeader");
  // fBranchNames.push_back("PixelHits");
  // fClassNames .push_back("TClonesArray(PixelHit)");
  
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

void FairMQEx9FileSink::Run()
{
  while (CheckCurrentState(RUNNING))
    {
      FairMQParts parts;
      
      if (Receive(parts, "data-in") >= 0)
	{

	  TObject* tempObjects[10];
	  for ( int ipart = 0 ; ipart < parts.Size() ; ipart++ ) 
	    {
	      Ex9TMessage tm(parts.At(ipart).GetData(), parts.At(ipart).GetSize());
	      tempObjects[ipart] = (TObject*)tm.ReadObject(tm.GetClass());
	      for ( int ibr = 0 ; ibr < fBranchNames.size() ; ibr++ ) 
		{
		  if ( strcmp(tempObjects[ipart]->GetName(),fBranchNames[ibr].c_str()) == 0 ) 
		    {
		      fOutputObjects[ibr] = tempObjects[ipart];
		      fTree->SetBranchAddress(fBranchNames[ibr].c_str(),&fOutputObjects[ibr]);
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

void FairMQEx9FileSink::SetProperty(const int key, const std::string& value)
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

void FairMQEx9FileSink::SetProperty(const int key, const int value)
{
    FairMQDevice::SetProperty(key, value);
}

std::string FairMQEx9FileSink::GetProperty(const int key, const std::string& default_)
{
    switch (key)
    {
        case OutputFileName :
	  return GetOutputFileName();

        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}

int FairMQEx9FileSink::GetProperty(const int key, const int value)
{
    return FairMQDevice::GetProperty(key, value);
}

FairMQEx9FileSink::~FairMQEx9FileSink()
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

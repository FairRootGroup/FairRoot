/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPixelFileSink.cxx
 *
 * @since 2016-03-08
 * @author R. Karabowicz
 */

#include <boost/thread.hpp>
#include <boost/bind.hpp>

#include "TMessage.h"

#include "FairMCEventHeader.h"
#include "FairMQPixelFileSink.h"
#include "FairMQLogger.h"
#include <options/FairMQProgOptions.h>

using namespace std;

// special class to expose protected TMessage constructor
class PixelTMessage : public TMessage
{
  public:
  PixelTMessage(void* buf, Int_t len)
    : TMessage(buf, len)
  {
    ResetBit(kIsOwner);
  }
};

FairMQPixelFileSink::FairMQPixelFileSink()
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

void FairMQPixelFileSink::Init()
{
  fFileName          = fConfig->GetValue<std::string>             ("file-name");
  fClassNames        = fConfig->GetValue<std::vector<std::string>>("class-name");
  fBranchNames       = fConfig->GetValue<std::vector<std::string>>("branch-name");
  fInputChannelName  = fConfig->GetValue<std::string>             ("in-channel");
  fAckChannelName    = fConfig->GetValue<std::string>             ("ack-channel");

  LOG(INFO) << "SHOULD CREATE THE FILE AND TREE";
  fFileOption = "RECREATE";
  fTreeName = "cbmsim";  

  // fBranchNames.push_back("EventHeader.");
  // fClassNames .push_back("FairEventHeader");
  // fBranchNames.push_back("PixelHits");
  // fClassNames .push_back("TClonesArray(PixelHit)");

  if ( ::getenv("DDS_SESSION_ID") ) {
    std::string DDS_SESSION_ID = ::getenv("DDS_SESSION_ID");
    if ( fFileName.length() > 5 ) {
      DDS_SESSION_ID = "." + DDS_SESSION_ID + ".root";
      fFileName.replace(fFileName.length()-5,5,DDS_SESSION_ID.c_str());
    }
  }
  
  fOutFile = TFile::Open(fFileName.c_str(),fFileOption.c_str());
  
  fTree = new TTree(fTreeName.c_str(), "/cbmout");

  fFolder = new TFolder("cbmout", "Main Output Folder");
  TFolder* foldEventHeader = fFolder->AddFolder("EvtHeader","EvtHeader");
  TFolder* foldPixel       = fFolder->AddFolder("Pixel","Pixel");
  
  TList* BranchNameList = new TList();
  
  for ( fNObjects = 0 ; fNObjects < fBranchNames.size() ; fNObjects++ ) {
    LOG(INFO) << "Creating output branch \"" << fClassNames[fNObjects] << "\" with name \"" << fBranchNames[fNObjects] << "\"";
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
    else if ( fClassNames[fNObjects].find("FairMCEventHeader") == 0 ) {
      fOutputObjects            [fNObjects] = new    FairMCEventHeader();
      fTree->Branch(fBranchNames[fNObjects].c_str(),"FairMCEventHeader", &fOutputObjects[fNObjects]);
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
  
  OnData(fInputChannelName, &FairMQPixelFileSink::StoreData);
}

bool FairMQPixelFileSink::StoreData(FairMQParts& parts, int /*index*/)
{
  std::vector<TObject*> tempObjects;
  for ( int ipart = 0 ; ipart < parts.Size() ; ipart++ ) 
    {
      PixelTMessage tm(parts.At(ipart)->GetData(), parts.At(ipart)->GetSize());
      tempObjects.push_back((TObject*)tm.ReadObject(tm.GetClass()));
      for ( unsigned int ibr = 0 ; ibr < fBranchNames.size() ; ibr++ ) 
        {
          if ( strcmp(tempObjects.back()->GetName(),fBranchNames[ibr].data()) == 0 )
            {
              fOutputObjects[ibr] = tempObjects.back();
              fTree->SetBranchAddress(fBranchNames[ibr].c_str(),&fOutputObjects[ibr]);
            }
        }
    }
  fTree->Fill();
  
  for ( int ipart = 0 ; ipart < tempObjects.size() ; ipart++ )
    {
      if ( tempObjects[ipart] )
        delete tempObjects[ipart];
    }
  tempObjects.clear();
  
  if ( fAckChannelName != "" )
    {
      unique_ptr<FairMQMessage> msg(NewMessage());
      Send(msg, fAckChannelName);
    }
  return true;
}

FairMQPixelFileSink::~FairMQPixelFileSink()
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

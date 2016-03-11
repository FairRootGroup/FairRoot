/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQEx9TaskProcessor.h"
#include "FairMQParts.h"
#include "PixelFindHits.h"
#include "TMessage.h"
#include "PixelDigiPar.h"

// special class to expose protected TMessage constructor
class Ex9TMessage2 : public TMessage
{
  public:
  Ex9TMessage2(void* buf, Int_t len)
    : TMessage(buf, len)
  {
    ResetBit(kIsOwner);
  }
};

// helper function to clean up the object holding the data after it is transported.
void free_tmessage4(void *data, void *hint)
{
    delete (TMessage*)hint;
}

FairMQEx9TaskProcessor::FairMQEx9TaskProcessor()
  : FairMQDevice()
  , fNewRunId(1)
  , fCurrentRunId(-1)
  , fInput(NULL)
  , fOutput(NULL)
  , fEventHeader(NULL)
  , fFairTask(NULL)
  , fGeoPar(nullptr)
  , fParCList(NULL)
{

}

FairMQEx9TaskProcessor::~FairMQEx9TaskProcessor()
{
  if(fGeoPar)
    {
      delete fGeoPar;
      fGeoPar=nullptr;
    }
  
  if(fInput)
    {
      delete fInput;
      fInput=nullptr;
    }
  
  if(fOutput)
    {
      delete fOutput;
      fOutput=nullptr;
    }
}


void FairMQEx9TaskProcessor::Init()
{
    //fHitFinder->InitMQ(fRootParFileName,fAsciiParFileName);
  fFairTask = new PixelFindHits();
  fGeoPar = new FairGeoParSet("FairGeoParSet");
  fParCList = new TList();
  fParCList->Add(fGeoPar);
  fFairTask->GetParList(fParCList);
  
  fOutput = new TList();
  fInput = new TList();
}

void FairMQEx9TaskProcessor::Run()
{
    int receivedMsgs = 0;
    int sentMsgs = 0;

    while (CheckCurrentState(RUNNING))
    {
      FairMQParts parts;
      
      if ( Receive(parts,"data-in") >= 0 )
        {
	  LOG(DEBUG)<<"message received";
	  receivedMsgs++;
	  
	  TObject* tempObjects[10];
	  for ( int ipart = 0 ; ipart < parts.Size() ; ipart++ ) 
	    {
	      Ex9TMessage2 tm(parts.At(ipart).GetData(), parts.At(ipart).GetSize());
	      tempObjects[ipart] = (TObject*)tm.ReadObject(tm.GetClass());
	      if ( strcmp(tempObjects[ipart]->GetName(),"EventHeader.") == 0 ) 
		fEventHeader = (FairEventHeader*)tempObjects[ipart];
	      else {
		fInput->Add(tempObjects[ipart]);
	      }
	    }
	  
	  fNewRunId = fEventHeader->GetRunId();
	  if(fNewRunId!=fCurrentRunId)
            {
	      fCurrentRunId=fNewRunId;
	      UpdateParameters();
	      PixelDigiPar* tempDP = (PixelDigiPar*)fParCList->FindObject("PixelDigiParameters");
	      fFairTask->InitMQ(fParCList);
            }
            
	  
	  // Execute hit finder task
	  fOutput->Clear();
	  LOG(INFO) << " analyzing event " << fEventHeader->GetMCEntryNumber();
	  fFairTask->ExecMQ(fInput,fOutput);

	  TMessage* messageFEH;
	  TMessage* messageTCA[10];
	  FairMQParts partsOut;
	  
	  messageFEH = new TMessage(kMESS_OBJECT);
	  messageFEH->WriteObject(fEventHeader);
	  partsOut.AddPart(NewMessage(messageFEH->Buffer(), messageFEH->BufferSize(), free_tmessage4, messageFEH));
	  for ( int iobj = 0 ; iobj < fOutput->GetEntries() ; iobj++ ) {
	    messageTCA[iobj] = new TMessage(kMESS_OBJECT);
	    messageTCA[iobj]->WriteObject(fOutput->At(iobj));
	    partsOut.AddPart(NewMessage(messageTCA[iobj]->Buffer(), messageTCA[iobj]->BufferSize(), free_tmessage4, messageTCA[iobj]));
	    Send(partsOut, "data-out");
	  }
	  
	  sentMsgs++;
        }
      fInput->Clear();
    }
    
    MQLOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
}




void FairMQEx9TaskProcessor::CustomCleanup(void *data, void *hint)
{
    delete (std::string*)hint;
}



void FairMQEx9TaskProcessor::SetProperty(const int key, const std::string& value)
{
    switch (key)
    {
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}



std::string FairMQEx9TaskProcessor::GetProperty(const int key, const std::string& default_)
{
    switch (key)
    {
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}


void FairMQEx9TaskProcessor::SetProperty(const int key, const int value)
{
    FairMQDevice::SetProperty(key, value);
}

int FairMQEx9TaskProcessor::GetProperty(const int key, const int value)
{
    return FairMQDevice::GetProperty(key, value);
}







void FairMQEx9TaskProcessor::UpdateParameters() {
  for ( int iparC = 0 ; iparC < fParCList->GetEntries() ; iparC++ ) {
    FairParGenericSet* tempObj = (FairParGenericSet*)(fParCList->At(iparC));
    fParCList->Remove(tempObj);
    fParCList->AddAt(UpdateParameter(tempObj),iparC);
  }
}

FairParGenericSet* FairMQEx9TaskProcessor::UpdateParameter(FairParGenericSet* thisPar) {
  std::string paramName = thisPar->GetName();
  //  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
  std::string* reqStr = new std::string(paramName + "," + std::to_string(fCurrentRunId));
  LOG(WARN) << "Requesting parameter \"" << paramName << "\" for Run ID " << fCurrentRunId << " (" << thisPar << ")";
  std::unique_ptr<FairMQMessage> req(fTransportFactory->CreateMessage(const_cast<char*>(reqStr->c_str()), reqStr->length(), CustomCleanup, reqStr));
  std::unique_ptr<FairMQMessage> rep(fTransportFactory->CreateMessage());
  
  if (fChannels.at("param").at(0).Send(req) > 0)
    {
      if (fChannels.at("param").at(0).Receive(rep) > 0)
	{
	  Ex9TMessage2 tm(rep->GetData(), rep->GetSize());
	  thisPar = (FairParGenericSet*)tm.ReadObject(tm.GetClass());
	  LOG(WARN) << "Received parameter"<< paramName <<" from the server (" << thisPar << ")";
	  return thisPar;
	}
    } 
  return NULL;
}

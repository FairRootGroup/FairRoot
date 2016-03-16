/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

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

template <typename T>
FairMQEx9TaskProcessor<T>::FairMQEx9TaskProcessor()
  : FairMQDevice()
  , fNewRunId(1)
  , fCurrentRunId(-1)
  , fDataToKeep("")
  , fInput(NULL)
  , fOutput(NULL)
  , fEventHeader(NULL)
  , fFairTask(NULL)
  , fGeoPar(nullptr)
  , fParCList(NULL)
{

}

template <typename T>
FairMQEx9TaskProcessor<T>::~FairMQEx9TaskProcessor()
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

  delete fFairTask;
}


template <typename T>
void FairMQEx9TaskProcessor<T>::Init()
{
    //fHitFinder->InitMQ(fRootParFileName,fAsciiParFileName);
  fFairTask = new T();
  fGeoPar = new FairGeoParSet("FairGeoParSet");
  fParCList = new TList();
  fParCList->Add(fGeoPar);
  fFairTask->GetParList(fParCList);
  
  fOutput = new TList();
  fInput = new TList();
}

template <typename T>
void FairMQEx9TaskProcessor<T>::Run()
{
    int receivedMsgs = 0;
    int sentMsgs = 0;
    TObject* objectToKeep = NULL;

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
	      fFairTask->InitMQ(fParCList);
            }
            
	  
	  // Execute hit finder task
	  fOutput->Clear();
	  //	  LOG(INFO) << " The blocking line... analyzing event " << fEventHeader->GetMCEntryNumber();
	  fFairTask->ExecMQ(fInput,fOutput);

	  if ( !fDataToKeep.empty() ) {
	    objectToKeep = fInput->FindObject(fDataToKeep.c_str());
	    if ( objectToKeep ) fOutput->Add(objectToKeep);
	  }
	  
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
	  }
	  Send(partsOut, "data-out");
	  sentMsgs++;
        }
      fInput->Clear();
    }
    
    MQLOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
}




template <typename T>
void FairMQEx9TaskProcessor<T>::CustomCleanup(void *data, void *hint)
{
    delete (std::string*)hint;
}



template <typename T>
void FairMQEx9TaskProcessor<T>::SetProperty(const int key, const std::string& value)
{
    switch (key)
    {
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}



template <typename T>
std::string FairMQEx9TaskProcessor<T>::GetProperty(const int key, const std::string& default_)
{
    switch (key)
    {
        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}


template <typename T>
void FairMQEx9TaskProcessor<T>::SetProperty(const int key, const int value)
{
    FairMQDevice::SetProperty(key, value);
}

template <typename T>
int FairMQEx9TaskProcessor<T>::GetProperty(const int key, const int value)
{
    return FairMQDevice::GetProperty(key, value);
}







template <typename T>
void FairMQEx9TaskProcessor<T>::UpdateParameters() {
  for ( int iparC = 0 ; iparC < fParCList->GetEntries() ; iparC++ ) {
    FairParGenericSet* tempObj = (FairParGenericSet*)(fParCList->At(iparC));
    fParCList->Remove(tempObj);
    fParCList->AddAt(UpdateParameter(tempObj),iparC);
  }
}

template <typename T>
FairParGenericSet* FairMQEx9TaskProcessor<T>::UpdateParameter(FairParGenericSet* thisPar) {
  std::string paramName = thisPar->GetName();
  //  boost::this_thread::sleep(boost::posix_time::milliseconds(1000));
  std::string* reqStr = new std::string(paramName + "," + std::to_string(fCurrentRunId));
  LOG(WARN) << "Requesting parameter \"" << paramName << "\" for Run ID " << fCurrentRunId << " (" << thisPar << ")";
  std::unique_ptr<FairMQMessage> req(NewMessage(const_cast<char*>(reqStr->c_str()), reqStr->length(), CustomCleanup, reqStr));
  std::unique_ptr<FairMQMessage> rep(NewMessage());
  
  if (Send(req,"param") > 0)
    {
      if (Receive(rep,"param") > 0)
	{
	  Ex9TMessage2 tm(rep->GetData(), rep->GetSize());
	  thisPar = (FairParGenericSet*)tm.ReadObject(tm.GetClass());
	  LOG(WARN) << "Received parameter"<< paramName <<" from the server (" << thisPar << ")";
	  return thisPar;
	}
    } 
  return NULL;
}

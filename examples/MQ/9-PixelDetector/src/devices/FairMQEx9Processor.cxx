/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairMQEx9Processor.h"
#include "FairMQParts.h"

TClonesArray* fOutput;
std::string fRootParFileName;
std::string fAsciiParFileName;
std::string fInputClassName;
std::string fParamName;
std::string fGeoParamName;
int fCurrentRunId;
PixelDigiPar* fDigiPar;
FairGeoParSet* fGeoPar;


RootSerializer fSerializer;
RootDeSerializer fDeSerializer;

//base_RootDeSerializer<PixelDigiPar> fParamDeserializer;
PixelFindHitsTask fHitFinder;

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

// helper function to clean up the object holding the data after it is transported.
void free_tmessage3(void* /*data*/, void* hint)
{
    delete (TMessage*)hint;
}


FairMQEx9Processor::FairMQEx9Processor() 
 : FairMQDevice(),
   fEventHeader(nullptr),
   fInput(nullptr),
   fOutput(nullptr),
   fRootParFileName(""),
   fAsciiParFileName(""),
   fInputClassName(""),
   fParamName("PixelDigiParameters"),
   fGeoParamName("FairGeoParSet"),
   fCurrentRunId(-1),
   fDigiPar(nullptr),
   fGeoPar(nullptr),
   fSerializer(),
   fDeSerializer(),
   //fParamDeserializer(),
   fHitFinder()
{

}

FairMQEx9Processor::~FairMQEx9Processor()
{
    if(fDigiPar)
    {
        delete fDigiPar;
        fDigiPar=nullptr;
    }

    if(fGeoPar)
    {
        delete fGeoPar;
        fGeoPar=nullptr;
    }

    if(fOutput)
    {
        delete fOutput;
        fOutput=nullptr;
    }


}


void FairMQEx9Processor::Init()
{
  //	fDeSerializer.InitContainer(fInputClassName);
    //fParamDeserializer.InitContainer("PixelDigiPar");
    //fHitFinder->InitMQ(fRootParFileName,fAsciiParFileName);
    fOutput = new TClonesArray("PixelHit");
    fInput = new TList();
}

void FairMQEx9Processor::Run()
{
    int receivedMsgs = 0;
    int sentMsgs = 0;

    //    const FairMQChannel& inputChannel = fChannels["data-in"].at(0);
    //    const FairMQChannel& outputChannel = fChannels["data-out"].at(0);

    while (CheckCurrentState(RUNNING))
    {
      //      std::unique_ptr<FairMQParts> msg(fTransportFactory->CreateMessage());

      FairMQParts parts;

        LOG(TRACE)<<"in loop";
        if ( Receive(parts,"data-in") >= 0 )
        {
	  LOG(INFO) << "my message has " << parts.Size() << " parts...";
            LOG(DEBUG)<<"message received";
            receivedMsgs++;
    
	    TObject* tempObjects[10];
	    for ( int ipart = 0 ; ipart < parts.Size() ; ipart++ ) 
	      {
		Ex9TMessage tm(parts.At(ipart).GetData(), parts.At(ipart).GetSize());
		LOG(INFO) << "GOT PART " << ipart;
		//	      tempObjects[ipart] = new TObject();
		tempObjects[ipart] = (TObject*)tm.ReadObject(tm.GetClass());
		LOG(INFO) << "WITH NAME \"" << tempObjects[ipart]->GetName() << "\"";
		if ( strcmp(tempObjects[ipart]->GetName(),"EventHeader.") == 0 ) 
		  fEventHeader = (FairEventHeader*)tempObjects[ipart];
		else
		  fInput->Add(tempObjects[ipart]);
	      }
	    LOG(INFO) << "now there are " << fInput->GetEntries() << " entries in the tlist";

        // Deserialize data into TClonesArray
	    // Ex9TMessage tmFEH(parts.At(0).GetData(), parts.At(0).GetSize());
	    // fEventHeader        = (FairEventHeader*)(tmFEH.ReadObject(tmFEH.GetClass()));
	    // Ex9TMessage tmTCA(parts.At(1).GetData(), parts.At(1).GetSize());
	    // TClonesArray* input = (TClonesArray*)   (tmTCA.ReadObject(tmTCA.GetClass()));
	    //	    LOG(INFO) << "feh with name \"" << fEventHeader->GetName() << "\", tca with name \"" << input->GetName() << "\"";
	    fNewRunId = fEventHeader->GetRunId();
	    //            Int_t runId = 1456915975;
            if(fNewRunId!=fCurrentRunId)
            {
                fCurrentRunId=fNewRunId;
                UpdateParameters();
            }
            

            // Execute hit finder task
            fHitFinder.Exec(fInput,fOutput);
            LOG(TRACE)<<"exec task finish";
            // if output not empty serialize and send


	    TMessage* messageFEH;
	    TMessage* messageTCA;
	    FairMQParts partsOut;
	    
	    messageFEH = new TMessage(kMESS_OBJECT);
	    messageFEH->WriteObject(fEventHeader);
	    partsOut.AddPart(NewMessage(messageFEH->Buffer(), messageFEH->BufferSize(), free_tmessage3, messageFEH));
	    messageTCA = new TMessage(kMESS_OBJECT);
	    messageTCA->WriteObject(fOutput);
	    partsOut.AddPart(NewMessage(messageTCA->Buffer(), messageTCA->BufferSize(), free_tmessage3, messageTCA));
            Send(partsOut, "data-out");

	    sentMsgs++;
	    LOG(TRACE)<<"message sent ";
        }
	fInput->Clear();
    }
    
    MQLOG(INFO) << "Received " << receivedMsgs << " and sent " << sentMsgs << " messages!";
}




void FairMQEx9Processor::CustomCleanup(void* /*data*/, void* hint)
{
    delete static_cast<std::string*>(hint);
}





void FairMQEx9Processor::UpdateParameters()
{
    //*
    if(fDigiPar)
    {
        delete fDigiPar;
        fDigiPar=nullptr;
    }

    if(fGeoPar)
    {
        delete fGeoPar;
        fGeoPar=nullptr;
    }

    fDigiPar = new PixelDigiPar();
    fGeoPar = new FairGeoParSet();
    // */
    LOG(WARN)<<"Update digi parameters...";
    fDigiPar=UpdateParameter<PixelDigiPar>(fParamName,fDigiPar);
    auto fFeCols = fDigiPar->GetFECols();
    auto fFeRows = fDigiPar->GetFERows();
    auto fMaxFEperCol = fDigiPar->GetMaxFEperCol();
    auto fPitchX = fDigiPar->GetXPitch();
    auto fPitchY = fDigiPar->GetYPitch();
    //fGeoParSet=geopar;
    LOG(TRACE)<<"FairMQEx9Processor::UpdateParameters() "
          <<" fFeCols="<<fFeCols
          <<" fFeRows="<<fFeRows
          <<" fMaxFEperCol="<<fMaxFEperCol
          <<" fPitchX="<<fPitchX
          <<" fPitchY="<<fPitchY
          ;

    LOG(WARN)<<"Update geo parameters...";
    fGeoPar=UpdateParameter<FairGeoParSet>(fGeoParamName,fGeoPar);
    fHitFinder.Init(fDigiPar, fGeoPar);

    fFeCols = fDigiPar->GetFECols();
    fFeRows = fDigiPar->GetFERows();
    fMaxFEperCol = fDigiPar->GetMaxFEperCol();
    fPitchX = fDigiPar->GetXPitch();
    fPitchY = fDigiPar->GetYPitch();

}



void FairMQEx9Processor::SetProperty(const int key, const std::string& value)
{
    switch (key)
    {
        case RootParam :
            fRootParFileName = value;
            break;

        case AsciiParam :
            fAsciiParFileName = value;
            break;

        case InputClassName :
            fInputClassName = value;
            break;

        case ParamName :
            fParamName = value;
            break;
        
        default:
            FairMQDevice::SetProperty(key, value);
            break;
    }
}



std::string FairMQEx9Processor::GetProperty(const int key, const std::string& default_)
{
    switch (key)
    {
        case RootParam :
            return fRootParFileName;

        case AsciiParam :
            return fAsciiParFileName;

        case InputClassName :
            return fInputClassName;

        case ParamName :
            return fParamName;

        default:
            return FairMQDevice::GetProperty(key, default_);
    }
}


void FairMQEx9Processor::SetProperty(const int key, const int value)
{
    FairMQDevice::SetProperty(key, value);
}

int FairMQEx9Processor::GetProperty(const int key, const int value)
{
    return FairMQDevice::GetProperty(key, value);
}








/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQTransportDevice.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairMQTransportDevice.h"
  
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "FairMQProgOptions.h"

#include "FairOnlineSink.h"

#include "FairMCEventHeader.h"
#include "FairRootManager.h"
#include "FairRunSim.h"
#include "FairRuntimeDb.h"

#include "FairGenericStack.h"
#include "FairMCApplication.h"

#include "FairEventHeader.h"
#include "FairModule.h"
#include "FairParRootFileIo.h"
#include "FairParSet.h"

#include "TClonesArray.h"
#include "TROOT.h"
#include "TRint.h"
#include "TVirtualMC.h"
#include "TVirtualMCApplication.h"
#include "TList.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TMessage.h"

using namespace std;

// special class to expose protected TMessage constructor
class TransTMessage : public TMessage
{
  public:
  TransTMessage(void* buf, Int_t len)
    : TMessage(buf, len)
  {
    ResetBit(kIsOwner);
  }
};

FairMQTransportDevice::FairMQTransportDevice()
  : FairMQRunDevice()
  , fTransportDeviceId(0)
  , fGeneratorChannelName("simIn")
  , fRunSim(NULL)
  , fNofEvents(1)
  , fTransportName("TGeant3")
  , fMaterialsFile("")
  , fMagneticField(NULL)
  , fDetectorArray(NULL)
  , fStoreTrajFlag(false)
  , fTaskArray(NULL)
  , fFirstParameter(NULL)
  , fSecondParameter(NULL)
  , fSink(NULL)
  , fVMC(NULL)
  , fStack(NULL)
  , fMCApplication(NULL)
{
}

void FairMQTransportDevice::Init()
{
    OnData(fGeneratorChannelName, &FairMQTransportDevice::TransportData);
}

void FairMQTransportDevice::InitTask() 
{
  fRunSim = new FairRunSim();

  fRunSim->SetSink(fSink);

  if ( fFirstParameter || fSecondParameter ) {
    FairRuntimeDb *rtdb=fRunSim->GetRuntimeDb();
    if ( fFirstParameter )
      rtdb->setFirstInput(fFirstParameter);
    if ( fSecondParameter )
      rtdb->setSecondInput(fSecondParameter);
  }

  fRunSim->SetName(fTransportName.data());

  if ( fUserConfig.Length() > 0 )
    fRunSim->SetUserConfig(fUserConfig);
  if ( fUserCuts.Length() > 0 )
    fRunSim->SetUserCuts(fUserCuts);
  // ------------------------------------------------------------------------

  // -----   Create media   -------------------------------------------------
  fRunSim->SetMaterials(fMaterialsFile.data());
  // ------------------------------------------------------------------------
  
  // -----   Magnetic field   -------------------------------------------
  if ( fMagneticField )
    fRunSim->SetField(fMagneticField);
  // --------------------------------------------------------------------

  // -----   Create geometry   ----------------------------------------------
  for ( int idet = 0 ; idet < fDetectorArray->GetEntries() ; idet++ ) {
    fRunSim->AddModule((FairModule*)(fDetectorArray->At(idet)));
  }
  // ------------------------------------------------------------------------

  // -----   Negotiate the run number   -------------------------------------
  // -----      via the fUpdateChannelName   --------------------------------
  // -----      ask the fParamMQServer   ------------------------------------
  // -----      receive the run number and sampler id   ---------------------
  std::string* askForRunNumber = new string("ReportSimDevice");
  FairMQMessagePtr req(NewMessage(const_cast<char*>(askForRunNumber->c_str()),
                                  askForRunNumber->length(),
                                  [](void* /*data*/, void* object) { delete static_cast<string*>(object); },
                                  askForRunNumber));
  std::unique_ptr<FairMQMessage> rep(NewMessage());

  unsigned int runId = 0;
  if (Send(req, fUpdateChannelName) > 0)
      {
          if (Receive(rep, fUpdateChannelName) > 0)
              {
                  std::string repString = string(static_cast<char*>(rep->GetData()), rep->GetSize());
                  LOG(INFO) << " -> " << repString.data();
                  runId = stoi(repString);
                  repString = repString.substr(repString.find_first_of('_')+1,repString.length());
                  fTransportDeviceId = stoi(repString);
                  LOG(INFO) << "runId = " << runId << "  ///  fTransportDeviceId = " << fTransportDeviceId;
              }
      }
  // ------------------------------------------------------------------------

  fRunSim->SetStoreTraj(fStoreTrajFlag);

  // -----   Set tasks   ----------------------------------------------------
  if ( fTaskArray ) {
    for ( int itask = 0 ; itask < fTaskArray->GetEntries() ; itask++ ) {
      fRunSim->AddTask((FairTask*)(fTaskArray->At(itask)));
    }
  }
  // ------------------------------------------------------------------------

  // -----   Initialize simulation run   ------------------------------------
  fRunSim->SetRunId(runId); // run n simulations with same run id - offset the event number
  fRunSim->Init();
  // ------------------------------------------------------------------------
  
  fVMC           = TVirtualMC::GetMC();
  fMCApplication = FairMCApplication::Instance();
  fStack         = fMCApplication->GetStack();
  fStack->Register();
  //  fRunSim->Run(0);
}

void FairMQTransportDevice::PreRun()
{
}

bool FairMQTransportDevice::TransportData(FairMQMessagePtr& mPtr, int /*index*/)
{
    auto message = new TransTMessage(mPtr->GetData(), mPtr->GetSize());
    auto chunk = static_cast<TClonesArray*>(message->ReadObjectAny(message->GetClass()));

    fStack->SetParticleArray(chunk);
    fVMC->ProcessRun(1);

    return true;
}

void FairMQTransportDevice::UpdateParameterServer()
{
  FairRuntimeDb* rtdb = fRunSim->GetRuntimeDb();
  
  printf("FairMQTransportDevice::UpdateParameterServer() (%d containers)\n",rtdb->getListOfContainers()->GetEntries());

  // send the parameters to be saved
  TIter next(rtdb->getListOfContainers());
  FairParSet* cont;
  while ((cont=static_cast<FairParSet*>(next())))
    {
      std::string ridString = std::string("RUNID") + std::to_string(fRunSim->GetRunId()) + std::string("RUNID") + std::string(cont->getDescription());
      cont->setDescription(ridString.data());
      SendObject(cont,fUpdateChannelName);
    }

  printf("FairMQTransportDevice::UpdateParameterServer() finished\n");
}

void FairMQTransportDevice::PostRun()
{
}

FairMQTransportDevice::~FairMQTransportDevice()
{
}

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQSimDevice.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairMQSimDevice.h"
  
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "FairMQProgOptions.h"

#include "FairOnlineSink.h"

#include "FairMCEventHeader.h"
#include "FairRootManager.h"
#include "FairRunSim.h"
#include "FairRuntimeDb.h"

#include "FairEventHeader.h"
#include "FairModule.h"
#include "FairPrimaryGenerator.h"
#include "FairParRootFileIo.h"
#include "FairParSet.h"

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
class SimMQTMessage : public TMessage
{
  public:
  SimMQTMessage(void* buf, Int_t len)
    : TMessage(buf, len)
  {
    ResetBit(kIsOwner);
  }
};

FairMQSimDevice::FairMQSimDevice()
  : FairMQDevice()
  , fSimDeviceId(0)
  , fUpdateChannelName("updateChannel")
  , fRunSim(NULL)
  , fNofEvents(1)
  , fTransportName("TGeant3")
  , fMaterialsFile("")
  , fMagneticField(NULL)
  , fDetectorArray(NULL)
  , fPrimaryGenerator(NULL)
  , fStoreTrajFlag(false)
  , fTaskArray(NULL)
  , fFirstParameter(NULL)
  , fSecondParameter(NULL)
  , fSink(NULL)
{
}

void FairMQSimDevice::InitTask() 
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
                  fSimDeviceId = stoi(repString);
                  LOG(INFO) << "runId = " << runId << "  ///  fSimDeviceId = " << fSimDeviceId;
              }
      }
  // ------------------------------------------------------------------------

  // ------------------------------------------------------------------------
  if ( fPrimaryGenerator )
      {
          fPrimaryGenerator->SetEventNr(fSimDeviceId*fNofEvents); // run n simulations with same run id - offset the event number
          fRunSim->SetGenerator(fPrimaryGenerator);
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

}

void FairMQSimDevice::PreRun()
{
}

bool FairMQSimDevice::ConditionalRun()
{
    if ( fSimDeviceId == 0 )
        UpdateParameterServer();
    fRunSim->Run(fNofEvents);
    return false;
}

void FairMQSimDevice::UpdateParameterServer()
{
  FairRuntimeDb* rtdb = fRunSim->GetRuntimeDb();
  
  printf("FairMQSimDevice::UpdateParameterServer() (%d containers)\n",rtdb->getListOfContainers()->GetEntries());

  // send the parameters to be saved
  TIter next(rtdb->getListOfContainers());
  FairParSet* cont;
  while ((cont=static_cast<FairParSet*>(next())))
    {
      std::string ridString = std::string("RUNID") + std::to_string(fRunSim->GetRunId()) + std::string("RUNID") + std::string(cont->getDescription());
      cont->setDescription(ridString.data());
      SendObject(cont,fUpdateChannelName);
    }

  printf("FairMQSimDevice::UpdateParameterServer() finished\n");
}

void FairMQSimDevice::SendObject(TObject* obj, std::string chan) {
  TMessage* tmsg = new TMessage(kMESS_OBJECT);
  tmsg->WriteObject(obj);

  FairMQMessagePtr mess(NewMessage(tmsg->Buffer(),
                                   tmsg->BufferSize(),
                                   [](void* /*data*/, void* object){ delete static_cast<TMessage*>(object); },
                                   tmsg));
  std::unique_ptr<FairMQMessage> rep(NewMessage());
  
  printf ("sending %s",obj->GetName());
  if (Send(mess, chan) > 0)
    {
      if (Receive(rep, chan) > 0)
        {
          std::string repString = string(static_cast<char*>(rep->GetData()), rep->GetSize());
          LOG(INFO) << " -> " << repString.data();
        }
    }
}

void FairMQSimDevice::PostRun()
{
}

FairMQSimDevice::~FairMQSimDevice()
{
}

void  FairMQSimDevice::SendBranches()
{
  /// Fill the Root tree.
  LOG(DEBUG) << "called FairMQSimDevice::SendBranches()!!!!";
  if ( !CheckCurrentState(RUNNING) )
    {
      fRunSim->StopMCRun();
    }

  TList* branchNameList = FairRootManager::Instance()->GetBranchNameList();
  TObjString* ObjStr;
  
  for (auto& mi : fChannels)
    {
      LOG(DEBUG) << "trying channel >" << mi.first.data() << "<";

      FairMQParts parts;
      
      for(Int_t t=0; t<branchNameList->GetEntries(); t++) 
        {
          ObjStr= static_cast<TObjString*>(branchNameList->TList::At(t));
          LOG(DEBUG) << "              branch >" << ObjStr->GetString().Data() << "<";
          std::string modifiedBranchName = std::string("#") + ObjStr->GetString().Data() + "#";
          if ( mi.first.find(modifiedBranchName) != std::string::npos || mi.first.find("#all#") != std::string::npos ) 
            {
              TObject* object   = (FairRootManager::Instance()->GetObject(ObjStr->GetString()))->Clone();
              TMessage* message = new TMessage(kMESS_OBJECT);
              message->WriteObject(object);
              parts.AddPart(NewMessage(message->Buffer(),
                                       message->BufferSize(),                        
                                       [](void* /*data*/, void* hint) { delete (TMessage*)hint;},
                                       message));
              LOG(DEBUG) << "channel >" << mi.first.data() << "< --> >" << ObjStr->GetString().Data() << "<";
            }
        }
      if ( parts.Size() > 0 )
        Send(parts,mi.first.data());
    }
}

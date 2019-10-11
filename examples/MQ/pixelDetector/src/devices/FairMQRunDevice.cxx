/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQRunDevice.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairMQRunDevice.h"
  
#include "FairMQLogger.h"
#include "FairMQMessage.h"

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

#include <TROOT.h>
#include <TRint.h>
#include <TVirtualMC.h>
#include <TVirtualMCApplication.h>
#include <TList.h>
#include <TObjString.h>
#include <TObjArray.h>
#include "RootSerializer.h"

using namespace std;

FairMQRunDevice::FairMQRunDevice()
  : FairMQDevice()
{
}

void FairMQRunDevice::SendObject(TObject* obj, std::string chan) {
  FairMQMessagePtr mess(NewMessage());
  Serialize<RootSerializer>(*mess,obj);

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

FairMQRunDevice::~FairMQRunDevice()
{
}

void  FairMQRunDevice::SendBranches()
{
  /// Fill the Root tree.
  LOG(DEBUG) << "called FairMQRunDevice::SendBranches()!!!!";

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
              FairMQMessagePtr mess(NewMessage());
              Serialize<RootSerializer>(*mess,object);
              parts.AddPart(std::move(mess));
              LOG(DEBUG) << "channel >" << mi.first.data() << "< --> >" << ObjStr->GetString().Data() << "<";
            }
        }
      if ( parts.Size() > 0 )
        Send(parts,mi.first.data());
    }
}

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

#include "FairRootManager.h"
#include "RootSerializer.h"

#include <FairMQLogger.h>
#include <FairMQMessage.h>

#include <TList.h>
#include <TObjString.h>
#include <Rtypes.h>

#include <cstdio> // printf

using namespace std;

void FairMQRunDevice::SendObject(TObject* obj, const std::string& chan) {
  FairMQMessagePtr mess(NewMessage());
  Serialize<RootSerializer>(*mess, obj);

  FairMQMessagePtr rep(NewMessage());

  printf("sending %s",obj->GetName());
  if (Send(mess, chan) > 0) {
    if (Receive(rep, chan) > 0) {
      std::string repString = string(static_cast<char*>(rep->GetData()), rep->GetSize());
      LOG(info) << " -> " << repString.data();
    }
  }
}

void FairMQRunDevice::SendBranches()
{
  /// Fill the Root tree.
  LOG(debug) << "called FairMQRunDevice::SendBranches()!!!!";

  TList* branchNameList = FairRootManager::Instance()->GetBranchNameList();
  TObjString* ObjStr;

  for (auto& mi : fChannels) {
    LOG(debug) << "trying channel >" << mi.first.data() << "<";

    FairMQParts parts;

    for(Int_t t = 0; t < branchNameList->GetEntries(); t++) {
      ObjStr = static_cast<TObjString*>(branchNameList->TList::At(t));
      LOG(debug) << "              branch >" << ObjStr->GetString().Data() << "<";
      std::string modifiedBranchName = std::string("#") + ObjStr->GetString().Data() + "#";
      if (mi.first.find(modifiedBranchName) != std::string::npos || mi.first.find("#all#") != std::string::npos) {
        TObject* object = (FairRootManager::Instance()->GetObject(ObjStr->GetString()))->Clone();
        FairMQMessagePtr mess(NewMessage());
        Serialize<RootSerializer>(*mess, object);
        parts.AddPart(std::move(mess));
        LOG(debug) << "channel >" << mi.first.data() << "< --> >" << ObjStr->GetString().Data() << "<";
      }
    }
    if (parts.Size() > 0)
      Send(parts, mi.first.data());
  }
}

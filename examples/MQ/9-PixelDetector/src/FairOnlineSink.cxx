/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairOnlineSink.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairOnlineSink.h"
  
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "FairMQProgOptions.h"

#include "FairMQSimDevice.h"
#include "FairRootManager.h"

#include "FairEventHeader.h"
#include "FairModule.h"
#include "FairPrimaryGenerator.h"
#include "FairParRootFileIo.h"
#include "FairParSet.h"

#include "FairMCEventHeader.h"

#include "TROOT.h"
#include "TRint.h"
#include "TVirtualMC.h"
#include "TVirtualMCApplication.h"
#include "TList.h"
#include "TObjString.h"
#include "TObjArray.h"
#include "TMessage.h"

using namespace std;

FairOnlineSink::FairOnlineSink()
  : FairSink()
  , fMQSimDevice(NULL)
{
}

FairOnlineSink::~FairOnlineSink()
{
}

//_____________________________________________________________________________
void FairOnlineSink::RegisterImpl(const char* , const char* , void* )
{
  return;
}

//_____________________________________________________________________________
void FairOnlineSink::RegisterAny(const char* brname, const std::type_info &oi, const std::type_info &pi, void* obj)
{
  return;
}

void  FairOnlineSink::Fill()
{
  /// Fill the Root tree.
  LOG(DEBUG) << "called FairOnlineSink::Fill()!!!!";
  
  if ( fMQSimDevice )
      fMQSimDevice->SendBranches();
}
 
Bool_t FairOnlineSink::InitSink()
{
    return kTRUE;
}

void  FairOnlineSink::Reset()
{
}

void  FairOnlineSink::Close()
{
}

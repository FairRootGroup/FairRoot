/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMQPrimaryGeneratorDevice.cxx
 *
 * @since 2017.10.24
 * @author R. Karabowicz
 */

#include "FairMQPrimaryGeneratorDevice.h"
  
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "FairMQProgOptions.h"

#include "FairMCEventHeader.h"
#include "FairRootManager.h"
#include "FairRunSim.h"
#include "FairRuntimeDb.h"

#include "FairEventHeader.h"
#include "FairModule.h"
#include "FairPrimaryGenerator.h"
#include "FairParRootFileIo.h"
#include "FairParSet.h"
#include "FairStack.h"

#include "RootSerializer.h"

#include "TROOT.h"
#include "TRint.h"
#include "TVirtualMC.h"
#include "TVirtualMCApplication.h"
#include "TList.h"
#include "TObjString.h"
#include "TObjArray.h"

using namespace std;

FairMQPrimaryGeneratorDevice::FairMQPrimaryGeneratorDevice()
  : FairMQDevice()
  , fRunConditional(true)
  , fGeneratorChannelName("primariesChannel")
  , fEventCounter(0)
  , fNofEvents(10)
  , fPrimaryGenerator(NULL)
  , fMCEventHeader(NULL)
  , fStack(NULL)
{
}

void FairMQPrimaryGeneratorDevice::InitTask() 
{
    fStack = new FairStack();
    fMCEventHeader = new FairMCEventHeader();
    fPrimaryGenerator->SetEvent(fMCEventHeader);
    fPrimaryGenerator->Init();

    if ( !fRunConditional )
        OnData(fGeneratorChannelName, &FairMQPrimaryGeneratorDevice::Reply);
}

void FairMQPrimaryGeneratorDevice::PreRun()
{
}

bool FairMQPrimaryGeneratorDevice::ConditionalRun()
{
    if ( !fRunConditional ) return false;
    return GenerateAndSendData();
}

bool FairMQPrimaryGeneratorDevice::Reply(FairMQMessagePtr& mPtr, int /*index*/)
{
    return GenerateAndSendData();
}

bool FairMQPrimaryGeneratorDevice::GenerateAndSendData() {
    fStack->Reset();
    fPrimaryGenerator->GenerateEvent(fStack);

    TClonesArray* prims = fStack->GetListOfParticles();

    FairMQMessagePtr mess(NewMessage());
    Serialize<RootSerializer>(*mess,prims);

    if (Send(mess, fGeneratorChannelName) > 0)
        {
        }

    int numberofparts = (int)prims->GetEntries();

    fEventCounter++;

    if ( fEventCounter >= fNofEvents )
        return false;

    return true;
}

void FairMQPrimaryGeneratorDevice::PostRun()
{
}

FairMQPrimaryGeneratorDevice::~FairMQPrimaryGeneratorDevice()
{
}

void  FairMQPrimaryGeneratorDevice::SendPrimaries()
{
}

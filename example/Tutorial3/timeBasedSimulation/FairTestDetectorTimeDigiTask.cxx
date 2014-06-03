/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorTimeDigiTask.h"

#include "FairLink.h"             // for FairLink
#include "FairRootManager.h"      // for FairRootManager
#include "FairTestDetectorDigi.h" // for FairTestDetectorDigi
#include "FairTestDetectorDigiWriteoutBuffer.h"
#include "FairTestDetectorPoint.h" // for FairTestDetectorPoint

#include "Riosfwd.h"      // for ostream
#include "TClonesArray.h" // for TClonesArray
#include "TMath.h"        // for Sqrt
#include "TRandom.h"      // for TRandom, gRandom
#include "TString.h"      // for TString

#include <stddef.h> // for NULL
#include <iostream> // for operator<<, basic_ostream, etc

using namespace std;

// -----   Default constructor   -------------------------------------------
FairTestDetectorTimeDigiTask::FairTestDetectorTimeDigiTask()
    : FairTask()
    , fTimeResolution(100.)
    , fPointArray(NULL)
    , fDigiArray(NULL)
    , fDataBuffer(NULL)
    , fTimeOrderedDigi(kFALSE)
{
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTestDetectorTimeDigiTask::~FairTestDetectorTimeDigiTask()
{
}
// -------------------------------------------------------------------------

// -----   Public method Init (abstract in base class)  --------------------
InitStatus FairTestDetectorTimeDigiTask::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman)
    {
        std::cout << "-E- FairTestDetectorTimeDigiTask::Init: " /// todo replace with logger!
                  << "RootManager not instantiated!" << std::endl;
        return kFATAL;
    }

    fPointArray = (TClonesArray*)ioman->GetObject("FairTestDetectorPoint");
    if (!fPointArray)
    {
        std::cout << "-W- FairTestDetectorTimeDigiTask::Init: "
                  << "No Point array!" << std::endl;
        return kERROR;
    }

    // Create and register output array
    fDataBuffer = new FairTestDetectorDigiWriteoutBuffer("FairTestDetectorDigi", "TOY", kTRUE);
    fDataBuffer = (FairTestDetectorDigiWriteoutBuffer*)ioman->RegisterWriteoutBuffer("FairTestDetectorDigi", fDataBuffer);
    fDataBuffer->ActivateBuffering(fTimeOrderedDigi);

    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FairTestDetectorTimeDigiTask::Exec(Option_t* opt)
{

    // fDigiArray->Delete();

    // fill the map

    std::cout << "EventTime: " << FairRootManager::Instance()->GetEventTime() << std::endl;

    for (int ipnt = 0; ipnt < fPointArray->GetEntries(); ipnt++)
    {
        FairTestDetectorPoint* point = (FairTestDetectorPoint*)fPointArray->At(ipnt);
        if (!point)
        {
            continue;
        }

        Int_t xPad = CalcPad(point->GetX(), point->GetXOut());
        Int_t yPad = CalcPad(point->GetY(), point->GetYOut());
        Int_t zPad = CalcPad(point->GetZ(), point->GetZOut());

        Double_t timestamp = CalcTimeStamp(point->GetTime());

        FairTestDetectorDigi* digi = new FairTestDetectorDigi(xPad, yPad, zPad, timestamp);
        if (fTimeResolution > 0)
        {
            digi->SetTimeStampError(fTimeResolution / TMath::Sqrt(fTimeResolution));
        }
        else
        {
            digi->SetTimeStampError(0);
        }

        digi->SetLink(FairLink("FairTestDetectorPoint", ipnt));

        Double_t timeOfFlight = point->GetTime();
        Double_t eventTime = FairRootManager::Instance()->GetEventTime();

        fDataBuffer->FillNewData(digi, timeOfFlight + eventTime, digi->GetTimeStamp() + 10);
    }
}
// -------------------------------------------------------------------------

Int_t FairTestDetectorTimeDigiTask::CalcPad(Double_t posIn, Double_t posOut)
{
    Int_t result = (Int_t)(posIn + posOut) / 2;
    return result;
}
// -------------------------------------------------------------------------

Double_t FairTestDetectorTimeDigiTask::CalcTimeStamp(Double_t timeOfFlight)
{
    Double_t eventTime = FairRootManager::Instance()->GetEventTime();
    Double_t detectionTime = gRandom->Gaus(0, fTimeResolution);

    Double_t result = eventTime + timeOfFlight + detectionTime;

    if (result < 0)
    {
        return 0;
    }
    else
    {
        return result;
    }
}

ClassImp(FairTestDetectorTimeDigiTask)

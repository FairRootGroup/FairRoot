/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorDigiTask.h"

#include "FairLink.h"              // for FairLink
#include "FairRootManager.h"       // for FairRootManager
#include "FairTestDetectorDigi.h"  // for FairTestDetectorDigi
#include "FairTestDetectorPoint.h" // for FairTestDetectorPoint

#include "Riosfwd.h"      // for ostream
#include "TClonesArray.h" // for TClonesArray
#include "TMath.h"        // for Sqrt
#include "TRandom.h"      // for TRandom, gRandom

#include <stddef.h> // for NULL
#include <iostream> // for operator<<, basic_ostream, etc

// -----   Default constructor   -------------------------------------------
FairTestDetectorDigiTask::FairTestDetectorDigiTask()
    : FairTask("TestDetectorDigTask")
    , fTimeResolution(0.)
    , fPointArray(NULL)
    , fDigiArray(NULL)
{
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTestDetectorDigiTask::~FairTestDetectorDigiTask()
{
}
// -------------------------------------------------------------------------

// -----   Public method Init (abstract in base class)  --------------------
InitStatus FairTestDetectorDigiTask::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman)
    {
        std::cout << "-E- FairTestDetectorDigiTask::Init: " /// todo replace with logger!
                  << "RootManager not instantiated!" << std::endl;
        return kFATAL;
    }

    fPointArray = (TClonesArray*)ioman->GetObject("FairTestDetectorPoint");
    if (!fPointArray)
    {
        std::cout << "-W- FairTestDetectorDigiTask::Init: "
                  << "No Point array!" << std::endl;
        return kERROR;
    }

    // Create and register output array
    fDigiArray = new TClonesArray("FairTestDetectorDigi");
    ioman->Register("FairTestDetectorDigi", "FairTestDetector", fDigiArray, kTRUE);

    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FairTestDetectorDigiTask::Exec(Option_t* opt)
{

    fDigiArray->Delete();

    // fill the map

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

        FairTestDetectorDigi* digi = new ((*fDigiArray)[ipnt]) FairTestDetectorDigi(xPad, yPad, zPad, timestamp);
        if (fTimeResolution > 0)
        {
            digi->SetTimeStampError(fTimeResolution / TMath::Sqrt(fTimeResolution));
        }
        else
        {
            digi->SetTimeStampError(0);
        }

        digi->SetLink(FairLink("FairTestDetectorPoint", ipnt));
    }
}
// -------------------------------------------------------------------------

Int_t FairTestDetectorDigiTask::CalcPad(Double_t posIn, Double_t posOut)
{
    Int_t result = (Int_t)(posIn + posOut) / 2;
    return result;
}
// -------------------------------------------------------------------------

Double_t FairTestDetectorDigiTask::CalcTimeStamp(Double_t timeOfFlight)
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

ClassImp(FairTestDetectorDigiTask)

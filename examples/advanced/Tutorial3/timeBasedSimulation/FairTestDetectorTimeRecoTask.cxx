/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorTimeRecoTask.h"

#include "FairLink.h"               // for FairLink
#include "FairRootManager.h"        // for FairRootManager
#include "FairRunAna.h"             // for FairRunAna
#include "FairTSBufferFunctional.h" // for StopTime
#include "FairTestDetectorDigi.h"   // for FairTestDetectorDigi
#include "FairTestDetectorHit.h"    // for FairTestDetectorHit
#include "FairLogger.h"

#include "TClonesArray.h" // for TClonesArray
#include "TMath.h"        // for Sqrt
#include "TVector3.h"     // for TVector3

#include <stddef.h> // for NULL

// -----   Default constructor   -------------------------------------------
FairTestDetectorTimeRecoTask::FairTestDetectorTimeRecoTask()
    : FairTask()
    , fDigiArray(NULL)
    , fHitArray(NULL)
    , fFunctor(NULL)
{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTestDetectorTimeRecoTask::FairTestDetectorTimeRecoTask(Int_t verbose)
    : FairTask()
    , fDigiArray(NULL)
    , fHitArray(NULL)
    , fFunctor(NULL)
{
    fVerbose = verbose;
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTestDetectorTimeRecoTask::~FairTestDetectorTimeRecoTask()
{
}
// -------------------------------------------------------------------------

// -----   Public method Init (abstract in base class)  --------------------
InitStatus FairTestDetectorTimeRecoTask::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman)
    {
      LOG(ERROR) <<"FairTestDetectorTimeRecoTask::Init: "
		 << "RootManager not instantiated!" << FairLogger::endl;
        return kFATAL;
    }

    fDigiArray = static_cast<TClonesArray*>(ioman->GetObject("FairTestDetectorSortedDigi"));
    if (!fDigiArray)
    {
      LOG(WARNING) << "FairTestDetectorTimeRecoTask::Init: "
		   << "No Point array!" << FairLogger::endl;
        return kERROR;
    }

    fFunctor = new StopTime();

    // Create and register output array
    fHitArray = new TClonesArray("FairTestDetectorHit");
    ioman->Register("FairTestDetectorHit", "FairTestDetector", fHitArray, kTRUE);

    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FairTestDetectorTimeRecoTask::Exec(Option_t* /*opt*/)
{

    fHitArray->Delete();

    if (FairRunAna::Instance()->IsTimeStamp())
    {
        fDigiArray = FairRootManager::Instance()->GetData("FairTestDetectorSortedDigi", fFunctor, FairRootManager::Instance()->GetEventTime() + 200);
        //    LOG(INFO) << "EventTime: " 
        //              << FairRootManager::Instance()->GetEventTime() 
	//              << FairLogger::endl;
    }

    // fill the map

    for (int ipnt = 0; ipnt < fDigiArray->GetEntries(); ipnt++)
    {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fDigiArray->At(ipnt));
        if (!digi)
        {
	  LOG(WARNING)  << "No digi!" << FairLogger::endl;
            continue;
        }

        // Double_t timestamp = digi->GetTimeStamp();
        TVector3 pos(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
        TVector3 dpos(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));

        FairTestDetectorHit* hit = new ((*fHitArray)[ipnt]) FairTestDetectorHit(-1, -1, pos, dpos);
        hit->SetTimeStamp(digi->GetTimeStamp());
        hit->SetTimeStampError(digi->GetTimeStampError());
        hit->SetLink(FairLink("FairTestDetectorDigi", ipnt));

        fHitArray->Sort();
    }

    fDigiArray->Delete();
}
// -------------------------------------------------------------------------

ClassImp(FairTestDetectorTimeRecoTask)

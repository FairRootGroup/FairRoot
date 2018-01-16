/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorRecoTask.h"

#include "FairLink.h"             // for FairLink
#include "FairRootManager.h"      // for FairRootManager
#include "FairTestDetectorDigi.h" // for FairTestDetectorDigi
#include "FairTestDetectorHit.h"  // for FairTestDetectorHit
#include <iosfwd>                 // for ostream
#include "TClonesArray.h"         // for TClonesArray
#include "TMath.h"                // for Sqrt
#include "TVector3.h"             // for TVector3
#include <stddef.h>               // for NULL
#include <iostream>               // for operator<<, basic_ostream, etc

#include "FairMQLogger.h"

// -----   Default constructor   -------------------------------------------
FairTestDetectorRecoTask::FairTestDetectorRecoTask()
    : FairTask()
    , fDigiArray(NULL)
    , fHitArray(NULL)

{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTestDetectorRecoTask::FairTestDetectorRecoTask(Int_t verbose)
    : FairTask()
    , fDigiArray(NULL)
    , fHitArray(NULL)
{
    fVerbose = verbose;
}
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTestDetectorRecoTask::~FairTestDetectorRecoTask()
{
}
// -------------------------------------------------------------------------

// -----   Public method Init (abstract in base class)  --------------------
InitStatus FairTestDetectorRecoTask::Init()
{
    FairRootManager* ioman = FairRootManager::Instance();
    if (!ioman)
    {
        std::cout << "-E- FairTestDetectorRecoTask::Init: " /// todo replace with logger!
                  << "RootManager not instantiated!" << std::endl;
        return kFATAL;
    }

    fDigiArray = static_cast<TClonesArray*>(ioman->GetObject("FairTestDetectorDigi"));
    if (!fDigiArray)
    {
        std::cout << "-W- FairTestDetectorRecoTask::Init: "
                  << "No Point array!" << std::endl;
        return kERROR;
    }

    // Create and register output array
    fHitArray = new TClonesArray("FairTestDetectorHit");
    ioman->Register("FairTestDetectorHit", "FairTestDetector", fHitArray, kTRUE);

    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FairTestDetectorRecoTask::Exec(Option_t* /*opt*/)
{

    fHitArray->Clear();

    // fill the map

    for (int ipnt = 0; ipnt < fDigiArray->GetEntriesFast(); ipnt++)
    {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fDigiArray->At(ipnt));
        if (!digi)
            continue;

        /*
        LOG(debug) << " x= "  << digi->GetX()
                   << " y= " << digi->GetY()
                   << " z= " << digi->GetZ()
                   << " t= " << digi->GetTimeStamp();
         // */

        TVector3 pos(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
        TVector3 dpos(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));

        FairTestDetectorHit* hit = new ((*fHitArray)[ipnt]) FairTestDetectorHit(-1, -1, pos, dpos);
        if ( fStreamProcessing == kFALSE )
          hit->AddLink(FairLink(-1, FairRootManager::Instance()->GetEntryNr(), FairRootManager::Instance()->GetBranchId("FairTestDetectorDigi"), ipnt));
        hit->SetTimeStamp(digi->GetTimeStamp());
        hit->SetTimeStampError(digi->GetTimeStampError());
    }
}
// -------------------------------------------------------------------------

ClassImp(FairTestDetectorRecoTask)

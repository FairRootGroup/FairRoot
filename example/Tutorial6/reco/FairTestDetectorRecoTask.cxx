/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestDetectorRecoTask.h"

#include "FairLink.h"             // for FairLink
#include "FairRootManager.h"      // for FairRootManager
#include "FairEventHeader.h" // 
#include "FairTestDetectorDigi.h" // for FairTestDetectorDigi
#include "FairTestDetectorHit.h"  // for FairTestDetectorHit
#include "Riosfwd.h"              // for ostream
#include "TClonesArray.h"         // for TClonesArray
#include "TMath.h"                // for Sqrt
#include "TVector3.h"             // for TVector3
#include <stddef.h>               // for NULL
#include <iostream>               // for operator<<, basic_ostream, etc

#include "FairMQLogger.h"

#include "FairDbTutPar.h"
#include "FairRuntimeDb.h"
#include "FairParAsciiFileIo.h"
#include "FairParRootFileIo.h"
#include "FairParTSQLIo.h"

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

// -----   Default constructor   -------------------------------------------
FairTestDetectorRecoTask::FairTestDetectorRecoTask()
    : FairTask()
    , fEvtHeader(NULL)
    , fDigiArray(NULL)
    , fHitArray(NULL)

{
}
// -------------------------------------------------------------------------

// -----   Standard constructor   ------------------------------------------
FairTestDetectorRecoTask::FairTestDetectorRecoTask(Int_t verbose)
    : FairTask()
	, fEvtHeader(NULL)
    , fDigiArray(NULL)
    , fHitArray(NULL)
    , fRunId(0)
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
   FairRuntimeDb* db = FairRuntimeDb::instance();
   // FairRuntimeDb IO managing
   TString workdir = getenv("VMCWORKDIR"); 

   if (!db->getFirstInput() ) { 
      LOG(DEBUG) << "-W- FairTestDetectorRecoTask::Init() set Io input: "  << endl;
	  // Set the Ascii IO as first input
	 FairParAsciiFileIo* db_input =  new FairParAsciiFileIo();
	 TString filename = workdir + "/tutorial5/macros/ascii-example.par";
	 db_input->open(filename.Data(),"in");
	 db->setFirstInput(db_input); 
   }

   if (! db->getOutput() ) { 
      LOG(DEBUG) << "-W- FairTestDetectorRecoTask::Init() set Io output: "  << endl;
	  Bool_t kParameterMerged = kTRUE;
	  FairParRootFileIo* db_output = new FairParRootFileIo(kParameterMerged);
      TString filename = workdir + "/tutorial6/data/zmq_test_par.root";  
	  db_output->open(filename.Data());
	  db->setOutput(db_output);

	  // Set the SQL based IO as second input
      //FairParTSQLIo* inp2 = new FairParTSQLIo();
      //inp2->SetVerbosity(1);
	  //inp2->open();
	  //db->setSecondInput(inp2);
   }

   // Paramater managing  
   FairDbTutPar* par = (FairDbTutPar*)(db->getContainer("TUTParDefault"));
   if (par) { 
	 LOG(DEBUG) << "-I- FairTestDetectorDb init parameter for runId: "  <<  fRunId << endl;
     db->initContainers(fRunId);
     db->saveOutput();
	 LOG(DEBUG) << "-I- FairTestDetectorDb parameter initialised for runId: "  <<  fRunId << endl;
   }
    return kSUCCESS;
}

// -----   Public method Exec   --------------------------------------------
void FairTestDetectorRecoTask::Exec(Option_t* opt)
{

    fHitArray->Delete();

    // fill the map
    for (int ipnt = 0; ipnt < fDigiArray->GetEntries(); ipnt++)
    {
        FairTestDetectorDigi* digi = (FairTestDetectorDigi*)fDigiArray->At(ipnt);
        if (!digi)
            continue;

        /*   
        LOG(DEBUG) << " x= "  << digi->GetX()
                   << " y= " << digi->GetY()
                   << " z= " << digi->GetZ()
                   << " t= " << digi->GetTimeStamp();
		*/ 

        TVector3 pos(digi->GetX() + 0.5, digi->GetY() + 0.5, digi->GetZ() + 0.5);
        TVector3 dpos(1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12), 1 / TMath::Sqrt(12));

        FairTestDetectorHit* hit = new ((*fHitArray)[ipnt]) FairTestDetectorHit(-1, -1, pos, dpos);
        hit->SetTimeStamp(digi->GetTimeStamp());
        hit->SetTimeStampError(digi->GetTimeStampError());

       
  
        // hit->SetLink(FairLink("FairTestDetectorDigi", ipnt));
    }
}
// -------------------------------------------------------------------------

void FairTestDetectorRecoTask::InitWithId(Int_t rid)
{
  cout << "-I_ FairTestDetectorRecoTask::init() called !!!!" << rid << ":" << fRunId << endl; 
  if (rid != fRunId ) {
    fRunId = rid;
    cout << "-I_ FairTestDetectorRecoTask::init() called !!!!" << endl; 
	Init();
  }
}

ClassImp(FairTestDetectorRecoTask)

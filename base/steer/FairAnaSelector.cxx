/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----            FairAnaSelector source file                        -----
// -----            Created 14/10/11  by R. Karabowicz                 -----
// -----            Updated 01/02/12  by R. Karabowicz                 -----
// -------------------------------------------------------------------------

#include "FairAnaSelector.h"

#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN
#include "FairParAsciiFileIo.h"         // for FairParAsciiFileIo
#include "FairParRootFileIo.h"          // for FairParRootFileIo
#include "FairRootManager.h"            // for FairRootManager
#include "FairRunAnaProof.h"            // for FairRunAnaProof
#include "FairRuntimeDb.h"              // for FairRuntimeDb
#include "FairTask.h"                   // for FairTask

#include "Riosfwd.h"                    // for ostream
#include "TFile.h"                      // for TFile
#include "TList.h"                      // for TList
#include "TNamed.h"                     // for TNamed
#include "TObject.h"                    // for TObject
#include "TProofOutputFile.h"           // for TProofOutputFile
#include "TProofServ.h"                 // for TProofServ
#include "TSystem.h"                    // for TSystem, gSystem

#include <iomanip>                      // for setprecision, setw
#include <iostream>                     // for operator<<, basic_ostream, etc
#include <map>                          // for map
#include <utility>                      // for pair

using std::cout;
using std::cerr;
using std::endl;
using std::pair;
using std::setw;
using std::left;
using std::right;
using std::fixed;
using std::setprecision;
using std::map;

//_____________________________________________________________________________
void FairAnaSelector::Init(TTree* tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).
  if (!tree) {
    fLogger->Warning(MESSAGE_ORIGIN,"FairAnaSelect::Init(): There is no tree.");
    return;
  } else {
    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): Got tree     : \"%p\"",tree));
    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): Tree name    : \"%s\"",tree->GetName()));
    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): Tree title   : \"%s\"",tree->GetTitle()));
    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): Tree filename: \"%s\"",tree->GetCurrentFile()->GetName()));
  }

  if ( fRunAna ) {
    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Init(): Already have fRunAna.");

    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): SetInTree(%p)",tree));
    fRunAna->SetInTree(tree);
    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Init(): SetInTree done");

    FairRootManager* ioman = FairRootManager::Instance();
    ioman->OpenInTree();

    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): Containers static? %s",(fRunAna->GetContainerStatic()?"YES":"NO")));
    if ( !fRunAna->GetContainerStatic() ) {
      fRunAna->InitContainers();
    }
  } else {
    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Init(): Have to create fRunAna.");

    TString vmcPath = gSystem->Getenv("VMCWORKDIR");

    TNamed* contStat    = (TNamed*) fInput->FindObject("FAIRRUNANA_fContainerStatic");
    TNamed* outStat     = (TNamed*) fInput->FindObject("FAIRRUNANA_fProofOutputStatus");
    TNamed* outFile     = (TNamed*) fInput->FindObject("FAIRRUNANA_fOutputFileName");
    TNamed* outDir      = (TNamed*) fInput->FindObject("FAIRRUNANA_fOutputDirectory");
    TNamed* par1Name    = (TNamed*) fInput->FindObject("FAIRRUNANA_fParInput1FName");
    TNamed* par2Name    = (TNamed*) fInput->FindObject("FAIRRUNANA_fParInput2FName");
    TString containerS  = contStat->GetTitle();
    TString outputStat  = outStat->GetTitle();
    TString par1Str     = par1Name->GetTitle();
    TString par2Str     = par2Name->GetTitle();
    TString outFileName = outFile->GetTitle();
    TString outDirName  = outDir->GetTitle();

    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): out status   : \"%s\"",outputStat.Data()));
    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): par1 file    : \"%s\"",par1Str.Data()));
    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): par2 file    : \"%s\"",par2Str.Data()));

    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): OutputFile option \"%s\" RECOGNIZED",outputStat.Data()));
    
    outFileName.Remove(outFileName.Length()-5);
    TString outputFileName = Form("%s/%s_worker_%s.root",outDirName.Data(),outFileName.Data(),gProofServ->GetOrdinal());
    
    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): output will go to file: \"%s\"",outputFileName.Data()));
    fFile = TFile::Open(outputFileName.Data(),"RECREATE");

    fRunAna = new FairRunAnaProof("RunOnProofWorker");

    fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): SetInTree(%p)",tree));
    fRunAna->SetInTree(tree);
    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Init(): SetInTree done");

    fRunAna->SetOutputFile(fFile);
    if ( containerS == "kTRUE" ) {
      fRunAna->SetContainerStatic(kTRUE);
    } else {
      fRunAna->SetContainerStatic(kFALSE);
    }

    // -----  Parameter database   --------------------------------------------
    FairRuntimeDb* rtdb = fRunAna->GetRuntimeDb();

    if ( par1Str.Contains(".root") ) {
      FairParRootFileIo* parInput1 = new FairParRootFileIo();
      parInput1->open(par1Str.Data());
      rtdb->setFirstInput (parInput1);
    }
    if ( par1Str.Contains(".par") ) {
      FairParAsciiFileIo* parInput1 = new FairParAsciiFileIo();
      parInput1->open(par1Str.Data(),"in");
      rtdb->setFirstInput (parInput1);
    }

    if ( par2Str.Contains(".root") ) {
      FairParRootFileIo* parInput2 = new FairParRootFileIo();
      parInput2->open(par2Str.Data());
      rtdb->setSecondInput(parInput2);
    }
    if ( par2Str.Contains(".par") ) {
      FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
      parInput2->open(par2Str.Data(),"in");
      rtdb->setSecondInput(parInput2);
    }

    // ------------------------------------------------------------------------

    FairTask* fairTaskList = dynamic_cast<FairTask*>(fInput->FindObject("FairTaskList"));

    if ( fairTaskList != 0 ) {
      fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Init(): FairTask = \"%p\"",fairTaskList));
      if ( 1 == 0 ) {
	fLogger->Debug(MESSAGE_ORIGIN,"FairAnaSelector::Init() FairTaskList->Print()");
	fairTaskList->Print();
	fLogger->Debug(MESSAGE_ORIGIN,"FairAnaSelector::Init() FairTaskList->ls()");
	fairTaskList->ls();
	fLogger->Debug(MESSAGE_ORIGIN,"FairAnaSelector::Init() FairTaskList finished");
      }
      fRunAna->SetTask(fairTaskList);
    }

    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Init(): vvvvv fRunAna->Init() vvvvv");
    fRunAna->Init();
    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Init(): ^^^^^ fRunAna->Init() ^^^^^");
  }

}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairAnaSelector::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.
  fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Notify()");

  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::Begin(TTree* /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Begin()");

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::SlaveBegin(TTree* tree)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::SlaveBegin(): Tree address   : \"%p\"",tree));

  // useless, because have no tree anyways in slavebegin, init will be anyways called whenever a new tree comes
  //  Init(tree);

  fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::SlaveBegin(): finishing");
}
//_____________________________________________________________________________

//_____________________________________________________________________________
Bool_t FairAnaSelector::Process(Long64_t entry)
{
  // The Process() function is called for each entry in the tree (or possibly
  // keyed object in the case of PROOF) to be processed. The entry argument
  // specifies which entry in the currently loaded tree is to be processed.
  // It can be passed to either FairAnaSelector::GetEntry() or TBranch::GetEntry()
  // to read either all or the required parts of the data. When processing
  // keyed objects with PROOF, the object is already loaded and is available
  // via the fObject pointer.
  //
  // This function should contain the "body" of the analysis. It can contain
  // simple or elaborate selection criteria, run algorithms on the data
  // of the event and typically fill histograms.
  //
  // The processing can be stopped by calling Abort().
  //
  // Use fStatus to set the return value of TTree::Process().
  //
  // The return value is currently not used.
  //  fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Process(): Proceeding to analyze event %d",entry));

  fRunAna->RunOneEvent(entry);

  //  fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::Process(): Event %d",entry));
  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  if ( !fRunAna ) {
    return;
  }

  if ( !fProofFile ) {
    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::SlaveTerminate(): Calling fRunAna->TerminateRun()");
    fRunAna->TerminateRun();
  }

  fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::SlaveTerminate(): fProofFile = \"%p\"",fProofFile));
  fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::SlaveTerminate():      fFile = \"%p\"",fFile));

  fLogger->Info(MESSAGE_ORIGIN,Form("FairAnaSelector::SlaveTerminate(): WorkingDirectory = \"%s\"",gSystem->WorkingDirectory()));
  
  if ( fProofFile ) {

    // fOutput->ls();
    // fOutput->Print();
    // fProofFile->Print();

    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::SlaveTerminate(): fOutput->Add(fProofFile);");
    fOutput->Add(fProofFile);

    //    fProofFile->Print();

    fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::SlaveTerminate(): fFile->Close();");
    fRunAna->TerminateRun();
    //    fFile->Close();
    
  }
  
  fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::SlaveTerminate(): Finishing...");
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Terminate(): fOutput->ls()");
  fOutput->ls();
  fLogger->Info(MESSAGE_ORIGIN,"FairAnaSelector::Terminate(): -------------");
}
//_____________________________________________________________________________

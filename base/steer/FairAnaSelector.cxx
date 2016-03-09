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

#include "FairFileSource.h"             // for FairFileSource
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
    LOG(WARNING) << "FairAnaSelector::Init(): There is no tree." << FairLogger::endl;
    return;
  } else {
    LOG(INFO) << "FairAnaSelector::Init(): Got tree     : \"" << tree << "\"" << FairLogger::endl;
    LOG(INFO) << "FairAnaSelector::Init(): Tree name    : \"" << tree->GetName() << "\"" << FairLogger::endl;
    LOG(INFO) << "FairAnaSelector::Init(): Tree title   : \"" << tree->GetTitle() << "\"" << FairLogger::endl;
    LOG(INFO) << "FairAnaSelector::Init(): Tree filename: \"" << tree->GetCurrentFile()->GetName() << "\"" << FairLogger::endl;
  }

  if ( fRunAna ) {
    LOG(INFO) << "FairAnaSelector::Init(): Already have fRunAna." << FairLogger::endl;

    LOG(INFO) << "FairAnaSelector::Init(): SetInTree(" << tree << ")" << FairLogger::endl;
    fProofSource->SetInTree(tree);
    LOG(INFO) << "FairAnaSelector::Init(): SetInTree done" << FairLogger::endl;

    LOG(INFO) << "FairAnaSelector::Init(): Containers static? " << (fRunAna->GetContainerStatic()?"YES":"NO") << FairLogger::endl;

    if ( !fRunAna->GetContainerStatic() ) {
      fRunAna->InitContainers();
    }
    FairRootManager::Instance()->UpdateBranches();
  } else {
    LOG(INFO) << "FairAnaSelector::Init(): Have to create fRunAna." << FairLogger::endl;

    TString vmcPath = gSystem->Getenv("VMCWORKDIR");

    TNamed* contStat    = static_cast<TNamed*>( fInput->FindObject("FAIRRUNANA_fContainerStatic") );
    TNamed* outStat     = static_cast<TNamed*>( fInput->FindObject("FAIRRUNANA_fProofOutputStatus") );
    TNamed* outFile     = static_cast<TNamed*>( fInput->FindObject("FAIRRUNANA_fOutputFileName") );
    TNamed* outDir      = static_cast<TNamed*>( fInput->FindObject("FAIRRUNANA_fOutputDirectory") );
    TNamed* par1Name    = static_cast<TNamed*>( fInput->FindObject("FAIRRUNANA_fParInput1FName") );
    TNamed* par2Name    = static_cast<TNamed*>( fInput->FindObject("FAIRRUNANA_fParInput2FName") );
    TString containerS  = contStat->GetTitle();
    TString outputStat  = outStat->GetTitle();
    TString par1Str     = par1Name->GetTitle();
    TString par2Str     = par2Name->GetTitle();
    TString outFileName = outFile->GetTitle();
    TString outDirName  = outDir->GetTitle();

    LOG(INFO) << "FairAnaSelector::Init(): out status   : \"" << outputStat.Data() << "\"" << FairLogger::endl;
    LOG(INFO) << "FairAnaSelector::Init(): par1 file    : \"" << par1Str.Data() << "\"" << FairLogger::endl;
    LOG(INFO) << "FairAnaSelector::Init(): par2 file    : \"" << par2Str.Data() << "\"" << FairLogger::endl;

    LOG(INFO) << "FairAnaSelector::Init(): OutputFile option \"" << outputStat.Data() << "\" RECOGNIZED" << FairLogger::endl;

    if ( outputStat.Contains("copy") ) {
      TString outputFileName = outFile->GetTitle();
      if ( outputFileName[0] != '/' ) {
	outputFileName = Form("%s/%s",outDir->GetTitle(),outFile->GetTitle());
      }
      outputFileName.Remove(outputFileName.Length()-5);
      outputFileName = Form("%s_worker_%s.root",outputFileName.Data(),gProofServ->GetOrdinal());
      //      outputFileName = outputFileName(outputFileName.Last('/')+1,outputFileName.Length());
      LOG(INFO) << "the file name = \"" << outputFileName.Data() << "\"" << FairLogger::endl;
      fFile = TFile::Open(outputFileName.Data(),"RECREATE");
    }
    else if ( outputStat.Contains("merge") ) {
      TString outputFileName = outFile->GetTitle();
      if ( outputFileName[0] != '/' ) {
	outputFileName = Form("%s/%s",outDir->GetTitle(),outFile->GetTitle());
      }
      outputFileName = outputFileName(outputFileName.Last('/')+1,outputFileName.Length());
      fProofFile = new TProofOutputFile(outputFileName.Data());
      if (!(fFile = fProofFile->OpenFile("RECREATE"))) {
	Warning("SlaveBegin", "problems opening file: %s/%s",
		fProofFile->GetDir(), fProofFile->GetFileName());
      }
    }

    fRunAna = new FairRunAnaProof("RunOnProofWorker");

    LOG(INFO) << "FairAnaSelector::Init(): SetInTree(" << tree << ")" << FairLogger::endl;
    fProofSource = new FairFileSource(tree->GetCurrentFile());
    fRunAna->SetSource(fProofSource);
    LOG(INFO) << "FairAnaSelector::Init(): SetInTree done" << FairLogger::endl;

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
      LOG(INFO) << "FairAnaSelector::Init(): FairTask = \"" << fairTaskList << "\"" << FairLogger::endl;
      fRunAna->SetTask(fairTaskList);
    }

    LOG(INFO) << "FairAnaSelector::Init(): vvvvv fRunAna->Init() vvvvv" << FairLogger::endl;
    fRunAna->Init();
    LOG(INFO) << "FairAnaSelector::Init(): ^^^^^ fRunAna->Init() ^^^^^" << FairLogger::endl;
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
  LOG(INFO) << "FairAnaSelector::Notify()" << FairLogger::endl;

  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::Begin(TTree* /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  LOG(INFO) << "FairAnaSelector::Begin()" << FairLogger::endl;

  fCurrentDirectory = gSystem->pwd();
  TNamed* outFile     = static_cast<TNamed*>( fInput->FindObject("FAIRRUNANA_fOutputFileName") );
  TNamed* outDir      = static_cast<TNamed*>( fInput->FindObject("FAIRRUNANA_fOutputDirectory") );

  TString outputFileName = outFile->GetTitle();
  if ( outputFileName[0] != '/' ) {
    outputFileName = Form("%s/%s",outDir->GetTitle(),outFile->GetTitle());
  }
  TString outputDir = outputFileName(0,outputFileName.Last('/')+1);
  fCurrentDirectory = gSystem->pwd();
  gSystem->cd(outputDir.Data());

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::SlaveBegin(TTree* tree)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  LOG(INFO) << "FairAnaSelector::SlaveBegin(): Tree address   : \"" << tree << "\"" << FairLogger::endl;

  // useless, because have no tree anyways in slavebegin, init will be anyways called whenever a new tree comes
  //  Init(tree);

  LOG(INFO) << "FairAnaSelector::SlaveBegin(): finishing" << FairLogger::endl;
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
  //  LOG(INFO) << "FairAnaSelector::Process(): Proceeding to analyze event " << entry << "." << FairLogger::endl;

  fRunAna->RunOneEvent(entry);

  //  LOG(INFO) << "FairAnaSelector::Process(): Event " << entry << " analyzed." << FairLogger::endl;
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
    LOG(INFO) << "FairAnaSelector::SlaveTerminate(): Calling fRunAna->TerminateRun()" << FairLogger::endl;
    fRunAna->TerminateRun();
  }

  LOG(INFO) << "FairAnaSelector::SlaveTerminate(): fProofFile = \"" << fProofFile << "\"" << FairLogger::endl;
  if ( fProofFile )
    LOG(INFO) << "FairAnaSelector::SlaveTerminate(): fProofFile = \"" << fProofFile->GetName() << "\"" << FairLogger::endl;
  LOG(INFO) << "FairAnaSelector::SlaveTerminate():      fFile = \"" << fFile << "\"" << FairLogger::endl;
  if ( fFile )
    LOG(INFO) << "FairAnaSelector::SlaveTerminate():      fFile = \"" << fFile->GetName() << "\"" << FairLogger::endl;

  LOG(INFO) << "FairAnaSelector::SlaveTerminate(): WorkingDirectory = \"" << gSystem->WorkingDirectory() << "\"" << FairLogger::endl;

  if ( fProofFile ) {
    // fOutput->ls();
    // fOutput->Print();
    // fProofFile->Print();

    LOG(INFO) << "FairAnaSelector::SlaveTerminate(): fOutput->Add(fProofFile);" << FairLogger::endl;
    fOutput->Add(fProofFile);

    //    fProofFile->Print();

    LOG(INFO) << "FairAnaSelector::SlaveTerminate(): fFile->Close();" << FairLogger::endl;
    fRunAna->TerminateRun();

    //    fFile->Close();
  }

  LOG(INFO) << "FairAnaSelector::SlaveTerminate(): Finishing..." << FairLogger::endl;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  LOG(INFO) << "FairAnaSelector::Terminate(): fOutput->ls()" << FairLogger::endl;
  gSystem->cd(fCurrentDirectory.Data());
  LOG(INFO) << "FairAnaSelector::Terminate(): -------------" << FairLogger::endl;
}
//_____________________________________________________________________________

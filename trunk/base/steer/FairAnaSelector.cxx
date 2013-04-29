// -------------------------------------------------------------------------
// -----            FairAnaSelector source file                        -----
// -----            Created 14/10/11  by R. Karabowicz                 -----
// -----            Updated 01/02/12  by R. Karabowicz                 -----
// -------------------------------------------------------------------------

#include "FairAnaSelector.h"


#include "TFile.h"
#include "TProofOutputFile.h"
#include "TH2.h"
#include "TSystem.h"
#include "TStyle.h"
#include "TCanvas.h"

#include "FairTask.h"
#include "FairRunAna.h"
#include "FairRuntimeDb.h"
#include "FairParRootFileIo.h"
#include "FairParAsciiFileIo.h"

#include <iostream>
#include <iomanip>
#include <map>

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
    cout << "-W- FairAnaSelector::Init(): There is no tree." << endl;
    return;
  } else {
    cout << "-I- FairAnaSelector::Init(): Got tree     : \"" << tree << "\"" << endl;
    cout << "-I- FairAnaSelector::Init(): Tree name    : \"" << tree->GetName() << "\"" << endl;
    cout << "-I- FairAnaSelector::Init(): Tree title   : \"" << tree->GetTitle() << "\"" << endl;
    cout << "-I- FairAnaSelector::Init(): Tree filename: \"" << tree->GetCurrentFile()->GetName() << "\"" << endl;
  }

  if ( fRunAna ) {
    cout << "-I- FairAnaSelector::Init(): Already have fRunAna." << endl;

    cout << "-I- FairAnaSelector::Init(): SetInTree(" << tree << ")" << endl;
    fRunAna->SetInTree(tree);
    cout << "-I- FairAnaSelector::Init(): SetInTree done" << endl;

    FairRootManager* ioman = FairRootManager::Instance();
    ioman->OpenInTree();

    cout << "Containers static? " << (fRunAna->GetContainerStatic()?"YES":"NO") << endl;
    if ( !fRunAna->GetContainerStatic() ) {
      fRunAna->InitContainers();
    }
  } else {
    cout << "-I- FairAnaSelector::Init(): Have to create fRunAna." << endl;

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

    cout << "-I- FairAnaSelector::Init(): out status   : \"" << outputStat.Data() << "\"" << endl;
    cout << "-I- FairAnaSelector::Init(): par1 file    : \"" << par1Str.Data() << "\"" << endl;
    cout << "-I- FairAnaSelector::Init(): par2 file    : \"" << par2Str.Data() << "\"" << endl;

    if ( outputStat != "copy" ) {
      cout << "-I- FairAnaSelector::Init(): OutputFile option \"" << outputStat.Data() << "\" not yet supported, will \"copy\" anyways" << endl;
    }

    cout << "-I- FairAnaSelector::Init(): OutputFile option \"" << outputStat.Data() << "\" RECOGNIZED" << endl;

    cout << "-I- FairAnaSelector::Init(): gSystem->WorkingDirectory() = \""
         << gSystem->WorkingDirectory() << "\"" << endl;
    TString workDir = gSystem->WorkingDirectory();

    Int_t workerNumber = -1; // is there better way to get it?

    for ( Int_t iposWork = 0 ; iposWork < 100 ; iposWork++ ) {
      TString tempStr = Form("-0.%d",iposWork);
      if ( workDir.Contains(tempStr.Data()) ) {
        workerNumber = iposWork;
        break;
      }
    }
    if ( workerNumber == -1 ) {
      cout << "-E- FairAnaSelector::Init(): Did not recognize worker number." << endl;
    } else {
      cout << "-I- FairAnaSelector::Init(): worker number = " << workerNumber << endl;
    }

    outFileName.Remove(outFileName.Length()-5);
    TString outputFileName = Form("%s/%s_worker_0.%d.root",outDirName.Data(),outFileName.Data(),workerNumber);

    cout << "-I- FairAnaSelector::Init(): output will go to file: \"" << outputFileName.Data() << "\"" << endl;
    fFile = TFile::Open(outputFileName.Data(),"RECREATE");

    fRunAna = new FairRunAna();
    fRunAna->SetRunOnProofWorker();

    cout << "-I- FairAnaSelector::Init(): SetInTree(" << tree << ")" << endl;
    fRunAna->SetInTree(tree);
    cout << "-I- FairAnaSelector::Init(): SetInTree done" << endl;

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
    cout << "-I- FairAnaSelector::Init(): FairTask = \"" << fairTaskList << "\"" << endl;

    if ( 1 == 0 ) {
      cout << "fairTaskList->Print()" << endl;
      fairTaskList->Print();
      cout << "fairTaskList->ls()" << endl;
      fairTaskList->ls();
      cout << "fairTaskList finished" << endl;
    }

    fRunAna->SetTask(fairTaskList);

    cout << "-I- FairAnaSelector::Init(): vvvvv fRunAna->Init() vvvvv" << endl;
    fRunAna->Init();
    cout << "-I- FairAnaSelector::Init(): ^^^^^ fRunAna->Init() ^^^^^" << endl;
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
  cout << "-I- FairAnaSelector::Notify()" << endl;

  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::Begin(TTree* /*tree*/)
{
  // The Begin() function is called at the start of the query.
  // When running with PROOF Begin() is only called on the client.
  // The tree argument is deprecated (on PROOF 0 is passed).
  cout << "-I- FairAnaSelector::Begin()" << endl;

}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::SlaveBegin(TTree* tree)
{
  // The SlaveBegin() function is called after the Begin() function.
  // When running with PROOF SlaveBegin() is called on each slave server.
  // The tree argument is deprecated (on PROOF 0 is passed).
  cout << "-I- FairAnaSelector::SlaveBegin(): Tree address   : \"" << tree << "\"" << endl;

  // useless, because have no tree anyways in slavebegin, init will be anyways called whenever a new tree comes
  //  Init(tree);

  cout << "-I- FairAnaSelector::SlaveBegin(): finishing" << endl;
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
  //  cout << "-I- FairAnaSelector::Process(): Proceeding to analyze event " << entry << "." << endl;

  fRunAna->RunOneEvent(entry);

  //  cout << "-I- FairAnaSelector::Process(): Event " << entry << " analyzed." << endl;
  return kTRUE;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::SlaveTerminate()
{
  // The SlaveTerminate() function is called after all entries or objects
  // have been processed. When running with PROOF SlaveTerminate() is called
  // on each slave server.
  if ( !fRunAna ) { return; }

  if ( !fProofFile ) {
    cout << "-I- FairAnaSelector::SlaveTerminate(): Calling fRunAna->TerminateRun()" << endl;
    fRunAna->TerminateRun();
  }

  cout << "-I- FairAnaSelector::SlaveTerminate(): fProofFile = \"" << fProofFile << "\"" << endl;
  cout << "-I- FairAnaSelector::SlaveTerminate():      fFile = \"" << fFile << "\"" << endl;

  cout << "-I- FairAnaSelector::SlaveTerminate(): WorkingDirectory = \"" << gSystem->WorkingDirectory() << "\"" << endl;

  if ( fProofFile ) {

    cout << "-------------------------------- fOutput->ls()" << endl;
    fOutput->ls();
    cout << "-------------------------------- fOutput->Print()" << endl;
    fOutput->Print();
    cout << "-------------------------------- fProofFile->Print()" << endl;
    fProofFile->Print();
    cout << "--------------------------------" << endl;

    cout << "-I- FairAnaSelector::SlaveTerminate(): fOutput->Add(fProofFile);" << endl;
    fOutput->Add(fProofFile);

    cout << "-------------------------------- fProofFile->Print()" << endl;
    fProofFile->Print();
    cout << "--------------------------------" << endl;

    cout << "-I- FairAnaSelector::SlaveTerminate(): fFile->Close();" << endl;
    fRunAna->TerminateRun();
    //    fFile->Close();

  }

  cout << "-I- FairAnaSelector::SlaveTerminate(): Finishing..." << endl;
}
//_____________________________________________________________________________

//_____________________________________________________________________________
void FairAnaSelector::Terminate()
{
  // The Terminate() function is the last function to be called during
  // a query. It always runs on the client, it can be used to present
  // the results graphically or save the results to file.
  cout << "-I- FairAnaSelector::Terminate(): fOutput->ls()" << endl;
  fOutput->ls();
  cout << "-I- FairAnaSelector::Terminate(): -------------" << endl;
}
//_____________________________________________________________________________

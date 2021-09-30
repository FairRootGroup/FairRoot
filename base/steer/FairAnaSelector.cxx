/********************************************************************************
 * Copyright (C) 2014-2021 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----            FairAnaSelector source file                        -----
// -----            Created 14/10/11  by R. Karabowicz                 -----
// -----            Updated 01/02/12  by R. Karabowicz                 -----
// -------------------------------------------------------------------------

#include "FairAnaSelector.h"

#include "FairConfig.h"           // for FairConfig
#include "FairFileSource.h"       // for FairFileSource
#include "FairLogger.h"           // for FairLogger, MESSAGE_ORIGIN
#include "FairParAsciiFileIo.h"   // for FairParAsciiFileIo
#include "FairParRootFileIo.h"    // for FairParRootFileIo
#include "FairRootFileSink.h"     // for FairRootFileSink
#include "FairRootManager.h"      // for FairRootManager
#include "FairRunAnaProof.h"      // for FairRunAnaProof
#include "FairRuntimeDb.h"        // for FairRuntimeDb
#include "FairTask.h"             // for FairTask

#include <TFile.h>              // for TFile
#include <TList.h>              // for TList
#include <TNamed.h>             // for TNamed
#include <TObject.h>            // for TObject
#include <TProofOutputFile.h>   // for TProofOutputFile
#include <TProofServ.h>         // for TProofServ
#include <TSystem.h>            // for TSystem, gSystem

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
        LOG(warn) << "FairAnaSelector::Init(): There is no tree.";
        return;
    } else {
        LOG(info) << "FairAnaSelector::Init(): Got tree     : \"" << tree << "\"";
        LOG(info) << "FairAnaSelector::Init(): Tree name    : \"" << tree->GetName() << "\"";
        LOG(info) << "FairAnaSelector::Init(): Tree title   : \"" << tree->GetTitle() << "\"";
        LOG(info) << "FairAnaSelector::Init(): Tree filename: \"" << tree->GetCurrentFile()->GetName() << "\"";
    }

    if (fRunAna) {
        LOG(info) << "FairAnaSelector::Init(): Already have fRunAna.";

        LOG(info) << "FairAnaSelector::Init(): SetInTree(" << tree << ")";
        fProofSource->SetInTree(tree);
        LOG(info) << "FairAnaSelector::Init(): SetInTree done";

        LOG(info) << "FairAnaSelector::Init(): Containers static? " << (fRunAna->GetContainerStatic() ? "YES" : "NO");

        if (!fRunAna->GetContainerStatic()) {
            fRunAna->InitContainers();
        }
        FairRootManager::Instance()->UpdateBranches();
    } else {
        LOG(info) << "FairAnaSelector::Init(): Have to create fRunAna.";

        const auto vmcPath = FairConfig::Instance().GetVMCWorkDir();

        TNamed* contStat = static_cast<TNamed*>(fInput->FindObject("FAIRRUNANA_fContainerStatic"));
        TNamed* outStat = static_cast<TNamed*>(fInput->FindObject("FAIRRUNANA_fProofOutputStatus"));
        TNamed* outFile = static_cast<TNamed*>(fInput->FindObject("FAIRRUNANA_fOutputFileName"));
        TNamed* outDir = static_cast<TNamed*>(fInput->FindObject("FAIRRUNANA_fOutputDirectory"));
        TNamed* par1Name = static_cast<TNamed*>(fInput->FindObject("FAIRRUNANA_fParInput1FName"));
        TNamed* par2Name = static_cast<TNamed*>(fInput->FindObject("FAIRRUNANA_fParInput2FName"));
        TString containerS = contStat->GetTitle();
        TString outputStat = outStat->GetTitle();
        TString par1Str = par1Name->GetTitle();
        TString par2Str = par2Name->GetTitle();
        TString outFileName = outFile->GetTitle();
        TString outDirName = outDir->GetTitle();

        LOG(info) << "FairAnaSelector::Init(): out status   : \"" << outputStat.Data() << "\"";
        LOG(info) << "FairAnaSelector::Init(): par1 file    : \"" << par1Str.Data() << "\"";
        LOG(info) << "FairAnaSelector::Init(): par2 file    : \"" << par2Str.Data() << "\"";

        LOG(info) << "FairAnaSelector::Init(): OutputFile option \"" << outputStat.Data() << "\" RECOGNIZED";

        if (outputStat.Contains("copy")) {
            TString outputFileName = outFile->GetTitle();
            if (outputFileName[0] != '/') {
                outputFileName = Form("%s/%s", outDir->GetTitle(), outFile->GetTitle());
            }
            outputFileName.Remove(outputFileName.Length() - 5);
            outputFileName = Form("%s_worker_%s.root", outputFileName.Data(), gProofServ->GetOrdinal());
            //      outputFileName = outputFileName(outputFileName.Last('/')+1,outputFileName.Length());
            LOG(info) << "the file name = \"" << outputFileName.Data() << "\"";
            fFile = TFile::Open(outputFileName.Data(), "RECREATE");
        } else if (outputStat.Contains("merge")) {
            TString outputFileName = outFile->GetTitle();
            if (outputFileName[0] != '/') {
                outputFileName = Form("%s/%s", outDir->GetTitle(), outFile->GetTitle());
            }
            //      outputFileName = outputFileName(outputFileName.Last('/')+1,outputFileName.Length());
            fProofFile = new TProofOutputFile(outputFileName.Data());
            if (!(fFile = fProofFile->OpenFile("RECREATE"))) {
                Warning("SlaveBegin", "problems opening file: %s/%s", fProofFile->GetDir(), fProofFile->GetFileName());
            }
        }

        fRunAna = new FairRunAnaProof("RunOnProofWorker");

        LOG(info) << "FairAnaSelector::Init(): SetInTree(" << tree << ")";
        fProofSource = new FairFileSource(tree->GetCurrentFile());
        fRunAna->SetSource(fProofSource);
        LOG(info) << "FairAnaSelector::Init(): SetInTree done";

        fRunAna->SetSink(new FairRootFileSink(fFile));
        if (containerS == "kTRUE") {
            fRunAna->SetContainerStatic(kTRUE);
        } else {
            fRunAna->SetContainerStatic(kFALSE);
        }

        // -----  Parameter database   --------------------------------------------
        FairRuntimeDb* rtdb = fRunAna->GetRuntimeDb();

        if (par1Str.Contains(".root")) {
            FairParRootFileIo* parInput1 = new FairParRootFileIo();
            parInput1->open(par1Str.Data());
            rtdb->setFirstInput(parInput1);
        }
        if (par1Str.Contains(".par")) {
            FairParAsciiFileIo* parInput1 = new FairParAsciiFileIo();
            parInput1->open(par1Str.Data(), "in");
            rtdb->setFirstInput(parInput1);
        }

        if (par2Str.Contains(".root")) {
            FairParRootFileIo* parInput2 = new FairParRootFileIo();
            parInput2->open(par2Str.Data());
            rtdb->setSecondInput(parInput2);
        }
        if (par2Str.Contains(".par")) {
            FairParAsciiFileIo* parInput2 = new FairParAsciiFileIo();
            parInput2->open(par2Str.Data(), "in");
            rtdb->setSecondInput(parInput2);
        }

        // ------------------------------------------------------------------------

        FairTask* fairTaskList = dynamic_cast<FairTask*>(fInput->FindObject("FairTaskList"));

        if (fairTaskList != 0) {
            LOG(info) << "FairAnaSelector::Init(): FairTask = \"" << fairTaskList << "\"";
            fRunAna->SetTask(fairTaskList);
        }

        LOG(info) << "FairAnaSelector::Init(): vvvvv fRunAna->Init() vvvvv";
        fRunAna->Init();
        LOG(info) << "FairAnaSelector::Init(): ^^^^^ fRunAna->Init() ^^^^^";
    }
}

Bool_t FairAnaSelector::Notify()
{
    // The Notify() function is called when a new file is opened. This
    // can be either for a new TTree in a TChain or when when a new TTree
    // is started when using PROOF. It is normally not necessary to make changes
    // to the generated code, but the routine can be extended by the
    // user if needed. The return value is currently not used.
    LOG(info) << "FairAnaSelector::Notify()";

    return kTRUE;
}

void FairAnaSelector::Begin(TTree* /*tree*/)
{
    // The Begin() function is called at the start of the query.
    // When running with PROOF Begin() is only called on the client.
    // The tree argument is deprecated (on PROOF 0 is passed).
    LOG(info) << "FairAnaSelector::Begin()";

    fCurrentDirectory = gSystem->pwd();
    TNamed* outFile = static_cast<TNamed*>(fInput->FindObject("FAIRRUNANA_fOutputFileName"));
    TNamed* outDir = static_cast<TNamed*>(fInput->FindObject("FAIRRUNANA_fOutputDirectory"));

    TString outputFileName = outFile->GetTitle();
    if (outputFileName[0] != '/') {
        outputFileName = Form("%s/%s", outDir->GetTitle(), outFile->GetTitle());
    }
    TString outputDir = outputFileName(0, outputFileName.Last('/') + 1);
    fCurrentDirectory = gSystem->pwd();
    gSystem->cd(outputDir.Data());
}

void FairAnaSelector::SlaveBegin(TTree* tree)
{
    // The SlaveBegin() function is called after the Begin() function.
    // When running with PROOF SlaveBegin() is called on each slave server.
    // The tree argument is deprecated (on PROOF 0 is passed).
    LOG(info) << "FairAnaSelector::SlaveBegin(): Tree address   : \"" << tree << "\"";

    // useless, because have no tree anyways in slavebegin, init will be anyways called whenever a new tree comes
    //  Init(tree);

    LOG(info) << "FairAnaSelector::SlaveBegin(): finishing";
}

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
    //  LOG(info) << "FairAnaSelector::Process(): Proceeding to analyze event " << entry << ".";

    fRunAna->RunOneEvent(entry);

    //  LOG(info) << "FairAnaSelector::Process(): Event " << entry << " analyzed.";
    return kTRUE;
}

void FairAnaSelector::SlaveTerminate()
{
    // The SlaveTerminate() function is called after all entries or objects
    // have been processed. When running with PROOF SlaveTerminate() is called
    // on each slave server.
    if (!fRunAna) {
        return;
    }

    if (!fProofFile) {
        LOG(info) << "FairAnaSelector::SlaveTerminate(): Calling fRunAna->TerminateRun()";
        fRunAna->TerminateRun();
    }

    LOG(info) << "FairAnaSelector::SlaveTerminate(): fProofFile = \"" << fProofFile << "\"";
    if (fProofFile)
        LOG(info) << "FairAnaSelector::SlaveTerminate(): fProofFile = \"" << fProofFile->GetName() << "\"";
    LOG(info) << "FairAnaSelector::SlaveTerminate():      fFile = \"" << fFile << "\"";
    if (fFile)
        LOG(info) << "FairAnaSelector::SlaveTerminate():      fFile = \"" << fFile->GetName() << "\"";

    LOG(info) << "FairAnaSelector::SlaveTerminate(): WorkingDirectory = \"" << gSystem->WorkingDirectory() << "\"";

    if (fProofFile) {
        // fOutput->ls();
        // fOutput->Print();
        // fProofFile->Print();

        LOG(info) << "FairAnaSelector::SlaveTerminate(): fOutput->Add(fProofFile);";
        fOutput->Add(fProofFile);

        //    fProofFile->Print();

        LOG(info) << "FairAnaSelector::SlaveTerminate(): fFile->Close();";
        fRunAna->TerminateRun();

        //    fFile->Close();
    }
    LOG(info) << "FairAnaSelector::SlaveTerminate(): Finishing...";
}

void FairAnaSelector::Terminate()
{
    // The Terminate() function is the last function to be called during
    // a query. It always runs on the client, it can be used to present
    // the results graphically or save the results to file.
    LOG(info) << "FairAnaSelector::Terminate(): fOutput->ls()";
    gSystem->cd(fCurrentDirectory.Data());
    LOG(info) << "FairAnaSelector::Terminate(): -------------";
}

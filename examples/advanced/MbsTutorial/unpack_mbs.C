
void unpack_mbs()
{
    TStopwatch timer;
    timer.Start();

    // Create source with unpackers ----------------------------------------------
    TString dir = FairConfig::Instance().GetVMCWorkDir();
    TString tutdir = dir + "/advanced/MbsTutorial";

    FairLmdSource* source = new FairLmdSource();
    source->AddFile("sample_data_2.lmd");

    // NeuLAND MBS parameters -------------------------------
    Short_t type = 94;
    Short_t subType = 9400;
    Short_t procId = 12;
    Short_t subCrate = 0;
    Short_t control = 3;
    FairMBSUnpack* unpacker = new FairMBSUnpack(type, subType, procId, subCrate, control);
    source->AddUnpacker(unpacker);
    // ------------------------------------------------------

    // Create online run ---------------------------------------------------------
    FairRunOnline* run = new FairRunOnline(source);
    run->SetSink(new FairRootFileSink("output.root"));
    run->ActivateHttpServer();
    run->SetAutoFinish(kFALSE);
    // ---------------------------------------------------------------------------

    // Create analysis task ------------------------------------------------------
    FairMBSTask* task = new FairMBSTask("ExampleTask", 1);
    run->AddTask(task);
    // ---------------------------------------------------------------------------

    // Initialize ----------------------------------------------------------------
    run->Init();
    // ---------------------------------------------------------------------------

    // Runtime data base ---------------------------------------------------------
    FairRuntimeDb* rtdb = run->GetRuntimeDb();
    Bool_t kParameterMerged = kTRUE;
    FairParRootFileIo* parOut = new FairParRootFileIo(kParameterMerged);
    parOut->open("params.root");
    rtdb->setOutput(parOut);
    rtdb->print();
    // ---------------------------------------------------------------------------

    // Run -----------------------------------------------------------------------
    run->Run(0, 400);
    rtdb->saveOutput();
    // ---------------------------------------------------------------------------

    timer.Stop();
    Double_t rtime = timer.RealTime();
    Double_t ctime = timer.CpuTime();
    Int_t nHits = unpacker->GetNHitsTotal();
    if (9086 == nHits) {
        cout << endl << endl;
        cout << "Macro finished successfully." << endl;
        cout << "Real time " << rtime << " s, CPU time " << ctime << "s" << endl << endl;
    }
}

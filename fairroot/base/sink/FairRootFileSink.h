/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairRootFileSink                      -----
// -----                    Created 22.12.2017 by R. Karabowicz            -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef __FAIRROOT__FairRootFileSink__
#define __FAIRROOT__FairRootFileSink__

#include "FairSink.h"

#include <Rtypes.h>
#include <TBranch.h>
#include <TFile.h>
#include <TString.h>
#include <memory>
#include <typeinfo>

class FairEventHeader;
class FairFileHeader;

class FairRootFileSink : public FairSink
{
  public:
    FairRootFileSink(TFile* f, const char* Title = "OutputRootFile");
    FairRootFileSink(const TString* RootFileName, const char* Title = "OutputRootFile");
    FairRootFileSink(const TString RootFileName, const char* Title = "OutputRootFile");
    FairRootFileSink(const FairRootFileSink&) = delete;
    FairRootFileSink operator=(const FairRootFileSink&) = delete;
    ~FairRootFileSink() override = default;

    Bool_t InitSink() override;
    void Reset() override;

    Sink_Type GetSinkType() override { return kFILESINK; }

    virtual void FillEventHeader(FairEventHeader* feh);

    virtual TFile* OpenRootFile(TString fileName = "");
    TFile* GetRootFile() { return fRootFile.get(); }
    TString GetFileName() override { return (fRootFile ? fRootFile->GetName() : ""); }

    void SetOutTree(TTree* fTree) override { fOutTree = fTree; }
    TTree* GetOutTree() { return fOutTree; }

    void Fill() override;

    Int_t Write(const char* name = nullptr, Int_t option = 0, Int_t bufsize = 0) override;

    void RegisterImpl(const char*, const char*, void*) override;
    void RegisterAny(const char* brname, const std::type_info& oi, const std::type_info& pi, void* obj) override;

    void WriteFolder() override;
    bool CreatePersistentBranchesAny() override;

    void WriteObject(TObject* f, const char*, Int_t option = 0) override;
    void WriteGeometry() override;

    FairSink* CloneSink() override;
    void Close() override;

  private:
    /** Title of input sink, could be input, background or signal*/
    TString fOutputTitle;
    /** ROOT file */
    std::unique_ptr<TFile> fRootFile;
    /** Output Tree  */
    TTree* fOutTree{nullptr};
    /** Initialization flag, true if initialized */
    Bool_t fIsInitialized{kFALSE};

    void TruncateBranchNames();
    void TruncateBranchNames(TBranch* b, TString ffn);
    // bool CreatePersistentBranchesAny();

    /**File Header*/
    FairFileHeader* fFileHeader{nullptr};   //!

    bool fPersistentBranchesDone{false};   //!

    ClassDefOverride(FairRootFileSink, 1);
};

#endif /* defined(__FAIRROOT__FairRootFileSink__) */

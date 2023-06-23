/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARROOTFILEIO_H
#define FAIRPARROOTFILEIO_H

#include "FairParIo.h"   // for FairParIo

#include <Rtypes.h>   // for Bool_t, Text_t, Int_t, etc
#include <TFile.h>    // for TFile
#include <TNamed.h>   // for TNamed
#include <fstream>
#include <memory>

class FairRtdbRun;

class FairParRootFile : public TNamed
{
  public:
    FairParRootFile(const Text_t* fname, Option_t* option = "READ", const Text_t* ftitle = "", Int_t compress = 1);
    FairParRootFile(TFile* f);
    ~FairParRootFile() override;
    FairRtdbRun* getRun() { return run.get(); }
    void readVersions(FairRtdbRun*);

    Bool_t IsOpen() { return RootFile && (RootFile->IsOpen()); }
    void cd()
    {
        if (RootFile) {
            RootFile->cd();
        }
    }
    Bool_t IsWritable() { return RootFile && RootFile->IsWritable(); }

    TKey* GetKey(const Text_t* t)
    {
        if (RootFile) {
            return RootFile->GetKey(t);
        } else {
            return nullptr;
        }
    }
    TList* GetListOfKeys()
    {
        if (RootFile) {
            return RootFile->GetListOfKeys();
        } else {
            return nullptr;
        }
    }
    void Close()
    {
        if (RootFile) {
            RootFile->Close();
        }
    }

  protected:
    TFile* RootFile;

  private:
    std::unique_ptr<FairRtdbRun> run;   //! pointer to current run in ROOT file

    FairParRootFile(const FairParRootFile&);
    FairParRootFile& operator=(const FairParRootFile&);

    ClassDefOverride(FairParRootFile, 0);   // ROOT file for Parameter I/O
};

class FairParRootFileIo : public FairParIo
{
  protected:
    FairParRootFile* file;   // pointer to ROOT file
    Bool_t fMerging;

  public:
    FairParRootFileIo();
    FairParRootFileIo(Bool_t merged);
    ~FairParRootFileIo() override;
    Bool_t open(const Text_t* fname, Option_t* option = "READ", const Text_t* ftitle = "", Int_t compress = 1);
    Bool_t open(const TList* fnamelist, Option_t* option = "READ", const Text_t* ftitle = "", Int_t compress = 1);
    static void MergeFiles(TFile* newParFile, const TList* fnamelist);
    void close() override;
    void print() override;
    FairParRootFile* getParRootFile();
    void readVersions(FairRtdbRun*) override;
    TList* getKeys();
    Bool_t check() override
    {
        // returns kTRUE if file is open
        if (file) {
            return file->IsOpen();
        } else {
            return kFALSE;
        }
    }
    void cd() override
    {
        // sets the global ROOT file pointer gFile
        if (file) {
            file->cd();
        }
    }
    /**
    Open an existing root file for IO
    */
    Bool_t open(TFile* f);
    void setMerging(Bool_t io) { fMerging = io; }

  private:
    FairParRootFileIo(const FairParRootFileIo&);
    FairParRootFileIo& operator=(const FairParRootFileIo&);
    void ActivateSelf();

    ClassDefOverride(FairParRootFileIo, 0);   // Parameter I/O from ROOT files
};

#endif /* !FAIRPARROOTFILEIO_H */

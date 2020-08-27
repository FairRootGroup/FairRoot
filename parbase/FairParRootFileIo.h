/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
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
using std::fstream;

class FairRtdbRun;
class TKey;
class TList;

class FairParRootFile : public TNamed
{
  public:
    FairRtdbRun* run;   //! pointer to current run in ROOT file
    FairParRootFile(const Text_t* fname, Option_t* option = "READ", const Text_t* ftitle = "", Int_t compress = 1);
    FairParRootFile(TFile* f);
    ~FairParRootFile();
    FairRtdbRun* getRun() { return run; }
    void readVersions(FairRtdbRun*);

    Bool_t IsOpen() { return RootFile->IsOpen(); }
    void cd() { RootFile->cd(); }
    Bool_t IsWritable() { return RootFile->IsWritable(); }

    TKey* GetKey(Text_t* t) { return RootFile->GetKey(t); }
    TList* GetListOfKeys() { return RootFile->GetListOfKeys(); }
    void Close() { RootFile->Close(); }

  protected:
    TFile* RootFile;

  private:
    FairParRootFile(const FairParRootFile&);
    FairParRootFile& operator=(const FairParRootFile&);

    ClassDef(FairParRootFile, 0);   // ROOT file for Parameter I/O
};

class FairParRootFileIo : public FairParIo
{
  protected:
    FairParRootFile* file;   // pointer to ROOT file
    Bool_t fMerging;

  public:
    FairParRootFileIo();
    FairParRootFileIo(Bool_t merged);
    ~FairParRootFileIo();
    Bool_t open(const Text_t* fname, Option_t* option = "READ", const Text_t* ftitle = "", Int_t compress = 1);
    Bool_t open(const TList* fnamelist, Option_t* option = "READ", const Text_t* ftitle = "", Int_t compress = 1);
    void close();
    void print();
    FairParRootFile* getParRootFile();
    void readVersions(FairRtdbRun*);
    TList* getKeys();
    Bool_t check()
    {
        // returns kTRUE if file is open
        if (file) {
            return file->IsOpen();
        } else {
            return kFALSE;
        }
    }
    void cd()
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

    ClassDef(FairParRootFileIo, 0);   // Parameter I/O from ROOT files
};

#endif /* !FAIRPARROOTFILEIO_H */

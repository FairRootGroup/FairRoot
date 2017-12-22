/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//
//  FairFileSink.h
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//

#ifndef __FAIRROOT__FairFileSink__
#define __FAIRROOT__FairFileSink__

#include "FairSink.h"
#include <list>
#include "TChain.h"
#include "TFile.h"
#include "TFolder.h"
#include "TF1.h"
class FairEventHeader;
class FairFileHeader;
class FairMCEventHeader;
class TString;
class FairLogger;
class FairRuntimeDb;

class FairFileSink : public FairSink
{
public:
    FairFileSink(TFile *f, const char* Title="OutputRootFile");
    FairFileSink(const TString* RootFileName, const char* Title="OutputRootFile");
    FairFileSink(const TString RootFileName, const char* Title="OutputRootFile");
    //  FairFileSink(const FairFileSink& file);
    virtual ~FairFileSink();

    Bool_t              Init();
    void                Close();
    void                Reset();

    virtual Sink_Type GetSinkType() { return kFILESINK; }

    virtual void FillEventHeader(FairEventHeader* feh);

    const TFile*        GetRootFile(){return fRootFile;}

    virtual void        SetOutTree(TTree* fTree) { fOutTree=fTree;}

    virtual void        Fill();

    virtual Int_t       Write(const char* name=0, Int_t option=0, Int_t bufsize=0);

    virtual void RegisterImpl(const char* , const char* , void* );
    virtual void RegisterAny(const char* brname, const std::type_info &oi, const std::type_info &pi, void* obj);

    virtual void WriteFolder();
    virtual bool CreatePersistentBranchesAny();

    virtual void WriteObject(TObject* f, const char*, Int_t option = 0);
    virtual void WriteGeometry();


private:
    /** Title of input sink, could be input, background or signal*/
    TString                           fOutputTitle;
    /**ROOT file*/
    TFile*                            fRootFile;
    /**Output Tree */
    TTree*                              fOutTree;
    /** list of folders from all input (and friends) files*/
    TObjArray                           *fListFolder; //!
    /**folder structure of output*/
    TFolder*                            fCbmout;
    /**Initialization flag, true if initialized*/
    Bool_t                              fIsInitialized;

    FairFileSink(const FairFileSink&);
    FairFileSink operator=(const FairFileSink&);

    void TruncateBranchNames();
    void TruncateBranchNames(TBranch* b, TString ffn);
    //    bool CreatePersistentBranchesAny();

    /**File Header*/
    FairFileHeader*                        fFileHeader; //!

    ClassDef(FairFileSink, 1)
};


#endif /* defined(__FAIRROOT__FairFileSink__) */

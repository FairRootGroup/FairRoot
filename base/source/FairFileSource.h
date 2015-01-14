/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//
//  FairFileSource.h
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//

#ifndef __FAIRROOT__FairFileSource__
#define __FAIRROOT__FairFileSource__

#include "FairSource.h"
#include <list>    
#include "TChain.h"
#include "TFile.h"
class FairFileHeader;
class TString;
class FairLogger;
class FairRuntimeDb;
class TFolder;

class FairFileSource : public FairSource
{
public:
    FairFileSource(TFile *f, const char* Title="InputRootFile", UInt_t identifier=0);
    FairFileSource(const TString* RootFileName, const char* Title="InputRootFile", UInt_t identifier=0);
  //  FairFileSource(const FairFileSource& file);
    virtual ~FairFileSource();
    
    Bool_t              Init();
    Int_t               ReadEvent(UInt_t i=0);
    void                Close();
    void                Reset();
    const TFile*        GetRootFile(){return fRootFile;}
    /** Add a friend file (input) by name)*/
    void                AddFriend(TString FileName);
    /**Add ROOT file to input, the file will be chained to already added files*/
    void                AddFile(TString FileName);
    void                AddFriendsToChain();
    void                PrintFriendList();
    Bool_t              CompareBranchList(TFile* fileHandle, TString inputLevel);
    void                CheckFriendChains();
    void                CreateNewFriendChain(TString inputFile, TString inputLevel);
    TTree*              GetInTree() {return fInChain->GetTree();}
    TChain*             GetInChain() {return fInChain;}
    TFile*              GetInFile() {return  fRootFile;}
    void                CloseInFile() { if(fRootFile) { fRootFile->Close(); }}
    /**Set the input tree when running on PROOF worker*/
    void                SetInTree (TTree*  tempTree)  {fInTree = NULL; fInTree  = tempTree;}
    TObjArray*          GetListOfFolders(){return fListFolder;}
    TFolder*            GetBranchDescriptionFolder(){return fCbmroot;}
    UInt_t              GetEntries(){return fNoOfEntries; }

private:
    /** Title of input source, could be input, background or signal*/
    TString                           fInputTitle;
    /**ROOT file*/
    TFile*                            fRootFile;
    /**File Header*/
    FairFileHeader*                   fFileHeader; //!
    /** Current Entry number */
    Int_t                             fCurrentEntryNr;  //!
    /** FairLogger */
    FairLogger*                       fLogger;
    /** List of all files added with AddFriend */
    std::list<TString>                fFriendFileList; //!
    std::list<TString>                fInputChainList;//!
    std::map<TString, TChain*>          fFriendTypeList;//!
    std::map<TString, std::list<TString>* > fCheckInputBranches; //!
    std::list<TString>                      fInputLevel; //!
    std::map<TString, std::multimap<TString, TArrayI> > fRunIdInfoAll; //!
    /**Input Chain */
    TChain*                             fInChain;
    /**Input Tree */
    TTree*                              fInTree;
    /** list of folders from all input (and friends) files*/
    TObjArray                           *fListFolder; //!
    /**Branch id for this run */
    Int_t                               fBranchSeqId;
    /**List of branch names as TObjString*/
    TList*                              fBranchNameList; //!
    /** RuntimeDb*/
    FairRuntimeDb*           fRtdb;
    /**folder structure of output*/
    TFolder*                            fCbmout;
    /**folder structure of input*/
    TFolder*                            fCbmroot;
    /***/
    UInt_t                              fSourceIdentifier;
    /**No of Entries in this source*/
    UInt_t                              fNoOfEntries;
    /**Initialization flag, true if initialized*/
    Bool_t                              IsInitialized;
    
    FairFileSource(const FairFileSource&);
    FairFileSource operator=(const FairFileSource&);

    ClassDef(FairFileSource, 0)
};


#endif /* defined(__FAIRROOT__FairFileSource__) */

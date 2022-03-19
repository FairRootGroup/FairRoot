/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
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

#include "FairFileSourceBase.h"

#include <TArrayI.h>
#include <TChain.h>
#include <TF1.h>
#include <TFile.h>
#include <TFolder.h>
#include <TString.h>
#include <list>
#include <map>
#include <memory>

class FairEventHeader;
class FairFileHeader;
class FairMCEventHeader;
class TTree;

class FairFileSource : public FairFileSourceBase
{
  public:
    FairFileSource(TFile* f, const char* Title = "InputRootFile", UInt_t identifier = 0);
    FairFileSource(const TString* RootFileName, const char* Title = "InputRootFile", UInt_t identifier = 0);
    FairFileSource(const TString RootFileName, const char* Title = "InputRootFile", UInt_t identifier = 0);
    // FairFileSource(const FairFileSource& file);
    virtual ~FairFileSource();

    Bool_t Init() override;
    Int_t ReadEvent(UInt_t i = 0) override;
    void Close() override;
    void Reset() override;

    Source_Type GetSourceType() override { return kFILE; }

    void SetParUnpackers() override {}

    Bool_t InitUnpackers() override { return kTRUE; }

    Bool_t ReInitUnpackers() override { return kTRUE; }

    /**Check the maximum event number we can run to*/
    Int_t CheckMaxEventNo(Int_t EvtEnd = 0) override;
    /**Read the tree entry on one branch**/
    void ReadBranchEvent(const char* BrName) override;
    /**Read specific tree entry on one branch**/
    void ReadBranchEvent(const char* BrName, Int_t Entry) override;
    void FillEventHeader(FairEventHeader* feh) override;

    const TFile* GetRootFile() { return fRootFile; }
    /** Add a friend file (input) by name)*/
    void AddFriend(TString FileName);
    /**Add ROOT file to input, the file will be chained to already added files*/
    void AddFile(TString FileName);
    void AddFriendsToChain();
    void PrintFriendList();
    void CheckFriendChains();
    void CreateNewFriendChain(TString inputFile, TString inputLevel);
    TTree* GetInTree() { return fInChain->GetTree(); }
    TChain* GetInChain() { return fInChain; }
    TFile* GetInFile() { return fRootFile; }
    void CloseInFile()
    {
        if (fRootFile) {
            fRootFile->Close();
        }
    }
    /**Set the input tree when running on PROOF worker*/
    void SetInTree(TTree* tempTree);
    TObjArray* GetListOfFolders() { return fListFolder; }
    TFolder* GetBranchDescriptionFolder() { return fCbmroot; }
    UInt_t GetEntries() { return fNoOfEntries; }

    //    TList*              GetBranchNameList() {return fBranchNameList;}

    void SetInputFile(TString name);

    /** Set the repetition time of the beam when it can interact (beamTime) and when no interaction happen (gapTime).
     * The total repetition time is beamTime + gapTime */
    void SetBeamTime(Double_t beamTime, Double_t gapTime);
    /** Set the min and max limit for event time in ns */
    void SetEventTimeInterval(Double_t min, Double_t max);
    /** Set the mean time for the event in ns */
    void SetEventMeanTime(Double_t mean);
    void SetEventTime();
    Double_t GetDeltaEventTime();
    void SetFileHeader(FairFileHeader* f) { fFileHeader = f; }
    Double_t GetEventTime();

    Bool_t ActivateObject(TObject** obj, const char* BrName) override;
    Bool_t ActivateObjectAny(void**, const std::type_info&, const char*) override;

    /**Set the status of the EvtHeader
     *@param Status:  True: The header was creatged in this session and has to be filled
              FALSE: We use an existing header from previous data level
     */
    void SetEvtHeaderNew(Bool_t Status) { fEvtHeaderIsNew = Status; }
    Bool_t IsEvtHeaderNew() { return fEvtHeaderIsNew; }

    /** Allow to disable the testing the file layout when adding files to a chain.
     */
    void SetCheckFileLayout(Bool_t enable) { fCheckFileLayout = enable; }

    /**Read one event from source to find out which RunId to use*/
    Bool_t SpecifyRunId() override;

  private:
    /** Title of input source, could be input, background or signal*/
    TString fInputTitle;
    /**ROOT file*/
    TFile* fRootFile;
    /** Current Entry number */
    Int_t fCurrentEntryNr;   //!
    /** List of all files added with AddFriend */
    std::list<TString> fFriendFileList;                                 //!
    std::list<TString> fInputChainList;                                 //!
    std::map<TString, TChain*> fFriendTypeList;                         //!
    std::list<TString> fInputLevel;                                     //!
    std::map<TString, std::multimap<TString, TArrayI>> fRunIdInfoAll;   //!
    /**Input Chain */
    TChain* fInChain;
    /**Input Tree */
    TTree* fInTree;
    /** list of folders from all input (and friends) files*/
    TObjArray* fListFolder;   //!
    /**folder structure of output*/
    TFolder* fCbmout;
    /**folder structure of input*/
    TFolder* fCbmroot;
    /***/
    UInt_t fSourceIdentifier;
    /**No of Entries in this source*/
    UInt_t fNoOfEntries;
    /**Initialization flag, true if initialized*/
    Bool_t IsInitialized;

    FairFileSource(const FairFileSource&);
    FairFileSource operator=(const FairFileSource&);

    /** MC Event header */
    FairMCEventHeader* fMCHeader;   //!

    /**Event Header*/
    FairEventHeader* fEvtHeader;   //!

    /**File Header*/
    FairFileHeader* fFileHeader;   //!

    /** This is true if the event time used, came from simulation*/
    Bool_t fEventTimeInMCHeader;   //!
    /**This flag is true if the event header was created in this session
     * otherwise it is false which means the header was created in a previous data
     * level and used here (e.g. in the digi)
     */
    Bool_t fEvtHeaderIsNew;   //!

    /** for internal use, to return the same event time for the same entry*/
    UInt_t fCurrentEntryNo;   //!
    /** for internal use, to return the same event time for the same entry*/
    UInt_t fTimeforEntryNo;   //!

    /** min time for one event (ns) */
    Double_t fEventTimeMin;   //!
    /** max time for one Event (ns) */
    Double_t fEventTimeMax;   //!
    /** Time of event since th start (ns) */
    Double_t fEventTime;   //!
    /** Time of particles in beam (ns) */
    Double_t fBeamTime;   //!
    /** Time without particles in beam (gap) (ns) */
    Double_t fGapTime;   //!
    /** EventMean time used (P(t)=1/fEventMeanTime*Exp(-t/fEventMeanTime) */
    Double_t fEventMeanTime;   //!
    /** used to generate random numbers for event time; */
    std::unique_ptr<TF1> fTimeProb;   //!
    /** True if the file layout should be checked when adding files to a chain.
     *  Default value is true.
     */
    Bool_t fCheckFileLayout;   //!

    ClassDefOverride(FairFileSource, 3);
};

#endif /* defined(__FAIRROOT__FairFileSource__) */

/********************************************************************************
 * Copyright (C) 2014-2024 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//
//  FairMixedSource.h
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//

#ifndef __FAIRROOT__FairMixedSource__
#define __FAIRROOT__FairMixedSource__

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
class FairRootManager;

class FairMixedSource : public FairFileSourceBase
{
  public:
    FairMixedSource(TFile* f, const char* Title = "InputRootFile", UInt_t identifier = 0);
    FairMixedSource(const TString* RootFileName, const char* Title = "InputRootFile", UInt_t identifier = 0);
    FairMixedSource(const TString RootFileName,
                    const Int_t signalId,
                    const char* Title = "InputRootFile",
                    UInt_t identifier = 0);
    //  FairMixedSource(const FairMixedSource& file);
    ~FairMixedSource() override = default;

    Bool_t Init() override;
    Int_t ReadEvent(UInt_t i = 0) override;

    /**Check the maximum event number we can run to*/
    Int_t CheckMaxEventNo(Int_t EvtEnd = 0) override;
    /**Read the tree entry on one branch**/
    void ReadBranchEvent(const char* BrName) override;
    /** Read specific tree entry on one branch**/
    void ReadBranchEvent(const char* BrName, Int_t Entry) override;

    void FillEventHeader(FairEventHeader* feh) override;

    /** Add a friend file (input) by name)*/

    Bool_t ActivateObject(TObject** obj, const char* BrName) override;
    Bool_t ActivateObjectAny(void**, const std::type_info&, const char*) override;

    void ReadBKEvent(UInt_t i = 0);

    /**Set the input signal file
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file
     */
    void SetSignalFile(TString name, UInt_t identifier);
    /**Set the input background file by name*/
    void SetBackgroundFile(TString name);
    /**Add signal file to input
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file to which this signal should be added
     */
    void AddSignalFile(TString name, UInt_t identifier);
    void AddBackgroundFile(TString name);

    TChain* GetBGChain() { return fBackgroundChain; }
    TChain* GetSignalChainNo(UInt_t i);

    Bool_t OpenBackgroundChain();
    Bool_t OpenSignalChain();

    /**Set the signal to background ratio in event units
     *@param background :  Number of background Events for one signal
     *@param Signalid :    Signal file Id, used when adding (setting) the signal file
     */
    void BGWindowWidthNo(UInt_t background, UInt_t Signalid);
    /**Set the signal to background rate in time units
     *@param background :  Time of background Events before one signal
     *@param Signalid :    Signal file Id, used when adding (setting) the signal file
     */
    void BGWindowWidthTime(Double_t background, UInt_t Signalid);

    /** Set the min and max limit for event time in ns */
    void SetEventTimeInterval(Double_t min, Double_t max);
    /** Set the mean time for the event in ns */
    void SetEventMeanTime(Double_t mean);
    /** Set the repetition time of the beam when it can interact (beamTime) and when no interaction happen (gapTime).
     * The total repetition time is beamTime + gapTime */
    void SetBeamTime(Double_t beamTime, Double_t gapTime);
    void SetEventTime();
    Double_t GetDeltaEventTime();
    void SetFileHeader(FairFileHeader* f) { fFileHeader = f; }
    Double_t GetEventTime();

    TFolder* GetBranchDescriptionFolder() { return fCbmroot; }
    UInt_t GetEntries() { return fNoOfEntries; }

    /**Set the status of the EvtHeader
     *@param Status:  True: The header was creatged in this session and has to be filled
              FALSE: We use an existing header from previous data level
     */
    void SetEvtHeaderNew(Bool_t Status) { fEvtHeaderIsNew = Status; }
    Bool_t IsEvtHeaderNew() { return fEvtHeaderIsNew; }

    /** Use the Backgraund RunID to initialize the parameter for the run */
    void UseRunIdFromBG();
    /** Use the Backgraund RunID to initialize the parameter for the run
     *@param identifier: Signal file identifier to be used by default we take the first Signal
     */
    void UseRunIdfromSG(UInt_t identifier = 1);

  private:
    /**IO manager */
    FairRootManager* fRootManager;

    /** Title of input source, could be input, background or signal*/
    TString fInputTitle;
    /** List of all files added with AddFriend */
    std::list<TString> fFriendFileList;                                 //!
    std::list<TString> fInputChainList;                                 //!
    std::map<TString, TChain*> fFriendTypeList;                         //!
    std::list<TString> fInputLevel;                                     //!
    std::map<TString, std::multimap<TString, TArrayI>> fRunIdInfoAll;   //!
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

    /** MC Event header */
    FairMCEventHeader* fMCHeader;   //!

    /**Event Header*/
    FairEventHeader* fEvtHeader;   //!

    /**Output Event Header*/
    FairEventHeader* fOutHeader;   //!

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
    /* /\**No of entries in BG Chain*\/ */
    UInt_t fNoOfBGEntries;   //!
    /* /\**Hold the current entry for each input chain*\/ */
    std::map<UInt_t, UInt_t> fCurrentEntry;   //!

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

    /**holds the SB ratio by number*/
    std::map<UInt_t, Double_t> fSignalBGN;   //!
    /* /\**True for background window in entry units*\/ */
    Bool_t fSBRatiobyN;   //!
    /* /\**True for background window in time units (ns) *\/ */
    Bool_t fSBRatiobyT;   //!

    /**Actual identifier of the added signals, this is used to identify how many signals are added*/
    UInt_t fActualSignalIdentifier;   //!
    /** Total number of signals added (Types and not files!)*/
    UInt_t fNoOfSignals;   //!
    /** list of chains which has to be created for the different signals*/
    std::list<TString>* fSignalChainList;   //!
    /**Chain containing the background*/
    TChain* fBackgroundChain;                    //!
    std::map<UInt_t, TChain*> fSignalTypeList;   //!

    /**True if RunId is taken from Backgraund*/
    Bool_t fRunIdFromBG;   //!
    /**True if RunId is taken from Signal */
    Bool_t fRunIdFromSG;   //!
    /** Identifier of signal file for RunID
     * Zero if RunId is taken from BG.
     */
    UInt_t fRunIdFromSG_identifier;   //!

    /**Read one event from source to find out which RunId to use*/
    Bool_t SpecifyRunId() override;

    FairMixedSource(const FairMixedSource&);
    FairMixedSource& operator=(const FairMixedSource&);

  public:
    ClassDefOverride(FairMixedSource, 0);
};

#endif /* defined(__FAIRROOT__FairMixedSource__) */

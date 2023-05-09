/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNANA_H
#define FAIRRUNANA_H

#include "FairRootManager.h"   // for FairRootManager
#include "FairRun.h"           // for FairRun
#include "FairRunInfo.h"       // for FairRunInfo

#include <Rtypes.h>    // for Bool_t, Double_t, UInt_t, etc
#include <TF1.h>       //
#include <TString.h>   // for TString

class FairField;
class FairFileSource;
class FairMixedSource;

/**
 * Configure and manage the  Analysis
 * \ingroup base_steer fairroot_singleton
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */
class FairRunAna : public FairRun
{
  public:
    static FairRunAna* Instance();
    ~FairRunAna() override;
    FairRunAna();
    /**initialize the run manager*/
    void Init() override;
    /**Run from event number NStart to event number NStop */
    void Run(Int_t NStart = 0, Int_t NStop = 0) override;
    /**Run over the whole input file with timpe window delta_t as unit (entry)*/
    void Run(Double_t delta_t);
    /**Run for the given single entry*/
    void Run(Long64_t entry);
    /**Run event reconstruction from event number NStart to event number NStop */
    void RunEventReco(Int_t NStart, Int_t NStop);
    /**Run over all TSBuffers until the data is processed*/
    void RunTSBuffers();
    /** the dummy run does not check the evt header or the parameters!! */
    void DummyRun(Int_t NStart, Int_t NStop);
    /** This methode is only needed and used with ZeroMQ
     * it read a certain event and call the task exec, but no output is written
     * @param entry : entry number in the tree
     */
    void RunMQ(Long64_t entry);
    /** Run on a list of lmd files*/
    void RunOnLmdFiles(UInt_t NStart = 0, UInt_t NStop = 0);

    void RunOnTBData();
    /** finish tasks, write output*/
    void TerminateRun();

    /** Switch On/Off the storing of FairEventHeader in output file*/
    void SetEventHeaderPersistence(Bool_t flag) { fStoreEventHeader = flag; }

    void Reinit(UInt_t runId);
    UInt_t getRunId() { return fRunId; }
    /** Get the magnetic field **/
    FairField* GetField() override { return fField; }
    /** Set the magnetic Field */
    void SetField(FairField* ffield) { fField = ffield; }
    /** Set external geometry file */
    void SetGeomFile(const char* GeoFileName);
    /** Return a pointer to the geometry file */
    TFile* GetGeoFile() { return fInputGeoFile; }
    /** Initialization of parameter container is set to static, i.e: the run id is
     *  is not checked anymore after initialization
     */

    void SetContainerStatic(Bool_t tempBool = kTRUE);
    Bool_t GetContainerStatic() { return fStatic; };
    void RunWithTimeStamps();
    Bool_t IsTimeStamp() { return fTimeStamps; }

    /** Set the flag for proccessing lmd files */
    void StopProcessingLMD() { fFinishProcessingLMDFile = kTRUE; }
    /** Get the status of lmd file proccessing */
    Bool_t GetLMDProcessingStatus() { return fFinishProcessingLMDFile; }

  protected:
    /**
     * Virtual function which calls the Fill function of the IOManager.
     * Allows to override the function with an experiment specific version.
     **/
    virtual void Fill();

  private:
    FairRunAna(const FairRunAna& M);
    FairRunAna& operator=(const FairRunAna&) { return *this; }

    FairRunInfo fRunInfo;   //!

  protected:
    /** This variable became true after Init is called*/
    Bool_t fIsInitialized;
    TFile* fInputGeoFile;
    static FairRunAna* fgRinstance;
    Bool_t fLoadGeo;
    /** true for static initialisation of parameters */
    Bool_t fStatic;   //!
    FairField* fField;
    Bool_t fTimeStamps;
    Bool_t fInFileIsOpen;   //!
    /** min time for one event (ns) */
    Double_t fEventTimeMin;   //!
    /** max time for one Event (ns) */
    Double_t fEventTimeMax;   //!
    /** Time of event since th start (ns) */
    Double_t fEventTime;   //!
    /** EventMean time used (P(t)=1/fEventMeanTime*Exp(-t/fEventMeanTime) */
    Double_t fEventMeanTime;   //!
    /** used to generate random numbers for event time; */
    TF1* fTimeProb;   //!
    /** Flag for proccessing lmd-files*/
    Bool_t fFinishProcessingLMDFile;   //!

    /** Temporary member to preserve old functionality without setting source in macro */
    FairFileSource* fFileSource;   //!
    /** Temporary member to preserve old functionality without setting source in macro */
    FairMixedSource* fMixedSource;   //!
    /** Flag for Event Header Persistency */
    Bool_t fStoreEventHeader;   //!

    /**
     * \brief Internal facade: Handle RunID changes
     */
    void CheckRunIdChanged();

    ClassDefOverride(FairRunAna, 6);
};

#endif   // FAIRRUNANA_H

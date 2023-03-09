/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUN_H
#define FAIRRUN_H

#include "FairAlignmentHandler.h"
#include "FairEventHeader.h"
#include "FairSink.h"
#include "FairSource.h"

#include <Rtypes.h>   // for Int_t, Bool_t, etc
#include <TMCtls.h>   // for multi-threading
#include <TNamed.h>   // for TNamed
#include <TString.h>
#include <map>
#include <memory>
#include <string>

class FairEventHeader;
class FairFileHeader;
class FairRootManager;
class FairRuntimeDb;
class FairSink;
class FairTask;
class TFile;
class FairField;
class TGeoHMatrix;

/**
 * Configure the Simuation or Analysis
 * @author M. Al-Turany  D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class FairRun : public TNamed
{
    friend class FairMCApplication;

  public:
    /**
     * default ctor
     */
    FairRun(Bool_t isMaster = kTRUE);
    /**
     * default dtor
     */
    ~FairRun() override;
    /**
     * static instance
     */
    static FairRun* Instance();
    /**
     * Add a FAIRTask to the simulation or analysis
     */
    virtual void AddTask(FairTask* t);
    virtual void StoreTaskNames(const FairTask* t);
    virtual void SetTask(FairTask* t);
    /**
     * Initialize the Simulation or analysis
     */
    virtual void Init() = 0;
    /*
     * Get the magnetic field *
     */
    virtual FairField* GetField() = 0;
    /**
     * run the analysis or simulation
     */
    virtual void Run(Int_t NStart = 0, Int_t NStop = 0) = 0;
    /**
     *       Set the experiment dependent run header
     *       for each run
     */
    void SetEventHeader(FairEventHeader* EvHeader) { fEvtHeader = EvHeader; }
    /**
     * return a pointer to the RuntimeDB
     */
    FairRuntimeDb* GetRuntimeDb() { return fRtdb; }
    /**
     * Set the sink
     */
    void SetSink(std::unique_ptr<FairSink> newsink);
    void SetSink(FairSink* tempSink);
    /**
     * return a non-owning pointer to the sink
     */
    FairSink* GetSink() { return fSink.get(); }
    /**
     * return the run ID for the actul run
     */
    Int_t GetRunId() { return (static_cast<Int_t>(fRunId)); }

    /**
     * Set the Run ID
     */
    void SetRunId(UInt_t runId) { fRunId = runId; }

    /**Get the detector specific run header*/
    FairEventHeader* GetEventHeader();
    /**
     * return true for Anaylsis session
     */
    Bool_t IsAna() { return fAna; }
    /**
     *Get task by name
     */

    FairTask* GetTask(const char* taskName);
    /**
     *Get Main Task
     */
    FairTask* GetMainTask() { return fTask; }
    /**
     * Return the number of Tasks added to this Run
     */
    Int_t GetNTasks() { return fNTasks; }

    /**Create a new file and save the TGeoManager to it*/
    void CreateGeometryFile(const char* geofile);

    /**
     * Set if RunInfo file should be written
     * \deprecated Use SetGenerateRunInfo() instead.
     *   Deprecated pre-v19, will be removed in v20.
     */
    [[deprecated]] void SetWriteRunInfoFile(Bool_t write);

    //** Set if RunInfo should be generated */
    void SetGenerateRunInfo(Bool_t write) { fGenerateRunInfo = write; }

    /**
     * Get info if RunInfo file is written
     * \deprecated Use \ref IsRunInfoGenerated() instead.
     *   Deprecated pre-v19, will be removed in v20.
     */
    [[deprecated]] Bool_t GetWriteRunInfoFile();

    //** Get info if RunInfo file is written */
    Bool_t IsRunInfoGenerated() { return fGenerateRunInfo; }

    //** Switches the use of FairLinks */
    void SetUseFairLinks(Bool_t val);

    //** Get info if run on master */
    Bool_t GetIsMaster() const { return fIsMaster; }

    //** Mark/Unmark event to be filled into output. Default is TRUE. */
    void MarkFill(Bool_t flag) { fMarkFill = flag; }

    //** Get option string */
    TString GetOptions() { return fOptions; };

    //** Set option string */
    void SetOptions(const TString& s) { fOptions = s; };

    /**
     * Set the output file name for analysis or simulation
     * \deprecated Use \ref FairSink and \ref SetSink().
     *   Deprecated pre-v19, will be removed in v20.
     */
    [[deprecated]] virtual void SetOutputFile(const char* fname);
    /**
     * Set the output file for analysis or simulation
     * \deprecated Use \ref FairSink and \ref SetSink().
     *   Deprecated pre-v19, will be removed in v20.
     */
    [[deprecated]] virtual void SetOutputFile(TFile* f);
    /**
     * Set the  output file name without creating the file
     * \deprecated Use \ref FairSink and \ref SetSink().
     *   Deprecated pre-v19, will be removed in v20.
     */
    [[deprecated]] void SetOutputFileName(const TString& name);
    /**
     * \deprecated Use \ref FairSink and \ref SetSink().
     *   Deprecated pre-v19, will be removed in v20.
     */
    [[deprecated]] TFile* GetOutputFile();

    /**
     * New functions which allow to postpone creating a new Sink in MT
     * to be kept after clean-up of deprecated functions above
     */
    void SetUserOutputFileName(const TString& name);
    TString GetUserOutputFileName() const;

    void AddAlignmentMatrices(const std::map<std::string, TGeoHMatrix>& alignmentMatrices, bool invertMatrices = false);

    /**
     * \brief Set the input signal file
     *
     * Takes an owning pointer!
     */
    virtual void SetSource(FairSource* tempSource);
    /** Return non-owning pointer to source **/
    FairSource* GetSource() { return fSource.get(); }
    FairRootManager& GetRootManager() { return *fRootManager; }
    FairRootManager const& GetRootManager() const { return *fRootManager; }

  private:
    FairRun(const FairRun& M);
    FairRun& operator=(const FairRun&) { return *this; }
    /** Number of Tasks added*/
    Int_t fNTasks;

  protected:
    /** static pointer to this run*/
    static TMCThreadLocal FairRun* fRunInstance;
    /** RuntimeDb*/
    FairRuntimeDb* fRtdb;
    /** Tasks used*/
    FairTask* fTask;
    /**IO manager */
    FairRootManager* fRootManager;
    /**Output sink*/
    std::unique_ptr<FairSink> fSink{};   //!
    /**Output file name set by user*/
    TString fUserOutputFileName;
    /**Options for derived classes, to be set & parsed by user*/
    TString fOptions;
    /**Run Id*/
    UInt_t fRunId;   //!
    /** true for Anaylsis session*/
    Bool_t fAna;   //!
    /** MC Event Header */
    FairEventHeader* fEvtHeader;   //!
    /** File  Header */
    FairFileHeader* fFileHeader;
    /** true if RunInfo file should be written*/
    Bool_t fGenerateRunInfo;   //!
    /** true if on master*/
    Bool_t fIsMaster;   //!

    Bool_t fMarkFill;   //!

    FairAlignmentHandler fAlignmentHandler;

    std::unique_ptr<FairSource> fSource{};   //!

    void AlignGeometry() const;
    /**
     * Call FillEventHeader on the source
     */
    void FillEventHeader()
    {
        if (fSource)
            fSource->FillEventHeader(fEvtHeader);
    }

    /**
     * Get the RunId of the Event Header
     */
    UInt_t GetEvtHeaderRunId() const { return fEvtHeader->GetRunId(); }

    ClassDefOverride(FairRun, 5);
};
#endif   // FAIRRUN_H

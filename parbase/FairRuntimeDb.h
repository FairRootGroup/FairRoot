/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNTIMEDB_H
#define FAIRRUNTIMEDB_H

#include <Rtypes.h>    // for Bool_t, Int_t, Text_t, etc
#include <TList.h>     // for TList
#include <TObject.h>   // for TObject
#include <TString.h>   // for TString

class FairContFact;
class FairLogger;
class FairParIo;
class FairParSet;
class FairRtdbRun;

static TList contFactories;   //! list of container factories

/**
 * \ingroup parbase
 *
 * See Also: \ref parbase_runtimedb
 */
class FairRuntimeDb : public TObject
{
  private:
    static FairRuntimeDb* gRtdb;   //!

  protected:
    FairRuntimeDb(void);
    TList* containerList;      // list of parameter containers
    TList* runs;               // list of runs
    FairParIo* firstInput;     // first (prefered) input for parameters
    FairParIo* secondInput;    // second input (used if not found in first input)
    FairParIo* output;         // output for parameters
    FairRtdbRun* currentRun;   // Current run
    TString currentFileName;   // Name of current event file
    Bool_t versionsChanged;    // flag for write of list of runs (set kTRUE by each write)
    Bool_t isRootFileOutput;   // flag indicating that the output is a ROOT file
    /** Fair Logger */
    FairLogger* fLogger;   //!

    /**
     * Select which IO type to use.
     */
    typedef enum
    {
        UNKNOWN_Type = 0,
        AsciiFileOutput = 1,   // Ascii in-out-put
        RootFileOutput = 2,    // Root Files
        RootTSQLOutput = 3     // Use a TSQL db
    } ParamIOType;
    ParamIOType ioType;   // IO Type

  public:
    static FairRuntimeDb* instance(void);
    ~FairRuntimeDb() override;

    Bool_t addParamContext(const char*);
    void printParamContexts();
    void addContFactory(FairContFact*);
    void removeContFactory(FairContFact* fact);
    FairContFact* getContFactory(const Text_t*);

    Bool_t addContainer(FairParSet*);
    FairParSet* getContainer(const Text_t*);
    FairParSet* findContainer(const char*);
    void removeContainer(Text_t*);
    void removeAllContainers(void);
    Bool_t initContainers(UInt_t runId, Int_t refId = -1, const Text_t* fileName = "");
    void setContainersStatic(Bool_t f = kTRUE);
    Bool_t writeContainers(void);
    Bool_t writeContainer(FairParSet*, FairRtdbRun*, FairRtdbRun* refRun = 0);

    FairRtdbRun* addRun(Int_t runId, Int_t refId = -1);
    FairRtdbRun* getRun(Int_t);
    FairRtdbRun* getRun(Text_t*);
    FairRtdbRun* getCurrentRun(void) { return currentRun; }
    Text_t const* getCurrentFileName() { return currentFileName.Data(); }
    void clearRunList(void);

    void removeRun(Text_t*);

    Bool_t setInputVersion(Int_t run, Text_t* container, Int_t version, Int_t inputNumber);
    Bool_t setRootOutputVersion(Int_t run, Text_t* container, Int_t version);
    void setVersionsChanged(Bool_t f = kTRUE) { versionsChanged = f; }
    void resetInputVersions(void);
    void resetOutputVersions(void);
    void resetAllVersions(void);

    Bool_t readAll(void);
    void writeVersions(void);
    void saveOutput(void);

    Bool_t setFirstInput(FairParIo*);
    Bool_t setSecondInput(FairParIo*);
    Bool_t setOutput(FairParIo*);
    FairParIo* getFirstInput(void);
    FairParIo* getSecondInput(void);
    FairParIo* getOutput(void);
    void closeFirstInput(void);
    void closeSecondInput(void);
    void closeOutput(void);
    void activateParIo(FairParIo*);
    TList* getListOfContainers() { return containerList; }
    void print(void);

    Int_t findOutputVersion(FairParSet*);

  private:
    FairRuntimeDb(const FairRuntimeDb& M);
    FairRuntimeDb& operator=(const FairRuntimeDb&) { return *this; }
    Bool_t initContainers(void);

    ClassDefOverride(FairRuntimeDb, 0);   // Class for runtime database
};

#endif /* !FAIRRUNTIMEDB_H */

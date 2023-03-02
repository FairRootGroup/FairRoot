/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                      FairTask header file                      -----
// -----          Created 12/01/04  by M. Al-Turany / D. Bertini       -----
// -------------------------------------------------------------------------

/** FairTask
 * @author M. Al-Turany, Denis Bertini
 * @since 12.01.04
 **
 ** Base class for tasks in the cbmroot framework.
 ** Derived classes should implement the Exec method.
 **/

#ifndef FAIRTASK_H
#define FAIRTASK_H

#include <Rtypes.h>    // for Int_t, FairTask::Class, etc
#include <TString.h>   // for TString
#include <TTask.h>     // for TTask
#include <map>

class FairLogger;

enum InitStatus
{
    kSUCCESS,
    kERROR,
    kFATAL
};

/**
 * \ingroup base_steer
 */
class FairTask : public TTask
{
  public:
    /** Default constructor **/
    FairTask();

    /** Standard constructor
     *@param name        Name of task
     *@param iVerbose    Verbosity level
     **/
    FairTask(const char* name, Int_t iVerbose = 1);

    FairTask(const FairTask&) = delete;
    FairTask& operator=(const FairTask&) = delete;
    FairTask(FairTask&&) = delete;
    FairTask& operator=(FairTask&&) = delete;

    /** Destructor **/
    ~FairTask() override;

    /** Initialisation at begin of run. For this task and all of the subtasks.
        Method used internally in FairRoot. **/
    void InitTask();

    /** Reinitialisation. For this task and all of the subtasks.
        Method used internally in FairRoot. **/
    void ReInitTask();

    /** Set parameters. For this task and all of the subtasks.
        Method used internally in FairRoot. **/
    void SetParTask();

    /** Action at end of run. For this task and all of the subtasks.
        Method used internally in FairRoot. **/
    virtual void FinishTask();

    /** Action at end of event. For this task and all of the subtasks. **/
    virtual void FinishEvent();

    /** Set verbosity level. For this task and all of the subtasks. **/
    void SetVerbose(Int_t iVerbose);

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
    /**
     * \deprecated Deprecated in v18.8, will be removed in v20.
     */
    [[deprecated]] void SetInputPersistance(Bool_t val) { fInputPersistance = val; }
#pragma GCC diagnostic pop

    /**
     * \deprecated Deprecated in v18.8, will be removed in v20.
     */
    [[deprecated]] void CheckInputPersistance(TString branchName);

    void ExecuteTask(Option_t* option = "0") override;   // *MENU*

    /** Set persistency of branch with given name true or false
     *  In case is is set to false the branch will not be written to the output.
     **/
    void SetOutputBranchPersistent(TString, Bool_t);

    /** Check if the branch with the given name is persistent.
     *  If the branch is not in the map, the default return value is true.
     **/
    Bool_t IsOutputBranchPersistent(TString);

    void SetStreamProcessing(Bool_t val = kTRUE) { fStreamProcessing = val; }

  protected:
    Int_t fVerbose;                           //  Verbosity level
    [[deprecated]] Int_t fInputPersistance;   ///< \deprecated Deprecated in v18.8, will be removed in v20.
    FairLogger* fLogger;                      //!
    Bool_t fStreamProcessing;

    /** Intialisation at begin of run. To be implemented in the derived class.
     * \retval  kSUCCESS   If not kSUCCESS, task will be set inactive.
     **/
    virtual InitStatus Init() { return kSUCCESS; };

    /** Reinitialisation. To be implemented in the derived class.
     * \retval  kSUCCESS   If not kSUCCESS, task will be set inactive.
     **/
    virtual InitStatus ReInit() { return kSUCCESS; };

    /** Intialise parameter containers.
        To be implemented in the derived class.
    **/
    virtual void SetParContainers(){};

    /** Action at end of run. For this task and all of the subtasks.
        To be implemented in the derived class.
    **/
    virtual void Finish(){};

    /** Recursive intialisation of subtasks at begin of run **/
    void InitTasks();

    /** Recursive reinitialisation of subtasks **/
    void ReInitTasks();

    void ExecuteTasks(Option_t* option) override;

    /** Recursive parameter initialisation for subtasks **/
    void SetParTasks();

    /** Recursive finish of subtasks **/
    void FinishTasks();

    /** Recursive FinishEvent of subtasks **/
    void FinishEvents();

  private:
    std::map<TString, Bool_t> fOutputPersistance;

    ClassDefOverride(FairTask, 4);
};

#endif

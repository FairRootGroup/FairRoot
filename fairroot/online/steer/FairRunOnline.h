/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNONLINE_H
#define FAIRRUNONLINE_H

/**
 * Configure and manage the Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "FairField.h"
#include "FairRootManager.h"
#include "FairRun.h"

#include <Rtypes.h>
#include <TString.h>

class FairField;
class FairSource;
class THttpServer;
class TObject;

class FairRunOnline : public FairRun
{
  public:
    static FairRunOnline* Instance();
    ~FairRunOnline() override;
    FairRunOnline();
    FairRunOnline(FairSource* source);

    /**initialize the run manager*/
    void Init() override;
    /**Run for the given number of events*/
    void Run(Int_t Ev_start, Int_t Ev_end) override;

    void Reinit(UInt_t runId);
    UInt_t getRunId() { return fRunId; }
    /** Get the magnetic field **/
    FairField* GetField() override { return fField; }
    /** Set the magnetic Field */
    void SetField(FairField* ffield) { fField = ffield; }

    /** Set if the run should be closed automatically after executing the
        run functuion
    **/
    void SetAutoFinish(Bool_t val) { fAutomaticFinish = val; }

    /** Initialization of parameter container is set to static, i.e: the run id is
     *  is not checked anymore after initialization
     */

    /** Init containers executed on PROOF, which is part of Init when running locally*/
    void InitContainers();
    void SetContainerStatic(Bool_t tempBool = kTRUE);
    Bool_t GetContainerStatic() { return fStatic; };

    /** Add histogram to be displayed using THttpServer.*/
    virtual void AddObject(TObject* object);

    /** Activate http server on defined host port. To be called before Init.
     * @param refreshRate an interval in number of events for server update.
     * @param httpPort the port which is used by the http server
     */
    void ActivateHttpServer(Int_t refreshRate = 10000, Int_t httpPort = 8080);

    /** Register a command on the http server.
     * @param name a command name starting with /
     * @param command a call to method "/object_name/->Method()"
     */
    void RegisterHttpCommand(TString name, TString command);

    /** Get direct access to the http server. */
    THttpServer* GetHttpServer() { return fServer; }

    /** Write last data to file, close input and output **/
    void Finish();

  private:
    Bool_t fAutomaticFinish;

    FairRunOnline(const FairRunOnline& M);
    FairRunOnline& operator=(const FairRunOnline&) { return *this; }

    /** Main Event loop **/
    Int_t EventLoop();

  protected:
    /** This variable became true after Init is called*/
    Bool_t fIsInitialized;
    static FairRunOnline* fgRinstance;
    /** true for static initialisation of parameters */
    Bool_t fStatic;   //!
    FairField* fField;

    Int_t fNevents;             //!
    THttpServer* fServer;       //!
    Int_t fServerRefreshRate;   //!

    virtual void Fill();

    ClassDefOverride(FairRunOnline, 1);
};

#endif   // FAIRRUNONLINE_H

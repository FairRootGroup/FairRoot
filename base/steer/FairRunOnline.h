#ifndef FAIRRUNONLINE_H
#define FAIRRUNONLINE_H


/**
 * Configure and manage the Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "FairRun.h"
#include "FairRootManager.h"

#include "TString.h"
#include <iostream>

class FairRuntimeDb;
class FairEventHeader;
class FairMCEventHeader;
class FairField;
class TFile;
class FairLogger;
class TF1;
class TTree;
class FairSource;
class TFolder;

class FairRunOnline : public FairRun
{

  public:
    static FairRunOnline* Instance();
    virtual ~FairRunOnline();
    FairRunOnline(FairSource* source);

    /**initialize the run manager*/
    void        Init();
    /**Run for the given number of events*/
    void        Run(Int_t nev, Int_t dummy);

    void        Reinit(UInt_t runId);
    UInt_t      getRunId() { return fRunId; }
    /** Get the magnetic field **/
    FairField*  GetField() { return fField; }
    /** Set the magnetic Field */
    void        SetField (FairField* ffield) { fField = ffield; }

    /** Initialization of parameter container is set to static, i.e: the run id is
     *  is not checked anymore after initialization
     */

    /** Init containers executed on PROOF, which is part of Init when running locally*/
    void        InitContainers();
    void        SetContainerStatic(Bool_t tempBool=kTRUE);
    Bool_t      GetContainerStatic() { return fStatic; };

    void AddObject(TObject* object);

    void SetGenerateHtml(Bool_t flag = kTRUE);

  private:
    FairRunOnline(const FairRunOnline& M);
    FairRunOnline& operator= (const  FairRunOnline&) { return *this; }

  protected:
    /** This variable became true after Init is called*/
    Bool_t                                  fIsInitialized;
    static FairRunOnline*                   fgRinstance;
    FairEventHeader*                        fEvtHeader;//!
    /** true for static initialisation of parameters */
    Bool_t                                  fStatic;//!
    FairField*                              fField;

    FairSource* fSource;       //!
    TFolder*    fFolder;       //!
    Bool_t      fGenerateHtml; //!

    void WriteObjects();
    void GenerateHtml();

    ClassDef(FairRunOnline, 0)
};

#endif //FAIRRUNONLINE_H

#ifndef FAIRRUNANA_H
#define FAIRRUNANA_H


/**
 * Configure and manage the  Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "FairRun.h"
#include "FairRunInfo.h"
#include "FairRootManager.h"

#include "TProof.h"
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

class FairRunAna : public FairRun
{

  public:

    static FairRunAna* Instance();
    virtual ~FairRunAna();
    FairRunAna();
    FairRunAna(const char* type, const char* proofName="");
    /** Add a friend file (input) by name)*/
    void        AddFriend(TString fName);
    /**initialize the run manager*/
    void        Init();
    /**Run from event number NStart to event number NStop */
    void        Run(Int_t NStart ,Int_t NStop);
    /**Run over the whole input file with timpe window delta_t as unit (entry)*/
    void        Run(Double_t delta_t);
    /**Run for the given single entry*/
    void        Run(Long64_t entry);
    /**Run for one event, used on PROOF nodes*/
    void        RunOneEvent(Long64_t entry);
    /**Run from event number NStart to event number NStop over mixed input files */
    void        RunMixed(Int_t NStart, Int_t NStop);
    /**Run over all TSBuffers until the data is processed*/
    void        RunTSBuffers();
    /** the dummy run does not check the evt header or the parameters!! */
    void        DummyRun(Int_t NStart ,Int_t NStop);
    /** run on proof from event NStart to event NStop*/
    void        RunOnProof(Int_t NStart, Int_t NStop);
    /** Run on a list of lmd files*/
    void        RunOnLmdFiles(UInt_t NStart=0, UInt_t NStop=0);
    /** finish tasks, write output*/
    void        TerminateRun();
    /**Set the input signal file
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file
     */
    void        SetSignalFile(TString name, UInt_t identifier );
    /**Set the input background file by name*/
    void        SetBackgroundFile(TString name);
    /**Add input background file by name*/
    void        AddBackgroundFile(TString name);
    /**Add signal file to input
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file to which this signal should be added
     */
    void        AddSignalFile(TString name, UInt_t identifier );
    /**Set the input file by name*/
    void        SetInputFile(TString fname);
    /**Add a file to input chain */
    void        AddFile(TString name);

    void        Reinit(UInt_t runId);
    UInt_t      getRunId() {
      return fRunId;
    }
    /** Get the magnetic field **/
    FairField*  GetField() {
      return fField;
    }
    /** Set the magnetic Field */
    void        SetField (FairField* ffield ) {
      fField=ffield ;
    }
    /** Set external geometry file */
    void        SetGeomFile(const char* GeoFileName);
    /** Return a pointer to the geometry file */
    TFile*      GetGeoFile() {
      return fInputGeoFile;
    }
    /** Initialization of parameter container is set to static, i.e: the run id is
     *  is not checked anymore after initialization
     */

    /** Init containers executed on PROOF, which is part of Init when running locally*/
    void        InitContainers();

    /** set the input tree of fRootManager when running on PROOF worker*/
    void        SetInTree (TTree* tempTree)   {
      fRootManager->SetInTree (tempTree);
    }

    void        SetContainerStatic(Bool_t tempBool=kTRUE);
    Bool_t      GetContainerStatic() { return fStatic; };
    void        RunWithTimeStamps();
    Bool_t      IsTimeStamp() {
      return fTimeStamps;
    }
    void        CompressData();

    /** Set the min and max limit for event time in ns */
    void SetEventTimeInterval(Double_t min, Double_t max);

    /** Set the mean time for the event in ns */
    void SetEventMeanTime(Double_t mean);

    /**Set the signal to background ratio in event units
     *@param background :  Number of background Events for one signal
     *@param Signalid :    Signal file Id, used when adding (setting) the signal file
     * here we just forward the call to the FairRootManager
     */
    void BGWindowWidthNo(UInt_t background, UInt_t Signalid);
    /**Set the signal to background rate in time units
     *@param background :  Time of background Events before one signal
     *@param Signalid :    Signal file Id, used when adding (setting) the signal file
     * here we just forward the call to the FairRootManager
     */
    void BGWindowWidthTime(Double_t background, UInt_t Signalid);

    /** GetProof */
    TProof* GetProof() { return fProof;}

    /** To be set to kTRUE only when running on PROOF worker, only by TSelector */
    void SetRunOnProofWorker(Bool_t tb = kTRUE) {
      fRunOnProofWorker = tb;
    }
    /** Set PROOF ARchive (PAR) file name*/
    void SetProofParName(TString parName) {
      fProofParName = parName;
    }
    /** Set directory for storing output files*/
    void SetOutputDirectory(TString dirName) {
      fOutputDirectory = dirName;
    }
    /** Set PROOF output status, possibilities: "copy","merge","dataset"*/
    void SetProofOutputStatus(TString outStat) {
      fProofOutputStatus = outStat;
    }

    /** Set the flag for proccessing lmd files */
    void StopProcessingLMD( void ) {
      fFinishProcessingLMDFile = kTRUE;
    }
    /** Get the status of lmd file proccessing */
    Bool_t GetLMDProcessingStatus( void ) {
      return fFinishProcessingLMDFile;
    }


  private:

    FairRunAna(const FairRunAna& M);
    FairRunAna& operator= (const  FairRunAna&) {
      return *this;
    }

    FairRunInfo fRunInfo;//!

  protected:
    /** This variable became true after Init is called*/
    Bool_t                                  fIsInitialized;
    TFile*                                  fInputGeoFile;
    static FairRunAna*                      fgRinstance;
    Bool_t                                  fLoadGeo;
    FairEventHeader*                        fEvtHeader;//!
    FairMCEventHeader*                      fMCHeader;//!
    /** true for static initialisation of parameters */
    Bool_t                                  fStatic;//!
    FairField*                              fField;
    Bool_t                                  fTimeStamps;
    Bool_t                                  fInFileIsOpen;//!
    /**True if signal and background mixing is used*/
    Bool_t                                  fMixedInput;//!
    /** min time for one event (ns) */
    Double_t                                fEventTimeMin;  //!
    /** max time for one Event (ns) */
    Double_t                                fEventTimeMax;  //!
    /** Time of event since th start (ns) */
    Double_t                                fEventTime;     //!
    /** EventMean time used (P(t)=1/fEventMeanTime*Exp(-t/fEventMeanTime) */
    Double_t                                fEventMeanTime; //!
    /** used to generate random numbers for event time; */
    TF1*                                    fTimeProb;      //!
    /** PROOF **/
    TProof*                                 fProof;
    /** flag indicating running in PROOF mode*/
    Bool_t                                  fProofAnalysis; //!
    /** executing on PROOF worker*/
    Bool_t                                  fRunOnProofWorker; //!
    /** PROOF server name*/
    TString                                 fProofServerName; //!
    /** PROOF ARchive (PAR) file name*/
    TString                                 fProofParName; //!
    /** Output directory*/
    TString                                 fOutputDirectory; //!
    /** Output status indicator: "copy","merge","dataset"*/
    TString                                  fProofOutputStatus;
    /** Flag for proccessing lmd-files*/
    Bool_t                                   fFinishProcessingLMDFile;  //!

    ClassDef(FairRunAna ,4)

};

#endif //FAIRRUNANA_H

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNANA_H
#define FAIRRUNANA_H


/**
 * Configure and manage the  Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "FairRun.h"                    // for FairRun

#include "FairRootManager.h"            // for FairRootManager
#include "FairRunInfo.h"                // for FairRunInfo

#include "Rtypes.h"                     // for Bool_t, Double_t, UInt_t, etc
#include "TString.h"                    // for TString

class FairField;
class TF1;
class TFile;
class TTree;

class FairFileSource;
class FairMixedSource;

class FairRunAna : public FairRun
{

  public:

    static FairRunAna* Instance();
    virtual ~FairRunAna();
    FairRunAna();
    /**initialize the run manager*/
    void        Init();
    /**Run from event number NStart to event number NStop */
    void        Run(Int_t NStart=0 ,Int_t NStop=0);
    /**Run over the whole input file with timpe window delta_t as unit (entry)*/
    void        Run(Double_t delta_t);
    /**Run for the given single entry*/
    void        Run(Long64_t entry);
    /**Run event reconstruction from event number NStart to event number NStop */
    void        RunEventReco(Int_t NStart ,Int_t NStop);
    /**Run over all TSBuffers until the data is processed*/
    void        RunTSBuffers();
    /** the dummy run does not check the evt header or the parameters!! */
    void        DummyRun(Int_t NStart ,Int_t NStop);
    /** This methode is only needed and used with ZeroMQ
      * it read a certain event and call the task exec, but no output is written
      * @param entry : entry number in the tree
      */
    void RunMQ(Long64_t entry);
    /** Run on a list of lmd files*/
    void        RunOnLmdFiles(UInt_t NStart=0, UInt_t NStop=0);

    void RunOnTBData();
    /** finish tasks, write output*/
    void        TerminateRun();
    /**Set the input signal file
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file
     */

    virtual void   SetSource(FairSource* tempSource) { fRootManager->SetSource(tempSource); }

    // ********************************************************* //
    // THE BELOW FUNCTIONS SHOULD BE MOVED TO FairFileSource
    /**Set the input file by name*/
    void        SetInputFile(TString fname);
    /**Add a file to input chain */
    void        AddFile(TString name);
    /** Add a friend file (input) by name)*/
    void        AddFriend(TString fName);
    // ********************************************************* //
    // THE BELOW FUNCTIONS SHOULD BE MOVED TO FairMixedSource
    void        SetSignalFile(TString name, UInt_t identifier );
    /**Add signal file to input
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file to which this signal should be added
     */
    void        AddSignalFile(TString name, UInt_t identifier );
    /**Set the input background file by name*/
    void        SetBackgroundFile(TString name);
    /**Add input background file by name*/
    void        AddBackgroundFile(TString name);
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
    /**
     * This method will simply forward the call to the FairRootManager, 
     * if  true all inputs are mixed, i.e: each read event will take one entry from each input and put
     * them in one big event and send it to the next step
    */
    //    void SetMixAllInputs(Bool_t Status);
    // ********************************************************* //
    // THE BELOW FUNCTIONS SHOULD BE MOVED TO FairFileSource and FairMixedSource
    /** Set the min and max limit for event time in ns */
    void SetEventTimeInterval(Double_t min, Double_t max);
    /** Set the mean time for the event in ns */
    void SetEventMeanTime(Double_t mean);
    /** Set the time intervall the beam is interacting and the gap in ns */
    void SetBeamTime(Double_t beamTime, Double_t gapTime);
    // ********************************************************* //
 
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

    void        SetContainerStatic(Bool_t tempBool=kTRUE);
    Bool_t      GetContainerStatic() { return fStatic; };
    void        RunWithTimeStamps();
    Bool_t      IsTimeStamp() {
      return fTimeStamps;
    }

    /** Set the flag for proccessing lmd files */
    void StopProcessingLMD( void ) {
      fFinishProcessingLMDFile = kTRUE;
    }
    /** Get the status of lmd file proccessing */
    Bool_t GetLMDProcessingStatus( void ) {
      return fFinishProcessingLMDFile;
    }

  protected:
    /**
     * Virtual function which calls the Fill function of the IOManager.
     * Allows to override the function with an experiment specific version.
    **/
    virtual void Fill() { fRootManager->Fill(); }            
                                               
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
    /** true for static initialisation of parameters */
    Bool_t                                  fStatic;//!
    FairField*                              fField;
    Bool_t                                  fTimeStamps;
    Bool_t                                  fInFileIsOpen;//!
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
    /** Flag for proccessing lmd-files*/
    Bool_t                                  fFinishProcessingLMDFile;  //!

    /** Temporary member to preserve old functionality without setting source in macro */
    FairFileSource*                         fFileSource;  //! 
    /** Temporary member to preserve old functionality without setting source in macro */
    FairMixedSource*                        fMixedSource; //! 

    ClassDef(FairRunAna ,6)

};

#endif //FAIRRUNANA_H

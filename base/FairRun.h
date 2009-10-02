#ifndef FAIRRUN_H
#define FAIRRUN_H

#include "TNamed.h"
//#include "TString.h"

    
class FairTask;
class TFile;
class FairRuntimeDb;
class FairRootManager;

/**
 * Configure the Simuation or Analysis
 * @author M. Al-Turany  D. Bertini
 * @version 0.1
 * @since 12.01.04
 */
   


class FairRun : public TNamed {


public:
    FairRun();
    virtual ~FairRun();
    static FairRun * Instance();
    /**
      Add a FAIRTask to the simulation or analysis
    */
    virtual void        AddTask(FairTask *t);
    /**
      Initialize the Simulation or analysis
    */
    virtual void    Init()=0;
    /**
      run the analysis or simulation
    */
    virtual void    Run(Int_t NStart =0,Int_t NStop=0)=0;
    /**
      Set the output file name for analysis or simulation
    */
    void        SetOutputFile(const char *fname);
    FairRuntimeDb* GetRuntimeDb(void) {return fRtdb;}
    TFile *GetOutputFile(){return fOutFile;}
     Int_t                GetRunId() { return ((Int_t) fRunId);}
   /** return true for Anaylsis session*/
    Bool_t	          IsAna(){return fAna;} 
   /**Get task by name*/
    FairTask* GetTask(const char* taskName);
private:
    FairRun(const FairRun &M);
    FairRun& operator= (const  FairRun&) {return *this;}


protected:

    static FairRun*          fRunInstance;
    FairRuntimeDb*           fRtdb;
    FairTask*                fTask;
    const char*             Outfname;
    FairRootManager*         fRootManager;
    TFile*		            fOutFile;
    UInt_t                  fRunId;//!
   /** true for Anaylsis session*/
    Bool_t	          fAna;  //! 
    ClassDef(FairRun ,1)
};
#endif //FAIRRUN_H

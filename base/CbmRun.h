#ifndef CBMRUN_H
#define CBMRUN_H

#include "TNamed.h"
//#include "TString.h"

    
class CbmTask;
class TFile;
class CbmRuntimeDb;
class CbmRootManager;

/**
 * Configure the Simuation or Analysis
 * @author M. Al-Turany  D. Bertini
 * @version 0.1
 * @since 12.01.04
 */
   


class CbmRun : public TNamed {


public:
    CbmRun();
    virtual ~CbmRun();
    static CbmRun * Instance();
    /**
      Add a CBMTask to the simulation or analysis
    */
    virtual void        AddTask(CbmTask *t);
    /**
      Initialize the Simulation or analysis
    */
    virtual void    Init();
    /**
      run the analysis or simulation
    */
    virtual void    Run(Int_t NStart =0,Int_t NStop=0);
    /**
      Set the output file name for analysis or simulation
    */
    void        SetOutputFile(const char *fname);
    CbmRuntimeDb* GetRuntimeDb(void) {return fRtdb;}
    TFile *GetOutputFile(){return fOutFile;}
     Int_t                GetRunId() { return ((Int_t) fRunId);}
   /** return true for Anaylsis session*/
    Bool_t	          IsAna(){return fAna;} 
   /**Get task by name*/
    CbmTask* GetTask(const char* taskName);
private:
    CbmRun(const CbmRun &M);
    CbmRun& operator= (const  CbmRun&) {return *this;}


protected:

    static CbmRun*          fRunInstance;
    CbmRuntimeDb*           fRtdb;
    CbmTask*                fTask;
    const char*             Outfname;
    CbmRootManager*         fRootManager;
    TFile*		            fOutFile;
    UInt_t                  fRunId;//!
   /** true for Anaylsis session*/
    Bool_t	          fAna;  //! 
    ClassDef(CbmRun ,1)
};
#endif //CBMRUN_H

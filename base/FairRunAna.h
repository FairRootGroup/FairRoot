#ifndef FAIRRUNANA_H
#define FAIRRUNANA_H


/**
 * Configure and manage the  Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "FairRun.h"
#include "TString.h"
#include <iostream>

class FairRuntimeDb;
class FairEventHeader;
class FairField;
class TFile;
class FairLogger;


class FairRunAna : public FairRun
{

  public:

    static FairRunAna* Instance();
    virtual ~FairRunAna();
    FairRunAna();
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
    /** the dummy run does not check the evt header or the parameters!! */
    void        DummyRun(Int_t NStart ,Int_t NStop);
    /**Set the input file by name*/
    void        SetInputFile(TString fname);
    void        AddFile(TString name);
    void        LoadGeometry() {fLoadGeo=kTRUE;}
    void        Reinit(UInt_t runId);
    UInt_t      getRunId() {return fRunId;}
    /** Get the magnetic field **/
    FairField*  GetField() {return fField; }
    void      SetField (FairField* ffield ) {fField=ffield ;}
    void        SetGeomFile(const char* GeoFileName);
    TFile*      GetGeoFile() {return fInputGeoFile;}
    void        SetContainerStatic() {
      fStatic=kTRUE;
      std::cout << "-I- FairRunAna : Parameter Cont. initialisation is static"
                << std::endl;
    }
    void        RunWithTimeStamps();
    Bool_t      IsTimeStamp() {return fTimeStamps;}
    void        CompressData();


  private:
    FairRunAna(const FairRunAna& M);
    FairRunAna& operator= (const  FairRunAna&) {return *this;}

  protected:
    Bool_t                                  fIsInitialized;
    TFile*                                  fInputGeoFile;
    static FairRunAna*                      fgRinstance;
    Bool_t                                  fLoadGeo;
    FairEventHeader*                        fEvtHeader;//!
    /** true for static initialisation of parameters */
    Bool_t                                  fStatic;//!
    FairField*                              fField;
    Bool_t                                  fTimeStamps;
    Bool_t                                  fInFileIsOpen;//!

    ClassDef(FairRunAna ,3)

};

#endif //FAIRRUNANA_H

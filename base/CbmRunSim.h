#ifndef CBMRUNSIM_H
#define CBMRUNSIM_H

#include "CbmRun.h"

#include "CbmMCApplication.h"
#include "CbmIon.h"
#include "CbmParticle.h"
#include "TObjArray.h"
#include "TString.h"
#include <iostream>

class CbmModule;
class CbmField;
class CbmPrimaryGenerator;

/**
 * Configure the Simulation session
 * @author M. Al-Turany  D. Bertini
 * @version 0.1
 * @since 12.01.04
 */
class CbmRunSim : public CbmRun {
public:
    /** default ctor*/
    CbmRunSim();
    /** default dtor*/
    virtual ~CbmRunSim();
    /** Singelton instance*/
    static CbmRunSim *Instance(); 
    /**
     *       Add a module to the simulation (e.g. PIPE, Magnet, ..etc)
    */
    void        AddModule  (CbmModule *Mod);
    /**
     *       Add a user defined ion to the simulation
    */
    void        AddNewIon(CbmIon *ion){fIons->Add(ion);}
    /**
     *       Add a user defined ion to the simulation
    */
    void        AddNewParticle(CbmParticle *Particle){fParticles->Add(Particle);}
    /**
     *       this method is used by the CBMMCApplication
    */
    TObjArray*  GetUserDefIons();
    /**
     *       this method is used by the CBMMCApplication
    */
    TObjArray*  GetUserDefParticles();

    /**
    *       Initialize the Simulation
    */
    virtual void        Init();
    /**
    *       run the analysis or simulation
    */
    virtual void    Run(Int_t NStart =0,Int_t NStop=0);
    /**  
    *       Set the magnetic that has to be used for simulation field
    */
    void        SetField(CbmField *field);
    /**
     *       Set the event generator that has to be used for simulation field
    */

    void        SetGenerator(CbmPrimaryGenerator *Gen);
    /**
    *       Set the material file name to be used
    */
    void        SetMaterials(const char * MatFileName);
    /**switch On/Off the track visualisation */    
    void SetStoreTraj(Bool_t storeTraj=kTRUE) {fStoreTraj = storeTraj;}
    /**switch On/Off the debug mode */    
    void SetTrackingDebugMode( Bool_t set ) { if (fApp) fApp->SetTrackingDebugMode( set ); }
    /**Set geometry builder*/
    void SetGeoModel( char * name );
    /**return the geometry loader used in this session*/
    TString* GetGeoModel () { return fLoaderName; }
    /**Get the field used in simulation*/
    CbmField*  GetField() { return fField;}
    /**return the full list of modules used in simulation*/
    TObjArray*        GetListOfModules() { return ListOfModules;}
    /**Get the used primary generator*/
    CbmPrimaryGenerator* GetPrimaryGenerator() { return fGen;}
    /**switch On/Off external decayer (Pythia) */    
    void SetPythiaDecayer(Bool_t decayer){fPythiaDecayer = decayer;}
    /**switch On/Off user defined decay if true gconfig/UserDecay.C macro will be called  */    
    void SetUserDecay(Bool_t decay){fUserDecay = decay;}
    /**Flag for external decayer*/
    Bool_t  IsExtDecayer(){return fPythiaDecayer; }
    /**Flag for User decay*/
    Bool_t  IsUserDecay(){return fUserDecay; }
    /** */
    void SetRadLenRegister(Bool_t value) {fRadLength= value;}
private:
   CbmRunSim(const CbmRunSim &M);
    CbmRunSim& operator= (const  CbmRunSim&) {return *this;}
protected:

    Int_t                 count;  /*Internal counter*/
    CbmMCApplication*     fApp;  //!
    CbmPrimaryGenerator*  fGen; //!
    static CbmRunSim*     fginstance;//!
    CbmField*             fField;
    const char*           fMapName; //!
    TObjArray*            fIons; //!
    TObjArray*            fParticles; //!
    TObjArray*            ListOfModules; //!
    TString 	          MatFname; //!
    Bool_t                fStoreTraj;
    TString*              fLoaderName;
    Bool_t                fPythiaDecayer;
    Bool_t                fUserDecay;
    Bool_t                fRadLength;
    
    ClassDef(CbmRunSim ,1)
    
};
#endif //CBMRUNSIM_H

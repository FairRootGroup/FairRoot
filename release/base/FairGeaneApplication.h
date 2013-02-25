// -------------------------------------------------------------------------
// -----               FairGeaneApplication header file                   -----
// -----            Created 10/11/10  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#ifndef FAIR_GEANE_APPLICATION_H
#define FAIR_GEANE_APPLICATION_H


#include "TVirtualMCApplication.h"
#include "TLorentzVector.h"
#include "FairTask.h"

class FairField;
class FairPrimaryGenerator;
class TTask;


/**
 * The Main Application for GEANE
 * @author M. Al-Turany
 * @version 0.1
 * @since 10.11.10
 */

class FairGeaneApplication : public TVirtualMCApplication
{
  public:
    /** default constructor */
    FairGeaneApplication();
    /** Special constructor, used for initializing G3 for Geane track propagation
    *@param Debug    true to print step info*/
    FairGeaneApplication(Bool_t Debug);
    /** default destructor */
    virtual ~FairGeaneApplication();
#if ROOT_VERSION_CODE < 333824
    /** Calculate user field  b at point x */
    void          Field(const Double_t* x, Double_t* b) const;      // MC Application
#endif
    /** Return Field used in simulation*/
    FairField*             GetField() {return fxField;}
    /** Initialize MC engine */
    void                  InitMC(const char* setup,  const char* cuts);
    /**
    * Set the magnetic field for simulation or Geane
    * @param field: magnetic field
    */
    void                   SetField(FairField* field);
    /** Define action at each step, dispatch the action to the corresponding detectors */
    void          GeaneStepping();                           // MC Application
    void ConstructGeometry();
    /** Singelton instance
     */
    static FairGeaneApplication* Instance();

    /**pure virtual functions that hasve to be implimented */

    void InitGeometry() {;}
    void GeneratePrimaries() {;}
    void BeginEvent() {;}
    void BeginPrimary() {;}
    void PreTrack() {;}
    void PostTrack() {;}
    void FinishPrimary() {;}
    void FinishEvent() {;}
    void Stepping() {;}
    void StopRun() {;}


  private:
    // data members
    /**Magnetic Field Pointer*/
    FairField*            fxField; //
    /**MC Engine 1= Geant3, 2 = Geant4*/
    Int_t                fMcVersion;     // mc Version
    /** Debug flag*/
    Bool_t               fDebug;//!
    TLorentzVector fTrkPos; //!

    ClassDef(FairGeaneApplication,1)  //Interface to MonteCarlo application
  private:
    FairGeaneApplication(const FairGeaneApplication&);
    FairGeaneApplication& operator=(const FairGeaneApplication&);
};

// inline functions

inline FairGeaneApplication* FairGeaneApplication::Instance()
{ return (FairGeaneApplication*)(TVirtualMCApplication::Instance());}

#endif

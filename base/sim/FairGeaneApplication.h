/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairGeaneApplication header file                   -----
// -----            Created 10/11/10  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#ifndef FAIR_GEANE_APPLICATION_H
#define FAIR_GEANE_APPLICATION_H

#include <Rtypes.h>                  // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>              // for Bool_t, Int_t
#include <TLorentzVector.h>          // for TLorentzVector
#include <TVirtualMCApplication.h>   // for TVirtualMCApplication

class FairField;
class TBuffer;
class TClass;
class TMemberInspector;

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
    /** Return Field used in simulation*/
    FairField* GetField() { return fxField; }
    /** Initialize MC engine */
    void InitMC(const char* setup, const char* cuts);
    /**
     * Set the magnetic field for simulation or Geane
     * @param field: magnetic field
     */
    void SetField(FairField* field);
    /** Define action at each step, dispatch the action to the corresponding detectors */
    void GeaneStepping();   // MC Application
    void ConstructGeometry();
    /** Singelton instance
     */
    static FairGeaneApplication* Instance();

    /**pure virtual functions that hasve to be implimented */

    void InitGeometry() { ; }
    void GeneratePrimaries() { ; }
    void BeginEvent() { ; }
    void BeginPrimary() { ; }
    void PreTrack() { ; }
    void PostTrack() { ; }
    void FinishPrimary() { ; }
    void FinishEvent() { ; }
    void Stepping() { ; }
    void StopRun() { ; }

  private:
    // data members
    /**Magnetic Field Pointer*/
    FairField* fxField;   //
    /**MC Engine 1= Geant3, 2 = Geant4*/
    Int_t fMcVersion;   // mc Version
    /** Debug flag*/
    Bool_t fDebug;            //!
    TLorentzVector fTrkPos;   //!

    // Interface to MonteCarlo application
    ClassDef(FairGeaneApplication, 1);

  private:
    FairGeaneApplication(const FairGeaneApplication&);
    FairGeaneApplication& operator=(const FairGeaneApplication&);
};

// inline functions

inline FairGeaneApplication* FairGeaneApplication::Instance()
{
    return static_cast<FairGeaneApplication*>(TVirtualMCApplication::Instance());
}

#endif

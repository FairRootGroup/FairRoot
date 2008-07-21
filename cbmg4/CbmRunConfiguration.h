// $Id: CbmRunConfiguration.h,v 1.2 2006/03/30 12:13:04 dbertini Exp $
// Category: run
//
// Author: I. Hrivnacova
//
// Class CbmRunConfiguration
// -------------------------
// This class creates all Cbm* specific action classes
// that will be initialized and managed by Geant4 kernel (G4RunManager).
// It creates also CbmRunMessenger that implements commands for
// CbmRun methods.

#ifndef Cbm_RUN_CONFIGURATION_H
#define Cbm_RUN_CONFIGURATION_H

#include "G4Types.hh"
#include "TG4RunConfiguration.h"

//#include "Rtypes.h"

//class G4RunManager;

class CbmRunConfiguration : public TG4RunConfiguration
{
  public:
    CbmRunConfiguration();
    // --> protected
    // CbmRunConfiguration(const CbmRunConfiguration& right);
    virtual ~CbmRunConfiguration();

  protected:
  // methods
    virtual G4bool      IsSpecialStacking() const{return kFALSE;}
  // methods
 //   virtual void CreateUserConfiguration();
    
  ClassDef(CbmRunConfiguration, 1) // Cbm* specific action classes for Geant4  
};

#endif //Cbm_RUN_CONFIGURATION_H


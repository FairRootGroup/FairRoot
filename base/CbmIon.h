// -------------------------------------------------------------------------
// -----                       CbmIon header file                      -----
// -----          Created 27/08/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/** CbmIon.h
 *@author V.Friese <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 **
 ** A class for the user definition of an ion. It will be instantiated
 ** from the constructor of the CbmIonGenerator.  
 **/


#ifndef CBMION_H
#define CBMION_H

#include "TNamed.h"

class CbmIon: public TNamed {
public:
  
  /** Default constructor **/
  CbmIon();


  /** Standard constructor 
   *@param name  name
   *@param z     atomic number
   *@param a     atomic mass
   *@param q     electric charge
   *@param e     excitation energy
   *@param m     mass [GeV]
   ** If mass is not given, it will be set to a times the proton mass.
   **/
   
  CbmIon(const char* name, Int_t z, Int_t a, Int_t q, Double_t e=0., Double_t m=0.);
  void SetParams( const char* name, Int_t z, Int_t a,
                 Int_t q, Double_t e=0., Double_t m=0.){
    SetName(name);
    fZ=z;
    fA=a;
    fQ=q;
    fExcEnergy=e;
    fMass=m;
  }
  /** Destructor **/
  virtual ~CbmIon();


  /** Accessors **/
  Int_t GetZ()            const { return fZ; }
  Int_t GetA()            const { return fA; }
  Int_t GetQ()            const { return fQ; }
  Double_t GetExcEnergy() const { return fExcEnergy; }
  Double_t GetMass()      const { return fMass; }


  /** Modifiers **/
  void SetExcEnergy(Double_t eExc) { fExcEnergy = eExc; }
  void SetMass(Double_t mass)      { fMass = mass; }


   
 private:     

  /** Data members **/
  static Int_t fgNIon;  //! Number of ions instantiated. One per generator.
  Int_t    fZ;          // Atomic number
  Int_t    fA;          // Atomic mass
  Int_t    fQ;          // Electric charge
  Double_t fExcEnergy;  // Excitation energy [GeV]
  Double_t fMass;       // Mass [GeV]


  ClassDef(CbmIon,1);
    
};

#endif

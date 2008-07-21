// -------------------------------------------------------------------------
// -----                CbmShieldGenerator header file                 -----
// -----                Created 15/09/06 by V. Friese                  -----
// -------------------------------------------------------------------------

/** CbmShieldGenerator
 *@author V.Friese  <v.friese@gsi.de>
 *@since 15.09.06
 *@version 1.0
 *
 ** The CbmShieldGenerator is similar to the CbmAsciiGenerator. It uses the
 ** ASCII output of the SHIELD code as input for simulation.
 ** The format of the event header is:
 ** event nr.; number of particles; beam momentum; impact parameter
 ** followed by a line for each particle of the format
 ** PID; A; Z; px; py; pz
 ** The PID must be given as for GEANT3. For ions, it is 1000. The total
 ** momentum is required, not momentum per nucleon.
**/


#ifndef CBMSHIELDGENERATOR_H
#define CBMSHIELDGENERATOR_H 1


#include "CbmGenerator.h"

#include <fstream>
#include <map>

class TDatabasePDG;
class CbmPrimaryGenerator;
class CbmIon;

class CbmShieldGenerator : public CbmGenerator  
{

 public: 

  /** Default constructor without arguments should not be used. **/
  CbmShieldGenerator();


  /** Standard constructor. 
   ** @param fileName The input file name
   **/
  CbmShieldGenerator(const char* fileName);


  /** Destructor. **/
  virtual ~CbmShieldGenerator();

	
  /** Reads on event from the input file and pushes the tracks onto
   ** the stack. Abstract method in base class.
   ** @param primGen  pointer to the CbmPrimaryGenerator
   **/
  virtual Bool_t ReadEvent(CbmPrimaryGenerator* primGen);



 private:

  ifstream*      fInputFile;          //! Input file stream
  const Char_t*  fFileName;           //! Input file Name
  TDatabasePDG*  fPDG;                //!  PDG database

	
  /** Private method CloseInput. Just for convenience. Closes the 
   ** input file properly. Called from destructor and from ReadEvent. **/
  void CloseInput();


  /** Private method RegisterIons. Goes through the input file and registers
   ** any ion needed. **/
  Int_t RegisterIons();



  /** STL map from ion name to CbmIon **/
  std::map<TString, CbmIon*> fIonMap;       //!
	
	
  ClassDef(CbmShieldGenerator,1);

};

#endif

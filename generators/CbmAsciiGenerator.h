// -------------------------------------------------------------------------
// -----                CbmAsciiGenerator header file                  -----
// -----          Created 09/06/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/**  CbmAsciiGenerator.h 
 *@author V.Friese  <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 *@author M.Al-Turany<M.Al-Turany@gsi.de>
 *
 The CbmAsciiGenerator reads an Ascii input file. The file must contain
 for each event a header line of the format  NTRACKS  IEV  VX VY VZ,
 where NTRACKS is the number of tracks in the event, IEV the event number,
 and VX, VY, VZ the event vertex coordinates in cm. The header line is
 followed by NTRACKS lines of the format G3PID, PX, PY, PZ, where
 G3PID is the GEANT3 particle code, and PX, PY, PZ the cartesian 
 momentum coordinates in GeV.
 Derived from CbmGenerator.
**/


#ifndef CBM_ASCIIGENERATOR_H
#define CBM_ASCIIGENERATOR_H


#include "CbmGenerator.h"

#include <fstream>

class TDatabasePDG;
class CbmPrimaryGenerator;



class CbmAsciiGenerator : public CbmGenerator  
{

 public: 

  /** Default constructor without arguments should not be used. **/
  CbmAsciiGenerator();


  /** Standard constructor. 
   ** @param fileName The input file name
   **/
  CbmAsciiGenerator(const char* fileName);


  /** Destructor. **/
  virtual ~CbmAsciiGenerator();

	
  /** Reads on event from the input file and pushes the tracks onto
   ** the stack. Abstract method in base class.
   ** @param primGen  pointer to the CbmPrimaryGenerator
   **/
  virtual Bool_t ReadEvent(CbmPrimaryGenerator* primGen);



 private:

  ifstream* fInputFile;               //! Input file stream
  const Char_t * fFileName;           //! Input file Name
	

  /** Private method CloseInput. Just for convenience. Closes the 
   ** input file properly. Called from destructor and from ReadEvent. **/
  void CloseInput();
	
	
  /** PDG data base */
  
//  TDatabasePDG *fPDG; //!

  ClassDef(CbmAsciiGenerator,1);

};

#endif

// -------------------------------------------------------------------------
// -----                    CbmGenerator header file                   -----
// -----          Created 09/06/04  by D. Bertini / V. Friese          -----
// -------------------------------------------------------------------------


/** CbmGenerator.h
 *@author D.Bertini <d.bertini@gsi.de>
 *@author V.Friese  <v.friese@gsi.de>
 *
The CbmGenerator is the abtract base class for the generators used to 
generate input for the transport simulation.Each concrete generator class 
derived from this one must implement the abtract method ReadEvent,
which has to use the method CbmPrimaryGenerator::AddTrack.
**/


#ifndef CBMGENERATOR_H
#define CBMGENERATOR_H

#include "TNamed.h"

//class TVirtualMCStack;
class CbmPrimaryGenerator;


class CbmGenerator : public TNamed 
{

 public:

  /** Default constructor. **/
  CbmGenerator();


  /** Constructor with name and title **/
  CbmGenerator(const char* name, const char *title="CBM Generator");


  /** Destructor. **/
  virtual ~CbmGenerator();


  /** Abstract method ReadEvent must be implemented by any derived class.
      It has to handle the generation of input tracks (reading from input 
      file) and the handing of the tracks to the CbmPrimaryGenerator. I
      t is called from CbmMCApplication.
      *@param pStack The stack
      *@return kTRUE if successful, kFALSE if not
  **/
  virtual Bool_t ReadEvent(CbmPrimaryGenerator* primGen) = 0;

  ClassDef(CbmGenerator,1);

private:
   CbmGenerator(const CbmGenerator &G);
   CbmGenerator& operator= (const CbmGenerator&) {return *this;}


};

#endif



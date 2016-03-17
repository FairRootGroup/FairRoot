/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 16.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGITIZE_H
#define PIXELDIGITIZE_H 1

#include "FairTask.h"

#include "PixelPoint.h"

#include <list>
#include <map>

class TClonesArray;
class PixelDigiPar;

class PixelDigitize : public FairTask
{

 public:

  /** Default constructor **/
  PixelDigitize();


  /** Standard constructor **/
  PixelDigitize(Int_t iVerbose);


  /** Constructor with name **/
  PixelDigitize(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelDigitize();


  /** Execution **/
  virtual void Exec(Option_t* opt);


 private:

  PixelDigiPar*     fDigiPar;

  TClonesArray*     fPoints;       /** Input array of PixelPoint **/
  TClonesArray*     fDigis;        /** Output array of PixelDigi **/

  Int_t             fNPoints;
  Int_t             fNDigis;

  Int_t             fTNofEvents;
  Int_t             fTNofPoints;
  Int_t             fTNofDigis;

  Int_t fFeCols;            // Colums read per Frontend 
  Int_t fFeRows;            // Rows read per Frontend
  Int_t fMaxFEperCol;       // max number of Frontend elemens per column
  Double_t fPitchX;         // Pixel cell size X
  Double_t fPitchY;         // Pixel cell size Y
  
  /** Activate pixel **/
  void ActivatePixel(Int_t index, Int_t detId, Int_t feId, Int_t col, Int_t row, Double_t charge, Double_t timestamp);


  /** Get parameter containers **/
  virtual void SetParContainers();


  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Reset eventwise counters **/
  void Reset();


  /** Finish at the end of each event **/
  virtual void Finish();

  PixelDigitize(const PixelDigitize&);
  PixelDigitize& operator=(const PixelDigitize&);

  ClassDef(PixelDigitize,1);

};

#endif



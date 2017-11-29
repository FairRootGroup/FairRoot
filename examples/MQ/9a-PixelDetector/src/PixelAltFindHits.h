/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelAltFindHits.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELALTFINDHITS_H
#define PIXELALTFINDHITS_H 1

#include "FairTask.h"

#include "PixelPoint.h"

#include "PixelPayload.h"

#include <list>
#include <map>
#include <string>

class TClonesArray;
class PixelDigiPar;
class FairGeoParSet;


class PixelAltFindHits : public FairTask
{

 public:

  /** Default constructor **/
  PixelAltFindHits();


  /** Standard constructor **/
  PixelAltFindHits(Int_t iVerbose);


  /** Constructor with name **/
  PixelAltFindHits(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelAltFindHits();


  /** Execution **/
  virtual void Exec(Option_t* opt);

  virtual void GetParList(TList* tempList);
  virtual void InitMQ    (TList* tempList);
  virtual void ExecMQ    (TList* inputList,TList* outputList);
  virtual void ExecMQ    (PixelPayload::Digi *digiPalVector,
			  int                 nofDigis,
		          PixelPayload::Hit  *hitPalVector,
			  int                &nofHits);

 private:

  PixelDigiPar*     fDigiPar;
  FairGeoParSet* fGeoParSet;


  TClonesArray*     fDigis;        /** Input array of PixelDigi **/
  TClonesArray*     fHits;         /** Output array of PixelHit **/

  Int_t             fNDigis;
  Int_t             fNHits;

  Int_t             fTNofEvents;
  Int_t             fTNofDigis;
  Int_t             fTNofHits;

  Int_t fFeCols;            // Colums read per Frontend 
  Int_t fFeRows;            // Rows read per Frontend
  Int_t fMaxFEperCol;       // max number of Frontend elemens per column
  Double_t fPitchX;         // Pixel cell size X
  Double_t fPitchY;         // Pixel cell size Y
  
  Int_t FindHit(Int_t detId, Int_t feId, Int_t col, Int_t row, Int_t index, 
		Double_t& posX, Double_t& posY, Double_t& posZ, 
		Double_t& errX, Double_t& errY, Double_t& errZ);

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

  PixelAltFindHits(const PixelAltFindHits&);
  PixelAltFindHits& operator=(const PixelAltFindHits&);

  ClassDef(PixelAltFindHits,1);

};

#endif



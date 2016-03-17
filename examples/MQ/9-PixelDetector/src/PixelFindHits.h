/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelFindHits.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELFINDHITS_H
#define PIXELFINDHITS_H 1

#include "FairTask.h"

#include "PixelPoint.h"

#include <list>
#include <map>
#include <string>

class TClonesArray;
class PixelDigiPar;
class FairGeoParSet;


class PixelFindHits : public FairTask
{

 public:

  /** Default constructor **/
  PixelFindHits();


  /** Standard constructor **/
  PixelFindHits(Int_t iVerbose);


  /** Constructor with name **/
  PixelFindHits(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelFindHits();


  /** Execution **/
  virtual void Exec(Option_t* opt);

// MQ
  void ExecMQ(Option_t* opt);
  TClonesArray* ExecMQ(TClonesArray* digis);
  void InitMQ(const std::string& root_file, const std::string& ascii_file);
  void UpdateParameter(PixelDigiPar* digipar, FairGeoParSet* geopar);

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

  PixelFindHits(const PixelFindHits&);
  PixelFindHits& operator=(const PixelFindHits&);

  ClassDef(PixelFindHits,1);

};

#endif



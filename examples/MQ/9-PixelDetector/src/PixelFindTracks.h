/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelFindTracks.h
 *
 *  Created on: 23.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELFINDTRACKS_H
#define PIXELFINDTRACKS_H 1

#include "FairTask.h"

#include "PixelHit.h"

#include <list>
#include <map>

class TClonesArray;
class TH2F;
class PixelDigiPar;

class PixelFindTracks : public FairTask
{

 public:

  /** Default constructor **/
  PixelFindTracks();


  /** Standard constructor **/
  PixelFindTracks(Int_t iVerbose);


  /** Constructor with name **/
  PixelFindTracks(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelFindTracks();


  /** Execution **/
  virtual void Exec(Option_t* opt);

  virtual void GetParList(TList* tempList);
  virtual void InitMQ    (TList* tempList);
  virtual void ExecMQ    (TList* inputList,TList* outputList);


 private:

  PixelDigiPar*     fDigiPar;

  TClonesArray*     fHits;         /** Input array of PixelHit **/
  TClonesArray*     fTracks;       /** Output array of PixelTrack **/

  Int_t             fTNofEvents;

  Int_t             fNHits;
  Int_t             fTNofHits;

  Int_t             fNTracks;
  Int_t             fTNofTracks;

  TH2F*             fhDist2D;

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

  PixelFindTracks(const PixelFindTracks&);
  PixelFindTracks& operator=(const PixelFindTracks&);

  ClassDef(PixelFindTracks,1);

};

#endif



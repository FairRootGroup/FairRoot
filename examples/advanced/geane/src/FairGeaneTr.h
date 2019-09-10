/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairGeaneTr.h
 *
 * @since 2019-09-10
 * @author R. Karabowicz
 */

#ifndef FAIRGEANETR_H
#define FAIRGEANETR_H 1


#include "FairTask.h"
#include "TVector3.h"
#include "FairGeanePro.h"

class TGeant3;
class TClonesArray;
class TTree;
class TFile;
class PixelPoint;

class FairGeaneTr : public FairTask
{
 public:
  /** Default constructor **/
  FairGeaneTr();

  /** Destructor **/
  ~FairGeaneTr();

  /** Virtual method Init **/
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);
 private:
  /** Input array of Points **/
  TClonesArray* fPointArray;
  PixelPoint	 *fPoint1;
  PixelPoint	 *fPoint2;

  /** Output array of Hits **/
  TClonesArray* fTrackParIni;   // initial MC track parameters
  TClonesArray* fTrackParFinal; // final MC track parameters
  TClonesArray* fTrackParGeane; // calculated track parameters
  TClonesArray* fTrackParWrong; // demonstrate effect of wrong charge

  TGeant3 *gMC3;
  ClassDef(FairGeaneTr,1);
  Int_t fEvent;
  FairGeanePro *fPro;
};

#endif //FAIRGEANETR_H

/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairTutGeaneTr.h
 *
 * @since 2019-09-10
 * @author R. Karabowicz
 */

#ifndef FAIRTUTGEANETR_H
#define FAIRTUTGEANETR_H 1


#include "FairTask.h"
#include "TVector3.h"
#include "FairGeanePro.h"

class TGeant3;
class TClonesArray;
class TTree;
class TFile;
class FairTutGeanePoint;

class FairTutGeaneTr : public FairTask
{
 public:
  /** Default constructor **/
  FairTutGeaneTr();

  /** Destructor **/
  ~FairTutGeaneTr();

  /** Virtual method Init **/
  virtual InitStatus Init();

  /** Virtual method Exec **/
  virtual void Exec(Option_t* opt);
 private:
  void Reset();

  /** Finish at the end of run **/
  virtual void Finish();

  /** Input array of Points **/
  TClonesArray* fPointArray;
  FairTutGeanePoint	 *fPoint1;
  FairTutGeanePoint	 *fPoint2;

  /** Output array of Hits **/
  TClonesArray* fTrackParIni;   // initial MC track parameters
  TClonesArray* fTrackParFinal; // final MC track parameters
  TClonesArray* fTrackParGeane; // calculated track parameters
  TClonesArray* fTrackParWrong; // demonstrate effect of wrong charge

  TGeant3 *gMC3;
  Int_t fEvent;
  FairGeanePro *fPro;

  ClassDef(FairTutGeaneTr,1);
};

#endif //FAIRTUTGEANETR_H

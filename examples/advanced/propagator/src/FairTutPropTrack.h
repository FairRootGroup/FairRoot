/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRTUTPROPTRACK_H_
#define FAIRTUTPROPTRACK_H_

#include "TObject.h"
#include "FairTrackParP.h"
#include "TRef.h"

class FairTutPropTrack : public TObject {
 public:
  FairTutPropTrack();
  FairTutPropTrack(int pdgcode, const FairTrackParP &first);

  void Print();

  //  FairTrackParP GetParamFirst() { return fTrackParamFirst; }

 private:
  int           fPdgCode;
  FairTrackParP fTrackParamFirst;

 public:
  ClassDef(FairTutPropTrack, 1)
};

#endif /* FAIRTUTPROPTRACK_H_ */

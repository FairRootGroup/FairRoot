/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----    FairTutorialDet4HitProducerIdealMissallign header file      -----
// -----                  Created 11.02.13 by F. Uhlig                 -----
// -------------------------------------------------------------------------


/** FairTutorialDet4HitProducerIdealMissallign.h
 *@author Florian Uhlig <f.uhlig@gsi.de>
 **
 ** The ideal hit producer produces hits of type CbmTutorialDetHit
 ** by copying the MCPoint position. At the same time it will shift
 ** the hit position by a given offset in x- and y-direction. This
 ** shift should mimic a missalignment of the detector due to inaccurate
 ** measurement of the detector positions.
 ** The position error is set to 1 mm.
 **/


#ifndef FAIRTUTORIALDET4HITPRODUCERIDEALMISSALLIGN_H
#define FAIRTUTORIALDET4HITPRODUCERIDEALMISSALLIGN_H 1

#include "FairTask.h"                   // for InitStatus, FairTask

#include "Rtypes.h"                     // for Bool_t, Double_t, etc
#include "TArrayD.h"                    // for TArrayD

class FairTutorialDet4MisalignPar;
class FairTutorialDet4GeoPar;
class FairTutorialDet4GeoHandler;
class TClonesArray;

class FairTutorialDet4HitProducerIdealMisalign : public FairTask
{

  public:

    /** Default constructor **/
    FairTutorialDet4HitProducerIdealMisalign();


    /** Destructor **/
    ~FairTutorialDet4HitProducerIdealMisalign();


    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method ReInit **/
    virtual InitStatus ReInit();

    virtual void SetParContainers();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    void DoMisalignment(Bool_t val) {fDoMisalignment=val;}

  private:

    /** Input array of CbmTofPoints **/
    TClonesArray* fPointArray; //!

    /** Output array of CbmTofHits **/
    TClonesArray* fHitArray;  //!

    TArrayD fShiftX;
    TArrayD fShiftY;
    TArrayD fShiftZ;
    TArrayD fRotX;
    TArrayD fRotY;
    TArrayD fRotZ;

    FairTutorialDet4MisalignPar* fDigiPar;
    FairTutorialDet4GeoHandler* fGeoHandler;
    FairTutorialDet4GeoPar* fGeoPar;

    Bool_t fDoMisalignment;
  private:

    Double_t GetHitErr(Double_t sigma);

    FairTutorialDet4HitProducerIdealMisalign(const FairTutorialDet4HitProducerIdealMisalign&);
    FairTutorialDet4HitProducerIdealMisalign& operator=(const FairTutorialDet4HitProducerIdealMisalign&);

    ClassDef(FairTutorialDet4HitProducerIdealMisalign,1);

};

#endif

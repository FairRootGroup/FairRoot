// -------------------------------------------------------------------------
// -----    FairTutorialDetHitProducerIdealMissallign header file      -----
// -----                  Created 11.02.13 by F. Uhlig                 -----
// -------------------------------------------------------------------------


/** FairTutorialDetHitProducerIdealMissallign.h
 *@author Florian Uhlig <f.uhlig@gsi.de>
 **
 ** The ideal hit producer produces hits of type CbmTutorialDetHit
 ** by copying the MCPoint position. At the same time it will shift
 ** the hit position by a given offset in x- and y-direction. This
 ** shift should mimic a missalignment of the detector due to inaccurate
 ** measurement of the detector positions.
 ** The position error is set to 1 mm.
 **/


#ifndef FAIRTUTORIALDETHITPRODUCERIDEALMISSALLIGN_H
#define FAIRTUTORIALDETHITPRODUCERIDEALMISSALLIGN_H 1


#include "FairTask.h"

#include "TArrayD.h"

class FairTutorialDetMissallignPar;
class TClonesArray;

class FairTutorialDetHitProducerIdealMissallign : public FairTask
{

  public:

    /** Default constructor **/
    FairTutorialDetHitProducerIdealMissallign();


    /** Destructor **/
    ~FairTutorialDetHitProducerIdealMissallign();


    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method ReInit **/
    virtual InitStatus ReInit();

    virtual void SetParContainers();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);


  private:

    /** Input array of CbmTofPoints **/
    TClonesArray* fPointArray; //!

    /** Output array of CbmTofHits **/
    TClonesArray* fHitArray;  //!

    TArrayD fShiftX;
    TArrayD fShiftY;

    FairTutorialDetMissallignPar* fDigiPar;

  private:

    FairTutorialDetHitProducerIdealMissallign(const FairTutorialDetHitProducerIdealMissallign&);
    FairTutorialDetHitProducerIdealMissallign& operator=(const FairTutorialDetHitProducerIdealMissallign&);

    ClassDef(FairTutorialDetHitProducerIdealMissallign,1);

};

#endif

// -------------------------------------------------------------------------
// -----                 FairTutorialDetGeoHandler header file                  -----
// -----                 Created 20/11/12  by F. Uhlig                 -----
// -------------------------------------------------------------------------


/** FairTutorialDetGeoHandler.h
 ** Helper class to extract information from the GeoManager which is
 ** needed in many other TOF classes. This helper class should be a
 ** single place to hold all these functions.
 ** @author F. Uhlig <f.uhlig@gsi.de>
 **/

#ifndef FAIRTUTORIALDETGEOHANDLER_H
#define FAIRTUTORIALDETGEOHANDLER_H 1

#include "TObject.h"

#include <map>

class FairLogger;
class TGeoBBox;
class TGeoVolume;
class TGeoHMatrix;

class FairTutorialDetGeoHandler : public TObject
{
  public:

    /** Constructor **/
    FairTutorialDetGeoHandler();


    /** Destructor **/
    ~FairTutorialDetGeoHandler() {};

    Int_t GetUniqueDetectorId();
    Int_t GetUniqueDetectorId(TString volName);

//  Int_t GetDetectorId(Int_t uniqueId);

    Int_t Init(Bool_t isSimulation=kFALSE);

    void FillDetectorInfoArray(Int_t uniqueId);
    void NavigateTo(TString volName);

    // Implement Interface functions to the TGeoManager to be
    // the same as for the VMC
    Int_t CurrentVolOffID(Int_t off, Int_t& copy) const;
    Int_t CurrentVolID(Int_t& copy) const;
    Int_t VolId(const Text_t* name) const;
    Int_t VolIdGeo(const char* name) const;
    const char* CurrentVolName() const;
    const char* CurrentVolOffName(Int_t off) const;

//  Int_t CheckGeometryVersion();

  private:

    Bool_t fIsSimulation; //!

    Int_t fLastUsedDetectorID;  //!

    UInt_t fGeoPathHash;        //!
    TGeoVolume* fCurrentVolume; //!
    TGeoBBox* fVolumeShape;     //!
    Double_t fGlobal[3];        //! Global centre of volume
    TGeoHMatrix* fGlobalMatrix; //!

    FairTutorialDetGeoHandler(const FairTutorialDetGeoHandler&);
    FairTutorialDetGeoHandler operator=(const FairTutorialDetGeoHandler&);

    ClassDef(FairTutorialDetGeoHandler,1)

};


#endif //FAIRTUTORIALDETGEOHANDLER_H


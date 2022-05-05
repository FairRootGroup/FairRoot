/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIR_VOLUME_H
#define FAIR_VOLUME_H

#include "FairModule.h"

#include <Rtypes.h>    // for Int_t, FairVolume::Class, etc
#include <TNamed.h>    // for TNamed
#include <TString.h>   // for TString

class FairDetector;
class FairGeoNode;

/**
 * This Object is only used for internal book keeping!
 * @author M. Al-Turany, D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class FairVolume : public TNamed
{
  public:
    FairVolume();
    FairVolume(const TString& name, Int_t id = 0, Int_t modId = 0, FairModule* fMod = nullptr);
    ~FairVolume() override;

    void setRealName(TString name) { fRealName = name; }
    const char* getRealName() const { return fRealName.Data(); }
    Int_t getVolumeId() const { return fVolumeId; }
    Int_t getModId() const { return fModId; }
    void setModId(Int_t id) { fModId = id; }
    void setCopyNo(Int_t id) { fCopyNo = id; }
    void setVolumeId(Int_t id) { fVolumeId = id; }
    void setGeoNode(FairGeoNode* d) { fNode = d; }
    void setMotherId(Int_t fM) { fMotherId = fM; }
    void setMotherCopyNo(Int_t copyNo) { fMotherCopyNo = copyNo; }

    FairModule* GetModule() const { return fModule; }
    FairDetector* GetDetector() const { return fDetector; }
    void SetModule(FairModule* mod);

    Int_t getMCid() const { return fMCid; }
    Int_t getCopyNo() const { return fCopyNo; }
    void setMCid(Int_t id) { fMCid = id; }
    FairGeoNode* getGeoNode() const { return fNode; }
    Int_t getMotherId() const { return fMotherId; }
    Int_t getMotherCopyNo() const { return fMotherCopyNo; }

  private:
    FairVolume(const FairVolume&);
    FairVolume& operator=(const FairVolume&);

    TString fRealName{""};            /**Volume Name in ASCII file*/
    Int_t fVolumeId{-1};              /**Volume Id in GeoManager*/
    Int_t fModId{-1};                 /**Module Id in which this volume exist*/
    Int_t fMCid{-1};                  /**Volume Id in MC*/
    Int_t fCopyNo{-1};                /**Volume Copy No*/
    Int_t fMotherId{-1};              /**Mother Volume Id*/
    Int_t fMotherCopyNo{-1};          /**Mother Volume Copy No*/
    FairDetector* fDetector{nullptr}; /** The Detector which will proccess the hits for this volume*/
    FairModule* fModule{nullptr};     /**The Module in which the volume is */
    FairGeoNode* fNode{nullptr};      /**Node corresponding to this volume*/

    ClassDefOverride(FairVolume, 2);
};

#endif

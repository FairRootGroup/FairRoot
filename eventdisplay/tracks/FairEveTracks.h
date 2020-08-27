/*
 * FairEveTracks.h
 *
 *  Created on: 4 maj 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIRTEVERACKS_H_
#define FAIRTEVERACKS_H_
#include "FairEventManager.h"
#include "FairTask.h"

#include <Rtypes.h>
#include <RtypesCore.h>
#include <TClonesArray.h>
#include <TEveElement.h>
#include <TEveTrack.h>
#include <TEveTrackPropagator.h>
#include <TGeoTrack.h>
#include <TNamed.h>

/**
 * base evelement that represents tracks
 */
class FairEveTracks
    : public TEveElement
    , public TNamed
{
    FairEventManager *fEventManager;
    TObjArray *fEveTrList;
    Double_t fPt[2];
    Double_t fEta[2];
    Double_t fEnergy[2];
    Bool_t fUsePt;
    Bool_t fUseEta;
    Bool_t fUseEnergy;

  protected:
    Double_t GetPtMin() const { return fPt[0]; };
    Double_t GetPtMax() const { return fPt[1]; };
    Double_t GetEtaMin() const { return fEta[0]; };
    Double_t GetEtaMax() const { return fEta[1]; }
    Double_t GetEnergyMin() const { return fEnergy[0]; };
    Double_t GetEnergyMax() const { return fEnergy[1]; };
    ;
    Bool_t UsePtCut() const { return fUsePt; };
    Bool_t UseEtaCut() const { return fUseEta; };
    Bool_t UseEnergyCut() const { return fUseEnergy; };
    TEveTrackPropagator *fTrPropagator;
    TEveTrackList *fTrackGroup;
    /**
     * reset object group (track groups)
     */
    void ResetGroup();
    FairEventManager *GetEventManager() const { return fEventManager; };
    TObjArray *GetTracksList() const { return fEveTrList; };
    /**
     *
     * @param tr
     * @return track group based on parameter
     */
    virtual TEveTrackList *GetTrackGroup(void *tr) = 0;

  public:
    FairEveTracks();
    /**
     * makes visible tracks not visible, hidden tracks become visible
     */
    virtual void SwapTracks();
    /**
     * set pt cut, cut is used only if use = kTRUE
     * @param min
     * @param max
     * @param use
     */
    void SetPtCut(Double_t min, Double_t max, Bool_t use)
    {
        fPt[0] = min;
        fPt[1] = max;
        fUsePt = use;
    };
    /**
     * set pseudorapidity cut, cut is used only if use = kTRUE
     * @param min
     * @param max
     * @param use
     */
    void SetEtaCut(Double_t min, Double_t max, Bool_t use)
    {
        fEta[0] = min;
        fEta[1] = max;
        fUseEta = use;
    }
    /**
     * set energy cut, cut is used only if use = kTRUE
     * @param min
     * @param max
     * @param use
     */
    void SetEnergyCut(Double_t min, Double_t max, Bool_t use)
    {
        fEnergy[0] = min;
        fEnergy[1] = max;
        fUseEnergy = use;
    }
    /**
     * reset group, repaint tracks assigned to this class
     */
    virtual void Repaint() = 0;
    virtual InitStatus Init();
    virtual ~FairEveTracks();
    ClassDef(FairEveTracks, 0)
};

#endif /* FAIRTEVERACKS_H_ */

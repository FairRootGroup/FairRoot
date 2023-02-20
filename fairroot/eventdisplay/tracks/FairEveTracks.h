/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
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

#include <Rtypes.h>       // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>   // for Double_t, Bool_t, kFALSE, Color_t
#include <TEveElement.h>  // for TEveElement
#include <TNamed.h>       // for TNamed
#include <TString.h>      // for TString
#include "FairTask.h"     // for InitStatus
class FairEventManager;  // lines 23-23
class TBuffer;
class TClass;
class TEveTrackList;  // lines 24-24
class TMemberInspector;


/**
 * base evelement that represents tracks
 */
class FairEveTracks
    : public TEveElement
    , public TNamed
{
    FairEventManager *fEventManager;   //!
    Double_t fPt[2];
    Double_t fEta[2];
    Double_t fEnergy[2];
    Bool_t fUsePt;
    Bool_t fUseEta;
    Bool_t fUseEnergy;
    const Bool_t fAcceptCompound;

  protected:
    Double_t GetPtMin() const { return fPt[0]; };
    Double_t GetPtMax() const { return fPt[1]; };
    Double_t GetEtaMin() const { return fEta[0]; };
    Double_t GetEtaMax() const { return fEta[1]; }
    Double_t GetEnergyMin() const { return fEnergy[0]; };
    Double_t GetEnergyMax() const { return fEnergy[1]; };
    Bool_t UsePtCut() const { return fUsePt; };
    Bool_t UseEtaCut() const { return fUseEta; };
    Bool_t UseEnergyCut() const { return fUseEnergy; };
    FairEventManager *GetEventManager() const { return fEventManager; };
    /**
     *
     * @param groupName - name of the track group
     * @param color - group color
     * @return track group based on parameter
     */
    TEveTrackList *FindTrackGroup(TString groupName, Color_t color);

  public:
    /**
     *
     * @param acceptCompound use compound tracks in track list
     */
    FairEveTracks(Bool_t acceptCompound = kFALSE);
    /**
     * makes visible tracks not visible, hidden tracks become visible
     */
    void ToggleTracks();
    /**
     * makes visible group of tracks that was not visible, hiden groups become visible
     */
    void ToggleGroups();
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

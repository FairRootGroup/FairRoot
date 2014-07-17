/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
* class for event management and navigation.
* 06.12.07 M.Al-Turany
*/
#ifndef FairEventManager_H
#define FairEventManager_H

#include "TEveEventManager.h"           // for TEveEventManager

#include "FairRunAna.h"                 // for FairRunAna

#include "Rtypes.h"                     // for Float_t, Int_t, Bool_t, etc

class FairRootManager; //does not work with streamer, reason unclear
class FairTask;
class TGListTreeItem;

class FairEventManager : public TEveEventManager
{
  public:
    static FairEventManager* Instance();
    FairEventManager();
    virtual ~FairEventManager();
    virtual void Open();
    virtual void GotoEvent(Int_t event); // *MENU*
    virtual void NextEvent();   // *MENU*
    virtual void PrevEvent();   // *MENU*
    virtual void Close();
    virtual void DisplaySettings();       //  *Menu*
    virtual Int_t Color(Int_t pdg);
    void AddTask(FairTask* t) {fRunAna->AddTask(t);}
    virtual void Init( Int_t visopt = 1, Int_t vislvl = 3, Int_t maxvisnds = 10000);
    virtual Int_t GetCurrentEvent() {return fEntry;}
    virtual void SetPriOnly(Bool_t Pri) {fPriOnly=Pri;}
    virtual Bool_t IsPriOnly() {return fPriOnly;}
    virtual void SelectPDG(Int_t PDG) {fCurrentPDG= PDG;}
    virtual Int_t GetCurrentPDG() {return fCurrentPDG;}
    virtual void SetMaxEnergy( Float_t max) {fMaxEnergy = max;}
    virtual void SetMinEnergy( Float_t min) {fMinEnergy = min;}
    virtual void SetEvtMaxEnergy( Float_t max) {fEvtMaxEnergy = max;}
    virtual void SetEvtMinEnergy( Float_t min) {fEvtMinEnergy = min;}
    virtual Float_t GetEvtMaxEnergy() {return fEvtMaxEnergy ;}
    virtual Float_t GetEvtMinEnergy() {return fEvtMinEnergy ;}
    virtual Float_t GetMaxEnergy() {return fMaxEnergy;}
    virtual Float_t GetMinEnergy() {return fMinEnergy;}
    void UpdateEditor();
    virtual void AddParticlesToPdgDataBase(Int_t pdg=0);

    ClassDef(FairEventManager,1);
  private:
    FairRootManager* fRootManager; //!
    Int_t fEntry;                 //!
    FairRunAna* fRunAna;          //!
    TGListTreeItem*  fEvent;     //!
    Bool_t fPriOnly;             //!
    Int_t fCurrentPDG;           //!
    Float_t fMinEnergy;         //!
    Float_t fMaxEnergy;         //!
    Float_t fEvtMinEnergy;         //!
    Float_t fEvtMaxEnergy;         //!

    static FairEventManager*    fgRinstance; //!

    FairEventManager(const FairEventManager&);
    FairEventManager& operator=(const FairEventManager&);
};

#endif

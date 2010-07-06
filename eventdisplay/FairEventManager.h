/**
* class for event management and navigation.
* 06.12.07 M.Al-Turany
*/
#ifndef FairEventManager_H
#define FairEventManager_H

#include "TEveEventManager.h"

#include "FairRunAna.h"
#include "FairRootManager.h"

class FairRootManager; //does not work with streamer, reason unclear
class FairTask;
class TList;

class FairEventManager : public TEveEventManager
{
public:
   static FairEventManager *Instance();
   FairEventManager();
   virtual ~FairEventManager();
   virtual void Open();
   virtual void GotoEvent(Int_t event); // *MENU*
   virtual void NextEvent();   // *MENU*
   virtual void PrevEvent();   // *MENU*
   virtual void Close();
   void DisplaySettings();       //  *Menu*
   Int_t Color(Int_t pdg);
   void AddTask(FairTask *t){fRunAna->AddTask(t);}
   void Init();
   Int_t GetCurrentEvent(){return fEntry;}
   void SetPriOnly(Bool_t Pri){fPriOnly=Pri;}
   Bool_t IsPriOnly(){return fPriOnly;}
   void SelectPDG(Int_t PDG){fCurrentPDG= PDG;}
   Int_t GetCurrentPDG(){return fCurrentPDG;}
   void SetMaxEnergy( Float_t max){fMaxEnergy = max;}
   void SetMinEnergy( Float_t min){fMinEnergy = min;}
   void SetEvtMaxEnergy( Float_t max){fEvtMaxEnergy = max;}
   void SetEvtMinEnergy( Float_t min){fEvtMinEnergy = min;}
   Float_t GetEvtMaxEnergy(){return fEvtMaxEnergy ;}
   Float_t GetEvtMinEnergy(){return fEvtMinEnergy ;}
   Float_t GetMaxEnergy(){return fMaxEnergy;}
   Float_t GetMinEnergy(){return fMinEnergy;}
   void UpdateEditor();
   void AddParticlesToPdgDataBase() ;

   ClassDef(FairEventManager,1);
private:
   FairRootManager *fRootManager; //!
   Int_t fEntry;                 //!
   FairRunAna *fRunAna;          //!
   TGListTreeItem  *fEvent;     //!
   Bool_t fPriOnly;             //!
   Int_t fCurrentPDG;           //!
   Float_t fMinEnergy;         //!
   Float_t fMaxEnergy;         //!
   Float_t fEvtMinEnergy;         //!
   Float_t fEvtMaxEnergy;         //!

   static FairEventManager*    fgRinstance; //!
};

#endif

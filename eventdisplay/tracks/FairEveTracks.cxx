/*
 * FairTracks.cxx
 *
 *  Created on: 4 maj 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#include "FairEveTracks.h"

#include "FairEveTrack.h"

#include <TEveElement.h>
#include <TEveManager.h>
#include <TEveSelection.h>
#include <TEveTrack.h>

FairEveTracks::FairEveTracks()
    : fEventManager(nullptr)
    , fEveTrList(nullptr)
    , fPt{0, 10}
    , fEta{-10, 10}
    , fEnergy{0, 10}
    , fUsePt(kFALSE)
    , fUseEta(kFALSE)
    , fUseEnergy(kFALSE)
    , fTrPropagator(nullptr)
    , fTrackGroup(nullptr)
{
    fTrPropagator = new TEveTrackPropagator();
    fEveTrList = new TObjArray();
}

void FairEveTracks::ResetGroup()
{
    TEveElement *el = dynamic_cast<TEveElement *>(this);
    if (el == nullptr)
        return;
    for (Int_t i = 0; i < fEveTrList->GetEntriesFast(); i++) {
        TEveTrackList *ele = static_cast<TEveTrackList *>(fEveTrList->At(i));
        gEve->RemoveElement(ele, el);
    }
    fEveTrList->Clear();
}

void FairEveTracks::SwapTracks()
{
    for (int i = 0; i < fEveTrList->GetEntriesFast(); i++) {
        TEveTrackList *eveList = (TEveTrackList *)fEveTrList->UncheckedAt(i);
        for (TEveElement::List_i iter = eveList->BeginChildren(); iter != eveList->EndChildren(); ++iter) {
            FairEveTrack *el = dynamic_cast<FairEveTrack *>((*iter));
            if (el->GetRnrSelf()) {
                el->SetRnrSelfChildren(kFALSE, kFALSE);
            } else {
                el->SetRnrSelfChildren(kTRUE, kTRUE);
            }
        }
    }
    gEve->Redraw3D(kFALSE);
}

InitStatus FairEveTracks::Init()
{
    fEventManager = FairEventManager::Instance();
    return kSUCCESS;
}

FairEveTracks::~FairEveTracks()
{
    // TODO Auto-generated destructor stub
}

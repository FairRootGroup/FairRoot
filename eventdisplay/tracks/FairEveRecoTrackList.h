/*
 * FairEveRecoTrackList.h
 *
 *  Created on: 17 cze 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVERECOTRACKLIST_H_
#define FAIREVERECOTRACKLIST_H_

#include <TEvePointSet.h>
#include <TEveTrackPropagator.h>
#include <TEveCompound.h>
#include <TEveTrack.h>
#include <TGedFrame.h>
#include "FairEveRecoTrack.h"
#include "TEveTrackEditor.h"

class FairEveRecoTrackList: public TEveTrackList{
public:
    FairEveRecoTrackList(){fChildClass=FairEveRecoTrack::Class();};
    FairEveRecoTrackList(TString name, TEveTrackPropagator *prop=0);
    void SetLineColor(Color_t col);
    void SetLineStyle (Style_t s);
    void SetLineWidth (Width_t w);
    void SetMarkerColor (Color_t c);
    void SetMarkerSize (Size_t s);
    void SetMarkerStyle (Style_t s);
    virtual Bool_t AcceptElement(TEveElement* el);
    virtual ~FairEveRecoTrackList();
    ClassDef(FairEveRecoTrackList,0)
};



#endif /* FAIREVERECOTRACKLIST_H_ */

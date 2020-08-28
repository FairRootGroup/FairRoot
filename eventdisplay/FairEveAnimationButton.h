/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveAnimationButton.h
 *
 *  Created on: 26 maj 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVEANIMATIONBUTTON_H_
#define FAIREVEANIMATIONBUTTON_H_

#include <GuiTypes.h>
#include <Rtypes.h>
#include <RtypesCore.h>
#include <TGButton.h>
#include <TGComboBox.h>
#include <TGDoubleSlider.h>
#include <TGFrame.h>
#include <TGLabel.h>
#include <TGNumberEntry.h>
#include <TGedFrame.h>   // for TGedFrame
#include <TObject.h>

class FairEveAnimationButton : public TNamed
{
    const Int_t fWidth;
    Double_t fValMin, fValMax;
    TString fFunctionName;
    TGedFrame *fParent;
    TGCompositeFrame *fTab;
    TGNumberEntry *fMin;
    TGNumberEntry *fMax;
    TGNumberEntry *fStep;
    TGComboBox *fComboOpt;
    TGComboBox *fTypeOpt;

  public:
    enum eAnimationType
    {
        kEventByEvent = 0,
        kTimeSlice = 1
    };
    enum eScreenshotType
    {
        k3D = 0,
        kXY = 1,
        kZ = 2,
        kAll = 3
    };
    FairEveAnimationButton(TGedFrame *frame = 0,
                           TGCompositeFrame *tab = 0,
                           TString name = "",
                           Int_t width = 170,
                           Int_t buttons = 2);
    /**
     * set name of function called when button is pressed
     * @param name
     */
    void SetFunctionName(TString name) { fFunctionName = name; };
    void SetMinMax(Double_t min, Double_t max)
    {
        fValMin = min;
        fValMax = max;
    };
    void Init();
    eScreenshotType GetScreenshotType();
    eAnimationType GetAnimationType();
    Double_t GetMin();
    Double_t GetMax();
    Double_t GetStep();
    virtual ~FairEveAnimationButton();

    ClassDef(FairEveAnimationButton, 1)
};

#endif /* FAIREVEANIMATIONBUTTON_H_ */

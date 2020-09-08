/********************************************************************************
 *    Copyright (C) 2020 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIREVETRANSPARENCYCONTROL_H_
#define FAIREVETRANSPARENCYCONTROL_H_

#include <Rtypes.h>
#include <TGButton.h>
#include <TGFrame.h>

class TGNumberEntry;

class FairEveTransparencyControl : public TGHorizontalFrame
{
    TGCheckButton *fCheck;
    TGNumberEntry *fNumber;

  public:
    FairEveTransparencyControl(TGFrame const *parent, char const *label = "Transparency");

    TGCheckButton *GetCheck() const { return fCheck; }
    TGNumberEntry *GetNumber() const { return fNumber; }

    void Toggled(Bool_t);   // SLOT to receive check button events
    void ValueSet();        // SLOT to receive number entry events

    virtual ~FairEveTransparencyControl(){};

    ClassDef(FairEveTransparencyControl, 1)
};

#endif /* FAIREVETRANSPARENCYCONTROL_H_ */

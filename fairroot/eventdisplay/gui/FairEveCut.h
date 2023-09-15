/********************************************************************************
 * Copyright (C) 2020-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairEveCut.h
 *
 *  Created on: 5 maj 2020
 *      Author: Daniel Wielanek
 *		E-mail: daniel.wielanek@gmail.com
 *		Warsaw University of Technology, Faculty of Physics
 */
#ifndef FAIREVECUT_H_
#define FAIREVECUT_H_
#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for Bool_t, Int_t, Double_t, kTRUE
#include <TGButton.h>    // for TGCheckButton
#include <TObject.h>     // for TObject
#include <TString.h>     // for TString
class TBuffer;
class TClass;
class TGCompositeFrame;
class TGNumberEntry;  // lines 25-25
class TGedFrame;

/**
 * base class for graphics cuts
 */
class FairEveCut : public TObject
{
  protected:
    const Int_t fWidth;
    const TString fName;
    TGedFrame *fParent;
    TGCompositeFrame *fTab;

  public:
    /**
     * default c-tor
     * @param frame paretn frame (editor)
     * @param tab tab in editor
     * @param name name of the cut
     * @param width width of frame
     */
    FairEveCut(TGedFrame *frame = 0, TGCompositeFrame *tab = 0, TString name = "", Int_t width = 170);
    virtual void Init() = 0;
    void AddUpdateButton();
    virtual ~FairEveCut();
    ClassDef(FairEveCut, 0)
};

/**
 * cut for selection of objects with properting from given range
 */
class FairEveMinMaxCut : public FairEveCut
{
    TGCheckButton *fUseCut;
    TGNumberEntry *fLow;
    TGNumberEntry *fHigh;

  public:
    FairEveMinMaxCut(TGedFrame *frame = 0, TGCompositeFrame *tab = 0, TString name = "", Int_t width = 170);
    void Init();
    Bool_t GetValues(Double_t &min, Double_t &max) const;
    virtual ~FairEveMinMaxCut();
    ClassDef(FairEveMinMaxCut, 0)
};

/**
 * represents booealn cut, check button is used to accept objects
 */
class FairEveBoolCut : public FairEveCut
{
    TGCheckButton *fHasCut;
    Bool_t fStatus;
    Bool_t fAutoUpdate;

  public:
    FairEveBoolCut(TGedFrame *frame = 0, TGCompositeFrame *tab = 0, TString name = "", Int_t width = 170);
    void Init();
    void UpdateWhenChanged() { fAutoUpdate = kTRUE; };
    void SetInitStatus(Bool_t stat) { fStatus = stat; };
    Bool_t GetValue() const { return fHasCut->IsOn(); };
    virtual ~FairEveBoolCut();
    ClassDef(FairEveBoolCut, 0)
};

/**
 * cut for selection of particles with given property expressed as an integer nubmer
 */
class FairEveIntCut : public FairEveCut
{
    TGCheckButton *fUseCut;
    TGNumberEntry *fCut;

  public:
    FairEveIntCut(TGedFrame *frame = 0, TGCompositeFrame *tab = 0, TString name = "", Int_t width = 170);
    void Init();
    Bool_t GetValue(Int_t &val) const;
    virtual ~FairEveIntCut(){};
    ClassDef(FairEveIntCut, 0)
};

#endif /* FAIREDTABEDITOR_H_ */

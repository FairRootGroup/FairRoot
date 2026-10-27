/********************************************************************************
 *                  Copyright (C) 2026 Jagiellonian University                  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRSHAPESET_H
#define FAIRSHAPESET_H

#include "FairShapeSetDraw.h"   // for FairShapeSetDraw

#include <Rtypes.h>       // for Double_t, FairShapeSet::Class, etc
#include <TEveBoxSet.h>   // for TEveShapeSet

class FairShapeSet : public TEveBoxSet
{
  public:
    FairShapeSet(FairShapeSetDraw* drawer, const char* name = "FairShapeSet", const char* t = "")
        : TEveBoxSet(name, t)
        , fDraw(drawer) {};
    FairShapeSet(const FairShapeSet&) = delete;
    FairShapeSet(FairShapeSet&&) = delete;
    FairShapeSet operator=(const FairShapeSet&) = delete;
    FairShapeSet operator=(FairShapeSet&&) = delete;
    virtual ~FairShapeSet() = default;

    void SetTimeWindowPlus(Double_t time) { fDraw->SetTimeWindowPlus(time); }
    void SetTimeWindowMinus(Double_t time) { fDraw->SetTimeWindowMinus(time); }

    Double_t GetTimeWindowPlus() { return fDraw->GetTimeWindowPlus(); }
    Double_t GetTimeWindowMinus() { return fDraw->GetTimeWindowMinus(); }

  private:
    FairShapeSetDraw* fDraw{nullptr};

    ClassDef(FairShapeSet, 1);
};

#endif

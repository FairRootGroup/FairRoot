/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "FairTut8RawItem.h"

FairTut8RawItem::FairTut8RawItem()
    : TObject()
    , fSam(0)
    , fGtb(0)
    , fTacAddr(0)
    , fTacCh(0)
    , fCal(0)
    , fClock(0)
    , fTacData(0)
    , fQdcData(0)
{
}

FairTut8RawItem::FairTut8RawItem(UShort_t sam,
                                 UShort_t gtb,
                                 UShort_t tacAddr,
                                 UShort_t tacCh,
                                 UShort_t cal,
                                 UShort_t clock,
                                 UShort_t tacData,
                                 UShort_t qdcData)
    : TObject()
    , fSam(sam)
    , fGtb(gtb)
    , fTacAddr(tacAddr)
    , fTacCh(tacCh)
    , fCal(cal)
    , fClock(clock)
    , fTacData(tacData)
    , fQdcData(qdcData)
{
}

FairTut8RawItem::FairTut8RawItem(const FairTut8RawItem& right)
    : TObject(right)
    , fSam(right.fSam)
    , fGtb(right.fGtb)
    , fTacAddr(right.fTacAddr)
    , fTacCh(right.fTacCh)
    , fCal(right.fCal)
    , fClock(right.fClock)
    , fTacData(right.fTacData)
    , fQdcData(right.fQdcData)
{
}

ClassImp(FairTut8RawItem)

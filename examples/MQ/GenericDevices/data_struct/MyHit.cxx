/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   MyHit.cxx
 * Author: winckler
 * 
 * Created on November 24, 2014, 1:40 PM
 */

#include "MyHit.h"
#include "MyHit.h"

MyHit::MyHit()
    : FairHit()
{
}

MyHit::MyHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos)
    : FairHit(detID, pos, dpos, mcindex)
{
}

MyHit::MyHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos, Double_t timeStamp, Double_t timeStampError)
    : FairHit(detID, pos, dpos, mcindex)//
{
	SetTimeStamp(timeStamp);
	SetTimeStampError(timeStampError);
}

MyHit::~MyHit()
{
}

ClassImp(MyHit)
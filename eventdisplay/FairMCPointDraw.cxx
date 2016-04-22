/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCPointsDraw.cpp
 *
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#include "FairMCPointDraw.h"

#include "FairMCPoint.h"                // for FairMCPoint

#include "TVector3.h"                   // for TVector3

class TObject;

FairMCPointDraw::FairMCPointDraw()
{
  // TODO Auto-generated constructor stub

}

FairMCPointDraw::~FairMCPointDraw()
{
  // TODO Auto-generated destructor stub
}

TVector3 FairMCPointDraw::GetVector(TObject* obj)
{
  FairMCPoint* p = static_cast<FairMCPoint*>(obj);
  return TVector3(p->GetX(), p->GetY(), p->GetZ());
}


ClassImp(FairMCPointDraw)

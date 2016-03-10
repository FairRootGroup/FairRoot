/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#include "PixelFindHitsTask.h"

// Includes from base
//#include "FairRootManager.h"
//#include "FairRunAna.h"
//#include "FairRuntimeDb.h"
#include "FairLink.h"
//#include "FairLogger.h"

// Includes from ROOT
#include "TClonesArray.h"
#include "TObjArray.h"
#include "TMath.h"
#include "TGeoManager.h"
#include "TGeoNode.h"
#include "TGeoVolume.h"
#include "TGeoBBox.h"

#include "PixelDigi.h"
#include "PixelHit.h"
#include "PixelDigiPar.h"

#include <map>

 // 
#include "FairParRootFileIo.h"
#include "FairParAsciiFileIo.h"
#include "FairGeoParSet.h"
#include "FairMQLogger.h"

using std::pair;
using std::map;



// -----   Default constructor  -----------------------------------------
PixelFindHitsTask::PixelFindHitsTask() 
  : fGeoParSet(nullptr)
  , fNDigis(0)
  , fNHits(0)
  , fTNofEvents(0)
  , fTNofDigis(0) 
  , fTNofHits(0)
  , fFeCols(0)
  , fFeRows(0)
  , fMaxFEperCol(0)
  , fPitchX(0.)
  , fPitchY(0.)
{
  //Reset();
}
// -------------------------------------------------------------------------



// -----   Destructor   ----------------------------------------------------
PixelFindHitsTask::~PixelFindHitsTask() { 
  //Reset();
  
}
// -------------------------------------------------------------------------


// -----   Private method Reset   ------------------------------------------
void PixelFindHitsTask::Reset(TClonesArray* hits) 
{
  fNDigis = fNHits = 0;
  if ( hits ) hits->Delete();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void PixelFindHitsTask::Finish() 
{
  //if ( fDigis ) fDigis->Delete();

  LOG(INFO) << "-------------------- PixelFindHitsTask : Summary ------------------------";
  LOG(INFO) << " Events:        " << fTNofEvents;
  LOG(INFO) << " Digis:         " << fTNofDigis  << "    ( " << (Double_t)fTNofDigis /((Double_t)fTNofEvents) << " per event )";
  LOG(INFO) << " Hits:          " << fTNofHits   << "    ( " << (Double_t)fTNofHits  /((Double_t)fTNofEvents) << " per event )";
  LOG(INFO) << "---------------------------------------------------------------------"; 
}
// -------------------------------------------------------------------------



void PixelFindHitsTask::Init(PixelDigiPar* digipar, FairGeoParSet* geopar)
{
  fFeCols = digipar->GetFECols();
  fFeRows = digipar->GetFERows();
  fMaxFEperCol = digipar->GetMaxFEperCol();
  fPitchX = digipar->GetXPitch();
  fPitchY = digipar->GetYPitch();
  fGeoParSet=geopar;
  LOG(INFO)<<"PixelFindHitsTask::Init"
          <<" fFeCols="<<fFeCols
          <<" fFeRows="<<fFeRows
          <<" fMaxFEperCol="<<fMaxFEperCol
          <<" fPitchX="<<fPitchX
          <<" fPitchY="<<fPitchX
          ;
  LOG(INFO)<<"geopar->printParams()";
  geopar->printParams();
  LOG(INFO)<<"fGeoParSet->printParams()";
  fGeoParSet->printParams();
}


void PixelFindHitsTask::Exec(TClonesArray* digis, TClonesArray* hits) 
{

  Reset(hits);

  LOG(INFO) << "PixelFindHits::Exec() EVENT " << fTNofEvents;

  fTNofEvents++;
  LOG(DEBUG)<<"PixelFindHits::Exec() ok 0 ";
  fNDigis = digis->GetEntriesFast();
  LOG(DEBUG)<<"PixelFindHits::Exec() fNDigis = "<<fNDigis;
  fTNofDigis+= fNDigis;
//*
  for ( Int_t iDigi = 0 ; iDigi < fNDigis ; iDigi++ ) 
  {
    PixelDigi* currentDigi = (PixelDigi*)digis->At(iDigi);

    Int_t detId = currentDigi->GetDetectorID();    
    TString nodeName = Form("/cave/Pixel%d_%d",detId/256,detId%256);
    LOG(DEBUG)<<"PixelFindHits::Exec() ok 1 node name = "<<nodeName.Data();
    fGeoParSet->GetGeometry()->cd(nodeName.Data());
    LOG(DEBUG)<<"PixelFindHits::Exec() ok 2 ";
    TGeoNode* curNode = fGeoParSet->GetGeometry()->GetCurrentNode();
    LOG(DEBUG)<<"PixelFindHits::Exec() ok 3 ";
    TGeoMatrix* matrix = curNode->GetMatrix();

    TGeoVolume* actVolume = fGeoParSet->GetGeometry()->GetCurrentVolume();
    TGeoBBox* actBox = (TGeoBBox*)(actVolume->GetShape());

    Int_t feId = currentDigi->GetFeID();
    Int_t col  = currentDigi->GetCol();
    Int_t row  = currentDigi->GetRow();

    Double_t locPosCalc[3];
    locPosCalc[0] = ( ((feId-1)/fMaxFEperCol)*fFeCols + col + 0.5 )*fPitchX;
    locPosCalc[1] = ( ((feId-1)%fMaxFEperCol)*fFeRows + row + 0.5 )*fPitchY;
    locPosCalc[2] = 0.;

    locPosCalc[0] -= actBox->GetDX();
    locPosCalc[1] -= actBox->GetDY();

    Double_t globPos[3];

    curNode->LocalToMaster(locPosCalc,globPos);

    LOG(DEBUG) << "HIT   ON " << detId << " POSITION:  " << locPosCalc[0] << " / " << locPosCalc[1];
    LOG(DEBUG) << "GLOB HIT " << detId << " POSITION:  " << globPos[0] << " / " << globPos[1] << " / " << globPos[2];

    TVector3 pos   (globPos[0],globPos[1],globPos[2]);
    TVector3 posErr(fPitchX/TMath::Sqrt(12.),fPitchY/TMath::Sqrt(12.),actBox->GetDZ());

    new ((*hits)[fNHits]) PixelHit(detId,currentDigi->GetIndex(),pos,posErr);

    fNHits++;
  }


  fTNofHits += fNHits;
  //return fHits;
}





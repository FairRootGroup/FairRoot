/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairRadLenManager source file                   -----
// -----          original author                  D.Bertini           -----
// -----          adapted april 2010               O.Hartmann          -----
// -------------------------------------------------------------------------


#include <iostream>
#include "FairRadGridManager.h"
#include "FairRootManager.h"
#include "TLorentzVector.h"
#include "TParticle.h"
#include "TVirtualMC.h"
#include "FairMesh.h"

using namespace std;

ClassImp(FairRadGridManager)

FairRadGridManager* FairRadGridManager::fgInstance = NULL;

Double_t FairRadGridManager::fLtmp = 0.0 ;

FairRadGridManager* FairRadGridManager::Instance()
{
  /**singelton instance*/
  return fgInstance;
}

FairRadGridManager::FairRadGridManager()
  : fPointCollection(NULL),
    fTrackID(0),
    fVolumeID(0),
    fPosIn(TLorentzVector(0,0,0,0)),
    fPosOut(TLorentzVector(0,0,0,0)),
    fMomIn(TLorentzVector(0,0,0,0)),
    fMomOut(TLorentzVector(0,0,0,0)),
    fTime(0),
    fLength(0),
    fELoss(0),
    fA(0),
    fZmat(0),
    fDensity(0),
    fRadl(0),
    fAbsl(0),
    fEstimator(0),
    fMeshList(NULL)
{
  /** radiation length default ctor */
  if(NULL == fgInstance) {
    fgInstance = this;
  }
  fLtmp=0;
}

FairRadGridManager::~FairRadGridManager()
{
  /** radiation length default dtor */
  fgInstance = NULL;
}

void FairRadGridManager::Init()
{
//  fMeshList = new TObjArray();
}

void FairRadGridManager::Reset()
{
  //  No free of memory ?
  //  fMesh->Reset();
}

void FairRadGridManager::FillMeshList()
{

  /**Add a point to the collection*/
  TParticle* part = gMC->GetStack()->GetCurrentTrack();
  fTrackID = gMC->GetStack()->GetCurrentTrackNumber();
  gMC->TrackPosition(fPosIn);
  gMC->TrackMomentum(fMomIn);
  fELoss = 0.;
//  Int_t MatId=  gMC->CurrentMaterial(fA, fZmat, fDensity, fRadl, fAbsl);

  /** Sum energy loss for all steps in the mesh*/
  for (Int_t i=0; i<fMeshList->GetEntriesFast(); i++ ) {
    FairMesh* aMesh = (FairMesh*) fMeshList->At(i);
    Double_t fBinVolume = aMesh->GetBinVolume();
    Double_t fDiag = aMesh->GetDiag();

    // Geometry bound test
    if ( IsTrackInside(fPosIn,aMesh) ) {
      fELoss = gMC->Edep();
      //cout << "-I- track (" << fTrackID << ")  is inside " << endl;
      //cout << " E deposited is " << fELoss << endl;
      gMC->TrackPosition(fPosOut);
      gMC->TrackMomentum(fMomOut);

      // Now cumulate fEloss (Gev/cm3)
      // and normalize it to the mesh volume

      // 1 estimator Edep
      fELoss = fELoss/fBinVolume;
      // 2 estimator TrackLengh
      fLength = gMC->TrackStep();
      // fill TID

      aMesh->fillTID(fPosOut.X(),fPosOut.Y(),fELoss);
      // fill total Fluence
      if ( fLength < 5*fDiag ) {

        fLength = fLength/fBinVolume;
        aMesh->fillFluence(fPosOut.X(),fPosOut.Y(),fLength);

        // fill SEU
        if ( part->P() > 0.02 ) {
          aMesh->fillSEU(fPosOut.X(),fPosOut.Y(),fLength);
        }
      }

    }

  }
}

Bool_t FairRadGridManager::IsTrackEntering(TLorentzVector&,
    TLorentzVector&)
{
  // assume for the moment vertical scoring planes
  //    cout << " is entering diagnosis " << endl;
  //    cout << " Z pos " << pos.Z() << endl;
  //    cout << " Zmin "  << fZmin   << endl;
  //    cout << " diff "  << pos.Z()-fZmin   << endl;


  //    if (  (( TMath::Abs(pos.Z() - fZmin) ) < 1.0e-06 )
  //       &&
  //         ( mom.Z() > 0 )
  //      ) return kTRUE;
  //   else
  //     return kFALSE;

  return kFALSE;
}

Bool_t FairRadGridManager::IsTrackInside(TLorentzVector& pos , FairMesh* aMesh)
{
  // check if inside volume
  if ( (pos.X() >= aMesh->GetXmin()) && (pos.X() <= aMesh->GetXmax())
       &&
       (pos.Y() >= aMesh->GetYmin()) && (pos.Y() <= aMesh->GetYmax())
       &&
       (pos.Z() >= aMesh->GetZmin()) && (pos.Z() <= aMesh->GetZmax())
     ) {
    /*       cout << " inside Xpos: " << pos.X() << " Xmin: " << aMesh->GetXmin()
          << " Xmax: " << aMesh->GetXmax()  << endl;
           cout << " inside Ypos: " << pos.Y() << " Ymin: " << aMesh->GetYmin()
          << " Ymax: " << aMesh->GetYmax() << endl;
           cout << " inside Zpos: " << pos.Z() << " Zmin: "
          << aMesh->GetZmin() << " Zmax: " << aMesh->GetZmax() << endl;
    */
    return kTRUE;
  } else {
    return kFALSE;
  }
}

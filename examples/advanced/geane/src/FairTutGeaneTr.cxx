/********************************************************************************
 *    Copyright (C) 2019 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairTutGeaneTr.cxx
 *
 * @since 2019-09-10
 * @author R. Karabowicz
 */

#include "FairTutGeaneTr.h"

#include "TClonesArray.h"
#include "TGeant3TGeo.h"
#include "TGeant3.h"
#include "TVector3.h"
#include "TTree.h"
#include "TDatabasePDG.h"

#include "FairRootManager.h"
#include "FairLogger.h"
#include "FairTrackParP.h"
#include "FairTutGeanePoint.h"

// -----   Default constructor   -------------------------------------------
FairTutGeaneTr::FairTutGeaneTr()
    : FairTask("FairTutGeaneTr")
    , gMC3(0)
    , fPointArray(0)
    , fPoint1(0)
    , fPoint2(0)
    , fTrackParIni(0)
    , fTrackParFinal(0)
    , fTrackParGeane(0)
    , fTrackParWrong(0)
    , fEvent(0)
    , fPro(0)
{ }
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairTutGeaneTr::~FairTutGeaneTr()
{
  Reset();
  if ( fTrackParIni ) {
    fTrackParIni->Delete();
    delete fTrackParIni;
  }
  if ( fTrackParGeane ) {
    fTrackParGeane->Delete();
    delete fTrackParGeane;
  }
  if ( fTrackParWrong ) {
    fTrackParWrong->Delete();
    delete fTrackParWrong;
  }
  if ( fTrackParFinal ) {
    fTrackParFinal->Delete();
    delete fTrackParFinal;
  }
}
// -------------------------------------------------------------------------

// -----   Public method Init   --------------------------------------------
InitStatus FairTutGeaneTr::Init() {

     // Get RootManager
    FairRootManager* ioman = FairRootManager::Instance();
    if ( ! ioman ) {
        LOG(error) << "FairTutGeaneTr::Init: RootManager not instantised!";
        return kFATAL;
    }

    fTrackParIni = new TClonesArray("FairTrackParP");
    ioman->Register("GeaneTrackIni","Geane", fTrackParIni, kTRUE);

    fTrackParFinal = new TClonesArray("FairTrackParP");
    ioman->Register("GeaneTrackFinal","Geane", fTrackParFinal, kTRUE);

    fTrackParGeane = new TClonesArray("FairTrackParP");
    ioman->Register("GeaneTrackPar","Geane", fTrackParGeane, kTRUE);

    fTrackParWrong = new TClonesArray("FairTrackParP");
    ioman->Register("GeaneTrackParWrongQ","Geane", fTrackParWrong, kTRUE);

    // Get input array

    fPointArray = static_cast<TClonesArray*>(ioman->GetObject("FairTutGeanePoint"));

    // Create and register output array

    fPro = new FairGeanePro();

    TVector3 planePoint(0.,0.,20.);
    TVector3 planeVectJ(1.,0.,0.);
    TVector3 planeVectK(0.,1.,0.);
    
    fPro->PropagateToPlane(planePoint,planeVectJ,planeVectK);

    return kSUCCESS;

}
// -------------------------------------------------------------------------

// -----   Public method Exec   --------------------------------------------
void FairTutGeaneTr::Exec(Option_t*) {
    Reset();

    LOG(debug) << "FairTutGeaneTr::Exec";

    Int_t NoOfEntries=fPointArray->GetEntriesFast();
    LOG(debug) << "fPointArray has " << NoOfEntries << " entries";
    for (Int_t i=0; i<NoOfEntries; i++)	{
        fPoint1 = static_cast<FairTutGeanePoint*>(fPointArray->At(i));
        if ( fPoint1->GetZ() > 6. ) continue;
        LOG(debug) << "first loop for " << i << "from "<< NoOfEntries << " entries ";
        Int_t trId=fPoint1->GetTrackID();
        fPoint2=0;
        for (Int_t k=0; k<NoOfEntries; k++)	{
            fPoint2 = static_cast<FairTutGeanePoint*>(fPointArray->At(k));
            if ( fPoint2->GetZ() < 15. ) continue;
            LOG(debug) << "second loop for " << k;
            if(fPoint2->GetTrackID()==trId) break;
        }

        if(fPoint2==0) break;

        TVector3 StartPos   (fPoint1->GetX(),fPoint1->GetY(),fPoint1->GetZ());
        //    TVector3 StartPos(0.,0.,0.);
        TVector3 StartPosErr(0,0,0);
        TVector3 StartMom   (fPoint1->GetPx(),fPoint1->GetPy(),fPoint1->GetPz());
        //    TVector3 StartMom(1.,0.1,0.1);
        TVector3 StartMomErr(0,0,0);

        TVector3 EndPos   (fPoint2->GetX(),fPoint2->GetY(),fPoint2->GetZ());
        TVector3 EndPosErr(0,0,0);
        TVector3 EndMom   (fPoint2->GetPx(),fPoint2->GetPy(),fPoint2->GetPz());
        TVector3 EndMomErr(0,0,0);

        Int_t PDGCode= -13;

        TDatabasePDG *fdbPDG= TDatabasePDG::Instance();
        TParticlePDG *fParticle= fdbPDG->GetParticle(PDGCode);
        Double_t  fCharge= fParticle->Charge();

        TClonesArray& clref1 = *fTrackParIni;
        Int_t size1 = clref1.GetEntriesFast();
        FairTrackParP *fStart= new (clref1[size1]) FairTrackParP(StartPos, StartMom, StartPosErr, StartMomErr, fCharge, TVector3(0.,0.,5.), TVector3(1.,0.,0.), TVector3(0.,1.,0.));
        //  fStart->Print();

        TClonesArray& clref = *fTrackParGeane;
        Int_t size = clref.GetEntriesFast();
        FairTrackParP *fRes=	new(clref[size]) FairTrackParP();
        // fRes->Print();

        TClonesArray& clrew = *fTrackParWrong;
        Int_t sizeW = clrew.GetEntriesFast();
        FairTrackParP *fWro=	new(clrew[sizeW]) FairTrackParP();
        // fRes->Print();

        TClonesArray& clref2 = *fTrackParFinal;
        Int_t size2 = clref2.GetEntriesFast();
        FairTrackParP *fFinal= new(clref2[size2]) FairTrackParP(EndPos, EndMom, EndPosErr, EndMomErr, fCharge, TVector3(0.,0.,20.), TVector3(1.,0.,0.), TVector3(0.,1.,0.));

        LOG(debug) << "propagateFROM " << fStart->GetX() << " / " << fStart->GetY() << " / " << fStart->GetZ();
        Bool_t rc =  fPro->Propagate(fStart, fRes,PDGCode);
        LOG(debug) << "propagated TO " << fRes->GetX() << " / " << fRes->GetY() << " / " << fRes->GetZ();

        rc =  fPro->Propagate(fStart, fWro,-PDGCode);

    }
}

// -----   Private method Reset   ------------------------------------------
void FairTutGeaneTr::Reset() {
  if ( fTrackParIni   ) fTrackParIni  ->Clear();
  if ( fTrackParGeane ) fTrackParGeane->Clear();
  if ( fTrackParWrong ) fTrackParWrong->Clear();
  if ( fTrackParFinal ) fTrackParFinal->Clear();
}
// -------------------------------------------------------------------------

// -----   Public method Finish   ------------------------------------------
void FairTutGeaneTr::Finish() {
  if ( fTrackParIni   ) fTrackParIni  ->Delete();
  if ( fTrackParGeane ) fTrackParGeane->Delete();
  if ( fTrackParWrong ) fTrackParWrong->Delete();
  if ( fTrackParFinal ) fTrackParFinal->Delete();
}

ClassImp(FairTutGeaneTr)

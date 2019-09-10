/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairGeaneTr.cxx
 *
 * @since 2019-09-10
 * @author R. Karabowicz
 */

#include "FairGeaneTr.h"

#include "TClonesArray.h"
#include "TGeant3TGeo.h"
#include "TGeant3.h"
#include "TVector3.h"
#include "TTree.h"
#include "TDatabasePDG.h"

#include "FairRootManager.h"
#include "FairLogger.h"
#include "FairTrackParP.h"
#include "PixelPoint.h"

// -----   Default constructor   -------------------------------------------
FairGeaneTr::FairGeaneTr()
    : FairTask("FairGeanePropagator")
    , fPro(0)
{ }
// -------------------------------------------------------------------------

// -----   Destructor   ----------------------------------------------------
FairGeaneTr::~FairGeaneTr() { }
// -------------------------------------------------------------------------

// -----   Public method Init   --------------------------------------------
InitStatus FairGeaneTr::Init() {

     // Get RootManager
    FairRootManager* ioman = FairRootManager::Instance();
    if ( ! ioman ) {
        LOG(error) << "FairGeaneTr::Init: RootManager not instantised!";
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

    fPointArray = static_cast<TClonesArray*>(ioman->GetObject("PixelPoint"));

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
void FairGeaneTr::Exec(Option_t*) {
    LOG(debug) << "FairGeaneTr::Exec";

    Int_t NoOfEntries=fPointArray->GetEntriesFast();
    LOG(debug) << "fPointArray has " << NoOfEntries << " entries";
    for (Int_t i=0; i<NoOfEntries; i++)	{
        fPoint1 = static_cast<PixelPoint*>(fPointArray->At(i));
        if ( fPoint1->GetZ() > 6. ) continue;
        LOG(debug) << "first loop for " << i << "from "<< NoOfEntries << " entries ";
        Int_t trId=fPoint1->GetTrackID();
        fPoint2=0;
        for (Int_t k=0; k<NoOfEntries; k++)	{
            fPoint2 = static_cast<PixelPoint*>(fPointArray->At(k));
            if ( fPoint2->GetZ() < 15. ) continue;
            LOG(debug) << "second loop for " << k;
            if(fPoint2->GetTrackID()==trId) break;
        }

        if(fPoint2==0) break;

        TVector3 StartPos    = TVector3 (fPoint1->GetX(),fPoint1->GetY(),fPoint1->GetZ());
        //    TVector3 StartPos    = TVector3 (0.,0.,0.);
        TVector3 StartPosErr = TVector3(0,0,0);
        TVector3 StartMom    = TVector3 (fPoint1->GetPx(),fPoint1->GetPy(),fPoint1->GetPz());
        //    TVector3 StartMom    = TVector3 (1.,0.1,0.1);
        TVector3 StartMomErr = TVector3(0,0,0);

        TVector3 EndPos =TVector3 (fPoint2->GetX(),fPoint2->GetY(),fPoint2->GetZ());
        TVector3 EndPosErr=TVector3(0,0,0);
        TVector3 EndMom= TVector3 (fPoint2->GetPx(),fPoint2->GetPy(),fPoint2->GetPz());
        TVector3 EndMomErr=TVector3(0,0,0);

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

ClassImp(FairGeaneTr)

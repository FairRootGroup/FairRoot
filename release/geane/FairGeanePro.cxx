// Class for the interface to propagate track parameters with GEANE
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//

#include "FairGeanePro.h"
#include "FairTrackParP.h"
#include "FairTrackParH.h"
#include "FairRunAna.h"
#include "FairField.h"
#include "FairGeaneUtil.h"

#include "TGeant3TGeo.h"
#include "TVector3.h"
#include "TArrayD.h"
#include "TDatabasePDG.h"
#include "TGeoTorus.h"
#include "TMatrixFSym.h"
#include "TVirtualMC.h"
#include "TGeant3.h"
#include "FairGeaneApplication.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;

// -----   Default constructor   -------------------------------------------
FairGeanePro::FairGeanePro()
  : TNamed("Geane", "Propagate Tracks"),
    gMC3((TGeant3*) gMC),
    fPropOption(""),
    nepred(1),
    fdbPDG(TDatabasePDG::Instance()),
    afErtrio(gMC3->fErtrio),
    GeantCode(0),
    ProMode(0),
    VName(""),
    VCopyNo(0),
    VEnter(kTRUE),
    fpoint(TVector3(0., 0., 0.)),
    fwire1(TVector3(0., 0., 0.)),
    fwire2(TVector3(0., 0., 0.)),
    fPCA(0),
    fRad(0.),
    fDi(0.),
    fvpf(TVector3(0., 0., 0.)),
    fvwi(TVector3(0., 0., 0.)),
    ftrklength(0.),
    flag(0),
    fApp(FairGeaneApplication::Instance())
{
  if(gMC3==NULL) {
    std::cerr<<"FairGeanePro::TGeant3 has not been initialized! ABORTING!"<<std::endl;
    throw;
  }
  //  nepred=1;
  xlf[0] = 0.;
  //  fdbPDG= TDatabasePDG::Instance();
  //  fErrorMat= new TArrayD(15);
  //  afErtrio=gMC3->fErtrio;
  // Pos=TVector3(0,  0 , 0);
  // PosErr = TVector3(0,0,0);
  // Mom=TVector3(0,0,0);
  // fTrkPar= new FairTrackPar();
  //  ProMode=0;
  //   FairRunAna *fRun= FairRunAna::Instance();
  //   fField= fRun->GetField();

  // PCA stuff
  //  fPCA = 0;
  /*
  fpoint = TVector3(0., 0., 0.);
  fwire1 = TVector3(0., 0., 0.);
  fwire2 = TVector3(0., 0., 0.);
  */

  for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++) { trpmat[i][j] = 0.; }

  //  fApp = FairGeaneApplication::Instance();

  //   fPropOption = "";
  for(int i = 0; i < 15; i++) {
    ein[i] = 0.;
    if(i < 3) {
      x2[i] = 0;
      p2[i] = 0;
      x1[i] = 0;
      p1[i] = 0;
    }
  }

  pli[0] = 1.;
  pli[1] = 0.;
  pli[2] = 0.;
  pli[3] = 0.;
  pli[4] = 1.;
  pli[5] = 0.;

  plo[0] = 0.;
  plo[1] = 0.;
  plo[2] = 0.;
  plo[3] = 1.;
  plo[4] = 0.;
  plo[5] = 0.;
  plo[6] = 0.;
  plo[7] = 1.;
  plo[8] = 0.;
  plo[9] = 0.;
  plo[10] = 0.;
  plo[11] = 1.;

  //  GeantCode = 0;
  /*
  VName = "";
  VCopyNo = 0;
  VEnter = kTRUE;
  */

}

// -----   Destructor   ----------------------------------------------------
FairGeanePro::~FairGeanePro() { }



Bool_t FairGeanePro::Propagate(FairTrackParH* TParam, FairTrackParH* TEnd, Int_t PDG)
{
  // Propagate a helix track and return a helix (SC system)

  //Bool_t NeedSDSC=kFALSE;
  Int_t ch=1;   //        CHARGE OF PARTICLE

  Double_t fCov[15], fCovOut[15];
  TParam->GetCovQ(fCov);

  Init(TParam);
  Double_t Q = TParam->GetQ();
  if (fabs(Q)>1.E-8) { ch= int (Q/TMath::Abs(Q)); }
  if (ProMode==1) { //Propagate to Volume
    //***** We have the right representation go further
    for(Int_t i=0; i<15; i++) {
      ein[i]=fCov[i];

    }
    if(fPropOption.Contains("V")) {
      //cout << "Propagate Helix to Volume" << endl;
      Int_t option;
      if(VEnter) { option =1; }
      else { option =2; }
      gMC3->Eufilv(1, ein, (Char_t*)VName.Data(), &VCopyNo, &option);
    } else if(fPropOption.Contains("L")) {
      if(fPCA == 0) {
        gMC3->Eufill(nepred, ein,xlf);
      } else if(fPCA != 0) {

        // max length estimate:
        // we calculate the geometrical distance of the start point
        // from the point/wire extremity and multiply it * 2
        TVector3 start = TVector3(TParam->GetX(), TParam->GetY(), TParam->GetZ());
        Double_t maxdistance = 0;
        if(fPCA == 1) { maxdistance = (fpoint - start).Mag(); }
        else if(fPCA == 2) {
          Double_t distance1, distance2;
          distance1 = (fwire1 - start).Mag();
          distance2 = (fwire2 - start).Mag();
          if(distance1 < distance2) { maxdistance = distance2; }
          else { maxdistance = distance1; }
        }
        maxdistance *= 2.;

        // output
        Int_t findpca = FindPCA(fPCA, PDG, fpoint, fwire1, fwire2, maxdistance, fRad, fvpf, fvwi, fDi, ftrklength);
        if(findpca != 0) { return kFALSE; }

        // reset parameters
        Init(TParam);
        gMC3->Eufill(nepred, ein, &ftrklength);
      }
    }
  } else if(ProMode ==3) {
    cout << "Propagate Helix parameter to Plane is not implimented yet" << endl;
    return kFALSE;
  }
  //Propagate
  if(Propagate(PDG)==kFALSE) { return kFALSE; }

  for(Int_t i=0; i<15; i++) {
    fCovOut[i]=afErtrio->errout[i];
    if(i == 0) { fCovOut[i] = fCovOut[i] * ch * ch; }
    if(i > 0 && i < 5) { fCovOut[i] = fCovOut[i] * ch; }
  }

  // do not remove (useful for debug)
  if(fabs(p2[0]) < 1e-9 && fabs(p2[1]) < 1e-9 && fabs(p2[2]) < 1e-9) { return kFALSE; }
  TEnd->SetTrackPar(x2[0], x2[1], x2[2],p2[0],p2[1],p2[2], ch ,fCovOut );
  return kTRUE;

}
Bool_t FairGeanePro::Propagate(FairTrackParP* TStart, FairTrackParH* TEnd, Int_t PDG)
{
  // Propagate a parabola track (SD system) and return a helix (SC system) (not used nor implemented)
  cout << "FairGeanePro::Propagate(FairTrackParP *TParam, FairTrackParH &TEnd, Int_t PDG) : (not used nor implemented)" << endl;
  return kFALSE;
}

Bool_t FairGeanePro::Propagate(FairTrackParP* TStart, FairTrackParP* TEnd, Int_t PDG)
{
  // Propagate a parabola track (SD system) and return a parabola (SD system) (not used nor implemented)
  Int_t ch=1;   //        CHARGE OF PARTICLE
  Double_t fCov[15], fCovOut[15];
  TStart->GetCovQ(fCov);

  Init(TStart);
  Double_t Q = TStart->GetQ() ;
  if (Q!=0) { ch= int (Q/TMath::Abs(Q)); }

  if (ProMode==1) { //Propagate to Volume
    cout << "Propagate Parabola parameter to Volume is not implimented yet" << endl;
    return kFALSE;
  } else if(ProMode ==3) {
    /** We have the right representation go further*/
    for(Int_t i=0; i<15; i++) {
      ein[i]=fCov[i];

    }

    if(fPropOption.Contains("P")) { gMC3->Eufilp(nepred, ein, pli, plo); }
    else if(fPropOption.Contains("L")) {
      if(fPCA == 0) { cout << "Propagate Parabola to Parabola in Length not yet implemented" << endl; }
      else if(fPCA != 0) {

        // max length estimate:
        // we calculate the geometrical distance of the start point
        // from the point/wire extremity and multiply it * 2
        TVector3 start = TVector3(TStart->GetX(), TStart->GetY(), TStart->GetZ());
        Double_t maxdistance = 0;
        if(fPCA == 1) { maxdistance = (fpoint - start).Mag(); }
        else if(fPCA == 2) {
          Double_t distance1, distance2;
          distance1 = (fwire1 - start).Mag();
          distance2 = (fwire2 - start).Mag();
          if(distance1 < distance2) { maxdistance = distance2; }
          else { maxdistance = distance1; }
        }
        maxdistance *= 2.;

        // output
        Int_t findpca = FindPCA(fPCA, PDG, fpoint, fwire1, fwire2, maxdistance, fRad, fvpf, fvwi, fDi, ftrklength);
        //std::cout<<" FairGeanePro::ftrklength="<<ftrklength<< std::endl;
        if(findpca != 0) { return kFALSE; }

        // reset parameters
        Init(TStart);

        // find plane
        // unitary vector along distance
        // fvpf on track, fvwi on wire
        TVector3 fromwiretoextr = fvpf - fvwi;
        fromwiretoextr.SetMag(1.);
        if(fabs(fromwiretoextr.Mag()-1)>1E-4) {
          std::cerr<<"fromwire.Mag()!=1"<<std::endl;
          return kFALSE;
        }

        //for wires:
        // unitary vector along the wire
        TVector3 wiredirection = fwire2 - fwire1;
        if(fPCA==1) { // point
          TVector3 mom(TStart->GetPx(),TStart->GetPy(),TStart->GetPz());
          wiredirection=mom.Cross(fromwiretoextr);
        }
        wiredirection.SetMag(1.);
        // check orthogonality
        if(fabs(fromwiretoextr * wiredirection) > 1e-3) {
          return kFALSE; // throw away the event
          // wiredirection = (fromwiretoextr.Cross(wiredirection)).Cross(fromwiretoextr);
          // wiredirection.SetMag(1.);
        }

        TVector3 jver = TStart->GetJVer();;
        TVector3 kver = TStart->GetKVer();
        Bool_t backtracking = kFALSE;
        if(fPropOption.Contains("B")) { backtracking = kTRUE; }
        PropagateFromPlane(jver, kver);
        PropagateToPlane(fvwi, fromwiretoextr, wiredirection);
        if(backtracking == kTRUE) { fPropOption = "BPE"; }

        gMC3->Eufilp(nepred, ein, pli, plo);
      }
    }
  }
  //Propagate
  if(Propagate(PDG)==kFALSE) { return kFALSE; }

  for(Int_t i=0; i<15; i++) {
    fCovOut[i]=afErtrio->errout[i];
    if(i == 0) { fCovOut[i] = fCovOut[i] * ch * ch; }
    if(i > 0 && i < 5) { fCovOut[i] = fCovOut[i] * ch; }
  }

  // plane
  TVector3 origin(plo[6], plo[7], plo[8]);
  TVector3 dj(plo[0], plo[1], plo[2]);
  TVector3 dk(plo[3], plo[4], plo[5]);
  TVector3 di(plo[9], plo[10], plo[11]); // = dj.Cross(dk);


  if(fabs(p2[0]) < 1e-9 && fabs(p2[1]) < 1e-9 && fabs(p2[2]) < 1e-9) { return kFALSE; }

  TEnd->SetTrackPar(x2[0], x2[1], x2[2],p2[0],p2[1],p2[2], ch ,fCovOut, origin, di, dj, dk);

  return kTRUE;

}


Bool_t FairGeanePro::Propagate(FairTrackParH* TStart, FairTrackParP* TEnd, Int_t PDG)
{
  // Propagate a helix track (SC system) and return a parabola (SD system) (not used nor implemented)
  cout << "FairGeanePro::Propagate(FairTrackParH *TParam, FairTrackParP &TEnd, Int_t PDG) not implemented" << endl;
  return kFALSE;
}

Bool_t FairGeanePro::Propagate(Float_t* X1, Float_t* P1, Float_t* X2, Float_t* P2,Int_t PDG)
{
//  fApp->GeanePreTrack(X1, P1, PDG);
  GeantCode=fdbPDG->ConvertPdgToGeant3(PDG);
  xlf[0]=1000
         ;
  gMC3->Eufill(1, ein,xlf);
  gMC3->Ertrak(X1,P1,X2,P2,GeantCode, "L");
  if(X2[0]<-1.E29) { return kFALSE; }
  if(gMC3->IsTrackOut()) { return kFALSE; }
  return kTRUE;
}

Bool_t FairGeanePro::Propagate(Int_t PDG)
{
  // main propagate call to fortran ERTRAK

  GeantCode=fdbPDG->ConvertPdgToGeant3(PDG);
  //cout <<  " FairGeanePro::Propagate ---------------------------"<< "  " << x1[0]<< " "<< x1[1]<< "  "<<  x1[2] << endl;
  //fApp->GeanePreTrack(x1, p1, PDG);
  gMC3->Ertrak(x1,p1,x2,p2,GeantCode, fPropOption.Data());
  if(x2[0]<-1.E29) { return kFALSE; }
  if(gMC3->IsTrackOut()) { return kFALSE; }

  ftrklength=gMC3->TrackLength();

  Double_t trasp[25];
  for(int i = 0; i < 25; i++) {
    //       trasp[i] = afErtrio->ertrsp[i]; // single precision tr. mat.
    trasp[i] = afErtrio->erdtrp[i];          // double precision tr. mat.
  }
  FairGeaneUtil fUtil;
  fUtil.FromVecToMat(trpmat, trasp);
  return kTRUE;
}

void FairGeanePro::Init(FairTrackPar* TParam)
{
  // starting and ending point initialization
  x1[0]=TParam->GetX();
  x1[1]=TParam->GetY();
  x1[2]=TParam->GetZ();
  p1[0]=TParam->GetPx();
  p1[1]=TParam->GetPy();
  p1[2]=TParam->GetPz();

  x2[0]=0;
  x2[1]=0;
  x2[2]=0;
  p2[0]=0;
  p2[1]=0;
  p2[2]=0;
}

Bool_t FairGeanePro::PropagateFromPlane(TVector3& v1, TVector3& v2)
{
  // define initial plane (option "P")
  TVector3 v1u=v1.Unit();
  TVector3 v2u=v2.Unit();
  pli[0]=v1u.X();
  pli[1]=v1u.Y();
  pli[2]=v1u.Z();
  pli[3]=v2u.X();
  pli[4]=v2u.Y();
  pli[5]=v2u.Z();
  return kTRUE;
}

Bool_t FairGeanePro::PropagateToPlane(TVector3& v0, TVector3& v1, TVector3& v2)
{
  // define final plane (option "P")
  // uncomment to set the initial error to zero
  //  for(Int_t i=0;i<15;i++) ein[i]=0.00;
  TVector3 v1u=v1.Unit();
  TVector3 v2u=v2.Unit();


  plo[0]=v1u.X();
  plo[1]=v1u.Y();
  plo[2]=v1u.Z();
  plo[3]=v2u.X();
  plo[4]=v2u.Y();
  plo[5]=v2u.Z();

  plo[6]=v0.X();
  plo[7]=v0.Y();
  plo[8]=v0.Z();

  TVector3 v3=v1u.Cross(v2u);

  plo[9]=v3(0);
  plo[10]=v3(1);
  plo[11]=v3(2);

  fPropOption="PE";
  ProMode=3;  //need errors in representation 3 (SD)(see Geane doc)
  //  gMC3->Eufilp(nepred, ein, pli, plo);
  return kTRUE;
}
Bool_t FairGeanePro::PropagateToVolume(TString VolName, Int_t CopyNo , Int_t option)
{
  // define final volume (option "V")
  for(Int_t i=0; i<15; i++) { ein[i]=0.00; }
  VName= VolName;
  VCopyNo= CopyNo;
  if(option==1) { VEnter=kTRUE; }
  else { VEnter=kFALSE; }
  fPropOption="VE";
  ProMode=1;  //need errors in representation 1 (SC) (see Geane doc)
  return kTRUE;
}

Bool_t FairGeanePro::PropagateToLength(Float_t length)
{
  // define final length (option "L")
  xlf[0]=length;
  fPropOption="LE";
  ProMode=1; //need errors in representation 1 (SC)(see Geane doc)
  return kTRUE;
}
Bool_t FairGeanePro::PropagateOnlyParameters()
{
  int index = fPropOption.Index("E");
  if(index == -1) { fPropOption.Append("O"); }
  else { fPropOption.Replace(index, 1, "O"); }
  return kTRUE;
}

Bool_t FairGeanePro::SetWire(TVector3 extremity1, TVector3 extremity2)
{
  // define wires for PCA extrapolation in STT
  fwire1 = extremity1;
  fwire2 = extremity2;
  return kTRUE;
}

Bool_t FairGeanePro::SetPoint(TVector3 pnt)
{
  // define point for PCA extrapolation in TPC
  fpoint = pnt;
  return kTRUE;
}

Bool_t FairGeanePro::PropagateToPCA(Int_t pca)
{
  // through track length
  fPropOption="LE";
  ProMode=1; //need errors in representation 1 (SC)(see Geane doc)
  fPCA = pca;
  // initialization
  fRad = 0.;
  fDi = 0.;
  fvpf = TVector3(0.,0.,0.);
  fvwi = TVector3(0.,0.,0.);
  ftrklength = 0;
  return kTRUE;
}

Bool_t FairGeanePro::PropagateToPCA(Int_t pca, Int_t dir)
{
  // through track length
  if(dir > 0) { fPropOption="LE"; }
  else if(dir < 0) { fPropOption="BLE"; }
  else { cout << "FairGeanePro::PropagateToPCA(int, int) ERROR: no direction set" << endl; }
  ProMode=1; //need errors in representation 1 (SC)(see Geane doc)
  fPCA = pca;
  // initialization
  fRad = 0.;
  fDi = 0.;
  fvpf = TVector3(0.,0.,0.);
  fvwi = TVector3(0.,0.,0.);
  ftrklength = 0;
  return kTRUE;
}

Bool_t FairGeanePro::ActualFindPCA(Int_t pca, FairTrackParP* par, Int_t dir)
{
  Init(par);
  // through track length
  if(dir > 0) { fPropOption="LE"; }
  else if(dir < 0) { fPropOption="BLE"; }
  else { cout << "FairGeanePro::ActualFindPCA ERROR: no direction set" << endl; }
  ProMode=1; //need errors in representation 1 (SC)(see Geane doc)
  fPCA = pca;
  // initialization
  fRad = 0.;
  fDi = 0.;
  fvpf = TVector3(0.,0.,0.);
  fvwi = TVector3(0.,0.,0.);
  ftrklength = 0;
  for(Int_t i=0; i<15; i++) { ein[i]=0.00; }
  return kTRUE;
}

Bool_t FairGeanePro::BackTrackToVertex()
{
  // through track length
  fPropOption="BLE";
  ProMode=1; //need errors in representation 1 (SC)(see Geane doc)
  fPCA = 1; // to point
  // initialization (forse non necessario) CHECK!!!!
  fRad = 0.;
  fDi = 0.;
  fvpf = TVector3(0.,0.,0.);
  fvwi = TVector3(0.,0.,0.);
  ftrklength = 0;
  return kTRUE;
}

Bool_t FairGeanePro::PropagateToVirtualPlaneAtPCA(Int_t pca)
{
  // through track length
  fPropOption="LE";
  ProMode=3; //need errors in representation 3 (SD)(see Geane doc)
  fPCA = pca;
  // initialization
  fRad = 0.;
  fDi = 0.;
  fvpf = TVector3(0.,0.,0.);
  fvwi = TVector3(0.,0.,0.);
  ftrklength = 0;
  return kTRUE;
}

Bool_t FairGeanePro::BackTrackToVirtualPlaneAtPCA(Int_t pca)
{
  // through track length
  fPropOption="BLE";
  ProMode=3; //need errors in representation 3 (SD)(see Geane doc)
  fPCA = pca;
  // initialization
  fRad = 0.;
  fDi = 0.;
  fvpf = TVector3(0.,0.,0.);
  fvwi = TVector3(0.,0.,0.);
  ftrklength = 0;
  return kTRUE;
}

//=====================

int FairGeanePro::FindPCA(Int_t pca, Int_t PDGCode, TVector3 point, TVector3 wire1, TVector3 wire2, Double_t maxdistance, Double_t& Rad, TVector3& vpf, TVector3& vwi, Double_t& Di, Float_t& trklength)
{
  // find the point of closest approach of the track to a point(measured position) or to a line(wire)

  // INPUT ----------------------------------------
  // .. pca = ic = 1 closest approach to point
  //        = 2 closest approach to wire
  //        = 0 no closest approach
  // .. PDGCode = pdg code of the particle
  // .. point point with respect to which calculate the closest approach
  // .. wire, wire2 line with respect to which calculate the closest approach
  // .. maxdistance = geometrical distance[start - point/wire extr] * 2
  // OUTPUT ----------------------------------------
  // .. Rad radius if the found circle
  // .. vpf: point of closest approach on track
  // .. vwi: point of closest approach on wire
  // .. Di : distance between track and wire in the PCA
  // .. trklength : track length to add to the GEANE one

  Float_t pf[3] = {point.X(), point.Y(), point.Z()};
  Float_t w1[3] = {wire1.X(), wire1.Y(), wire1.Z()};
  Float_t w2[3] = {wire2.X(), wire2.Y(), wire2.Z()};

  GeantCode=fdbPDG->ConvertPdgToGeant3(PDGCode);

  // flags Rotondi's function
  int flg=0;

  // cl track length to the three last points of closest approach
  // dst assigned distance between initial point in ERTRAK and PFINAL along straight line (currently noy used)
  Float_t cl[3],dst;

  // GEANE filled points
  Float_t po1[3],po2[3],po3[3];

  // cl track length to the three last points of closest approach
  Float_t clen[3];

  // track length to add to GEANE computed one
  Double_t Le=0.0;
  Double_t dist1,dist2;

  // initialization of some variables
  dst = 999.;
  cl[0] = 0;
  cl[1] = 0;
  cl[2] = 0;

  // GEANE filled points
  po1[0]=0;
  po1[1]=0;
  po1[2]=0;
  po2[0]=0;
  po2[1]=0;
  po2[2]=0;
  po3[0]=0;
  po3[1]=0;
  po3[2]=0;

  gMC3->SetClose(pca,pf,dst,w1,w2,po1,po2,po3,cl);

  // maximum distance calculated 2 * geometric distance
  // start point - end point (the point to which we want
  // to find the PCA)
  Float_t stdlength[1] = {maxdistance};

  gMC3->Eufill(1, ein, stdlength);

  //check needed for low momentum tracks
  gMC3->Ertrak(x1,p1,x2,p2,GeantCode, fPropOption.Data());
  if(x2[0]<-1.E29) { return 1; }
  if(gMC3->IsTrackOut()) { return 1; }
  gMC3->GetClose(po1,po2,po3,clen);

  // check on cases when only two steps are performed!
  // in these cases po1[i] = 0 ==> let' s copy po2 into
  // po1 in order to use only the two actually extrapolated
  // points po2 and po3 to complete the PCA calculation
  if(clen[0] == 0 && clen[1] == 0) {
    po1[0] = po2[0];
    po1[1] = po2[1];
    po1[2] = po2[2];
  }

  if(pca == 1) {
    if((po1[0] == po2[0] && po1[1] == po2[1] && po1[2] == po2[2])
        || (po2[0] == po3[0] && po2[1] == po3[1] && po2[2] == po3[2])) {
      Int_t quitFlag=0;
      Track2ToPoint(TVector3(po1),TVector3(po3),TVector3(pf),vpf,Di,Le,quitFlag);
      if(quitFlag!=0) {std::cerr<<"ABORT"<<std::endl; return 1;} //abort
    } else {
      Track3ToPoint(TVector3(po1),TVector3(po2),TVector3(po3),TVector3(pf),vpf,flg,Di,Le,Rad);
      if(flg==1) {
        Int_t quitFlag=0;
        Track2ToPoint(TVector3(po1),TVector3(po3),TVector3(pf),vpf,Di,Le,quitFlag);
        if(quitFlag!=0) {std::cerr<<"ABORT"<<std::endl; return 1;} //abort
      } else if(flg==2) {std::cerr<<"ABORT"<<std::endl; return 1;} //abort
    }
    // if the propagation to closest approach to a POINT  is performed
    // vwi is the point itself (with respect to which the PCA is calculated)
    vwi = point;
  } else if(pca == 2) {
    if((po1[0] == po2[0] && po1[1] == po2[1] && po1[2] == po2[2])
        || (po2[0] == po3[0] && po2[1] == po3[1] && po2[2] == po3[2])) {
      Track2ToLine(TVector3(po1),TVector3(po3),TVector3(w1),
                   TVector3(w2),vpf,vwi,flg,Di,Le);
      if(flg==1) {
        dist1 = (vwi-TVector3(w1)).Mag();
        dist2 = (vwi-TVector3(w2)).Mag();
        Int_t quitFlag=0;
        dist1<dist2?Track2ToPoint(TVector3(po1),TVector3(po3),TVector3(w1),vpf,Di,Le,quitFlag):
        Track2ToPoint(TVector3(po1),TVector3(po3),TVector3(w2),vpf,Di,Le,quitFlag);
        if(quitFlag!=0) {std::cerr<<"ABORT"<<std::endl; return 1;} //abort
      } else if(flg==2) {
        std::cerr<<"ABORT"<<std::endl;
        return 1;
      }
    } else {
      Track3ToLine(TVector3(po1),TVector3(po2),TVector3(po3),
                   TVector3(w1),TVector3(w2),vpf,vwi,flg,Di,Le,Rad);
      if(flg==1) {
        Track2ToLine(TVector3(po1),TVector3(po3),TVector3(w1),
                     TVector3(w2),vpf,vwi,flg,Di,Le);
        if(flg==1) {
          dist1 = (vwi-TVector3(w1)).Mag();
          dist2 = (vwi-TVector3(w2)).Mag();
          Int_t quitFlag=0;
          dist1<dist2?Track2ToPoint(TVector3(po1),TVector3(po3),TVector3(w1),vpf,Di,Le,quitFlag):
          Track2ToPoint(TVector3(po1),TVector3(po3),TVector3(w2),vpf,Di,Le,quitFlag);
          if(quitFlag!=0) {std::cerr<<"ABORT"<<std::endl; return 1;} //abort
        } else if(flg==2) {
          std::cerr<<"ABORT"<<std::endl;
          return 1;
        }
      } else if(flg==2) {
        dist1 = (vwi-TVector3(w1)).Mag();
        dist2 = (vwi-TVector3(w2)).Mag();

        dist1<dist2?Track3ToPoint(TVector3(po1),TVector3(po2),TVector3(po3),TVector3(w1),vpf,flg,Di,Le,Rad):
        Track3ToPoint(TVector3(po1),TVector3(po2),TVector3(po3),TVector3(w2),vpf,flg,Di,Le,Rad);
        if(flg==2) {std::cerr<<"ABORT"<<std::endl; return 1;} //abort
      } else if(flg==3) {
        dist1 = (vwi-TVector3(w1)).Mag();
        dist2 = (vwi-TVector3(w2)).Mag();
        Int_t quitFlag=0;
        dist1<dist2?Track2ToPoint(TVector3(po1),TVector3(po3),TVector3(w1),vpf,Di,Le,quitFlag):
        Track2ToPoint(TVector3(po1),TVector3(po3),TVector3(w2),vpf,Di,Le,quitFlag);
        if(quitFlag!=0) {std::cerr<<"ABORT"<<std::endl; return 1;} //abort
      } else if(flg==4) {
        Track2ToLine(TVector3(po1),TVector3(po3),TVector3(w1),
                     TVector3(w2),vpf,vwi,flg,Di,Le);
        if(flg==2) {
          std::cerr<<"ABORT"<<std::endl;
          return 1;
        }
      }

    }
  }

  // calculated track length corresponding
  // to the point of closest approach
  trklength = clen[0]+Le;

  // PCA before starting point
  if(trklength<0) { return 1; }
  flag = flg;

  return 0;
}


void FairGeanePro::Track2ToLine( TVector3 X1,  TVector3 X2,  TVector3 w1,
                                 TVector3 w2,  TVector3& Pfinal, TVector3& Pwire,
                                 Int_t& Iflag, Double_t& Dist, Double_t& Length)
{

  // Closest approach to a line from 2 GEANE points
  //
  // METHOD: the nearest points on the two lines
  //         x1,x2 and w1,w2 is found.
  //         The method is described in:
  //  http://softsurfer.com/Archive/algorithm_0106/algorithm_0106.htm
  //  http://www.geometrictools.com/Documentation/DistanceLine3Line3.pdf.
  //
  // INPUT: x1, x2   closest appoach GEANE points
  //        w1, w2   points of the line  (wire)  to approach
  //
  // OUTPUT: Pfinal  point of closest approach on the track
  //         Pwire    point of closest approach on the wire
  //         Dist    distance between Pfian and w1
  //         Length  arc length to add to the GEANE length of x1
  //         Iflag   =1 when Pwire is outside [w1,w2]
  //                 In this case, when w1 and w2 are the extremes
  //                 of the wire, the user could remake the procedure
  //                 by calling Track3ToPoint or Track2ToPoint, where the
  //                 Point is w1 or w2;
  //                 = 2 when the two lines are parallel and the solution
  //                 does not exists.
  //
  // Authors: Andrea Fontana and Alberto Rotondi 20 MAy 2007
  //


  TVector3 x21, x32, w21;
  TVector3 xw1, xw2;

  Double_t a1, b1, c1, d1, e1, t1, s1;
  Double_t Delta1;

  Double_t Eps = 1.E-08;

  Iflag =0;

  // line-line distance
  x21 = X2-X1;
  w21 = w2-w1;

  xw1 = X1-w1;
  xw2 = X2-w1;

  a1 =  x21.Mag2();
  b1 =  x21.Dot(w21);
  c1 =  w21.Mag2();
  d1 =  xw1.Dot(x21);
  e1 =  xw1.Dot(w21);

  Delta1 = a1*c1-b1*b1;

  if(Delta1 > Eps) {
    t1 = (a1*e1-b1*d1)/Delta1;
    s1 = (b1*e1-c1*d1)/Delta1;

    Pfinal = (X1 + x21*s1);
    Pwire  = (w1 + w21*t1);
    Length = s1*x21.Mag();
    Dist= (Pfinal-Pwire).Mag();

  } else {
    // lines are paralllel, no solution does exist
    Pfinal.SetXYZ(0.,0.,0.);
    Pwire.SetXYZ(0.,0.,0.);
    Dist=0.;
    Length=0.;
    Iflag = 2;
    return;
  }
  // flag when the point on the wire is outside (w1,w2)
  if((((Pwire[0]<w1[0] && Pwire[0]<w2[0]) || (w2[0]<Pwire[0] && w1[0]<Pwire[0]))
      && (fabs(Pwire[0]-w1[0]) > 1e-11 && fabs(Pwire[0]- w2[0]) > 1e-11))
      || (((Pwire[1]<w1[1] && Pwire[1]<w2[1]) || (w2[1]<Pwire[1] && w1[1]<Pwire[1]))
          && (fabs(Pwire[1]-w1[1]) > 1e-11 && fabs(Pwire[1]- w2[1]) > 1e-11))
      || (((Pwire[2]<w1[2] && Pwire[2]<w2[2]) || (w2[2]<Pwire[2] && w1[2]<Pwire[2]))
          && (fabs(Pwire[2]-w1[2]) > 1e-11 && fabs(Pwire[2]- w2[2]) > 1e-11))) {
    Iflag=1;
  }
}



void FairGeanePro::Track2ToPoint( TVector3 X1,  TVector3 X2,  TVector3 w1, TVector3& Pfinal,
                                  Double_t& Dist, Double_t& Length, Int_t& quitFlag)
{

  //
  // Closest approach to a point from 2 GEANE points
  //
  // METHOD: the nearest point to w1 on the line x1,x2
  //         is found. Elementary vector calculus is used!
  //
  // INPUT: x1, x2     closest appoach GEANE points
  //        w1         point to approach w1
  //
  // OUTPUT: Pfinal  point of closest approach
  //         Dist    distance between Pfinal and w1
  //         Length  arc length to add to the GEANE length of x1
  //         quitFlag error flag which will be set to 1 if points dont form line
  // Authors: Andrea Fontana and Alberto Rotondi  May 2007
  //

  quitFlag = 0;

  TVector3 u21;

  Double_t a, t1;

  // w-point - x-line distance
  Double_t d=(X2-X1).Mag();
  if(fabs(d)<1.E-8) {
    quitFlag=1;
    return;
  }
  a= 1./d;

  u21 = (X2-X1).Unit();

  // output
  Dist= ((w1-X1).Cross(u21)).Mag();
  t1  =  a*(w1-X1).Dot(u21);
  Pfinal = (X2-X1)*t1 + X1;
  Length = (X2-X1).Mag()*t1;
}


void FairGeanePro::Track3ToLine(TVector3 X1, TVector3 X2, TVector3 X3,
                                TVector3 w1, TVector3 w2,
                                // output
                                TVector3& Pfinal, TVector3& Wire,
                                Int_t& Iflag, Double_t& Dist,
                                Double_t& Length, Double_t& Radius)
{

  // Find the closest approach points between a curve (helix)
  // and a line (wire)
  //
  // METHOD:the classical Eberly method is used: see
  //  http://www.geometrictools.com/Documentation/DistanceLine3Circle.pdf.
  //        (see also www.geometrictools.com for the other formulae used
  //        in this interface).
  //        The 4-degree polynomial resulting for the line parameter t is
  //        solved with the efficient SolveQuartic Root routine.
  //        The minimal distance solution is found by using our Track3ToPoint
  //        routine
  //
  // INPUT: x1, x2, x3  closest appoach GEANE points
  //        w1, w2      points of the line (wire) to approach
  //
  // OUTPUT: Pfinal  track point of closest approach
  //         Wire    line point of closest approach
  //         Iflag   = 1, the points are on a straight line
  //                 within the precision of the method (20 micron).
  //                 In this case the user should recall Track2ToPoint
  //                 = 2, Pwire is outside [w1,w2]
  //                 In this case, when w1 and w2 are the extremes
  //                 of the wire, the user could remake the procedure
  //                 by calling Track3ToPoint, where the Point is w1 or w2.
  //                 = 3 both conditions 1 and 2 are encountered
  //                 = 4, the method failed for mathematical reasons.
  //                 In this case the user should use Track2ToLine where
  //                 x1=x1 and x2=x3.
  //         Dist    distance between Pfinal and Wire
  //         Length  arc length to add to the GEANE length of x1
  //         Radius  radius of the found circle
  //
  // Authors: Andrea Fontana and Alberto Rotondi 20 June  2007
  //

  TVector3 xp1, xp2, xp3, xp32;
  TVector3 x21, x31;
  TVector3 e1, e2, e3, aperp;
  TVector3 Ppfinal, Pwire;
  TVector3 wp1, wp2, wpt, xR, xpR;
  TVector3 xw1, xw2;
  TVector3 px;

  Double_t T[3][3], TM1[3][3];

  TVector3 N, M, D, B, Pointw;
  Double_t a0, a1, b0, b1, c0, c1, c2;
  Double_t d0, d1, d2, d3, d4, sol4[4], dmin;
  Double_t Angle;
  Double_t dx;
  Int_t it, imin;

  Iflag = 0;

  // go to the circle plane: matrix of director cosines

  x21 = X2-X1;
  e1 = x21.Unit();
  T[0][0] = e1.X();
  T[0][1] = e1.Y();
  T[0][2] = e1.Z();

  x31 = X3-X1;
  e3 = e1.Cross(x31);
  // if the points are on the same line
  if(e3.Mag() < 1e-8) {
    Iflag = 1;
    return;
  }
  e3 = e3.Unit();

  T[2][0] = e3.X();
  T[2][1] = e3.Y();
  T[2][2] = e3.Z();

  e2 = e3.Cross(e1);
  T[1][0] = e2.X();
  T[1][1] = e2.Y();
  T[1][2] = e2.Z();

  // new coordinates
  for(Int_t i=0; i<3; i++) {
    xp1[i]=0.;
    xp2[i]=0.;
    xp3[i]=0.;
    wp1[i]=0.;
    wp2[i]=0.;
  }
  for(Int_t i=0; i<3; i++) {
    xp1[i] = 0.;
    for(Int_t j=0; j<3; j++) {
      TM1[i][j] = T[j][i];
      xp2[i] += T[i][j] * (X2[j]-X1[j]);
      xp3[i] += T[i][j] * (X3[j]-X1[j]);
      wp1[i] += T[i][j] * (w1[j]-X1[j]);
      wp2[i] += T[i][j] * (w2[j]-X1[j]);
    }
  }

  // radius and center

  xp32= xp3 - xp2;
  xpR[0] = 0.5*xp2[0];
  if(fabs(xp3[1])<1.E-8) {
    Iflag = 4;
    return;
  }
  xpR[1] = 0.5*(xp32[0]*xp3[0]/xp3[1]+ xp3[1]);
  xpR[2] = 0.;
  Radius = sqrt(pow(xpR[0]-xp1[0],2)+pow(xpR[1]-xp1[1],2));

  // Eberly's method

  B = wp1;
  M = wp2 - wp1;
  D = wp1-xpR;
  N.SetXYZ(0.,0.,1.);

  a0 = M.Dot(D);
  a1 = M.Dot(M);
  b0 = M.Dot(D) -(N.Dot(M))*(N.Dot(D));
  b1 = M.Dot(M) -(N.Dot(M))*(N.Dot(M));
  c0 = D.Dot(D) -(N.Dot(D))*(N.Dot(D));
  c1 = b0;
  c2 = b1;

  d0 = a0*a0*c0 -b0*b0*Radius*Radius;
  d1 = 2.*(a0*a1*c0+a0*a0*c1-b0*b1*Radius*Radius);
  d2 = a1*a1*c0+4.*a0*a1*c1+a0*a0*c2-b1*b1*Radius*Radius;
  d3 = 2.*(a1*a1*c1+a0*a1*c2);
  d4 = a1*a1*c2;

  // solve the quartic equation
  for(Int_t k=0; k<4; k++) {
    sol4[k] =0.;
  }
  if(fabs(d4) < 1.E-12) {
    Iflag = 4;
    return;
  }

  TGeoTorus t;
  it = t.SolveQuartic(d3/d4,d2/d4,d1/d4,d0/d4,sol4);

  if(it==0) {
    Iflag = 4;
    return;
  }

  // select the right solution
  dmin = 1.e+08;
  imin=-1;
  for(Int_t j=0; j<it; j++) {
    Pointw[0] = B[0] + sol4[j]*M[0];
    Pointw[1] = B[1] + sol4[j]*M[1];
    Pointw[2] = B[2] + sol4[j]*M[2];
    Track3ToPoint(xp1,xp2,xp3, Pointw, px, Iflag, dx, Length, Radius);
    if(Iflag==2) {
      Iflag = 4;
      return;
    }
    if(dx<dmin) {
      dmin=dx;
      imin=j;
    }
  }

  // final solution
  Pwire[0] = B[0] + sol4[imin]*M[0];
  Pwire[1] = B[1] + sol4[imin]*M[1];
  Pwire[2] = B[2] + sol4[imin]*M[2];
  Track3ToPoint(xp1,xp2,xp3, Pwire, px, Iflag, dx, Length, Radius);
  if(Iflag==2) {
    Iflag = 4;
    return;
  }

  // output: distance and points in the circle plane reference

  Dist = dx;
  Ppfinal = px;

  //
  // back to lab coordinates
  //

  xR[0]=0.;
  xR[1]=0.;
  xR[2]=0.;
  Pfinal[0]=0.;
  Pfinal[1]=0.;
  Pfinal[2]=0.;
  Wire[0]=0.;
  Wire[1]=0.;
  Wire[2]=0.;

  for(Int_t i=0; i<3; i++) {
    for(Int_t j=0; j<3; j++) {
      Pfinal[i] += TM1[i][j] * Ppfinal[j];
      Wire[i]   += TM1[i][j] * Pwire[j];
      xR[i]     += TM1[i][j] * xpR[j];
    }
  }
  Pfinal = Pfinal+X1;
  Wire   = Wire + X1;
  xR     = xR + X1;

  double dx1=(X1-xR).Mag();
  double dx2=(Pfinal-xR).Mag();
  double dx12=dx1*dx2;
  if(fabs(dx12)<1.E-8) {
    Iflag = 4;
    return;
  }

  // now find the length
  Angle = TMath::ACos((X1-xR).Dot(Pfinal-xR)/(dx12));
  Length = Radius*Angle;
  if((X2-X1).Dot(Pfinal-X1) < 0.) { Length = -Length; }

  // flag straight points within 20 microns
  Double_t epsi=0;
  if(Radius>1E-8) { epsi = Radius*(1.-TMath::Cos(0.5*(X3-X1).Mag()/Radius)); }
  if(epsi < 0.0020) { Iflag=1; }

  // flag when the point on the wire is outside (w1,w2)
  if((((Wire[0]<w1[0] && Wire[0]<w2[0]) || (w2[0]<Wire[0] && w1[0]<Wire[0]))
      && (fabs(Wire[0]-w1[0]) > 1e-11 && fabs(Wire[0]- w2[0]) > 1e-11))
      || (((Wire[1]<w1[1] && Wire[1]<w2[1]) || (w2[1]<Wire[1] && w1[1]<Wire[1]))
          && (fabs(Wire[1]-w1[1]) > 1e-11 && fabs(Wire[1]- w2[1]) > 1e-11))
      || (((Wire[2]<w1[2] && Wire[2]<w2[2]) || (w2[2]<Wire[2] && w1[2]<Wire[2]))
          && (fabs(Wire[2]-w1[2]) > 1e-11 && fabs(Wire[2]- w2[2]) > 1e-11))) {
    Iflag=2;
  }
}

void FairGeanePro::Track3ToPoint( TVector3 X1, TVector3 X2, TVector3 X3, TVector3 w1,
                                  // output
                                  TVector3& Pfinal, Int_t& Iflag,
                                  Double_t& Dist, Double_t& Length, Double_t& Radius)
{

  // Closest approach to a point from 3 GEANE points
  //
  // METHOD: first, we go on the circle plane to have
  //         x1=(0,0), x2=(x2,0), x3=(x3,y3).
  //         Then, the point on the circle is found as the
  //         intersection between the circle and the line
  //         joining the circle center and the projection of
  //         the point on the circle plane.
  //         The 3D distance is found between w1 and this
  //         point on the circle.
  //
  // INPUT: x1, x2, x3 closest appoach GEANE points
  //        w1         point to approach
  //
  // OUTPUT: Pfinal  point of closest approach on the track
  //         Dist    distance between Pfinal and w1
  //         Length  arc length to add to the GEANE length of x1
  //         Iflag   when =1 the points are on a straight line
  //                 within the precision of the method (20 micron).
  //                 In this case the user should recall Track2ToPoint
  //                 if =2 mathematical errors
  // Authors: Andrea Fontana and Alberto Rotondi 20 May 2007
  //


  TVector3 xp1, xp2, xp3, xp32;
  TVector3 x21, x31;
  TVector3 e1, e2, e3;
  TVector3 Ppfinal, x32;
  TVector3 wp1, wpt, xR, xpR;
  TVector3 xw1, xw2;

  TVector3 xc1, xc2, xc3, wc1;

  Double_t m1, m3, Rt;
  Double_t T[3][3], TM1[3][3];

  Double_t Angle;


  Iflag = 0;

  // go to the circle plane with origin in x1 prime (xp1):
  // matrix of director cosines

  x21 = X2-X1;

  Double_t x21mag=x21.Mag();
  if(x21mag<1.E-8) {
    Iflag=2;
    return;
  }

  m1 = 1./x21mag;
  e1 = m1*x21;
  T[0][0] = e1.X();
  T[0][1] = e1.Y();
  T[0][2] = e1.Z();

  x31 = X3-X1;
  e3 = e1.Cross(x31);

  // if the points are on the same line
  if(e3.Mag() < 1e-8) {
    Iflag = 1;
    return;
  }

  m3 = 1./e3.Mag();
  e3 = m3*e3;
  T[2][0] = e3.X();
  T[2][1] = e3.Y();
  T[2][2] = e3.Z();

  e2 = e3.Cross(e1);
  T[1][0] = e2.X();
  T[1][1] = e2.Y();
  T[1][2] = e2.Z();

  // new coordinates
  for(Int_t i=0; i<3; i++) {
    xp1[i]=0.;
    xp2[i]=0.;
    xp3[i]=0.;
    wp1[i]=0.;
  }
  for(Int_t i=0; i<3; i++) {
    for(Int_t j=0; j<3; j++) {
      TM1[i][j] = T[j][i];
      xp1[i] += 0.;
      xp2[i] += T[i][j] * (X2[j]-X1[j]);
      xp3[i] += T[i][j] * (X3[j]-X1[j]);
      wp1[i] += T[i][j] * (w1[j]-X1[j]);
    }
  }

  // radius Radius and center xpR

  xp32= xp3 - xp2;
  xpR[0] = 0.5*xp2[0];
  if(fabs(xp3[1])<1.E-8) {
    Iflag = 2;
    return;
  }
  xpR[1] = 0.5*(xp32[0]*xp3[0]/xp3[1]+ xp3[1]);
  xpR[2] = 0.;

  Radius = sqrt( pow(xpR[0]-xp1[0],2) + pow(xpR[1]-xp1[1],2) );

  // distance and points
  wpt = wp1;
  wpt[2] =0.;   // point projection on the circle plane

  Double_t dwp=(wpt-xpR).Mag();
  if(fabs(dwp)<1.E-8) {
    Iflag = 2;
    return;
  }
  Rt = Radius/dwp;
  Ppfinal = (wpt-xpR)*Rt + xpR;
  Dist = (wp1-Ppfinal).Mag();

  // back to lab coordinates:
  //from Ppfinal to Pfinal and from xpR to xR

  xR[0]=0.;
  xR[1]=0.;
  xR[2]=0.;
  Pfinal[0]=0.;
  Pfinal[1]=0.;
  Pfinal[2]=0.;
  for(Int_t i=0; i<3; i++) {
    for(Int_t j=0; j<3; j++) {
      Pfinal[i] += TM1[i][j] * Ppfinal[j];
      xR[i]     += TM1[i][j] * xpR[j];
    }
  }
  Pfinal = Pfinal+X1;
  xR = xR +X1;

  // now find the length
  double dx1=(X1-xR).Mag();
  double dx2=(Pfinal-xR).Mag();
  double dx12=dx1*dx2;
  if(fabs(dx12)<1.E-8) {
    Iflag = 2;
    return;
  }
  // now find the length
  Angle = TMath::ACos((X1-xR).Dot(Pfinal-xR)/(dx12));
  Length = Radius*Angle;

  // flag straight points within 20 microns
  Double_t epsi=0;
  if(Radius>1E-8) { epsi = Radius*(1.-TMath::Cos(0.5*(X3-X1).Mag()/Radius)); }
  if(epsi < 0.0020) { Iflag=1; }
}

void FairGeanePro::GetTransportMatrix(Double_t trm[5][5])
{
  for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++) { trm[i][j] = trpmat[i][j]; }
}

ClassImp(FairGeanePro)



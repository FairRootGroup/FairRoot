// Class for the interface to propagate track parameters with GEANE
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//
#ifndef CBMGEANEPRO_H
#define CBMGEANEPRO_H 1

#include "TNamed.h"
#include "TVector3.h"
#include "TGeant3.h"

//class TGeant3;
class TDatabasePDG;
class TArrayD;
class CbmTrackPar;
class CbmTrackParP;
class CbmTrackParH;
class CbmField;
class CbmMCApplication;
class CbmGeanePro : public TNamed

{

  public:
  /** Default constructor **/  
   CbmGeanePro();

  /** Destructor **/
  ~CbmGeanePro();

  Bool_t Propagate(CbmTrackParH *TStart, CbmTrackParH *TEnd, Int_t PDG);
  Bool_t Propagate(CbmTrackParP *TStart, CbmTrackParH *TEnd, Int_t PDG);
  Bool_t Propagate(CbmTrackParP *TStart, CbmTrackParP *TEnd, Int_t PDG);
  Bool_t Propagate(CbmTrackParH *TStart, CbmTrackParP *TEnd, Int_t PDG);

  Bool_t PropagateToPlane(TVector3 &v0, TVector3 &v1, TVector3 &v2);
  Bool_t PropagateFromPlane(TVector3 &v1, TVector3 &v2);
  Bool_t PropagateToVolume(TString VolName, Int_t CopyNo ,Int_t option);
  Bool_t PropagateToLength(Float_t length);

  void Init(CbmTrackPar *TParam);
  void Propagate(Int_t PDG);

  void Track2ToLine(TVector3 x1, TVector3 x2, TVector3 w1, TVector3 w2, TVector3 &Pfinal, TVector3 &Pwire, Int_t &Iflag, Double_t &Dist, Double_t &Length);
  void Track2ToPoint(TVector3 x1, TVector3 x2, TVector3 w1, TVector3 &Pfinal, Double_t &Dist, Double_t &Length);
  void Track3ToLine(TVector3 x1, TVector3 x2, TVector3 x3, TVector3 w1, TVector3 w2, TVector3 &Pfinal, TVector3 &Wire, Int_t &Iflag, Double_t &Dist, Double_t &Length, Double_t &Radius);
  void Track3ToPoint(TVector3 x1, TVector3 x2, TVector3 x3, TVector3 w1, TVector3 &Pfinal, Int_t &Iflag, Double_t &Dist, Double_t &Length, Double_t &Radius);

  Bool_t SetWire(TVector3 extremity1, TVector3 extremity2);
  Bool_t SetPoint(TVector3 pnt);
  Bool_t PropagateToPCA(Int_t pca);
  int FindPCA(Int_t pca, Int_t PDGCode, TVector3 point, TVector3 wire1, TVector3 wire2, Double_t maxdistance, Double_t &Rad, TVector3 &vpf, TVector3 &vwi, Double_t &Di, Float_t &trklength);
  TVector3 GetPCAOnWire() { return vwi; }
  TVector3 GetPCAOnTrack() { return vpf; }
  Float_t GetLengthAtPCA() { return trklength; }
  Bool_t PropagateToVirtualPlaneAtPCA(Int_t pca);
  Bool_t BackTrackToVertex();
  Bool_t BackTrackToVirtualPlaneAtPCA(Int_t pca);
  void setBackProp(){fPropOption="BPE";}

  // function to call the FindPCA alone to retrieve 
  // the PCA.
  Bool_t ActualFindPCA(Int_t pca, CbmTrackParP *par, Int_t dir);

  // transport matrix
  void GetTransportMatrix(Double_t trm[5][5]);


 private:

  TGeant3 *gMC3;
  TString fPropOption;
  Float_t ein[15];   // Input error matrix
  Int_t nepred;      // Number of predictions
  TDatabasePDG *fdbPDG;
  Float_t pli[6];
  Float_t x2[3];
  Float_t p2[3];
  TVector3 Pos;
  TVector3 PosErr;
  TVector3 Mom;
  TArrayD *fErrorMat;
  Ertrio_t *afErtrio;
  Float_t x1[3];
  Float_t p1[3];
  Int_t GeantCode;
  CbmTrackParH *fTrkParH;
  CbmTrackParP *fTrkParP;
  CbmTrackPar *fTrkPar;
  Int_t ProMode;
  CbmField *fField;
  Float_t plo[12];
  TString VName;
  Int_t VCopyNo;
  Bool_t VEnter;

  TVector3 fpoint, fwire1, fwire2;
  Int_t fPCA;
  Double_t Rad, Di;
  TVector3 vpf, vwi;
  Float_t trklength;
  Int_t flag; 
  CbmMCApplication *fApp; 
  Double_t trpmat[5][5];
  ClassDef(CbmGeanePro,1);
};

#endif

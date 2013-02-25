// Class for the interface to propagate track parameters with GEANE
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//
#ifndef FAIRGEANEPRO_H
#define FAIRGEANEPRO_H 1

#include "TNamed.h"
#include "TVector3.h"
#include "TGeant3.h"

//class TGeant3;
class TDatabasePDG;
class TArrayD;
class FairTrackPar;
class FairTrackParP;
class FairTrackParH;
class FairField;
class FairGeaneApplication;

class FairGeanePro : public TNamed
{

  public:
    /** Default constructor **/
    FairGeanePro();

    /** Destructor **/
    ~FairGeanePro();

    Bool_t Propagate(FairTrackParH* TStart, FairTrackParH* TEnd, Int_t PDG);
    Bool_t Propagate(FairTrackParP* TStart, FairTrackParH* TEnd, Int_t PDG);
    Bool_t Propagate(FairTrackParP* TStart, FairTrackParP* TEnd, Int_t PDG);
    Bool_t Propagate(FairTrackParH* TStart, FairTrackParP* TEnd, Int_t PDG);
    Bool_t Propagate(Float_t* x1, Float_t* p1, Float_t* x2, Float_t* p2,Int_t PDG);
    Bool_t PropagateToPlane(TVector3& v0, TVector3& v1, TVector3& v2);
    Bool_t PropagateFromPlane(TVector3& v1, TVector3& v2);
    Bool_t PropagateToVolume(TString VolName, Int_t CopyNo ,Int_t option);
    Bool_t PropagateToLength(Float_t length);
    Bool_t PropagateOnlyParameters();

    void Init(FairTrackPar* TParam);
    Bool_t Propagate(Int_t PDG);

  private:
    void Track2ToLine(TVector3 x1, TVector3 x2, TVector3 w1, TVector3 w2, TVector3& Pfinal, TVector3& Pwire, Int_t& Iflag, Double_t& Dist, Double_t& Length);
    void Track2ToPoint(TVector3 x1, TVector3 x2, TVector3 w1, TVector3& Pfinal, Double_t& Dist, Double_t& Length, Int_t& quitFlag);
    void Track3ToLine(TVector3 x1, TVector3 x2, TVector3 x3, TVector3 w1, TVector3 w2, TVector3& Pfinal, TVector3& Wire, Int_t& Iflag, Double_t& Dist, Double_t& Length, Double_t& Radius);
    void Track3ToPoint(TVector3 x1, TVector3 x2, TVector3 x3, TVector3 w1, TVector3& Pfinal, Int_t& Iflag, Double_t& Dist, Double_t& Length, Double_t& Radius);

  public:

    Bool_t SetWire(TVector3 extremity1, TVector3 extremity2);
    Bool_t SetPoint(TVector3 pnt);
    Bool_t PropagateToPCA(Int_t pca);
    Bool_t PropagateToPCA(Int_t pca, Int_t dir);
    int FindPCA(Int_t pca, Int_t PDGCode, TVector3 point, TVector3 wire1, TVector3 wire2, Double_t maxdistance, Double_t& Rad, TVector3& vpf, TVector3& vwi, Double_t& Di, Float_t& trklength);
    TVector3 GetPCAOnWire() { return fvwi; }
    TVector3 GetPCAOnTrack() { return fvpf; }
    Float_t GetLengthAtPCA() { return ftrklength; }
    Bool_t PropagateToVirtualPlaneAtPCA(Int_t pca);
    Bool_t BackTrackToVertex();
    Bool_t BackTrackToVirtualPlaneAtPCA(Int_t pca);
    void setBackProp() {fPropOption="BPE";}

    // function to call the FindPCA alone to retrieve
    // the PCA.
    Bool_t ActualFindPCA(Int_t pca, FairTrackParP* par, Int_t dir);

    // transport matrix
    void GetTransportMatrix(Double_t trm[5][5]);


  private:

    TGeant3* gMC3;
    TString fPropOption;
    Float_t xlf[1];    // track length when PropagateToTrack is chosen
    Float_t ein[15];   // Input error matrix
    Int_t nepred;      // Number of predictions
    TDatabasePDG* fdbPDG;
    Float_t pli[6];
    Float_t x2[3];
    Float_t p2[3];
    /*   TVector3 Pos; */
    /*   TVector3 PosErr; */
    /*   TVector3 Mom; */
    /*   TArrayD *fErrorMat; */
    Ertrio_t* afErtrio;
    Float_t x1[3];
    Float_t p1[3];
    Int_t GeantCode;
    /*   FairTrackParH *fTrkParH; */
    /*   FairTrackParP *fTrkParP; */
    /*   FairTrackPar *fTrkPar; */
    Int_t ProMode;
    /*   FairField *fField; */
    Float_t plo[12];
    TString VName;
    Int_t VCopyNo;
    Bool_t VEnter;

    TVector3 fpoint, fwire1, fwire2;
    Int_t fPCA;
    Double_t fRad, fDi;
    TVector3 fvpf, fvwi;
    Float_t ftrklength;
    Int_t flag;
    FairGeaneApplication* fApp;
    Double_t trpmat[5][5];

    FairGeanePro(const FairGeanePro&);
    FairGeanePro& operator=(const FairGeanePro&);

    ClassDef(FairGeanePro,1);
};

#endif

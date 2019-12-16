/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Class for the interface to propagate track parameters with GEANE
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//
#ifndef FAIRGEANEPRO_H
#define FAIRGEANEPRO_H 1

#include "FairPropagator.h"                     // for TNamed

#include "FairLogger.h"

#include "TGeant3.h"                    // for Ertrio_t, etc
#include "TString.h"                    // for TString
#include "TVector3.h"                   // for TVector3

class FairTrackPar;
class FairTrackParP;
class FairTrackParH;
class FairGeaneApplication;
class TDatabasePDG;

class FairGeanePro : public FairPropagator
{
  public:
    /** Default constructor **/
    FairGeanePro();

    /** Destructor **/
    ~FairGeanePro();

    /* Old methods that still should be working */
    virtual bool Propagate(FairTrackParH* TStart, FairTrackParH* TEnd, int PDG);
    virtual bool Propagate(FairTrackParP* TStart, FairTrackParH* TEnd, int PDG);
    virtual bool Propagate(FairTrackParP* TStart, FairTrackParP* TEnd, int PDG);
    virtual bool Propagate(FairTrackParH* TStart, FairTrackParP* TEnd, int PDG);
    virtual bool Propagate(float* x1, float* p1, float* x2, float* p2, int PDG);

    /* Old methods that still should be working */

    /**New method to set the plane to propagate particles to
     @v0 v1 v2  Plane defining vectors
    */
    virtual bool SetDestinationPlane(TVector3& v0, TVector3& v1, TVector3& v2);

    /**New method to set the plane to propagate particles from
     @v0 v1     Plane defining vectors
    */
    virtual bool SetOriginPlane(TVector3& v0, TVector3& v1);

    /**New method to set the volume to propagate particles to
       @volName Volume name
       @copyNo  Copy number
       @option  Option
    */
    virtual bool SetDestinationVolume(std::string volName, int copyNo, int option);

    /**New method to set the length to propagate particles to
       @length  Track length
    */
    virtual bool SetDestinationLength(float length);

    /**New method to set to propagate only parameters
    */
    virtual bool SetPropagateOnlyParameters();

    /* ====== Depracated functions ====== */
    bool PropagateToPlane(TVector3& v0, TVector3& v1, TVector3& v2);
    bool PropagateFromPlane(TVector3& v1, TVector3& v2);
    bool PropagateToVolume(TString VolName, int CopyNo ,int option);
    bool PropagateToLength(float length);
    bool PropagateOnlyParameters();
    /* ====== ====== ====== ====== ====== */

    void Init(FairTrackPar* TParam);
    bool Propagate(int PDG);

  private:
    void Track2ToLine(TVector3 x1, TVector3 x2, TVector3 w1, TVector3 w2, TVector3& Pfinal, TVector3& Pwire, int& Iflag, double& Dist, double& Length);
    void Track2ToPoint(TVector3 x1, TVector3 x2, TVector3 w1, TVector3& Pfinal, double& Dist, double& Length, int& quitFlag);
    void Track3ToLine(TVector3 x1, TVector3 x2, TVector3 x3, TVector3 w1, TVector3 w2, TVector3& Pfinal, TVector3& Wire, int& Iflag, double& Dist, double& Length, double& Radius);
    void Track3ToPoint(TVector3 x1, TVector3 x2, TVector3 x3, TVector3 w1, TVector3& Pfinal, int& Iflag, double& Dist, double& Length, double& Radius);

  public:
    /* ====== Depracated functions ====== */
    int FindPCA(int pca, int PDGCode, TVector3 point, TVector3 wire1, TVector3 wire2, double maxdistance, double& Rad, TVector3& vpf, TVector3& vwi, double& Di, float& trklength);

    bool SetWire(TVector3 extremity1, TVector3 extremity2);
    bool SetPoint(TVector3 pnt);
    bool PropagateToPCA(int pca);
    bool PropagateToPCA(int pca, int dir);
    // function to call the FindPCA alone to retrieve
    // the PCA.
    bool ActualFindPCA(int pca, FairTrackParP* par, int dir);

    TVector3 GetPCAOnWire() {
        LOG(warning) << "Function GetPCAOnWire obsolete, contact FairRoot group if you need it.";
        return fvwi;
    }
    TVector3 GetPCAOnTrack() {
        LOG(warning) << "Function GetPCAOnTrack obsolete, contact FairRoot group if you need it.";
        return fvpf;
    }
    float GetLengthAtPCA() {
        LOG(warning) << "Function GetLengthAtPCA obsolete, contact FairRoot group if you need it.";
        return ftrklength;
    }
    float GetTimeAtPCA() {
        LOG(warning) << "Function GetTimeAtPCA obsolete, contact FairRoot group if you need it.";
        return ftrktime;
    }

    bool PropagateToVirtualPlaneAtPCA(int pca);
    bool BackTrackToVertex();
    bool BackTrackToVirtualPlaneAtPCA(int pca);
    /* ====== ====== ====== ====== ====== */

    void setBackProp() {
        fPropOption="BPE";
    }

    virtual bool SetPCAPropagation(int pca, int dir = 1, FairTrackParP* par = nullptr);

    virtual PCAOutputStruct FindPCA(int PCA, int PDGCode, TVector3 Point, TVector3 Wire1, TVector3 Wire2, double MaxDistance);

    // transport matrix
    void GetTransportMatrix(double trm[5][5]);

    void SetPrintErrors(bool printError = kTRUE) { fPrintErrors = printError; }

  private:
    TGeant3* gMC3;
    TString fPropOption;
    float xlf[1];    // track length when PropagateToTrack is chosen
    float ein[15];   // Input error matrix
    int nepred;      // Number of predictions
    TDatabasePDG* fdbPDG;
    float pli[6];
    float x2[3];
    float p2[3];
    /*   TVector3 Pos; */
    /*   TVector3 PosErr; */
    /*   TVector3 Mom; */
    /*   TArrayD *fErrorMat; */
    Ertrio_t* afErtrio;
    float x1[3];
    float p1[3];
    int GeantCode;
    /*   FairTrackParH *fTrkParH; */
    /*   FairTrackParP *fTrkParP; */
    /*   FairTrackPar *fTrkPar; */
    int ProMode;
    /*   FairField *fField; */
    float plo[12];
    TString VName;
    int VCopyNo;
    bool VEnter;

    TVector3 fpoint, fwire1, fwire2;
    int fPCA;
    double fRad, fDi;
    TVector3 fvpf, fvwi;
    float ftrklength;
    float ftrktime;
    int flag;
    FairGeaneApplication* fApp;
    double trpmat[5][5];

    // if kFALSE --> do not print the ABORT messages
    bool fPrintErrors;

    FairGeanePro(const FairGeanePro&);
    FairGeanePro& operator=(const FairGeanePro&);

    ClassDef(FairGeanePro,2);
};

#endif

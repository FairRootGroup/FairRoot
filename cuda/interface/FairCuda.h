/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef _FAIRCUDA_H_
#define _FAIRCUDA_H_

#include "../cuda_imp/HitTrk.h"
#include "Rtypes.h"
#include "TObject.h"
#include "iostream.h"
#include "TMatrixD.h"
//extern "C" Float_t denlan_(Float_t *x);
extern "C" void IncrementArray(Int_t device);
extern "C" void DeviceInfo();


//extern "C" void runTest(Int_t argc);
//extern "C" void CudaFilter(const double *, const double *, const double *, const double * , int , int , const double *, int, int, const double*, int, int, const double *, const double*);

extern "C" void CudaFilter(TMatrixD* h, TMatrixD* fM, TMatrixD* pull, TMatrixD* fH, TMatrixD* preC, TMatrixD* prea, TMatrixD* av, TMatrixD* curC ,TMatrixD* fV, TMatrixD* fR, TMatrixD* fResVec, double* fDeltaChi2 );


extern "C" void CircleFitG(Double_t X[HIT], Double_t Y[HIT], Double_t Z[HIT], Double_t Zerr[HIT], Double_t* Mx,Double_t* My,Double_t* M0,Double_t result[8]);

extern "C" void CircleFitGAllD(Double_t X[TRK* HIT], Double_t Y[TRK* HIT], Double_t Z[TRK* HIT], Double_t Zerr[TRK* HIT], Double_t Mx[TRK],Double_t My[TRK],Double_t M0[TRK],Double_t result[8*TRK]);

extern "C" void CircleFitGAllF(Float_t X[TRK* HIT], Float_t Y[TRK* HIT], Float_t Z[TRK* HIT], Float_t Zerr[TRK* HIT], Float_t Mx[TRK],Float_t My[TRK],Float_t M0[TRK],Float_t result[8*TRK]);


extern "C" void CircleFitGF(Float_t X[HIT], Float_t Y[HIT], Float_t Z[HIT], Float_t Zerr[HIT], Float_t* Mx,Float_t* My,Float_t* M0,Float_t result[8]);

class FairCuda : public TObject
{
  public:
    FairCuda() {;}
    virtual ~FairCuda() {;}

    void IncrementArray_(Int_t device) {return IncrementArray(device);}
    void DeviceInfo_() {return DeviceInfo();}
// void runTest_(Int_t argc){return runTest(argc);}
//  void Filter(){cout << "Cuda Filter "<< endl;}
    void Filter(TMatrixD* h, TMatrixD* fM, TMatrixD* pull, TMatrixD* fH, TMatrixD* preC, TMatrixD* prea, TMatrixD* av, TMatrixD* curC, TMatrixD* fV, TMatrixD* fR, TMatrixD* fResVec, double* fDeltaChi2) {
      return CudaFilter(h,fM, pull, fH, preC, prea,av,curC, fV, fR,fResVec,fDeltaChi2);
    }


    void CircleFit(Double_t X[HIT], Double_t Y[HIT],Double_t Z[HIT], Double_t Zerr[HIT], Double_t* Mx,Double_t* My,Double_t* M0, Double_t result[8]) {
      //  printf("\n Cuda  Mx = %f  My = %f\n ", Mx[0], My[0]);
      return CircleFitG(X,Y,Z,Zerr,Mx,My,M0,result);
    }


    void CircleFitAllD(Double_t X[TRK* HIT], Double_t Y[TRK* HIT],Double_t Z[TRK* HIT], Double_t Zerr[TRK* HIT], Double_t Mx[TRK],Double_t My[TRK],Double_t M0[TRK], Double_t result[8*TRK]) {
      //    printf("\n Fair Cuda  : Call GPU function \n ");
      return CircleFitGAllD(X,Y,Z,Zerr,Mx,My,M0,result);
//       printf("\n Fair Cuda  : Back to Application \n ");

    }

    void CircleFitAllF(Float_t X[TRK* HIT], Float_t Y[TRK* HIT],Float_t Z[TRK* HIT], Float_t Zerr[TRK* HIT], Float_t Mx[TRK],Float_t My[TRK],Float_t M0[TRK], Float_t result[8*TRK]) {
//       printf("\n Fair Cuda  : Call GPU function \n ");
      return CircleFitGAllF(X,Y,Z,Zerr,Mx,My,M0,result);
//       printf("\n Fair Cuda  : Back to Application \n ");

    }



    void CircleFitF (Float_t X[HIT], Float_t Y[HIT],Float_t Z[HIT], Float_t Zerr[HIT], Float_t* Mx,Float_t* My,Float_t* M0, Float_t result[8]) {
      //  printf("\n Cuda  Mx = %f  My = %f\n ", Mx[0], My[0]);
      return CircleFitGF(X,Y,Z,Zerr,Mx,My,M0,result);
    }

    ClassDef(FairCuda, 1)
};


#endif



/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEANEUTIL_H
#define FAIRGEANEUTIL_H
#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <RtypesCore.h>  // for Double_t, Int_t
#include <TObject.h>     // for TObject
#include <TVector3.h>    // for TVector3
class TBuffer;
class TClass;
class TMemberInspector;

class FairGeaneUtil : public TObject
{
  public:
    FairGeaneUtil();
    ~FairGeaneUtil();

    // frame changing
    void FromPtToSC(Double_t PC[3], Double_t RC[15], Double_t* PD, Double_t* RD, Int_t& IERR);

    void FromPtToSD(Double_t PD[3],
                    Double_t RD[15],
                    Double_t H[3],
                    Int_t CH,
                    Double_t SPU,
                    Double_t DJ[3],
                    Double_t DK[3],
                    Int_t& IERR,
                    Double_t* PC,
                    Double_t* RC);

    void FromSCToPt(Double_t PC[3], Double_t RC[15], Double_t* PD, Double_t* RD, Int_t& IERR);

    void FromSCToSD(Double_t PC[3],
                    Double_t RC[15],
                    Double_t H[3],
                    Int_t CH,
                    Double_t DJ[3],
                    Double_t DK[3],
                    Int_t& IERR,
                    Double_t& SPU,
                    Double_t* PD,
                    Double_t* RD);

    void FromSD1ToSD2(Double_t PD1[3],
                      Double_t RD1[15],
                      Double_t H[3],
                      Int_t CH,
                      Double_t SP1,
                      Double_t DJ1[3],
                      Double_t DK1[3],
                      Double_t DJ2[3],
                      Double_t DK2[3],
                      Int_t& IERR,
                      Double_t& SP2,
                      Double_t* PD2,
                      Double_t* RD2);

    void FromSDToPt(Double_t PD[3],
                    Double_t RD[15],
                    Double_t H[3],
                    Int_t CH,
                    Double_t SPU,
                    Double_t DJ[3],
                    Double_t DK[3],
                    Int_t& IERR,
                    Double_t* PC,
                    Double_t* RC);

    void FromSDToSC(Double_t PD[3],
                    Double_t RD[15],
                    Double_t H[3],
                    Int_t CH,
                    Double_t SPU,
                    Double_t DJ[3],
                    Double_t DK[3],
                    Int_t& IERR,
                    Double_t* PC,
                    Double_t* RC);

    typedef Double_t sixMat[6][6];
    void FromSCToMars(Double_t PC[3], Double_t RC[15], Double_t H[3], Int_t CH, Double_t* PD, sixMat& RD);

    void FromMarsToSC(Double_t PD[3], Double_t RD[6][6], Double_t H[3], Int_t CH, Double_t* PC, Double_t* RC);

    void FromSDToMars(Double_t PC[3],
                      Double_t RC[15],
                      Double_t H[3],
                      Int_t CH,
                      Double_t SP1,
                      Double_t DJ1[3],
                      Double_t DK1[3],
                      Double_t* PD,
                      sixMat& RD);

    void FromMarsToSD(Double_t PD[3],
                      Double_t RD[6][6],
                      Double_t H[3],
                      Int_t CH,
                      Double_t DJ1[3],
                      Double_t DK1[3],
                      Int_t& IERR,
                      Double_t& SP1,
                      Double_t* PC,
                      Double_t* RC);

    void FromMat25ToVec15(Double_t A[5][5], Double_t* V);
    void FromMatToVec(Double_t A[5][5], Double_t* V);

    typedef Double_t fiveMat[5][5];
    void FromVec15ToMat25(Double_t V[15], fiveMat& A);

    void FromVecToMat(fiveMat& A, Double_t V[25]);
    void SymmProd(Double_t A[25], Double_t S[15], Double_t* R);
    TVector3 FromMARSToSDCoord(TVector3 xyz, TVector3 o, TVector3 di, TVector3 dj, TVector3 dk);
    TVector3 FromSDToMARSCoord(TVector3 uvw, TVector3 o, TVector3 di, TVector3 dj, TVector3 dk);

    ClassDef(FairGeaneUtil, 1);
};

#endif

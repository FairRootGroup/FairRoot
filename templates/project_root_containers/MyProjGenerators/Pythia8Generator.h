/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                  M. Al-Turany   June 2014                     -----
// -------------------------------------------------------------------------

#ifndef My_PYTHIA8GENERATOR_H
#define My_PYTHIA8GENERATOR_H 1

#include "FairGenerator.h"    // for FairGenerator
#include "Pythia8/Basics.h"   // for RndmEngine
#include "Pythia8/Pythia.h"   // for Pythia

#include <Rtypes.h>           // for Double_t, Bool_t, Int_t, etc
#include <TRandom.h>          // for TRandom
#include <TRandom1.h>         // for TRandom1
#include <TRandom3.h>         // for TRandom3, gRandom
class FairPrimaryGenerator;   // lines 22-22

class FairPrimaryGenerator;

class PyTr1Rng : public RndmEngine
{
  public:
    PyTr1Rng() { rng = new TRandom1(gRandom->TRandom::GetSeed()); };
    virtual ~PyTr1Rng(){};

    Double_t flat() { return rng->Rndm(); };

  private:
    TRandom1 *rng;   //!
};

class PyTr3Rng : public RndmEngine
{
  public:
    PyTr3Rng() { rng = new TRandom3(gRandom->TRandom::GetSeed()); };
    virtual ~PyTr3Rng(){};

    Double_t flat() { return rng->Rndm(); };

  private:
    TRandom3 *rng;   //!
};

class Pythia8Generator : public FairGenerator
{
  public:
    /** default constructor **/
    Pythia8Generator();

    /** destructor **/
    virtual ~Pythia8Generator();

    /** public method ReadEvent **/
    Bool_t ReadEvent(FairPrimaryGenerator *);
    void SetParameters(char *);
    void Print();   //!

    virtual Bool_t Init();   //!

    void SetMom(Double_t mom) { fMom = mom; };
    void SetId(Double_t id) { fId = id; };
    void SetHNLId(Int_t id) { fHNL = id; };
    void UseRandom1()
    {
        fUseRandom1 = kTRUE;
        fUseRandom3 = kFALSE;
    };
    void UseRandom3()
    {
        fUseRandom1 = kFALSE;
        fUseRandom3 = kTRUE;
    };
    void GetPythiaInstance(int);

  private:
    Pythia fPythia;              //!
    RndmEngine *fRandomEngine;   //!

  protected:
    Double_t fMom;        // proton momentum
    Int_t fHNL;           // HNL ID
    Int_t fId;            // target type
    Bool_t fUseRandom1;   // flag to use TRandom1
    Bool_t fUseRandom3;   // flag to use TRandom3 (default)

    ClassDef(Pythia8Generator, 1);
};

#endif /* !My_PYTHIA8GENERATOR_H */

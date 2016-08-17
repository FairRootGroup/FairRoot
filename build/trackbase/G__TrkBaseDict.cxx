// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddItrackbasedIG__TrkBaseDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "FairTrackPar.h"
#include "FairTrackParP.h"
#include "FairTrackParH.h"
#include "FairGeaneUtil.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairTrackPar(void *p = 0);
   static void *newArray_FairTrackPar(Long_t size, void *p);
   static void delete_FairTrackPar(void *p);
   static void deleteArray_FairTrackPar(void *p);
   static void destruct_FairTrackPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTrackPar*)
   {
      ::FairTrackPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTrackPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTrackPar", ::FairTrackPar::Class_Version(), "invalid", 21,
                  typeid(::FairTrackPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTrackPar::Dictionary, isa_proxy, 4,
                  sizeof(::FairTrackPar) );
      instance.SetNew(&new_FairTrackPar);
      instance.SetNewArray(&newArray_FairTrackPar);
      instance.SetDelete(&delete_FairTrackPar);
      instance.SetDeleteArray(&deleteArray_FairTrackPar);
      instance.SetDestructor(&destruct_FairTrackPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTrackPar*)
   {
      return GenerateInitInstanceLocal((::FairTrackPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTrackPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTrackParP(void *p = 0);
   static void *newArray_FairTrackParP(Long_t size, void *p);
   static void delete_FairTrackParP(void *p);
   static void deleteArray_FairTrackParP(void *p);
   static void destruct_FairTrackParP(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTrackParP*)
   {
      ::FairTrackParP *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTrackParP >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTrackParP", ::FairTrackParP::Class_Version(), "invalid", 198,
                  typeid(::FairTrackParP), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTrackParP::Dictionary, isa_proxy, 4,
                  sizeof(::FairTrackParP) );
      instance.SetNew(&new_FairTrackParP);
      instance.SetNewArray(&newArray_FairTrackParP);
      instance.SetDelete(&delete_FairTrackParP);
      instance.SetDeleteArray(&deleteArray_FairTrackParP);
      instance.SetDestructor(&destruct_FairTrackParP);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTrackParP*)
   {
      return GenerateInitInstanceLocal((::FairTrackParP*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTrackParP*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTrackParH(void *p = 0);
   static void *newArray_FairTrackParH(Long_t size, void *p);
   static void delete_FairTrackParH(void *p);
   static void deleteArray_FairTrackParH(void *p);
   static void destruct_FairTrackParH(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTrackParH*)
   {
      ::FairTrackParH *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTrackParH >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTrackParH", ::FairTrackParH::Class_Version(), "invalid", 367,
                  typeid(::FairTrackParH), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTrackParH::Dictionary, isa_proxy, 4,
                  sizeof(::FairTrackParH) );
      instance.SetNew(&new_FairTrackParH);
      instance.SetNewArray(&newArray_FairTrackParH);
      instance.SetDelete(&delete_FairTrackParH);
      instance.SetDeleteArray(&deleteArray_FairTrackParH);
      instance.SetDestructor(&destruct_FairTrackParH);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTrackParH*)
   {
      return GenerateInitInstanceLocal((::FairTrackParH*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTrackParH*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeaneUtil(void *p = 0);
   static void *newArray_FairGeaneUtil(Long_t size, void *p);
   static void delete_FairGeaneUtil(void *p);
   static void deleteArray_FairGeaneUtil(void *p);
   static void destruct_FairGeaneUtil(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeaneUtil*)
   {
      ::FairGeaneUtil *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeaneUtil >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeaneUtil", ::FairGeaneUtil::Class_Version(), "invalid", 496,
                  typeid(::FairGeaneUtil), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeaneUtil::Dictionary, isa_proxy, 4,
                  sizeof(::FairGeaneUtil) );
      instance.SetNew(&new_FairGeaneUtil);
      instance.SetNewArray(&newArray_FairGeaneUtil);
      instance.SetDelete(&delete_FairGeaneUtil);
      instance.SetDeleteArray(&deleteArray_FairGeaneUtil);
      instance.SetDestructor(&destruct_FairGeaneUtil);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeaneUtil*)
   {
      return GenerateInitInstanceLocal((::FairGeaneUtil*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeaneUtil*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairTrackPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTrackPar::Class_Name()
{
   return "FairTrackPar";
}

//______________________________________________________________________________
const char *FairTrackPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrackPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTrackPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrackPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTrackPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrackPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTrackPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrackPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTrackParP::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTrackParP::Class_Name()
{
   return "FairTrackParP";
}

//______________________________________________________________________________
const char *FairTrackParP::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParP*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTrackParP::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParP*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTrackParP::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParP*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTrackParP::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParP*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTrackParH::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTrackParH::Class_Name()
{
   return "FairTrackParH";
}

//______________________________________________________________________________
const char *FairTrackParH::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParH*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTrackParH::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParH*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTrackParH::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParH*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTrackParH::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParH*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeaneUtil::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeaneUtil::Class_Name()
{
   return "FairGeaneUtil";
}

//______________________________________________________________________________
const char *FairGeaneUtil::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeaneUtil*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeaneUtil::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeaneUtil*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeaneUtil::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeaneUtil*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeaneUtil::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeaneUtil*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairTrackPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTrackPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTrackPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTrackPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTrackPar(void *p) {
      return  p ? new(p) ::FairTrackPar : new ::FairTrackPar;
   }
   static void *newArray_FairTrackPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairTrackPar[nElements] : new ::FairTrackPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTrackPar(void *p) {
      delete ((::FairTrackPar*)p);
   }
   static void deleteArray_FairTrackPar(void *p) {
      delete [] ((::FairTrackPar*)p);
   }
   static void destruct_FairTrackPar(void *p) {
      typedef ::FairTrackPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTrackPar

//______________________________________________________________________________
void FairTrackParP::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTrackParP.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTrackParP::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTrackParP::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTrackParP(void *p) {
      return  p ? new(p) ::FairTrackParP : new ::FairTrackParP;
   }
   static void *newArray_FairTrackParP(Long_t nElements, void *p) {
      return p ? new(p) ::FairTrackParP[nElements] : new ::FairTrackParP[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTrackParP(void *p) {
      delete ((::FairTrackParP*)p);
   }
   static void deleteArray_FairTrackParP(void *p) {
      delete [] ((::FairTrackParP*)p);
   }
   static void destruct_FairTrackParP(void *p) {
      typedef ::FairTrackParP current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTrackParP

//______________________________________________________________________________
void FairTrackParH::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTrackParH.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTrackParH::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTrackParH::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTrackParH(void *p) {
      return  p ? new(p) ::FairTrackParH : new ::FairTrackParH;
   }
   static void *newArray_FairTrackParH(Long_t nElements, void *p) {
      return p ? new(p) ::FairTrackParH[nElements] : new ::FairTrackParH[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTrackParH(void *p) {
      delete ((::FairTrackParH*)p);
   }
   static void deleteArray_FairTrackParH(void *p) {
      delete [] ((::FairTrackParH*)p);
   }
   static void destruct_FairTrackParH(void *p) {
      typedef ::FairTrackParH current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTrackParH

//______________________________________________________________________________
void FairGeaneUtil::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeaneUtil.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGeaneUtil::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGeaneUtil::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeaneUtil(void *p) {
      return  p ? new(p) ::FairGeaneUtil : new ::FairGeaneUtil;
   }
   static void *newArray_FairGeaneUtil(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeaneUtil[nElements] : new ::FairGeaneUtil[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeaneUtil(void *p) {
      delete ((::FairGeaneUtil*)p);
   }
   static void deleteArray_FairGeaneUtil(void *p) {
      delete [] ((::FairGeaneUtil*)p);
   }
   static void destruct_FairGeaneUtil(void *p) {
      typedef ::FairGeaneUtil current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGeaneUtil

namespace {
  void TriggerDictionaryInitialization_G__TrkBaseDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/Users/turany/development/FairRoot/fairtools",
"/Users/turany/development/FairRoot/geobase",
"/Users/turany/development/FairRoot/parbase",
"/Users/turany/development/FairRoot/base",
"/Users/turany/development/FairRoot/base/steer",
"/Users/turany/development/FairRoot/base/event",
"/Users/turany/development/FairRoot/base/field",
"/Users/turany/development/FairRoot/base/sim",
"/Users/turany/development/FairRoot/base/source",
"/Users/turany/development/FairRoot/field",
"/Users/turany/development/FairRoot/passive",
"/Users/turany/development/FairRoot/trackbase",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/trackbase/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__TrkBaseDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairTrackPar;
class FairTrackParP;
class FairTrackParH;
class FairGeaneUtil;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__TrkBaseDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRSTSTRACKPAR
#define FAIRSTSTRACKPAR 1

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Double_t, Int_t, etc
#include "TVector3.h"                   // for TVector3

class FairTrackPar : public TObject
{

  public:

    /** Constructor **/
    FairTrackPar();

    /** Constructor with all variables **/
    FairTrackPar(Double_t x,  Double_t y,  Double_t z,
                 Double_t fx, Double_t fy, Double_t fz, Int_t q);

    /** Destructor **/
    virtual ~FairTrackPar();

    /** Output to screen **/
    virtual void  Print(Option_t* option = "") const;
    /** Accessors **/
    virtual TVector3 GetPosition() const {
      return TVector3(fX, fY, fZ);
    };

    virtual Double_t GetX()   {
      return fX;
    };
    virtual Double_t GetY()   {
      return fY;
    };
    virtual Double_t GetZ()   {
      return fZ;
    };
    Int_t   GetQ()  const {
      return fq;
    };

    virtual Double_t GetDX()  const {
      return fDX;
    };
    virtual Double_t GetDY()  const {
      return fDY;
    };
    virtual Double_t GetDZ()  const {
      return fDZ;
    };

    virtual TVector3 GetMomentum() const {
      return TVector3(fPx, fPy, fPz);
    };

    virtual Double_t GetPx() const {
      return fPx;
    };
    virtual Double_t GetPy() const {
      return fPy;
    };
    virtual Double_t GetPz() const {
      return fPz;
    };
    virtual Double_t GetQp() const {
      return fQp;
    };

    virtual Double_t GetDPx() const {
      return fDPx;
    };
    virtual Double_t GetDPy() const {
      return fDPy;
    };
    virtual Double_t GetDPz() const {
      return fDPz;
    };
    virtual Double_t GetDQp() const {
      return fDQp;
    };

    virtual void GetFieldValue(const Double_t point[3], Double_t* bField);


    virtual void SetX(Double_t x)   {
      fX  = x;
    };
    virtual void SetY(Double_t y)   {
      fY  = y;
    };
    virtual void SetZ(Double_t z)   {
      fZ  = z;
    };

    virtual void SetDX(Double_t dx)   {
      fDX  = dx;
    };
    virtual void SetDY(Double_t dy)   {
      fDY  = dy;
    };
    virtual void SetDZ(Double_t dz)   {
      fDZ  = dz;
    };

    virtual void SetPx(Double_t px) {
      fPx = px;
    };
    virtual void SetPy(Double_t py) {
      fPy = py;
    };
    virtual void SetPz(Double_t pz) {
      fPz = pz;
    };

    virtual void SetDPx(Double_t dpx) {
      fDPx = dpx;
    };
    virtual void SetDPy(Double_t dpy) {
      fDPy = dpy;
    };
    virtual void SetDPz(Double_t dpz) {
      fDPz = dpz;
    };

    void SetQp(Double_t qp) {
      fQp = qp;
    };


  protected:

    /** Position of track [cm] **/
    Double_t fX, fY, fZ;

    /** Error in position of track [cm] **/
    Double_t fDX, fDY, fDZ;

    /** momentum  [GeV]**/
    Double_t fPx, fPy, fPz;

    /** Error in momentum  [GeV]**/
    Double_t fDPx, fDPy, fDPz;

    /** Charge over momentum [1/GeV] **/
    Double_t fQp;

    /** Error in charge over momentum [1/GeV] **/
    Double_t fDQp;

    /** charge*/
    Int_t fq;

    ClassDef(FairTrackPar,2);

};
#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Class for the representation of a track as parabola (SD system)
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//
//
// GEANE parameters (q/p, v', w', v, w) of Helix track
// The Helix can be constructed using the Helix parameter (1/p, v', w', v, w) in SC reference
// and the covariance matrix. Or using position and momentum in LAB referance.

#ifndef FAIRSTSTRACKPARP
#define FAIRSTSTRACKPARP 1

#include "FairTrackPar.h"               // for FairTrackPar

#include "Rtypes.h"                     // for Double_t, Int_t, etc
#include "TVector3.h"                   // for TVector3

class FairTrackParH;

class FairTrackParP : public FairTrackPar
{

  public:

    /** Constructor **/
    FairTrackParP();

    /** Constructor with all track variables in SD **/
    // spu = the sign of u-component of particle momentum
    // constructor without spu, to be used when spu is calculated as output
    //  DJ(3)     UNIT VECTOR IN V-DIRECTION
    //      DK(3)     UNIT VECTOR IN W-DIRECTION    OF DETECTOR SYSTEM


    FairTrackParP(Double_t v, Double_t w,
                  Double_t Tv, Double_t Tw, Double_t qp,
                  Double_t CovMatrix[15],
                  TVector3 o, TVector3 dj, TVector3 dk);
    // constructor with spu, to be used when spu is needed as input
    FairTrackParP(Double_t v, Double_t w,
                  Double_t Tv, Double_t Tw, Double_t qp,
                  Double_t CovMatrix[15],
                  TVector3 o, TVector3 dj, TVector3 dk, Double_t spu);

    /** Constructor with position and momentum track in LAB **/
    // DIAGONAL MARS covariance matrix
    FairTrackParP(TVector3 pos, TVector3 Mom,
                  TVector3 posErr, TVector3 MomErr, Int_t q,
                  TVector3 o, TVector3 dj, TVector3 dk);
    // NON DIAGONAL MARS covariance matrix
    FairTrackParP(TVector3 pos, TVector3 Mom,
                  Double_t covMARS[6][6], Int_t q,
                  TVector3 o, TVector3 dj, TVector3 dk);
    // constructor from helix
    FairTrackParP(FairTrackParH* helix, TVector3 dj, TVector3 dk, Int_t& ierr);

    /** Destructor **/
    virtual ~FairTrackParP();

    /** copy Constructor **/
    //to be implemented


    /** Output to screen **/
    virtual void  Print(Option_t* option = "") const;

    //define track parameters in LAB
    void SetTrackPar(Double_t X,  Double_t Y,  Double_t Z, Double_t Px, Double_t Py, Double_t Pz, Int_t Q, Double_t  CovMatrix[15], TVector3 o, TVector3 di, TVector3 dj, TVector3 dk);
    //void SetTrackPar(Double_t X,  Double_t Y,  Double_t Z, Double_t Px, Double_t Py, Double_t Pz, Int_t Q, Double_t  CovMatrix[15]);
    //define track parameters in SD
    void SetTrackPar(Double_t v, Double_t w, Double_t Tv, Double_t Tw, Double_t qp,Double_t CovMatrix[15], TVector3 o, TVector3 di, TVector3 dj, TVector3 dk, Double_t spu);
    //void SetTrackPar(Double_t v, Double_t w, Double_t Tv, Double_t Tw, Double_t qp,Double_t CovMatrix[15]);

    /** Modifiers **/
    void SetTV(Double_t tv) { fTV = tv; };
    void SetTW(Double_t tw) { fTW = tw; };

    void Reset();
    ClassDef(FairTrackParP,1);

    /** Accessors **/

    // MARS
    /* Double_t GetDX();
     Double_t GetDY();
     Double_t GetDZ();
     Double_t GetDPx();
     Double_t GetDPy();
     Double_t GetDPz();
     Double_t GetDQp();
     Double_t GetX();
     Double_t GetY();
     Double_t GetZ();
    */
    // MARS
    void GetMARSCov(Double_t Cov66[6][6]) {for(Int_t i=0; i<6; i++) for(Int_t j=0; j<6; j++) { Cov66[i][j] = fCovMatrix66[i][j]; }  }

    // SD
    Double_t* GetCov() {return fCovMatrix;};
    void GetCov(Double_t* Cov) {for(Int_t i=0; i<15; i++) { Cov[i]=fCovMatrix[i]; }}
    void GetCovQ(Double_t* CovQ);
    Double_t GetV();
    Double_t GetW();
    Double_t GetTV();
    Double_t GetTW();
    Double_t GetDV();
    Double_t GetDW();
    Double_t GetDTV();
    Double_t GetDTW();

    // SD MOMENTUM
    TVector3 GetSDMomentum() {return TVector3(fPx_sd, fPy_sd, fPz_sd);}

    // plane
    TVector3 GetOrigin();
    TVector3 GetIVer();
    TVector3 GetJVer();
    TVector3 GetKVer();
    void SetPlane(TVector3 o, TVector3 dj, TVector3 dk);

    // spu
    Double_t GetSPU() {return fSPU;};

    // set/get transport matrix
    void SetTransportMatrix(Double_t mat[5][5]);
    void GetTransportMatrix(Double_t mat[5][5]);

  private:

    /** Points coordinates in SD system */
    Double_t fU, fV, fW, fTV, fTW;
    /** momentum id SD **/
    Double_t fPx_sd, fPy_sd, fPz_sd;
    /** Errors in SD system */
    Double_t fDU, fDV, fDW, fDTV, fDTW;
    /** Covariant matrix*/
    // in SD
    Double_t fCovMatrix[15];
    // in MARS
    Double_t fCovMatrix66[6][6];

    /**Calculate the cov. mat. for this helix*/
    void CalCov();

    // plane
    TVector3 forigin;
    TVector3 fiver;
    TVector3 fjver;
    TVector3 fkver;
    Double_t fDI[3]; //!
    Double_t fDJ[3]; //!
    Double_t fDK[3]; //!
    // spu
    Double_t fSPU;
    // transport matrix
    Double_t ftrmat[5][5]; //!

};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Class for the representation of a track as helix (SC system)
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//
//
// GEANE parameters (q/p, lambda, phi, y_perp, z_perp) of Helix track
// The Helix can be constructed using the Helix parameter (1/p, lambda, phi,y_perp,z_perp) in SC reference
// and the covariance matrix. Or using position and momentum in LAB referance.

#ifndef FAIRSTSTRACKPARH
#define FAIRSTSTRACKPARH 1

#include "FairTrackPar.h"               // for FairTrackPar

#include "Rtypes.h"                     // for Double_t, Int_t, etc
#include "TVector3.h"                   // for TVector3

class FairTrackParP;

class FairTrackParH : public FairTrackPar
{

  public:

    /** Constructor **/
    FairTrackParH();

    /** Constructor with track variables  (in SC) **/
    FairTrackParH(Double_t x,  Double_t y,  Double_t z,
                  Double_t lambda, Double_t phi, Double_t qp,
                  Double_t CovMatrix[15]);

    /** Constructor track parameters with position and momentum (in LAB)**/

    FairTrackParH(TVector3 pos, TVector3 Mom, TVector3 posErr, TVector3 MomErr, Int_t q);

    /** copy Constructor **/
    FairTrackParH(FairTrackPar& Trkbase);

    //FairTrackParH(FairTrackParH &Trk);

    FairTrackParH(FairTrackParP* parab, Int_t& ierr);

    /** Destructor **/
    virtual ~FairTrackParH();

    /** Output to screen **/
//   void Print();
    virtual void  Print(Option_t* option = "") const;

    /** Accessors **/
    Double_t GetLambda() { return fLm; };
    Double_t GetPhi() { return fPhi; };
    Double_t GetDLambda() ; /**Get Error in Lambda*/
    Double_t GetDPhi()  ;   /**Get Error in Phi*/
    /**Get the coveriant matrix*/
    void GetCov(Double_t* Cov) {for(Int_t i=0; i<15; i++) { Cov[i]=fCovMatrix[i]; }}
    void GetCovQ(Double_t* CovQ);
    // MARS
    void GetMARSCov(Double_t Cov66[6][6]) {for(Int_t i=0; i<6; i++) for(Int_t j=0; j<6; j++) { Cov66[i][j] = fCovMatrix66[i][j]; }  }
    Double_t GetDX_sc();  /**Get dx in SC*/
    Double_t GetDY_sc();  /**Get dy in SC*/
    Double_t GetDZ_sc();  /**Get dz in SC*/
    Double_t GetX_sc() {return fX_sc;} /**Get x in SC*/
    Double_t GetY_sc() {return fY_sc;} /**Get y in SC*/
    Double_t GetZ_sc() {return fZ_sc;} /**Get z in SC*/
// Double_t GetDPx() ;   /**Get error in Px (in SC frame)*/
// Double_t GetDPy() ;   /**Get error in Py (in SC frame)*/
// Double_t GetDPz() ;   /**Get error in Pz (in SC frame)*/
//  Double_t GetDQp() ;   /**Get error in Q/P*/
    Double_t GetX();  /**Get X in Lab*/
    Double_t GetY();  /**Get Y in Lab*/
    Double_t GetZ();  /**Get Z in Lab*/



    /** Modifiers **/
    void SetLambda(Double_t Lm ) { fLm = Lm; };
    void SetPhi(Double_t Phi) { fPhi = Phi; };

    void SetDLambda(Double_t DLm ) { fDLm = DLm; };
    void SetDPhi(Double_t DPhi) { fDPhi = DPhi; };

    void  SetX_sc(Double_t x) {fX_sc =x;} /**Set x in SC*/
    void  SetY_sc(Double_t y) {fY_sc =y;} /**Set y in SC*/
    void  SetZ_sc(Double_t z) {fZ_sc =z;} /**Set z in SC*/
    void  SetCov(Double_t* Cov) {for(Int_t i=0; i<15; i++) { fCovMatrix[i]=Cov[i]; }}
    void  SetTrackPar(Double_t x,  Double_t y,  Double_t z,
                      Double_t Px, Double_t Py, Double_t Pz, Int_t Q,
                      Double_t CovMatrix[15]);

    void  SetTrackPar(Double_t x,  Double_t y,  Double_t z,
                      Double_t pq, Double_t lm, Double_t phi,  Double_t CovMatrix[15]);
    void Reset();
    ClassDef(FairTrackParH,1);


  private:

    /** fLm = Dip angle **/
    Double_t fLm;
    /**fPhi = azimuthal angle **/
    Double_t fPhi;
    /** Error in Lambda*/
    Double_t fDLm;
    /** Error in Phi*/
    Double_t fDPhi;
    /** Points coordinates in SC system */
    Double_t fX_sc, fY_sc, fZ_sc;
    /** Errors for X,Y,Z  (in SC system) */
    Double_t fDX_sc, fDY_sc, fDZ_sc;
    /** Covariant matrix in SC*/
    Double_t fCovMatrix[15];
    // in MARS
    Double_t fCovMatrix66[6][6];

    /**Calculate the cov. mat. for this helix*/
    void CalCov();

    /** just to simplify a little bit typing the equations
       cLm  = Cos(Lambda),
       sLm  = Sin(Lambda),
       cphi = cos(Phi),
       sphi = Sin(Phi)
       //! do not streame this to the file
    */
    Double_t cLm,sLm, cphi ,sphi; //!

};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEANEUTIL_H
#define FAIRGEANEUTIL_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Double_t, Int_t, etc
#include "TVector3.h"                   // for TVector3

class FairGeaneUtil : public TObject
{

  public:
    FairGeaneUtil();
    ~FairGeaneUtil();

    // frame changing
    void FromPtToSC(Double_t PC[3], Double_t RC[15],
                    Double_t* PD, Double_t* RD, Int_t& IERR);

    void FromPtToSD(Double_t PD[3], Double_t RD[15], Double_t H[3],Int_t CH,
                    Double_t SPU, Double_t DJ[3], Double_t DK[3],
                    Int_t& IERR, Double_t* PC, Double_t* RC);

    void FromSCToPt(Double_t PC[3], Double_t RC[15],
                    Double_t* PD, Double_t* RD, Int_t& IERR);

    void FromSCToSD(Double_t PC[3], Double_t RC[15], Double_t H[3], Int_t CH,
                    Double_t DJ[3], Double_t DK[3],
                    Int_t& IERR, Double_t& SPU,
                    Double_t* PD, Double_t* RD);

    void FromSD1ToSD2(Double_t PD1[3], Double_t RD1[15],Double_t H[3],
                      Int_t CH, Double_t SP1,
                      Double_t DJ1[3], Double_t DK1[3],
                      Double_t DJ2[3], Double_t DK2[3],
                      Int_t& IERR, Double_t& SP2,
                      Double_t* PD2, Double_t* RD2);

    void FromSDToPt(Double_t PD[3], Double_t RD[15], Double_t H[3],
                    Int_t CH, Double_t SPU, Double_t DJ[3], Double_t DK[3],
                    Int_t& IERR, Double_t* PC, Double_t* RC);

    void FromSDToSC(Double_t PD[3], Double_t RD[15], Double_t H[3], Int_t CH,
                    Double_t SPU, Double_t DJ[3], Double_t DK[3],
                    Int_t& IERR, Double_t* PC, Double_t* RC);

    typedef Double_t sixMat[6][6];
    void FromSCToMars(Double_t PC[3], Double_t RC[15], Double_t H[3], Int_t CH,
                      Double_t* PD, sixMat& RD);

    void FromMarsToSC(Double_t PD[3], Double_t RD[6][6],  Double_t H[3],
                      Int_t CH,
                      Double_t* PC, Double_t* RC);

    void FromSDToMars(Double_t PC[3], Double_t RC[15],
                      Double_t H[3], Int_t CH,
                      Double_t SP1, Double_t DJ1[3], Double_t DK1[3],
                      Double_t* PD, sixMat& RD);

    void FromMarsToSD(Double_t PD[3], Double_t RD[6][6],
                      Double_t H[3], Int_t CH,
                      Double_t DJ1[3], Double_t DK1[3],
                      Int_t& IERR, Double_t& SP1,
                      Double_t* PC, Double_t* RC);

    //---------------------------------------

    void FromMat25ToVec15(Double_t A[5][5], Double_t* V);
    void FromMatToVec(Double_t A[5][5], Double_t* V);

    typedef Double_t fiveMat[5][5];
    void FromVec15ToMat25(Double_t V[15], fiveMat& A);

    void FromVecToMat(fiveMat& A, Double_t V[25]);
    void SymmProd(Double_t A[25], Double_t S[15], Double_t* R);
    TVector3 FromMARSToSDCoord(TVector3 xyz, TVector3 o, TVector3 di, TVector3 dj, TVector3 dk);
    TVector3 FromSDToMARSCoord(TVector3 uvw, TVector3 o, TVector3 di, TVector3 dj, TVector3 dk);

    ClassDef(FairGeaneUtil,1);
};


#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairGeaneUtil", payloadCode, "@",
"FairTrackPar", payloadCode, "@",
"FairTrackParH", payloadCode, "@",
"FairTrackParP", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__TrkBaseDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__TrkBaseDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__TrkBaseDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__TrkBaseDict() {
  TriggerDictionaryInitialization_G__TrkBaseDict_Impl();
}

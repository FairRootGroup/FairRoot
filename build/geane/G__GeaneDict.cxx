// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIgeanedIG__GeaneDict

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
#include "FairGeane.h"
#include "FairGeanePro.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairGeane(void *p = 0);
   static void *newArray_FairGeane(Long_t size, void *p);
   static void delete_FairGeane(void *p);
   static void deleteArray_FairGeane(void *p);
   static void destruct_FairGeane(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeane*)
   {
      ::FairGeane *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeane >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeane", ::FairGeane::Class_Version(), "invalid", 28,
                  typeid(::FairGeane), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeane::Dictionary, isa_proxy, 4,
                  sizeof(::FairGeane) );
      instance.SetNew(&new_FairGeane);
      instance.SetNewArray(&newArray_FairGeane);
      instance.SetDelete(&delete_FairGeane);
      instance.SetDeleteArray(&deleteArray_FairGeane);
      instance.SetDestructor(&destruct_FairGeane);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeane*)
   {
      return GenerateInitInstanceLocal((::FairGeane*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeane*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeanePro(void *p = 0);
   static void *newArray_FairGeanePro(Long_t size, void *p);
   static void delete_FairGeanePro(void *p);
   static void deleteArray_FairGeanePro(void *p);
   static void destruct_FairGeanePro(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeanePro*)
   {
      ::FairGeanePro *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeanePro >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeanePro", ::FairGeanePro::Class_Version(), "invalid", 91,
                  typeid(::FairGeanePro), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeanePro::Dictionary, isa_proxy, 4,
                  sizeof(::FairGeanePro) );
      instance.SetNew(&new_FairGeanePro);
      instance.SetNewArray(&newArray_FairGeanePro);
      instance.SetDelete(&delete_FairGeanePro);
      instance.SetDeleteArray(&deleteArray_FairGeanePro);
      instance.SetDestructor(&destruct_FairGeanePro);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeanePro*)
   {
      return GenerateInitInstanceLocal((::FairGeanePro*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeanePro*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairGeane::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeane::Class_Name()
{
   return "FairGeane";
}

//______________________________________________________________________________
const char *FairGeane::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeane*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeane::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeane*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeane::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeane*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeane::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeane*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeanePro::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeanePro::Class_Name()
{
   return "FairGeanePro";
}

//______________________________________________________________________________
const char *FairGeanePro::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeanePro*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeanePro::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeanePro*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeanePro::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeanePro*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeanePro::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeanePro*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairGeane::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeane.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGeane::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGeane::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeane(void *p) {
      return  p ? new(p) ::FairGeane : new ::FairGeane;
   }
   static void *newArray_FairGeane(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeane[nElements] : new ::FairGeane[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeane(void *p) {
      delete ((::FairGeane*)p);
   }
   static void deleteArray_FairGeane(void *p) {
      delete [] ((::FairGeane*)p);
   }
   static void destruct_FairGeane(void *p) {
      typedef ::FairGeane current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGeane

//______________________________________________________________________________
void FairGeanePro::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeanePro.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGeanePro::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGeanePro::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeanePro(void *p) {
      return  p ? new(p) ::FairGeanePro : new ::FairGeanePro;
   }
   static void *newArray_FairGeanePro(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeanePro[nElements] : new ::FairGeanePro[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeanePro(void *p) {
      delete ((::FairGeanePro*)p);
   }
   static void deleteArray_FairGeanePro(void *p) {
      delete [] ((::FairGeanePro*)p);
   }
   static void destruct_FairGeanePro(void *p) {
      typedef ::FairGeanePro current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGeanePro

namespace {
  void TriggerDictionaryInitialization_G__GeaneDict_Impl() {
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
"/Users/turany/development/FairRoot/trackbase",
"/Users/turany/development/FairRoot/base/source",
"/Users/turany/development/FairRoot/geane",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include/TGeant3",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/geane/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__GeaneDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairGeane;
class FairGeanePro;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__GeaneDict dictionary payload"

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
// Class for the GEANE initialization
//
// Author: M. Al-Turany
//
#ifndef FAIRGeane_H
#define FAIRGeane_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for FairGeane::Class, ClassDef, etc
#include "TString.h"                    // for TString

class FairGeaneApplication;
class FairField;

class FairGeane : public  FairTask
{
  public:

    /** Default constructor **/
    //FairGeane();

    FairGeane(const char* name, TString UserConfig="",    TString UserCuts="");

    FairGeane(TString fUserConfig="",    TString fUserCuts="");

    InitStatus Init();

    void SetParTask();

    virtual ~FairGeane();

    void SetField(FairField* field);

    ClassDef(FairGeane,1)

  protected:
    FairGeaneApplication* fApp; //!
    const char* fName; //!
    TString fUserConfig;  //!
    TString fUserCuts; //!

  private:
    FairGeane(const FairGeane&);
    FairGeane& operator=(const FairGeane&);

};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// Class for the interface to propagate track parameters with GEANE
//
// Authors: M. Al-Turany, A. Fontana, L. Lavezzi and A. Rotondi
//
#ifndef FAIRGEANEPRO_H
#define FAIRGEANEPRO_H 1

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Int_t, Bool_t, Double_t, etc
#include "TGeant3.h"                    // for Ertrio_t, etc
#include "TString.h"                    // for TString
#include "TVector3.h"                   // for TVector3

class FairTrackPar;
class FairTrackParP;
class FairTrackParH;
class FairGeaneApplication;
class TDatabasePDG;

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

    void SetPrintErrors(bool printError = kTRUE) { fPrintErrors = printError; }

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

    // if kFALSE --> do not print the ABORT messages
    Bool_t fPrintErrors;

    FairGeanePro(const FairGeanePro&);
    FairGeanePro& operator=(const FairGeanePro&);

    ClassDef(FairGeanePro,1);
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairGeane", payloadCode, "@",
"FairGeanePro", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__GeaneDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__GeaneDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__GeaneDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__GeaneDict() {
  TriggerDictionaryInitialization_G__GeaneDict_Impl();
}

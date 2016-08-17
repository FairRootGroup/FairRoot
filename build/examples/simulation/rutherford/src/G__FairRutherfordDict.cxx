// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIsimulationdIrutherforddIsrcdIG__FairRutherfordDict

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
#include "FairRutherford.h"
#include "FairRutherfordContFact.h"
#include "FairRutherfordGeo.h"
#include "FairRutherfordGeoPar.h"
#include "FairRutherfordPoint.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairRutherfordContFact(void *p = 0);
   static void *newArray_FairRutherfordContFact(Long_t size, void *p);
   static void delete_FairRutherfordContFact(void *p);
   static void deleteArray_FairRutherfordContFact(void *p);
   static void destruct_FairRutherfordContFact(void *p);
   static void streamer_FairRutherfordContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRutherfordContFact*)
   {
      ::FairRutherfordContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRutherfordContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRutherfordContFact", ::FairRutherfordContFact::Class_Version(), "invalid", 130,
                  typeid(::FairRutherfordContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRutherfordContFact::Dictionary, isa_proxy, 16,
                  sizeof(::FairRutherfordContFact) );
      instance.SetNew(&new_FairRutherfordContFact);
      instance.SetNewArray(&newArray_FairRutherfordContFact);
      instance.SetDelete(&delete_FairRutherfordContFact);
      instance.SetDeleteArray(&deleteArray_FairRutherfordContFact);
      instance.SetDestructor(&destruct_FairRutherfordContFact);
      instance.SetStreamerFunc(&streamer_FairRutherfordContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRutherfordContFact*)
   {
      return GenerateInitInstanceLocal((::FairRutherfordContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRutherfordContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRutherfordGeo(void *p = 0);
   static void *newArray_FairRutherfordGeo(Long_t size, void *p);
   static void delete_FairRutherfordGeo(void *p);
   static void deleteArray_FairRutherfordGeo(void *p);
   static void destruct_FairRutherfordGeo(void *p);
   static void streamer_FairRutherfordGeo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRutherfordGeo*)
   {
      ::FairRutherfordGeo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRutherfordGeo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRutherfordGeo", ::FairRutherfordGeo::Class_Version(), "invalid", 159,
                  typeid(::FairRutherfordGeo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRutherfordGeo::Dictionary, isa_proxy, 16,
                  sizeof(::FairRutherfordGeo) );
      instance.SetNew(&new_FairRutherfordGeo);
      instance.SetNewArray(&newArray_FairRutherfordGeo);
      instance.SetDelete(&delete_FairRutherfordGeo);
      instance.SetDeleteArray(&deleteArray_FairRutherfordGeo);
      instance.SetDestructor(&destruct_FairRutherfordGeo);
      instance.SetStreamerFunc(&streamer_FairRutherfordGeo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRutherfordGeo*)
   {
      return GenerateInitInstanceLocal((::FairRutherfordGeo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRutherfordGeo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRutherfordGeoPar(void *p = 0);
   static void *newArray_FairRutherfordGeoPar(Long_t size, void *p);
   static void delete_FairRutherfordGeoPar(void *p);
   static void deleteArray_FairRutherfordGeoPar(void *p);
   static void destruct_FairRutherfordGeoPar(void *p);
   static void streamer_FairRutherfordGeoPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRutherfordGeoPar*)
   {
      ::FairRutherfordGeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRutherfordGeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRutherfordGeoPar", ::FairRutherfordGeoPar::Class_Version(), "invalid", 203,
                  typeid(::FairRutherfordGeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRutherfordGeoPar::Dictionary, isa_proxy, 16,
                  sizeof(::FairRutherfordGeoPar) );
      instance.SetNew(&new_FairRutherfordGeoPar);
      instance.SetNewArray(&newArray_FairRutherfordGeoPar);
      instance.SetDelete(&delete_FairRutherfordGeoPar);
      instance.SetDeleteArray(&deleteArray_FairRutherfordGeoPar);
      instance.SetDestructor(&destruct_FairRutherfordGeoPar);
      instance.SetStreamerFunc(&streamer_FairRutherfordGeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRutherfordGeoPar*)
   {
      return GenerateInitInstanceLocal((::FairRutherfordGeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRutherfordGeoPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRutherford(void *p = 0);
   static void *newArray_FairRutherford(Long_t size, void *p);
   static void delete_FairRutherford(void *p);
   static void deleteArray_FairRutherford(void *p);
   static void destruct_FairRutherford(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRutherford*)
   {
      ::FairRutherford *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRutherford >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRutherford", ::FairRutherford::Class_Version(), "invalid", 26,
                  typeid(::FairRutherford), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRutherford::Dictionary, isa_proxy, 4,
                  sizeof(::FairRutherford) );
      instance.SetNew(&new_FairRutherford);
      instance.SetNewArray(&newArray_FairRutherford);
      instance.SetDelete(&delete_FairRutherford);
      instance.SetDeleteArray(&deleteArray_FairRutherford);
      instance.SetDestructor(&destruct_FairRutherford);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRutherford*)
   {
      return GenerateInitInstanceLocal((::FairRutherford*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRutherford*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRutherfordPoint(void *p = 0);
   static void *newArray_FairRutherfordPoint(Long_t size, void *p);
   static void delete_FairRutherfordPoint(void *p);
   static void deleteArray_FairRutherfordPoint(void *p);
   static void destruct_FairRutherfordPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRutherfordPoint*)
   {
      ::FairRutherfordPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRutherfordPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRutherfordPoint", ::FairRutherfordPoint::Class_Version(), "invalid", 247,
                  typeid(::FairRutherfordPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRutherfordPoint::Dictionary, isa_proxy, 4,
                  sizeof(::FairRutherfordPoint) );
      instance.SetNew(&new_FairRutherfordPoint);
      instance.SetNewArray(&newArray_FairRutherfordPoint);
      instance.SetDelete(&delete_FairRutherfordPoint);
      instance.SetDeleteArray(&deleteArray_FairRutherfordPoint);
      instance.SetDestructor(&destruct_FairRutherfordPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRutherfordPoint*)
   {
      return GenerateInitInstanceLocal((::FairRutherfordPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRutherfordPoint*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairRutherfordContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRutherfordContFact::Class_Name()
{
   return "FairRutherfordContFact";
}

//______________________________________________________________________________
const char *FairRutherfordContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRutherfordContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRutherfordContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRutherfordContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRutherfordGeo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRutherfordGeo::Class_Name()
{
   return "FairRutherfordGeo";
}

//______________________________________________________________________________
const char *FairRutherfordGeo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordGeo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRutherfordGeo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordGeo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRutherfordGeo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordGeo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRutherfordGeo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordGeo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRutherfordGeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRutherfordGeoPar::Class_Name()
{
   return "FairRutherfordGeoPar";
}

//______________________________________________________________________________
const char *FairRutherfordGeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordGeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRutherfordGeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordGeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRutherfordGeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordGeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRutherfordGeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordGeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRutherford::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRutherford::Class_Name()
{
   return "FairRutherford";
}

//______________________________________________________________________________
const char *FairRutherford::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherford*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRutherford::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherford*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRutherford::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherford*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRutherford::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherford*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRutherfordPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRutherfordPoint::Class_Name()
{
   return "FairRutherfordPoint";
}

//______________________________________________________________________________
const char *FairRutherfordPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRutherfordPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRutherfordPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRutherfordPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRutherfordPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairRutherfordContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRutherfordContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRutherfordContFact(void *p) {
      return  p ? new(p) ::FairRutherfordContFact : new ::FairRutherfordContFact;
   }
   static void *newArray_FairRutherfordContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairRutherfordContFact[nElements] : new ::FairRutherfordContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRutherfordContFact(void *p) {
      delete ((::FairRutherfordContFact*)p);
   }
   static void deleteArray_FairRutherfordContFact(void *p) {
      delete [] ((::FairRutherfordContFact*)p);
   }
   static void destruct_FairRutherfordContFact(void *p) {
      typedef ::FairRutherfordContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRutherfordContFact(TBuffer &buf, void *obj) {
      ((::FairRutherfordContFact*)obj)->::FairRutherfordContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRutherfordContFact

//______________________________________________________________________________
void FairRutherfordGeo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRutherfordGeo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoSet::Streamer(R__b);
      R__b.ReadStaticArray((char*)modName);
      R__b.ReadStaticArray((char*)eleName);
      R__b.CheckByteCount(R__s, R__c, FairRutherfordGeo::IsA());
   } else {
      R__c = R__b.WriteVersion(FairRutherfordGeo::IsA(), kTRUE);
      FairGeoSet::Streamer(R__b);
      R__b.WriteArray(modName, 20);
      R__b.WriteArray(eleName, 20);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRutherfordGeo(void *p) {
      return  p ? new(p) ::FairRutherfordGeo : new ::FairRutherfordGeo;
   }
   static void *newArray_FairRutherfordGeo(Long_t nElements, void *p) {
      return p ? new(p) ::FairRutherfordGeo[nElements] : new ::FairRutherfordGeo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRutherfordGeo(void *p) {
      delete ((::FairRutherfordGeo*)p);
   }
   static void deleteArray_FairRutherfordGeo(void *p) {
      delete [] ((::FairRutherfordGeo*)p);
   }
   static void destruct_FairRutherfordGeo(void *p) {
      typedef ::FairRutherfordGeo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRutherfordGeo(TBuffer &buf, void *obj) {
      ((::FairRutherfordGeo*)obj)->::FairRutherfordGeo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRutherfordGeo

//______________________________________________________________________________
void FairRutherfordGeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRutherfordGeoPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b.CheckByteCount(R__s, R__c, FairRutherfordGeoPar::IsA());
   } else {
      R__c = R__b.WriteVersion(FairRutherfordGeoPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRutherfordGeoPar(void *p) {
      return  p ? new(p) ::FairRutherfordGeoPar : new ::FairRutherfordGeoPar;
   }
   static void *newArray_FairRutherfordGeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairRutherfordGeoPar[nElements] : new ::FairRutherfordGeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRutherfordGeoPar(void *p) {
      delete ((::FairRutherfordGeoPar*)p);
   }
   static void deleteArray_FairRutherfordGeoPar(void *p) {
      delete [] ((::FairRutherfordGeoPar*)p);
   }
   static void destruct_FairRutherfordGeoPar(void *p) {
      typedef ::FairRutherfordGeoPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRutherfordGeoPar(TBuffer &buf, void *obj) {
      ((::FairRutherfordGeoPar*)obj)->::FairRutherfordGeoPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRutherfordGeoPar

//______________________________________________________________________________
void FairRutherford::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRutherford.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRutherford::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRutherford::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRutherford(void *p) {
      return  p ? new(p) ::FairRutherford : new ::FairRutherford;
   }
   static void *newArray_FairRutherford(Long_t nElements, void *p) {
      return p ? new(p) ::FairRutherford[nElements] : new ::FairRutherford[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRutherford(void *p) {
      delete ((::FairRutherford*)p);
   }
   static void deleteArray_FairRutherford(void *p) {
      delete [] ((::FairRutherford*)p);
   }
   static void destruct_FairRutherford(void *p) {
      typedef ::FairRutherford current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRutherford

//______________________________________________________________________________
void FairRutherfordPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRutherfordPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRutherfordPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRutherfordPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRutherfordPoint(void *p) {
      return  p ? new(p) ::FairRutherfordPoint : new ::FairRutherfordPoint;
   }
   static void *newArray_FairRutherfordPoint(Long_t nElements, void *p) {
      return p ? new(p) ::FairRutherfordPoint[nElements] : new ::FairRutherfordPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRutherfordPoint(void *p) {
      delete ((::FairRutherfordPoint*)p);
   }
   static void deleteArray_FairRutherfordPoint(void *p) {
      delete [] ((::FairRutherfordPoint*)p);
   }
   static void destruct_FairRutherfordPoint(void *p) {
      typedef ::FairRutherfordPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRutherfordPoint

namespace {
  void TriggerDictionaryInitialization_G__FairRutherfordDict_Impl() {
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
"/Users/turany/development/FairRoot/dbase",
"/Users/turany/development/FairRoot/dbase/dbInterface",
"/Users/turany/development/FairRoot/dbase/dbValidation",
"/Users/turany/development/FairRoot/dbase/dbUtils",
"/Users/turany/development/FairRoot/input/db",
"/Users/turany/development/FairRoot/dbase/dbInput",
"/Users/turany/development/FairRoot/dbase/dbIO",
"/Users/turany/development/FairRoot/examples/simulation/rutherford/src",
"/Users/turany/development/FairRoot/examples/common/mcstack",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/simulation/rutherford/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__FairRutherfordDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Factory for all FairRutherford parameter containers)ATTRDUMP"))) FairRutherfordContFact;
class FairRutherfordGeo;
class FairRutherfordGeoPar;
class FairRutherford;
class FairRutherfordPoint;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__FairRutherfordDict dictionary payload"

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
#ifndef CBMRUTHERFORD_H
#define CBMRUTHERFORD_H

#include "FairDetector.h"               // for FairDetector

#include "Rtypes.h"                     // for Int_t, Double32_t, Double_t, etc
#include "TLorentzVector.h"             // for TLorentzVector
#include "TVector3.h"                   // for TVector3

class FairRutherfordPoint;
class FairVolume;
class TClonesArray;

class FairRutherford: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    FairRutherford(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairRutherford();

    /**       destructor     */
    virtual ~FairRutherford();

    /**      Initialization of the detector is done here    */
    virtual void   Initialize();

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
    */
    virtual Bool_t ProcessHits( FairVolume* v=0);

    /**       Registers the produced collections in FAIRRootManager.     */
    virtual void   Register();

    /** Gets the produced collections */
    virtual TClonesArray* GetCollection(Int_t iColl) const ;

    /**      has to be called after each event to reset the containers      */
    virtual void   Reset();

    /**      Create the detector geometry        */
    void ConstructGeometry();



    /**      This method is an example of how to add your own point
     *       of type FairRutherfordPoint to the clones array
    */
    FairRutherfordPoint* AddHit(Int_t trackID, Int_t detID,
                                TVector3 pos, TVector3 mom,
                                Double_t time, Double_t length,
                                Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
    */

//    virtual void   CopyClones( TClonesArray* cl1,  TClonesArray* cl2 ,
//                               Int_t offset) {;}
    virtual void   SetSpecialPhysicsCuts() {;}
    virtual void   EndOfEvent();
    virtual void   FinishPrimary() {;}
    virtual void   FinishRun() {;}
    virtual void   BeginPrimary() {;}
    virtual void   PostTrack() {;}
    virtual void   PreTrack() {;}
    virtual void   BeginEvent() {;}


  private:

    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t          fTrackID;           //!  track index
    Int_t          fVolumeID;          //!  volume id
    TLorentzVector fPos;               //!  position at entrance
    TLorentzVector fMom;               //!  momentum at entrance
    Double32_t     fTime;              //!  time
    Double32_t     fLength;            //!  length
    Double32_t     fELoss;             //!  energy loss

    /** container for data points */

    TClonesArray*  fFairRutherfordPointCollection;

    FairRutherford(const FairRutherford&);
    FairRutherford& operator=(const FairRutherford&);

    ClassDef(FairRutherford,1)
};

#endif //CBMRUTHERFORD_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDCONTFACT_H
#define CBMRUTHERFORDCONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for ClassDef

class FairParSet;

class FairRutherfordContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairRutherfordContFact();
    ~FairRutherfordContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairRutherfordContFact,0) // Factory for all FairRutherford parameter containers
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDGEO_H
#define CBMRUTHERFORDGEO_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Rtypes.h"                     // for Int_t, etc

#include "TString.h"                    // for TString

class  FairRutherfordGeo : public FairGeoSet
{

  protected:
    char modName[20];  // name of module
    char eleName[20];  // substring for elements in module
  public:
    FairRutherfordGeo();
    ~FairRutherfordGeo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(FairRutherfordGeo,1)
};

inline Int_t FairRutherfordGeo::getModNumInMod(const TString& name)
{
  /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   newdetector ?? has to be 11.
  */
  return static_cast<Int_t>((name[10]-'0')-1); //
}

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDGEOPAR_H
#define CBMRUTHERFORDGEOPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for FairRutherfordGeoPar::Class, etc

class TObjArray;
class FairParamList;

class FairRutherfordGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    FairRutherfordGeoPar(const char* name="FairRutherfordGeoPar",
                         const char* title="FairRutherford Geometry Parameters",
                         const char* context="TestDefaultContext");
    ~FairRutherfordGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    FairRutherfordGeoPar(const FairRutherfordGeoPar&);
    FairRutherfordGeoPar& operator=(const FairRutherfordGeoPar&);

    ClassDef(FairRutherfordGeoPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef CBMRUTHERFORDPOINT_H
#define CBMRUTHERFORDPOINT_H 1

#include "FairMCPoint.h"                // for FairMCPoint

#include "Rtypes.h"                     // for Double_t, Double32_t, etc
#include "TVector3.h"                   // for TVector3

class FairRutherfordPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairRutherfordPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairRutherfordPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                        Double_t tof, Double_t length, Double_t eLoss,
                        Double_t radius, Double_t phi, Double_t theta);




    /** Destructor **/
    virtual ~FairRutherfordPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

  private:

    Double32_t fRadius, fPhi, fTheta;

    /** Copy constructor **/
    FairRutherfordPoint(const FairRutherfordPoint& point);
    FairRutherfordPoint operator=(const FairRutherfordPoint& point);

    ClassDef(FairRutherfordPoint,1)

};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairRutherford", payloadCode, "@",
"FairRutherfordContFact", payloadCode, "@",
"FairRutherfordGeo", payloadCode, "@",
"FairRutherfordGeoPar", payloadCode, "@",
"FairRutherfordPoint", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__FairRutherfordDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__FairRutherfordDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__FairRutherfordDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__FairRutherfordDict() {
  TriggerDictionaryInitialization_G__FairRutherfordDict_Impl();
}

// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIsimulationdITutorial1dIsrcdIG__Tutorial1Dict

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
#include "FairTutorialDet1.h"
#include "FairTutorialDet1ContFact.h"
#include "FairTutorialDet1Geo.h"
#include "FairTutorialDet1GeoPar.h"
#include "FairTutorialDet1Point.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairTutorialDet1ContFact(void *p = 0);
   static void *newArray_FairTutorialDet1ContFact(Long_t size, void *p);
   static void delete_FairTutorialDet1ContFact(void *p);
   static void deleteArray_FairTutorialDet1ContFact(void *p);
   static void destruct_FairTutorialDet1ContFact(void *p);
   static void streamer_FairTutorialDet1ContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet1ContFact*)
   {
      ::FairTutorialDet1ContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet1ContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet1ContFact", ::FairTutorialDet1ContFact::Class_Version(), "invalid", 130,
                  typeid(::FairTutorialDet1ContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet1ContFact::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet1ContFact) );
      instance.SetNew(&new_FairTutorialDet1ContFact);
      instance.SetNewArray(&newArray_FairTutorialDet1ContFact);
      instance.SetDelete(&delete_FairTutorialDet1ContFact);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet1ContFact);
      instance.SetDestructor(&destruct_FairTutorialDet1ContFact);
      instance.SetStreamerFunc(&streamer_FairTutorialDet1ContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet1ContFact*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet1ContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet1ContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet1Geo(void *p = 0);
   static void *newArray_FairTutorialDet1Geo(Long_t size, void *p);
   static void delete_FairTutorialDet1Geo(void *p);
   static void deleteArray_FairTutorialDet1Geo(void *p);
   static void destruct_FairTutorialDet1Geo(void *p);
   static void streamer_FairTutorialDet1Geo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet1Geo*)
   {
      ::FairTutorialDet1Geo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet1Geo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet1Geo", ::FairTutorialDet1Geo::Class_Version(), "invalid", 159,
                  typeid(::FairTutorialDet1Geo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet1Geo::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet1Geo) );
      instance.SetNew(&new_FairTutorialDet1Geo);
      instance.SetNewArray(&newArray_FairTutorialDet1Geo);
      instance.SetDelete(&delete_FairTutorialDet1Geo);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet1Geo);
      instance.SetDestructor(&destruct_FairTutorialDet1Geo);
      instance.SetStreamerFunc(&streamer_FairTutorialDet1Geo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet1Geo*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet1Geo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet1Geo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet1GeoPar(void *p = 0);
   static void *newArray_FairTutorialDet1GeoPar(Long_t size, void *p);
   static void delete_FairTutorialDet1GeoPar(void *p);
   static void deleteArray_FairTutorialDet1GeoPar(void *p);
   static void destruct_FairTutorialDet1GeoPar(void *p);
   static void streamer_FairTutorialDet1GeoPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet1GeoPar*)
   {
      ::FairTutorialDet1GeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet1GeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet1GeoPar", ::FairTutorialDet1GeoPar::Class_Version(), "invalid", 203,
                  typeid(::FairTutorialDet1GeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet1GeoPar::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet1GeoPar) );
      instance.SetNew(&new_FairTutorialDet1GeoPar);
      instance.SetNewArray(&newArray_FairTutorialDet1GeoPar);
      instance.SetDelete(&delete_FairTutorialDet1GeoPar);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet1GeoPar);
      instance.SetDestructor(&destruct_FairTutorialDet1GeoPar);
      instance.SetStreamerFunc(&streamer_FairTutorialDet1GeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet1GeoPar*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet1GeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet1GeoPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet1(void *p = 0);
   static void *newArray_FairTutorialDet1(Long_t size, void *p);
   static void delete_FairTutorialDet1(void *p);
   static void deleteArray_FairTutorialDet1(void *p);
   static void destruct_FairTutorialDet1(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet1*)
   {
      ::FairTutorialDet1 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet1 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet1", ::FairTutorialDet1::Class_Version(), "invalid", 26,
                  typeid(::FairTutorialDet1), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet1::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet1) );
      instance.SetNew(&new_FairTutorialDet1);
      instance.SetNewArray(&newArray_FairTutorialDet1);
      instance.SetDelete(&delete_FairTutorialDet1);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet1);
      instance.SetDestructor(&destruct_FairTutorialDet1);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet1*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet1*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet1*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet1Point(void *p = 0);
   static void *newArray_FairTutorialDet1Point(Long_t size, void *p);
   static void delete_FairTutorialDet1Point(void *p);
   static void deleteArray_FairTutorialDet1Point(void *p);
   static void destruct_FairTutorialDet1Point(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet1Point*)
   {
      ::FairTutorialDet1Point *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet1Point >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet1Point", ::FairTutorialDet1Point::Class_Version(), "invalid", 247,
                  typeid(::FairTutorialDet1Point), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet1Point::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet1Point) );
      instance.SetNew(&new_FairTutorialDet1Point);
      instance.SetNewArray(&newArray_FairTutorialDet1Point);
      instance.SetDelete(&delete_FairTutorialDet1Point);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet1Point);
      instance.SetDestructor(&destruct_FairTutorialDet1Point);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet1Point*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet1Point*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet1Point*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet1ContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet1ContFact::Class_Name()
{
   return "FairTutorialDet1ContFact";
}

//______________________________________________________________________________
const char *FairTutorialDet1ContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1ContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet1ContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1ContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet1ContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1ContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet1ContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1ContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet1Geo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet1Geo::Class_Name()
{
   return "FairTutorialDet1Geo";
}

//______________________________________________________________________________
const char *FairTutorialDet1Geo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1Geo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet1Geo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1Geo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet1Geo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1Geo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet1Geo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1Geo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet1GeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet1GeoPar::Class_Name()
{
   return "FairTutorialDet1GeoPar";
}

//______________________________________________________________________________
const char *FairTutorialDet1GeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1GeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet1GeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1GeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet1GeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1GeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet1GeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1GeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet1::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet1::Class_Name()
{
   return "FairTutorialDet1";
}

//______________________________________________________________________________
const char *FairTutorialDet1::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet1::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet1::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet1::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet1Point::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet1Point::Class_Name()
{
   return "FairTutorialDet1Point";
}

//______________________________________________________________________________
const char *FairTutorialDet1Point::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1Point*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet1Point::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1Point*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet1Point::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1Point*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet1Point::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet1Point*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairTutorialDet1ContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet1ContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet1ContFact(void *p) {
      return  p ? new(p) ::FairTutorialDet1ContFact : new ::FairTutorialDet1ContFact;
   }
   static void *newArray_FairTutorialDet1ContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet1ContFact[nElements] : new ::FairTutorialDet1ContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet1ContFact(void *p) {
      delete ((::FairTutorialDet1ContFact*)p);
   }
   static void deleteArray_FairTutorialDet1ContFact(void *p) {
      delete [] ((::FairTutorialDet1ContFact*)p);
   }
   static void destruct_FairTutorialDet1ContFact(void *p) {
      typedef ::FairTutorialDet1ContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet1ContFact(TBuffer &buf, void *obj) {
      ((::FairTutorialDet1ContFact*)obj)->::FairTutorialDet1ContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet1ContFact

//______________________________________________________________________________
void FairTutorialDet1Geo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet1Geo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoSet::Streamer(R__b);
      R__b.ReadStaticArray((char*)modName);
      R__b.ReadStaticArray((char*)eleName);
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet1Geo::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet1Geo::IsA(), kTRUE);
      FairGeoSet::Streamer(R__b);
      R__b.WriteArray(modName, 20);
      R__b.WriteArray(eleName, 20);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet1Geo(void *p) {
      return  p ? new(p) ::FairTutorialDet1Geo : new ::FairTutorialDet1Geo;
   }
   static void *newArray_FairTutorialDet1Geo(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet1Geo[nElements] : new ::FairTutorialDet1Geo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet1Geo(void *p) {
      delete ((::FairTutorialDet1Geo*)p);
   }
   static void deleteArray_FairTutorialDet1Geo(void *p) {
      delete [] ((::FairTutorialDet1Geo*)p);
   }
   static void destruct_FairTutorialDet1Geo(void *p) {
      typedef ::FairTutorialDet1Geo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet1Geo(TBuffer &buf, void *obj) {
      ((::FairTutorialDet1Geo*)obj)->::FairTutorialDet1Geo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet1Geo

//______________________________________________________________________________
void FairTutorialDet1GeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet1GeoPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet1GeoPar::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet1GeoPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet1GeoPar(void *p) {
      return  p ? new(p) ::FairTutorialDet1GeoPar : new ::FairTutorialDet1GeoPar;
   }
   static void *newArray_FairTutorialDet1GeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet1GeoPar[nElements] : new ::FairTutorialDet1GeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet1GeoPar(void *p) {
      delete ((::FairTutorialDet1GeoPar*)p);
   }
   static void deleteArray_FairTutorialDet1GeoPar(void *p) {
      delete [] ((::FairTutorialDet1GeoPar*)p);
   }
   static void destruct_FairTutorialDet1GeoPar(void *p) {
      typedef ::FairTutorialDet1GeoPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet1GeoPar(TBuffer &buf, void *obj) {
      ((::FairTutorialDet1GeoPar*)obj)->::FairTutorialDet1GeoPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet1GeoPar

//______________________________________________________________________________
void FairTutorialDet1::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet1.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet1::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet1::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet1(void *p) {
      return  p ? new(p) ::FairTutorialDet1 : new ::FairTutorialDet1;
   }
   static void *newArray_FairTutorialDet1(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet1[nElements] : new ::FairTutorialDet1[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet1(void *p) {
      delete ((::FairTutorialDet1*)p);
   }
   static void deleteArray_FairTutorialDet1(void *p) {
      delete [] ((::FairTutorialDet1*)p);
   }
   static void destruct_FairTutorialDet1(void *p) {
      typedef ::FairTutorialDet1 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet1

//______________________________________________________________________________
void FairTutorialDet1Point::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet1Point.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet1Point::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet1Point::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet1Point(void *p) {
      return  p ? new(p) ::FairTutorialDet1Point : new ::FairTutorialDet1Point;
   }
   static void *newArray_FairTutorialDet1Point(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet1Point[nElements] : new ::FairTutorialDet1Point[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet1Point(void *p) {
      delete ((::FairTutorialDet1Point*)p);
   }
   static void deleteArray_FairTutorialDet1Point(void *p) {
      delete [] ((::FairTutorialDet1Point*)p);
   }
   static void destruct_FairTutorialDet1Point(void *p) {
      typedef ::FairTutorialDet1Point current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet1Point

namespace {
  void TriggerDictionaryInitialization_G__Tutorial1Dict_Impl() {
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
"/Users/turany/development/FairRoot/examples/simulation/Tutorial1/src",
"/Users/turany/development/FairRoot/examples/common/mcstack",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/simulation/Tutorial1/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__Tutorial1Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Factory for all MyDet parameter containers)ATTRDUMP"))) FairTutorialDet1ContFact;
class FairTutorialDet1Geo;
class FairTutorialDet1GeoPar;
class FairTutorialDet1;
class FairTutorialDet1Point;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__Tutorial1Dict dictionary payload"

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
#ifndef FAIRTUTORIALDET1_H
#define FAIRTUTORIALDET1_H

#include "FairDetector.h"               // for FairDetector

#include "Rtypes.h"                     // for Int_t, Double32_t, Double_t, etc
#include "TLorentzVector.h"             // for TLorentzVector
#include "TVector3.h"                   // for TVector3

class FairTutorialDet1Point;
class FairVolume;
class TClonesArray;

class FairTutorialDet1: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    FairTutorialDet1(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairTutorialDet1();

    /**       destructor     */
    virtual ~FairTutorialDet1();

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
     *       of type FairTutorialDet1Point to the clones array
    */
    FairTutorialDet1Point* AddHit(Int_t trackID, Int_t detID,
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

    TClonesArray*  fFairTutorialDet1PointCollection;

    FairTutorialDet1(const FairTutorialDet1&);
    FairTutorialDet1& operator=(const FairTutorialDet1&);

    ClassDef(FairTutorialDet1,1)
};

#endif //FAIRTUTORIALDET_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1CONTFACT_H
#define FAIRTUTORIALDET1CONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"

class FairParSet;

class FairTutorialDet1ContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairTutorialDet1ContFact();
    ~FairTutorialDet1ContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairTutorialDet1ContFact,0) // Factory for all MyDet parameter containers
};

#endif  /* !FAIRTUTORIALDETCONTFACT_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1GEO_H
#define FAIRTUTORIALDET1GEO_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Rtypes.h"                     // for Int_t, etc

#include "TString.h"                    // for TString

class  FairTutorialDet1Geo : public FairGeoSet
{

  protected:
    char modName[20];  // name of module
    char eleName[20];  // substring for elements in module
  public:
    FairTutorialDet1Geo();
    ~FairTutorialDet1Geo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(FairTutorialDet1Geo,1)
};

inline Int_t FairTutorialDet1Geo::getModNumInMod(const TString& name)
{
  /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   tutdet ?? has to be 6.
  */
  return static_cast<Int_t>((name[6]-'0')-1); //
}

#endif  /*  FAIRTUTORIALDETGEO_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1GEOPAR_H
#define FAIRTUTORIALDET1GEOPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef

class TObjArray;
class FairParamList;

class FairTutorialDet1GeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    FairTutorialDet1GeoPar(const char* name="FairTutorialDet1GeoPar",
                           const char* title="FairTutorialDet1 Geometry Parameters",
                           const char* context="TestDefaultContext");
    ~FairTutorialDet1GeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    FairTutorialDet1GeoPar(const FairTutorialDet1GeoPar&);
    FairTutorialDet1GeoPar& operator=(const FairTutorialDet1GeoPar&);

    ClassDef(FairTutorialDet1GeoPar,1)
};

#endif /* FAIRTUTORIALDETGEOPAR_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET1POINT_H
#define FAIRTUTORIALDET1POINT_H 1

#include "FairMCPoint.h"                // for FairMCPoint

#include "Rtypes.h"                     // for Double_t, etc
#include "TVector3.h"                   // for TVector3

class FairTutorialDet1Point : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairTutorialDet1Point();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTutorialDet1Point(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                          Double_t tof, Double_t length, Double_t eLoss);


    /** Copy constructor **/
    //    FairTutorialDet1Point(const FairTutorialDet1Point& point) { *this = point; };


    /** Destructor **/
    virtual ~FairTutorialDet1Point();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;


    ClassDef(FairTutorialDet1Point,1)

};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairTutorialDet1", payloadCode, "@",
"FairTutorialDet1ContFact", payloadCode, "@",
"FairTutorialDet1Geo", payloadCode, "@",
"FairTutorialDet1GeoPar", payloadCode, "@",
"FairTutorialDet1Point", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__Tutorial1Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__Tutorial1Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__Tutorial1Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__Tutorial1Dict() {
  TriggerDictionaryInitialization_G__Tutorial1Dict_Impl();
}

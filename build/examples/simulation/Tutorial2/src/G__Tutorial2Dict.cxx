// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIsimulationdITutorial2dIsrcdIG__Tutorial2Dict

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
#include "FairTutorialDet2.h"
#include "FairTutorialDet2ContFact.h"
#include "FairTutorialDet2Geo.h"
#include "FairTutorialDet2GeoPar.h"
#include "FairTutorialDet2Point.h"
#include "FairTutorialDet2DigiPar.h"
#include "FairTutorialDet2Digitizer.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairTutorialDet2ContFact(void *p = 0);
   static void *newArray_FairTutorialDet2ContFact(Long_t size, void *p);
   static void delete_FairTutorialDet2ContFact(void *p);
   static void deleteArray_FairTutorialDet2ContFact(void *p);
   static void destruct_FairTutorialDet2ContFact(void *p);
   static void streamer_FairTutorialDet2ContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet2ContFact*)
   {
      ::FairTutorialDet2ContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet2ContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet2ContFact", ::FairTutorialDet2ContFact::Class_Version(), "invalid", 127,
                  typeid(::FairTutorialDet2ContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet2ContFact::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet2ContFact) );
      instance.SetNew(&new_FairTutorialDet2ContFact);
      instance.SetNewArray(&newArray_FairTutorialDet2ContFact);
      instance.SetDelete(&delete_FairTutorialDet2ContFact);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet2ContFact);
      instance.SetDestructor(&destruct_FairTutorialDet2ContFact);
      instance.SetStreamerFunc(&streamer_FairTutorialDet2ContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet2ContFact*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet2ContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet2ContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet2Geo(void *p = 0);
   static void *newArray_FairTutorialDet2Geo(Long_t size, void *p);
   static void delete_FairTutorialDet2Geo(void *p);
   static void deleteArray_FairTutorialDet2Geo(void *p);
   static void destruct_FairTutorialDet2Geo(void *p);
   static void streamer_FairTutorialDet2Geo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet2Geo*)
   {
      ::FairTutorialDet2Geo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet2Geo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet2Geo", ::FairTutorialDet2Geo::Class_Version(), "invalid", 152,
                  typeid(::FairTutorialDet2Geo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet2Geo::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet2Geo) );
      instance.SetNew(&new_FairTutorialDet2Geo);
      instance.SetNewArray(&newArray_FairTutorialDet2Geo);
      instance.SetDelete(&delete_FairTutorialDet2Geo);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet2Geo);
      instance.SetDestructor(&destruct_FairTutorialDet2Geo);
      instance.SetStreamerFunc(&streamer_FairTutorialDet2Geo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet2Geo*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet2Geo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet2Geo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet2GeoPar(void *p = 0);
   static void *newArray_FairTutorialDet2GeoPar(Long_t size, void *p);
   static void delete_FairTutorialDet2GeoPar(void *p);
   static void deleteArray_FairTutorialDet2GeoPar(void *p);
   static void destruct_FairTutorialDet2GeoPar(void *p);
   static void streamer_FairTutorialDet2GeoPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet2GeoPar*)
   {
      ::FairTutorialDet2GeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet2GeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet2GeoPar", ::FairTutorialDet2GeoPar::Class_Version(), "invalid", 194,
                  typeid(::FairTutorialDet2GeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet2GeoPar::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet2GeoPar) );
      instance.SetNew(&new_FairTutorialDet2GeoPar);
      instance.SetNewArray(&newArray_FairTutorialDet2GeoPar);
      instance.SetDelete(&delete_FairTutorialDet2GeoPar);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet2GeoPar);
      instance.SetDestructor(&destruct_FairTutorialDet2GeoPar);
      instance.SetStreamerFunc(&streamer_FairTutorialDet2GeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet2GeoPar*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet2GeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet2GeoPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet2(void *p = 0);
   static void *newArray_FairTutorialDet2(Long_t size, void *p);
   static void delete_FairTutorialDet2(void *p);
   static void deleteArray_FairTutorialDet2(void *p);
   static void destruct_FairTutorialDet2(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet2*)
   {
      ::FairTutorialDet2 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet2 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet2", ::FairTutorialDet2::Class_Version(), "invalid", 25,
                  typeid(::FairTutorialDet2), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet2::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet2) );
      instance.SetNew(&new_FairTutorialDet2);
      instance.SetNewArray(&newArray_FairTutorialDet2);
      instance.SetDelete(&delete_FairTutorialDet2);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet2);
      instance.SetDestructor(&destruct_FairTutorialDet2);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet2*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet2*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet2*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet2Point(void *p = 0);
   static void *newArray_FairTutorialDet2Point(Long_t size, void *p);
   static void delete_FairTutorialDet2Point(void *p);
   static void deleteArray_FairTutorialDet2Point(void *p);
   static void destruct_FairTutorialDet2Point(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet2Point*)
   {
      ::FairTutorialDet2Point *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet2Point >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet2Point", ::FairTutorialDet2Point::Class_Version(), "invalid", 239,
                  typeid(::FairTutorialDet2Point), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet2Point::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet2Point) );
      instance.SetNew(&new_FairTutorialDet2Point);
      instance.SetNewArray(&newArray_FairTutorialDet2Point);
      instance.SetDelete(&delete_FairTutorialDet2Point);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet2Point);
      instance.SetDestructor(&destruct_FairTutorialDet2Point);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet2Point*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet2Point*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet2Point*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet2DigiPar(void *p = 0);
   static void *newArray_FairTutorialDet2DigiPar(Long_t size, void *p);
   static void delete_FairTutorialDet2DigiPar(void *p);
   static void deleteArray_FairTutorialDet2DigiPar(void *p);
   static void destruct_FairTutorialDet2DigiPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet2DigiPar*)
   {
      ::FairTutorialDet2DigiPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet2DigiPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet2DigiPar", ::FairTutorialDet2DigiPar::Class_Version(), "invalid", 305,
                  typeid(::FairTutorialDet2DigiPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet2DigiPar::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet2DigiPar) );
      instance.SetNew(&new_FairTutorialDet2DigiPar);
      instance.SetNewArray(&newArray_FairTutorialDet2DigiPar);
      instance.SetDelete(&delete_FairTutorialDet2DigiPar);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet2DigiPar);
      instance.SetDestructor(&destruct_FairTutorialDet2DigiPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet2DigiPar*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet2DigiPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet2DigiPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet2Digitizer(void *p = 0);
   static void *newArray_FairTutorialDet2Digitizer(Long_t size, void *p);
   static void delete_FairTutorialDet2Digitizer(void *p);
   static void deleteArray_FairTutorialDet2Digitizer(void *p);
   static void destruct_FairTutorialDet2Digitizer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet2Digitizer*)
   {
      ::FairTutorialDet2Digitizer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet2Digitizer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet2Digitizer", ::FairTutorialDet2Digitizer::Class_Version(), "invalid", 385,
                  typeid(::FairTutorialDet2Digitizer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet2Digitizer::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet2Digitizer) );
      instance.SetNew(&new_FairTutorialDet2Digitizer);
      instance.SetNewArray(&newArray_FairTutorialDet2Digitizer);
      instance.SetDelete(&delete_FairTutorialDet2Digitizer);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet2Digitizer);
      instance.SetDestructor(&destruct_FairTutorialDet2Digitizer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet2Digitizer*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet2Digitizer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet2Digitizer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet2ContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet2ContFact::Class_Name()
{
   return "FairTutorialDet2ContFact";
}

//______________________________________________________________________________
const char *FairTutorialDet2ContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2ContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet2ContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2ContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet2ContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2ContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet2ContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2ContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet2Geo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet2Geo::Class_Name()
{
   return "FairTutorialDet2Geo";
}

//______________________________________________________________________________
const char *FairTutorialDet2Geo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Geo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet2Geo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Geo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet2Geo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Geo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet2Geo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Geo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet2GeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet2GeoPar::Class_Name()
{
   return "FairTutorialDet2GeoPar";
}

//______________________________________________________________________________
const char *FairTutorialDet2GeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2GeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet2GeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2GeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet2GeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2GeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet2GeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2GeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet2::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet2::Class_Name()
{
   return "FairTutorialDet2";
}

//______________________________________________________________________________
const char *FairTutorialDet2::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet2::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet2::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet2::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet2Point::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet2Point::Class_Name()
{
   return "FairTutorialDet2Point";
}

//______________________________________________________________________________
const char *FairTutorialDet2Point::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Point*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet2Point::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Point*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet2Point::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Point*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet2Point::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Point*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet2DigiPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet2DigiPar::Class_Name()
{
   return "FairTutorialDet2DigiPar";
}

//______________________________________________________________________________
const char *FairTutorialDet2DigiPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2DigiPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet2DigiPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2DigiPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet2DigiPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2DigiPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet2DigiPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2DigiPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet2Digitizer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet2Digitizer::Class_Name()
{
   return "FairTutorialDet2Digitizer";
}

//______________________________________________________________________________
const char *FairTutorialDet2Digitizer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Digitizer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet2Digitizer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Digitizer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet2Digitizer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Digitizer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet2Digitizer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet2Digitizer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairTutorialDet2ContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet2ContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet2ContFact(void *p) {
      return  p ? new(p) ::FairTutorialDet2ContFact : new ::FairTutorialDet2ContFact;
   }
   static void *newArray_FairTutorialDet2ContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet2ContFact[nElements] : new ::FairTutorialDet2ContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet2ContFact(void *p) {
      delete ((::FairTutorialDet2ContFact*)p);
   }
   static void deleteArray_FairTutorialDet2ContFact(void *p) {
      delete [] ((::FairTutorialDet2ContFact*)p);
   }
   static void destruct_FairTutorialDet2ContFact(void *p) {
      typedef ::FairTutorialDet2ContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet2ContFact(TBuffer &buf, void *obj) {
      ((::FairTutorialDet2ContFact*)obj)->::FairTutorialDet2ContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet2ContFact

//______________________________________________________________________________
void FairTutorialDet2Geo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet2Geo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoSet::Streamer(R__b);
      R__b.ReadStaticArray((char*)modName);
      R__b.ReadStaticArray((char*)eleName);
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet2Geo::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet2Geo::IsA(), kTRUE);
      FairGeoSet::Streamer(R__b);
      R__b.WriteArray(modName, 20);
      R__b.WriteArray(eleName, 20);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet2Geo(void *p) {
      return  p ? new(p) ::FairTutorialDet2Geo : new ::FairTutorialDet2Geo;
   }
   static void *newArray_FairTutorialDet2Geo(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet2Geo[nElements] : new ::FairTutorialDet2Geo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet2Geo(void *p) {
      delete ((::FairTutorialDet2Geo*)p);
   }
   static void deleteArray_FairTutorialDet2Geo(void *p) {
      delete [] ((::FairTutorialDet2Geo*)p);
   }
   static void destruct_FairTutorialDet2Geo(void *p) {
      typedef ::FairTutorialDet2Geo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet2Geo(TBuffer &buf, void *obj) {
      ((::FairTutorialDet2Geo*)obj)->::FairTutorialDet2Geo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet2Geo

//______________________________________________________________________________
void FairTutorialDet2GeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet2GeoPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet2GeoPar::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet2GeoPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet2GeoPar(void *p) {
      return  p ? new(p) ::FairTutorialDet2GeoPar : new ::FairTutorialDet2GeoPar;
   }
   static void *newArray_FairTutorialDet2GeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet2GeoPar[nElements] : new ::FairTutorialDet2GeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet2GeoPar(void *p) {
      delete ((::FairTutorialDet2GeoPar*)p);
   }
   static void deleteArray_FairTutorialDet2GeoPar(void *p) {
      delete [] ((::FairTutorialDet2GeoPar*)p);
   }
   static void destruct_FairTutorialDet2GeoPar(void *p) {
      typedef ::FairTutorialDet2GeoPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet2GeoPar(TBuffer &buf, void *obj) {
      ((::FairTutorialDet2GeoPar*)obj)->::FairTutorialDet2GeoPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet2GeoPar

//______________________________________________________________________________
void FairTutorialDet2::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet2.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet2::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet2::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet2(void *p) {
      return  p ? new(p) ::FairTutorialDet2 : new ::FairTutorialDet2;
   }
   static void *newArray_FairTutorialDet2(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet2[nElements] : new ::FairTutorialDet2[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet2(void *p) {
      delete ((::FairTutorialDet2*)p);
   }
   static void deleteArray_FairTutorialDet2(void *p) {
      delete [] ((::FairTutorialDet2*)p);
   }
   static void destruct_FairTutorialDet2(void *p) {
      typedef ::FairTutorialDet2 current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet2

//______________________________________________________________________________
void FairTutorialDet2Point::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet2Point.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet2Point::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet2Point::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet2Point(void *p) {
      return  p ? new(p) ::FairTutorialDet2Point : new ::FairTutorialDet2Point;
   }
   static void *newArray_FairTutorialDet2Point(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet2Point[nElements] : new ::FairTutorialDet2Point[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet2Point(void *p) {
      delete ((::FairTutorialDet2Point*)p);
   }
   static void deleteArray_FairTutorialDet2Point(void *p) {
      delete [] ((::FairTutorialDet2Point*)p);
   }
   static void destruct_FairTutorialDet2Point(void *p) {
      typedef ::FairTutorialDet2Point current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet2Point

//______________________________________________________________________________
void FairTutorialDet2DigiPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet2DigiPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet2DigiPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet2DigiPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet2DigiPar(void *p) {
      return  p ? new(p) ::FairTutorialDet2DigiPar : new ::FairTutorialDet2DigiPar;
   }
   static void *newArray_FairTutorialDet2DigiPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet2DigiPar[nElements] : new ::FairTutorialDet2DigiPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet2DigiPar(void *p) {
      delete ((::FairTutorialDet2DigiPar*)p);
   }
   static void deleteArray_FairTutorialDet2DigiPar(void *p) {
      delete [] ((::FairTutorialDet2DigiPar*)p);
   }
   static void destruct_FairTutorialDet2DigiPar(void *p) {
      typedef ::FairTutorialDet2DigiPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet2DigiPar

//______________________________________________________________________________
void FairTutorialDet2Digitizer::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet2Digitizer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet2Digitizer::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet2Digitizer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet2Digitizer(void *p) {
      return  p ? new(p) ::FairTutorialDet2Digitizer : new ::FairTutorialDet2Digitizer;
   }
   static void *newArray_FairTutorialDet2Digitizer(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet2Digitizer[nElements] : new ::FairTutorialDet2Digitizer[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet2Digitizer(void *p) {
      delete ((::FairTutorialDet2Digitizer*)p);
   }
   static void deleteArray_FairTutorialDet2Digitizer(void *p) {
      delete [] ((::FairTutorialDet2Digitizer*)p);
   }
   static void destruct_FairTutorialDet2Digitizer(void *p) {
      typedef ::FairTutorialDet2Digitizer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet2Digitizer

namespace {
  void TriggerDictionaryInitialization_G__Tutorial2Dict_Impl() {
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
"/Users/turany/development/FairRoot/examples/simulation/Tutorial2/src",
"/Users/turany/development/FairRoot/examples/common/mcstack",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/simulation/Tutorial2/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__Tutorial2Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Factory for all MyDet parameter containers)ATTRDUMP"))) FairTutorialDet2ContFact;
class FairTutorialDet2Geo;
class FairTutorialDet2GeoPar;
class FairTutorialDet2;
class FairTutorialDet2Point;
class FairTutorialDet2DigiPar;
class FairTutorialDet2Digitizer;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__Tutorial2Dict dictionary payload"

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
#ifndef FAIRTUTORIALDET2_H
#define FAIRTUTORIALDET2_H

#include "FairDetector.h"

#include "TVector3.h"
#include "TLorentzVector.h"

class FairTutorialDet2Point;
class FairVolume;
class TClonesArray;

class FairTutorialDet2: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    FairTutorialDet2(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairTutorialDet2();

    /**       destructor     */
    virtual ~FairTutorialDet2();

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
     *       of type FairTutorialDet2Point to the clones array
    */
    FairTutorialDet2Point* AddHit(Int_t trackID, Int_t detID,
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

    TClonesArray*  fFairTutorialDet2PointCollection;

    FairTutorialDet2(const FairTutorialDet2&);
    FairTutorialDet2& operator=(const FairTutorialDet2&);

    ClassDef(FairTutorialDet2,1)
};

#endif //FAIRTUTORIALDET_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2CONTFACT_H
#define FAIRTUTORIALDET2CONTFACT_H

#include "FairContFact.h"

class FairContainer;

class FairTutorialDet2ContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairTutorialDet2ContFact();
    ~FairTutorialDet2ContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairTutorialDet2ContFact,0) // Factory for all MyDet parameter containers
};

#endif  /* !FAIRTUTORIALDETCONTFACT_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2GEO_H
#define FAIRTUTORIALDET2GEO_H

#include "FairGeoSet.h"

class  FairTutorialDet2Geo : public FairGeoSet
{

  protected:
    char modName[20];  // name of module
    char eleName[20];  // substring for elements in module
  public:
    FairTutorialDet2Geo();
    ~FairTutorialDet2Geo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(FairTutorialDet2Geo,1)
};

inline Int_t FairTutorialDet2Geo::getModNumInMod(const TString& name)
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
#ifndef FAIRTUTORIALDET2GEOPAR_H
#define FAIRTUTORIALDET2GEOPAR_H

#include "FairParGenericSet.h"

class TObjArray;
class FairParamList;

class FairTutorialDet2GeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    FairTutorialDet2GeoPar(const char* name="FairTutorialDet2GeoPar",
                           const char* title="FairTutorialDet2 Geometry Parameters",
                           const char* context="TestDefaultContext");
    ~FairTutorialDet2GeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    FairTutorialDet2GeoPar(const FairTutorialDet2GeoPar&);
    FairTutorialDet2GeoPar& operator=(const FairTutorialDet2GeoPar&);

    ClassDef(FairTutorialDet2GeoPar,1)
};

#endif /* FAIRTUTORIALDETGEOPAR_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET2POINT_H
#define FAIRTUTORIALDET2POINT_H 1


#include "FairMCPoint.h"

#include "TObject.h"
#include "TVector3.h"

class FairTutorialDet2Point : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairTutorialDet2Point();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTutorialDet2Point(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                          Double_t tof, Double_t length, Double_t eLoss);


    /** Copy constructor **/
    //    FairTutorialDet2Point(const FairTutorialDet2Point& point) { *this = point; };


    /** Destructor **/
    virtual ~FairTutorialDet2Point();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;


    ClassDef(FairTutorialDet2Point,1)

};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairTutorialDetDigiPar header file              -----
// -----                 Created 15/05/08  by F. Uhlig                 -----
// -------------------------------------------------------------------------

#ifndef FAIRTUTORIALDET2DIGIPAR_H
#define FAIRTUTORIALDET2DIGIPAR_H


#include "FairParGenericSet.h"

#include "TObject.h"
#include "TObjArray.h"
#include "TArrayF.h"
#include "TArrayI.h"

class FairParIo;
class FairParamList;


class FairTutorialDet2DigiPar : public FairParGenericSet
{

  public:

    /** Standard constructor **/
    FairTutorialDet2DigiPar(const char* name    = "FairTutorialDet2DigiPar",
                            const char* title   = "Tutorial Det digi parameters",
                            const char* context = "Default");


    /** Destructor **/
    virtual ~FairTutorialDet2DigiPar();


    /** Initialisation from input device**/
    //virtual Bool_t init(FairParIo* input);


    /** Output to file **/
    //  virtual Int_t write(FairParIo* output);

    //  virtual void print();
    virtual void printparams();


    /** Reset all parameters **/
    virtual void clear();

    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

  private:

    TArrayF* ftutdetdigipar;  //
    TArrayI ftutdetdigiparsector; //
    Int_t ftutdetdigiparstation; //

    FairTutorialDet2DigiPar(const FairTutorialDet2DigiPar&);
    FairTutorialDet2DigiPar& operator=(const FairTutorialDet2DigiPar&);

    ClassDef(FairTutorialDet2DigiPar,1);


};


#endif





/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// --------------------------------------------------------------------------
// -----          Header for the FairTutorialDet2Digitizer               ------
// -----              Created 06.06.08 by F.Uhlig                      ------
// --------------------------------------------------------------------------



#ifndef FAIRTUTORIALDET2DIGITIZER_H
#define FAIRTUTORIALDET2DIGITIZER_H


#include "FairTask.h"

#include "TVector3.h"

class TClonesArray;

class FairTutorialDet2DigiPar;

class FairTutorialDet2Digitizer : public FairTask
{
  public:



    /** Default constructor **/
    FairTutorialDet2Digitizer();

    /** Standard constructor **/
    FairTutorialDet2Digitizer(const char* name, const char* title="FAIR Task");

    /** Destructor **/
    virtual ~FairTutorialDet2Digitizer();

    /** Initialisation **/
    virtual InitStatus ReInit();
    virtual InitStatus Init();
    virtual void SetParContainers();

    /** Executed task **/
    virtual void Exec(Option_t* option);

    /** Finish task **/
    virtual void Finish();

    /*
    void AddHit(TVector3& posHit, TVector3& posHitErr,
                Int_t TrackID, Int_t PlaneID, Int_t ref, Double_t ELoss,
                Double_t ELossTR, Double_t ELossdEdX);
    */
    void Register();

  private:

    TClonesArray* fTutorialDetPoints; //! Tutorial Det MC points
    //    TClonesArray *fDigiCollection; //! TRD hits
    //TClonesArray *fListStack;         //Tracks

    FairTutorialDet2DigiPar* fDigiPar;

    //    Double_t fDx;               //!
    //Double_t fDy;               //!
    //Int_t fNHits;

    FairTutorialDet2Digitizer(const FairTutorialDet2Digitizer&);
    FairTutorialDet2Digitizer& operator=(const FairTutorialDet2Digitizer&);

    ClassDef(FairTutorialDet2Digitizer,1)

};
#endif //FAIRTUTORIALDETDIGITIZER_H

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairTutorialDet2", payloadCode, "@",
"FairTutorialDet2ContFact", payloadCode, "@",
"FairTutorialDet2DigiPar", payloadCode, "@",
"FairTutorialDet2Digitizer", payloadCode, "@",
"FairTutorialDet2Geo", payloadCode, "@",
"FairTutorialDet2GeoPar", payloadCode, "@",
"FairTutorialDet2Point", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__Tutorial2Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__Tutorial2Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__Tutorial2Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__Tutorial2Dict() {
  TriggerDictionaryInitialization_G__Tutorial2Dict_Impl();
}

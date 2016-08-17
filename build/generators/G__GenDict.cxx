// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIgeneratorsdIG__GenDict

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
#include "FairAsciiGenerator.h"
#include "FairBoxGenerator.h"
#include "FairIonGenerator.h"
#include "FairParticleGenerator.h"
#include "FairShieldGenerator.h"
#include "FairUrqmdGenerator.h"
#include "FairEvtGenGenerator.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairAsciiGenerator(void *p = 0);
   static void *newArray_FairAsciiGenerator(Long_t size, void *p);
   static void delete_FairAsciiGenerator(void *p);
   static void deleteArray_FairAsciiGenerator(void *p);
   static void destruct_FairAsciiGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairAsciiGenerator*)
   {
      ::FairAsciiGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairAsciiGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairAsciiGenerator", ::FairAsciiGenerator::Class_Version(), "invalid", 46,
                  typeid(::FairAsciiGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairAsciiGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairAsciiGenerator) );
      instance.SetNew(&new_FairAsciiGenerator);
      instance.SetNewArray(&newArray_FairAsciiGenerator);
      instance.SetDelete(&delete_FairAsciiGenerator);
      instance.SetDeleteArray(&deleteArray_FairAsciiGenerator);
      instance.SetDestructor(&destruct_FairAsciiGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairAsciiGenerator*)
   {
      return GenerateInitInstanceLocal((::FairAsciiGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairAsciiGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairIonGenerator(void *p = 0);
   static void *newArray_FairIonGenerator(Long_t size, void *p);
   static void delete_FairIonGenerator(void *p);
   static void deleteArray_FairIonGenerator(void *p);
   static void destruct_FairIonGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairIonGenerator*)
   {
      ::FairIonGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairIonGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairIonGenerator", ::FairIonGenerator::Class_Version(), "invalid", 272,
                  typeid(::FairIonGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairIonGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairIonGenerator) );
      instance.SetNew(&new_FairIonGenerator);
      instance.SetNewArray(&newArray_FairIonGenerator);
      instance.SetDelete(&delete_FairIonGenerator);
      instance.SetDeleteArray(&deleteArray_FairIonGenerator);
      instance.SetDestructor(&destruct_FairIonGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairIonGenerator*)
   {
      return GenerateInitInstanceLocal((::FairIonGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairIonGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParticleGenerator(void *p = 0);
   static void *newArray_FairParticleGenerator(Long_t size, void *p);
   static void delete_FairParticleGenerator(void *p);
   static void deleteArray_FairParticleGenerator(void *p);
   static void destruct_FairParticleGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParticleGenerator*)
   {
      ::FairParticleGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParticleGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParticleGenerator", ::FairParticleGenerator::Class_Version(), "invalid", 381,
                  typeid(::FairParticleGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParticleGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairParticleGenerator) );
      instance.SetNew(&new_FairParticleGenerator);
      instance.SetNewArray(&newArray_FairParticleGenerator);
      instance.SetDelete(&delete_FairParticleGenerator);
      instance.SetDeleteArray(&deleteArray_FairParticleGenerator);
      instance.SetDestructor(&destruct_FairParticleGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParticleGenerator*)
   {
      return GenerateInitInstanceLocal((::FairParticleGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParticleGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairShieldGenerator(void *p = 0);
   static void *newArray_FairShieldGenerator(Long_t size, void *p);
   static void delete_FairShieldGenerator(void *p);
   static void deleteArray_FairShieldGenerator(void *p);
   static void destruct_FairShieldGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairShieldGenerator*)
   {
      ::FairShieldGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairShieldGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairShieldGenerator", ::FairShieldGenerator::Class_Version(), "invalid", 482,
                  typeid(::FairShieldGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairShieldGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairShieldGenerator) );
      instance.SetNew(&new_FairShieldGenerator);
      instance.SetNewArray(&newArray_FairShieldGenerator);
      instance.SetDelete(&delete_FairShieldGenerator);
      instance.SetDeleteArray(&deleteArray_FairShieldGenerator);
      instance.SetDestructor(&destruct_FairShieldGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairShieldGenerator*)
   {
      return GenerateInitInstanceLocal((::FairShieldGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairShieldGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairUrqmdGenerator(void *p = 0);
   static void *newArray_FairUrqmdGenerator(Long_t size, void *p);
   static void delete_FairUrqmdGenerator(void *p);
   static void deleteArray_FairUrqmdGenerator(void *p);
   static void destruct_FairUrqmdGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairUrqmdGenerator*)
   {
      ::FairUrqmdGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairUrqmdGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairUrqmdGenerator", ::FairUrqmdGenerator::Class_Version(), "invalid", 576,
                  typeid(::FairUrqmdGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairUrqmdGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairUrqmdGenerator) );
      instance.SetNew(&new_FairUrqmdGenerator);
      instance.SetNewArray(&newArray_FairUrqmdGenerator);
      instance.SetDelete(&delete_FairUrqmdGenerator);
      instance.SetDeleteArray(&deleteArray_FairUrqmdGenerator);
      instance.SetDestructor(&destruct_FairUrqmdGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairUrqmdGenerator*)
   {
      return GenerateInitInstanceLocal((::FairUrqmdGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairUrqmdGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairBoxGenerator(void *p = 0);
   static void *newArray_FairBoxGenerator(Long_t size, void *p);
   static void delete_FairBoxGenerator(void *p);
   static void deleteArray_FairBoxGenerator(void *p);
   static void destruct_FairBoxGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairBoxGenerator*)
   {
      ::FairBoxGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairBoxGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairBoxGenerator", ::FairBoxGenerator::Class_Version(), "invalid", 138,
                  typeid(::FairBoxGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairBoxGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairBoxGenerator) );
      instance.SetNew(&new_FairBoxGenerator);
      instance.SetNewArray(&newArray_FairBoxGenerator);
      instance.SetDelete(&delete_FairBoxGenerator);
      instance.SetDeleteArray(&deleteArray_FairBoxGenerator);
      instance.SetDestructor(&destruct_FairBoxGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairBoxGenerator*)
   {
      return GenerateInitInstanceLocal((::FairBoxGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairBoxGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairEvtGenGenerator(void *p = 0);
   static void *newArray_FairEvtGenGenerator(Long_t size, void *p);
   static void delete_FairEvtGenGenerator(void *p);
   static void deleteArray_FairEvtGenGenerator(void *p);
   static void destruct_FairEvtGenGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairEvtGenGenerator*)
   {
      ::FairEvtGenGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairEvtGenGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairEvtGenGenerator", ::FairEvtGenGenerator::Class_Version(), "invalid", 732,
                  typeid(::FairEvtGenGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairEvtGenGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairEvtGenGenerator) );
      instance.SetNew(&new_FairEvtGenGenerator);
      instance.SetNewArray(&newArray_FairEvtGenGenerator);
      instance.SetDelete(&delete_FairEvtGenGenerator);
      instance.SetDeleteArray(&deleteArray_FairEvtGenGenerator);
      instance.SetDestructor(&destruct_FairEvtGenGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairEvtGenGenerator*)
   {
      return GenerateInitInstanceLocal((::FairEvtGenGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairEvtGenGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairAsciiGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairAsciiGenerator::Class_Name()
{
   return "FairAsciiGenerator";
}

//______________________________________________________________________________
const char *FairAsciiGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairAsciiGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairAsciiGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairAsciiGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairAsciiGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairAsciiGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairAsciiGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairAsciiGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairIonGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairIonGenerator::Class_Name()
{
   return "FairIonGenerator";
}

//______________________________________________________________________________
const char *FairIonGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairIonGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairIonGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairIonGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairIonGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairIonGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairIonGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairIonGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParticleGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParticleGenerator::Class_Name()
{
   return "FairParticleGenerator";
}

//______________________________________________________________________________
const char *FairParticleGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParticleGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParticleGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParticleGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParticleGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParticleGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParticleGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParticleGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairShieldGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairShieldGenerator::Class_Name()
{
   return "FairShieldGenerator";
}

//______________________________________________________________________________
const char *FairShieldGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairShieldGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairShieldGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairShieldGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairShieldGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairShieldGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairShieldGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairShieldGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairUrqmdGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairUrqmdGenerator::Class_Name()
{
   return "FairUrqmdGenerator";
}

//______________________________________________________________________________
const char *FairUrqmdGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairUrqmdGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairUrqmdGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairUrqmdGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairUrqmdGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairUrqmdGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairUrqmdGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairUrqmdGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairBoxGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairBoxGenerator::Class_Name()
{
   return "FairBoxGenerator";
}

//______________________________________________________________________________
const char *FairBoxGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBoxGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairBoxGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBoxGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairBoxGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBoxGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairBoxGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBoxGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairEvtGenGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairEvtGenGenerator::Class_Name()
{
   return "FairEvtGenGenerator";
}

//______________________________________________________________________________
const char *FairEvtGenGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEvtGenGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairEvtGenGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEvtGenGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairEvtGenGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEvtGenGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairEvtGenGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEvtGenGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairAsciiGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairAsciiGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairAsciiGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairAsciiGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairAsciiGenerator(void *p) {
      return  p ? new(p) ::FairAsciiGenerator : new ::FairAsciiGenerator;
   }
   static void *newArray_FairAsciiGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairAsciiGenerator[nElements] : new ::FairAsciiGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairAsciiGenerator(void *p) {
      delete ((::FairAsciiGenerator*)p);
   }
   static void deleteArray_FairAsciiGenerator(void *p) {
      delete [] ((::FairAsciiGenerator*)p);
   }
   static void destruct_FairAsciiGenerator(void *p) {
      typedef ::FairAsciiGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairAsciiGenerator

//______________________________________________________________________________
void FairIonGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairIonGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairIonGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairIonGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairIonGenerator(void *p) {
      return  p ? new(p) ::FairIonGenerator : new ::FairIonGenerator;
   }
   static void *newArray_FairIonGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairIonGenerator[nElements] : new ::FairIonGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairIonGenerator(void *p) {
      delete ((::FairIonGenerator*)p);
   }
   static void deleteArray_FairIonGenerator(void *p) {
      delete [] ((::FairIonGenerator*)p);
   }
   static void destruct_FairIonGenerator(void *p) {
      typedef ::FairIonGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairIonGenerator

//______________________________________________________________________________
void FairParticleGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParticleGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParticleGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParticleGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParticleGenerator(void *p) {
      return  p ? new(p) ::FairParticleGenerator : new ::FairParticleGenerator;
   }
   static void *newArray_FairParticleGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairParticleGenerator[nElements] : new ::FairParticleGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParticleGenerator(void *p) {
      delete ((::FairParticleGenerator*)p);
   }
   static void deleteArray_FairParticleGenerator(void *p) {
      delete [] ((::FairParticleGenerator*)p);
   }
   static void destruct_FairParticleGenerator(void *p) {
      typedef ::FairParticleGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParticleGenerator

//______________________________________________________________________________
void FairShieldGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairShieldGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairShieldGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairShieldGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairShieldGenerator(void *p) {
      return  p ? new(p) ::FairShieldGenerator : new ::FairShieldGenerator;
   }
   static void *newArray_FairShieldGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairShieldGenerator[nElements] : new ::FairShieldGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairShieldGenerator(void *p) {
      delete ((::FairShieldGenerator*)p);
   }
   static void deleteArray_FairShieldGenerator(void *p) {
      delete [] ((::FairShieldGenerator*)p);
   }
   static void destruct_FairShieldGenerator(void *p) {
      typedef ::FairShieldGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairShieldGenerator

//______________________________________________________________________________
void FairUrqmdGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairUrqmdGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairUrqmdGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairUrqmdGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairUrqmdGenerator(void *p) {
      return  p ? new(p) ::FairUrqmdGenerator : new ::FairUrqmdGenerator;
   }
   static void *newArray_FairUrqmdGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairUrqmdGenerator[nElements] : new ::FairUrqmdGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairUrqmdGenerator(void *p) {
      delete ((::FairUrqmdGenerator*)p);
   }
   static void deleteArray_FairUrqmdGenerator(void *p) {
      delete [] ((::FairUrqmdGenerator*)p);
   }
   static void destruct_FairUrqmdGenerator(void *p) {
      typedef ::FairUrqmdGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairUrqmdGenerator

//______________________________________________________________________________
void FairBoxGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairBoxGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairBoxGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairBoxGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairBoxGenerator(void *p) {
      return  p ? new(p) ::FairBoxGenerator : new ::FairBoxGenerator;
   }
   static void *newArray_FairBoxGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairBoxGenerator[nElements] : new ::FairBoxGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairBoxGenerator(void *p) {
      delete ((::FairBoxGenerator*)p);
   }
   static void deleteArray_FairBoxGenerator(void *p) {
      delete [] ((::FairBoxGenerator*)p);
   }
   static void destruct_FairBoxGenerator(void *p) {
      typedef ::FairBoxGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairBoxGenerator

//______________________________________________________________________________
void FairEvtGenGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairEvtGenGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairEvtGenGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairEvtGenGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairEvtGenGenerator(void *p) {
      return  p ? new(p) ::FairEvtGenGenerator : new ::FairEvtGenGenerator;
   }
   static void *newArray_FairEvtGenGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairEvtGenGenerator[nElements] : new ::FairEvtGenGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairEvtGenGenerator(void *p) {
      delete ((::FairEvtGenGenerator*)p);
   }
   static void deleteArray_FairEvtGenGenerator(void *p) {
      delete [] ((::FairEvtGenGenerator*)p);
   }
   static void destruct_FairEvtGenGenerator(void *p) {
      typedef ::FairEvtGenGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairEvtGenGenerator

namespace {
  void TriggerDictionaryInitialization_G__GenDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/Users/turany/development/FairRoot/fairtools",
"/Users/turany/development/FairRoot/geobase",
"/Users/turany/development/FairRoot/field",
"/Users/turany/development/FairRoot/base",
"/Users/turany/development/FairRoot/base/steer",
"/Users/turany/development/FairRoot/base/event",
"/Users/turany/development/FairRoot/base/field",
"/Users/turany/development/FairRoot/base/sim",
"/Users/turany/development/FairRoot/generators",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/generators/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__GenDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairAsciiGenerator;
class FairIonGenerator;
class FairParticleGenerator;
class FairShieldGenerator;
class FairUrqmdGenerator;
class FairBoxGenerator;
class FairEvtGenGenerator;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__GenDict dictionary payload"

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
// -------------------------------------------------------------------------
// -----                FairAsciiGenerator header file                  -----
// -----          Created 09/06/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/**  FairAsciiGenerator.h
 *@author V.Friese  <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 *@author M.Al-Turany<M.Al-Turany@gsi.de>
 *
 The FairAsciiGenerator reads an Ascii input file. The file must contain
 for each event a header line of the format  NTRACKS  IEV  VX VY VZ,
 where NTRACKS is the number of tracks in the event, IEV the event number,
 and VX, VY, VZ the event vertex coordinates in cm. The header line is
 followed by NTRACKS lines of the format G3PID, PX, PY, PZ, where
 G3PID is the GEANT3 particle code, and PX, PY, PZ the cartesian
 momentum coordinates in GeV.
 Derived from FairGenerator.
**/


#ifndef FAIR_ASCIIGENERATOR_H
#define FAIR_ASCIIGENERATOR_H

#include "FairGenerator.h"              // for FairGenerator

#include "Riosfwd.h"                    // for ifstream
#include "Rtypes.h"                     // for FairAsciiGenerator::Class, etc

#include <fstream>                      // for ifstream

class FairPrimaryGenerator;

class FairAsciiGenerator : public FairGenerator
{

  public:

    /** Default constructor without arguments should not be used. **/
    FairAsciiGenerator();


    /** Standard constructor.
     ** @param fileName The input file name
     **/
    FairAsciiGenerator(const char* fileName);


    /** Destructor. **/
    virtual ~FairAsciiGenerator();


    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);



  private:

    std::ifstream* fInputFile;               //! Input file stream
    const Char_t* fFileName;            //! Input file Name


    /** Private method CloseInput. Just for convenience. Closes the
     ** input file properly. Called from destructor and from ReadEvent. **/
    void CloseInput();

    FairAsciiGenerator(const FairAsciiGenerator&);
    FairAsciiGenerator& operator=(const FairAsciiGenerator&);

    /** PDG data base */

//  TDatabasePDG *fPDG; //!

    ClassDef(FairAsciiGenerator,1);

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
// -----                FairBoxGenerator header file                    -----
// -----          Created 09/09/04  by Yu.Kharlov                      -----
// -------------------------------------------------------------------------

/**  FairBoxGenerator.h
 *@author Yuri Kharlov <Yuri.Kharlov@cern.ch>
 *
 * The FairBoxGenerator generates particles within given range
 * over pt, phi, eta, y or theta a fixed multiplicity per event.
 * Derived from FairGenerator.
**/

/* $Id: FairBoxGenerator.h,v 1.3 2006/07/14 11:23:57 kharlov Exp $ */

/* History of cvs commits:
 *
 * $Log: FairBoxGenerator.h,v $
 * Revision 1.3  2006/07/14 11:23:57  kharlov
 * Add protection for simultaneously set ranges; split vertex and kinematics ranges
 *
 * Revision 1.2  2006/03/29 16:25:50  kharlov
 * New functionality added
 *
 */

#ifndef FAIR_BOXGENERATOR_H
#define FAIR_BOXGENERATOR_H

#include "FairGenerator.h"              // for FairGenerator

#include "Rtypes.h"                     // for Double32_t, Bool_t, kTRUE, etc

class FairPrimaryGenerator;

class FairBoxGenerator : public FairGenerator
{
  public:

    /** Default constructor. **/
    FairBoxGenerator();

    /** Constructor with PDG-ID, multiplicity
     **@param pdgid Particle type (PDG encoding)
     **@param mult  Multiplicity (default is 1)
     **/
    FairBoxGenerator(Int_t pdgid, Int_t mult=1);

    /** Destructor **/
    virtual ~FairBoxGenerator() {};

    /** Modifiers **/
    void SetPDGType      (Int_t pdg)  {fPDGType = pdg;  };

    void SetMultiplicity (Int_t mult) {fMult    = mult; };

    void SetPRange(Double32_t pmin=0   , Double32_t pmax=10)
    {fPMin=pmin; fPMax=pmax; fPRangeIsSet=kTRUE;}

    void SetPtRange      (Double32_t ptmin=0   , Double32_t ptmax=10)
    {fPtMin=ptmin; fPtMax=ptmax; fPtRangeIsSet=kTRUE;};

    void SetPhiRange     (Double32_t phimin=0  , Double32_t phimax=360)
    {fPhiMin=phimin; fPhiMax=phimax;};

    void SetEtaRange     (Double32_t etamin=-5 , Double32_t etamax=7)
    {fEtaMin=etamin; fEtaMax=etamax; fEtaRangeIsSet=kTRUE;};

    void SetYRange       (Double32_t ymin=-5   , Double32_t ymax=7)
    {fYMin=ymin; fYMax=ymax; fYRangeIsSet=kTRUE;};

    void SetThetaRange   (Double32_t thetamin=0, Double32_t thetamax=90)
    {fThetaMin=thetamin; fThetaMax=thetamax; fThetaRangeIsSet=kTRUE;};

    void SetCosTheta   ()
    {fCosThetaIsSet=kTRUE;};

    void SetXYZ   (Double32_t x=0, Double32_t y=0, Double32_t z=0) {
      fX=x;
      fY=y;
      fZ=z;
      fPointVtxIsSet=kTRUE;
    }

    void SetBoxXYZ (Double32_t x1=0, Double32_t y1=0, Double32_t x2=0, Double32_t y2=0, Double32_t z=0) {
      fX1=x1;
      fY1=y1;
      fX2=x2;
      fY2=y2;
      fZ=z;
      fBoxVtxIsSet=kTRUE;
    }

    void SetDebug(Bool_t debug=0) {fDebug = debug;}

    /** Initializer **/
    Bool_t Init();

    /** Creates an event with given type and multiplicity.
     **@param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

    /** Clone this object (used in MT mode only) */
    virtual FairGenerator* CloneGenerator() const;

  protected:
    /** Copy constructor. **/
    FairBoxGenerator(const FairBoxGenerator&);
    FairBoxGenerator& operator=(const FairBoxGenerator&);

  private:
    Int_t      fPDGType;             // Particle type (PDG encoding)
    Int_t      fMult;                // Multiplicity

    Double32_t fPDGMass;             // Particle mass [GeV]
    Double32_t fPtMin,  fPtMax;      // Transverse momentum range [GeV]
    Double32_t fPhiMin, fPhiMax;     // Azimuth angle range [degree]
    Double32_t fEtaMin, fEtaMax;     // Pseudorapidity range in lab system
    Double32_t fYMin,   fYMax;       // Rapidity range in lab system
    Double32_t fPMin,   fPMax;       // Momentum range in lab system
    Double32_t fThetaMin, fThetaMax; // Polar angle range in lab system [degree]
    Double32_t fX, fY, fZ;           // Point vertex coordinates [cm]
    Double32_t fX1, fY1, fX2, fY2;   // Box vertex coords (x1,y1)->(x2,y2)

    Bool_t     fEtaRangeIsSet;       // True if eta range is set
    Bool_t     fYRangeIsSet;         // True if rapidity range is set
    Bool_t     fThetaRangeIsSet;     // True if theta range is set
    Bool_t     fCosThetaIsSet;       // True if uniform distribution in
    //cos(theta) is set (default -> not set)
    Bool_t     fPtRangeIsSet;        // True if transverse momentum range is set
    Bool_t     fPRangeIsSet;         // True if abs.momentum range is set
    Bool_t     fPointVtxIsSet;       // True if point vertex is set
    Bool_t     fBoxVtxIsSet;         // True if box vertex is set
    Bool_t     fDebug;               // Debug switch

    ClassDef(FairBoxGenerator,3);

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
// -----                   FairIonGenerator header file                 -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/**
 * 24.10.07  implement constructor with ion name. M. Al-Turany
*/

#ifndef FAIRIONGENERATOR_H
#define FAIRIONGENERATOR_H

#include "FairGenerator.h"              // for FairGenerator

#include "Rtypes.h"                     // for Double_t, Int_t, etc

class FairIon;
class FairPrimaryGenerator;

class FairIonGenerator : public FairGenerator
{

  public:

    /** Default constructor **/
    FairIonGenerator();


    /** Constructor with ion name
      ** For the generation of ions with pre-defined FairIon
     ** By default, the  excitation energy is zero. This can be changed with the
     ** respective modifiers.
     **@param ionName  Ion name
     **@param mult      Number of ions per event
     **@param px,py,pz  Momentum components [GeV] per nucleon!
     **@param vx,vy,vz  Vertex coordinates [cm]
     **/
    FairIonGenerator(const Char_t* ionName, Int_t mult, Double_t px,
                     Double_t py, Double_t pz,  Double_t vx = 0,
                     Double_t vy = 0, Double_t vz = 0);


    /** Default constructor
     ** For the generation of ions with atomic number z and mass number a.
     ** By default, the mass equals a times the proton mass and the
     ** excitation energy is zero. This can be changed with the
     ** respective modifiers.
     **@param z         Atomic number
     **@param a         Atomic mass
     **@param q         Electric charge [e]
     **@param mult      Number of ions per event
     **@param px,py,pz  Momentum components [GeV] per nucleon!
     **@param vx,vy,vz  Vertex coordinates [cm]
     **/
    FairIonGenerator(Int_t z, Int_t a, Int_t q, Int_t mult, Double_t px,
                     Double_t py, Double_t pz,  Double_t vx = 0,
                     Double_t vy = 0, Double_t vz = 0);


    /** Destructor **/
    virtual ~FairIonGenerator();


    /** Modifiers **/
    void SetCharge(Int_t charge) {fQ=charge;}
    void SetExcitationEnergy(Double_t eExc);
    void SetMass(Double_t mass);


    /** Method ReadEvent
     ** Generates <mult> of the specified ions and hands hem to the
     ** FairPrimaryGenerator.
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);


  private:

    static Int_t fgNIon;     //! Number of the instance of this class
    Int_t    fMult;          // Multiplicity per event
    Double_t fPx, fPy, fPz;  // Momentum components [GeV] per nucleon
    Double_t fVx, fVy, fVz;  // Vertex coordinates [cm]
    FairIon*   fIon;          // Pointer to the FairIon to be generated
    Int_t    fQ;    // Electric charge [e]

    FairIonGenerator(const FairIonGenerator&);
    FairIonGenerator& operator=(const FairIonGenerator&);

    ClassDef(FairIonGenerator,1)

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
// -----                FairParticleGenerator header file               -----
// -----          Created 09/07/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/**  FairParticleGenerator.h
 *@author V.Friese  <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 *
 The FairParticleGenerator generates a single particle type with given
 momentum components, vertex and multiplicity per event.
 Derived from FairGenerator.
**/


#ifndef FAIR_PARTICLEGENERATOR_H
#define FAIR_PARTICLEGENERATOR_H

#include "FairGenerator.h"              // for FairGenerator

#include "Rtypes.h"                     // for Double32_t, Int_t, etc

class FairPrimaryGenerator;

class FairParticleGenerator : public FairGenerator
{

  public:

    /** Default constructor. **/
    FairParticleGenerator();


    /** Constructor with PDG-ID, multiplicity and momentum
     ** (optionally vertex)
     **@param pdgid Particle type (PDG encoding)
     **@param mult  Multiplicity
     **@param px,py,pz Momentum components [GeV]
     **@param vx,vy,vz Vertex coordinates [cm], Default (0,0,0)
     **/
    FairParticleGenerator(Int_t pdgid, Int_t mult, Double32_t px,
                          Double32_t py, Double32_t pz, Double32_t vx = 0.,
                          Double32_t vy = 0., Double32_t vz = 0.);


    /** Destructor **/
    virtual ~FairParticleGenerator() {};



    /** Modifiers **/
    void SetPDGType(Int_t pdg)       {fPDGType = pdg;  };
    void SetMultiplicity(Int_t mult) {fMult    = mult; };
    void SetMomentum(Double32_t px, Double32_t py, Double32_t pz);
    void SetVertex(Double32_t vx, Double32_t vy, Double32_t vz);


    /** Creates an event with given type and multiplicity.
     **@param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);



  private:

    Int_t      fPDGType;       // Particle type (PDG encoding)
    Int_t      fMult;          // Multiplicity
    Double32_t fPx, fPy, fPz;  // Momentum components [GeV]
    Double32_t fVx, fVy, fVz;  // Vertex coordinates [cm]


    ClassDef(FairParticleGenerator,1);

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
// -----                FairShieldGenerator header file                 -----
// -----                Created 15/09/06 by V. Friese                  -----
// -------------------------------------------------------------------------

/** FairShieldGenerator
 *@author V.Friese  <v.friese@gsi.de>
 *@since 15.09.06
 *@version 1.0
 *
 ** The FairShieldGenerator is similar to the FairAsciiGenerator. It uses the
 ** ASCII output of the SHIELD code as input for simulation.
 ** The format of the event header is:
 ** event nr.; number of particles; beam momentum; impact parameter
 ** followed by a line for each particle of the format
 ** PID; A; Z; px; py; pz
 ** The PID must be given as for GEANT3. For ions, it is 1000. The total
 ** momentum is required, not momentum per nucleon.
**/


#ifndef FAIRSHIELDGENERATOR_H
#define FAIRSHIELDGENERATOR_H 1

#include "FairGenerator.h"              // for FairGenerator

#include "Riosfwd.h"                    // for ifstream
#include "Rtypes.h"                     // for FairShieldGenerator::Class, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for ifstream
#include <map>                          // for map

class TDatabasePDG;
class FairPrimaryGenerator;
class FairIon;

class FairShieldGenerator : public FairGenerator
{

  public:

    /** Default constructor without arguments should not be used. **/
    FairShieldGenerator();


    /** Standard constructor.
     ** @param fileName The input file name
     **/
    FairShieldGenerator(const char* fileName);


    /** Destructor. **/
    virtual ~FairShieldGenerator();


    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param primGen  pointer to the FairPrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);



  private:

    std::ifstream*      fInputFile;          //! Input file stream
    const Char_t*  fFileName;           //! Input file Name
    TDatabasePDG*  fPDG;                //!  PDG database


    /** Private method CloseInput. Just for convenience. Closes the
     ** input file properly. Called from destructor and from ReadEvent. **/
    void CloseInput();


    /** Private method RegisterIons. Goes through the input file and registers
     ** any ion needed. **/
    Int_t RegisterIons();



    /** STL map from ion name to FairIon **/
    std::map<TString, FairIon*> fIonMap;       //!

    FairShieldGenerator(const FairShieldGenerator&);
    FairShieldGenerator& operator=(const FairShieldGenerator&);

    ClassDef(FairShieldGenerator,1);

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
// -----                FairUrqmdGenerator header file                  -----
// -----          Created 11/06/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------


/** FairUrqmdGenerator.h
 *@ author V.Friese <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 *
 The FairUrqmdGenerator reads the output file 14 (ftn14) from UrQMD. The UrQMD
 calculation has to be performed in the CM system of the collision; Lorentz
 transformation into the lab is performed by this class.
 Derived from FairGenerator.
**/



#ifndef FAIRURQMDGENERATOR_H
#define FAIRURQMDGENERATOR_H

#include "FairGenerator.h"              // for FairGenerator

#include "Rtypes.h"                     // for Int_t, Bool_t, etc

#include <stdio.h>                      // for FILE
#include <map>                          // for map

class FairPrimaryGenerator;

class FairUrqmdGenerator : public FairGenerator
{

  public:

    /** Default constructor without arguments should not be used. **/
    FairUrqmdGenerator();


    /** Standard constructor.
     * @param fileName The input file name
     **/
    FairUrqmdGenerator(const char* fileName);
   
    /** Standard constructor.
     * @param fileName The input file name
     * @param conversion_table name of conversion table file (from Urqmd->PDG) should use the full path to the file
     **/

    FairUrqmdGenerator(const char* fileName,  const char* conversion_table);

    /** Destructor. **/
    ~FairUrqmdGenerator();


    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param pStack    pointer to the stack
     ** @param ver       not used
     **/
    Bool_t ReadEvent(FairPrimaryGenerator* primGen);

    /** Skip defined number of events in file **/
    Bool_t SkipEvents(Int_t count);

  private:

    FILE* fInputFile;                     //!  Input file

    std::map<Int_t,Int_t> fParticleTable;      //!  Map from UrQMD PID to PDGPID

    const Char_t* fFileName;              //!  Input file name

    /** Private method ReadConversionTable. Reads the conversion table
        from UrQMD particle code to PDG particle code and fills the
        conversion map. Is called from the constructor. **/
    void ReadConversionTable(TString conversion_table="");

    /** Check return value from fscanf call **/
    void CheckReturnValue(Int_t retval);

    FairUrqmdGenerator(const FairUrqmdGenerator&);
    FairUrqmdGenerator& operator=(const FairUrqmdGenerator&);

    ClassDef(FairUrqmdGenerator,1);

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
// -----                FairEvtGenGenerator header file                 -----
// -----          Created 09/10/06  by S. Spataro                      -----
// -------------------------------------------------------------------------

/**  FairEvtGenGenerator.h
 *@author S.Spataro  <stefano.spataro@exp2.physik.uni-giessen.de>
 *
 The FairEvtGenGenerator reads an EvtGen input file. The file must contain
 for each event a header line of the format:

 [start]
1       11
  N      Id Ist   M1   M2   DF   DL      px      py      pz       E       t       x       y       z
  0   70553   2   -1   -1    1    2  0.0000  0.0000  0.0000 10.5704  0.0000  0.0000  0.0000  0.0000
  1     521   2    0    0    3    4 -0.1756  0.1064 -0.1494  5.2852  0.0000  0.0000  0.0000  0.0000
  2    -521   2    0    0    7    8  0.1756 -0.1064  0.1494  5.2852  0.0000  0.0000  0.0000  0.0000
  3     333   2    1    1    5    6 -1.4042 -2.0079 -0.7628  2.7603  0.0492 -0.0016  0.0010 -0.0014
  4     211   1    1    1   -1   -1  1.2286  2.1142  0.6134  2.5249  0.0492 -0.0016  0.0010 -0.0014
  5     321   1    3    3   -1   -1 -0.9021 -1.1453 -0.4297  1.5981  0.0492 -0.0016  0.0010 -0.0014
  6    -321   1    3    3   -1   -1 -0.5021 -0.8625 -0.3330  1.1622  0.0492 -0.0016  0.0010 -0.0014
  7     333   2    2    2    9   10 -1.2388  0.1390 -2.0780  2.6316  0.6223  0.0207 -0.0125  0.0176
  8    -211   1    2    2   -1   -1  1.4144 -0.2454  2.2274  2.6536  0.6223  0.0207 -0.0125  0.0176
  9     321   1    7    7   -1   -1 -0.4624  0.1538 -0.9382  1.1668  0.6223  0.0207 -0.0125  0.0176
 10    -321   1    7    7   -1   -1 -0.7764 -0.0148 -1.1398  1.4649  0.6223  0.0207 -0.0125  0.0176


2       11
  N      Id Ist   M1   M2   DF   DL      px      py      pz       E       t       x       y       z
  0   70553   2   -1   -1    1    2  0.0000  0.0000  0.0000 10.5699  0.0000  0.0000  0.0000  0.0000
  1     521   2    0    0    3    4 -0.2228 -0.0227 -0.1080  5.2850  0.0000  0.0000  0.0000  0.0000
  2    -521   2    0    0    7    8  0.2228  0.0227  0.1080  5.2850  0.0000  0.0000  0.0000  0.0000
  3     333   2    1    1    5    6  2.2879  0.7442 -0.3869  2.6413  0.0413 -0.0017 -0.0002 -0.0008
  4     211   1    1    1   -1   -1 -2.5107 -0.7669  0.2789  2.6437  0.0413 -0.0017 -0.0002 -0.0008
  5     321   1    3    3   -1   -1  0.9174  0.3217 -0.2480  1.1182  0.0413 -0.0017 -0.0002 -0.0008
  6    -321   1    3    3   -1   -1  1.3705  0.4225 -0.1389  1.5231  0.0413 -0.0017 -0.0002 -0.0008
  7     333   2    2    2    9   10  2.2762 -1.0938 -0.6929  2.8103  0.0116  0.0005  0.0000  0.0002
  8    -211   1    2    2   -1   -1 -2.0534  1.1165  0.8009  2.4747  0.0116  0.0005  0.0000  0.0002
  9     321   1    7    7   -1   -1  1.4371 -0.7057 -0.4321  1.7302  0.0116  0.0005  0.0000  0.0002
 10    -321   1    7    7   -1   -1  0.8392 -0.3881 -0.2608  1.0801  0.0116  0.0005  0.0000  0.0002


...
 [stop]

 where the first row has the number of event and the number of particles, and below "N" is the line
 number of the event, "Id" is the PDG id number, "Ist" is the number of daughter particles, "M1" and
 "M2" are the two "N" numbers of the mother particle, "DF" and "DL" the "N" of the daughter particles,
 "px" "py" "pz" "E" are the 4-momentum components [in GeV/c], "x" "y" "z" "t" are vertex positions
 [in mm] and decay time.

 In order to produce the output file one shoulkd write, in the EvtGen macro:

 [CUT]
  ...
  ofstream out;
  out.open("evtgen_out.evt");

  EvtStdHep stdhep;
  myGenerator.generateEvent(root_part,t_init);
  stdhep.init();
  root_part->makeStdHep(stdhep);

  out << count << "\t" << stdhep.getNPart();
  out <<stdhep<<endl;

  root_part->deleteTree();
...
[CUT]

 Derived from FairGenerator.
**/


#ifndef FAIR_EVTGENGENERATOR_H
#define FAIR_EVTGENGENERATOR_H


#include "FairGenerator.h"              // for FairGenerator

#include "Rtypes.h"                     // for FairEvtGenGenerator::Class, etc

#include <stdio.h>                      // for FILE

class FairPrimaryGenerator;
class TF1;

class FairEvtGenGenerator : public FairGenerator
{

  public:

    /** Default constructor without arguments should not be used. **/
    FairEvtGenGenerator();


    /** Standard constructor.
     ** @param fileName The input file name
     **/
    FairEvtGenGenerator(const char* fileName);

    /** @param fileName: The input file name, DensityFunction: axial gas density
     **/
    FairEvtGenGenerator(const char* fileName, Double_t Rsigma, TF1* DensityFunction);


    /** Destructor. **/
    virtual ~FairEvtGenGenerator();


    /** Reads on event from the input file and pushes the tracks onto
     ** the stack. Abstract method in base class.
     ** @param primGen  pointer to the FairrimaryGenerator
     **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);



  private:

    //ifstream* fInputFile;             //! Input file stream
    const Char_t* fFileName;            //! Input file Name
    FILE* fInputFile;                   //! Input file pointer

    /** Private method CloseInput. Just for convenience. Closes the
     ** input file properly. Called from destructor and from ReadEvent. **/
    void CloseInput();

    int    fGasmode;
    double fRsigma;


    /** PDG data base */

//  TDatabasePDG *fPDG; //!
    TF1* fDensityFunction;

    FairEvtGenGenerator(const FairEvtGenGenerator&);
    FairEvtGenGenerator& operator=(const FairEvtGenGenerator&);

    ClassDef(FairEvtGenGenerator,1);

};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairAsciiGenerator", payloadCode, "@",
"FairBoxGenerator", payloadCode, "@",
"FairEvtGenGenerator", payloadCode, "@",
"FairIonGenerator", payloadCode, "@",
"FairParticleGenerator", payloadCode, "@",
"FairShieldGenerator", payloadCode, "@",
"FairUrqmdGenerator", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__GenDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__GenDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__GenDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__GenDict() {
  TriggerDictionaryInitialization_G__GenDict_Impl();
}

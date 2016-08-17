// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIcommondIpassivedIG__PassiveDict

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
#include "FairCave.h"
#include "FairGeoCave.h"
#include "FairGeoMagnet.h"
#include "FairGeoPassivePar.h"
#include "FairGeoPipe.h"
#include "FairGeoTarget.h"
#include "FairMagnet.h"
#include "FairPassiveContFact.h"
#include "FairPipe.h"
#include "FairTarget.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairMagnet(void *p = 0);
   static void *newArray_FairMagnet(Long_t size, void *p);
   static void delete_FairMagnet(void *p);
   static void deleteArray_FairMagnet(void *p);
   static void destruct_FairMagnet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMagnet*)
   {
      ::FairMagnet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMagnet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMagnet", ::FairMagnet::Class_Version(), "invalid", 222,
                  typeid(::FairMagnet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMagnet::Dictionary, isa_proxy, 4,
                  sizeof(::FairMagnet) );
      instance.SetNew(&new_FairMagnet);
      instance.SetNewArray(&newArray_FairMagnet);
      instance.SetDelete(&delete_FairMagnet);
      instance.SetDeleteArray(&deleteArray_FairMagnet);
      instance.SetDestructor(&destruct_FairMagnet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMagnet*)
   {
      return GenerateInitInstanceLocal((::FairMagnet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMagnet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTarget(void *p = 0);
   static void *newArray_FairTarget(Long_t size, void *p);
   static void delete_FairTarget(void *p);
   static void deleteArray_FairTarget(void *p);
   static void destruct_FairTarget(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTarget*)
   {
      ::FairTarget *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTarget >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTarget", ::FairTarget::Class_Version(), "invalid", 311,
                  typeid(::FairTarget), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTarget::Dictionary, isa_proxy, 4,
                  sizeof(::FairTarget) );
      instance.SetNew(&new_FairTarget);
      instance.SetNewArray(&newArray_FairTarget);
      instance.SetDelete(&delete_FairTarget);
      instance.SetDeleteArray(&deleteArray_FairTarget);
      instance.SetDestructor(&destruct_FairTarget);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTarget*)
   {
      return GenerateInitInstanceLocal((::FairTarget*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTarget*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairPipe(void *p = 0);
   static void *newArray_FairPipe(Long_t size, void *p);
   static void delete_FairPipe(void *p);
   static void deleteArray_FairPipe(void *p);
   static void destruct_FairPipe(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairPipe*)
   {
      ::FairPipe *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairPipe >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairPipe", ::FairPipe::Class_Version(), "invalid", 281,
                  typeid(::FairPipe), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairPipe::Dictionary, isa_proxy, 4,
                  sizeof(::FairPipe) );
      instance.SetNew(&new_FairPipe);
      instance.SetNewArray(&newArray_FairPipe);
      instance.SetDelete(&delete_FairPipe);
      instance.SetDeleteArray(&deleteArray_FairPipe);
      instance.SetDestructor(&destruct_FairPipe);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairPipe*)
   {
      return GenerateInitInstanceLocal((::FairPipe*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairPipe*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairCave(void *p = 0);
   static void *newArray_FairCave(Long_t size, void *p);
   static void delete_FairCave(void *p);
   static void deleteArray_FairCave(void *p);
   static void destruct_FairCave(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairCave*)
   {
      ::FairCave *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairCave >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairCave", ::FairCave::Class_Version(), "invalid", 20,
                  typeid(::FairCave), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairCave::Dictionary, isa_proxy, 4,
                  sizeof(::FairCave) );
      instance.SetNew(&new_FairCave);
      instance.SetNewArray(&newArray_FairCave);
      instance.SetDelete(&delete_FairCave);
      instance.SetDeleteArray(&deleteArray_FairCave);
      instance.SetDestructor(&destruct_FairCave);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairCave*)
   {
      return GenerateInitInstanceLocal((::FairCave*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairCave*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoCave(void *p = 0);
   static void *newArray_FairGeoCave(Long_t size, void *p);
   static void delete_FairGeoCave(void *p);
   static void deleteArray_FairGeoCave(void *p);
   static void destruct_FairGeoCave(void *p);
   static void streamer_FairGeoCave(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoCave*)
   {
      ::FairGeoCave *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoCave >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoCave", ::FairGeoCave::Class_Version(), "invalid", 57,
                  typeid(::FairGeoCave), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoCave::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoCave) );
      instance.SetNew(&new_FairGeoCave);
      instance.SetNewArray(&newArray_FairGeoCave);
      instance.SetDelete(&delete_FairGeoCave);
      instance.SetDeleteArray(&deleteArray_FairGeoCave);
      instance.SetDestructor(&destruct_FairGeoCave);
      instance.SetStreamerFunc(&streamer_FairGeoCave);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoCave*)
   {
      return GenerateInitInstanceLocal((::FairGeoCave*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoCave*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoPipe(void *p = 0);
   static void *newArray_FairGeoPipe(Long_t size, void *p);
   static void delete_FairGeoPipe(void *p);
   static void deleteArray_FairGeoPipe(void *p);
   static void destruct_FairGeoPipe(void *p);
   static void streamer_FairGeoPipe(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoPipe*)
   {
      ::FairGeoPipe *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoPipe >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoPipe", ::FairGeoPipe::Class_Version(), "invalid", 161,
                  typeid(::FairGeoPipe), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoPipe::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoPipe) );
      instance.SetNew(&new_FairGeoPipe);
      instance.SetNewArray(&newArray_FairGeoPipe);
      instance.SetDelete(&delete_FairGeoPipe);
      instance.SetDeleteArray(&deleteArray_FairGeoPipe);
      instance.SetDestructor(&destruct_FairGeoPipe);
      instance.SetStreamerFunc(&streamer_FairGeoPipe);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoPipe*)
   {
      return GenerateInitInstanceLocal((::FairGeoPipe*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoPipe*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoTarget(void *p = 0);
   static void *newArray_FairGeoTarget(Long_t size, void *p);
   static void delete_FairGeoTarget(void *p);
   static void deleteArray_FairGeoTarget(void *p);
   static void destruct_FairGeoTarget(void *p);
   static void streamer_FairGeoTarget(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoTarget*)
   {
      ::FairGeoTarget *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoTarget >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoTarget", ::FairGeoTarget::Class_Version(), "invalid", 191,
                  typeid(::FairGeoTarget), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoTarget::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoTarget) );
      instance.SetNew(&new_FairGeoTarget);
      instance.SetNewArray(&newArray_FairGeoTarget);
      instance.SetDelete(&delete_FairGeoTarget);
      instance.SetDeleteArray(&deleteArray_FairGeoTarget);
      instance.SetDestructor(&destruct_FairGeoTarget);
      instance.SetStreamerFunc(&streamer_FairGeoTarget);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoTarget*)
   {
      return GenerateInitInstanceLocal((::FairGeoTarget*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoTarget*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoMagnet(void *p = 0);
   static void *newArray_FairGeoMagnet(Long_t size, void *p);
   static void delete_FairGeoMagnet(void *p);
   static void deleteArray_FairGeoMagnet(void *p);
   static void destruct_FairGeoMagnet(void *p);
   static void streamer_FairGeoMagnet(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoMagnet*)
   {
      ::FairGeoMagnet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoMagnet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoMagnet", ::FairGeoMagnet::Class_Version(), "invalid", 88,
                  typeid(::FairGeoMagnet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoMagnet::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoMagnet) );
      instance.SetNew(&new_FairGeoMagnet);
      instance.SetNewArray(&newArray_FairGeoMagnet);
      instance.SetDelete(&delete_FairGeoMagnet);
      instance.SetDeleteArray(&deleteArray_FairGeoMagnet);
      instance.SetDestructor(&destruct_FairGeoMagnet);
      instance.SetStreamerFunc(&streamer_FairGeoMagnet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoMagnet*)
   {
      return GenerateInitInstanceLocal((::FairGeoMagnet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoMagnet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoPassivePar(void *p = 0);
   static void *newArray_FairGeoPassivePar(Long_t size, void *p);
   static void delete_FairGeoPassivePar(void *p);
   static void deleteArray_FairGeoPassivePar(void *p);
   static void destruct_FairGeoPassivePar(void *p);
   static void streamer_FairGeoPassivePar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoPassivePar*)
   {
      ::FairGeoPassivePar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoPassivePar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoPassivePar", ::FairGeoPassivePar::Class_Version(), "invalid", 120,
                  typeid(::FairGeoPassivePar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoPassivePar::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoPassivePar) );
      instance.SetNew(&new_FairGeoPassivePar);
      instance.SetNewArray(&newArray_FairGeoPassivePar);
      instance.SetDelete(&delete_FairGeoPassivePar);
      instance.SetDeleteArray(&deleteArray_FairGeoPassivePar);
      instance.SetDestructor(&destruct_FairGeoPassivePar);
      instance.SetStreamerFunc(&streamer_FairGeoPassivePar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoPassivePar*)
   {
      return GenerateInitInstanceLocal((::FairGeoPassivePar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoPassivePar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairPassiveContFact(void *p = 0);
   static void *newArray_FairPassiveContFact(Long_t size, void *p);
   static void delete_FairPassiveContFact(void *p);
   static void deleteArray_FairPassiveContFact(void *p);
   static void destruct_FairPassiveContFact(void *p);
   static void streamer_FairPassiveContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairPassiveContFact*)
   {
      ::FairPassiveContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairPassiveContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairPassiveContFact", ::FairPassiveContFact::Class_Version(), "invalid", 254,
                  typeid(::FairPassiveContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairPassiveContFact::Dictionary, isa_proxy, 16,
                  sizeof(::FairPassiveContFact) );
      instance.SetNew(&new_FairPassiveContFact);
      instance.SetNewArray(&newArray_FairPassiveContFact);
      instance.SetDelete(&delete_FairPassiveContFact);
      instance.SetDeleteArray(&deleteArray_FairPassiveContFact);
      instance.SetDestructor(&destruct_FairPassiveContFact);
      instance.SetStreamerFunc(&streamer_FairPassiveContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairPassiveContFact*)
   {
      return GenerateInitInstanceLocal((::FairPassiveContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairPassiveContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairMagnet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMagnet::Class_Name()
{
   return "FairMagnet";
}

//______________________________________________________________________________
const char *FairMagnet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMagnet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMagnet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMagnet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMagnet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMagnet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMagnet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMagnet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTarget::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTarget::Class_Name()
{
   return "FairTarget";
}

//______________________________________________________________________________
const char *FairTarget::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTarget*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTarget::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTarget*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTarget::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTarget*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTarget::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTarget*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairPipe::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairPipe::Class_Name()
{
   return "FairPipe";
}

//______________________________________________________________________________
const char *FairPipe::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairPipe*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairPipe::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairPipe*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairPipe::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairPipe*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairPipe::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairPipe*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairCave::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairCave::Class_Name()
{
   return "FairCave";
}

//______________________________________________________________________________
const char *FairCave::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairCave*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairCave::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairCave*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairCave::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairCave*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairCave::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairCave*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoCave::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoCave::Class_Name()
{
   return "FairGeoCave";
}

//______________________________________________________________________________
const char *FairGeoCave::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCave*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoCave::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCave*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoCave::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCave*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoCave::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCave*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoPipe::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoPipe::Class_Name()
{
   return "FairGeoPipe";
}

//______________________________________________________________________________
const char *FairGeoPipe::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPipe*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoPipe::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPipe*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoPipe::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPipe*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoPipe::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPipe*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoTarget::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoTarget::Class_Name()
{
   return "FairGeoTarget";
}

//______________________________________________________________________________
const char *FairGeoTarget::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTarget*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoTarget::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTarget*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoTarget::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTarget*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoTarget::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTarget*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoMagnet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoMagnet::Class_Name()
{
   return "FairGeoMagnet";
}

//______________________________________________________________________________
const char *FairGeoMagnet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMagnet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoMagnet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMagnet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoMagnet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMagnet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoMagnet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMagnet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoPassivePar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoPassivePar::Class_Name()
{
   return "FairGeoPassivePar";
}

//______________________________________________________________________________
const char *FairGeoPassivePar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPassivePar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoPassivePar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPassivePar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoPassivePar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPassivePar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoPassivePar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPassivePar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairPassiveContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairPassiveContFact::Class_Name()
{
   return "FairPassiveContFact";
}

//______________________________________________________________________________
const char *FairPassiveContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairPassiveContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairPassiveContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairPassiveContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairPassiveContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairPassiveContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairPassiveContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairPassiveContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairMagnet::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMagnet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMagnet::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMagnet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMagnet(void *p) {
      return  p ? new(p) ::FairMagnet : new ::FairMagnet;
   }
   static void *newArray_FairMagnet(Long_t nElements, void *p) {
      return p ? new(p) ::FairMagnet[nElements] : new ::FairMagnet[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMagnet(void *p) {
      delete ((::FairMagnet*)p);
   }
   static void deleteArray_FairMagnet(void *p) {
      delete [] ((::FairMagnet*)p);
   }
   static void destruct_FairMagnet(void *p) {
      typedef ::FairMagnet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMagnet

//______________________________________________________________________________
void FairTarget::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTarget.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTarget::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTarget::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTarget(void *p) {
      return  p ? new(p) ::FairTarget : new ::FairTarget;
   }
   static void *newArray_FairTarget(Long_t nElements, void *p) {
      return p ? new(p) ::FairTarget[nElements] : new ::FairTarget[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTarget(void *p) {
      delete ((::FairTarget*)p);
   }
   static void deleteArray_FairTarget(void *p) {
      delete [] ((::FairTarget*)p);
   }
   static void destruct_FairTarget(void *p) {
      typedef ::FairTarget current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTarget

//______________________________________________________________________________
void FairPipe::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairPipe.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairPipe::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairPipe::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairPipe(void *p) {
      return  p ? new(p) ::FairPipe : new ::FairPipe;
   }
   static void *newArray_FairPipe(Long_t nElements, void *p) {
      return p ? new(p) ::FairPipe[nElements] : new ::FairPipe[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairPipe(void *p) {
      delete ((::FairPipe*)p);
   }
   static void deleteArray_FairPipe(void *p) {
      delete [] ((::FairPipe*)p);
   }
   static void destruct_FairPipe(void *p) {
      typedef ::FairPipe current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairPipe

//______________________________________________________________________________
void FairCave::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairCave.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairCave::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairCave::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairCave(void *p) {
      return  p ? new(p) ::FairCave : new ::FairCave;
   }
   static void *newArray_FairCave(Long_t nElements, void *p) {
      return p ? new(p) ::FairCave[nElements] : new ::FairCave[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairCave(void *p) {
      delete ((::FairCave*)p);
   }
   static void deleteArray_FairCave(void *p) {
      delete [] ((::FairCave*)p);
   }
   static void destruct_FairCave(void *p) {
      typedef ::FairCave current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairCave

//______________________________________________________________________________
void FairGeoCave::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoCave.

   FairGeoSet::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoCave(void *p) {
      return  p ? new(p) ::FairGeoCave : new ::FairGeoCave;
   }
   static void *newArray_FairGeoCave(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoCave[nElements] : new ::FairGeoCave[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoCave(void *p) {
      delete ((::FairGeoCave*)p);
   }
   static void deleteArray_FairGeoCave(void *p) {
      delete [] ((::FairGeoCave*)p);
   }
   static void destruct_FairGeoCave(void *p) {
      typedef ::FairGeoCave current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoCave(TBuffer &buf, void *obj) {
      ((::FairGeoCave*)obj)->::FairGeoCave::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoCave

//______________________________________________________________________________
void FairGeoPipe::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoPipe.

   FairGeoSet::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoPipe(void *p) {
      return  p ? new(p) ::FairGeoPipe : new ::FairGeoPipe;
   }
   static void *newArray_FairGeoPipe(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoPipe[nElements] : new ::FairGeoPipe[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoPipe(void *p) {
      delete ((::FairGeoPipe*)p);
   }
   static void deleteArray_FairGeoPipe(void *p) {
      delete [] ((::FairGeoPipe*)p);
   }
   static void destruct_FairGeoPipe(void *p) {
      typedef ::FairGeoPipe current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoPipe(TBuffer &buf, void *obj) {
      ((::FairGeoPipe*)obj)->::FairGeoPipe::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoPipe

//______________________________________________________________________________
void FairGeoTarget::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoTarget.

   FairGeoSet::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoTarget(void *p) {
      return  p ? new(p) ::FairGeoTarget : new ::FairGeoTarget;
   }
   static void *newArray_FairGeoTarget(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoTarget[nElements] : new ::FairGeoTarget[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoTarget(void *p) {
      delete ((::FairGeoTarget*)p);
   }
   static void deleteArray_FairGeoTarget(void *p) {
      delete [] ((::FairGeoTarget*)p);
   }
   static void destruct_FairGeoTarget(void *p) {
      typedef ::FairGeoTarget current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoTarget(TBuffer &buf, void *obj) {
      ((::FairGeoTarget*)obj)->::FairGeoTarget::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoTarget

//______________________________________________________________________________
void FairGeoMagnet::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoMagnet.

   FairGeoSet::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoMagnet(void *p) {
      return  p ? new(p) ::FairGeoMagnet : new ::FairGeoMagnet;
   }
   static void *newArray_FairGeoMagnet(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoMagnet[nElements] : new ::FairGeoMagnet[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoMagnet(void *p) {
      delete ((::FairGeoMagnet*)p);
   }
   static void deleteArray_FairGeoMagnet(void *p) {
      delete [] ((::FairGeoMagnet*)p);
   }
   static void destruct_FairGeoMagnet(void *p) {
      typedef ::FairGeoMagnet current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoMagnet(TBuffer &buf, void *obj) {
      ((::FairGeoMagnet*)obj)->::FairGeoMagnet::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoMagnet

//______________________________________________________________________________
void FairGeoPassivePar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoPassivePar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b.CheckByteCount(R__s, R__c, FairGeoPassivePar::IsA());
   } else {
      R__c = R__b.WriteVersion(FairGeoPassivePar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoPassivePar(void *p) {
      return  p ? new(p) ::FairGeoPassivePar : new ::FairGeoPassivePar;
   }
   static void *newArray_FairGeoPassivePar(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoPassivePar[nElements] : new ::FairGeoPassivePar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoPassivePar(void *p) {
      delete ((::FairGeoPassivePar*)p);
   }
   static void deleteArray_FairGeoPassivePar(void *p) {
      delete [] ((::FairGeoPassivePar*)p);
   }
   static void destruct_FairGeoPassivePar(void *p) {
      typedef ::FairGeoPassivePar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoPassivePar(TBuffer &buf, void *obj) {
      ((::FairGeoPassivePar*)obj)->::FairGeoPassivePar::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoPassivePar

//______________________________________________________________________________
void FairPassiveContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairPassiveContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairPassiveContFact(void *p) {
      return  p ? new(p) ::FairPassiveContFact : new ::FairPassiveContFact;
   }
   static void *newArray_FairPassiveContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairPassiveContFact[nElements] : new ::FairPassiveContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairPassiveContFact(void *p) {
      delete ((::FairPassiveContFact*)p);
   }
   static void deleteArray_FairPassiveContFact(void *p) {
      delete [] ((::FairPassiveContFact*)p);
   }
   static void destruct_FairPassiveContFact(void *p) {
      typedef ::FairPassiveContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairPassiveContFact(TBuffer &buf, void *obj) {
      ((::FairPassiveContFact*)obj)->::FairPassiveContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairPassiveContFact

namespace {
  void TriggerDictionaryInitialization_G__PassiveDict_Impl() {
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
"/Users/turany/development/FairRoot/examples/common/passive",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/common/passive/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__PassiveDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairMagnet;
class FairTarget;
class __attribute__((annotate(R"ATTRDUMP(PNDPIPE)ATTRDUMP"))) FairPipe;
class __attribute__((annotate(R"ATTRDUMP(PNDCaveSD)ATTRDUMP"))) FairCave;
class __attribute__((annotate(R"ATTRDUMP(Class for the geometry of CAVE)ATTRDUMP"))) FairGeoCave;
class __attribute__((annotate(R"ATTRDUMP(Class for geometry of beam pipe)ATTRDUMP"))) FairGeoPipe;
class __attribute__((annotate(R"ATTRDUMP(Class for geometry of Target)ATTRDUMP"))) FairGeoTarget;
class __attribute__((annotate(R"ATTRDUMP(Class for the geometry of Magnet)ATTRDUMP"))) FairGeoMagnet;
class FairGeoPassivePar;
class __attribute__((annotate(R"ATTRDUMP(Factory for all Passive parameter containers)ATTRDUMP"))) FairPassiveContFact;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__PassiveDict dictionary payload"

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
#ifndef Cave_H
#define Cave_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairCave::Class, ClassDef, etc

class FairCave : public FairModule
{
  public:
    FairCave(const char* name, const char* Title="Exp Cave");
    FairCave();
    virtual ~FairCave();
    virtual void ConstructGeometry();


  private:
    Double_t world[3];
    ClassDef(FairCave,1) //PNDCaveSD
};

#endif //Cave_H

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDGEOCAVE_H
#define PNDGEOCAVE_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoCave::Class, Bool_t, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairGeoMedia;

class  FairGeoCave : public FairGeoSet
{
  protected:
    TString name;
  public:
    FairGeoCave();
    ~FairGeoCave() {}
    const char* getModuleName(Int_t) {return name.Data();}
    Bool_t read(std::fstream&,FairGeoMedia*);
    void addRefNodes();
    void write(std::fstream&);
    void print();
    ClassDef(FairGeoCave,0) // Class for the geometry of CAVE
};

#endif  /* !PNDGEOCAVE_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDGEOMAGNET_H
#define PNDGEOMAGNET_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Rtypes.h"                     // for FairGeoMagnet::Class, Int_t, etc

class  FairGeoMagnet : public FairGeoSet
{
  protected:
    char modName[2];  // name of module
    char eleName[2];  // substring for elements in module
  public:
    FairGeoMagnet();
    ~FairGeoMagnet() {}
    const char* getModuleName(Int_t) {return modName;}
    const char* getEleName(Int_t) {return eleName;}
    ClassDef(FairGeoMagnet,0) // Class for the geometry of Magnet
};

#endif  /* !FAIRGEOMAGNET_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDGEOPASSIVEPAR_H
#define PNDGEOPASSIVEPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for FairGeoPassivePar::Class, etc

class FairParamList;
class TObjArray;

class FairGeoPassivePar : public FairParGenericSet
{
  public:
    TObjArray*            fGeoSensNodes; // List of FairGeoNodes for sensitive volumes
    TObjArray*            fGeoPassNodes; // List of FairGeoNodes for sensitive volumes

    FairGeoPassivePar(const char* name="FairGeoPassivePar",
                      const char* title="Passive Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~FairGeoPassivePar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray*             GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray*             GetGeoPassiveNodes() {return fGeoPassNodes;}

  private:
    FairGeoPassivePar(const FairGeoPassivePar&);
    FairGeoPassivePar& operator=(const FairGeoPassivePar&);

    ClassDef(FairGeoPassivePar,1)
};

#endif /* !PNDGEOPASSIVEPAR_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDGEOPIPE_H
#define PNDGEOPIPE_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Rtypes.h"                     // for FairGeoPipe::Class, Int_t, etc

class FairGeoBuilder;

class  FairGeoPipe : public FairGeoSet
{
  protected:
    char modName[2];  // name of module
    char eleName[2];  // substring for elements in module
  public:
    FairGeoPipe();
    virtual ~FairGeoPipe();
    const char* getModuleName(Int_t) {return modName;}
    const char* getEleName(Int_t) {return eleName;}
    Bool_t create(FairGeoBuilder*);
    ClassDef(FairGeoPipe,0) // Class for geometry of beam pipe
};

#endif  /* !PNDGEOPIPE_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDGEOTARGET_H
#define PNDGEOTARGET_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Rtypes.h"                     // for FairGeoTarget::Class, Int_t, etc

class  FairGeoTarget : public FairGeoSet
{
  protected:
    char modName[2];  // name of module
    char eleName[2];  // substring for elements in module
  public:
    FairGeoTarget();
    ~FairGeoTarget() {}
    const char* getModuleName(Int_t) {return modName;}
    const char* getEleName(Int_t) {return eleName;}
    ClassDef(FairGeoTarget,0) // Class for geometry of Target
};

#endif  /* !PNDGEOTARGET_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef MAGNET_H
#define MAGNET_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairMagnet::Class, Bool_t, etc

#include <string>                       // for string

class FairMagnet : public FairModule
{
  public:
    FairMagnet(const char* name, const char* Title="PND Magnet");
    FairMagnet();
    virtual ~FairMagnet();
    void ConstructGeometry();
    void ConstructASCIIGeometry();
    Bool_t CheckIfSensitive(std::string name);
    ClassDef(FairMagnet,1)

};

#endif //MAGNET_H

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PNDPASSIVECONTFACT_H
#define PNDPASSIVECONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for FairPassiveContFact::Class, etc

class FairParSet;

class FairPassiveContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairPassiveContFact();
    ~FairPassiveContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairPassiveContFact,0) // Factory for all Passive parameter containers
};

#endif  /* !PNDPASSIVECONTFACT_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIPE_H
#define PIPE_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairPipe::Class, ClassDef, etc

class FairPipe : public FairModule
{
  public:
    FairPipe(const char* name, const char* Title="PND Pipe");
    FairPipe();

    virtual ~FairPipe();
    virtual void ConstructGeometry();

    ClassDef(FairPipe,1) //PNDPIPE

};

#endif //PIPE_H

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef Target_H
#define Target_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairTarget::Class, ClassDef, etc

class FairTarget : public FairModule
{
  public:
    FairTarget(const char* name, const char* Title="PND Target");
    FairTarget();
    virtual ~FairTarget();
    virtual void ConstructGeometry();
    ClassDef(FairTarget,1)

};

#endif //Target_H


#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairCave", payloadCode, "@",
"FairGeoCave", payloadCode, "@",
"FairGeoMagnet", payloadCode, "@",
"FairGeoPassivePar", payloadCode, "@",
"FairGeoPipe", payloadCode, "@",
"FairGeoTarget", payloadCode, "@",
"FairMagnet", payloadCode, "@",
"FairPassiveContFact", payloadCode, "@",
"FairPipe", payloadCode, "@",
"FairTarget", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__PassiveDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__PassiveDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__PassiveDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__PassiveDict() {
  TriggerDictionaryInitialization_G__PassiveDict_Impl();
}

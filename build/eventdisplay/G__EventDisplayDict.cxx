// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIeventdisplaydIG__EventDisplayDict

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
#include "FairEventManager.h"
#include "FairMCTracks.h"
#include "FairEventManagerEditor.h"
#include "FairMCTracksEditor.h"
#include "FairBoxSet.h"
#include "FairBoxSetDraw.h"
#include "FairBoxSetEditor.h"
#include "FairPointSetDraw.h"
#include "FairMCPointDraw.h"
#include "FairHitDraw.h"
#include "FairHitPointSetDraw.h"
#include "FairTimeStampPointDraw.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairEventManager(void *p = 0);
   static void *newArray_FairEventManager(Long_t size, void *p);
   static void delete_FairEventManager(void *p);
   static void deleteArray_FairEventManager(void *p);
   static void destruct_FairEventManager(void *p);
   static void streamer_FairEventManager(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairEventManager*)
   {
      ::FairEventManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairEventManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairEventManager", ::FairEventManager::Class_Version(), "invalid", 34,
                  typeid(::FairEventManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairEventManager::Dictionary, isa_proxy, 16,
                  sizeof(::FairEventManager) );
      instance.SetNew(&new_FairEventManager);
      instance.SetNewArray(&newArray_FairEventManager);
      instance.SetDelete(&delete_FairEventManager);
      instance.SetDeleteArray(&deleteArray_FairEventManager);
      instance.SetDestructor(&destruct_FairEventManager);
      instance.SetStreamerFunc(&streamer_FairEventManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairEventManager*)
   {
      return GenerateInitInstanceLocal((::FairEventManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairEventManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCTracks(void *p = 0);
   static void *newArray_FairMCTracks(Long_t size, void *p);
   static void delete_FairMCTracks(void *p);
   static void deleteArray_FairMCTracks(void *p);
   static void destruct_FairMCTracks(void *p);
   static void streamer_FairMCTracks(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCTracks*)
   {
      ::FairMCTracks *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCTracks >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCTracks", ::FairMCTracks::Class_Version(), "invalid", 147,
                  typeid(::FairMCTracks), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCTracks::Dictionary, isa_proxy, 16,
                  sizeof(::FairMCTracks) );
      instance.SetNew(&new_FairMCTracks);
      instance.SetNewArray(&newArray_FairMCTracks);
      instance.SetDelete(&delete_FairMCTracks);
      instance.SetDeleteArray(&deleteArray_FairMCTracks);
      instance.SetDestructor(&destruct_FairMCTracks);
      instance.SetStreamerFunc(&streamer_FairMCTracks);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCTracks*)
   {
      return GenerateInitInstanceLocal((::FairMCTracks*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCTracks*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCTracksEditor(void *p = 0);
   static void *newArray_FairMCTracksEditor(Long_t size, void *p);
   static void delete_FairMCTracksEditor(void *p);
   static void deleteArray_FairMCTracksEditor(void *p);
   static void destruct_FairMCTracksEditor(void *p);
   static void streamer_FairMCTracksEditor(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCTracksEditor*)
   {
      ::FairMCTracksEditor *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCTracksEditor >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCTracksEditor", ::FairMCTracksEditor::Class_Version(), "invalid", 280,
                  typeid(::FairMCTracksEditor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCTracksEditor::Dictionary, isa_proxy, 16,
                  sizeof(::FairMCTracksEditor) );
      instance.SetNew(&new_FairMCTracksEditor);
      instance.SetNewArray(&newArray_FairMCTracksEditor);
      instance.SetDelete(&delete_FairMCTracksEditor);
      instance.SetDeleteArray(&deleteArray_FairMCTracksEditor);
      instance.SetDestructor(&destruct_FairMCTracksEditor);
      instance.SetStreamerFunc(&streamer_FairMCTracksEditor);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCTracksEditor*)
   {
      return GenerateInitInstanceLocal((::FairMCTracksEditor*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCTracksEditor*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairEventManagerEditor(void *p = 0);
   static void *newArray_FairEventManagerEditor(Long_t size, void *p);
   static void delete_FairEventManagerEditor(void *p);
   static void deleteArray_FairEventManagerEditor(void *p);
   static void destruct_FairEventManagerEditor(void *p);
   static void streamer_FairEventManagerEditor(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairEventManagerEditor*)
   {
      ::FairEventManagerEditor *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairEventManagerEditor >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairEventManagerEditor", ::FairEventManagerEditor::Class_Version(), "invalid", 231,
                  typeid(::FairEventManagerEditor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairEventManagerEditor::Dictionary, isa_proxy, 16,
                  sizeof(::FairEventManagerEditor) );
      instance.SetNew(&new_FairEventManagerEditor);
      instance.SetNewArray(&newArray_FairEventManagerEditor);
      instance.SetDelete(&delete_FairEventManagerEditor);
      instance.SetDeleteArray(&deleteArray_FairEventManagerEditor);
      instance.SetDestructor(&destruct_FairEventManagerEditor);
      instance.SetStreamerFunc(&streamer_FairEventManagerEditor);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairEventManagerEditor*)
   {
      return GenerateInitInstanceLocal((::FairEventManagerEditor*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairEventManagerEditor*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairBoxSetDraw(void *p);
   static void deleteArray_FairBoxSetDraw(void *p);
   static void destruct_FairBoxSetDraw(void *p);
   static void streamer_FairBoxSetDraw(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairBoxSetDraw*)
   {
      ::FairBoxSetDraw *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairBoxSetDraw >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairBoxSetDraw", ::FairBoxSetDraw::Class_Version(), "FairBoxSetDraw.h", 41,
                  typeid(::FairBoxSetDraw), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairBoxSetDraw::Dictionary, isa_proxy, 16,
                  sizeof(::FairBoxSetDraw) );
      instance.SetDelete(&delete_FairBoxSetDraw);
      instance.SetDeleteArray(&deleteArray_FairBoxSetDraw);
      instance.SetDestructor(&destruct_FairBoxSetDraw);
      instance.SetStreamerFunc(&streamer_FairBoxSetDraw);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairBoxSetDraw*)
   {
      return GenerateInitInstanceLocal((::FairBoxSetDraw*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairBoxSetDraw*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairPointSetDraw(void *p);
   static void deleteArray_FairPointSetDraw(void *p);
   static void destruct_FairPointSetDraw(void *p);
   static void streamer_FairPointSetDraw(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairPointSetDraw*)
   {
      ::FairPointSetDraw *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairPointSetDraw >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairPointSetDraw", ::FairPointSetDraw::Class_Version(), "invalid", 605,
                  typeid(::FairPointSetDraw), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairPointSetDraw::Dictionary, isa_proxy, 16,
                  sizeof(::FairPointSetDraw) );
      instance.SetDelete(&delete_FairPointSetDraw);
      instance.SetDeleteArray(&deleteArray_FairPointSetDraw);
      instance.SetDestructor(&destruct_FairPointSetDraw);
      instance.SetStreamerFunc(&streamer_FairPointSetDraw);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairPointSetDraw*)
   {
      return GenerateInitInstanceLocal((::FairPointSetDraw*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairPointSetDraw*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairHitDraw(void *p = 0);
   static void *newArray_FairHitDraw(Long_t size, void *p);
   static void delete_FairHitDraw(void *p);
   static void deleteArray_FairHitDraw(void *p);
   static void destruct_FairHitDraw(void *p);
   static void streamer_FairHitDraw(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairHitDraw*)
   {
      ::FairHitDraw *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairHitDraw >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairHitDraw", ::FairHitDraw::Class_Version(), "invalid", 720,
                  typeid(::FairHitDraw), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairHitDraw::Dictionary, isa_proxy, 16,
                  sizeof(::FairHitDraw) );
      instance.SetNew(&new_FairHitDraw);
      instance.SetNewArray(&newArray_FairHitDraw);
      instance.SetDelete(&delete_FairHitDraw);
      instance.SetDeleteArray(&deleteArray_FairHitDraw);
      instance.SetDestructor(&destruct_FairHitDraw);
      instance.SetStreamerFunc(&streamer_FairHitDraw);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairHitDraw*)
   {
      return GenerateInitInstanceLocal((::FairHitDraw*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairHitDraw*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairBoxSet(void *p);
   static void deleteArray_FairBoxSet(void *p);
   static void destruct_FairBoxSet(void *p);
   static void streamer_FairBoxSet(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairBoxSet*)
   {
      ::FairBoxSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairBoxSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairBoxSet", ::FairBoxSet::Class_Version(), "invalid", 335,
                  typeid(::FairBoxSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairBoxSet::Dictionary, isa_proxy, 16,
                  sizeof(::FairBoxSet) );
      instance.SetDelete(&delete_FairBoxSet);
      instance.SetDeleteArray(&deleteArray_FairBoxSet);
      instance.SetDestructor(&destruct_FairBoxSet);
      instance.SetStreamerFunc(&streamer_FairBoxSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairBoxSet*)
   {
      return GenerateInitInstanceLocal((::FairBoxSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairBoxSet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairBoxSetEditor(void *p = 0);
   static void *newArray_FairBoxSetEditor(Long_t size, void *p);
   static void delete_FairBoxSetEditor(void *p);
   static void deleteArray_FairBoxSetEditor(void *p);
   static void destruct_FairBoxSetEditor(void *p);
   static void streamer_FairBoxSetEditor(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairBoxSetEditor*)
   {
      ::FairBoxSetEditor *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairBoxSetEditor >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairBoxSetEditor", ::FairBoxSetEditor::Class_Version(), "invalid", 528,
                  typeid(::FairBoxSetEditor), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairBoxSetEditor::Dictionary, isa_proxy, 16,
                  sizeof(::FairBoxSetEditor) );
      instance.SetNew(&new_FairBoxSetEditor);
      instance.SetNewArray(&newArray_FairBoxSetEditor);
      instance.SetDelete(&delete_FairBoxSetEditor);
      instance.SetDeleteArray(&deleteArray_FairBoxSetEditor);
      instance.SetDestructor(&destruct_FairBoxSetEditor);
      instance.SetStreamerFunc(&streamer_FairBoxSetEditor);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairBoxSetEditor*)
   {
      return GenerateInitInstanceLocal((::FairBoxSetEditor*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairBoxSetEditor*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairHitPointSetDraw(void *p = 0);
   static void *newArray_FairHitPointSetDraw(Long_t size, void *p);
   static void delete_FairHitPointSetDraw(void *p);
   static void deleteArray_FairHitPointSetDraw(void *p);
   static void destruct_FairHitPointSetDraw(void *p);
   static void streamer_FairHitPointSetDraw(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairHitPointSetDraw*)
   {
      ::FairHitPointSetDraw *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairHitPointSetDraw >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairHitPointSetDraw", ::FairHitPointSetDraw::Class_Version(), "invalid", 764,
                  typeid(::FairHitPointSetDraw), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairHitPointSetDraw::Dictionary, isa_proxy, 16,
                  sizeof(::FairHitPointSetDraw) );
      instance.SetNew(&new_FairHitPointSetDraw);
      instance.SetNewArray(&newArray_FairHitPointSetDraw);
      instance.SetDelete(&delete_FairHitPointSetDraw);
      instance.SetDeleteArray(&deleteArray_FairHitPointSetDraw);
      instance.SetDestructor(&destruct_FairHitPointSetDraw);
      instance.SetStreamerFunc(&streamer_FairHitPointSetDraw);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairHitPointSetDraw*)
   {
      return GenerateInitInstanceLocal((::FairHitPointSetDraw*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairHitPointSetDraw*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCPointDraw(void *p = 0);
   static void *newArray_FairMCPointDraw(Long_t size, void *p);
   static void delete_FairMCPointDraw(void *p);
   static void deleteArray_FairMCPointDraw(void *p);
   static void destruct_FairMCPointDraw(void *p);
   static void streamer_FairMCPointDraw(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCPointDraw*)
   {
      ::FairMCPointDraw *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCPointDraw >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCPointDraw", ::FairMCPointDraw::Class_Version(), "invalid", 679,
                  typeid(::FairMCPointDraw), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCPointDraw::Dictionary, isa_proxy, 16,
                  sizeof(::FairMCPointDraw) );
      instance.SetNew(&new_FairMCPointDraw);
      instance.SetNewArray(&newArray_FairMCPointDraw);
      instance.SetDelete(&delete_FairMCPointDraw);
      instance.SetDeleteArray(&deleteArray_FairMCPointDraw);
      instance.SetDestructor(&destruct_FairMCPointDraw);
      instance.SetStreamerFunc(&streamer_FairMCPointDraw);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCPointDraw*)
   {
      return GenerateInitInstanceLocal((::FairMCPointDraw*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCPointDraw*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTimeStampPointDraw(void *p = 0);
   static void *newArray_FairTimeStampPointDraw(Long_t size, void *p);
   static void delete_FairTimeStampPointDraw(void *p);
   static void deleteArray_FairTimeStampPointDraw(void *p);
   static void destruct_FairTimeStampPointDraw(void *p);
   static void streamer_FairTimeStampPointDraw(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTimeStampPointDraw*)
   {
      ::FairTimeStampPointDraw *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTimeStampPointDraw >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTimeStampPointDraw", ::FairTimeStampPointDraw::Class_Version(), "invalid", 803,
                  typeid(::FairTimeStampPointDraw), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTimeStampPointDraw::Dictionary, isa_proxy, 16,
                  sizeof(::FairTimeStampPointDraw) );
      instance.SetNew(&new_FairTimeStampPointDraw);
      instance.SetNewArray(&newArray_FairTimeStampPointDraw);
      instance.SetDelete(&delete_FairTimeStampPointDraw);
      instance.SetDeleteArray(&deleteArray_FairTimeStampPointDraw);
      instance.SetDestructor(&destruct_FairTimeStampPointDraw);
      instance.SetStreamerFunc(&streamer_FairTimeStampPointDraw);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTimeStampPointDraw*)
   {
      return GenerateInitInstanceLocal((::FairTimeStampPointDraw*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTimeStampPointDraw*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairEventManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairEventManager::Class_Name()
{
   return "FairEventManager";
}

//______________________________________________________________________________
const char *FairEventManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairEventManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairEventManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairEventManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCTracks::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCTracks::Class_Name()
{
   return "FairMCTracks";
}

//______________________________________________________________________________
const char *FairMCTracks::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCTracks*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCTracks::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCTracks*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCTracks::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCTracks*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCTracks::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCTracks*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCTracksEditor::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCTracksEditor::Class_Name()
{
   return "FairMCTracksEditor";
}

//______________________________________________________________________________
const char *FairMCTracksEditor::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCTracksEditor*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCTracksEditor::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCTracksEditor*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCTracksEditor::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCTracksEditor*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCTracksEditor::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCTracksEditor*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairEventManagerEditor::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairEventManagerEditor::Class_Name()
{
   return "FairEventManagerEditor";
}

//______________________________________________________________________________
const char *FairEventManagerEditor::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventManagerEditor*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairEventManagerEditor::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventManagerEditor*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairEventManagerEditor::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventManagerEditor*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairEventManagerEditor::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventManagerEditor*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairBoxSetDraw::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairBoxSetDraw::Class_Name()
{
   return "FairBoxSetDraw";
}

//______________________________________________________________________________
const char *FairBoxSetDraw::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSetDraw*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairBoxSetDraw::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSetDraw*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairBoxSetDraw::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSetDraw*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairBoxSetDraw::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSetDraw*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairPointSetDraw::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairPointSetDraw::Class_Name()
{
   return "FairPointSetDraw";
}

//______________________________________________________________________________
const char *FairPointSetDraw::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairPointSetDraw*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairPointSetDraw::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairPointSetDraw*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairPointSetDraw::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairPointSetDraw*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairPointSetDraw::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairPointSetDraw*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairHitDraw::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairHitDraw::Class_Name()
{
   return "FairHitDraw";
}

//______________________________________________________________________________
const char *FairHitDraw::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairHitDraw*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairHitDraw::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairHitDraw*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairHitDraw::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairHitDraw*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairHitDraw::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairHitDraw*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairBoxSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairBoxSet::Class_Name()
{
   return "FairBoxSet";
}

//______________________________________________________________________________
const char *FairBoxSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairBoxSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairBoxSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairBoxSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairBoxSetEditor::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairBoxSetEditor::Class_Name()
{
   return "FairBoxSetEditor";
}

//______________________________________________________________________________
const char *FairBoxSetEditor::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSetEditor*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairBoxSetEditor::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSetEditor*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairBoxSetEditor::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSetEditor*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairBoxSetEditor::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBoxSetEditor*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairHitPointSetDraw::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairHitPointSetDraw::Class_Name()
{
   return "FairHitPointSetDraw";
}

//______________________________________________________________________________
const char *FairHitPointSetDraw::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairHitPointSetDraw*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairHitPointSetDraw::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairHitPointSetDraw*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairHitPointSetDraw::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairHitPointSetDraw*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairHitPointSetDraw::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairHitPointSetDraw*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCPointDraw::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCPointDraw::Class_Name()
{
   return "FairMCPointDraw";
}

//______________________________________________________________________________
const char *FairMCPointDraw::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCPointDraw*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCPointDraw::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCPointDraw*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCPointDraw::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCPointDraw*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCPointDraw::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCPointDraw*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTimeStampPointDraw::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTimeStampPointDraw::Class_Name()
{
   return "FairTimeStampPointDraw";
}

//______________________________________________________________________________
const char *FairTimeStampPointDraw::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTimeStampPointDraw*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTimeStampPointDraw::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTimeStampPointDraw*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTimeStampPointDraw::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTimeStampPointDraw*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTimeStampPointDraw::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTimeStampPointDraw*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairEventManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairEventManager.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TEveEventManager::Streamer(R__b);
      R__b >> fAxesPhi;
      R__b >> fAxesRho;
      R__b.CheckByteCount(R__s, R__c, FairEventManager::IsA());
   } else {
      R__c = R__b.WriteVersion(FairEventManager::IsA(), kTRUE);
      TEveEventManager::Streamer(R__b);
      R__b << fAxesPhi;
      R__b << fAxesRho;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairEventManager(void *p) {
      return  p ? new(p) ::FairEventManager : new ::FairEventManager;
   }
   static void *newArray_FairEventManager(Long_t nElements, void *p) {
      return p ? new(p) ::FairEventManager[nElements] : new ::FairEventManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairEventManager(void *p) {
      delete ((::FairEventManager*)p);
   }
   static void deleteArray_FairEventManager(void *p) {
      delete [] ((::FairEventManager*)p);
   }
   static void destruct_FairEventManager(void *p) {
      typedef ::FairEventManager current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairEventManager(TBuffer &buf, void *obj) {
      ((::FairEventManager*)obj)->::FairEventManager::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairEventManager

//______________________________________________________________________________
void FairMCTracks::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCTracks.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairTask::Streamer(R__b);
      R__b >> fTrPr;
      R__b >> fEveTrList;
      R__b >> MinEnergyLimit;
      R__b >> MaxEnergyLimit;
      R__b >> PEnergy;
      R__b.CheckByteCount(R__s, R__c, FairMCTracks::IsA());
   } else {
      R__c = R__b.WriteVersion(FairMCTracks::IsA(), kTRUE);
      FairTask::Streamer(R__b);
      R__b << fTrPr;
      R__b << fEveTrList;
      R__b << MinEnergyLimit;
      R__b << MaxEnergyLimit;
      R__b << PEnergy;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCTracks(void *p) {
      return  p ? new(p) ::FairMCTracks : new ::FairMCTracks;
   }
   static void *newArray_FairMCTracks(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCTracks[nElements] : new ::FairMCTracks[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCTracks(void *p) {
      delete ((::FairMCTracks*)p);
   }
   static void deleteArray_FairMCTracks(void *p) {
      delete [] ((::FairMCTracks*)p);
   }
   static void destruct_FairMCTracks(void *p) {
      typedef ::FairMCTracks current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairMCTracks(TBuffer &buf, void *obj) {
      ((::FairMCTracks*)obj)->::FairMCTracks::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairMCTracks

//______________________________________________________________________________
void FairMCTracksEditor::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCTracksEditor.

   TGedFrame::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCTracksEditor(void *p) {
      return  p ? new(p) ::FairMCTracksEditor : new ::FairMCTracksEditor;
   }
   static void *newArray_FairMCTracksEditor(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCTracksEditor[nElements] : new ::FairMCTracksEditor[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCTracksEditor(void *p) {
      delete ((::FairMCTracksEditor*)p);
   }
   static void deleteArray_FairMCTracksEditor(void *p) {
      delete [] ((::FairMCTracksEditor*)p);
   }
   static void destruct_FairMCTracksEditor(void *p) {
      typedef ::FairMCTracksEditor current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairMCTracksEditor(TBuffer &buf, void *obj) {
      ((::FairMCTracksEditor*)obj)->::FairMCTracksEditor::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairMCTracksEditor

//______________________________________________________________________________
void FairEventManagerEditor::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairEventManagerEditor.

   TGedFrame::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairEventManagerEditor(void *p) {
      return  p ? new(p) ::FairEventManagerEditor : new ::FairEventManagerEditor;
   }
   static void *newArray_FairEventManagerEditor(Long_t nElements, void *p) {
      return p ? new(p) ::FairEventManagerEditor[nElements] : new ::FairEventManagerEditor[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairEventManagerEditor(void *p) {
      delete ((::FairEventManagerEditor*)p);
   }
   static void deleteArray_FairEventManagerEditor(void *p) {
      delete [] ((::FairEventManagerEditor*)p);
   }
   static void destruct_FairEventManagerEditor(void *p) {
      typedef ::FairEventManagerEditor current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairEventManagerEditor(TBuffer &buf, void *obj) {
      ((::FairEventManagerEditor*)obj)->::FairEventManagerEditor::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairEventManagerEditor

//______________________________________________________________________________
void FairBoxSetDraw::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairBoxSetDraw.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairTask::Streamer(R__b);
      R__b >> fVerbose;
      R__b >> fManager;
      R__b >> fX;
      R__b >> fY;
      R__b >> fZ;
      R__b >> fTimeWindowPlus;
      R__b >> fTimeWindowMinus;
      R__b >> fStartTime;
      R__b >> fUseEventTime;
      R__b >> fStartFunctor;
      R__b >> fStopFunctor;
      R__b.CheckByteCount(R__s, R__c, FairBoxSetDraw::IsA());
   } else {
      R__c = R__b.WriteVersion(FairBoxSetDraw::IsA(), kTRUE);
      FairTask::Streamer(R__b);
      R__b << fVerbose;
      R__b << fManager;
      R__b << fX;
      R__b << fY;
      R__b << fZ;
      R__b << fTimeWindowPlus;
      R__b << fTimeWindowMinus;
      R__b << fStartTime;
      R__b << fUseEventTime;
      R__b << fStartFunctor;
      R__b << fStopFunctor;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairBoxSetDraw(void *p) {
      delete ((::FairBoxSetDraw*)p);
   }
   static void deleteArray_FairBoxSetDraw(void *p) {
      delete [] ((::FairBoxSetDraw*)p);
   }
   static void destruct_FairBoxSetDraw(void *p) {
      typedef ::FairBoxSetDraw current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairBoxSetDraw(TBuffer &buf, void *obj) {
      ((::FairBoxSetDraw*)obj)->::FairBoxSetDraw::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairBoxSetDraw

//______________________________________________________________________________
void FairPointSetDraw::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairPointSetDraw.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairTask::Streamer(R__b);
      R__b >> fVerbose;
      R__b.CheckByteCount(R__s, R__c, FairPointSetDraw::IsA());
   } else {
      R__c = R__b.WriteVersion(FairPointSetDraw::IsA(), kTRUE);
      FairTask::Streamer(R__b);
      R__b << fVerbose;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairPointSetDraw(void *p) {
      delete ((::FairPointSetDraw*)p);
   }
   static void deleteArray_FairPointSetDraw(void *p) {
      delete [] ((::FairPointSetDraw*)p);
   }
   static void destruct_FairPointSetDraw(void *p) {
      typedef ::FairPointSetDraw current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairPointSetDraw(TBuffer &buf, void *obj) {
      ((::FairPointSetDraw*)obj)->::FairPointSetDraw::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairPointSetDraw

//______________________________________________________________________________
void FairHitDraw::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairHitDraw.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairBoxSetDraw::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, FairHitDraw::IsA());
   } else {
      R__c = R__b.WriteVersion(FairHitDraw::IsA(), kTRUE);
      FairBoxSetDraw::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairHitDraw(void *p) {
      return  p ? new(p) ::FairHitDraw : new ::FairHitDraw;
   }
   static void *newArray_FairHitDraw(Long_t nElements, void *p) {
      return p ? new(p) ::FairHitDraw[nElements] : new ::FairHitDraw[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairHitDraw(void *p) {
      delete ((::FairHitDraw*)p);
   }
   static void deleteArray_FairHitDraw(void *p) {
      delete [] ((::FairHitDraw*)p);
   }
   static void destruct_FairHitDraw(void *p) {
      typedef ::FairHitDraw current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairHitDraw(TBuffer &buf, void *obj) {
      ((::FairHitDraw*)obj)->::FairHitDraw::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairHitDraw

//______________________________________________________________________________
void FairBoxSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairBoxSet.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TEveBoxSet::Streamer(R__b);
      R__b >> fDraw;
      R__b.CheckByteCount(R__s, R__c, FairBoxSet::IsA());
   } else {
      R__c = R__b.WriteVersion(FairBoxSet::IsA(), kTRUE);
      TEveBoxSet::Streamer(R__b);
      R__b << fDraw;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairBoxSet(void *p) {
      delete ((::FairBoxSet*)p);
   }
   static void deleteArray_FairBoxSet(void *p) {
      delete [] ((::FairBoxSet*)p);
   }
   static void destruct_FairBoxSet(void *p) {
      typedef ::FairBoxSet current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairBoxSet(TBuffer &buf, void *obj) {
      ((::FairBoxSet*)obj)->::FairBoxSet::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairBoxSet

//______________________________________________________________________________
void FairBoxSetEditor::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairBoxSetEditor.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TGedFrame::Streamer(R__b);
      R__b >> fInfoFrame;
      R__b >> fTimeWindowPlus;
      R__b >> fTimeWindowMinus;
      R__b >> fObject;
      R__b >> fM;
      R__b.CheckByteCount(R__s, R__c, FairBoxSetEditor::IsA());
   } else {
      R__c = R__b.WriteVersion(FairBoxSetEditor::IsA(), kTRUE);
      TGedFrame::Streamer(R__b);
      R__b << fInfoFrame;
      R__b << fTimeWindowPlus;
      R__b << fTimeWindowMinus;
      R__b << fObject;
      R__b << fM;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairBoxSetEditor(void *p) {
      return  p ? new(p) ::FairBoxSetEditor : new ::FairBoxSetEditor;
   }
   static void *newArray_FairBoxSetEditor(Long_t nElements, void *p) {
      return p ? new(p) ::FairBoxSetEditor[nElements] : new ::FairBoxSetEditor[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairBoxSetEditor(void *p) {
      delete ((::FairBoxSetEditor*)p);
   }
   static void deleteArray_FairBoxSetEditor(void *p) {
      delete [] ((::FairBoxSetEditor*)p);
   }
   static void destruct_FairBoxSetEditor(void *p) {
      typedef ::FairBoxSetEditor current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairBoxSetEditor(TBuffer &buf, void *obj) {
      ((::FairBoxSetEditor*)obj)->::FairBoxSetEditor::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairBoxSetEditor

//______________________________________________________________________________
void FairHitPointSetDraw::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairHitPointSetDraw.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairPointSetDraw::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, FairHitPointSetDraw::IsA());
   } else {
      R__c = R__b.WriteVersion(FairHitPointSetDraw::IsA(), kTRUE);
      FairPointSetDraw::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairHitPointSetDraw(void *p) {
      return  p ? new(p) ::FairHitPointSetDraw : new ::FairHitPointSetDraw;
   }
   static void *newArray_FairHitPointSetDraw(Long_t nElements, void *p) {
      return p ? new(p) ::FairHitPointSetDraw[nElements] : new ::FairHitPointSetDraw[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairHitPointSetDraw(void *p) {
      delete ((::FairHitPointSetDraw*)p);
   }
   static void deleteArray_FairHitPointSetDraw(void *p) {
      delete [] ((::FairHitPointSetDraw*)p);
   }
   static void destruct_FairHitPointSetDraw(void *p) {
      typedef ::FairHitPointSetDraw current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairHitPointSetDraw(TBuffer &buf, void *obj) {
      ((::FairHitPointSetDraw*)obj)->::FairHitPointSetDraw::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairHitPointSetDraw

//______________________________________________________________________________
void FairMCPointDraw::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCPointDraw.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairPointSetDraw::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, FairMCPointDraw::IsA());
   } else {
      R__c = R__b.WriteVersion(FairMCPointDraw::IsA(), kTRUE);
      FairPointSetDraw::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCPointDraw(void *p) {
      return  p ? new(p) ::FairMCPointDraw : new ::FairMCPointDraw;
   }
   static void *newArray_FairMCPointDraw(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCPointDraw[nElements] : new ::FairMCPointDraw[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCPointDraw(void *p) {
      delete ((::FairMCPointDraw*)p);
   }
   static void deleteArray_FairMCPointDraw(void *p) {
      delete [] ((::FairMCPointDraw*)p);
   }
   static void destruct_FairMCPointDraw(void *p) {
      typedef ::FairMCPointDraw current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairMCPointDraw(TBuffer &buf, void *obj) {
      ((::FairMCPointDraw*)obj)->::FairMCPointDraw::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairMCPointDraw

//______________________________________________________________________________
void FairTimeStampPointDraw::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTimeStampPointDraw.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairBoxSetDraw::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, FairTimeStampPointDraw::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTimeStampPointDraw::IsA(), kTRUE);
      FairBoxSetDraw::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTimeStampPointDraw(void *p) {
      return  p ? new(p) ::FairTimeStampPointDraw : new ::FairTimeStampPointDraw;
   }
   static void *newArray_FairTimeStampPointDraw(Long_t nElements, void *p) {
      return p ? new(p) ::FairTimeStampPointDraw[nElements] : new ::FairTimeStampPointDraw[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTimeStampPointDraw(void *p) {
      delete ((::FairTimeStampPointDraw*)p);
   }
   static void deleteArray_FairTimeStampPointDraw(void *p) {
      delete [] ((::FairTimeStampPointDraw*)p);
   }
   static void destruct_FairTimeStampPointDraw(void *p) {
      typedef ::FairTimeStampPointDraw current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTimeStampPointDraw(TBuffer &buf, void *obj) {
      ((::FairTimeStampPointDraw*)obj)->::FairTimeStampPointDraw::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTimeStampPointDraw

namespace {
  void TriggerDictionaryInitialization_G__EventDisplayDict_Impl() {
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
"/Users/turany/development/FairRoot/trackbase",
"/Users/turany/development/FairRoot/geane",
"/Users/turany/development/FairRoot/eventdisplay",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/TGeant3",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/eventdisplay/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__EventDisplayDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairEventManager;
class FairMCTracks;
class __attribute__((annotate(R"ATTRDUMP(Specialization of TGedEditor for proper update propagation to TEveManager.)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Specialization of TGedEditor for proper update propagation to TEveManager.)ATTRDUMP"))) FairMCTracksEditor;
class __attribute__((annotate(R"ATTRDUMP(Specialization of TGedEditor for proper update propagation to TEveManager.)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(Specialization of TGedEditor for proper update propagation to TEveManager.)ATTRDUMP"))) FairEventManagerEditor;
class __attribute__((annotate("$clingAutoload$FairBoxSetDraw.h")))  FairBoxSetDraw;
class FairPointSetDraw;
class FairHitDraw;
class FairBoxSet;
class FairBoxSetEditor;
class FairHitPointSetDraw;
class FairMCPointDraw;
class FairTimeStampPointDraw;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__EventDisplayDict dictionary payload"

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
/**
* class for event management and navigation.
* 06.12.07 M.Al-Turany
*/
#ifndef FairEventManager_H
#define FairEventManager_H

#include "TEveEventManager.h"           // for TEveEventManager

#include "FairRunAna.h"                 // for FairRunAna

#include "Rtypes.h"                     // for Float_t, Int_t, Bool_t, etc
#include "TEveViewer.h"
#include "TEveScene.h"
#include "TEveProjectionAxes.h"
#include "TEveProjectionManager.h"

class FairRootManager; //does not work with streamer, reason unclear
class FairTask;
class TGListTreeItem;

class FairEventManager : public TEveEventManager
{
  public:
    static FairEventManager* Instance();
    FairEventManager();
    virtual ~FairEventManager();
    virtual void Open();
    virtual void GotoEvent(Int_t event); // *MENU*
    virtual void NextEvent();   // *MENU*
    virtual void PrevEvent();   // *MENU*
    virtual void Close();
    virtual void DisplaySettings();       //  *Menu*
    virtual Int_t Color(Int_t pdg);
    void AddTask(FairTask* t) {fRunAna->AddTask(t);}
    virtual void Init( Int_t visopt = 1, Int_t vislvl = 3, Int_t maxvisnds = 10000);
    virtual Int_t GetCurrentEvent() {return fEntry;}
    virtual void SetPriOnly(Bool_t Pri) {fPriOnly=Pri;}
    virtual Bool_t IsPriOnly() {return fPriOnly;}
    virtual void SelectPDG(Int_t PDG) {fCurrentPDG= PDG;}
    virtual Int_t GetCurrentPDG() {return fCurrentPDG;}
    virtual void SetMaxEnergy( Float_t max) {fMaxEnergy = max;}
    virtual void SetMinEnergy( Float_t min) {fMinEnergy = min;}
    virtual void SetEvtMaxEnergy( Float_t max) {fEvtMaxEnergy = max;}
    virtual void SetEvtMinEnergy( Float_t min) {fEvtMinEnergy = min;}
    virtual Float_t GetEvtMaxEnergy() {return fEvtMaxEnergy ;}
    virtual Float_t GetEvtMinEnergy() {return fEvtMinEnergy ;}
    virtual Float_t GetMaxEnergy() {return fMaxEnergy;}
    virtual Float_t GetMinEnergy() {return fMinEnergy;}
    virtual void SetRPhiPlane(Double_t a, Double_t b, Double_t c, Double_t d);
    virtual void SetRhoZPlane(Double_t a, Double_t b, Double_t c, Double_t d);
    void UpdateEditor();
    virtual void AddParticlesToPdgDataBase(Int_t pdg=0);
    ClassDef(FairEventManager,1);
  protected:
    TEveViewer* GetRPhiView() const {return fRPhiView;};
    TEveViewer *GetRhoZView() const {return fRhoZView;};
    TEveViewer *GetMultiView() const {return fMultiView;};
    TEveViewer *GetMultiRPhiView() const { return fMultiRPhiView;};
    TEveViewer *GetMultiRhoZView() const {return fMultiRhoZView;};
    TEveScene* GetRhoZScene() const {return fRhoZScene;};
    TEveScene* GetRPhiScene() const {return fRPhiScene;};
    TEveProjectionManager* GetRhoZProjManager() const {return fRhoZProjManager;};
    TEveProjectionManager* GetRPhiProjManager() const {return fRPhiProjManager;};
    TEveProjectionAxes *GetRPhiAxes() const { return fAxesPhi;};
    TEveProjectionAxes *GetRhoZAxes() const {return fAxesRho;};
  private:
    FairRootManager* fRootManager; //!
    Int_t fEntry;                 //!
    FairRunAna* fRunAna;          //!
    TGListTreeItem*  fEvent;     //!
    Bool_t fPriOnly;             //!
    Int_t fCurrentPDG;           //!
    Float_t fMinEnergy;         //!
    Float_t fMaxEnergy;         //!
    Float_t fEvtMinEnergy;         //!
    Float_t fEvtMaxEnergy;         //!
    Double_t fRPhiPlane[4];			//!
    Double_t fRhoZPlane[4];	//!
    TEveViewer *fRPhiView;	//!
    TEveViewer *fRhoZView;	//!
    TEveViewer *fMultiView;	//!
    TEveViewer *fMultiRPhiView;	//!
    TEveViewer *fMultiRhoZView;	//!
    TEveScene *fRPhiScene; //!
    TEveScene *fRhoZScene;//!
    TEveProjectionManager *fRPhiProjManager;	//!
    TEveProjectionManager *fRhoZProjManager;	//!
    TEveProjectionAxes *fAxesPhi;
    TEveProjectionAxes *fAxesRho;

    static FairEventManager*    fgRinstance; //!
    FairEventManager(const FairEventManager&);
    FairEventManager& operator=(const FairEventManager&);
    void SetViewers(TEveViewer *RPhi, TEveViewer *RhoZ);
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
// -----                      FairMCTracks header file                 -----
// -----                Created 10/12/07  by M. Al-Turany              -----
// -------------------------------------------------------------------------


/** FairMCTracks
 * @author M. Al-Turany
 * @since 10.12.07
 *   MVD event display object
 **
 **/

#ifndef FAIRMCTRACKS_H
#define FAIRMCTRACKS_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for Double_t, etc
#include "TEveTrackPropagator.h"        // IWYU pragma: keep needed by cint
#include "TString.h"                    // for TString

class FairEventManager;
class TClonesArray;
class TEveTrackList;
class TObjArray;
class TParticle;

class FairMCTracks : public FairTask
{

  public:

    /** Default constructor **/
    FairMCTracks();


    /** Standard constructor
    *@param name        Name of task
    *@param iVerbose    Verbosity level
    **/
    FairMCTracks(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FairMCTracks();

    /** Set verbosity level. For this task and all of the subtasks. **/
    void SetVerbose(Int_t iVerbose) {fVerbose = iVerbose;}
    /** Executed task **/
    virtual void Exec(Option_t* option);
    virtual InitStatus Init();
    virtual void SetParContainers();

    /** Action after each event**/
    virtual void Finish();
    void Reset();
    TEveTrackList* GetTrGroup(TParticle* P);

  protected:


    TClonesArray*  fTrackList;  //!
    TEveTrackPropagator* fTrPr;
    FairEventManager* fEventManager;  //!
    TObjArray* fEveTrList;
    TString fEvent; //!
    TEveTrackList* fTrList;  //!
    //TEveElementList *fTrackCont;

    Double_t MinEnergyLimit;
    Double_t MaxEnergyLimit;
    Double_t PEnergy;

  private:
    FairMCTracks(const FairMCTracks&);
    FairMCTracks& operator=(const FairMCTracks&);

    ClassDef(FairMCTracks,1);

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
// -----                       FairEventManagerEditor                  -----
// -----                  Created 16/12/07  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#ifndef ROOT_FAIREVENTMANAGEREDITOR
#define ROOT_FAIREVENTMANAGEREDITOR

#include "TGedFrame.h"                  // for TGedFrame

#include "GuiTypes.h"                   // for Pixel_t
#include "Rtypes.h"                     // for ClassDef
#include "TGFrame.h"                    // for EFrameType::kChildFrame

class FairEventManager;
class TEveGValuator;
class TGCheckButton;
class TGLabel;
class TGNumberEntry;
class TGWindow;
class TObject;

class FairEventManagerEditor : public TGedFrame
{
    FairEventManagerEditor(const FairEventManagerEditor&);            // Not implemented
    FairEventManagerEditor& operator=(const FairEventManagerEditor&); // Not implemented

  protected:
    TObject* fObject;
    FairEventManager*  fManager;
    TGNumberEntry*  fCurrentEvent, *fCurrentPDG;
    TGCheckButton*  fVizPri;
    TEveGValuator* fMinEnergy ,*fMaxEnergy;
    TGLabel* fEventTime;
  public:
    FairEventManagerEditor(const TGWindow* p=0, Int_t width=170, Int_t height=30,
                           UInt_t options = kChildFrame, Pixel_t back=GetDefaultFrameBackground());
    virtual ~FairEventManagerEditor() {}
    void SetModel( TObject* obj);
    virtual void SelectEvent();
    virtual void SelectPDG();
    void DoVizPri();
    virtual void MaxEnergy();
    virtual void MinEnergy();
    virtual void Init();

    ClassDef(FairEventManagerEditor, 0); // Specialization of TGedEditor for proper update propagation to TEveManager.
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef ROOT_FAIREMCTRACKSEDITOR
#define ROOT_FAIREMCTRACKSEDITOR

#include "TGedFrame.h"                  // for TGedFrame

#include "GuiTypes.h"                   // for Pixel_t
#include "Rtypes.h"                     // for FairMCTracksEditor::Class, etc
#include "TGFrame.h"                    // for EFrameType::kChildFrame

class FairEventManager;
class TGWindow;
class TObject;

class FairMCTracksEditor : public TGedFrame
{
    FairMCTracksEditor(const FairMCTracksEditor&);            // Not implemented
    FairMCTracksEditor& operator=(const FairMCTracksEditor&); // Not implemented

  protected:
    TObject* fObject;
    FairEventManager*  fManager;
  public:
    FairMCTracksEditor(const TGWindow* p=0, Int_t width=170, Int_t height=30,
                       UInt_t options = kChildFrame, Pixel_t back=GetDefaultFrameBackground());
    virtual ~FairMCTracksEditor() {}

    virtual void SetModel( TObject* obj);


    ClassDef(FairMCTracksEditor, 0); // Specialization of TGedEditor for proper update propagation to TEveManager.
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
// -----              FairBoxSet header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------


/** FairBoxSet
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *   One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an input
 *   to place the points.
 *   If one wants to change the color of the points one has to overwrite the method GetValue. This method takes a TObject and
 *   an integer and translates this into an integer as input for the EveBoxSet method DigitValue
 **
 **/

#ifndef FAIRBOXSET_H
#define FAIRBOXSET_H

#include "TEveBoxSet.h"                 // for TEveBoxSet

#include "FairBoxSetDraw.h"             // for FairBoxSetDraw

#include "Rtypes.h"                     // for Double_t, FairBoxSet::Class, etc


class FairBoxSet : public TEveBoxSet
{

  public:

    /** Standard constructor
       **/
    FairBoxSet(FairBoxSetDraw* drawer, const char* name = "FairBoxSet", const char* t = "");

    void SetTimeWindowPlus(Double_t time) {fDraw->SetTimeWindowPlus(time);}
    void SetTimeWindowMinus(Double_t time) {fDraw->SetTimeWindowMinus(time);}

    Double_t GetTimeWindowPlus() {return fDraw->GetTimeWindowPlus();}
    Double_t GetTimeWindowMinus() {return fDraw->GetTimeWindowMinus();}


    /** Destructor **/
    virtual ~FairBoxSet() {};



  protected:

  private:
    FairBoxSetDraw* fDraw;

    FairBoxSet(const FairBoxSet&);
    FairBoxSet operator=(const FairBoxSet&);

    ClassDef(FairBoxSet,1);

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
// -----              FairBoxSetDraw header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------


/** FairBoxSetDraw
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *   One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an input
 *   to place the points.
 *   If one wants to change the color of the points one has to overwrite the method GetValue. This method takes a TObject and
 *   an integer and translates this into an integer as input for the EveBoxSet method DigitValue
 **
 **/

#ifndef FAIRBOXSETDRAW_H
#define FAIRBOXSETDRAW_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "FairTSBufferFunctional.h"     // IWYU pragma: keep needed for cint

#include "Rtypes.h"                     // for Double_t, Int_t, Bool_t, etc

class FairBoxSet;
class TObject;
class TVector3;
class TClonesArray;
class FairEventManager;
class FairRootManager;

class FairBoxSetDraw : public FairTask
{

  public:

    /** Default constructor **/
    FairBoxSetDraw();


    /** Standard constructor
    *@param name        Name of task
    *@param iVerbose    Verbosity level
    **/
    FairBoxSetDraw(const char* name, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FairBoxSetDraw();

    virtual Double_t GetTimeWindowPlus() {return fTimeWindowPlus;}
    virtual Double_t GetTimeWindowMinus() {return fTimeWindowMinus;}

    /** Set verbosity level. For this task and all of the subtasks. **/
    virtual void SetVerbose(Int_t iVerbose) {fVerbose = iVerbose;};
    virtual void SetBoxDimensions(Double_t x, Double_t y, Double_t z) {
      fX = x;
      fY = y;
      fZ = z;
    }

    virtual void SetTimeWindowMinus(Double_t val);
    virtual void SetTimeWindowPlus(Double_t val);
    virtual void SetStartTime(Double_t val) {fStartTime = val;}
    virtual void UseEventTimeAsStartTime(Bool_t val = kTRUE) {fUseEventTime = val;}

    /** Executed task **/
    virtual void Exec(Option_t* option);

    FairBoxSet* CreateBoxSet();

    void Reset();

  protected:

    Int_t   fVerbose;       //  Verbosity level
    virtual void SetParContainers() ;
    virtual InitStatus Init();
    /** Action after each event**/
    virtual void Finish();

    virtual TVector3 GetVector(TObject* obj) = 0;
    virtual Int_t GetValue(TObject* obj,Int_t i);
    virtual void AddBoxes(FairBoxSet* set, TObject* obj, Int_t i = 0);

    TClonesArray* fList; //!
    FairEventManager* fEventManager;   //!
    FairRootManager* fManager;
    FairBoxSet* fq;    //!
    Double_t fX, fY, fZ;

    Double_t fTimeWindowPlus;
    Double_t fTimeWindowMinus;
    Double_t fStartTime;
    Bool_t fUseEventTime;


  private:
    FairBoxSetDraw(const FairBoxSetDraw&);
    FairBoxSetDraw& operator=(const FairBoxSetDraw&);
    BinaryFunctor* fStartFunctor;
    BinaryFunctor* fStopFunctor;

    ClassDef(FairBoxSetDraw,1);

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
// -----              FairBoxSetEditor header file                       -----
// -----          Created 26/03/09  by T. Stockmanns                   -----
// -------------------------------------------------------------------------


/** FairBoxSetEditor
 * @author T. Stockmanns
 * @since 26.3.2009
 *   Base class to display 3D Points in Eve as a BoxSet
 *   One has to overwrite the method GetVector which takes a TObject and writes out a TVector3 which is then taken as an input
 *   to place the points.
 *   If one wants to change the color of the points one has to overwrite the method GetValue. This method takes a TObject and
 *   an integer and translates this into an integer as input for the EveBoxSet method DigitValue
 **
 **/

#ifndef FairBoxSetEditor_H
#define FairBoxSetEditor_H

#include "TGedFrame.h"                  // for TGedFrame

#include "FairBoxSet.h"                 // for FairBoxSet

#include "GuiTypes.h"                   // for Pixel_t
#include "Rtypes.h"                     // for FairBoxSetEditor::Class, etc
#include "TGFrame.h"                    // for EFrameType::kChildFrame, etc
#include "TGNumberEntry.h"              // for TGNumberEntry
#include "TObject.h"                    // for TObject

class TGWindow;

class FairBoxSetEditor : public TGedFrame
{

  public:

    FairBoxSetEditor(const TGWindow* p=0, Int_t width=170, Int_t height=30,
                     UInt_t options = kChildFrame, Pixel_t back=GetDefaultFrameBackground());
    virtual ~FairBoxSetEditor() {};

    virtual void Init();

    virtual void SetModel(TObject* obj) {
      fM = dynamic_cast<FairBoxSet*>(obj);
      if (fM) {
        fTimeWindowPlus->SetNumber(fM->GetTimeWindowPlus());
        fTimeWindowMinus->SetNumber(fM->GetTimeWindowMinus());
      }
    }

    virtual void TimeWindow();

    TGVerticalFrame* fInfoFrame;
    TGNumberEntry* fTimeWindowPlus;
    TGNumberEntry* fTimeWindowMinus;


  protected:
    TObject* fObject;
    FairBoxSet* fM;



  private:
    FairBoxSetEditor(const FairBoxSetEditor&);
    FairBoxSetEditor& operator=(const FairBoxSetEditor&);


    ClassDef(FairBoxSetEditor,2);

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
// -----                      FairPointSetDraw header file                    -----
// -----          Created 10/12/07  by M. Al-Turany                    -----
// -------------------------------------------------------------------------


/** FairPointSetDraw
 * @author M. Al-Turany
 * @since 03.01.08
 *   Task to display MC points
 **
 **/

#ifndef FAIRPOINTSETDRAW_H
#define FAIRPOINTSETDRAW_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for Int_t, Color_t, etc

class FairEventManager;
class TClonesArray;
class TEvePointSet;
class TObject;
class TVector3;

class FairPointSetDraw : public FairTask
{

  public:

    /** Default constructor **/
    FairPointSetDraw();


    /** Standard constructor
    *@param name        Name of task
    *@param iVerbose    Verbosity level
    **/
    FairPointSetDraw(const char* name, Color_t color ,Style_t mstyle, Int_t iVerbose = 1);

    /** Destructor **/
    virtual ~FairPointSetDraw();

    /** Set verbosity level. For this task and all of the subtasks. **/
    void SetVerbose(Int_t iVerbose) {fVerbose = iVerbose;};
    /** Executed task **/
    virtual void Exec(Option_t* option);
    void Reset();
  protected:

    virtual TVector3 GetVector(TObject* obj) = 0;
    virtual TObject* GetValue(TObject* obj,Int_t i);

    Int_t   fVerbose;       //  Verbosity level
    virtual void SetParContainers() ;
    virtual InitStatus Init();
    /** Action after each event**/
    virtual void Finish() ;
    TClonesArray* fPointList; //!
    FairEventManager* fEventManager;   //!
    TEvePointSet* fq;    //!
    Color_t fColor; //!
    Style_t fStyle; //!

  private:
    FairPointSetDraw(const FairPointSetDraw&);
    FairPointSetDraw& operator=(const FairPointSetDraw&);

    ClassDef(FairPointSetDraw,1);

};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCPointsDraw.h
 *
 *  Created on: Apr 17, 2009
 *      Author: stockman
 */

#ifndef FAIRMCPOINTDRAW_H_
#define FAIRMCPOINTDRAW_H_

#include "FairPointSetDraw.h"           // for FairPointSetDraw

#include "Rtypes.h"                     // for FairMCPointDraw::Class, etc

class TObject;
class TVector3;

class FairMCPointDraw: public FairPointSetDraw
{
  public:
    FairMCPointDraw();
    FairMCPointDraw(const char* name, Color_t color ,Style_t mstyle, Int_t iVerbose = 1):FairPointSetDraw(name, color, mstyle, iVerbose) {};
    virtual ~FairMCPointDraw();

  protected:
    TVector3 GetVector(TObject* obj);

    ClassDef(FairMCPointDraw,1);
};

#endif /* FAIRMCPOINTDRAW_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairHitDraw.h
 *
 *  Created on: Apr 16, 2009
 *      Author: stockman
 *
 *      Simple method to draw points derived from FairHit
 */

#ifndef FAIRHITDRAW_H_
#define FAIRHITDRAW_H_

#include "FairBoxSetDraw.h"             // for FairBoxSetDraw

#include "Rtypes.h"                     // for FairHitDraw::Class, etc
#include "TVector3.h"                   // for TVector3

class TObject;

class FairHitDraw: public FairBoxSetDraw
{
  public:
    FairHitDraw();

    /** Standard constructor
      *@param name        Name of task
      *@param iVerbose    Verbosity level
      **/
    FairHitDraw(const char* name, Int_t iVerbose = 1);

  protected:

    TVector3 GetVector(TObject* obj);

    ClassDef(FairHitDraw,1);
};

#endif /* FAIRHITDRAW_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCPointsDraw.h
 *
 *  Created on: Sep. 30, 2009
 *      Author: stockman
 */

#ifndef FAIRHITPOINTSETDRAW_H_
#define FAIRHITPOINTSETDRAW_H_

#include "FairPointSetDraw.h"           // for FairPointSetDraw

#include "Rtypes.h"                     // for FairHitPointSetDraw::Class, etc

class TObject;
class TVector3;

class FairHitPointSetDraw: public FairPointSetDraw
{
  public:
    FairHitPointSetDraw();
    FairHitPointSetDraw(const char* name, Color_t color ,Style_t mstyle, Int_t iVerbose = 1):FairPointSetDraw(name, color, mstyle, iVerbose) {};
    virtual ~FairHitPointSetDraw();

  protected:
    TVector3 GetVector(TObject* obj);

    ClassDef(FairHitPointSetDraw,1);
};

#endif /* FAIRHITPOINTSETDRAW_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTimeStampPointDraw.h
 *
 *  Created on: Feb 28, 2011
 *      Author: stockman
 */

#ifndef FAIRTIMESTAMPPOINTDRAW_H_
#define FAIRTIMESTAMPPOINTDRAW_H_

#include "FairBoxSetDraw.h"             // for FairBoxSetDraw

#include "Rtypes.h"                     // for Int_t, etc
#include "TVector3.h"                   // for TVector3

class TObject;

class FairTimeStampPointDraw : public FairBoxSetDraw
{
  public:
    FairTimeStampPointDraw();
    FairTimeStampPointDraw(const char* name, Int_t iVerbose = 1);
    virtual ~FairTimeStampPointDraw();

  private:
    virtual TVector3 GetVector(TObject* obj);
    virtual Int_t GetValue(TObject* obj,Int_t i);

    ClassDef(FairTimeStampPointDraw, 1);
};

#endif /* FAIRTIMESTAMPPOINTDRAW_H_ */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairBoxSet", payloadCode, "@",
"FairBoxSetDraw", payloadCode, "@",
"FairBoxSetEditor", payloadCode, "@",
"FairEventManager", payloadCode, "@",
"FairEventManagerEditor", payloadCode, "@",
"FairHitDraw", payloadCode, "@",
"FairHitPointSetDraw", payloadCode, "@",
"FairMCPointDraw", payloadCode, "@",
"FairMCTracks", payloadCode, "@",
"FairMCTracksEditor", payloadCode, "@",
"FairPointSetDraw", payloadCode, "@",
"FairTimeStampPointDraw", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__EventDisplayDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__EventDisplayDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__EventDisplayDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__EventDisplayDict() {
  TriggerDictionaryInitialization_G__EventDisplayDict_Impl();
}

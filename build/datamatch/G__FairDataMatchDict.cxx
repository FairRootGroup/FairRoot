// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIdatamatchdIG__FairDataMatchDict

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
#include "FairMCMatch.h"
#include "FairMCMatchCreatorTask.h"
#include "FairMCMatchLoaderTask.h"
#include "FairMCMatchSelectorTask.h"
#include "FairMCObject.h"
#include "FairMCStage.h"
#include "FairMCResult.h"
#include "FairMCEntry.h"
#include "FairMCList.h"
#include "FairMCDataCrawler.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairMCMatch(void *p = 0);
   static void *newArray_FairMCMatch(Long_t size, void *p);
   static void delete_FairMCMatch(void *p);
   static void deleteArray_FairMCMatch(void *p);
   static void destruct_FairMCMatch(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCMatch*)
   {
      ::FairMCMatch *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCMatch >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCMatch", ::FairMCMatch::Class_Version(), "invalid", 46,
                  typeid(::FairMCMatch), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCMatch::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCMatch) );
      instance.SetNew(&new_FairMCMatch);
      instance.SetNewArray(&newArray_FairMCMatch);
      instance.SetDelete(&delete_FairMCMatch);
      instance.SetDeleteArray(&deleteArray_FairMCMatch);
      instance.SetDestructor(&destruct_FairMCMatch);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCMatch*)
   {
      return GenerateInitInstanceLocal((::FairMCMatch*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCMatch*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairMCMatchCreatorTask(void *p);
   static void deleteArray_FairMCMatchCreatorTask(void *p);
   static void destruct_FairMCMatchCreatorTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCMatchCreatorTask*)
   {
      ::FairMCMatchCreatorTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCMatchCreatorTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCMatchCreatorTask", ::FairMCMatchCreatorTask::Class_Version(), "invalid", 179,
                  typeid(::FairMCMatchCreatorTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCMatchCreatorTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCMatchCreatorTask) );
      instance.SetDelete(&delete_FairMCMatchCreatorTask);
      instance.SetDeleteArray(&deleteArray_FairMCMatchCreatorTask);
      instance.SetDestructor(&destruct_FairMCMatchCreatorTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCMatchCreatorTask*)
   {
      return GenerateInitInstanceLocal((::FairMCMatchCreatorTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCMatchCreatorTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairMCMatchLoaderTask(void *p);
   static void deleteArray_FairMCMatchLoaderTask(void *p);
   static void destruct_FairMCMatchLoaderTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCMatchLoaderTask*)
   {
      ::FairMCMatchLoaderTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCMatchLoaderTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCMatchLoaderTask", ::FairMCMatchLoaderTask::Class_Version(), "invalid", 262,
                  typeid(::FairMCMatchLoaderTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCMatchLoaderTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCMatchLoaderTask) );
      instance.SetDelete(&delete_FairMCMatchLoaderTask);
      instance.SetDeleteArray(&deleteArray_FairMCMatchLoaderTask);
      instance.SetDestructor(&destruct_FairMCMatchLoaderTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCMatchLoaderTask*)
   {
      return GenerateInitInstanceLocal((::FairMCMatchLoaderTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCMatchLoaderTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCMatchSelectorTask(void *p = 0);
   static void *newArray_FairMCMatchSelectorTask(Long_t size, void *p);
   static void delete_FairMCMatchSelectorTask(void *p);
   static void deleteArray_FairMCMatchSelectorTask(void *p);
   static void destruct_FairMCMatchSelectorTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCMatchSelectorTask*)
   {
      ::FairMCMatchSelectorTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCMatchSelectorTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCMatchSelectorTask", ::FairMCMatchSelectorTask::Class_Version(), "invalid", 341,
                  typeid(::FairMCMatchSelectorTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCMatchSelectorTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCMatchSelectorTask) );
      instance.SetNew(&new_FairMCMatchSelectorTask);
      instance.SetNewArray(&newArray_FairMCMatchSelectorTask);
      instance.SetDelete(&delete_FairMCMatchSelectorTask);
      instance.SetDeleteArray(&deleteArray_FairMCMatchSelectorTask);
      instance.SetDestructor(&destruct_FairMCMatchSelectorTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCMatchSelectorTask*)
   {
      return GenerateInitInstanceLocal((::FairMCMatchSelectorTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCMatchSelectorTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCEntry(void *p = 0);
   static void *newArray_FairMCEntry(Long_t size, void *p);
   static void delete_FairMCEntry(void *p);
   static void deleteArray_FairMCEntry(void *p);
   static void destruct_FairMCEntry(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCEntry*)
   {
      ::FairMCEntry *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCEntry >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCEntry", ::FairMCEntry::Class_Version(), "FairMCEntry.h", 28,
                  typeid(::FairMCEntry), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCEntry::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCEntry) );
      instance.SetNew(&new_FairMCEntry);
      instance.SetNewArray(&newArray_FairMCEntry);
      instance.SetDelete(&delete_FairMCEntry);
      instance.SetDeleteArray(&deleteArray_FairMCEntry);
      instance.SetDestructor(&destruct_FairMCEntry);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCEntry*)
   {
      return GenerateInitInstanceLocal((::FairMCEntry*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCEntry*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCList(void *p = 0);
   static void *newArray_FairMCList(Long_t size, void *p);
   static void delete_FairMCList(void *p);
   static void deleteArray_FairMCList(void *p);
   static void destruct_FairMCList(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCList*)
   {
      ::FairMCList *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCList >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCList", ::FairMCList::Class_Version(), "invalid", 803,
                  typeid(::FairMCList), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCList::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCList) );
      instance.SetNew(&new_FairMCList);
      instance.SetNewArray(&newArray_FairMCList);
      instance.SetDelete(&delete_FairMCList);
      instance.SetDeleteArray(&deleteArray_FairMCList);
      instance.SetDestructor(&destruct_FairMCList);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCList*)
   {
      return GenerateInitInstanceLocal((::FairMCList*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCList*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCObject(void *p = 0);
   static void *newArray_FairMCObject(Long_t size, void *p);
   static void delete_FairMCObject(void *p);
   static void deleteArray_FairMCObject(void *p);
   static void destruct_FairMCObject(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCObject*)
   {
      ::FairMCObject *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCObject >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCObject", ::FairMCObject::Class_Version(), "FairMCObject.h", 31,
                  typeid(::FairMCObject), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCObject::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCObject) );
      instance.SetNew(&new_FairMCObject);
      instance.SetNewArray(&newArray_FairMCObject);
      instance.SetDelete(&delete_FairMCObject);
      instance.SetDeleteArray(&deleteArray_FairMCObject);
      instance.SetDestructor(&destruct_FairMCObject);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCObject*)
   {
      return GenerateInitInstanceLocal((::FairMCObject*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCObject*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCStage(void *p = 0);
   static void *newArray_FairMCStage(Long_t size, void *p);
   static void delete_FairMCStage(void *p);
   static void deleteArray_FairMCStage(void *p);
   static void destruct_FairMCStage(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCStage*)
   {
      ::FairMCStage *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCStage >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCStage", ::FairMCStage::Class_Version(), "FairMCStage.h", 26,
                  typeid(::FairMCStage), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCStage::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCStage) );
      instance.SetNew(&new_FairMCStage);
      instance.SetNewArray(&newArray_FairMCStage);
      instance.SetDelete(&delete_FairMCStage);
      instance.SetDeleteArray(&deleteArray_FairMCStage);
      instance.SetDestructor(&destruct_FairMCStage);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCStage*)
   {
      return GenerateInitInstanceLocal((::FairMCStage*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCStage*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCResult(void *p = 0);
   static void *newArray_FairMCResult(Long_t size, void *p);
   static void delete_FairMCResult(void *p);
   static void deleteArray_FairMCResult(void *p);
   static void destruct_FairMCResult(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCResult*)
   {
      ::FairMCResult *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCResult >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCResult", ::FairMCResult::Class_Version(), "FairMCResult.h", 27,
                  typeid(::FairMCResult), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCResult::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCResult) );
      instance.SetNew(&new_FairMCResult);
      instance.SetNewArray(&newArray_FairMCResult);
      instance.SetDelete(&delete_FairMCResult);
      instance.SetDeleteArray(&deleteArray_FairMCResult);
      instance.SetDestructor(&destruct_FairMCResult);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCResult*)
   {
      return GenerateInitInstanceLocal((::FairMCResult*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCResult*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairMCDataCrawler(void *p);
   static void deleteArray_FairMCDataCrawler(void *p);
   static void destruct_FairMCDataCrawler(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCDataCrawler*)
   {
      ::FairMCDataCrawler *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCDataCrawler >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCDataCrawler", ::FairMCDataCrawler::Class_Version(), "invalid", 872,
                  typeid(::FairMCDataCrawler), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCDataCrawler::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCDataCrawler) );
      instance.SetDelete(&delete_FairMCDataCrawler);
      instance.SetDeleteArray(&deleteArray_FairMCDataCrawler);
      instance.SetDestructor(&destruct_FairMCDataCrawler);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCDataCrawler*)
   {
      return GenerateInitInstanceLocal((::FairMCDataCrawler*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCDataCrawler*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairMCMatch::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCMatch::Class_Name()
{
   return "FairMCMatch";
}

//______________________________________________________________________________
const char *FairMCMatch::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatch*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCMatch::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatch*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCMatch::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatch*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCMatch::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatch*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCMatchCreatorTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCMatchCreatorTask::Class_Name()
{
   return "FairMCMatchCreatorTask";
}

//______________________________________________________________________________
const char *FairMCMatchCreatorTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchCreatorTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCMatchCreatorTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchCreatorTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCMatchCreatorTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchCreatorTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCMatchCreatorTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchCreatorTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCMatchLoaderTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCMatchLoaderTask::Class_Name()
{
   return "FairMCMatchLoaderTask";
}

//______________________________________________________________________________
const char *FairMCMatchLoaderTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchLoaderTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCMatchLoaderTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchLoaderTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCMatchLoaderTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchLoaderTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCMatchLoaderTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchLoaderTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCMatchSelectorTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCMatchSelectorTask::Class_Name()
{
   return "FairMCMatchSelectorTask";
}

//______________________________________________________________________________
const char *FairMCMatchSelectorTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchSelectorTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCMatchSelectorTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchSelectorTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCMatchSelectorTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchSelectorTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCMatchSelectorTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCMatchSelectorTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCEntry::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCEntry::Class_Name()
{
   return "FairMCEntry";
}

//______________________________________________________________________________
const char *FairMCEntry::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCEntry*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCEntry::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCEntry*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCEntry::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCEntry*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCEntry::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCEntry*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCList::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCList::Class_Name()
{
   return "FairMCList";
}

//______________________________________________________________________________
const char *FairMCList::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCList*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCList::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCList*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCList::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCList*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCList::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCList*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCObject::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCObject::Class_Name()
{
   return "FairMCObject";
}

//______________________________________________________________________________
const char *FairMCObject::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCObject*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCObject::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCObject*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCObject::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCObject*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCObject::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCObject*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCStage::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCStage::Class_Name()
{
   return "FairMCStage";
}

//______________________________________________________________________________
const char *FairMCStage::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCStage*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCStage::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCStage*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCStage::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCStage*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCStage::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCStage*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCResult::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCResult::Class_Name()
{
   return "FairMCResult";
}

//______________________________________________________________________________
const char *FairMCResult::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCResult*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCResult::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCResult*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCResult::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCResult*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCResult::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCResult*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCDataCrawler::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCDataCrawler::Class_Name()
{
   return "FairMCDataCrawler";
}

//______________________________________________________________________________
const char *FairMCDataCrawler::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCDataCrawler*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCDataCrawler::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCDataCrawler*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCDataCrawler::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCDataCrawler*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCDataCrawler::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCDataCrawler*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairMCMatch::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCMatch.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCMatch::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCMatch::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCMatch(void *p) {
      return  p ? new(p) ::FairMCMatch : new ::FairMCMatch;
   }
   static void *newArray_FairMCMatch(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCMatch[nElements] : new ::FairMCMatch[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCMatch(void *p) {
      delete ((::FairMCMatch*)p);
   }
   static void deleteArray_FairMCMatch(void *p) {
      delete [] ((::FairMCMatch*)p);
   }
   static void destruct_FairMCMatch(void *p) {
      typedef ::FairMCMatch current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCMatch

//______________________________________________________________________________
void FairMCMatchCreatorTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCMatchCreatorTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCMatchCreatorTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCMatchCreatorTask::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairMCMatchCreatorTask(void *p) {
      delete ((::FairMCMatchCreatorTask*)p);
   }
   static void deleteArray_FairMCMatchCreatorTask(void *p) {
      delete [] ((::FairMCMatchCreatorTask*)p);
   }
   static void destruct_FairMCMatchCreatorTask(void *p) {
      typedef ::FairMCMatchCreatorTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCMatchCreatorTask

//______________________________________________________________________________
void FairMCMatchLoaderTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCMatchLoaderTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCMatchLoaderTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCMatchLoaderTask::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairMCMatchLoaderTask(void *p) {
      delete ((::FairMCMatchLoaderTask*)p);
   }
   static void deleteArray_FairMCMatchLoaderTask(void *p) {
      delete [] ((::FairMCMatchLoaderTask*)p);
   }
   static void destruct_FairMCMatchLoaderTask(void *p) {
      typedef ::FairMCMatchLoaderTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCMatchLoaderTask

//______________________________________________________________________________
void FairMCMatchSelectorTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCMatchSelectorTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCMatchSelectorTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCMatchSelectorTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCMatchSelectorTask(void *p) {
      return  p ? new(p) ::FairMCMatchSelectorTask : new ::FairMCMatchSelectorTask;
   }
   static void *newArray_FairMCMatchSelectorTask(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCMatchSelectorTask[nElements] : new ::FairMCMatchSelectorTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCMatchSelectorTask(void *p) {
      delete ((::FairMCMatchSelectorTask*)p);
   }
   static void deleteArray_FairMCMatchSelectorTask(void *p) {
      delete [] ((::FairMCMatchSelectorTask*)p);
   }
   static void destruct_FairMCMatchSelectorTask(void *p) {
      typedef ::FairMCMatchSelectorTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCMatchSelectorTask

//______________________________________________________________________________
void FairMCEntry::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCEntry.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCEntry::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCEntry::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCEntry(void *p) {
      return  p ? new(p) ::FairMCEntry : new ::FairMCEntry;
   }
   static void *newArray_FairMCEntry(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCEntry[nElements] : new ::FairMCEntry[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCEntry(void *p) {
      delete ((::FairMCEntry*)p);
   }
   static void deleteArray_FairMCEntry(void *p) {
      delete [] ((::FairMCEntry*)p);
   }
   static void destruct_FairMCEntry(void *p) {
      typedef ::FairMCEntry current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCEntry

//______________________________________________________________________________
void FairMCList::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCList.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCList::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCList::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCList(void *p) {
      return  p ? new(p) ::FairMCList : new ::FairMCList;
   }
   static void *newArray_FairMCList(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCList[nElements] : new ::FairMCList[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCList(void *p) {
      delete ((::FairMCList*)p);
   }
   static void deleteArray_FairMCList(void *p) {
      delete [] ((::FairMCList*)p);
   }
   static void destruct_FairMCList(void *p) {
      typedef ::FairMCList current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCList

//______________________________________________________________________________
void FairMCObject::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCObject.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCObject::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCObject::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCObject(void *p) {
      return  p ? new(p) ::FairMCObject : new ::FairMCObject;
   }
   static void *newArray_FairMCObject(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCObject[nElements] : new ::FairMCObject[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCObject(void *p) {
      delete ((::FairMCObject*)p);
   }
   static void deleteArray_FairMCObject(void *p) {
      delete [] ((::FairMCObject*)p);
   }
   static void destruct_FairMCObject(void *p) {
      typedef ::FairMCObject current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCObject

//______________________________________________________________________________
void FairMCStage::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCStage.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCStage::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCStage::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCStage(void *p) {
      return  p ? new(p) ::FairMCStage : new ::FairMCStage;
   }
   static void *newArray_FairMCStage(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCStage[nElements] : new ::FairMCStage[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCStage(void *p) {
      delete ((::FairMCStage*)p);
   }
   static void deleteArray_FairMCStage(void *p) {
      delete [] ((::FairMCStage*)p);
   }
   static void destruct_FairMCStage(void *p) {
      typedef ::FairMCStage current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCStage

//______________________________________________________________________________
void FairMCResult::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCResult.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCResult::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCResult::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCResult(void *p) {
      return  p ? new(p) ::FairMCResult : new ::FairMCResult;
   }
   static void *newArray_FairMCResult(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCResult[nElements] : new ::FairMCResult[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCResult(void *p) {
      delete ((::FairMCResult*)p);
   }
   static void deleteArray_FairMCResult(void *p) {
      delete [] ((::FairMCResult*)p);
   }
   static void destruct_FairMCResult(void *p) {
      typedef ::FairMCResult current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCResult

//______________________________________________________________________________
void FairMCDataCrawler::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCDataCrawler.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCDataCrawler::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCDataCrawler::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairMCDataCrawler(void *p) {
      delete ((::FairMCDataCrawler*)p);
   }
   static void deleteArray_FairMCDataCrawler(void *p) {
      delete [] ((::FairMCDataCrawler*)p);
   }
   static void destruct_FairMCDataCrawler(void *p) {
      typedef ::FairMCDataCrawler current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCDataCrawler

namespace ROOT {
   static TClass *vectorlEpairlEintcOfloatgRsPgR_Dictionary();
   static void vectorlEpairlEintcOfloatgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEpairlEintcOfloatgRsPgR(void *p = 0);
   static void *newArray_vectorlEpairlEintcOfloatgRsPgR(Long_t size, void *p);
   static void delete_vectorlEpairlEintcOfloatgRsPgR(void *p);
   static void deleteArray_vectorlEpairlEintcOfloatgRsPgR(void *p);
   static void destruct_vectorlEpairlEintcOfloatgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<pair<int,float> >*)
   {
      vector<pair<int,float> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<pair<int,float> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<pair<int,float> >", -2, "vector", 457,
                  typeid(vector<pair<int,float> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEpairlEintcOfloatgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<pair<int,float> >) );
      instance.SetNew(&new_vectorlEpairlEintcOfloatgRsPgR);
      instance.SetNewArray(&newArray_vectorlEpairlEintcOfloatgRsPgR);
      instance.SetDelete(&delete_vectorlEpairlEintcOfloatgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEpairlEintcOfloatgRsPgR);
      instance.SetDestructor(&destruct_vectorlEpairlEintcOfloatgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<pair<int,float> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<pair<int,float> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEpairlEintcOfloatgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<pair<int,float> >*)0x0)->GetClass();
      vectorlEpairlEintcOfloatgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEpairlEintcOfloatgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEpairlEintcOfloatgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<pair<int,float> > : new vector<pair<int,float> >;
   }
   static void *newArray_vectorlEpairlEintcOfloatgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<pair<int,float> >[nElements] : new vector<pair<int,float> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEpairlEintcOfloatgRsPgR(void *p) {
      delete ((vector<pair<int,float> >*)p);
   }
   static void deleteArray_vectorlEpairlEintcOfloatgRsPgR(void *p) {
      delete [] ((vector<pair<int,float> >*)p);
   }
   static void destruct_vectorlEpairlEintcOfloatgRsPgR(void *p) {
      typedef vector<pair<int,float> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<pair<int,float> >

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = 0);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 457,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<int>*)0x0)->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete ((vector<int>*)p);
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] ((vector<int>*)p);
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<int>

namespace ROOT {
   static TClass *maplEstringcOTClonesArraymUgR_Dictionary();
   static void maplEstringcOTClonesArraymUgR_TClassManip(TClass*);
   static void *new_maplEstringcOTClonesArraymUgR(void *p = 0);
   static void *newArray_maplEstringcOTClonesArraymUgR(Long_t size, void *p);
   static void delete_maplEstringcOTClonesArraymUgR(void *p);
   static void deleteArray_maplEstringcOTClonesArraymUgR(void *p);
   static void destruct_maplEstringcOTClonesArraymUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<string,TClonesArray*>*)
   {
      map<string,TClonesArray*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<string,TClonesArray*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<string,TClonesArray*>", -2, "map", 830,
                  typeid(map<string,TClonesArray*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEstringcOTClonesArraymUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<string,TClonesArray*>) );
      instance.SetNew(&new_maplEstringcOTClonesArraymUgR);
      instance.SetNewArray(&newArray_maplEstringcOTClonesArraymUgR);
      instance.SetDelete(&delete_maplEstringcOTClonesArraymUgR);
      instance.SetDeleteArray(&deleteArray_maplEstringcOTClonesArraymUgR);
      instance.SetDestructor(&destruct_maplEstringcOTClonesArraymUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<string,TClonesArray*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<string,TClonesArray*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEstringcOTClonesArraymUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<string,TClonesArray*>*)0x0)->GetClass();
      maplEstringcOTClonesArraymUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEstringcOTClonesArraymUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEstringcOTClonesArraymUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,TClonesArray*> : new map<string,TClonesArray*>;
   }
   static void *newArray_maplEstringcOTClonesArraymUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<string,TClonesArray*>[nElements] : new map<string,TClonesArray*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEstringcOTClonesArraymUgR(void *p) {
      delete ((map<string,TClonesArray*>*)p);
   }
   static void deleteArray_maplEstringcOTClonesArraymUgR(void *p) {
      delete [] ((map<string,TClonesArray*>*)p);
   }
   static void destruct_maplEstringcOTClonesArraymUgR(void *p) {
      typedef map<string,TClonesArray*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<string,TClonesArray*>

namespace ROOT {
   static TClass *maplEintcOFairMCStagemUgR_Dictionary();
   static void maplEintcOFairMCStagemUgR_TClassManip(TClass*);
   static void *new_maplEintcOFairMCStagemUgR(void *p = 0);
   static void *newArray_maplEintcOFairMCStagemUgR(Long_t size, void *p);
   static void delete_maplEintcOFairMCStagemUgR(void *p);
   static void deleteArray_maplEintcOFairMCStagemUgR(void *p);
   static void destruct_maplEintcOFairMCStagemUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<int,FairMCStage*>*)
   {
      map<int,FairMCStage*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<int,FairMCStage*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<int,FairMCStage*>", -2, "map", 830,
                  typeid(map<int,FairMCStage*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEintcOFairMCStagemUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<int,FairMCStage*>) );
      instance.SetNew(&new_maplEintcOFairMCStagemUgR);
      instance.SetNewArray(&newArray_maplEintcOFairMCStagemUgR);
      instance.SetDelete(&delete_maplEintcOFairMCStagemUgR);
      instance.SetDeleteArray(&deleteArray_maplEintcOFairMCStagemUgR);
      instance.SetDestructor(&destruct_maplEintcOFairMCStagemUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<int,FairMCStage*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<int,FairMCStage*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEintcOFairMCStagemUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<int,FairMCStage*>*)0x0)->GetClass();
      maplEintcOFairMCStagemUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplEintcOFairMCStagemUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEintcOFairMCStagemUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,FairMCStage*> : new map<int,FairMCStage*>;
   }
   static void *newArray_maplEintcOFairMCStagemUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<int,FairMCStage*>[nElements] : new map<int,FairMCStage*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEintcOFairMCStagemUgR(void *p) {
      delete ((map<int,FairMCStage*>*)p);
   }
   static void deleteArray_maplEintcOFairMCStagemUgR(void *p) {
      delete [] ((map<int,FairMCStage*>*)p);
   }
   static void destruct_maplEintcOFairMCStagemUgR(void *p) {
      typedef map<int,FairMCStage*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<int,FairMCStage*>

namespace {
  void TriggerDictionaryInitialization_G__FairDataMatchDict_Impl() {
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
"/Users/turany/development/FairRoot/datamatch",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/datamatch/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__FairDataMatchDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairMCMatch;
class FairMCMatchCreatorTask;
class FairMCMatchLoaderTask;
class FairMCMatchSelectorTask;
class __attribute__((annotate("$clingAutoload$FairMCEntry.h")))  FairMCEntry;
class FairMCList;
class __attribute__((annotate("$clingAutoload$FairMCResult.h")))  FairMCObject;
class __attribute__((annotate("$clingAutoload$FairMCStage.h")))  FairMCStage;
class __attribute__((annotate("$clingAutoload$FairMCResult.h")))  FairMCResult;
class FairMCDataCrawler;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__FairDataMatchDict dictionary payload"

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
/*
 * FairMCMatch.h
 *
 *  Created on: Nov 23, 2009
 *      Author: stockman
 */

#ifndef FAIRMCMATCH_H_
#define FAIRMCMATCH_H_

#include "TNamed.h"                     // for TNamed

#include "FairMCEntry.h"                // for FairMCEntry
#include "FairMCResult.h"               // for FairMCResult
#include "FairMCStage.h"                // for FairMCStage
#include "FairMultiLinkedData.h"        // for FairMultiLinkedData
#include "FairRootManager.h"            // for FairRootManager

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, FairMCMatch::Class, etc
#include "TString.h"                    // for TString
#include "TClonesArray.h"

#include <iostream>                     // for ostream, cout, endl
#include <map>                          // for map, etc
#include <string>                       // for string
#include <utility>                      // for pair

class FairLink;

typedef std::map<Int_t, FairMCStage*>::iterator TListIterator;
typedef std::map<Int_t, FairMCStage*>::const_iterator TListIteratorConst;

class FairMCMatch: public TNamed
{
  public:
    FairMCMatch();
    FairMCMatch(const char* name, const char* title)
      : TNamed(name, title),
        fUltimateStage(0),
        fList(),
        fFinalStageML(),
        fVerbose(0) {
      fFinalStageML.SetPersistanceCheck(kFALSE);
    }

    virtual ~FairMCMatch();

    void AddElement(Int_t type, int index, FairLink link);
    void AddElement(Int_t sourceType, int index, Int_t targetType, int link);
    void SetElements(Int_t sourceType, int index, FairMultiLinkedData* links);
    void InitStage(Int_t type, std::string fileName, std::string branchName);
    void InitStage(std::string fileName, std::string branchName = "");
    void RemoveStage(Int_t type);
    void LoadInMCLists(TClonesArray* myLinkArray);
    void ClearMCList();

    void SetCommonWeightStages(Float_t weight);

    FairMCEntry GetEntry(Int_t type, int index);
    FairMCEntry GetEntry(FairLink link);

    FairMCResult GetMCInfo(Int_t start, Int_t stop);
    FairMCResult GetMCInfo(TString start, TString stop);
    FairMCEntry  GetMCInfoSingle(FairLink aLink, Int_t stop);
    FairMCEntry  GetMCInfoSingle(FairLink aLink, TString stop);

    int GetNMCStages() const {return fList.size();}

    FairMCStage* GetMCStage(int index) const {
      TListIteratorConst iter = fList.begin();
      for (int i = 0; i < index; i++) {
        iter++;
      }
      return (iter->second);
    }

    FairMCStage* GetMCStageType(TString branch) {
      FairRootManager* ioman = FairRootManager::Instance();
      if (ioman->GetBranchId(branch) > 0) {
        return fList[ioman->GetBranchId(branch)];
      } else {
        return 0;
      }
    }

    FairMCStage* GetMCStageType(Int_t type) {
      return fList[type];
    }

    void CreateArtificialStage(TString branchName, std::string fileName = "");
    void CreateArtificialStage(Int_t stage, std::string fileName = "", std::string branchName = "");

    FairMultiLinkedData FindLinksToStage(Int_t stage);

    bool IsTypeInList(Int_t type);

    void PrintInfo(std::ostream& out = std::cout) {out << *this;}

    friend std::ostream& operator<< (std::ostream& out, const FairMCMatch& match) {
      for (int i = 0; i < match.GetNMCStages(); i++) {
        if (match.GetMCStage(i)->GetLoaded() == kTRUE) {
          match.GetMCStage(i)->PrintInfo(out);
          out << std::endl;
        }
      }
      return out;
    }

  private:

    Int_t fUltimateStage; ///< last stage in link chain. Here all recursive operations must stop.
    std::map<Int_t, FairMCStage*> fList;
    FairMultiLinkedData fFinalStageML;
    Int_t fVerbose;

    void FindStagesPointingToLinks(FairMultiLinkedData links, Int_t stop);
    FairMultiLinkedData FindStagesPointingToLink(FairLink link);

    FairMCResult GetMCInfoForward(Int_t start, Int_t stop);
    FairMCResult GetMCInfoBackward(Int_t start, Int_t stop);
    FairMCEntry GetMCInfoForwardSingle(FairLink link, Int_t stop);
    FairMCEntry GetMCInfoBackwardSingle(FairLink link, Int_t stop, Double_t weight = 1.);

    void GetNextStage(FairMultiLinkedData& startEntry, Int_t stopStage);
    void AddToFinalStage(FairLink link, Float_t mult);
    void ClearFinalStage();

    ClassDef(FairMCMatch, 1);
};

#endif /* PNDMCMATCH_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                 FAIRMCMATCHCREATORTASK header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------


/** FAIRMCMATCHCREATORTASK.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/


#ifndef FAIRMCMATCHCREATORTASK_H
#define FAIRMCMATCHCREATORTASK_H

#include "FairTask.h"                   // for InitStatus, FairTask

#include "Rtypes.h"                     // for Bool_t, etc

#include <map>                          // for map
#include <string>                       // for string

class FairMCMatch;
class TClonesArray;

class FairMCMatchCreatorTask : public FairTask
{
  public:

    /** Default constructor **/
    FairMCMatchCreatorTask();

    /** Destructor **/
    virtual ~FairMCMatchCreatorTask();


    /** Virtual method Init **/
    virtual void SetParContainers();
    void SetPersistance(Bool_t pers) {fPersistance = pers;}
    Bool_t GetPersistance() {return fPersistance;}

    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    virtual void Finish();

    virtual void InitDataStages() = 0;

  protected:
    FairMCMatch* fMCMatch;

  private:

    std::map<std::string, TClonesArray*> fBranches;
    Bool_t fPersistance;
    TClonesArray* fMCLink;//->
    Int_t fEventNr;

    InitStatus InitBranches();

    void Register();

    void Reset();

    void ProduceHits();

    FairMCMatchCreatorTask(const FairMCMatchCreatorTask&);
    FairMCMatchCreatorTask& operator=(const FairMCMatchCreatorTask&);

    ClassDef(FairMCMatchCreatorTask,1);

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
// -----                 FAIRMCMATCHCREATORTASK header file             -----
// -----                  Created 20/03/07  by R.Kliemt               -----
// -------------------------------------------------------------------------


/** PNDMCMATCHCREATORTASK.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/


#ifndef FAIRMCMATCHLOADERTASK_H
#define FAIRMCMATCHLOADERTASK_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for ClassDef

class FairMCMatch;
class TClonesArray;

class FairMCMatchLoaderTask : public FairTask
{
  public:

    /** Default constructor **/
    FairMCMatchLoaderTask();

    /** Destructor **/
    virtual ~FairMCMatchLoaderTask();


    /** Virtual method Init **/
    virtual void SetParContainers();
    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    virtual void Finish();

    virtual void InitDataStages() = 0;

  protected:

    FairMCMatch* fMCMatch;

  private:

    TClonesArray* fMCLink;
    int fEventNr;

    void Register();

    void Reset();

    void ProduceHits();

    FairMCMatchLoaderTask(const FairMCMatchLoaderTask&);
    FairMCMatchLoaderTask& operator=(const FairMCMatchLoaderTask&);

    ClassDef(FairMCMatchLoaderTask,1);
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
// -----                 FAIRMCMATCHSELECTORTASK header file             -----
// -----                  Created 18/01/10  by T.Stockmanns             -----
// -------------------------------------------------------------------------


/** FAIRMCMATCHSELECTORTASK.h
 *@author T.Stockmanns <t.stockmanns@fz-juelich.de>
 **
 ** Displays all available informations for a given event
 **/


#ifndef FAIRMCMATCHSELECTORTASK_H
#define FAIRMCMATCHSELECTORTASK_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "Rtypes.h"                     // for Int_t, Float_t, etc
#include "TString.h"                    // for TString

#include <utility>                      // for pair
#include <vector>                       // for vector

class FairMCMatch;

class FairMCMatchSelectorTask : public FairTask
{
  public:

    /** Default constructor **/
    FairMCMatchSelectorTask();

    FairMCMatchSelectorTask(TString start, TString stop);

    FairMCMatchSelectorTask(Int_t start, Int_t stop);

    /** Destructor **/
    virtual ~FairMCMatchSelectorTask();


    /** Virtual method Init **/
    virtual void SetParContainers();
    virtual InitStatus Init();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    virtual void Finish();

    virtual void SetStart(Int_t type) {fStart = type;}
    virtual void SetStop(Int_t type) {fStop = type;}

    virtual void SetAllWeights(Float_t weight) {fCommonWeight = weight;}
    virtual void SetWeightStage(Int_t type, Float_t weight) {
      fStageWeights.push_back(std::pair<Int_t, Float_t>(static_cast<Int_t>(type), weight));
    }

    virtual void SetWeights();

  private:
    FairMCMatch* fMCMatch;
    Int_t fStart;
    Int_t fStop;

    TString fStartString;
    TString fStopString;

    std::vector<std::pair<Int_t, Float_t> > fStageWeights;
    Float_t fCommonWeight;

    void Register();

    void Reset();

    void ProduceHits();

    FairMCMatchSelectorTask(const FairMCMatchSelectorTask&);
    FairMCMatchSelectorTask& operator=(const FairMCMatchSelectorTask&);

    ClassDef(FairMCMatchSelectorTask,1);

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
 * FairMCStage.h
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#ifndef FAIRMCOBJECT_H_
#define FAIRMCOBJECT_H_

#include "TObject.h"                    // for TObject

#include "FairLink.h"                   // for FairLink
#include "FairMCEntry.h"                // for FairMCEntry
#include "FairMultiLinkedData.h"        // for FairMultiLinkedData

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, FairMCObject::Class, etc

#include <iostream>                     // for ostream, etc
#include <utility>                      // for pair
#include <vector>                       // for vector

class FairMCObject: public TObject
{
  public:
    FairMCObject();
    FairMCObject(Int_t type)
      : TObject(),
        fStage(),
        fStageId(type)
        {
        }	
    FairMCObject(const FairMCObject& obj)
      : TObject(obj),
        fStage(obj.GetEntryVector()), 
        fStageId(obj.GetStageId())
        {
        }
    FairMCObject(Int_t type, std::vector<FairMCEntry> stage)
      : TObject(),
        fStage(stage),
        fStageId(type) 
        {
        }

    FairMCObject& operator=(const FairMCObject& from) {
      if (this == &from) { return *this; }

      TObject::operator=(from);
      fStage=from.fStage;
      fStageId=from.fStageId;

      return *this;
    }

    virtual ~FairMCObject();

    void SetStageId(Int_t type) {fStageId = type;}

    void SetEntry(std::vector<Int_t> type, std::vector<Int_t> link, int index);
    void SetEntry(FairMultiLinkedData* data, int index);
    void SetEntry(FairMCEntry link);

    void SetStage(std::vector<FairMCEntry> stage) {fStage = stage;}
    void SetLink(FairLink link, int index);
    void AddLink(FairLink link, int index);

    FairMCEntry GetEntry(int index) const {return fStage[index];}
    FairLink  GetSingleLink(int entryIndex, int linkIndex) const {
      return fStage.at(entryIndex).GetLink(linkIndex);
    }

    Int_t GetStageId(void) const {return fStageId;}

    FairMCEntry GetMCLink(Int_t index) {return fStage.at(index);}

    int GetNEntries() const {return fStage.size();}
    int GetNLinks(int entryIndex)const {return fStage.at(entryIndex).GetNLinks();}
    std::vector<FairMCEntry> GetEntryVector() const {return fStage;}

    FairMultiLinkedData PosInList(std::pair<int, int> link);
    FairMultiLinkedData PosInList(FairLink link);

    FairMultiLinkedData GetLinksWithType(Int_t type) {
      FairMultiLinkedData result;
      for (int i = 0; i < GetNEntries(); i++) {
        result.AddLinks(GetMCLink(i).GetLinksWithType(type));
      }
      return result;
    }

    void RemoveType(Int_t type);

    virtual void ClearEntries() {fStage.clear();}

    virtual void PrintInfo(std::ostream& out = std::cout) {out << *this;}

    /*
        void operator=(const FairMCObject& obj) {
          fStageId = obj.GetStageId();
          fStage = obj.GetEntryVector();
        }
    */

    friend std::ostream& operator<< (std::ostream& out, const FairMCObject& obj) {
      std::vector<FairMCEntry> stages = obj.GetEntryVector();
      for (unsigned int i = 0; i < stages.size(); i++) {
        if (stages[i].GetNLinks() > 0) {
          out << i << ": ";
          stages[i].PrintInfo(out);
          out << std::endl;
        }
      }
      return out;
    }

  private:
    void AdoptSize(int index);
    std::vector<FairMCEntry> fStage;
    Int_t fStageId;

    ClassDef(FairMCObject, 0);
};

#endif /* PNDMCOBJECT_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCStage.h
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#ifndef FAIRMCSTAGE_H_
#define FAIRMCSTAGE_H_

#include "FairMCObject.h"               // for FairMCObject

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Bool_t, Double_t, etc

#include <iostream>                     // for ostream, basic_ostream, etc
#include <string>                       // for string, operator<<, etc

class FairMCStage: public FairMCObject
{
  public:
    FairMCStage();
    FairMCStage(Int_t id, std::string fileName, std::string branchName, Double_t weight = 1.0);

    FairMCStage(const FairMCStage& mcStage)
      : FairMCObject(mcStage),
        fBranchName(mcStage.fBranchName),
        fFileName(mcStage.fFileName),
        fWeight(mcStage.fWeight),
        fLoaded(mcStage.fLoaded),
        fFill(mcStage.fFill) {
    }

    FairMCStage& operator=(const FairMCStage& result) {

      if (this == &result) { return *this; }

      FairMCObject::operator=(result);
      fBranchName = result.fBranchName;
      fFileName = result.fFileName;
      fWeight = result.fWeight;
      fLoaded = result.fLoaded;
      fFill = result.fFill;

      return *this;
    }



    virtual ~FairMCStage();

    void SetBranchName(std::string branchName)  { fBranchName = branchName; }
    void SetFileName(std::string fileName)      { fFileName = fileName; }
    void SetWeight(Double_t weight)       { fWeight = weight; }
    void SetLoaded(Bool_t loaded)         { fLoaded = loaded; }
    void SetFill(Bool_t fill)           { fFill = fill; }

    std::string GetBranchName(void)   const {return fBranchName;}
    std::string GetFileName(void)     const {return fFileName;}
    Double_t  GetWeight(void)     const {return fWeight;}
    Bool_t    GetLoaded(void)   const {return fLoaded;}
    Bool_t    GetFill(void)     const {return fFill;}

    virtual void ClearEntries() {
      FairMCObject::ClearEntries();
      fLoaded = kFALSE;
    }

    virtual void PrintInfo(std::ostream& out) {out << *this;}

    friend std::ostream& operator<< (std::ostream& out, const FairMCStage& stage) {
      out << stage.GetStageId() << ": " << stage.GetBranchName() << " // " <<  stage.GetFileName() << std::endl; //" with weight: " << stage.GetWeight() << std::endl;
      (static_cast<FairMCObject>(stage)).PrintInfo(out);
      return out;
    }

  private:
    std::string fBranchName;
    std::string fFileName;
    Double_t fWeight;
    Bool_t fLoaded; ///< indicates if this stage was loaded already from a Link file
    Bool_t fFill; ///< indicates if a corresponding DataFile with FairLinks exists to fill this stage

    ClassDef(FairMCStage, 1);
};

#endif /* PNDMCSTAGE_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCResult.h
 *
 *  Created on: Dec 1, 2009
 *      Author: stockman
 */

#ifndef FAIRMCRESULT_H_
#define FAIRMCRESULT_H_

#include "FairMCObject.h"               // for FairMCObject

#include "FairMCEntry.h"                // for FairMCEntry

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, FairMCResult::Class, etc

#include <iostream>                     // for operator<<, ostream, etc

class FairMCResult: public FairMCObject
{
  public:
    FairMCResult();
    FairMCResult(Int_t start, Int_t stop);

    FairMCResult(const FairMCResult& result)
      : FairMCObject(result.GetStartType(), result.GetEntryVector()),
        fStartType(result.GetStartType()),
        fStopType(result.GetStopType()) {
    }


    FairMCResult& operator=(const FairMCResult& result) {

      if (this == &result) { return *this; }

      FairMCObject::operator=(result);
      fStartType = result.fStartType;
      fStopType = result.fStopType;

      return *this;
    }

    virtual ~FairMCResult();

    void SetStartType(Int_t start) {fStartType = start;}
    void SetStopType(Int_t stop) {fStopType = stop;}

    Int_t GetStartType(void) const {return fStartType;}
    Int_t GetStopType(void) const {return fStopType;}

    virtual void PrintInfo(std::ostream& out = std::cout) { out << *this;}

    friend std::ostream& operator<< (std::ostream& out, const FairMCResult& result) {
      out << "MC Link from: " << result.GetStartType() << " to "  << result.GetStopType() << ":" << std::endl;
      (static_cast<FairMCObject>(result)).PrintInfo(out);
      return out;
    }


  private:
    Int_t fStartType;
    Int_t fStopType;

    ClassDef(FairMCResult, 2);
};

#endif /* FairMCResult_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCEntry.h
 *
 *  Created on: Dec 22, 2009
 *      Author: stockman
 */

#ifndef FAIRMCENTRY_H_
#define FAIRMCENTRY_H_

#include "FairMultiLinkedData.h"        // for FairMultiLinkedData

#include "FairLink.h"                   // for FairLink

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, FairMCEntry::Class, etc

#include <iostream>                     // for ostream
#include <set>                          // for set

class FairMCEntry : public FairMultiLinkedData
{
  public:
    FairMCEntry();
    FairMCEntry(std::set<FairLink> links, Int_t source = -1, Int_t pos = -1)
      : FairMultiLinkedData(links),
        fSource(source),
        fPos(pos) {
      SetPersistanceCheck(kFALSE);
    }

    FairMCEntry(FairMultiLinkedData links, Int_t source = -1, Int_t pos = -1)
      : FairMultiLinkedData(links),
        fSource(source),
        fPos(pos) {
      SetPersistanceCheck(kFALSE);
    }

    void SetSource(Int_t source) {fSource = source;}
    void SetPos(Int_t pos) {fPos = pos;}

    Int_t GetSource() const {return fSource;}
    Int_t GetPos() const {return fPos;}

    void RemoveType(Int_t type);

    virtual ~FairMCEntry();

    virtual void PrintInfo(std::ostream& out) {
      out << *this;
    }

    friend std::ostream& operator<< (std::ostream& out, const FairMCEntry& link) {
      (static_cast<FairMultiLinkedData>(link)).PrintLinkInfo(out);
      return out;
    }

  private:
    Int_t fSource;
    Int_t fPos;

    ClassDef(FairMCEntry, 1);
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
 * FairMCList.h
 *
 *  Created on: Dec 3, 2009
 *      Author: stockman
 */

#ifndef FAIRMCLIST_H_
#define FAIRMCLIST_H_

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Int_t, FairMCList::Class, etc

#include <vector>                       // for vector

class FairMCList : public TObject
{
  public:
    FairMCList();
    FairMCList(Int_t type, Int_t entry)
      : TObject(),
        fList(),
        fEntry(entry),
        fType(type) {
    }

    FairMCList(Int_t type, Int_t entry, std::vector<Int_t> list)
      : TObject(),
        fList(list),
        fEntry(entry),
        fType(type) {
    }

    virtual ~FairMCList();

    void SetType(Int_t type) { fType = type;}
    void SetEntry(Int_t entry) { fEntry = entry;}
    void AddElement(Int_t element) {fList.push_back(element);}

    Int_t GetType() const {return fType;}
    Int_t GetEntry() const {return fEntry;}
    Int_t GetNElements() const {return fList.size();}
    Int_t GetElement(Int_t index)const {return fList.at(index);}
    std::vector<Int_t> GetElements() const {return fList;}

    void Reset() {fList.clear();}

  private:
    std::vector<Int_t> fList;
    Int_t fEntry;
    Int_t fType;

    ClassDef(FairMCList, 1);
};

#endif /* PNDMCLIST_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairMCDataCrawler.h
 *
 *  Created on: Jul 5, 2011
 *      Author: stockman
 */

#ifndef FAIRMCDATACRAWLER_H_
#define FAIRMCDATACRAWLER_H_

#include "TObject.h"                    // for TObject

#include "FairMultiLinkedData.h"        // for FairMultiLinkedData

#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "TString.h"                    // for TString

class FairLink;
class FairRootManager;

class FairMCDataCrawler : public TObject
{
  public:
    FairMCDataCrawler();
    virtual ~FairMCDataCrawler();

    FairMultiLinkedData GetInfo(FairMultiLinkedData startLink, TString stopStage);
    FairMultiLinkedData GetInfo(FairMultiLinkedData startLink, Int_t stopStageId);

    FairMultiLinkedData* GetEntry(Int_t fileId, Int_t eventNr, Int_t type, Int_t index);
    FairMultiLinkedData* GetEntry(FairLink link);

    void SetStoreIntermediate(Bool_t val = kTRUE) {fStoreIntermediate = val;}
    void SetStoreAllEndpoints(Bool_t val = kTRUE) {fStoreAllEndpoints = val;}

    void Init();

    void SetVerbose(Int_t val) {fVerbose = val;};

    virtual void InitDataObjects() = 0;

  protected:

    FairRootManager* fIoman;

  private:
    FairMultiLinkedData fFinalStage;
    Int_t fUltimateStage; ///< last stage in link chain. Here all recursive operations must stop.

    Int_t fVerbose;
    Bool_t fStoreAllEndpoints; ///< true if non-stop-stage data is stored in results
    Bool_t fStoreIntermediate; ///< true if all intermediate steps should be stored

    void GetNextStage(FairMultiLinkedData& startEntry, Int_t stopStage);
    void AddToFinalStage(FairLink link, Float_t mult);
    void ClearFinalStage();

    FairMCDataCrawler(const FairMCDataCrawler&);
    FairMCDataCrawler& operator=(const FairMCDataCrawler&);

    ClassDef(FairMCDataCrawler, 1);
};

#endif /* PNDMCDATACRAWLER_H_ */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairMCDataCrawler", payloadCode, "@",
"FairMCEntry", payloadCode, "@",
"FairMCList", payloadCode, "@",
"FairMCMatch", payloadCode, "@",
"FairMCMatchCreatorTask", payloadCode, "@",
"FairMCMatchLoaderTask", payloadCode, "@",
"FairMCMatchSelectorTask", payloadCode, "@",
"FairMCObject", payloadCode, "@",
"FairMCResult", payloadCode, "@",
"FairMCStage", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__FairDataMatchDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__FairDataMatchDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__FairDataMatchDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__FairDataMatchDict() {
  TriggerDictionaryInitialization_G__FairDataMatchDict_Impl();
}

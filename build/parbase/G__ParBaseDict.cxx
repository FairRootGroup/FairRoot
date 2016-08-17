// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIparbasedIG__ParBaseDict

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
#include "FairContFact.h"
#include "FairDetParAsciiFileIo.h"
#include "FairDetParIo.h"
#include "FairDetParRootFileIo.h"
#include "FairGenericParAsciiFileIo.h"
#include "FairGenericParRootFileIo.h"
#include "FairParAsciiFileIo.h"
#include "FairParGenericSet.h"
#include "FairParIo.h"
#include "FairParRootFileIo.h"
#include "FairParSet.h"
#include "FairParamList.h"
#include "FairRtdbRun.h"
#include "FairRuntimeDb.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairContFact(void *p = 0);
   static void *newArray_FairContFact(Long_t size, void *p);
   static void delete_FairContFact(void *p);
   static void deleteArray_FairContFact(void *p);
   static void destruct_FairContFact(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairContFact*)
   {
      ::FairContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairContFact", ::FairContFact::Class_Version(), "invalid", 53,
                  typeid(::FairContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairContFact::Dictionary, isa_proxy, 4,
                  sizeof(::FairContFact) );
      instance.SetNew(&new_FairContFact);
      instance.SetNewArray(&newArray_FairContFact);
      instance.SetDelete(&delete_FairContFact);
      instance.SetDeleteArray(&deleteArray_FairContFact);
      instance.SetDestructor(&destruct_FairContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairContFact*)
   {
      return GenerateInitInstanceLocal((::FairContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairContainer(void *p);
   static void deleteArray_FairContainer(void *p);
   static void destruct_FairContainer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairContainer*)
   {
      ::FairContainer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairContainer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairContainer", ::FairContainer::Class_Version(), "invalid", 26,
                  typeid(::FairContainer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairContainer::Dictionary, isa_proxy, 4,
                  sizeof(::FairContainer) );
      instance.SetDelete(&delete_FairContainer);
      instance.SetDeleteArray(&deleteArray_FairContainer);
      instance.SetDestructor(&destruct_FairContainer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairContainer*)
   {
      return GenerateInitInstanceLocal((::FairContainer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairContainer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairDetParAsciiFileIo(void *p);
   static void deleteArray_FairDetParAsciiFileIo(void *p);
   static void destruct_FairDetParAsciiFileIo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairDetParAsciiFileIo*)
   {
      ::FairDetParAsciiFileIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairDetParAsciiFileIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairDetParAsciiFileIo", ::FairDetParAsciiFileIo::Class_Version(), "invalid", 101,
                  typeid(::FairDetParAsciiFileIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairDetParAsciiFileIo::Dictionary, isa_proxy, 4,
                  sizeof(::FairDetParAsciiFileIo) );
      instance.SetDelete(&delete_FairDetParAsciiFileIo);
      instance.SetDeleteArray(&deleteArray_FairDetParAsciiFileIo);
      instance.SetDestructor(&destruct_FairDetParAsciiFileIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairDetParAsciiFileIo*)
   {
      return GenerateInitInstanceLocal((::FairDetParAsciiFileIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairDetParAsciiFileIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairDetParIo(void *p = 0);
   static void *newArray_FairDetParIo(Long_t size, void *p);
   static void delete_FairDetParIo(void *p);
   static void deleteArray_FairDetParIo(void *p);
   static void destruct_FairDetParIo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairDetParIo*)
   {
      ::FairDetParIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairDetParIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairDetParIo", ::FairDetParIo::Class_Version(), "FairDetParIo.h", 17,
                  typeid(::FairDetParIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairDetParIo::Dictionary, isa_proxy, 4,
                  sizeof(::FairDetParIo) );
      instance.SetNew(&new_FairDetParIo);
      instance.SetNewArray(&newArray_FairDetParIo);
      instance.SetDelete(&delete_FairDetParIo);
      instance.SetDeleteArray(&deleteArray_FairDetParIo);
      instance.SetDestructor(&destruct_FairDetParIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairDetParIo*)
   {
      return GenerateInitInstanceLocal((::FairDetParIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairDetParIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairDetParRootFileIo(void *p);
   static void deleteArray_FairDetParRootFileIo(void *p);
   static void destruct_FairDetParRootFileIo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairDetParRootFileIo*)
   {
      ::FairDetParRootFileIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairDetParRootFileIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairDetParRootFileIo", ::FairDetParRootFileIo::Class_Version(), "invalid", 205,
                  typeid(::FairDetParRootFileIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairDetParRootFileIo::Dictionary, isa_proxy, 4,
                  sizeof(::FairDetParRootFileIo) );
      instance.SetDelete(&delete_FairDetParRootFileIo);
      instance.SetDeleteArray(&deleteArray_FairDetParRootFileIo);
      instance.SetDestructor(&destruct_FairDetParRootFileIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairDetParRootFileIo*)
   {
      return GenerateInitInstanceLocal((::FairDetParRootFileIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairDetParRootFileIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGenericParAsciiFileIo(void *p = 0);
   static void *newArray_FairGenericParAsciiFileIo(Long_t size, void *p);
   static void delete_FairGenericParAsciiFileIo(void *p);
   static void deleteArray_FairGenericParAsciiFileIo(void *p);
   static void destruct_FairGenericParAsciiFileIo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGenericParAsciiFileIo*)
   {
      ::FairGenericParAsciiFileIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGenericParAsciiFileIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGenericParAsciiFileIo", ::FairGenericParAsciiFileIo::Class_Version(), "invalid", 250,
                  typeid(::FairGenericParAsciiFileIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGenericParAsciiFileIo::Dictionary, isa_proxy, 4,
                  sizeof(::FairGenericParAsciiFileIo) );
      instance.SetNew(&new_FairGenericParAsciiFileIo);
      instance.SetNewArray(&newArray_FairGenericParAsciiFileIo);
      instance.SetDelete(&delete_FairGenericParAsciiFileIo);
      instance.SetDeleteArray(&deleteArray_FairGenericParAsciiFileIo);
      instance.SetDestructor(&destruct_FairGenericParAsciiFileIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGenericParAsciiFileIo*)
   {
      return GenerateInitInstanceLocal((::FairGenericParAsciiFileIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGenericParAsciiFileIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGenericParRootFileIo(void *p = 0);
   static void *newArray_FairGenericParRootFileIo(Long_t size, void *p);
   static void delete_FairGenericParRootFileIo(void *p);
   static void deleteArray_FairGenericParRootFileIo(void *p);
   static void destruct_FairGenericParRootFileIo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGenericParRootFileIo*)
   {
      ::FairGenericParRootFileIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGenericParRootFileIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGenericParRootFileIo", ::FairGenericParRootFileIo::Class_Version(), "invalid", 286,
                  typeid(::FairGenericParRootFileIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGenericParRootFileIo::Dictionary, isa_proxy, 4,
                  sizeof(::FairGenericParRootFileIo) );
      instance.SetNew(&new_FairGenericParRootFileIo);
      instance.SetNewArray(&newArray_FairGenericParRootFileIo);
      instance.SetDelete(&delete_FairGenericParRootFileIo);
      instance.SetDeleteArray(&deleteArray_FairGenericParRootFileIo);
      instance.SetDestructor(&destruct_FairGenericParRootFileIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGenericParRootFileIo*)
   {
      return GenerateInitInstanceLocal((::FairGenericParRootFileIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGenericParRootFileIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParAsciiFileIo(void *p = 0);
   static void *newArray_FairParAsciiFileIo(Long_t size, void *p);
   static void delete_FairParAsciiFileIo(void *p);
   static void deleteArray_FairParAsciiFileIo(void *p);
   static void destruct_FairParAsciiFileIo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParAsciiFileIo*)
   {
      ::FairParAsciiFileIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParAsciiFileIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParAsciiFileIo", ::FairParAsciiFileIo::Class_Version(), "invalid", 316,
                  typeid(::FairParAsciiFileIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParAsciiFileIo::Dictionary, isa_proxy, 4,
                  sizeof(::FairParAsciiFileIo) );
      instance.SetNew(&new_FairParAsciiFileIo);
      instance.SetNewArray(&newArray_FairParAsciiFileIo);
      instance.SetDelete(&delete_FairParAsciiFileIo);
      instance.SetDeleteArray(&deleteArray_FairParAsciiFileIo);
      instance.SetDestructor(&destruct_FairParAsciiFileIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParAsciiFileIo*)
   {
      return GenerateInitInstanceLocal((::FairParAsciiFileIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParAsciiFileIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairParGenericSet(void *p);
   static void deleteArray_FairParGenericSet(void *p);
   static void destruct_FairParGenericSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParGenericSet*)
   {
      ::FairParGenericSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParGenericSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParGenericSet", ::FairParGenericSet::Class_Version(), "invalid", 377,
                  typeid(::FairParGenericSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParGenericSet::Dictionary, isa_proxy, 4,
                  sizeof(::FairParGenericSet) );
      instance.SetDelete(&delete_FairParGenericSet);
      instance.SetDeleteArray(&deleteArray_FairParGenericSet);
      instance.SetDestructor(&destruct_FairParGenericSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParGenericSet*)
   {
      return GenerateInitInstanceLocal((::FairParGenericSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParGenericSet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParIo(void *p = 0);
   static void *newArray_FairParIo(Long_t size, void *p);
   static void delete_FairParIo(void *p);
   static void deleteArray_FairParIo(void *p);
   static void destruct_FairParIo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParIo*)
   {
      ::FairParIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParIo", ::FairParIo::Class_Version(), "FairParIo.h", 20,
                  typeid(::FairParIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParIo::Dictionary, isa_proxy, 4,
                  sizeof(::FairParIo) );
      instance.SetNew(&new_FairParIo);
      instance.SetNewArray(&newArray_FairParIo);
      instance.SetDelete(&delete_FairParIo);
      instance.SetDeleteArray(&deleteArray_FairParIo);
      instance.SetDestructor(&destruct_FairParIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParIo*)
   {
      return GenerateInitInstanceLocal((::FairParIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairParRootFile(void *p);
   static void deleteArray_FairParRootFile(void *p);
   static void destruct_FairParRootFile(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParRootFile*)
   {
      ::FairParRootFile *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParRootFile >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParRootFile", ::FairParRootFile::Class_Version(), "invalid", 497,
                  typeid(::FairParRootFile), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParRootFile::Dictionary, isa_proxy, 4,
                  sizeof(::FairParRootFile) );
      instance.SetDelete(&delete_FairParRootFile);
      instance.SetDeleteArray(&deleteArray_FairParRootFile);
      instance.SetDestructor(&destruct_FairParRootFile);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParRootFile*)
   {
      return GenerateInitInstanceLocal((::FairParRootFile*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParRootFile*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParRootFileIo(void *p = 0);
   static void *newArray_FairParRootFileIo(Long_t size, void *p);
   static void delete_FairParRootFileIo(void *p);
   static void deleteArray_FairParRootFileIo(void *p);
   static void destruct_FairParRootFileIo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParRootFileIo*)
   {
      ::FairParRootFileIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParRootFileIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParRootFileIo", ::FairParRootFileIo::Class_Version(), "invalid", 528,
                  typeid(::FairParRootFileIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParRootFileIo::Dictionary, isa_proxy, 4,
                  sizeof(::FairParRootFileIo) );
      instance.SetNew(&new_FairParRootFileIo);
      instance.SetNewArray(&newArray_FairParRootFileIo);
      instance.SetDelete(&delete_FairParRootFileIo);
      instance.SetDeleteArray(&deleteArray_FairParRootFileIo);
      instance.SetDestructor(&destruct_FairParRootFileIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParRootFileIo*)
   {
      return GenerateInitInstanceLocal((::FairParRootFileIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParRootFileIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParSet(void *p = 0);
   static void *newArray_FairParSet(Long_t size, void *p);
   static void delete_FairParSet(void *p);
   static void deleteArray_FairParSet(void *p);
   static void destruct_FairParSet(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParSet*)
   {
      ::FairParSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParSet", ::FairParSet::Class_Version(), "FairParSet.h", 18,
                  typeid(::FairParSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParSet::Dictionary, isa_proxy, 4,
                  sizeof(::FairParSet) );
      instance.SetNew(&new_FairParSet);
      instance.SetNewArray(&newArray_FairParSet);
      instance.SetDelete(&delete_FairParSet);
      instance.SetDeleteArray(&deleteArray_FairParSet);
      instance.SetDestructor(&destruct_FairParSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParSet*)
   {
      return GenerateInitInstanceLocal((::FairParSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParSet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParVersion(void *p = 0);
   static void *newArray_FairParVersion(Long_t size, void *p);
   static void delete_FairParVersion(void *p);
   static void deleteArray_FairParVersion(void *p);
   static void destruct_FairParVersion(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParVersion*)
   {
      ::FairParVersion *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParVersion >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParVersion", ::FairParVersion::Class_Version(), "invalid", 831,
                  typeid(::FairParVersion), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParVersion::Dictionary, isa_proxy, 4,
                  sizeof(::FairParVersion) );
      instance.SetNew(&new_FairParVersion);
      instance.SetNewArray(&newArray_FairParVersion);
      instance.SetDelete(&delete_FairParVersion);
      instance.SetDeleteArray(&deleteArray_FairParVersion);
      instance.SetDestructor(&destruct_FairParVersion);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParVersion*)
   {
      return GenerateInitInstanceLocal((::FairParVersion*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParVersion*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParamList(void *p = 0);
   static void *newArray_FairParamList(Long_t size, void *p);
   static void delete_FairParamList(void *p);
   static void deleteArray_FairParamList(void *p);
   static void destruct_FairParamList(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParamList*)
   {
      ::FairParamList *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParamList >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParamList", ::FairParamList::Class_Version(), "invalid", 744,
                  typeid(::FairParamList), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParamList::Dictionary, isa_proxy, 4,
                  sizeof(::FairParamList) );
      instance.SetNew(&new_FairParamList);
      instance.SetNewArray(&newArray_FairParamList);
      instance.SetDelete(&delete_FairParamList);
      instance.SetDeleteArray(&deleteArray_FairParamList);
      instance.SetDestructor(&destruct_FairParamList);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParamList*)
   {
      return GenerateInitInstanceLocal((::FairParamList*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParamList*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParamObj(void *p = 0);
   static void *newArray_FairParamObj(Long_t size, void *p);
   static void delete_FairParamObj(void *p);
   static void deleteArray_FairParamObj(void *p);
   static void destruct_FairParamObj(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParamObj*)
   {
      ::FairParamObj *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParamObj >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParamObj", ::FairParamObj::Class_Version(), "invalid", 691,
                  typeid(::FairParamObj), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParamObj::Dictionary, isa_proxy, 4,
                  sizeof(::FairParamObj) );
      instance.SetNew(&new_FairParamObj);
      instance.SetNewArray(&newArray_FairParamObj);
      instance.SetDelete(&delete_FairParamObj);
      instance.SetDeleteArray(&deleteArray_FairParamObj);
      instance.SetDestructor(&destruct_FairParamObj);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParamObj*)
   {
      return GenerateInitInstanceLocal((::FairParamObj*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParamObj*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRtdbRun(void *p = 0);
   static void *newArray_FairRtdbRun(Long_t size, void *p);
   static void delete_FairRtdbRun(void *p);
   static void deleteArray_FairRtdbRun(void *p);
   static void destruct_FairRtdbRun(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRtdbRun*)
   {
      ::FairRtdbRun *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRtdbRun >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRtdbRun", ::FairRtdbRun::Class_Version(), "invalid", 855,
                  typeid(::FairRtdbRun), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRtdbRun::Dictionary, isa_proxy, 4,
                  sizeof(::FairRtdbRun) );
      instance.SetNew(&new_FairRtdbRun);
      instance.SetNewArray(&newArray_FairRtdbRun);
      instance.SetDelete(&delete_FairRtdbRun);
      instance.SetDeleteArray(&deleteArray_FairRtdbRun);
      instance.SetDestructor(&destruct_FairRtdbRun);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRtdbRun*)
   {
      return GenerateInitInstanceLocal((::FairRtdbRun*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRtdbRun*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairRuntimeDb(void *p);
   static void deleteArray_FairRuntimeDb(void *p);
   static void destruct_FairRuntimeDb(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRuntimeDb*)
   {
      ::FairRuntimeDb *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRuntimeDb >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRuntimeDb", ::FairRuntimeDb::Class_Version(), "invalid", 930,
                  typeid(::FairRuntimeDb), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRuntimeDb::Dictionary, isa_proxy, 4,
                  sizeof(::FairRuntimeDb) );
      instance.SetDelete(&delete_FairRuntimeDb);
      instance.SetDeleteArray(&deleteArray_FairRuntimeDb);
      instance.SetDestructor(&destruct_FairRuntimeDb);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRuntimeDb*)
   {
      return GenerateInitInstanceLocal((::FairRuntimeDb*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRuntimeDb*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairContFact::Class_Name()
{
   return "FairContFact";
}

//______________________________________________________________________________
const char *FairContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairContainer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairContainer::Class_Name()
{
   return "FairContainer";
}

//______________________________________________________________________________
const char *FairContainer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairContainer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairContainer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairContainer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairContainer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairContainer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairContainer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairContainer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairDetParAsciiFileIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairDetParAsciiFileIo::Class_Name()
{
   return "FairDetParAsciiFileIo";
}

//______________________________________________________________________________
const char *FairDetParAsciiFileIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairDetParAsciiFileIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairDetParAsciiFileIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairDetParAsciiFileIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairDetParAsciiFileIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairDetParAsciiFileIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairDetParAsciiFileIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairDetParAsciiFileIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairDetParIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairDetParIo::Class_Name()
{
   return "FairDetParIo";
}

//______________________________________________________________________________
const char *FairDetParIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairDetParIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairDetParIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairDetParIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairDetParIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairDetParIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairDetParIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairDetParIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairDetParRootFileIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairDetParRootFileIo::Class_Name()
{
   return "FairDetParRootFileIo";
}

//______________________________________________________________________________
const char *FairDetParRootFileIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairDetParRootFileIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairDetParRootFileIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairDetParRootFileIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairDetParRootFileIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairDetParRootFileIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairDetParRootFileIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairDetParRootFileIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGenericParAsciiFileIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGenericParAsciiFileIo::Class_Name()
{
   return "FairGenericParAsciiFileIo";
}

//______________________________________________________________________________
const char *FairGenericParAsciiFileIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGenericParAsciiFileIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGenericParAsciiFileIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGenericParAsciiFileIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGenericParAsciiFileIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGenericParAsciiFileIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGenericParAsciiFileIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGenericParAsciiFileIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGenericParRootFileIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGenericParRootFileIo::Class_Name()
{
   return "FairGenericParRootFileIo";
}

//______________________________________________________________________________
const char *FairGenericParRootFileIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGenericParRootFileIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGenericParRootFileIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGenericParRootFileIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGenericParRootFileIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGenericParRootFileIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGenericParRootFileIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGenericParRootFileIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParAsciiFileIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParAsciiFileIo::Class_Name()
{
   return "FairParAsciiFileIo";
}

//______________________________________________________________________________
const char *FairParAsciiFileIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParAsciiFileIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParAsciiFileIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParAsciiFileIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParAsciiFileIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParAsciiFileIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParAsciiFileIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParAsciiFileIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParGenericSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParGenericSet::Class_Name()
{
   return "FairParGenericSet";
}

//______________________________________________________________________________
const char *FairParGenericSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParGenericSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParGenericSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParGenericSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParGenericSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParGenericSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParGenericSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParGenericSet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParIo::Class_Name()
{
   return "FairParIo";
}

//______________________________________________________________________________
const char *FairParIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParRootFile::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParRootFile::Class_Name()
{
   return "FairParRootFile";
}

//______________________________________________________________________________
const char *FairParRootFile::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParRootFile*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParRootFile::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParRootFile*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParRootFile::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParRootFile*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParRootFile::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParRootFile*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParRootFileIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParRootFileIo::Class_Name()
{
   return "FairParRootFileIo";
}

//______________________________________________________________________________
const char *FairParRootFileIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParRootFileIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParRootFileIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParRootFileIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParRootFileIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParRootFileIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParRootFileIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParRootFileIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParSet::Class_Name()
{
   return "FairParSet";
}

//______________________________________________________________________________
const char *FairParSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParSet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParVersion::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParVersion::Class_Name()
{
   return "FairParVersion";
}

//______________________________________________________________________________
const char *FairParVersion::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParVersion*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParVersion::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParVersion*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParVersion::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParVersion*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParVersion::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParVersion*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParamList::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParamList::Class_Name()
{
   return "FairParamList";
}

//______________________________________________________________________________
const char *FairParamList::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParamList*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParamList::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParamList*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParamList::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParamList*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParamList::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParamList*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParamObj::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParamObj::Class_Name()
{
   return "FairParamObj";
}

//______________________________________________________________________________
const char *FairParamObj::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParamObj*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParamObj::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParamObj*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParamObj::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParamObj*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParamObj::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParamObj*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRtdbRun::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRtdbRun::Class_Name()
{
   return "FairRtdbRun";
}

//______________________________________________________________________________
const char *FairRtdbRun::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRtdbRun*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRtdbRun::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRtdbRun*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRtdbRun::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRtdbRun*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRtdbRun::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRtdbRun*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRuntimeDb::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRuntimeDb::Class_Name()
{
   return "FairRuntimeDb";
}

//______________________________________________________________________________
const char *FairRuntimeDb::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRuntimeDb*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRuntimeDb::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRuntimeDb*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRuntimeDb::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRuntimeDb*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRuntimeDb::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRuntimeDb*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairContFact.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairContFact::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairContFact::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairContFact(void *p) {
      return  p ? new(p) ::FairContFact : new ::FairContFact;
   }
   static void *newArray_FairContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairContFact[nElements] : new ::FairContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairContFact(void *p) {
      delete ((::FairContFact*)p);
   }
   static void deleteArray_FairContFact(void *p) {
      delete [] ((::FairContFact*)p);
   }
   static void destruct_FairContFact(void *p) {
      typedef ::FairContFact current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairContFact

//______________________________________________________________________________
void FairContainer::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairContainer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairContainer::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairContainer::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairContainer(void *p) {
      delete ((::FairContainer*)p);
   }
   static void deleteArray_FairContainer(void *p) {
      delete [] ((::FairContainer*)p);
   }
   static void destruct_FairContainer(void *p) {
      typedef ::FairContainer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairContainer

//______________________________________________________________________________
void FairDetParAsciiFileIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairDetParAsciiFileIo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairDetParAsciiFileIo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairDetParAsciiFileIo::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairDetParAsciiFileIo(void *p) {
      delete ((::FairDetParAsciiFileIo*)p);
   }
   static void deleteArray_FairDetParAsciiFileIo(void *p) {
      delete [] ((::FairDetParAsciiFileIo*)p);
   }
   static void destruct_FairDetParAsciiFileIo(void *p) {
      typedef ::FairDetParAsciiFileIo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairDetParAsciiFileIo

//______________________________________________________________________________
void FairDetParIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairDetParIo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairDetParIo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairDetParIo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairDetParIo(void *p) {
      return  p ? new(p) ::FairDetParIo : new ::FairDetParIo;
   }
   static void *newArray_FairDetParIo(Long_t nElements, void *p) {
      return p ? new(p) ::FairDetParIo[nElements] : new ::FairDetParIo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairDetParIo(void *p) {
      delete ((::FairDetParIo*)p);
   }
   static void deleteArray_FairDetParIo(void *p) {
      delete [] ((::FairDetParIo*)p);
   }
   static void destruct_FairDetParIo(void *p) {
      typedef ::FairDetParIo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairDetParIo

//______________________________________________________________________________
void FairDetParRootFileIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairDetParRootFileIo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairDetParRootFileIo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairDetParRootFileIo::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairDetParRootFileIo(void *p) {
      delete ((::FairDetParRootFileIo*)p);
   }
   static void deleteArray_FairDetParRootFileIo(void *p) {
      delete [] ((::FairDetParRootFileIo*)p);
   }
   static void destruct_FairDetParRootFileIo(void *p) {
      typedef ::FairDetParRootFileIo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairDetParRootFileIo

//______________________________________________________________________________
void FairGenericParAsciiFileIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGenericParAsciiFileIo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGenericParAsciiFileIo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGenericParAsciiFileIo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGenericParAsciiFileIo(void *p) {
      return  p ? new(p) ::FairGenericParAsciiFileIo : new ::FairGenericParAsciiFileIo;
   }
   static void *newArray_FairGenericParAsciiFileIo(Long_t nElements, void *p) {
      return p ? new(p) ::FairGenericParAsciiFileIo[nElements] : new ::FairGenericParAsciiFileIo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGenericParAsciiFileIo(void *p) {
      delete ((::FairGenericParAsciiFileIo*)p);
   }
   static void deleteArray_FairGenericParAsciiFileIo(void *p) {
      delete [] ((::FairGenericParAsciiFileIo*)p);
   }
   static void destruct_FairGenericParAsciiFileIo(void *p) {
      typedef ::FairGenericParAsciiFileIo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGenericParAsciiFileIo

//______________________________________________________________________________
void FairGenericParRootFileIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGenericParRootFileIo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGenericParRootFileIo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGenericParRootFileIo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGenericParRootFileIo(void *p) {
      return  p ? new(p) ::FairGenericParRootFileIo : new ::FairGenericParRootFileIo;
   }
   static void *newArray_FairGenericParRootFileIo(Long_t nElements, void *p) {
      return p ? new(p) ::FairGenericParRootFileIo[nElements] : new ::FairGenericParRootFileIo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGenericParRootFileIo(void *p) {
      delete ((::FairGenericParRootFileIo*)p);
   }
   static void deleteArray_FairGenericParRootFileIo(void *p) {
      delete [] ((::FairGenericParRootFileIo*)p);
   }
   static void destruct_FairGenericParRootFileIo(void *p) {
      typedef ::FairGenericParRootFileIo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGenericParRootFileIo

//______________________________________________________________________________
void FairParAsciiFileIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParAsciiFileIo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParAsciiFileIo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParAsciiFileIo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParAsciiFileIo(void *p) {
      return  p ? new(p) ::FairParAsciiFileIo : new ::FairParAsciiFileIo;
   }
   static void *newArray_FairParAsciiFileIo(Long_t nElements, void *p) {
      return p ? new(p) ::FairParAsciiFileIo[nElements] : new ::FairParAsciiFileIo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParAsciiFileIo(void *p) {
      delete ((::FairParAsciiFileIo*)p);
   }
   static void deleteArray_FairParAsciiFileIo(void *p) {
      delete [] ((::FairParAsciiFileIo*)p);
   }
   static void destruct_FairParAsciiFileIo(void *p) {
      typedef ::FairParAsciiFileIo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParAsciiFileIo

//______________________________________________________________________________
void FairParGenericSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParGenericSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParGenericSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParGenericSet::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairParGenericSet(void *p) {
      delete ((::FairParGenericSet*)p);
   }
   static void deleteArray_FairParGenericSet(void *p) {
      delete [] ((::FairParGenericSet*)p);
   }
   static void destruct_FairParGenericSet(void *p) {
      typedef ::FairParGenericSet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParGenericSet

//______________________________________________________________________________
void FairParIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParIo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParIo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParIo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParIo(void *p) {
      return  p ? new(p) ::FairParIo : new ::FairParIo;
   }
   static void *newArray_FairParIo(Long_t nElements, void *p) {
      return p ? new(p) ::FairParIo[nElements] : new ::FairParIo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParIo(void *p) {
      delete ((::FairParIo*)p);
   }
   static void deleteArray_FairParIo(void *p) {
      delete [] ((::FairParIo*)p);
   }
   static void destruct_FairParIo(void *p) {
      typedef ::FairParIo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParIo

//______________________________________________________________________________
void FairParRootFile::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParRootFile.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParRootFile::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParRootFile::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairParRootFile(void *p) {
      delete ((::FairParRootFile*)p);
   }
   static void deleteArray_FairParRootFile(void *p) {
      delete [] ((::FairParRootFile*)p);
   }
   static void destruct_FairParRootFile(void *p) {
      typedef ::FairParRootFile current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParRootFile

//______________________________________________________________________________
void FairParRootFileIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParRootFileIo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParRootFileIo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParRootFileIo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParRootFileIo(void *p) {
      return  p ? new(p) ::FairParRootFileIo : new ::FairParRootFileIo;
   }
   static void *newArray_FairParRootFileIo(Long_t nElements, void *p) {
      return p ? new(p) ::FairParRootFileIo[nElements] : new ::FairParRootFileIo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParRootFileIo(void *p) {
      delete ((::FairParRootFileIo*)p);
   }
   static void deleteArray_FairParRootFileIo(void *p) {
      delete [] ((::FairParRootFileIo*)p);
   }
   static void destruct_FairParRootFileIo(void *p) {
      typedef ::FairParRootFileIo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParRootFileIo

//______________________________________________________________________________
void FairParSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParSet.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParSet::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParSet::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParSet(void *p) {
      return  p ? new(p) ::FairParSet : new ::FairParSet;
   }
   static void *newArray_FairParSet(Long_t nElements, void *p) {
      return p ? new(p) ::FairParSet[nElements] : new ::FairParSet[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParSet(void *p) {
      delete ((::FairParSet*)p);
   }
   static void deleteArray_FairParSet(void *p) {
      delete [] ((::FairParSet*)p);
   }
   static void destruct_FairParSet(void *p) {
      typedef ::FairParSet current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParSet

//______________________________________________________________________________
void FairParVersion::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParVersion.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParVersion::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParVersion::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParVersion(void *p) {
      return  p ? new(p) ::FairParVersion : new ::FairParVersion;
   }
   static void *newArray_FairParVersion(Long_t nElements, void *p) {
      return p ? new(p) ::FairParVersion[nElements] : new ::FairParVersion[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParVersion(void *p) {
      delete ((::FairParVersion*)p);
   }
   static void deleteArray_FairParVersion(void *p) {
      delete [] ((::FairParVersion*)p);
   }
   static void destruct_FairParVersion(void *p) {
      typedef ::FairParVersion current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParVersion

//______________________________________________________________________________
void FairParamList::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParamList.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParamList::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParamList::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParamList(void *p) {
      return  p ? new(p) ::FairParamList : new ::FairParamList;
   }
   static void *newArray_FairParamList(Long_t nElements, void *p) {
      return p ? new(p) ::FairParamList[nElements] : new ::FairParamList[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParamList(void *p) {
      delete ((::FairParamList*)p);
   }
   static void deleteArray_FairParamList(void *p) {
      delete [] ((::FairParamList*)p);
   }
   static void destruct_FairParamList(void *p) {
      typedef ::FairParamList current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParamList

//______________________________________________________________________________
void FairParamObj::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParamObj.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParamObj::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParamObj::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParamObj(void *p) {
      return  p ? new(p) ::FairParamObj : new ::FairParamObj;
   }
   static void *newArray_FairParamObj(Long_t nElements, void *p) {
      return p ? new(p) ::FairParamObj[nElements] : new ::FairParamObj[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParamObj(void *p) {
      delete ((::FairParamObj*)p);
   }
   static void deleteArray_FairParamObj(void *p) {
      delete [] ((::FairParamObj*)p);
   }
   static void destruct_FairParamObj(void *p) {
      typedef ::FairParamObj current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParamObj

//______________________________________________________________________________
void FairRtdbRun::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRtdbRun.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRtdbRun::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRtdbRun::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRtdbRun(void *p) {
      return  p ? new(p) ::FairRtdbRun : new ::FairRtdbRun;
   }
   static void *newArray_FairRtdbRun(Long_t nElements, void *p) {
      return p ? new(p) ::FairRtdbRun[nElements] : new ::FairRtdbRun[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRtdbRun(void *p) {
      delete ((::FairRtdbRun*)p);
   }
   static void deleteArray_FairRtdbRun(void *p) {
      delete [] ((::FairRtdbRun*)p);
   }
   static void destruct_FairRtdbRun(void *p) {
      typedef ::FairRtdbRun current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRtdbRun

//______________________________________________________________________________
void FairRuntimeDb::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRuntimeDb.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRuntimeDb::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRuntimeDb::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairRuntimeDb(void *p) {
      delete ((::FairRuntimeDb*)p);
   }
   static void deleteArray_FairRuntimeDb(void *p) {
      delete [] ((::FairRuntimeDb*)p);
   }
   static void destruct_FairRuntimeDb(void *p) {
      typedef ::FairRuntimeDb current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRuntimeDb

namespace {
  void TriggerDictionaryInitialization_G__ParBaseDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/Users/turany/development/FairRoot/fairtools",
"/Users/turany/development/FairRoot/base",
"/Users/turany/development/FairRoot/base/steer",
"/Users/turany/development/FairRoot/base/event",
"/Users/turany/development/FairRoot/base/field",
"/Users/turany/development/FairRoot/base/sim",
"/Users/turany/development/FairRoot/geobase",
"/Users/turany/development/FairRoot/parbase",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/parbase/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__ParBaseDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(base class of all factories for parameter containers)ATTRDUMP"))) FairContFact;
class __attribute__((annotate(R"ATTRDUMP(class for list elements in class FairContFact)ATTRDUMP"))) FairContainer;
class __attribute__((annotate(R"ATTRDUMP(Class for detector parameter I/O from ascii file)ATTRDUMP"))) FairDetParAsciiFileIo;
class __attribute__((annotate(R"ATTRDUMP(Base class for detector parameter IO)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FairDetParIo.h")))  FairDetParIo;
class __attribute__((annotate(R"ATTRDUMP(detector base class for parameter I/O from ROOT file)ATTRDUMP"))) FairDetParRootFileIo;
class __attribute__((annotate(R"ATTRDUMP(I/O from Ascii file for parameter containers derived from FairParGenericSet)ATTRDUMP"))) FairGenericParAsciiFileIo;
class __attribute__((annotate(R"ATTRDUMP(I/O from ROOT file for parameter containers derived from FairParGenericSet)ATTRDUMP"))) FairGenericParRootFileIo;
class __attribute__((annotate(R"ATTRDUMP(Parameter I/O from ASCII files)ATTRDUMP"))) FairParAsciiFileIo;
class __attribute__((annotate(R"ATTRDUMP(Base class for generic-style parameter containers)ATTRDUMP"))) FairParGenericSet;
class __attribute__((annotate(R"ATTRDUMP(Base class for all parameter I/Os)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FairParIo.h")))  FairParIo;
class __attribute__((annotate(R"ATTRDUMP(ROOT file for Parameter I/O)ATTRDUMP"))) FairParRootFile;
class __attribute__((annotate(R"ATTRDUMP(Parameter I/O from ROOT files)ATTRDUMP"))) FairParRootFileIo;
class __attribute__((annotate(R"ATTRDUMP(Base class for all parameter containers)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FairParSet.h")))  FairParSet;
class __attribute__((annotate(R"ATTRDUMP(Class for parameter versions)ATTRDUMP"))) FairParVersion;
class __attribute__((annotate(R"ATTRDUMP(Class for lists of parameters (of type FairParamObj))ATTRDUMP"))) FairParamList;
class __attribute__((annotate(R"ATTRDUMP(Class for binary parameter object (name + binary array))ATTRDUMP"))) FairParamObj;
class __attribute__((annotate(R"ATTRDUMP(Class for parameter version management of a run)ATTRDUMP"))) FairRtdbRun;
class __attribute__((annotate(R"ATTRDUMP(Class for runtime database)ATTRDUMP"))) FairRuntimeDb;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__ParBaseDict dictionary payload"

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
#ifndef FAIRCONTFACT_H
#define FAIRCONTFACT_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Bool_t, ClassDef, etc
#include "TList.h"                      // for TList
#include "TString.h"                    // for TString

class FairLogger;
class FairParIo;
class FairParSet;

class FairContainer : public TNamed
{
  private:
    FairContainer();
    FairContainer(const FairContainer&);
    FairContainer& operator=(const FairContainer&);

  protected:
    /** available contexts for this parameter container*/
    TList* contexts;
    /** actual context set by the user */
    TString actualContext;
    /** Fair Logger */
    FairLogger*  fLogger;//!
  public:
    FairContainer( const char*, const char*, const char*);
    ~FairContainer();
    void addContext(const char*);
    Bool_t setActualContext(const char* c);
    const char* getDefaultContext();
    const char* getActualContext() { return actualContext.Data(); }
    void print();
    TString getConcatName();
    const char* getContext();
    ClassDef(FairContainer,0) // class for list elements in class FairContFact
};

class FairContFact : public TNamed
{
  public:
    FairContFact();
    virtual ~FairContFact();
    Bool_t addContext(const char* name);
    void print();
    FairParSet* getContainer(const char*);
    virtual FairParSet* createContainer(FairContainer*) {return 0;}
    virtual void activateParIo(FairParIo*) {}
  protected:

    TList* containers;   // all parameter containers managed by this factory
    const char* getActualContext(const char* name) {
      return (static_cast<FairContainer*>(containers->FindObject(name)))->getActualContext();
    }
    /** Fair Logger */
    FairLogger*  fLogger;//!
    ClassDef(FairContFact,0) // base class of all factories for parameter containers
  private:
    FairContFact(const FairContFact&);
    FairContFact& operator=(const FairContFact&);


};

#endif  /* !FAIRCONTFACT_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDETPARASCIIFILEIO_H
#define FAIRDETPARASCIIFILEIO_H

#include "FairDetParIo.h"               // for FairDetParIo

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Text_t, Bool_t, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairParSet;

class FairDetParAsciiFileIo : public FairDetParIo
{
  protected:
    TString fHeader;  //! header of container output in file
    TString sepLine;  //! comment line
    std::fstream* pFile;   //! pointer to ascii file
// virtual Bool_t write(HDetector*) {return kTRUE;}
    Bool_t findContainer(const Text_t* name);
    Bool_t checkAllFound(Int_t*,Int_t);
    void writeHeader(const Text_t*, const Text_t* context="",
                     const Text_t* author="", const Text_t* description="");
    void writeComment(FairParSet*);
    void readComment(const Char_t*, FairParSet*);
//  Bool_t readLabPositions(const Text_t*,HDetGeomPar*,Int_t*,Int_t,Int_t);
//  Bool_t readVolumes(const Text_t*,HDetGeomPar*);
//  void readTransform(HGeomTransform&);
//  Bool_t readVolume(HGeomVolume*,HGeomShapes*,Text_t*);
//  void writeTransform(const HGeomTransform&);
//  void writeVolume(HGeomVolume*,HGeomShapes*);

  public:
    FairDetParAsciiFileIo(std::fstream* f);
    virtual ~FairDetParAsciiFileIo() {}
//  Bool_t read(HDetGeomPar*,Int_t*);
//  Int_t writeFile(HDetGeomPar*);

  private:

    FairDetParAsciiFileIo& operator=(const FairDetParAsciiFileIo&);
    FairDetParAsciiFileIo(const FairDetParAsciiFileIo&);

    ClassDef(FairDetParAsciiFileIo,0) // Class for detector parameter I/O from ascii file
};

#endif  /* !FAIRDETPARASCIIFILEIO_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDETPARIO_H
#define FAIRDETPARIO_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Int_t, FairDetParIo::Class, etc

class FairParSet;

class FairDetParIo : public TNamed
{
  protected:
    Int_t inputNumber; // input number (first or second input in runtime database)
  public:
    FairDetParIo();
    virtual ~FairDetParIo() {;}

    // sets the input number
    void setInputNumber(Int_t n) {inputNumber=n;}

    // returns the input number
    Int_t getInputNumber() {return inputNumber;}

    // initializes parameter container
    virtual Bool_t init(FairParSet*) {return kFALSE;}

    // writes parameter container to output
    virtual Int_t write(FairParSet*) {return kFALSE;}

    ClassDef(FairDetParIo,0)  // Base class for detector parameter IO
};

#endif  /* !HDETPARIO_H */







/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDETPARROOTFILEIO_H
#define FAIRDETPARROOTFILEIO_H

#include "FairDetParIo.h"               // for FairDetParIo

#include "Rtypes.h"                     // for Int_t, Text_t, etc

using std::fstream;

class FairParRootFile;
class FairParSet;
class TObject;

class FairDetParRootFileIo : public FairDetParIo
{
  protected:
    FairParRootFile* pFile;    // pointer to parameter ROOT file
  public:
    FairDetParRootFileIo(FairParRootFile* f);
    virtual ~FairDetParRootFileIo() {}
    virtual Bool_t read(FairParSet*);
    Int_t write(FairParSet*);
//  Bool_t read(HDetGeomPar*,Int_t*);
  protected:
    Int_t findInputVersion(Text_t* contName);
    Int_t getMaxVersion(Text_t* contName);
    TObject* findContainer(Text_t* contName, Int_t version);
  private:
    FairDetParRootFileIo(const FairDetParRootFileIo&);
    FairDetParRootFileIo& operator= (const FairDetParRootFileIo&);

    ClassDef(FairDetParRootFileIo,0) // detector base class for parameter I/O from ROOT file
};

#endif  /* !FAIRDETPARROOTFILEIO_H */

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGENERICPARASCIIFILEIO_H
#define FAIRGENERICPARASCIIFILEIO_H

#include "FairDetParAsciiFileIo.h"      // for FairDetParAsciiFileIo

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Int_t, Bool_t, etc

#include <fstream>                      // for fstream

class FairParGenericSet;
class FairParSet;
class TString;

class FairGenericParAsciiFileIo : public FairDetParAsciiFileIo
{
  public:
    FairGenericParAsciiFileIo(std::fstream* f=0);
    ~FairGenericParAsciiFileIo() {}
    Bool_t init(FairParSet*);
    Int_t write(FairParSet*);
  private:

    ClassDef(FairGenericParAsciiFileIo,0) // I/O from Ascii file for parameter containers derived from FairParGenericSet
    Bool_t readGenericSet(FairParGenericSet* pPar);
    Int_t writeGenericSet(FairParGenericSet* pPar);

    template <class type> const UChar_t* readData(type,const Char_t*,TString&,Int_t&);
    template <class type> void writeData(type*,Int_t);
};

#endif  /* !FAIRGENERICPARASCIIFILEIO_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGENERICPARROOTFILEIO_H
#define FAIRGENERICPARROOTFILEIO_H

#include "FairDetParRootFileIo.h"       // for FairDetParRootFileIo

#include "Rtypes.h"                    // for ClassDef macro

class FairParRootFile;
class FairParSet;

class FairGenericParRootFileIo : public FairDetParRootFileIo
{
  public:
    FairGenericParRootFileIo(FairParRootFile* f=0);
    ~FairGenericParRootFileIo() {}
    Bool_t init(FairParSet*);
    ClassDef(FairGenericParRootFileIo,0) // I/O from ROOT file for parameter containers derived from FairParGenericSet
};

#endif  /* !FAIRGENERICPARROOTFILEIO_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARASCIFILEIIO_H
#define FAIRPARASCIFILEIIO_H

#include "FairParIo.h"                  // for FairParIo

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Bool_t, Text_t, etc

#include <fstream>                      // for fstream, etc

class TList;

class FairParAsciiFileIo : public FairParIo
{
  protected:
    std::fstream* file;      // pointer to a file
  public:
    FairParAsciiFileIo();

    // default destructor closes an open file and deletes list of I/Os
    ~FairParAsciiFileIo();

    // opens file
    // if a file is already open, this file will be closed
    // activates detector I/Os
    Bool_t open(const Text_t* fname, const Text_t* status="in");

    // concatenate files whose names are stored in the TList
    // TList holds list od TObjStrings
    // create file all.par in local working directory
    // calls open to open the generated file all.par
    Bool_t open(const TList* fnamelist, const Text_t* status="in");

    // closes file
    void close();

    // returns kTRUE if file is open
    Bool_t check() {
      if (file) { return (file->rdbuf()->is_open()==1); }
      else { return kFALSE; }
    }

    // prints information about the file and the detector I/Os
    void print();

    std::fstream* getFile();
  private:
    FairParAsciiFileIo(const FairParAsciiFileIo&);
    FairParAsciiFileIo& operator=(const FairParAsciiFileIo&);

    ClassDef(FairParAsciiFileIo,0) // Parameter I/O from ASCII files
};

#endif  /* !FAIRPARASCIIFILEIO_H */

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARGENERICSET_H
#define FAIRPARGENERICSET_H

#include "FairParSet.h"                 // for FairParSet

#include "Rtypes.h"                     // for Bool_t, etc

class FairParIo;
class FairParamList;

class FairParGenericSet : public FairParSet
{
  public:
    FairParGenericSet(const char* name,const char* title,const char* context, Bool_t ownership=kFALSE)
      : FairParSet(name,title,context,ownership) {}
    virtual ~FairParGenericSet() {}
    virtual void putParams(FairParamList*)=0;
    virtual Bool_t getParams(FairParamList*)=0;
    virtual void printParams();

    Bool_t init(FairParIo* inp);
    Int_t  write(FairParIo* output);

   // DB add on
    void fill(UInt_t) {};
    void store(UInt_t) {};

  protected:
    FairParGenericSet()
      : FairParSet() {}
    ClassDef(FairParGenericSet,1) // Base class for generic-style parameter containers
};

#endif  /* !FAIRPARGENERICSET_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARIO_H
#define FAIRPARIO_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Bool_t, Text_t, etc
#include "TString.h"                    // for TString

class FairDetParIo;
class FairRtdbRun;
class TList;

class FairParIo : public TObject
{
  protected:
    TList* detParIoList;  // list of detector I/Os
    Bool_t autoWritable;  // flag indicating if automatic write is possible
    TString filename;
  public:
    FairParIo();
    virtual ~FairParIo();
    virtual FairDetParIo* getDetParIo(const Text_t*);
    virtual void setDetParIo(FairDetParIo*);
    virtual void removeDetParIo(Text_t*);
    void setInputNumber(Int_t);
    virtual void close() {;}

    // returns the filename
    const char* getFilename() {return filename.Data();}

    // creates input/output class for a special detector and stores pointer
    // used only for Oracle input/output
    // (code in  class OraIo)
    virtual void setDetParIo(Text_t*) {;}

    // prints information about input/output
    virtual void print() {;}

    // checks if the input/output is open
    virtual Bool_t check() { return kFALSE; }

    // reads versions of parameter containers for an event file
    virtual void readVersions(FairRtdbRun*) {;}

    // sets global file pointer in ROOT if input/output is a ROOT-file
    // (code in FairParRootFileIo)
    virtual void cd() {;}

    // set and get for flag autoWritable
    void setAutoWritable(Bool_t f=kTRUE) {autoWritable=f;}
    Bool_t isAutoWritable() {return autoWritable;}

  private:
    FairParIo(const FairParIo&);
    FairParIo& operator=(const FairParIo&);

    ClassDef(FairParIo,0) // Base class for all parameter I/Os
};

#endif  /* !FAIRPARIO_H */




/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARROOTFILEIO_H
#define FAIRPARROOTFILEIO_H

#include "FairParIo.h"                  // for FairParIo

#include "Rtypes.h"                     // for Bool_t, Text_t, Int_t, etc
#include "TFile.h"                      // for TFile
#include "TNamed.h"                     // for TNamed

#include <fstream>
using std::fstream;

class FairRtdbRun;
class TKey;
class TList;

class FairParRootFile : public TNamed
{
  public:
    FairRtdbRun* run;     //! pointer to current run in ROOT file
    FairParRootFile(const Text_t* fname, Option_t* option="READ",
                    const Text_t* ftitle="",Int_t compress=1);
    FairParRootFile(TFile* f);
    ~FairParRootFile();
    FairRtdbRun* getRun() {return run;}
    void readVersions(FairRtdbRun*);

    Bool_t IsOpen() {return RootFile->IsOpen();}
    void   cd() {RootFile->cd();}
    Bool_t IsWritable() {return RootFile->IsWritable();}

    TKey* GetKey(Text_t* t) { return RootFile->GetKey(t);}
    TList* GetListOfKeys() { return RootFile->GetListOfKeys();}
    void Close() {RootFile->Close();}

  protected:
    TFile* RootFile;

  private:
    FairParRootFile(const FairParRootFile&);
    FairParRootFile& operator=(const FairParRootFile&);

    ClassDef(FairParRootFile,0) // ROOT file for Parameter I/O

};


class FairParRootFileIo : public FairParIo
{
  protected:
    FairParRootFile* file;  // pointer to ROOT file
    Bool_t fMerging;
  public:
    FairParRootFileIo();
    FairParRootFileIo(Bool_t merged);
    ~FairParRootFileIo();
    Bool_t open(const Text_t* fname, Option_t* option="READ",
                const Text_t* ftitle="",Int_t compress=1);
    Bool_t open(const TList* fnamelist, Option_t* option="READ",
                const Text_t* ftitle="",Int_t compress=1);
    void close();
    void print();
    FairParRootFile* getParRootFile();
    void readVersions(FairRtdbRun*);
    TList* getKeys();
    Bool_t check() {
      // returns kTRUE if file is open
      if (file) { return file->IsOpen(); }
      else { return kFALSE; }
    }
    void cd() {
      // sets the global ROOT file pointer gFile
      if (file) { file->cd(); }
    }
    /**
    Open an existing root file for IO
    */
    Bool_t open(TFile* f);
    void setMerging( Bool_t io ) { fMerging=io;}

  private:
    FairParRootFileIo(const FairParRootFileIo&);
    FairParRootFileIo& operator=(const FairParRootFileIo&);

    ClassDef(FairParRootFileIo,0) // Parameter I/O from ROOT files
};

#endif  /* !FAIRPARROOTFILEIO_H */

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARSET_H
#define FAIRPARSET_H

#include "TNamed.h"
#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "TString.h"                    // for TString

class FairLogger;
class FairParIo;

class FairParSet : public TObject
{
  protected:
    TString fName;         //
    TString fTitle;        //
    TString detName;         //! name of the detector the container belongs to
    Int_t versions[3];       //! versions of container in the 2 possible inputs
    Bool_t status;           //! static flag
    Bool_t changed;          //! flag is kTRUE if parameters have changed
    Bool_t  owned;          //! if flag is KTRUE FairDB has the par. class ownership
    TString paramContext;    // Context/purpose for parameters and conditions
    TString author;          // Author of parameters
    TString description ;    // Description of parameters
    /** Fair Logger */
    FairLogger*  fLogger;  //!

  public:
    FairParSet(const char* name="",const char* title="",const char* context="", Bool_t owner=kFALSE);
    virtual ~FairParSet() {}

    virtual const char* GetName() const {return static_cast<const char*>(fName.Data());}
    virtual const char* GetTitle() const {return static_cast<const char*>(fTitle.Data());}

    virtual Bool_t init();
    virtual Bool_t init(FairParIo*) { return kFALSE; }
    virtual Int_t write();
    virtual Int_t write(FairParIo*) { return kFALSE; }
    virtual void clear() {}
    virtual void print();

    const char* getDetectorName() {return detName.Data();}
    void resetInputVersions();

    void setInputVersion(Int_t v=-1,Int_t i=0) {
      if (i>=0 && i<3) { versions[i]=v; }
    }
    Int_t getInputVersion(Int_t i) {
      if (i>=0 && i<3) { return versions[i]; }
      else { return 0; }
    }

    void setStatic(Bool_t flag=kTRUE) {status=flag;}
    Bool_t isStatic() {return status;}

    void setOwnership(Bool_t flag=kTRUE) {owned=flag;}
    Bool_t isOwned() {return owned;}

    void setChanged(Bool_t flag=kTRUE) {changed=flag;}
    Bool_t hasChanged() {return changed;}

    const char* getParamContext() const { return paramContext.Data(); }

    void setAuthor(const char* s) {author=s;}
    const char* getAuthor() const { return author.Data(); }

    void setDescription(const char* s) {description=s;}
    const char* getDescription() const { return description.Data(); }

    void copyComment(FairParSet& r) {
      author=r.getAuthor();
      description=r.getDescription();
    }


    virtual void fill(UInt_t) {};
    virtual void store(UInt_t) {};
    

    FairParSet& operator=(const FairParSet&);
    FairParSet(const FairParSet&);

    ClassDef(FairParSet,2) // Base class for all parameter containers
};

#endif  /* !FAIRPARSET_H */

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRPARAMLIST_H
#define FAIRPARAMLIST_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Text_t, Int_t, Bool_t, etc
#include "TArrayC.h"                    // for TArrayC
#include "TFile.h"                      // for TFile
#include "TList.h"                      // for TList
#include "TObject.h"                    // for TObject
#include "TROOT.h"                      // for TROOT, gROOT
#include "TSeqCollection.h"             // for TSeqCollection
#include "TString.h"                    // for TString

class FairLogger;
class TArrayD;
class TArrayF;
class TArrayI;

class FairParamObj : public TNamed
{
  protected:
    UChar_t* paramValue;    // Pointer to binary array
    Int_t arraySize;        // Size of binary array
    TString paramType;      // Type of parameter value or class name
    Bool_t basicType;       // kTRUE for C-types and C-type parameter arrays, kFALSE for classes
    Int_t bytesPerValue;    // number of bytes per value
    Int_t classVersion;     // Code version of classes stored as binary
    UChar_t* streamerInfo;  // Pointer to binary array container the streamer info
    Int_t streamerInfoSize; // Size of streamer info array
  public:
    FairParamObj(const Text_t* name="");
    FairParamObj(FairParamObj&);
    FairParamObj(const Text_t*,Int_t);
    FairParamObj(const Text_t*,Bool_t);
    FairParamObj(const Text_t*,UInt_t);
    FairParamObj(const Text_t*,Float_t);
    FairParamObj(const Text_t*,Double_t);
    FairParamObj(const Text_t*,const Int_t*,const Int_t);
    FairParamObj(const Text_t*,const UInt_t*,const Int_t);
    FairParamObj(const Text_t*,const Float_t*,const Int_t);
    FairParamObj(const Text_t*,const Double_t*,const Int_t);
    FairParamObj(const Text_t*,const Text_t*);
    FairParamObj(const Text_t*,const Char_t*,const Int_t);
    FairParamObj(const Text_t*,const UChar_t*,const Int_t);
    ~FairParamObj();
    void setParamType(const Text_t* t);
    UChar_t* setLength(Int_t l);
    void setParamValue(UChar_t*,const Int_t);
    void setClassVersion(const Int_t v) { classVersion=v; }
    UChar_t* setStreamerInfoSize(Int_t);
    void setStreamerInfo(UChar_t*,const Int_t);
    UChar_t* getParamValue() { return paramValue; }
    Bool_t isBasicType() { return basicType; }
    const char* getParamType() { return paramType.Data(); }
    Int_t getBytesPerValue() { return bytesPerValue; }
    Int_t getClassVersion() { return classVersion; }
    Int_t getLength() { return arraySize; }
    Int_t getNumParams();
    UChar_t* getStreamerInfo() { return streamerInfo; }
    Int_t getStreamerInfoSize() { return streamerInfoSize; }
    void print();
  protected:
    template <class type> void printData(type*,Int_t);

  private:
    FairParamObj& operator=(const FairParamObj&);

    ClassDef(FairParamObj,0) // Class for binary parameter object (name + binary array)
};


class FairParamList : public TObject
{
  protected:
    TList* paramList;      // List for parameters stored as string
    FairLogger* fLogger;  // FairRoot logging mechanism
    class FairParamTFile : public TFile
    {
      public:
        FairParamTFile() {
          // Create StreamerInfo index
          Int_t lenIndex = gROOT->GetListOfStreamerInfo()->GetSize()+1;
          if (lenIndex < 5000) { lenIndex = 5000; }
          fClassIndex = new TArrayC(lenIndex);
        }
        ~FairParamTFile() {
          delete fClassIndex;
          fClassIndex=0;
        }
    };
  public:
    FairParamList();
    ~FairParamList();
    void add(FairParamObj&);
    void add(const Text_t*,const Text_t*);
    void add(const Text_t*,Int_t);
    void add(const Text_t*,Bool_t);
    void add(const Text_t*,UInt_t);
    void add(const Text_t*,Float_t);
    void add(const Text_t*,Double_t);
    void add(const Text_t*,TArrayI&);
    void add(const Text_t*,TArrayC&);
    void add(const Text_t*,TArrayF&);
    void add(const Text_t*,TArrayD&);
    void add(const Text_t*,const UChar_t*,const Int_t);
    void add(const Text_t*,const Int_t*,const Int_t);
    void add(const Text_t*,const Float_t*,const Int_t);
    void add(const Text_t*,const Double_t*,const Int_t);
    void addObject(const Text_t*,TObject*);
    Bool_t fill(const Text_t*,Text_t*,const Int_t);
    Bool_t fill(const Text_t*,Int_t*,const Int_t nValues=1);
    Bool_t fill(const Text_t*,Bool_t*,const Int_t nValues=1);
    Bool_t fill(const Text_t*,UInt_t*,const Int_t nValues=1);
    Bool_t fill(const Text_t*,Float_t*,const Int_t nValues=1);
    Bool_t fill(const Text_t*,Double_t*,const Int_t nValues=1);
    Bool_t fill(const Text_t*,UChar_t*,const Int_t nValues=1);
    Bool_t fill(const Text_t*,TArrayI*);
    Bool_t fill(const Text_t*,TArrayC*);
    Bool_t fill(const Text_t*,TArrayF*);
    Bool_t fill(const Text_t*,TArrayD*);
    Bool_t fillObject(const Text_t*,TObject*);
    void print();
    FairParamObj* find(const Text_t* name) {
      return static_cast<FairParamObj*>(paramList->FindObject(name));
    }
    TList* getList() { return paramList; }
  private:
    FairParamList(const FairParamList&);
    FairParamList& operator=(const FairParamList&);

    ClassDef(FairParamList,3) // Class for lists of parameters (of type FairParamObj)
};

#endif  /* !FAIRPARAMLIST_H */

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRTDBRUN_H
#define FAIRRTDBRUN_H

#include "TNamed.h"                     // for TNamed

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Int_t, Text_t, UInt_t, etc
#include "TString.h"                    // for TString

#include <stdio.h>                      // for sprintf, sscanf
#include <fstream>                      // for fstream

class TList;
using std::fstream;

class FairParVersion : public TNamed
{
  protected:
    Int_t inputVersions[3]; //! version of the parameter container in the 2 possible inputs
    Int_t rootVersion;      // version of the parameter container in the ROOT output file
  public:
    FairParVersion() : TNamed(),rootVersion(0) {}
    FairParVersion(Text_t* name);
    ~FairParVersion() {}
    void setInputVersion(Int_t v=-1,Int_t i=0) {
      if (i>=0 && i<3) { inputVersions[i]=v; }
    }
    Int_t getInputVersion(Int_t i) {
      if (i>=0 && i<3) { return inputVersions[i]; }
      else { return -1; }
    }
    void resetInputVersions() {
      for(Int_t i=0; i<3; i++) {inputVersions[i]=-1;}
    }
    void setRootVersion(Int_t v) {rootVersion=v;}
    Int_t getRootVersion() {return rootVersion;}
    ClassDef(FairParVersion,1) // Class for parameter versions
};

class FairRtdbRun : public TNamed
{
  protected:
    TList* parVersions;   // List of container names with the versions
    TString refRun;       //! name of the reference run for initialization
  public:
    FairRtdbRun();
    FairRtdbRun(const Text_t* name,const Text_t* refName="");
    FairRtdbRun(Int_t r,Int_t rr=-1);
    FairRtdbRun(FairRtdbRun& run);
    ~FairRtdbRun();
    inline UInt_t getRunId(void);
    void addParVersion(FairParVersion* pv);
    FairParVersion* getParVersion(const Text_t* name);
    TList* getParVersions() {return parVersions;}
    const Text_t* getRefRun() {return refRun.Data();}
    void setRefRun(Text_t* s) {refRun=s;}
    inline void setRefRun(Int_t r);
    void resetInputVersions();
    void resetOutputVersions();
    void print();
    void write(std::fstream&);

  private:
    FairRtdbRun& operator=(const FairRtdbRun&);

    ClassDef(FairRtdbRun,1) // Class for parameter version management of a run
};

// -------------------- inlines ---------------------------

inline UInt_t FairRtdbRun::getRunId(void)
{
  UInt_t r;
  sscanf(GetName(),"%i",&r);
  return r;
}

inline void FairRtdbRun::setRefRun(Int_t r)
{
  if (r==-1) { refRun=""; }
  else {
    char name[255];
    sprintf(name,"%i",r);
    refRun=name;
  }
}

#endif  /* !FAIRRTDBRUN_H */

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNTIMEDB_H
#define FAIRRUNTIMEDB_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Bool_t, Int_t, Text_t, etc
#include "TList.h"                      // for TList
#include "TString.h"                    // for TString

class FairContFact;
class FairLogger;
class FairParIo;
class FairParSet;
class FairRtdbRun;

static TList contFactories;    //! list of container factories

class FairRuntimeDb : public TObject
{
  private:
    static FairRuntimeDb* gRtdb; //!

  protected:
    FairRuntimeDb(void);
    TList* containerList;    // list of parameter containers
    TList* runs;             // list of runs
    FairParIo* firstInput;    // first (prefered) input for parameters
    FairParIo* secondInput;   // second input (used if not found in first input)
    FairParIo* output;        // output for parameters
    FairRtdbRun* currentRun;  // Current run
    TString currentFileName; // Name of current event file
    Bool_t versionsChanged;  // flag for write of list of runs (set kTRUE by each write)
    Bool_t isRootFileOutput; // flag indicating that the output is a ROOT file
    /** Fair Logger */
    FairLogger*  fLogger;  //!

    /**
     * Select which IO type to use.
     */
    typedef enum {
      UNKNOWN_Type    = 0,
      AsciiFileOutput = 1, // Ascii in-out-put
      RootFileOutput  = 2, // Root Files
      RootTSQLOutput  = 3  // Use a TSQL db
    } ParamIOType;
    ParamIOType ioType;//IO Type

  public:
    static FairRuntimeDb* instance(void);
    ~FairRuntimeDb(void);

    Bool_t addParamContext(const char*);
    void printParamContexts();
    void addContFactory(FairContFact*);
    FairContFact* getContFactory(const Text_t*);

    Bool_t addContainer(FairParSet*);
    FairParSet* getContainer(const Text_t*);
    FairParSet* findContainer(const char*);
    void removeContainer(Text_t*);
    void removeAllContainers(void);
    Bool_t initContainers(Int_t runId,Int_t refId=-1,const Text_t* fileName="");
    void setContainersStatic(Bool_t f=kTRUE);
    Bool_t writeContainers(void);
    Bool_t writeContainer(FairParSet*,FairRtdbRun*,FairRtdbRun* refRun=0);

    FairRtdbRun* addRun(Int_t runId,Int_t refId=-1);
    FairRtdbRun* getRun(Int_t);
    FairRtdbRun* getRun(Text_t*);
    FairRtdbRun* getCurrentRun(void) {return currentRun;}
    Text_t const* getCurrentFileName() {return currentFileName.Data();}
    void clearRunList(void);

    void removeRun(Text_t*);

    Bool_t setInputVersion(Int_t run,Text_t* container,
                           Int_t version,Int_t inputNumber);
    Bool_t setRootOutputVersion(Int_t run,Text_t* container,Int_t version);
    void setVersionsChanged(Bool_t f=kTRUE) {versionsChanged=f;}
    void resetInputVersions(void);
    void resetOutputVersions(void);
    void resetAllVersions(void);

    Bool_t readAll(void);
    void writeVersions(void);
    void saveOutput(void);

    Bool_t setFirstInput(FairParIo*);
    Bool_t setSecondInput(FairParIo*);
    Bool_t setOutput(FairParIo*);
    FairParIo* getFirstInput(void);
    FairParIo* getSecondInput(void);
    FairParIo* getOutput(void);
    void closeFirstInput(void);
    void closeSecondInput(void);
    void closeOutput(void);
    void activateParIo(FairParIo*);
    TList* getListOfContainers() {return containerList;}
    void print(void);

    Int_t findOutputVersion(FairParSet*);

  private:
    FairRuntimeDb(const FairRuntimeDb& M);
    FairRuntimeDb& operator= (const  FairRuntimeDb&) {return *this;}
    Bool_t initContainers(void);

    ClassDef(FairRuntimeDb,0) // Class for runtime database
};

#endif  /* !FAIRRUNTIMEDB_H */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairContFact", payloadCode, "@",
"FairContainer", payloadCode, "@",
"FairDetParAsciiFileIo", payloadCode, "@",
"FairDetParIo", payloadCode, "@",
"FairDetParRootFileIo", payloadCode, "@",
"FairGenericParAsciiFileIo", payloadCode, "@",
"FairGenericParRootFileIo", payloadCode, "@",
"FairParAsciiFileIo", payloadCode, "@",
"FairParGenericSet", payloadCode, "@",
"FairParIo", payloadCode, "@",
"FairParRootFile", payloadCode, "@",
"FairParRootFileIo", payloadCode, "@",
"FairParSet", payloadCode, "@",
"FairParVersion", payloadCode, "@",
"FairParamList", payloadCode, "@",
"FairParamObj", payloadCode, "@",
"FairRtdbRun", payloadCode, "@",
"FairRuntimeDb", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__ParBaseDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__ParBaseDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__ParBaseDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__ParBaseDict() {
  TriggerDictionaryInitialization_G__ParBaseDict_Impl();
}

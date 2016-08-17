// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIadvanceddITutorial3dIG__FairTestDetectorDict

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
#include "simulation/FairTestDetector.h"
#include "simulation/FairTestDetectorContFact.h"
#include "simulation/FairTestDetectorGeo.h"
#include "simulation/FairTestDetectorGeoPar.h"
#include "simulation/FairConstField.h"
#include "simulation/FairConstPar.h"
#include "simulation/FairMapPar.h"
#include "data/FairTestDetectorPoint.h"
#include "data/FairTestDetectorHit.h"
#include "digitization/FairTestDetectorHitProducerSmearing.h"
#include "digitization/FairTestDetectorDigiTask.h"
#include "reconstruction/FairTestDetectorRecoTask.h"
#include "timeBasedSimulation/FairTestDetectorDigiRingSorter.h"
#include "timeBasedSimulation/FairTestDetectorDigiSorterTask.h"
#include "timeBasedSimulation/FairTestDetectorDigiWriteoutBuffer.h"
#include "timeBasedSimulation/FairTestDetectorTimeDigiTask.h"
#include "timeBasedSimulation/FairTestDetectorTimeRecoTask.h"
#include "data/FairTestDetectorDigi.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairTestDetectorContFact(void *p = 0);
   static void *newArray_FairTestDetectorContFact(Long_t size, void *p);
   static void delete_FairTestDetectorContFact(void *p);
   static void deleteArray_FairTestDetectorContFact(void *p);
   static void destruct_FairTestDetectorContFact(void *p);
   static void streamer_FairTestDetectorContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorContFact*)
   {
      ::FairTestDetectorContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorContFact", ::FairTestDetectorContFact::Class_Version(), "invalid", 150,
                  typeid(::FairTestDetectorContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorContFact::Dictionary, isa_proxy, 16,
                  sizeof(::FairTestDetectorContFact) );
      instance.SetNew(&new_FairTestDetectorContFact);
      instance.SetNewArray(&newArray_FairTestDetectorContFact);
      instance.SetDelete(&delete_FairTestDetectorContFact);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorContFact);
      instance.SetDestructor(&destruct_FairTestDetectorContFact);
      instance.SetStreamerFunc(&streamer_FairTestDetectorContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorContFact*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorGeo(void *p = 0);
   static void *newArray_FairTestDetectorGeo(Long_t size, void *p);
   static void delete_FairTestDetectorGeo(void *p);
   static void deleteArray_FairTestDetectorGeo(void *p);
   static void destruct_FairTestDetectorGeo(void *p);
   static void streamer_FairTestDetectorGeo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorGeo*)
   {
      ::FairTestDetectorGeo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorGeo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorGeo", ::FairTestDetectorGeo::Class_Version(), "invalid", 181,
                  typeid(::FairTestDetectorGeo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorGeo::Dictionary, isa_proxy, 16,
                  sizeof(::FairTestDetectorGeo) );
      instance.SetNew(&new_FairTestDetectorGeo);
      instance.SetNewArray(&newArray_FairTestDetectorGeo);
      instance.SetDelete(&delete_FairTestDetectorGeo);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorGeo);
      instance.SetDestructor(&destruct_FairTestDetectorGeo);
      instance.SetStreamerFunc(&streamer_FairTestDetectorGeo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorGeo*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorGeo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorGeo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorGeoPar(void *p = 0);
   static void *newArray_FairTestDetectorGeoPar(Long_t size, void *p);
   static void delete_FairTestDetectorGeoPar(void *p);
   static void deleteArray_FairTestDetectorGeoPar(void *p);
   static void destruct_FairTestDetectorGeoPar(void *p);
   static void streamer_FairTestDetectorGeoPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorGeoPar*)
   {
      ::FairTestDetectorGeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorGeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorGeoPar", ::FairTestDetectorGeoPar::Class_Version(), "invalid", 227,
                  typeid(::FairTestDetectorGeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorGeoPar::Dictionary, isa_proxy, 16,
                  sizeof(::FairTestDetectorGeoPar) );
      instance.SetNew(&new_FairTestDetectorGeoPar);
      instance.SetNewArray(&newArray_FairTestDetectorGeoPar);
      instance.SetDelete(&delete_FairTestDetectorGeoPar);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorGeoPar);
      instance.SetDestructor(&destruct_FairTestDetectorGeoPar);
      instance.SetStreamerFunc(&streamer_FairTestDetectorGeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorGeoPar*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorGeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorGeoPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetector(void *p = 0);
   static void *newArray_FairTestDetector(Long_t size, void *p);
   static void delete_FairTestDetector(void *p);
   static void deleteArray_FairTestDetector(void *p);
   static void destruct_FairTestDetector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetector*)
   {
      ::FairTestDetector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetector", ::FairTestDetector::Class_Version(), "invalid", 26,
                  typeid(::FairTestDetector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetector::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetector) );
      instance.SetNew(&new_FairTestDetector);
      instance.SetNewArray(&newArray_FairTestDetector);
      instance.SetDelete(&delete_FairTestDetector);
      instance.SetDeleteArray(&deleteArray_FairTestDetector);
      instance.SetDestructor(&destruct_FairTestDetector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetector*)
   {
      return GenerateInitInstanceLocal((::FairTestDetector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetector*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorPoint(void *p = 0);
   static void *newArray_FairTestDetectorPoint(Long_t size, void *p);
   static void delete_FairTestDetectorPoint(void *p);
   static void deleteArray_FairTestDetectorPoint(void *p);
   static void destruct_FairTestDetectorPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorPoint*)
   {
      ::FairTestDetectorPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorPoint", ::FairTestDetectorPoint::Class_Version(), "invalid", 596,
                  typeid(::FairTestDetectorPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorPoint::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorPoint) );
      instance.SetNew(&new_FairTestDetectorPoint);
      instance.SetNewArray(&newArray_FairTestDetectorPoint);
      instance.SetDelete(&delete_FairTestDetectorPoint);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorPoint);
      instance.SetDestructor(&destruct_FairTestDetectorPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorPoint*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorPoint*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorHit(void *p = 0);
   static void *newArray_FairTestDetectorHit(Long_t size, void *p);
   static void delete_FairTestDetectorHit(void *p);
   static void deleteArray_FairTestDetectorHit(void *p);
   static void destruct_FairTestDetectorHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorHit*)
   {
      ::FairTestDetectorHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorHit", ::FairTestDetectorHit::Class_Version(), "invalid", 725,
                  typeid(::FairTestDetectorHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorHit::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorHit) );
      instance.SetNew(&new_FairTestDetectorHit);
      instance.SetNewArray(&newArray_FairTestDetectorHit);
      instance.SetDelete(&delete_FairTestDetectorHit);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorHit);
      instance.SetDestructor(&destruct_FairTestDetectorHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorHit*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorDigi(void *p = 0);
   static void *newArray_FairTestDetectorDigi(Long_t size, void *p);
   static void delete_FairTestDetectorDigi(void *p);
   static void deleteArray_FairTestDetectorDigi(void *p);
   static void destruct_FairTestDetectorDigi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorDigi*)
   {
      ::FairTestDetectorDigi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorDigi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorDigi", ::FairTestDetectorDigi::Class_Version(), "FairTestDetectorDigi.h", 32,
                  typeid(::FairTestDetectorDigi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorDigi::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorDigi) );
      instance.SetNew(&new_FairTestDetectorDigi);
      instance.SetNewArray(&newArray_FairTestDetectorDigi);
      instance.SetDelete(&delete_FairTestDetectorDigi);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorDigi);
      instance.SetDestructor(&destruct_FairTestDetectorDigi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorDigi*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorDigi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorDigi*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorHitProducerSmearing(void *p = 0);
   static void *newArray_FairTestDetectorHitProducerSmearing(Long_t size, void *p);
   static void delete_FairTestDetectorHitProducerSmearing(void *p);
   static void deleteArray_FairTestDetectorHitProducerSmearing(void *p);
   static void destruct_FairTestDetectorHitProducerSmearing(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorHitProducerSmearing*)
   {
      ::FairTestDetectorHitProducerSmearing *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorHitProducerSmearing >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorHitProducerSmearing", ::FairTestDetectorHitProducerSmearing::Class_Version(), "invalid", 769,
                  typeid(::FairTestDetectorHitProducerSmearing), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorHitProducerSmearing::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorHitProducerSmearing) );
      instance.SetNew(&new_FairTestDetectorHitProducerSmearing);
      instance.SetNewArray(&newArray_FairTestDetectorHitProducerSmearing);
      instance.SetDelete(&delete_FairTestDetectorHitProducerSmearing);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorHitProducerSmearing);
      instance.SetDestructor(&destruct_FairTestDetectorHitProducerSmearing);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorHitProducerSmearing*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorHitProducerSmearing*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorHitProducerSmearing*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorDigiTask(void *p = 0);
   static void *newArray_FairTestDetectorDigiTask(Long_t size, void *p);
   static void delete_FairTestDetectorDigiTask(void *p);
   static void deleteArray_FairTestDetectorDigiTask(void *p);
   static void destruct_FairTestDetectorDigiTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorDigiTask*)
   {
      ::FairTestDetectorDigiTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorDigiTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorDigiTask", ::FairTestDetectorDigiTask::Class_Version(), "invalid", 824,
                  typeid(::FairTestDetectorDigiTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorDigiTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorDigiTask) );
      instance.SetNew(&new_FairTestDetectorDigiTask);
      instance.SetNewArray(&newArray_FairTestDetectorDigiTask);
      instance.SetDelete(&delete_FairTestDetectorDigiTask);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorDigiTask);
      instance.SetDestructor(&destruct_FairTestDetectorDigiTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorDigiTask*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorDigiTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorDigiTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorRecoTask(void *p = 0);
   static void *newArray_FairTestDetectorRecoTask(Long_t size, void *p);
   static void delete_FairTestDetectorRecoTask(void *p);
   static void deleteArray_FairTestDetectorRecoTask(void *p);
   static void destruct_FairTestDetectorRecoTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorRecoTask*)
   {
      ::FairTestDetectorRecoTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorRecoTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorRecoTask", ::FairTestDetectorRecoTask::Class_Version(), "invalid", 881,
                  typeid(::FairTestDetectorRecoTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorRecoTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorRecoTask) );
      instance.SetNew(&new_FairTestDetectorRecoTask);
      instance.SetNewArray(&newArray_FairTestDetectorRecoTask);
      instance.SetDelete(&delete_FairTestDetectorRecoTask);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorRecoTask);
      instance.SetDestructor(&destruct_FairTestDetectorRecoTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorRecoTask*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorRecoTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorRecoTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairConstField(void *p = 0);
   static void *newArray_FairConstField(Long_t size, void *p);
   static void delete_FairConstField(void *p);
   static void deleteArray_FairConstField(void *p);
   static void destruct_FairConstField(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairConstField*)
   {
      ::FairConstField *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairConstField >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairConstField", ::FairConstField::Class_Version(), "invalid", 284,
                  typeid(::FairConstField), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairConstField::Dictionary, isa_proxy, 4,
                  sizeof(::FairConstField) );
      instance.SetNew(&new_FairConstField);
      instance.SetNewArray(&newArray_FairConstField);
      instance.SetDelete(&delete_FairConstField);
      instance.SetDeleteArray(&deleteArray_FairConstField);
      instance.SetDestructor(&destruct_FairConstField);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairConstField*)
   {
      return GenerateInitInstanceLocal((::FairConstField*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairConstField*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairConstPar(void *p = 0);
   static void *newArray_FairConstPar(Long_t size, void *p);
   static void delete_FairConstPar(void *p);
   static void deleteArray_FairConstPar(void *p);
   static void destruct_FairConstPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairConstPar*)
   {
      ::FairConstPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairConstPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairConstPar", ::FairConstPar::Class_Version(), "invalid", 423,
                  typeid(::FairConstPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairConstPar::Dictionary, isa_proxy, 4,
                  sizeof(::FairConstPar) );
      instance.SetNew(&new_FairConstPar);
      instance.SetNewArray(&newArray_FairConstPar);
      instance.SetDelete(&delete_FairConstPar);
      instance.SetDeleteArray(&deleteArray_FairConstPar);
      instance.SetDestructor(&destruct_FairConstPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairConstPar*)
   {
      return GenerateInitInstanceLocal((::FairConstPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairConstPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairMapPar(void *p);
   static void deleteArray_FairMapPar(void *p);
   static void destruct_FairMapPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMapPar*)
   {
      ::FairMapPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMapPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMapPar", ::FairMapPar::Class_Version(), "FairMapPar.h", 25,
                  typeid(::FairMapPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMapPar::Dictionary, isa_proxy, 4,
                  sizeof(::FairMapPar) );
      instance.SetDelete(&delete_FairMapPar);
      instance.SetDeleteArray(&deleteArray_FairMapPar);
      instance.SetDestructor(&destruct_FairMapPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMapPar*)
   {
      return GenerateInitInstanceLocal((::FairMapPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMapPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorDigiWriteoutBuffer(void *p = 0);
   static void *newArray_FairTestDetectorDigiWriteoutBuffer(Long_t size, void *p);
   static void delete_FairTestDetectorDigiWriteoutBuffer(void *p);
   static void deleteArray_FairTestDetectorDigiWriteoutBuffer(void *p);
   static void destruct_FairTestDetectorDigiWriteoutBuffer(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorDigiWriteoutBuffer*)
   {
      ::FairTestDetectorDigiWriteoutBuffer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorDigiWriteoutBuffer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorDigiWriteoutBuffer", ::FairTestDetectorDigiWriteoutBuffer::Class_Version(), "invalid", 1018,
                  typeid(::FairTestDetectorDigiWriteoutBuffer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorDigiWriteoutBuffer::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorDigiWriteoutBuffer) );
      instance.SetNew(&new_FairTestDetectorDigiWriteoutBuffer);
      instance.SetNewArray(&newArray_FairTestDetectorDigiWriteoutBuffer);
      instance.SetDelete(&delete_FairTestDetectorDigiWriteoutBuffer);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorDigiWriteoutBuffer);
      instance.SetDestructor(&destruct_FairTestDetectorDigiWriteoutBuffer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorDigiWriteoutBuffer*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorDigiWriteoutBuffer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorDigiWriteoutBuffer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorTimeDigiTask(void *p = 0);
   static void *newArray_FairTestDetectorTimeDigiTask(Long_t size, void *p);
   static void delete_FairTestDetectorTimeDigiTask(void *p);
   static void deleteArray_FairTestDetectorTimeDigiTask(void *p);
   static void destruct_FairTestDetectorTimeDigiTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorTimeDigiTask*)
   {
      ::FairTestDetectorTimeDigiTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorTimeDigiTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorTimeDigiTask", ::FairTestDetectorTimeDigiTask::Class_Version(), "invalid", 1058,
                  typeid(::FairTestDetectorTimeDigiTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorTimeDigiTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorTimeDigiTask) );
      instance.SetNew(&new_FairTestDetectorTimeDigiTask);
      instance.SetNewArray(&newArray_FairTestDetectorTimeDigiTask);
      instance.SetDelete(&delete_FairTestDetectorTimeDigiTask);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorTimeDigiTask);
      instance.SetDestructor(&destruct_FairTestDetectorTimeDigiTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorTimeDigiTask*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorTimeDigiTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorTimeDigiTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorTimeRecoTask(void *p = 0);
   static void *newArray_FairTestDetectorTimeRecoTask(Long_t size, void *p);
   static void delete_FairTestDetectorTimeRecoTask(void *p);
   static void deleteArray_FairTestDetectorTimeRecoTask(void *p);
   static void destruct_FairTestDetectorTimeRecoTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorTimeRecoTask*)
   {
      ::FairTestDetectorTimeRecoTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorTimeRecoTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorTimeRecoTask", ::FairTestDetectorTimeRecoTask::Class_Version(), "invalid", 1125,
                  typeid(::FairTestDetectorTimeRecoTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorTimeRecoTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorTimeRecoTask) );
      instance.SetNew(&new_FairTestDetectorTimeRecoTask);
      instance.SetNewArray(&newArray_FairTestDetectorTimeRecoTask);
      instance.SetDelete(&delete_FairTestDetectorTimeRecoTask);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorTimeRecoTask);
      instance.SetDestructor(&destruct_FairTestDetectorTimeRecoTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorTimeRecoTask*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorTimeRecoTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorTimeRecoTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorDigiRingSorter(void *p = 0);
   static void *newArray_FairTestDetectorDigiRingSorter(Long_t size, void *p);
   static void delete_FairTestDetectorDigiRingSorter(void *p);
   static void deleteArray_FairTestDetectorDigiRingSorter(void *p);
   static void destruct_FairTestDetectorDigiRingSorter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorDigiRingSorter*)
   {
      ::FairTestDetectorDigiRingSorter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorDigiRingSorter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorDigiRingSorter", ::FairTestDetectorDigiRingSorter::Class_Version(), "invalid", 932,
                  typeid(::FairTestDetectorDigiRingSorter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorDigiRingSorter::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorDigiRingSorter) );
      instance.SetNew(&new_FairTestDetectorDigiRingSorter);
      instance.SetNewArray(&newArray_FairTestDetectorDigiRingSorter);
      instance.SetDelete(&delete_FairTestDetectorDigiRingSorter);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorDigiRingSorter);
      instance.SetDestructor(&destruct_FairTestDetectorDigiRingSorter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorDigiRingSorter*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorDigiRingSorter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorDigiRingSorter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTestDetectorDigiSorterTask(void *p = 0);
   static void *newArray_FairTestDetectorDigiSorterTask(Long_t size, void *p);
   static void delete_FairTestDetectorDigiSorterTask(void *p);
   static void deleteArray_FairTestDetectorDigiSorterTask(void *p);
   static void destruct_FairTestDetectorDigiSorterTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTestDetectorDigiSorterTask*)
   {
      ::FairTestDetectorDigiSorterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTestDetectorDigiSorterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTestDetectorDigiSorterTask", ::FairTestDetectorDigiSorterTask::Class_Version(), "invalid", 971,
                  typeid(::FairTestDetectorDigiSorterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTestDetectorDigiSorterTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairTestDetectorDigiSorterTask) );
      instance.SetNew(&new_FairTestDetectorDigiSorterTask);
      instance.SetNewArray(&newArray_FairTestDetectorDigiSorterTask);
      instance.SetDelete(&delete_FairTestDetectorDigiSorterTask);
      instance.SetDeleteArray(&deleteArray_FairTestDetectorDigiSorterTask);
      instance.SetDestructor(&destruct_FairTestDetectorDigiSorterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTestDetectorDigiSorterTask*)
   {
      return GenerateInitInstanceLocal((::FairTestDetectorDigiSorterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTestDetectorDigiSorterTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorContFact::Class_Name()
{
   return "FairTestDetectorContFact";
}

//______________________________________________________________________________
const char *FairTestDetectorContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorGeo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorGeo::Class_Name()
{
   return "FairTestDetectorGeo";
}

//______________________________________________________________________________
const char *FairTestDetectorGeo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorGeo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorGeo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorGeo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorGeo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorGeo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorGeo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorGeo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorGeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorGeoPar::Class_Name()
{
   return "FairTestDetectorGeoPar";
}

//______________________________________________________________________________
const char *FairTestDetectorGeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorGeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorGeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorGeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorGeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorGeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorGeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorGeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetector::Class_Name()
{
   return "FairTestDetector";
}

//______________________________________________________________________________
const char *FairTestDetector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorPoint::Class_Name()
{
   return "FairTestDetectorPoint";
}

//______________________________________________________________________________
const char *FairTestDetectorPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorHit::Class_Name()
{
   return "FairTestDetectorHit";
}

//______________________________________________________________________________
const char *FairTestDetectorHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorDigi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorDigi::Class_Name()
{
   return "FairTestDetectorDigi";
}

//______________________________________________________________________________
const char *FairTestDetectorDigi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorDigi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorDigi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorDigi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorHitProducerSmearing::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorHitProducerSmearing::Class_Name()
{
   return "FairTestDetectorHitProducerSmearing";
}

//______________________________________________________________________________
const char *FairTestDetectorHitProducerSmearing::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorHitProducerSmearing*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorHitProducerSmearing::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorHitProducerSmearing*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorHitProducerSmearing::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorHitProducerSmearing*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorHitProducerSmearing::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorHitProducerSmearing*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorDigiTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorDigiTask::Class_Name()
{
   return "FairTestDetectorDigiTask";
}

//______________________________________________________________________________
const char *FairTestDetectorDigiTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorDigiTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorDigiTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorDigiTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorRecoTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorRecoTask::Class_Name()
{
   return "FairTestDetectorRecoTask";
}

//______________________________________________________________________________
const char *FairTestDetectorRecoTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorRecoTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorRecoTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorRecoTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorRecoTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorRecoTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorRecoTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorRecoTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairConstField::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairConstField::Class_Name()
{
   return "FairConstField";
}

//______________________________________________________________________________
const char *FairConstField::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairConstField*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairConstField::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairConstField*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairConstField::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairConstField*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairConstField::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairConstField*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairConstPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairConstPar::Class_Name()
{
   return "FairConstPar";
}

//______________________________________________________________________________
const char *FairConstPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairConstPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairConstPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairConstPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairConstPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairConstPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairConstPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairConstPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMapPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMapPar::Class_Name()
{
   return "FairMapPar";
}

//______________________________________________________________________________
const char *FairMapPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMapPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMapPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMapPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMapPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMapPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMapPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMapPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorDigiWriteoutBuffer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorDigiWriteoutBuffer::Class_Name()
{
   return "FairTestDetectorDigiWriteoutBuffer";
}

//______________________________________________________________________________
const char *FairTestDetectorDigiWriteoutBuffer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiWriteoutBuffer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorDigiWriteoutBuffer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiWriteoutBuffer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorDigiWriteoutBuffer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiWriteoutBuffer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorDigiWriteoutBuffer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiWriteoutBuffer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorTimeDigiTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorTimeDigiTask::Class_Name()
{
   return "FairTestDetectorTimeDigiTask";
}

//______________________________________________________________________________
const char *FairTestDetectorTimeDigiTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorTimeDigiTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorTimeDigiTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorTimeDigiTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorTimeDigiTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorTimeDigiTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorTimeDigiTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorTimeDigiTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorTimeRecoTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorTimeRecoTask::Class_Name()
{
   return "FairTestDetectorTimeRecoTask";
}

//______________________________________________________________________________
const char *FairTestDetectorTimeRecoTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorTimeRecoTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorTimeRecoTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorTimeRecoTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorTimeRecoTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorTimeRecoTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorTimeRecoTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorTimeRecoTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorDigiRingSorter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorDigiRingSorter::Class_Name()
{
   return "FairTestDetectorDigiRingSorter";
}

//______________________________________________________________________________
const char *FairTestDetectorDigiRingSorter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiRingSorter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorDigiRingSorter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiRingSorter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorDigiRingSorter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiRingSorter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorDigiRingSorter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiRingSorter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTestDetectorDigiSorterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTestDetectorDigiSorterTask::Class_Name()
{
   return "FairTestDetectorDigiSorterTask";
}

//______________________________________________________________________________
const char *FairTestDetectorDigiSorterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiSorterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTestDetectorDigiSorterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiSorterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTestDetectorDigiSorterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiSorterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTestDetectorDigiSorterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTestDetectorDigiSorterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairTestDetectorContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorContFact(void *p) {
      return  p ? new(p) ::FairTestDetectorContFact : new ::FairTestDetectorContFact;
   }
   static void *newArray_FairTestDetectorContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorContFact[nElements] : new ::FairTestDetectorContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorContFact(void *p) {
      delete ((::FairTestDetectorContFact*)p);
   }
   static void deleteArray_FairTestDetectorContFact(void *p) {
      delete [] ((::FairTestDetectorContFact*)p);
   }
   static void destruct_FairTestDetectorContFact(void *p) {
      typedef ::FairTestDetectorContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTestDetectorContFact(TBuffer &buf, void *obj) {
      ((::FairTestDetectorContFact*)obj)->::FairTestDetectorContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTestDetectorContFact

//______________________________________________________________________________
void FairTestDetectorGeo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorGeo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoSet::Streamer(R__b);
      R__b.ReadStaticArray((char*)modName);
      R__b.ReadStaticArray((char*)eleName);
      R__b.CheckByteCount(R__s, R__c, FairTestDetectorGeo::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTestDetectorGeo::IsA(), kTRUE);
      FairGeoSet::Streamer(R__b);
      R__b.WriteArray(modName, 20);
      R__b.WriteArray(eleName, 20);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorGeo(void *p) {
      return  p ? new(p) ::FairTestDetectorGeo : new ::FairTestDetectorGeo;
   }
   static void *newArray_FairTestDetectorGeo(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorGeo[nElements] : new ::FairTestDetectorGeo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorGeo(void *p) {
      delete ((::FairTestDetectorGeo*)p);
   }
   static void deleteArray_FairTestDetectorGeo(void *p) {
      delete [] ((::FairTestDetectorGeo*)p);
   }
   static void destruct_FairTestDetectorGeo(void *p) {
      typedef ::FairTestDetectorGeo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTestDetectorGeo(TBuffer &buf, void *obj) {
      ((::FairTestDetectorGeo*)obj)->::FairTestDetectorGeo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTestDetectorGeo

//______________________________________________________________________________
void FairTestDetectorGeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorGeoPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b.CheckByteCount(R__s, R__c, FairTestDetectorGeoPar::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTestDetectorGeoPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorGeoPar(void *p) {
      return  p ? new(p) ::FairTestDetectorGeoPar : new ::FairTestDetectorGeoPar;
   }
   static void *newArray_FairTestDetectorGeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorGeoPar[nElements] : new ::FairTestDetectorGeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorGeoPar(void *p) {
      delete ((::FairTestDetectorGeoPar*)p);
   }
   static void deleteArray_FairTestDetectorGeoPar(void *p) {
      delete [] ((::FairTestDetectorGeoPar*)p);
   }
   static void destruct_FairTestDetectorGeoPar(void *p) {
      typedef ::FairTestDetectorGeoPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTestDetectorGeoPar(TBuffer &buf, void *obj) {
      ((::FairTestDetectorGeoPar*)obj)->::FairTestDetectorGeoPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTestDetectorGeoPar

//______________________________________________________________________________
void FairTestDetector::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetector::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetector(void *p) {
      return  p ? new(p) ::FairTestDetector : new ::FairTestDetector;
   }
   static void *newArray_FairTestDetector(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetector[nElements] : new ::FairTestDetector[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetector(void *p) {
      delete ((::FairTestDetector*)p);
   }
   static void deleteArray_FairTestDetector(void *p) {
      delete [] ((::FairTestDetector*)p);
   }
   static void destruct_FairTestDetector(void *p) {
      typedef ::FairTestDetector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetector

//______________________________________________________________________________
void FairTestDetectorPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorPoint(void *p) {
      return  p ? new(p) ::FairTestDetectorPoint : new ::FairTestDetectorPoint;
   }
   static void *newArray_FairTestDetectorPoint(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorPoint[nElements] : new ::FairTestDetectorPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorPoint(void *p) {
      delete ((::FairTestDetectorPoint*)p);
   }
   static void deleteArray_FairTestDetectorPoint(void *p) {
      delete [] ((::FairTestDetectorPoint*)p);
   }
   static void destruct_FairTestDetectorPoint(void *p) {
      typedef ::FairTestDetectorPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorPoint

//______________________________________________________________________________
void FairTestDetectorHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorHit(void *p) {
      return  p ? new(p) ::FairTestDetectorHit : new ::FairTestDetectorHit;
   }
   static void *newArray_FairTestDetectorHit(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorHit[nElements] : new ::FairTestDetectorHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorHit(void *p) {
      delete ((::FairTestDetectorHit*)p);
   }
   static void deleteArray_FairTestDetectorHit(void *p) {
      delete [] ((::FairTestDetectorHit*)p);
   }
   static void destruct_FairTestDetectorHit(void *p) {
      typedef ::FairTestDetectorHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorHit

//______________________________________________________________________________
void FairTestDetectorDigi::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorDigi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorDigi::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorDigi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorDigi(void *p) {
      return  p ? new(p) ::FairTestDetectorDigi : new ::FairTestDetectorDigi;
   }
   static void *newArray_FairTestDetectorDigi(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorDigi[nElements] : new ::FairTestDetectorDigi[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorDigi(void *p) {
      delete ((::FairTestDetectorDigi*)p);
   }
   static void deleteArray_FairTestDetectorDigi(void *p) {
      delete [] ((::FairTestDetectorDigi*)p);
   }
   static void destruct_FairTestDetectorDigi(void *p) {
      typedef ::FairTestDetectorDigi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorDigi

//______________________________________________________________________________
void FairTestDetectorHitProducerSmearing::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorHitProducerSmearing.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorHitProducerSmearing::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorHitProducerSmearing::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorHitProducerSmearing(void *p) {
      return  p ? new(p) ::FairTestDetectorHitProducerSmearing : new ::FairTestDetectorHitProducerSmearing;
   }
   static void *newArray_FairTestDetectorHitProducerSmearing(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorHitProducerSmearing[nElements] : new ::FairTestDetectorHitProducerSmearing[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorHitProducerSmearing(void *p) {
      delete ((::FairTestDetectorHitProducerSmearing*)p);
   }
   static void deleteArray_FairTestDetectorHitProducerSmearing(void *p) {
      delete [] ((::FairTestDetectorHitProducerSmearing*)p);
   }
   static void destruct_FairTestDetectorHitProducerSmearing(void *p) {
      typedef ::FairTestDetectorHitProducerSmearing current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorHitProducerSmearing

//______________________________________________________________________________
void FairTestDetectorDigiTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorDigiTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorDigiTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorDigiTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorDigiTask(void *p) {
      return  p ? new(p) ::FairTestDetectorDigiTask : new ::FairTestDetectorDigiTask;
   }
   static void *newArray_FairTestDetectorDigiTask(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorDigiTask[nElements] : new ::FairTestDetectorDigiTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorDigiTask(void *p) {
      delete ((::FairTestDetectorDigiTask*)p);
   }
   static void deleteArray_FairTestDetectorDigiTask(void *p) {
      delete [] ((::FairTestDetectorDigiTask*)p);
   }
   static void destruct_FairTestDetectorDigiTask(void *p) {
      typedef ::FairTestDetectorDigiTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorDigiTask

//______________________________________________________________________________
void FairTestDetectorRecoTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorRecoTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorRecoTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorRecoTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorRecoTask(void *p) {
      return  p ? new(p) ::FairTestDetectorRecoTask : new ::FairTestDetectorRecoTask;
   }
   static void *newArray_FairTestDetectorRecoTask(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorRecoTask[nElements] : new ::FairTestDetectorRecoTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorRecoTask(void *p) {
      delete ((::FairTestDetectorRecoTask*)p);
   }
   static void deleteArray_FairTestDetectorRecoTask(void *p) {
      delete [] ((::FairTestDetectorRecoTask*)p);
   }
   static void destruct_FairTestDetectorRecoTask(void *p) {
      typedef ::FairTestDetectorRecoTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorRecoTask

//______________________________________________________________________________
void FairConstField::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairConstField.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairConstField::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairConstField::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairConstField(void *p) {
      return  p ? new(p) ::FairConstField : new ::FairConstField;
   }
   static void *newArray_FairConstField(Long_t nElements, void *p) {
      return p ? new(p) ::FairConstField[nElements] : new ::FairConstField[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairConstField(void *p) {
      delete ((::FairConstField*)p);
   }
   static void deleteArray_FairConstField(void *p) {
      delete [] ((::FairConstField*)p);
   }
   static void destruct_FairConstField(void *p) {
      typedef ::FairConstField current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairConstField

//______________________________________________________________________________
void FairConstPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairConstPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairConstPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairConstPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairConstPar(void *p) {
      return  p ? new(p) ::FairConstPar : new ::FairConstPar;
   }
   static void *newArray_FairConstPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairConstPar[nElements] : new ::FairConstPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairConstPar(void *p) {
      delete ((::FairConstPar*)p);
   }
   static void deleteArray_FairConstPar(void *p) {
      delete [] ((::FairConstPar*)p);
   }
   static void destruct_FairConstPar(void *p) {
      typedef ::FairConstPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairConstPar

//______________________________________________________________________________
void FairMapPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMapPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMapPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMapPar::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairMapPar(void *p) {
      delete ((::FairMapPar*)p);
   }
   static void deleteArray_FairMapPar(void *p) {
      delete [] ((::FairMapPar*)p);
   }
   static void destruct_FairMapPar(void *p) {
      typedef ::FairMapPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMapPar

//______________________________________________________________________________
void FairTestDetectorDigiWriteoutBuffer::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorDigiWriteoutBuffer.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorDigiWriteoutBuffer::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorDigiWriteoutBuffer::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorDigiWriteoutBuffer(void *p) {
      return  p ? new(p) ::FairTestDetectorDigiWriteoutBuffer : new ::FairTestDetectorDigiWriteoutBuffer;
   }
   static void *newArray_FairTestDetectorDigiWriteoutBuffer(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorDigiWriteoutBuffer[nElements] : new ::FairTestDetectorDigiWriteoutBuffer[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorDigiWriteoutBuffer(void *p) {
      delete ((::FairTestDetectorDigiWriteoutBuffer*)p);
   }
   static void deleteArray_FairTestDetectorDigiWriteoutBuffer(void *p) {
      delete [] ((::FairTestDetectorDigiWriteoutBuffer*)p);
   }
   static void destruct_FairTestDetectorDigiWriteoutBuffer(void *p) {
      typedef ::FairTestDetectorDigiWriteoutBuffer current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorDigiWriteoutBuffer

//______________________________________________________________________________
void FairTestDetectorTimeDigiTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorTimeDigiTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorTimeDigiTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorTimeDigiTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorTimeDigiTask(void *p) {
      return  p ? new(p) ::FairTestDetectorTimeDigiTask : new ::FairTestDetectorTimeDigiTask;
   }
   static void *newArray_FairTestDetectorTimeDigiTask(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorTimeDigiTask[nElements] : new ::FairTestDetectorTimeDigiTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorTimeDigiTask(void *p) {
      delete ((::FairTestDetectorTimeDigiTask*)p);
   }
   static void deleteArray_FairTestDetectorTimeDigiTask(void *p) {
      delete [] ((::FairTestDetectorTimeDigiTask*)p);
   }
   static void destruct_FairTestDetectorTimeDigiTask(void *p) {
      typedef ::FairTestDetectorTimeDigiTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorTimeDigiTask

//______________________________________________________________________________
void FairTestDetectorTimeRecoTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorTimeRecoTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorTimeRecoTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorTimeRecoTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorTimeRecoTask(void *p) {
      return  p ? new(p) ::FairTestDetectorTimeRecoTask : new ::FairTestDetectorTimeRecoTask;
   }
   static void *newArray_FairTestDetectorTimeRecoTask(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorTimeRecoTask[nElements] : new ::FairTestDetectorTimeRecoTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorTimeRecoTask(void *p) {
      delete ((::FairTestDetectorTimeRecoTask*)p);
   }
   static void deleteArray_FairTestDetectorTimeRecoTask(void *p) {
      delete [] ((::FairTestDetectorTimeRecoTask*)p);
   }
   static void destruct_FairTestDetectorTimeRecoTask(void *p) {
      typedef ::FairTestDetectorTimeRecoTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorTimeRecoTask

//______________________________________________________________________________
void FairTestDetectorDigiRingSorter::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorDigiRingSorter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorDigiRingSorter::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorDigiRingSorter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorDigiRingSorter(void *p) {
      return  p ? new(p) ::FairTestDetectorDigiRingSorter : new ::FairTestDetectorDigiRingSorter;
   }
   static void *newArray_FairTestDetectorDigiRingSorter(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorDigiRingSorter[nElements] : new ::FairTestDetectorDigiRingSorter[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorDigiRingSorter(void *p) {
      delete ((::FairTestDetectorDigiRingSorter*)p);
   }
   static void deleteArray_FairTestDetectorDigiRingSorter(void *p) {
      delete [] ((::FairTestDetectorDigiRingSorter*)p);
   }
   static void destruct_FairTestDetectorDigiRingSorter(void *p) {
      typedef ::FairTestDetectorDigiRingSorter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorDigiRingSorter

//______________________________________________________________________________
void FairTestDetectorDigiSorterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTestDetectorDigiSorterTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTestDetectorDigiSorterTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTestDetectorDigiSorterTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTestDetectorDigiSorterTask(void *p) {
      return  p ? new(p) ::FairTestDetectorDigiSorterTask : new ::FairTestDetectorDigiSorterTask;
   }
   static void *newArray_FairTestDetectorDigiSorterTask(Long_t nElements, void *p) {
      return p ? new(p) ::FairTestDetectorDigiSorterTask[nElements] : new ::FairTestDetectorDigiSorterTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTestDetectorDigiSorterTask(void *p) {
      delete ((::FairTestDetectorDigiSorterTask*)p);
   }
   static void deleteArray_FairTestDetectorDigiSorterTask(void *p) {
      delete [] ((::FairTestDetectorDigiSorterTask*)p);
   }
   static void destruct_FairTestDetectorDigiSorterTask(void *p) {
      typedef ::FairTestDetectorDigiSorterTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTestDetectorDigiSorterTask

namespace ROOT {
   static TClass *maplEFairTestDetectorDigicOdoublegR_Dictionary();
   static void maplEFairTestDetectorDigicOdoublegR_TClassManip(TClass*);
   static void *new_maplEFairTestDetectorDigicOdoublegR(void *p = 0);
   static void *newArray_maplEFairTestDetectorDigicOdoublegR(Long_t size, void *p);
   static void delete_maplEFairTestDetectorDigicOdoublegR(void *p);
   static void deleteArray_maplEFairTestDetectorDigicOdoublegR(void *p);
   static void destruct_maplEFairTestDetectorDigicOdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<FairTestDetectorDigi,double>*)
   {
      map<FairTestDetectorDigi,double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<FairTestDetectorDigi,double>));
      static ::ROOT::TGenericClassInfo 
         instance("map<FairTestDetectorDigi,double>", -2, "map", 830,
                  typeid(map<FairTestDetectorDigi,double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplEFairTestDetectorDigicOdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(map<FairTestDetectorDigi,double>) );
      instance.SetNew(&new_maplEFairTestDetectorDigicOdoublegR);
      instance.SetNewArray(&newArray_maplEFairTestDetectorDigicOdoublegR);
      instance.SetDelete(&delete_maplEFairTestDetectorDigicOdoublegR);
      instance.SetDeleteArray(&deleteArray_maplEFairTestDetectorDigicOdoublegR);
      instance.SetDestructor(&destruct_maplEFairTestDetectorDigicOdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<FairTestDetectorDigi,double> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<FairTestDetectorDigi,double>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplEFairTestDetectorDigicOdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<FairTestDetectorDigi,double>*)0x0)->GetClass();
      maplEFairTestDetectorDigicOdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void maplEFairTestDetectorDigicOdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplEFairTestDetectorDigicOdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<FairTestDetectorDigi,double> : new map<FairTestDetectorDigi,double>;
   }
   static void *newArray_maplEFairTestDetectorDigicOdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<FairTestDetectorDigi,double>[nElements] : new map<FairTestDetectorDigi,double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplEFairTestDetectorDigicOdoublegR(void *p) {
      delete ((map<FairTestDetectorDigi,double>*)p);
   }
   static void deleteArray_maplEFairTestDetectorDigicOdoublegR(void *p) {
      delete [] ((map<FairTestDetectorDigi,double>*)p);
   }
   static void destruct_maplEFairTestDetectorDigicOdoublegR(void *p) {
      typedef map<FairTestDetectorDigi,double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<FairTestDetectorDigi,double>

namespace {
  void TriggerDictionaryInitialization_G__FairTestDetectorDict_Impl() {
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
"/Users/turany/development/FairRoot/fairmq",
"/Users/turany/development/FairRoot/fairmq/zeromq",
"/Users/turany/development/FairRoot/fairmq/nanomsg",
"/Users/turany/development/FairRoot/fairmq/devices",
"/Users/turany/development/FairRoot/fairmq/tools",
"/Users/turany/development/FairRoot/fairmq/options",
"/Users/turany/development/FairRoot/base/MQ",
"/Users/turany/development/FairRoot/base/MQ/baseMQtools",
"/Users/turany/development/FairRoot/base/MQ/devices",
"/Users/turany/development/FairRoot/base/MQ/tasks",
"/Users/turany/development/FairRoot/examples/common/mcstack",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/data",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/simulation",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/digitization",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/reconstruction",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/timeBasedSimulation",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/MQ/samplerTask",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/MQ/processorTask",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/MQ/fileSink",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/MQ/run",
"/Users/turany/development/FairRoot/examples/advanced/Tutorial3/MQ/data",
"/Users/turany/development/FairRoot/build/examples/advanced/Tutorial3",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/advanced/Tutorial3/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__FairTestDetectorDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Factory for all FairTestDetector parameter containers)ATTRDUMP"))) FairTestDetectorContFact;
class FairTestDetectorGeo;
class FairTestDetectorGeoPar;
class FairTestDetector;
class FairTestDetectorPoint;
class FairTestDetectorHit;
class __attribute__((annotate("$clingAutoload$FairTestDetectorDigi.h")))  FairTestDetectorDigi;
class FairTestDetectorHitProducerSmearing;
class FairTestDetectorDigiTask;
class FairTestDetectorRecoTask;
class FairConstField;
class FairConstPar;
class __attribute__((annotate("$clingAutoload$FairMapPar.h")))  FairMapPar;
class FairTestDetectorDigiWriteoutBuffer;
class FairTestDetectorTimeDigiTask;
class FairTestDetectorTimeRecoTask;
class FairTestDetectorDigiRingSorter;
class FairTestDetectorDigiSorterTask;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__FairTestDetectorDict dictionary payload"

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
#ifndef FAIRTESTDETECTOR_H_
#define FAIRTESTDETECTOR_H_

#include "FairDetector.h"

#include "Rtypes.h"         // for Int_t, Double32_t, Double_t, etc
#include "TLorentzVector.h" // for TLorentzVector
#include "TVector3.h"       // for TVector3

class FairTestDetectorPoint;
class FairVolume;
class TClonesArray;

class FairTestDetector : public FairDetector
{

  public:
    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    FairTestDetector(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairTestDetector();

    /**       destructor     */
    virtual ~FairTestDetector();

    /**      Initialization of the detector is done here    */
    virtual void Initialize();

    /**       this method is called for each step during simulation
     *       (see FairMCApplication::Stepping())
    */
    virtual Bool_t ProcessHits(FairVolume* v = 0);

    /**       Registers the produced collections in FAIRRootManager.     */
    virtual void Register();

    /** Gets the produced collections */
    virtual TClonesArray* GetCollection(Int_t iColl) const;

    /**      has to be called after each event to reset the containers      */
    virtual void Reset();

    /**      Create the detector geometry        */
    void ConstructGeometry();

    /**      This method is an example of how to add your own point
     *       of type FairTestDetectorPoint to the clones array
    */
    FairTestDetectorPoint*
        AddHit(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom, TVector3 posOut, TVector3 momOut, Double_t time, Double_t length, Double_t eLoss);

    /** The following methods can be implemented if you need to make
     *  any optional action in your detector during the transport.
    */

/*
    virtual void CopyClones(TClonesArray* cl1, TClonesArray* cl2, Int_t offset)
    {
        ;
    }
*/
    virtual void SetSpecialPhysicsCuts()
    {
        ;
    }
    virtual void EndOfEvent();
    virtual void FinishPrimary()
    {
        ;
    }
    virtual void FinishRun()
    {
        ;
    }
    virtual void BeginPrimary()
    {
        ;
    }
    virtual void PostTrack()
    {
        ;
    }
    virtual void PreTrack()
    {
        ;
    }
    virtual void BeginEvent()
    {
        ;
    }

  private:
    /** Track information to be stored until the track leaves the
    active volume.
    */
    Int_t fTrackID;         //!  track index
    Int_t fVolumeID;        //!  volume id
    TLorentzVector fPos;    //!  position at entrance
    TLorentzVector fMom;    //!  momentum at entrance
    TLorentzVector fPosOut; //!  position at entrance
    TLorentzVector fMomOut; //!  momentum at entrance
    Double32_t fTime;       //!  time
    Double32_t fLength;     //!  length
    Double32_t fELoss;      //!  energy loss

    /** container for data points */

    TClonesArray* fFairTestDetectorPointCollection;

    FairTestDetector(const FairTestDetector&);
    FairTestDetector& operator=(const FairTestDetector&);

    ClassDef(FairTestDetector, 1)
};

#endif /* FAIRTESTDETECTOR_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORCONTFACT_H_
#define FAIRTESTDETECTORCONTFACT_H_

#include "FairContFact.h" // for FairContFact, etc

#include "Rtypes.h" // for ClassDef

class FairParSet;

class FairTestDetectorContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairTestDetectorContFact();
    ~FairTestDetectorContFact()
    {
    }
    FairParSet* createContainer(FairContainer*);
    ClassDef(FairTestDetectorContFact, 0) // Factory for all FairTestDetector parameter containers
};

#endif /* FAIRTESTDETECTORCONTFACT_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORGEO_H_
#define FAIRTESTDETECTORGEO_H_

#include "FairGeoSet.h" // for FairGeoSet

#include "Rtypes.h"  // for Int_t, etc
#include "TString.h" // for TString

class FairTestDetectorGeo : public FairGeoSet
{

  protected:
    char modName[20]; // name of module
    char eleName[20]; // substring for elements in module
  public:
    FairTestDetectorGeo();
    ~FairTestDetectorGeo()
    {
    }
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(FairTestDetectorGeo, 1)
};

inline Int_t FairTestDetectorGeo::getModNumInMod(const TString& name)
{
    /** returns the module index from module name
     ?? in name[??] has to be the length of the detector name in the
     .geo file. For example if all nodes in this file starts with
     newdetector ?? has to be 11.
    */
    return static_cast<Int_t>((name[6] - '0') - 1); //
}

#endif /* FAIRTESTDETECTORGEO_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORGEOPAR_H_
#define FAIRTESTDETECTORGEOPAR_H_

#include "FairParGenericSet.h" // for FairParGenericSet

#include "Rtypes.h" // for Class Def

class TObjArray;
class FairParamList;

class FairTestDetectorGeoPar : public FairParGenericSet
{
  public:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray* fGeoPassNodes;

    FairTestDetectorGeoPar(const char* name = "FairTestDetectorGeoPar",
                           const char* title = "FairTestDetector Geometry Parameters",
                           const char* context = "TestDefaultContext");
    ~FairTestDetectorGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes()
    {
        return fGeoSensNodes;
    }
    TObjArray* GetGeoPassiveNodes()
    {
        return fGeoPassNodes;
    }

  private:
    FairTestDetectorGeoPar(const FairTestDetectorGeoPar&);
    FairTestDetectorGeoPar& operator=(const FairTestDetectorGeoPar&);

    ClassDef(FairTestDetectorGeoPar, 1)
};

#endif /* FAIRTESTDETECTORGEOPAR_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/** FairConstField.h
 ** @author M.Al-Turany <m.al/turany@gsi.de>
 ** @since 30.01.2007
 ** @version1.0
 ** A constant  magnetic field
 **/

#ifndef FairConstFIELD_H
#define FairConstFIELD_H 1

#include "FairField.h" // for FairField

#include "Rtypes.h" // for Double_t, etc

class FairConstPar;

class FairConstField : public FairField
{

  public:
    /** Default constructor **/
    FairConstField();

    /** Standard constructor
     ** @param name   Object name
     ** @param xMin,xMax   x region of field (global coordinates)
     ** @param yMin,yMax   y region of field (global coordinates)
     ** @param zMin,zMax   z region of field (global coordinates)
     ** @param bX,bY,bZ    Field values [kG]
     **/
    FairConstField(const char* name,
                   Double_t xMin,
                   Double_t xMax,
                   Double_t yMin,
                   Double_t yMax,
                   Double_t zMin,
                   Double_t zMax,
                   Double_t bX,
                   Double_t bY,
                   Double_t bZ);

    /** Constructor from PndFieldPar **/
    FairConstField(FairConstPar* fieldPar);

    /** Destructor **/
    virtual ~FairConstField();

    void FillParContainer();

    /** Set the field region
     ** @param xMin,xMax   x region of field (global coordinates)
     ** @param yMin,yMax   y region of field (global coordinates)
     ** @param zMin,zMax   z region of field (global coordinates)
     **/
    void SetFieldRegion(Double_t xMin, Double_t xMax, Double_t yMin, Double_t yMax, Double_t zMin, Double_t zMax);

    /** Set the field values
     ** @param bX,bY,bZ    Field values [kG]
     **/
    void SetField(Double_t bX, Double_t bY, Double_t bZ);

    /** Get components of field at a given point
     ** @param x,y,z   Point coordinates [cm]
     **/
    virtual Double_t GetBx(Double_t x, Double_t y, Double_t z);
    virtual Double_t GetBy(Double_t x, Double_t y, Double_t z);
    virtual Double_t GetBz(Double_t x, Double_t y, Double_t z);

    /** Accessors to field region **/
    Double_t GetXmin() const
    {
        return fXmin;
    }
    Double_t GetXmax() const
    {
        return fXmax;
    }
    Double_t GetYmin() const
    {
        return fYmin;
    }
    Double_t GetYmax() const
    {
        return fYmax;
    }
    Double_t GetZmin() const
    {
        return fZmin;
    }
    Double_t GetZmax() const
    {
        return fZmax;
    }

    /** Accessors to field values **/
    Double_t GetBx() const
    {
        return fBx;
    }
    Double_t GetBy() const
    {
        return fBy;
    }
    Double_t GetBz() const
    {
        return fBz;
    }

    /** Screen output **/
    virtual void Print(Option_t*) const;

    ClassDef(FairConstField, 1);

  private:
    /** Limits of the field region **/
    Double_t fXmin;
    Double_t fXmax;
    Double_t fYmin;
    Double_t fYmax;
    Double_t fZmin;
    Double_t fZmax;

    /** Field components inside the field region **/
    Double_t fBx;
    Double_t fBy;
    Double_t fBz;
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/** FairConstPar.h
 ** @author M.Al-Turany
 ** @since 30.01.2007
 ** @version 1.0
 **
 ** Parameter set for the region between Solenoid and dipole. For the runtime database.
 **/

#ifndef FairConstPAR_H
#define FairConstPAR_H 1

#include "FairMapPar.h" // for FairMapPar

#include "Rtypes.h" // for Double_t, etc

class FairField;
class FairParamList;

class FairConstPar : public FairMapPar
{

  public:
    /** Standard constructor  **/
    FairConstPar(const char* name, const char* title, const char* context);

    /** default constructor  **/
    FairConstPar();

    /** Destructor **/
    ~FairConstPar();

    void putParams(FairParamList* list);

    /** Get parameters **/
    Bool_t getParams(FairParamList* list);

    /** Set parameters from FairField  **/
    void SetParameters(FairField* field);

    Double_t GetBx() const
    {
        return fBx;
    }
    Double_t GetBy() const
    {
        return fBy;
    }
    Double_t GetBz() const
    {
        return fBz;
    }

  protected:
    /** Field values in [kG] **/
    Double_t fBx, fBy, fBz;

    ClassDef(FairConstPar, 1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/** FairMapPar.h
 ** @author M.Al-Turany
 ** @since 30.01.2007
 ** @version 1.0
 **
 ** Parameter set field maps.
 **/

#ifndef FairMAPPAR_H
#define FairMAPPAR_H 1

#include "FairParGenericSet.h" // for FairParGenericSet

#include "Rtypes.h"  // for Double_t, FairMapPar::Class, etc
#include "TString.h" // for TString

class FairMapPar : public FairParGenericSet
{

  public:
    /** Standard constructor  **/
    FairMapPar(const char* name, const char* title, const char* context);

    /** default constructor  **/
    FairMapPar();

    /** Destructor **/
    ~FairMapPar();

    /** Accessors **/
    Int_t GetType() const
    {
        return fType;
    }
    Double_t GetXmin() const
    {
        return fXmin;
    }
    Double_t GetXmax() const
    {
        return fXmax;
    }
    Double_t GetYmin() const
    {
        return fYmin;
    }
    Double_t GetYmax() const
    {
        return fYmax;
    }
    Double_t GetZmin() const
    {
        return fZmin;
    }
    Double_t GetZmax() const
    {
        return fZmax;
    }
    void MapName(TString& name)
    {
        name = fMapName;
    }
    Double_t GetPositionX() const
    {
        return fPosX;
    }
    Double_t GetPositionY() const
    {
        return fPosY;
    }
    Double_t GetPositionZ() const
    {
        return fPosZ;
    }
    Double_t GetScale() const
    {
        return fScale;
    }

  protected:
    /** Field type
     ** 0 = constant field
     ** 1 = field map
     ** 2 = field map sym2 (symmetries in x and y)
     ** 3 = field map sym3 (symmetries in x, y and z)
     **/
    Int_t fType;

    /** Field limits in case of constant field **/
    Double_t fXmin, fXmax;
    Double_t fYmin, fYmax;
    Double_t fZmin, fZmax;

    /** Field map name in case of field map **/
    TString fMapName;

    /** Field centre position for field map **/
    Double_t fPosX, fPosY, fPosZ;

    /** Scaling factor for field map **/
    Double_t fScale;

    ClassDef(FairMapPar, 1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORPOINT_H_
#define FAIRTESTDETECTORPOINT_H_

#include "FairMCPoint.h" // for FairMCPoint

#include "Rtypes.h"   // for Double_t, Double32_t, etc
#include "TVector3.h" // for TVector3

class FairTestDetectorPoint : public FairMCPoint
{

  public:
    /** Default constructor **/
    FairTestDetectorPoint();

    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTestDetectorPoint(Int_t trackID,
                          Int_t detID,
                          TVector3 pos,
                          TVector3 mom,
                          TVector3 posOut,
                          TVector3 momOut,
                          Double_t tof,
                          Double_t length,
                          Double_t eLoss);

    /** Destructor **/
    virtual ~FairTestDetectorPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

    /** Accessors **/
    Double_t GetXIn() const
    {
        return fX;
    }
    Double_t GetYIn() const
    {
        return fY;
    }
    Double_t GetZIn() const
    {
        return fZ;
    }
    Double_t GetXOut() const
    {
        return fX_out;
    }
    Double_t GetYOut() const
    {
        return fY_out;
    }
    Double_t GetZOut() const
    {
        return fZ_out;
    }
    Double_t GetPxOut() const
    {
        return fPx_out;
    }
    Double_t GetPyOut() const
    {
        return fPy_out;
    }
    Double_t GetPzOut() const
    {
        return fPz_out;
    }
    Double_t GetPxIn() const
    {
        return fPx;
    }
    Double_t GetPyIn() const
    {
        return fPy;
    }
    Double_t GetPzIn() const
    {
        return fPz;
    }

    void PositionOut(TVector3& pos) const
    {
        pos.SetXYZ(fX_out, fY_out, fZ_out);
    }
    void MomentumOut(TVector3& mom) const
    {
        mom.SetXYZ(fPx_out, fPy_out, fPz_out);
    }

  private:
    Double32_t fX_out;
    Double32_t fY_out;
    Double32_t fZ_out;
    Double32_t fPx_out;
    Double32_t fPy_out;
    Double32_t fPz_out;

    /** Copy constructor **/
    FairTestDetectorPoint(const FairTestDetectorPoint&);
    FairTestDetectorPoint operator=(const FairTestDetectorPoint&);

    ClassDef(FairTestDetectorPoint, 2)
};

#endif /* FAIRTESTDETECTORPOINT_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORHIT_H_
#define FAIRTESTDETECTORHIT_H_

#include "FairHit.h" // for FairHit

#include "Rtypes.h" // for FairTestDetectorHit::Class, etc

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class TVector3;

class FairTestDetectorHit : public FairHit
{
  public:
    /** Default constructor **/
    FairTestDetectorHit();

    /** Constructor **/
    FairTestDetectorHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);

    /** Destructor **/
    virtual ~FairTestDetectorHit();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    ClassDef(FairTestDetectorHit, 1);
};

#endif /* FAIRTESTDETECTORHIT_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORHITPRODUCERSMEARING_H_
#define FAIRTESTDETECTORHITPRODUCERSMEARING_H_

#include "FairTask.h" // for InitStatus, FairTask

#include "Rtypes.h" // for ClassDef

class TClonesArray;

class FairTestDetectorHitProducerSmearing : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorHitProducerSmearing();

    /** Destructor **/
    ~FairTestDetectorHitProducerSmearing();

    /** Initiliazation of task at the beginning of a run **/
    virtual InitStatus Init();

    /** ReInitiliazation of task when the runID changes **/
    virtual InitStatus ReInit();

    /** Executed for each event. **/
    virtual void Exec(Option_t* opt);

    /** Load the parameter container from the runtime database **/
    virtual void SetParContainers();

    /** Finish task called at the end of the run **/
    virtual void Finish();

  private:
    /** Input array from previous already existing data level **/
    TClonesArray* fPointsArray;

    /** Output array to  new data level**/
    TClonesArray* fHitsArray;

    FairTestDetectorHitProducerSmearing(const FairTestDetectorHitProducerSmearing&);
    FairTestDetectorHitProducerSmearing operator=(const FairTestDetectorHitProducerSmearing&);

    ClassDef(FairTestDetectorHitProducerSmearing, 1);
};

#endif /* FAIRTESTDETECTORHITPRODUCERSMEARING_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORDIGITASK_H_
#define FAIRTESTDETECTORDIGITASK_H_

#include "FairTask.h" // for FairTask, InitStatus

#include "Rtypes.h" // for Double_t, etc

class TClonesArray;

class FairTestDetectorDigiTask : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorDigiTask();

    /** Destructor **/
    ~FairTestDetectorDigiTask();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    void SetTimeResolution(Double_t timeInNs)
    {
        fTimeResolution = timeInNs;
    }
    Double_t GetTimeResolution()
    {
        return fTimeResolution;
    }

  private:
    Int_t CalcPad(Double_t posIn, Double_t posOut);
    Double_t CalcTimeStamp(Double_t timeOfFlight);

    Double_t fTimeResolution;

    TClonesArray* fPointArray;
    TClonesArray* fDigiArray;

    FairTestDetectorDigiTask(const FairTestDetectorDigiTask&);
    FairTestDetectorDigiTask& operator=(const FairTestDetectorDigiTask&);

    ClassDef(FairTestDetectorDigiTask, 1);
};

#endif /* FAIRTESTDETECTORDIGITASK_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTDETECTORRECOTASK_H_
#define FAIRTESTDETECTORRECOTASK_H_

#include "FairTask.h" // for FairTask, InitStatus

class TClonesArray;

class FairTestDetectorPoint;

class FairTestDetectorRecoTask : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorRecoTask();
    FairTestDetectorRecoTask(Int_t verbose);

    /** Destructor **/
    virtual ~FairTestDetectorRecoTask();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    TClonesArray* fDigiArray;
    TClonesArray* fHitArray;

  private:
    FairTestDetectorRecoTask(const FairTestDetectorRecoTask&);
    FairTestDetectorRecoTask& operator=(const FairTestDetectorRecoTask&);

    ClassDef(FairTestDetectorRecoTask, 1);
};

#endif /* FAIRTESTDETECTORRECOTASK_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiRingSorter.h
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#ifndef FairTestDetectorDigiRingSorter_H_
#define FairTestDetectorDigiRingSorter_H_

#include <FairRingSorter.h> // for FairRingSorter

#include "Rtypes.h" // for ClassDef

class FairTimeStamp;

class FairTestDetectorDigiRingSorter : public FairRingSorter
{
  public:
    FairTestDetectorDigiRingSorter(int size = 100, double width = 10)
        : FairRingSorter(size, width) {};
    virtual ~FairTestDetectorDigiRingSorter();

    virtual FairTimeStamp* CreateElement(FairTimeStamp* data);

    ClassDef(FairTestDetectorDigiRingSorter, 1);
};

#endif /* FairTestDetectorDigiRingSorter_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiSorterTask.h
 *
 *  Created on: Sep 9, 2011
 *      Author: stockman
 */

#ifndef FairTestDetectorDigiSorterTask_H_
#define FairTestDetectorDigiSorterTask_H_

#include <FairRingSorterTask.h> // for FairRingSorterTask

#include "Rtypes.h"  // for Double_t, etc
#include "TString.h" // for TString

class FairRingSorter;
class FairTimeStamp;

class FairTestDetectorDigiSorterTask : public FairRingSorterTask
{
  public:
    FairTestDetectorDigiSorterTask();
    FairTestDetectorDigiSorterTask(const char* name)
        : FairRingSorterTask(name) {};
    FairTestDetectorDigiSorterTask(Int_t numberOfCells, Double_t widthOfCells, TString inputBranch, TString outputBranch, TString folderName)
        : FairRingSorterTask(numberOfCells, widthOfCells, inputBranch, outputBranch, folderName) {};

    virtual ~FairTestDetectorDigiSorterTask();

    virtual void AddNewDataToTClonesArray(FairTimeStamp* data);
    virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const;

    ClassDef(FairTestDetectorDigiSorterTask, 1);
};

#endif /* FairTestDetectorDigiSorterTask_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairTestDetectorDigiWriteoutBuffer.h
 *
 *  Created on: May 10, 2011
 *      Author: stockman
 */

#ifndef FairTestDetectorDigiWriteoutBuffer_H_
#define FairTestDetectorDigiWriteoutBuffer_H_

#include "FairWriteoutBuffer.h" // for FairWriteoutBuffer

#include "FairTestDetectorDigi.h" // for FairTestDetectorDigi

#include "Rtypes.h"
#include "TString.h" // for TString

#include <map> // for map

class FairTimeStamp;

class FairTestDetectorDigiWriteoutBuffer : public FairWriteoutBuffer
{

  public:
    FairTestDetectorDigiWriteoutBuffer();
    FairTestDetectorDigiWriteoutBuffer(TString branchName, TString folderName, Bool_t persistance);

    virtual ~FairTestDetectorDigiWriteoutBuffer();

    void AddNewDataToTClonesArray(FairTimeStamp*);

    virtual double FindTimeForData(FairTimeStamp* data);
    virtual void FillDataMap(FairTimeStamp* data, double activeTime);
    virtual void EraseDataFromDataMap(FairTimeStamp* data);

  protected:
    std::map<FairTestDetectorDigi, double> fData_map;

    ClassDef(FairTestDetectorDigiWriteoutBuffer, 1);
};

#endif /* FairTestDetectorDigiWriteoutBuffer_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FairTestDetectorTimeDigiTask_H
#define FairTestDetectorTimeDigiTask_H

#include "FairTask.h" // for FairTask, InitStatus

#include "Rtypes.h" // for Double_t, etc

class TClonesArray;
class FairTestDetectorDigiWriteoutBuffer;

class FairTestDetectorTimeDigiTask : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorTimeDigiTask();

    /** Destructor **/
    ~FairTestDetectorTimeDigiTask();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    void SetTimeResolution(Double_t timeInNs)
    {
        fTimeResolution = timeInNs;
    }
    Double_t GetTimeResolution()
    {
        return fTimeResolution;
    }

    void RunTimeBased()
    {
        fTimeOrderedDigi = kTRUE;
    }

  private:
    Int_t CalcPad(Double_t posIn, Double_t posOut);
    Double_t CalcTimeStamp(Double_t timeOfFlight);

    Double_t fTimeResolution;

    TClonesArray* fPointArray;
    TClonesArray* fDigiArray;

    FairTestDetectorDigiWriteoutBuffer* fDataBuffer;

    Bool_t fTimeOrderedDigi;

    FairTestDetectorTimeDigiTask(const FairTestDetectorTimeDigiTask&);
    FairTestDetectorTimeDigiTask& operator=(const FairTestDetectorTimeDigiTask&);

    ClassDef(FairTestDetectorTimeDigiTask, 1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FairTestDetectorTimeRecoTask_H
#define FairTestDetectorTimeRecoTask_H

#include "FairTask.h" // for FairTask, InitStatus

#include "Rtypes.h" // for ClassDef

class BinaryFunctor;
class TClonesArray;

class FairTestDetectorTimeRecoTask : public FairTask
{
  public:
    /** Default constructor **/
    FairTestDetectorTimeRecoTask();
    FairTestDetectorTimeRecoTask(Int_t verbose);

    /** Destructor **/
    ~FairTestDetectorTimeRecoTask();

    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

  private:
    TClonesArray* fDigiArray;
    TClonesArray* fHitArray;

    BinaryFunctor* fFunctor; //!

    FairTestDetectorTimeRecoTask(const FairTestDetectorTimeRecoTask&);
    FairTestDetectorTimeRecoTask& operator=(const FairTestDetectorTimeRecoTask&);

    ClassDef(FairTestDetectorTimeRecoTask, 1);
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
 * FairTestDetectorDigi.h
 *
 *  Created on: 20.07.2012
 *      Author: stockman
 */

#ifndef FAIRTESTDETECTORDIGI_H_
#define FAIRTESTDETECTORDIGI_H_

#include "FairTimeStamp.h" // for FairTimeStamp

#include "Riosfwd.h" // for ostream
#include "Rtypes.h"  // for Int_t, etc

#include <iostream> // for operator<<, basic_ostream, etc
#include <string>
#include <sstream>

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class FairTestDetectorDigi : public FairTimeStamp
{
 public:
    FairTestDetectorDigi();
    FairTestDetectorDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp);
    virtual ~FairTestDetectorDigi();

    void SetXYZ(Int_t x, Int_t y, Int_t z)
    {
        SetX(x);
        SetY(y);
        SetZ(z);
    }
    void SetX(Int_t x)
    {
        fX = x;
    }
    void SetY(Int_t y)
    {
        fY = y;
    }
    void SetZ(Int_t z)
    {
        fZ = z;
    }

    Int_t GetX() const
    {
        return fX;
    }
    Int_t GetY() const
    {
        return fY;
    }
    Int_t GetZ() const
    {
        return fZ;
    }

    // temporary to avoid serialisation of the parent class
    virtual bool equal(FairTimeStamp* data)
    {
        FairTestDetectorDigi* myDigi = dynamic_cast<FairTestDetectorDigi*>(data);
        if (myDigi != 0)
        {
            if (fX == myDigi->GetX())
                if (fY == myDigi->GetY())
                    if (fZ == myDigi->GetZ())
                    {
                        return true;
                    }
        }
        return false;
    }

    virtual bool operator<(const FairTestDetectorDigi& myDigi) const
    {
        if (fX < myDigi.GetX())
        {
            return true;
        }
        else if (fX > myDigi.GetX())
        {
            return false;
        }
        if (fY < myDigi.GetY())
        {
            return true;
        }
        else if (fY > myDigi.GetY())
        {
            return false;
        }
        if (fZ < myDigi.GetZ())
        {
            return true;
        }
        else if (fZ > myDigi.GetZ())
        {
            return false;
        }
        return false;
    }

    friend std::ostream& operator<<(std::ostream& out, FairTestDetectorDigi& digi)
    {
        out << "FairTestDetectorDigi at:"
            << " (" << digi.GetX() << "/" << digi.GetY() << "/" << digi.GetZ() << ") "
            << " with TimeStamp: " << digi.GetTimeStamp() << std::endl;
        return out;
    }

    template <class T>
    std::string ToString (const T& value)
    {
      std::stringstream ss;
      ss.precision(5);
      ss << value;
      return ss.str();
    }

    std::string ToString()
    {
      std::string out = "FairTestDetectorDigi at: (" + ToString(GetX()) 
  	    + "/" + ToString(GetY()) + "/" + ToString(GetZ()) 
 	    + ") " + " with TimeStamp: " + ToString(GetTimeStamp());
      return out;
    }

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairTimeStamp>(*this);
        ar& fX;
        ar& fY;
        ar& fZ;
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    Int_t fX;
    Int_t fY;
    Int_t fZ;

    ClassDef(FairTestDetectorDigi, 1);
};

#endif /* FAIRTESTDETECTORDIGI_H_ */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairConstField", payloadCode, "@",
"FairConstPar", payloadCode, "@",
"FairMapPar", payloadCode, "@",
"FairTestDetector", payloadCode, "@",
"FairTestDetectorContFact", payloadCode, "@",
"FairTestDetectorDigi", payloadCode, "@",
"FairTestDetectorDigiRingSorter", payloadCode, "@",
"FairTestDetectorDigiSorterTask", payloadCode, "@",
"FairTestDetectorDigiTask", payloadCode, "@",
"FairTestDetectorDigiWriteoutBuffer", payloadCode, "@",
"FairTestDetectorGeo", payloadCode, "@",
"FairTestDetectorGeoPar", payloadCode, "@",
"FairTestDetectorHit", payloadCode, "@",
"FairTestDetectorHitProducerSmearing", payloadCode, "@",
"FairTestDetectorPoint", payloadCode, "@",
"FairTestDetectorRecoTask", payloadCode, "@",
"FairTestDetectorTimeDigiTask", payloadCode, "@",
"FairTestDetectorTimeRecoTask", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__FairTestDetectorDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__FairTestDetectorDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__FairTestDetectorDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__FairTestDetectorDict() {
  TriggerDictionaryInitialization_G__FairTestDetectorDict_Impl();
}

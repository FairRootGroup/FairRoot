// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIbasedIG__BaseDict

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
#include "steer/FairAnaSelector.h"
#include "steer/FairRadGridManager.h"
#include "steer/FairRadLenManager.h"
#include "steer/FairRadMapManager.h"
#include "steer/FairRingSorter.h"
#include "steer/FairRingSorterTask.h"
#include "steer/FairRootManager.h"
#include "steer/FairRun.h"
#include "steer/FairRunAna.h"
#include "steer/FairRunAnaProof.h"
#include "steer/FairRunSim.h"
#include "steer/FairTSBufferFunctional.h"
#include "steer/FairTask.h"
#include "steer/FairTrajFilter.h"
#include "steer/FairWriteoutBuffer.h"
#include "steer/FairRunOnline.h"
#include "steer/FairLinkManager.h"
#include "sim/FairBaseContFact.h"
#include "sim/FairBaseParSet.h"
#include "sim/FairGeoParSet.h"
#include "sim/FairDetector.h"
#include "sim/FairGeaneApplication.h"
#include "sim/FairGenerator.h"
#include "sim/FairGenericStack.h"
#include "sim/FairIon.h"
#include "sim/FairMCApplication.h"
#include "sim/FairModule.h"
#include "sim/FairParticle.h"
#include "sim/FairPrimaryGenerator.h"
#include "sim/FairRunIdGenerator.h"
#include "sim/FairVolume.h"
#include "sim/FairVolumeList.h"
#include "event/FairEventBuilder.h"
#include "event/FairEventBuilderManager.h"
#include "event/FairEventHeader.h"
#include "event/FairFileHeader.h"
#include "event/FairFileInfo.h"
#include "event/FairHit.h"
#include "event/FairLink.h"
#include "event/FairMCEventHeader.h"
#include "event/FairMCPoint.h"
#include "event/FairMesh.h"
#include "event/FairMultiLinkedData.h"
#include "event/FairMultiLinkedData_Interface.h"
#include "event/FairRadLenPoint.h"
#include "event/FairRadMapPoint.h"
#include "event/FairRecoEventHeader.h"
#include "event/FairRunInfo.h"
#include "event/FairTimeStamp.h"
#include "event/FairTrackParam.h"
#include "field/FairField.h"
#include "field/FairFieldFactory.h"
#include "field/FairRKPropagator.h"
#include "source/FairSource.h"
#include "source/FairFileSource.h"
#include "source/FairMixedSource.h"
#include "source/FairOnlineSource.h"
#include "source/FairLmdSource.h"
#include "source/FairRemoteSource.h"
#include "source/FairMbsSource.h"
#include "source/FairUnpack.h"
#include "source/MRevBuffer.h"
#include "source/FairMbsStreamSource.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairBaseContFact(void *p = 0);
   static void *newArray_FairBaseContFact(Long_t size, void *p);
   static void delete_FairBaseContFact(void *p);
   static void deleteArray_FairBaseContFact(void *p);
   static void destruct_FairBaseContFact(void *p);
   static void streamer_FairBaseContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairBaseContFact*)
   {
      ::FairBaseContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairBaseContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairBaseContFact", ::FairBaseContFact::Class_Version(), "invalid", 2708,
                  typeid(::FairBaseContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairBaseContFact::Dictionary, isa_proxy, 16,
                  sizeof(::FairBaseContFact) );
      instance.SetNew(&new_FairBaseContFact);
      instance.SetNewArray(&newArray_FairBaseContFact);
      instance.SetDelete(&delete_FairBaseContFact);
      instance.SetDeleteArray(&deleteArray_FairBaseContFact);
      instance.SetDestructor(&destruct_FairBaseContFact);
      instance.SetStreamerFunc(&streamer_FairBaseContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairBaseContFact*)
   {
      return GenerateInitInstanceLocal((::FairBaseContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairBaseContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairBaseParSet(void *p = 0);
   static void *newArray_FairBaseParSet(Long_t size, void *p);
   static void delete_FairBaseParSet(void *p);
   static void deleteArray_FairBaseParSet(void *p);
   static void destruct_FairBaseParSet(void *p);
   static void streamer_FairBaseParSet(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairBaseParSet*)
   {
      ::FairBaseParSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairBaseParSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairBaseParSet", ::FairBaseParSet::Class_Version(), "invalid", 2752,
                  typeid(::FairBaseParSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairBaseParSet::Dictionary, isa_proxy, 16,
                  sizeof(::FairBaseParSet) );
      instance.SetNew(&new_FairBaseParSet);
      instance.SetNewArray(&newArray_FairBaseParSet);
      instance.SetDelete(&delete_FairBaseParSet);
      instance.SetDeleteArray(&deleteArray_FairBaseParSet);
      instance.SetDestructor(&destruct_FairBaseParSet);
      instance.SetStreamerFunc(&streamer_FairBaseParSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairBaseParSet*)
   {
      return GenerateInitInstanceLocal((::FairBaseParSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairBaseParSet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoParSet(void *p = 0);
   static void *newArray_FairGeoParSet(Long_t size, void *p);
   static void delete_FairGeoParSet(void *p);
   static void deleteArray_FairGeoParSet(void *p);
   static void destruct_FairGeoParSet(void *p);
   static void streamer_FairGeoParSet(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoParSet*)
   {
      ::FairGeoParSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoParSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoParSet", ::FairGeoParSet::Class_Version(), "invalid", 2877,
                  typeid(::FairGeoParSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoParSet::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoParSet) );
      instance.SetNew(&new_FairGeoParSet);
      instance.SetNewArray(&newArray_FairGeoParSet);
      instance.SetDelete(&delete_FairGeoParSet);
      instance.SetDeleteArray(&deleteArray_FairGeoParSet);
      instance.SetDestructor(&destruct_FairGeoParSet);
      instance.SetStreamerFunc(&streamer_FairGeoParSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoParSet*)
   {
      return GenerateInitInstanceLocal((::FairGeoParSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoParSet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairDetector(void *p);
   static void deleteArray_FairDetector(void *p);
   static void destruct_FairDetector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairDetector*)
   {
      ::FairDetector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairDetector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairDetector", ::FairDetector::Class_Version(), "invalid", 2968,
                  typeid(::FairDetector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairDetector::Dictionary, isa_proxy, 4,
                  sizeof(::FairDetector) );
      instance.SetDelete(&delete_FairDetector);
      instance.SetDeleteArray(&deleteArray_FairDetector);
      instance.SetDestructor(&destruct_FairDetector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairDetector*)
   {
      return GenerateInitInstanceLocal((::FairDetector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairDetector*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairEventBuilder(void *p);
   static void deleteArray_FairEventBuilder(void *p);
   static void destruct_FairEventBuilder(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairEventBuilder*)
   {
      ::FairEventBuilder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairEventBuilder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairEventBuilder", ::FairEventBuilder::Class_Version(), "invalid", 4661,
                  typeid(::FairEventBuilder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairEventBuilder::Dictionary, isa_proxy, 4,
                  sizeof(::FairEventBuilder) );
      instance.SetDelete(&delete_FairEventBuilder);
      instance.SetDeleteArray(&deleteArray_FairEventBuilder);
      instance.SetDestructor(&destruct_FairEventBuilder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairEventBuilder*)
   {
      return GenerateInitInstanceLocal((::FairEventBuilder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairEventBuilder*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairEventBuilderManager(void *p);
   static void deleteArray_FairEventBuilderManager(void *p);
   static void destruct_FairEventBuilderManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairEventBuilderManager*)
   {
      ::FairEventBuilderManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairEventBuilderManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairEventBuilderManager", ::FairEventBuilderManager::Class_Version(), "invalid", 4773,
                  typeid(::FairEventBuilderManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairEventBuilderManager::Dictionary, isa_proxy, 4,
                  sizeof(::FairEventBuilderManager) );
      instance.SetDelete(&delete_FairEventBuilderManager);
      instance.SetDeleteArray(&deleteArray_FairEventBuilderManager);
      instance.SetDestructor(&destruct_FairEventBuilderManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairEventBuilderManager*)
   {
      return GenerateInitInstanceLocal((::FairEventBuilderManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairEventBuilderManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairEventHeader(void *p = 0);
   static void *newArray_FairEventHeader(Long_t size, void *p);
   static void delete_FairEventHeader(void *p);
   static void deleteArray_FairEventHeader(void *p);
   static void destruct_FairEventHeader(void *p);
   static void streamer_FairEventHeader(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairEventHeader*)
   {
      ::FairEventHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairEventHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairEventHeader", ::FairEventHeader::Class_Version(), "invalid", 4863,
                  typeid(::FairEventHeader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairEventHeader::Dictionary, isa_proxy, 16,
                  sizeof(::FairEventHeader) );
      instance.SetNew(&new_FairEventHeader);
      instance.SetNewArray(&newArray_FairEventHeader);
      instance.SetDelete(&delete_FairEventHeader);
      instance.SetDeleteArray(&deleteArray_FairEventHeader);
      instance.SetDestructor(&destruct_FairEventHeader);
      instance.SetStreamerFunc(&streamer_FairEventHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairEventHeader*)
   {
      return GenerateInitInstanceLocal((::FairEventHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairEventHeader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairFileHeader(void *p = 0);
   static void *newArray_FairFileHeader(Long_t size, void *p);
   static void delete_FairFileHeader(void *p);
   static void deleteArray_FairFileHeader(void *p);
   static void destruct_FairFileHeader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairFileHeader*)
   {
      ::FairFileHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairFileHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairFileHeader", ::FairFileHeader::Class_Version(), "invalid", 4949,
                  typeid(::FairFileHeader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairFileHeader::Dictionary, isa_proxy, 4,
                  sizeof(::FairFileHeader) );
      instance.SetNew(&new_FairFileHeader);
      instance.SetNewArray(&newArray_FairFileHeader);
      instance.SetDelete(&delete_FairFileHeader);
      instance.SetDeleteArray(&deleteArray_FairFileHeader);
      instance.SetDestructor(&destruct_FairFileHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairFileHeader*)
   {
      return GenerateInitInstanceLocal((::FairFileHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairFileHeader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeaneApplication(void *p = 0);
   static void *newArray_FairGeaneApplication(Long_t size, void *p);
   static void delete_FairGeaneApplication(void *p);
   static void deleteArray_FairGeaneApplication(void *p);
   static void destruct_FairGeaneApplication(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeaneApplication*)
   {
      ::FairGeaneApplication *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeaneApplication >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeaneApplication", ::FairGeaneApplication::Class_Version(), "invalid", 3092,
                  typeid(::FairGeaneApplication), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeaneApplication::Dictionary, isa_proxy, 4,
                  sizeof(::FairGeaneApplication) );
      instance.SetNew(&new_FairGeaneApplication);
      instance.SetNewArray(&newArray_FairGeaneApplication);
      instance.SetDelete(&delete_FairGeaneApplication);
      instance.SetDeleteArray(&deleteArray_FairGeaneApplication);
      instance.SetDestructor(&destruct_FairGeaneApplication);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeaneApplication*)
   {
      return GenerateInitInstanceLocal((::FairGeaneApplication*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeaneApplication*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairGenerator(void *p);
   static void deleteArray_FairGenerator(void *p);
   static void destruct_FairGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGenerator*)
   {
      ::FairGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGenerator", ::FairGenerator::Class_Version(), "invalid", 3192,
                  typeid(::FairGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairGenerator) );
      instance.SetDelete(&delete_FairGenerator);
      instance.SetDeleteArray(&deleteArray_FairGenerator);
      instance.SetDestructor(&destruct_FairGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGenerator*)
   {
      return GenerateInitInstanceLocal((::FairGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairLink(void *p = 0);
   static void *newArray_FairLink(Long_t size, void *p);
   static void delete_FairLink(void *p);
   static void deleteArray_FairLink(void *p);
   static void destruct_FairLink(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairLink*)
   {
      ::FairLink *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairLink >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairLink", ::FairLink::Class_Version(), "FairLink.h", 26,
                  typeid(::FairLink), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairLink::Dictionary, isa_proxy, 4,
                  sizeof(::FairLink) );
      instance.SetNew(&new_FairLink);
      instance.SetNewArray(&newArray_FairLink);
      instance.SetDelete(&delete_FairLink);
      instance.SetDeleteArray(&deleteArray_FairLink);
      instance.SetDestructor(&destruct_FairLink);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairLink*)
   {
      return GenerateInitInstanceLocal((::FairLink*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairLink*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMultiLinkedData(void *p = 0);
   static void *newArray_FairMultiLinkedData(Long_t size, void *p);
   static void delete_FairMultiLinkedData(void *p);
   static void deleteArray_FairMultiLinkedData(void *p);
   static void destruct_FairMultiLinkedData(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMultiLinkedData*)
   {
      ::FairMultiLinkedData *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMultiLinkedData >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMultiLinkedData", ::FairMultiLinkedData::Class_Version(), "FairMultiLinkedData.h", 30,
                  typeid(::FairMultiLinkedData), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMultiLinkedData::Dictionary, isa_proxy, 4,
                  sizeof(::FairMultiLinkedData) );
      instance.SetNew(&new_FairMultiLinkedData);
      instance.SetNewArray(&newArray_FairMultiLinkedData);
      instance.SetDelete(&delete_FairMultiLinkedData);
      instance.SetDeleteArray(&deleteArray_FairMultiLinkedData);
      instance.SetDestructor(&destruct_FairMultiLinkedData);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMultiLinkedData*)
   {
      return GenerateInitInstanceLocal((::FairMultiLinkedData*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMultiLinkedData*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMultiLinkedData_Interface(void *p = 0);
   static void *newArray_FairMultiLinkedData_Interface(Long_t size, void *p);
   static void delete_FairMultiLinkedData_Interface(void *p);
   static void deleteArray_FairMultiLinkedData_Interface(void *p);
   static void destruct_FairMultiLinkedData_Interface(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMultiLinkedData_Interface*)
   {
      ::FairMultiLinkedData_Interface *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMultiLinkedData_Interface >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMultiLinkedData_Interface", ::FairMultiLinkedData_Interface::Class_Version(), "FairMultiLinkedData_Interface.h", 27,
                  typeid(::FairMultiLinkedData_Interface), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMultiLinkedData_Interface::Dictionary, isa_proxy, 4,
                  sizeof(::FairMultiLinkedData_Interface) );
      instance.SetNew(&new_FairMultiLinkedData_Interface);
      instance.SetNewArray(&newArray_FairMultiLinkedData_Interface);
      instance.SetDelete(&delete_FairMultiLinkedData_Interface);
      instance.SetDeleteArray(&deleteArray_FairMultiLinkedData_Interface);
      instance.SetDestructor(&destruct_FairMultiLinkedData_Interface);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMultiLinkedData_Interface*)
   {
      return GenerateInitInstanceLocal((::FairMultiLinkedData_Interface*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMultiLinkedData_Interface*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairHit(void *p = 0);
   static void *newArray_FairHit(Long_t size, void *p);
   static void delete_FairHit(void *p);
   static void deleteArray_FairHit(void *p);
   static void destruct_FairHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairHit*)
   {
      ::FairHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairHit", ::FairHit::Class_Version(), "invalid", 5092,
                  typeid(::FairHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairHit::Dictionary, isa_proxy, 4,
                  sizeof(::FairHit) );
      instance.SetNew(&new_FairHit);
      instance.SetNewArray(&newArray_FairHit);
      instance.SetDelete(&delete_FairHit);
      instance.SetDeleteArray(&deleteArray_FairHit);
      instance.SetDestructor(&destruct_FairHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairHit*)
   {
      return GenerateInitInstanceLocal((::FairHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairIon(void *p = 0);
   static void *newArray_FairIon(Long_t size, void *p);
   static void delete_FairIon(void *p);
   static void deleteArray_FairIon(void *p);
   static void destruct_FairIon(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairIon*)
   {
      ::FairIon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairIon >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairIon", ::FairIon::Class_Version(), "FairIon.h", 31,
                  typeid(::FairIon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairIon::Dictionary, isa_proxy, 4,
                  sizeof(::FairIon) );
      instance.SetNew(&new_FairIon);
      instance.SetNewArray(&newArray_FairIon);
      instance.SetDelete(&delete_FairIon);
      instance.SetDeleteArray(&deleteArray_FairIon);
      instance.SetDestructor(&destruct_FairIon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairIon*)
   {
      return GenerateInitInstanceLocal((::FairIon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairIon*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCApplication(void *p = 0);
   static void *newArray_FairMCApplication(Long_t size, void *p);
   static void delete_FairMCApplication(void *p);
   static void deleteArray_FairMCApplication(void *p);
   static void destruct_FairMCApplication(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCApplication*)
   {
      ::FairMCApplication *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCApplication >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCApplication", ::FairMCApplication::Class_Version(), "FairMCApplication.h", 54,
                  typeid(::FairMCApplication), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCApplication::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCApplication) );
      instance.SetNew(&new_FairMCApplication);
      instance.SetNewArray(&newArray_FairMCApplication);
      instance.SetDelete(&delete_FairMCApplication);
      instance.SetDeleteArray(&deleteArray_FairMCApplication);
      instance.SetDestructor(&destruct_FairMCApplication);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCApplication*)
   {
      return GenerateInitInstanceLocal((::FairMCApplication*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCApplication*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCEventHeader(void *p = 0);
   static void *newArray_FairMCEventHeader(Long_t size, void *p);
   static void delete_FairMCEventHeader(void *p);
   static void deleteArray_FairMCEventHeader(void *p);
   static void destruct_FairMCEventHeader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCEventHeader*)
   {
      ::FairMCEventHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCEventHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCEventHeader", ::FairMCEventHeader::Class_Version(), "invalid", 5349,
                  typeid(::FairMCEventHeader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCEventHeader::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCEventHeader) );
      instance.SetNew(&new_FairMCEventHeader);
      instance.SetNewArray(&newArray_FairMCEventHeader);
      instance.SetDelete(&delete_FairMCEventHeader);
      instance.SetDeleteArray(&deleteArray_FairMCEventHeader);
      instance.SetDestructor(&destruct_FairMCEventHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCEventHeader*)
   {
      return GenerateInitInstanceLocal((::FairMCEventHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCEventHeader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCPoint(void *p = 0);
   static void *newArray_FairMCPoint(Long_t size, void *p);
   static void delete_FairMCPoint(void *p);
   static void deleteArray_FairMCPoint(void *p);
   static void destruct_FairMCPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCPoint*)
   {
      ::FairMCPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCPoint", ::FairMCPoint::Class_Version(), "invalid", 5483,
                  typeid(::FairMCPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCPoint::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCPoint) );
      instance.SetNew(&new_FairMCPoint);
      instance.SetNewArray(&newArray_FairMCPoint);
      instance.SetDelete(&delete_FairMCPoint);
      instance.SetDeleteArray(&deleteArray_FairMCPoint);
      instance.SetDestructor(&destruct_FairMCPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCPoint*)
   {
      return GenerateInitInstanceLocal((::FairMCPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCPoint*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairModule(void *p = 0);
   static void *newArray_FairModule(Long_t size, void *p);
   static void delete_FairModule(void *p);
   static void deleteArray_FairModule(void *p);
   static void destruct_FairModule(void *p);
   static void streamer_FairModule(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairModule*)
   {
      ::FairModule *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairModule >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairModule", ::FairModule::Class_Version(), "FairModule.h", 49,
                  typeid(::FairModule), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairModule::Dictionary, isa_proxy, 17,
                  sizeof(::FairModule) );
      instance.SetNew(&new_FairModule);
      instance.SetNewArray(&newArray_FairModule);
      instance.SetDelete(&delete_FairModule);
      instance.SetDeleteArray(&deleteArray_FairModule);
      instance.SetDestructor(&destruct_FairModule);
      instance.SetStreamerFunc(&streamer_FairModule);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairModule*)
   {
      return GenerateInitInstanceLocal((::FairModule*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairModule*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairParticle(void *p = 0);
   static void *newArray_FairParticle(Long_t size, void *p);
   static void delete_FairParticle(void *p);
   static void deleteArray_FairParticle(void *p);
   static void destruct_FairParticle(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairParticle*)
   {
      ::FairParticle *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairParticle >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairParticle", ::FairParticle::Class_Version(), "FairParticle.h", 27,
                  typeid(::FairParticle), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairParticle::Dictionary, isa_proxy, 4,
                  sizeof(::FairParticle) );
      instance.SetNew(&new_FairParticle);
      instance.SetNewArray(&newArray_FairParticle);
      instance.SetDelete(&delete_FairParticle);
      instance.SetDeleteArray(&deleteArray_FairParticle);
      instance.SetDestructor(&destruct_FairParticle);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairParticle*)
   {
      return GenerateInitInstanceLocal((::FairParticle*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairParticle*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairPrimaryGenerator(void *p = 0);
   static void *newArray_FairPrimaryGenerator(Long_t size, void *p);
   static void delete_FairPrimaryGenerator(void *p);
   static void deleteArray_FairPrimaryGenerator(void *p);
   static void destruct_FairPrimaryGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairPrimaryGenerator*)
   {
      ::FairPrimaryGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairPrimaryGenerator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairPrimaryGenerator", ::FairPrimaryGenerator::Class_Version(), "invalid", 4185,
                  typeid(::FairPrimaryGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairPrimaryGenerator::Dictionary, isa_proxy, 4,
                  sizeof(::FairPrimaryGenerator) );
      instance.SetNew(&new_FairPrimaryGenerator);
      instance.SetNewArray(&newArray_FairPrimaryGenerator);
      instance.SetDelete(&delete_FairPrimaryGenerator);
      instance.SetDeleteArray(&deleteArray_FairPrimaryGenerator);
      instance.SetDestructor(&destruct_FairPrimaryGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairPrimaryGenerator*)
   {
      return GenerateInitInstanceLocal((::FairPrimaryGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairPrimaryGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRecoEventHeader(void *p = 0);
   static void *newArray_FairRecoEventHeader(Long_t size, void *p);
   static void delete_FairRecoEventHeader(void *p);
   static void deleteArray_FairRecoEventHeader(void *p);
   static void destruct_FairRecoEventHeader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRecoEventHeader*)
   {
      ::FairRecoEventHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRecoEventHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRecoEventHeader", ::FairRecoEventHeader::Class_Version(), "FairRecoEventHeader.h", 25,
                  typeid(::FairRecoEventHeader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRecoEventHeader::Dictionary, isa_proxy, 4,
                  sizeof(::FairRecoEventHeader) );
      instance.SetNew(&new_FairRecoEventHeader);
      instance.SetNewArray(&newArray_FairRecoEventHeader);
      instance.SetDelete(&delete_FairRecoEventHeader);
      instance.SetDeleteArray(&deleteArray_FairRecoEventHeader);
      instance.SetDestructor(&destruct_FairRecoEventHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRecoEventHeader*)
   {
      return GenerateInitInstanceLocal((::FairRecoEventHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRecoEventHeader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRootManager(void *p = 0);
   static void *newArray_FairRootManager(Long_t size, void *p);
   static void delete_FairRootManager(void *p);
   static void deleteArray_FairRootManager(void *p);
   static void destruct_FairRootManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRootManager*)
   {
      ::FairRootManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRootManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRootManager", ::FairRootManager::Class_Version(), "FairRootManager.h", 54,
                  typeid(::FairRootManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRootManager::Dictionary, isa_proxy, 4,
                  sizeof(::FairRootManager) );
      instance.SetNew(&new_FairRootManager);
      instance.SetNewArray(&newArray_FairRootManager);
      instance.SetDelete(&delete_FairRootManager);
      instance.SetDeleteArray(&deleteArray_FairRootManager);
      instance.SetDestructor(&destruct_FairRootManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRootManager*)
   {
      return GenerateInitInstanceLocal((::FairRootManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRootManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairRun(void *p);
   static void deleteArray_FairRun(void *p);
   static void destruct_FairRun(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRun*)
   {
      ::FairRun *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRun >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRun", ::FairRun::Class_Version(), "invalid", 1022,
                  typeid(::FairRun), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRun::Dictionary, isa_proxy, 4,
                  sizeof(::FairRun) );
      instance.SetDelete(&delete_FairRun);
      instance.SetDeleteArray(&deleteArray_FairRun);
      instance.SetDestructor(&destruct_FairRun);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRun*)
   {
      return GenerateInitInstanceLocal((::FairRun*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRun*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRunAna(void *p = 0);
   static void *newArray_FairRunAna(Long_t size, void *p);
   static void delete_FairRunAna(void *p);
   static void deleteArray_FairRunAna(void *p);
   static void destruct_FairRunAna(void *p);
   static void streamer_FairRunAna(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRunAna*)
   {
      ::FairRunAna *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRunAna >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRunAna", ::FairRunAna::Class_Version(), "invalid", 1225,
                  typeid(::FairRunAna), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRunAna::Dictionary, isa_proxy, 16,
                  sizeof(::FairRunAna) );
      instance.SetNew(&new_FairRunAna);
      instance.SetNewArray(&newArray_FairRunAna);
      instance.SetDelete(&delete_FairRunAna);
      instance.SetDeleteArray(&deleteArray_FairRunAna);
      instance.SetDestructor(&destruct_FairRunAna);
      instance.SetStreamerFunc(&streamer_FairRunAna);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRunAna*)
   {
      return GenerateInitInstanceLocal((::FairRunAna*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRunAna*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRunAnaProof(void *p = 0);
   static void *newArray_FairRunAnaProof(Long_t size, void *p);
   static void delete_FairRunAnaProof(void *p);
   static void deleteArray_FairRunAnaProof(void *p);
   static void destruct_FairRunAnaProof(void *p);
   static void streamer_FairRunAnaProof(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRunAnaProof*)
   {
      ::FairRunAnaProof *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRunAnaProof >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRunAnaProof", ::FairRunAnaProof::Class_Version(), "invalid", 1424,
                  typeid(::FairRunAnaProof), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRunAnaProof::Dictionary, isa_proxy, 16,
                  sizeof(::FairRunAnaProof) );
      instance.SetNew(&new_FairRunAnaProof);
      instance.SetNewArray(&newArray_FairRunAnaProof);
      instance.SetDelete(&delete_FairRunAnaProof);
      instance.SetDeleteArray(&deleteArray_FairRunAnaProof);
      instance.SetDestructor(&destruct_FairRunAnaProof);
      instance.SetStreamerFunc(&streamer_FairRunAnaProof);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRunAnaProof*)
   {
      return GenerateInitInstanceLocal((::FairRunAnaProof*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRunAnaProof*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *FairRunIdGenerator_Dictionary();
   static void FairRunIdGenerator_TClassManip(TClass*);
   static void *new_FairRunIdGenerator(void *p = 0);
   static void *newArray_FairRunIdGenerator(Long_t size, void *p);
   static void delete_FairRunIdGenerator(void *p);
   static void deleteArray_FairRunIdGenerator(void *p);
   static void destruct_FairRunIdGenerator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRunIdGenerator*)
   {
      ::FairRunIdGenerator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::FairRunIdGenerator));
      static ::ROOT::TGenericClassInfo 
         instance("FairRunIdGenerator", "invalid", 4433,
                  typeid(::FairRunIdGenerator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &FairRunIdGenerator_Dictionary, isa_proxy, 0,
                  sizeof(::FairRunIdGenerator) );
      instance.SetNew(&new_FairRunIdGenerator);
      instance.SetNewArray(&newArray_FairRunIdGenerator);
      instance.SetDelete(&delete_FairRunIdGenerator);
      instance.SetDeleteArray(&deleteArray_FairRunIdGenerator);
      instance.SetDestructor(&destruct_FairRunIdGenerator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRunIdGenerator*)
   {
      return GenerateInitInstanceLocal((::FairRunIdGenerator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRunIdGenerator*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *FairRunIdGenerator_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::FairRunIdGenerator*)0x0)->GetClass();
      FairRunIdGenerator_TClassManip(theClass);
   return theClass;
   }

   static void FairRunIdGenerator_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRunSim(void *p = 0);
   static void *newArray_FairRunSim(Long_t size, void *p);
   static void delete_FairRunSim(void *p);
   static void deleteArray_FairRunSim(void *p);
   static void destruct_FairRunSim(void *p);
   static void streamer_FairRunSim(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRunSim*)
   {
      ::FairRunSim *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRunSim >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRunSim", ::FairRunSim::Class_Version(), "invalid", 1546,
                  typeid(::FairRunSim), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRunSim::Dictionary, isa_proxy, 16,
                  sizeof(::FairRunSim) );
      instance.SetNew(&new_FairRunSim);
      instance.SetNewArray(&newArray_FairRunSim);
      instance.SetDelete(&delete_FairRunSim);
      instance.SetDeleteArray(&deleteArray_FairRunSim);
      instance.SetDestructor(&destruct_FairRunSim);
      instance.SetStreamerFunc(&streamer_FairRunSim);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRunSim*)
   {
      return GenerateInitInstanceLocal((::FairRunSim*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRunSim*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTrackParam(void *p = 0);
   static void *newArray_FairTrackParam(Long_t size, void *p);
   static void delete_FairTrackParam(void *p);
   static void deleteArray_FairTrackParam(void *p);
   static void destruct_FairTrackParam(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTrackParam*)
   {
      ::FairTrackParam *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTrackParam >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTrackParam", ::FairTrackParam::Class_Version(), "invalid", 6478,
                  typeid(::FairTrackParam), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTrackParam::Dictionary, isa_proxy, 4,
                  sizeof(::FairTrackParam) );
      instance.SetNew(&new_FairTrackParam);
      instance.SetNewArray(&newArray_FairTrackParam);
      instance.SetDelete(&delete_FairTrackParam);
      instance.SetDeleteArray(&deleteArray_FairTrackParam);
      instance.SetDestructor(&destruct_FairTrackParam);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTrackParam*)
   {
      return GenerateInitInstanceLocal((::FairTrackParam*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTrackParam*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTrajFilter(void *p = 0);
   static void *newArray_FairTrajFilter(Long_t size, void *p);
   static void delete_FairTrajFilter(void *p);
   static void deleteArray_FairTrajFilter(void *p);
   static void destruct_FairTrajFilter(void *p);
   static void streamer_FairTrajFilter(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTrajFilter*)
   {
      ::FairTrajFilter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTrajFilter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTrajFilter", ::FairTrajFilter::Class_Version(), "invalid", 2144,
                  typeid(::FairTrajFilter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTrajFilter::Dictionary, isa_proxy, 16,
                  sizeof(::FairTrajFilter) );
      instance.SetNew(&new_FairTrajFilter);
      instance.SetNewArray(&newArray_FairTrajFilter);
      instance.SetDelete(&delete_FairTrajFilter);
      instance.SetDeleteArray(&deleteArray_FairTrajFilter);
      instance.SetDestructor(&destruct_FairTrajFilter);
      instance.SetStreamerFunc(&streamer_FairTrajFilter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTrajFilter*)
   {
      return GenerateInitInstanceLocal((::FairTrajFilter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTrajFilter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairVolume(void *p = 0);
   static void *newArray_FairVolume(Long_t size, void *p);
   static void delete_FairVolume(void *p);
   static void deleteArray_FairVolume(void *p);
   static void destruct_FairVolume(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairVolume*)
   {
      ::FairVolume *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairVolume >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairVolume", ::FairVolume::Class_Version(), "invalid", 4496,
                  typeid(::FairVolume), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairVolume::Dictionary, isa_proxy, 4,
                  sizeof(::FairVolume) );
      instance.SetNew(&new_FairVolume);
      instance.SetNewArray(&newArray_FairVolume);
      instance.SetDelete(&delete_FairVolume);
      instance.SetDeleteArray(&deleteArray_FairVolume);
      instance.SetDestructor(&destruct_FairVolume);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairVolume*)
   {
      return GenerateInitInstanceLocal((::FairVolume*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairVolume*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairVolumeList(void *p = 0);
   static void *newArray_FairVolumeList(Long_t size, void *p);
   static void delete_FairVolumeList(void *p);
   static void deleteArray_FairVolumeList(void *p);
   static void destruct_FairVolumeList(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairVolumeList*)
   {
      ::FairVolumeList *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairVolumeList >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairVolumeList", ::FairVolumeList::Class_Version(), "invalid", 4586,
                  typeid(::FairVolumeList), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairVolumeList::Dictionary, isa_proxy, 4,
                  sizeof(::FairVolumeList) );
      instance.SetNew(&new_FairVolumeList);
      instance.SetNewArray(&newArray_FairVolumeList);
      instance.SetDelete(&delete_FairVolumeList);
      instance.SetDeleteArray(&deleteArray_FairVolumeList);
      instance.SetDestructor(&destruct_FairVolumeList);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairVolumeList*)
   {
      return GenerateInitInstanceLocal((::FairVolumeList*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairVolumeList*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairField(void *p = 0);
   static void *newArray_FairField(Long_t size, void *p);
   static void delete_FairField(void *p);
   static void deleteArray_FairField(void *p);
   static void destruct_FairField(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairField*)
   {
      ::FairField *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairField >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairField", ::FairField::Class_Version(), "invalid", 6630,
                  typeid(::FairField), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairField::Dictionary, isa_proxy, 4,
                  sizeof(::FairField) );
      instance.SetNew(&new_FairField);
      instance.SetNewArray(&newArray_FairField);
      instance.SetDelete(&delete_FairField);
      instance.SetDeleteArray(&deleteArray_FairField);
      instance.SetDestructor(&destruct_FairField);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairField*)
   {
      return GenerateInitInstanceLocal((::FairField*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairField*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGenericStack(void *p = 0);
   static void *newArray_FairGenericStack(Long_t size, void *p);
   static void delete_FairGenericStack(void *p);
   static void deleteArray_FairGenericStack(void *p);
   static void destruct_FairGenericStack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGenericStack*)
   {
      ::FairGenericStack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGenericStack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGenericStack", ::FairGenericStack::Class_Version(), "invalid", 3274,
                  typeid(::FairGenericStack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGenericStack::Dictionary, isa_proxy, 4,
                  sizeof(::FairGenericStack) );
      instance.SetNew(&new_FairGenericStack);
      instance.SetNewArray(&newArray_FairGenericStack);
      instance.SetDelete(&delete_FairGenericStack);
      instance.SetDeleteArray(&deleteArray_FairGenericStack);
      instance.SetDestructor(&destruct_FairGenericStack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGenericStack*)
   {
      return GenerateInitInstanceLocal((::FairGenericStack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGenericStack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTask(void *p = 0);
   static void *newArray_FairTask(Long_t size, void *p);
   static void delete_FairTask(void *p);
   static void deleteArray_FairTask(void *p);
   static void destruct_FairTask(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTask*)
   {
      ::FairTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTask", ::FairTask::Class_Version(), "FairTask.h", 38,
                  typeid(::FairTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTask::Dictionary, isa_proxy, 4,
                  sizeof(::FairTask) );
      instance.SetNew(&new_FairTask);
      instance.SetNewArray(&newArray_FairTask);
      instance.SetDelete(&delete_FairTask);
      instance.SetDeleteArray(&deleteArray_FairTask);
      instance.SetDestructor(&destruct_FairTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTask*)
   {
      return GenerateInitInstanceLocal((::FairTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairFieldFactory(void *p = 0);
   static void *newArray_FairFieldFactory(Long_t size, void *p);
   static void delete_FairFieldFactory(void *p);
   static void deleteArray_FairFieldFactory(void *p);
   static void destruct_FairFieldFactory(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairFieldFactory*)
   {
      ::FairFieldFactory *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairFieldFactory >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairFieldFactory", ::FairFieldFactory::Class_Version(), "invalid", 6739,
                  typeid(::FairFieldFactory), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairFieldFactory::Dictionary, isa_proxy, 4,
                  sizeof(::FairFieldFactory) );
      instance.SetNew(&new_FairFieldFactory);
      instance.SetNewArray(&newArray_FairFieldFactory);
      instance.SetDelete(&delete_FairFieldFactory);
      instance.SetDeleteArray(&deleteArray_FairFieldFactory);
      instance.SetDestructor(&destruct_FairFieldFactory);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairFieldFactory*)
   {
      return GenerateInitInstanceLocal((::FairFieldFactory*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairFieldFactory*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRadLenPoint(void *p = 0);
   static void *newArray_FairRadLenPoint(Long_t size, void *p);
   static void delete_FairRadLenPoint(void *p);
   static void deleteArray_FairRadLenPoint(void *p);
   static void destruct_FairRadLenPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRadLenPoint*)
   {
      ::FairRadLenPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRadLenPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRadLenPoint", ::FairRadLenPoint::Class_Version(), "invalid", 5990,
                  typeid(::FairRadLenPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRadLenPoint::Dictionary, isa_proxy, 4,
                  sizeof(::FairRadLenPoint) );
      instance.SetNew(&new_FairRadLenPoint);
      instance.SetNewArray(&newArray_FairRadLenPoint);
      instance.SetDelete(&delete_FairRadLenPoint);
      instance.SetDeleteArray(&deleteArray_FairRadLenPoint);
      instance.SetDestructor(&destruct_FairRadLenPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRadLenPoint*)
   {
      return GenerateInitInstanceLocal((::FairRadLenPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRadLenPoint*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRadLenManager(void *p = 0);
   static void *newArray_FairRadLenManager(Long_t size, void *p);
   static void delete_FairRadLenManager(void *p);
   static void deleteArray_FairRadLenManager(void *p);
   static void destruct_FairRadLenManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRadLenManager*)
   {
      ::FairRadLenManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRadLenManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRadLenManager", ::FairRadLenManager::Class_Version(), "invalid", 252,
                  typeid(::FairRadLenManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRadLenManager::Dictionary, isa_proxy, 4,
                  sizeof(::FairRadLenManager) );
      instance.SetNew(&new_FairRadLenManager);
      instance.SetNewArray(&newArray_FairRadLenManager);
      instance.SetDelete(&delete_FairRadLenManager);
      instance.SetDeleteArray(&deleteArray_FairRadLenManager);
      instance.SetDestructor(&destruct_FairRadLenManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRadLenManager*)
   {
      return GenerateInitInstanceLocal((::FairRadLenManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRadLenManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRadGridManager(void *p = 0);
   static void *newArray_FairRadGridManager(Long_t size, void *p);
   static void delete_FairRadGridManager(void *p);
   static void deleteArray_FairRadGridManager(void *p);
   static void destruct_FairRadGridManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRadGridManager*)
   {
      ::FairRadGridManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRadGridManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRadGridManager", ::FairRadGridManager::Class_Version(), "invalid", 136,
                  typeid(::FairRadGridManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRadGridManager::Dictionary, isa_proxy, 4,
                  sizeof(::FairRadGridManager) );
      instance.SetNew(&new_FairRadGridManager);
      instance.SetNewArray(&newArray_FairRadGridManager);
      instance.SetDelete(&delete_FairRadGridManager);
      instance.SetDeleteArray(&deleteArray_FairRadGridManager);
      instance.SetDestructor(&destruct_FairRadGridManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRadGridManager*)
   {
      return GenerateInitInstanceLocal((::FairRadGridManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRadGridManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRadMapManager(void *p = 0);
   static void *newArray_FairRadMapManager(Long_t size, void *p);
   static void delete_FairRadMapManager(void *p);
   static void deleteArray_FairRadMapManager(void *p);
   static void destruct_FairRadMapManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRadMapManager*)
   {
      ::FairRadMapManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRadMapManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRadMapManager", ::FairRadMapManager::Class_Version(), "invalid", 355,
                  typeid(::FairRadMapManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRadMapManager::Dictionary, isa_proxy, 4,
                  sizeof(::FairRadMapManager) );
      instance.SetNew(&new_FairRadMapManager);
      instance.SetNewArray(&newArray_FairRadMapManager);
      instance.SetDelete(&delete_FairRadMapManager);
      instance.SetDeleteArray(&deleteArray_FairRadMapManager);
      instance.SetDestructor(&destruct_FairRadMapManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRadMapManager*)
   {
      return GenerateInitInstanceLocal((::FairRadMapManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRadMapManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMesh(void *p = 0);
   static void *newArray_FairMesh(Long_t size, void *p);
   static void delete_FairMesh(void *p);
   static void deleteArray_FairMesh(void *p);
   static void destruct_FairMesh(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMesh*)
   {
      ::FairMesh *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMesh >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMesh", ::FairMesh::Class_Version(), "invalid", 5641,
                  typeid(::FairMesh), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMesh::Dictionary, isa_proxy, 4,
                  sizeof(::FairMesh) );
      instance.SetNew(&new_FairMesh);
      instance.SetNewArray(&newArray_FairMesh);
      instance.SetDelete(&delete_FairMesh);
      instance.SetDeleteArray(&deleteArray_FairMesh);
      instance.SetDestructor(&destruct_FairMesh);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMesh*)
   {
      return GenerateInitInstanceLocal((::FairMesh*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMesh*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairRKPropagator(void *p);
   static void deleteArray_FairRKPropagator(void *p);
   static void destruct_FairRKPropagator(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRKPropagator*)
   {
      ::FairRKPropagator *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRKPropagator >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRKPropagator", ::FairRKPropagator::Class_Version(), "invalid", 6797,
                  typeid(::FairRKPropagator), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRKPropagator::Dictionary, isa_proxy, 4,
                  sizeof(::FairRKPropagator) );
      instance.SetDelete(&delete_FairRKPropagator);
      instance.SetDeleteArray(&deleteArray_FairRKPropagator);
      instance.SetDestructor(&destruct_FairRKPropagator);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRKPropagator*)
   {
      return GenerateInitInstanceLocal((::FairRKPropagator*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRKPropagator*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTimeStamp(void *p = 0);
   static void *newArray_FairTimeStamp(Long_t size, void *p);
   static void delete_FairTimeStamp(void *p);
   static void deleteArray_FairTimeStamp(void *p);
   static void destruct_FairTimeStamp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTimeStamp*)
   {
      ::FairTimeStamp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTimeStamp >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTimeStamp", ::FairTimeStamp::Class_Version(), "FairTimeStamp.h", 32,
                  typeid(::FairTimeStamp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTimeStamp::Dictionary, isa_proxy, 4,
                  sizeof(::FairTimeStamp) );
      instance.SetNew(&new_FairTimeStamp);
      instance.SetNewArray(&newArray_FairTimeStamp);
      instance.SetDelete(&delete_FairTimeStamp);
      instance.SetDeleteArray(&deleteArray_FairTimeStamp);
      instance.SetDestructor(&destruct_FairTimeStamp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTimeStamp*)
   {
      return GenerateInitInstanceLocal((::FairTimeStamp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTimeStamp*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRadMapPoint(void *p = 0);
   static void *newArray_FairRadMapPoint(Long_t size, void *p);
   static void delete_FairRadMapPoint(void *p);
   static void deleteArray_FairRadMapPoint(void *p);
   static void destruct_FairRadMapPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRadMapPoint*)
   {
      ::FairRadMapPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRadMapPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRadMapPoint", ::FairRadMapPoint::Class_Version(), "invalid", 6081,
                  typeid(::FairRadMapPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRadMapPoint::Dictionary, isa_proxy, 4,
                  sizeof(::FairRadMapPoint) );
      instance.SetNew(&new_FairRadMapPoint);
      instance.SetNewArray(&newArray_FairRadMapPoint);
      instance.SetDelete(&delete_FairRadMapPoint);
      instance.SetDeleteArray(&deleteArray_FairRadMapPoint);
      instance.SetDestructor(&destruct_FairRadMapPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRadMapPoint*)
   {
      return GenerateInitInstanceLocal((::FairRadMapPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRadMapPoint*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairTSBufferFunctional(void *p);
   static void deleteArray_FairTSBufferFunctional(void *p);
   static void destruct_FairTSBufferFunctional(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTSBufferFunctional*)
   {
      ::FairTSBufferFunctional *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTSBufferFunctional >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTSBufferFunctional", ::FairTSBufferFunctional::Class_Version(), "invalid", 1876,
                  typeid(::FairTSBufferFunctional), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTSBufferFunctional::Dictionary, isa_proxy, 4,
                  sizeof(::FairTSBufferFunctional) );
      instance.SetDelete(&delete_FairTSBufferFunctional);
      instance.SetDeleteArray(&deleteArray_FairTSBufferFunctional);
      instance.SetDestructor(&destruct_FairTSBufferFunctional);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTSBufferFunctional*)
   {
      return GenerateInitInstanceLocal((::FairTSBufferFunctional*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTSBufferFunctional*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairFileInfo(void *p = 0);
   static void *newArray_FairFileInfo(Long_t size, void *p);
   static void delete_FairFileInfo(void *p);
   static void deleteArray_FairFileInfo(void *p);
   static void destruct_FairFileInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairFileInfo*)
   {
      ::FairFileInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairFileInfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairFileInfo", ::FairFileInfo::Class_Version(), "invalid", 5024,
                  typeid(::FairFileInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairFileInfo::Dictionary, isa_proxy, 4,
                  sizeof(::FairFileInfo) );
      instance.SetNew(&new_FairFileInfo);
      instance.SetNewArray(&newArray_FairFileInfo);
      instance.SetDelete(&delete_FairFileInfo);
      instance.SetDeleteArray(&deleteArray_FairFileInfo);
      instance.SetDestructor(&destruct_FairFileInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairFileInfo*)
   {
      return GenerateInitInstanceLocal((::FairFileInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairFileInfo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRunInfo(void *p = 0);
   static void *newArray_FairRunInfo(Long_t size, void *p);
   static void delete_FairRunInfo(void *p);
   static void deleteArray_FairRunInfo(void *p);
   static void destruct_FairRunInfo(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRunInfo*)
   {
      ::FairRunInfo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRunInfo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRunInfo", ::FairRunInfo::Class_Version(), "FairRunInfo.h", 22,
                  typeid(::FairRunInfo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRunInfo::Dictionary, isa_proxy, 4,
                  sizeof(::FairRunInfo) );
      instance.SetNew(&new_FairRunInfo);
      instance.SetNewArray(&newArray_FairRunInfo);
      instance.SetDelete(&delete_FairRunInfo);
      instance.SetDeleteArray(&deleteArray_FairRunInfo);
      instance.SetDestructor(&destruct_FairRunInfo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRunInfo*)
   {
      return GenerateInitInstanceLocal((::FairRunInfo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRunInfo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairWriteoutBuffer(void *p);
   static void deleteArray_FairWriteoutBuffer(void *p);
   static void destruct_FairWriteoutBuffer(void *p);
   static void streamer_FairWriteoutBuffer(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairWriteoutBuffer*)
   {
      ::FairWriteoutBuffer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairWriteoutBuffer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairWriteoutBuffer", ::FairWriteoutBuffer::Class_Version(), "invalid", 2415,
                  typeid(::FairWriteoutBuffer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairWriteoutBuffer::Dictionary, isa_proxy, 16,
                  sizeof(::FairWriteoutBuffer) );
      instance.SetDelete(&delete_FairWriteoutBuffer);
      instance.SetDeleteArray(&deleteArray_FairWriteoutBuffer);
      instance.SetDestructor(&destruct_FairWriteoutBuffer);
      instance.SetStreamerFunc(&streamer_FairWriteoutBuffer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairWriteoutBuffer*)
   {
      return GenerateInitInstanceLocal((::FairWriteoutBuffer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairWriteoutBuffer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRingSorter(void *p = 0);
   static void *newArray_FairRingSorter(Long_t size, void *p);
   static void delete_FairRingSorter(void *p);
   static void deleteArray_FairRingSorter(void *p);
   static void destruct_FairRingSorter(void *p);
   static void streamer_FairRingSorter(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRingSorter*)
   {
      ::FairRingSorter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRingSorter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRingSorter", ::FairRingSorter::Class_Version(), "invalid", 478,
                  typeid(::FairRingSorter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRingSorter::Dictionary, isa_proxy, 16,
                  sizeof(::FairRingSorter) );
      instance.SetNew(&new_FairRingSorter);
      instance.SetNewArray(&newArray_FairRingSorter);
      instance.SetDelete(&delete_FairRingSorter);
      instance.SetDeleteArray(&deleteArray_FairRingSorter);
      instance.SetDestructor(&destruct_FairRingSorter);
      instance.SetStreamerFunc(&streamer_FairRingSorter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRingSorter*)
   {
      return GenerateInitInstanceLocal((::FairRingSorter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRingSorter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRingSorterTask(void *p = 0);
   static void *newArray_FairRingSorterTask(Long_t size, void *p);
   static void delete_FairRingSorterTask(void *p);
   static void deleteArray_FairRingSorterTask(void *p);
   static void destruct_FairRingSorterTask(void *p);
   static void streamer_FairRingSorterTask(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRingSorterTask*)
   {
      ::FairRingSorterTask *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRingSorterTask >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRingSorterTask", ::FairRingSorterTask::Class_Version(), "invalid", 554,
                  typeid(::FairRingSorterTask), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRingSorterTask::Dictionary, isa_proxy, 16,
                  sizeof(::FairRingSorterTask) );
      instance.SetNew(&new_FairRingSorterTask);
      instance.SetNewArray(&newArray_FairRingSorterTask);
      instance.SetDelete(&delete_FairRingSorterTask);
      instance.SetDeleteArray(&deleteArray_FairRingSorterTask);
      instance.SetDestructor(&destruct_FairRingSorterTask);
      instance.SetStreamerFunc(&streamer_FairRingSorterTask);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRingSorterTask*)
   {
      return GenerateInitInstanceLocal((::FairRingSorterTask*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRingSorterTask*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairAnaSelector(void *p = 0);
   static void *newArray_FairAnaSelector(Long_t size, void *p);
   static void delete_FairAnaSelector(void *p);
   static void deleteArray_FairAnaSelector(void *p);
   static void destruct_FairAnaSelector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairAnaSelector*)
   {
      ::FairAnaSelector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairAnaSelector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairAnaSelector", ::FairAnaSelector::Class_Version(), "invalid", 45,
                  typeid(::FairAnaSelector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairAnaSelector::Dictionary, isa_proxy, 4,
                  sizeof(::FairAnaSelector) );
      instance.SetNew(&new_FairAnaSelector);
      instance.SetNewArray(&newArray_FairAnaSelector);
      instance.SetDelete(&delete_FairAnaSelector);
      instance.SetDeleteArray(&deleteArray_FairAnaSelector);
      instance.SetDestructor(&destruct_FairAnaSelector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairAnaSelector*)
   {
      return GenerateInitInstanceLocal((::FairAnaSelector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairAnaSelector*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairLinkManager(void *p = 0);
   static void *newArray_FairLinkManager(Long_t size, void *p);
   static void delete_FairLinkManager(void *p);
   static void deleteArray_FairLinkManager(void *p);
   static void destruct_FairLinkManager(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairLinkManager*)
   {
      ::FairLinkManager *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairLinkManager >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairLinkManager", ::FairLinkManager::Class_Version(), "invalid", 2645,
                  typeid(::FairLinkManager), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairLinkManager::Dictionary, isa_proxy, 4,
                  sizeof(::FairLinkManager) );
      instance.SetNew(&new_FairLinkManager);
      instance.SetNewArray(&newArray_FairLinkManager);
      instance.SetDelete(&delete_FairLinkManager);
      instance.SetDeleteArray(&deleteArray_FairLinkManager);
      instance.SetDestructor(&destruct_FairLinkManager);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairLinkManager*)
   {
      return GenerateInitInstanceLocal((::FairLinkManager*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairLinkManager*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairRunOnline(void *p = 0);
   static void *newArray_FairRunOnline(Long_t size, void *p);
   static void delete_FairRunOnline(void *p);
   static void deleteArray_FairRunOnline(void *p);
   static void destruct_FairRunOnline(void *p);
   static void streamer_FairRunOnline(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRunOnline*)
   {
      ::FairRunOnline *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRunOnline >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRunOnline", ::FairRunOnline::Class_Version(), "invalid", 2535,
                  typeid(::FairRunOnline), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRunOnline::Dictionary, isa_proxy, 16,
                  sizeof(::FairRunOnline) );
      instance.SetNew(&new_FairRunOnline);
      instance.SetNewArray(&newArray_FairRunOnline);
      instance.SetDelete(&delete_FairRunOnline);
      instance.SetDeleteArray(&deleteArray_FairRunOnline);
      instance.SetDestructor(&destruct_FairRunOnline);
      instance.SetStreamerFunc(&streamer_FairRunOnline);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRunOnline*)
   {
      return GenerateInitInstanceLocal((::FairRunOnline*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRunOnline*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairSource(void *p);
   static void deleteArray_FairSource(void *p);
   static void destruct_FairSource(void *p);
   static void streamer_FairSource(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairSource*)
   {
      ::FairSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairSource", ::FairSource::Class_Version(), "FairSource.h", 26,
                  typeid(::FairSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairSource::Dictionary, isa_proxy, 16,
                  sizeof(::FairSource) );
      instance.SetDelete(&delete_FairSource);
      instance.SetDeleteArray(&deleteArray_FairSource);
      instance.SetDestructor(&destruct_FairSource);
      instance.SetStreamerFunc(&streamer_FairSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairSource*)
   {
      return GenerateInitInstanceLocal((::FairSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairFileSource(void *p);
   static void deleteArray_FairFileSource(void *p);
   static void destruct_FairFileSource(void *p);
   static void streamer_FairFileSource(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairFileSource*)
   {
      ::FairFileSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairFileSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairFileSource", ::FairFileSource::Class_Version(), "FairFileSource.h", 32,
                  typeid(::FairFileSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairFileSource::Dictionary, isa_proxy, 16,
                  sizeof(::FairFileSource) );
      instance.SetDelete(&delete_FairFileSource);
      instance.SetDeleteArray(&deleteArray_FairFileSource);
      instance.SetDestructor(&destruct_FairFileSource);
      instance.SetStreamerFunc(&streamer_FairFileSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairFileSource*)
   {
      return GenerateInitInstanceLocal((::FairFileSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairFileSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairMixedSource(void *p);
   static void deleteArray_FairMixedSource(void *p);
   static void destruct_FairMixedSource(void *p);
   static void streamer_FairMixedSource(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMixedSource*)
   {
      ::FairMixedSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMixedSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMixedSource", ::FairMixedSource::Class_Version(), "invalid", 7133,
                  typeid(::FairMixedSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMixedSource::Dictionary, isa_proxy, 16,
                  sizeof(::FairMixedSource) );
      instance.SetDelete(&delete_FairMixedSource);
      instance.SetDeleteArray(&deleteArray_FairMixedSource);
      instance.SetDestructor(&destruct_FairMixedSource);
      instance.SetStreamerFunc(&streamer_FairMixedSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMixedSource*)
   {
      return GenerateInitInstanceLocal((::FairMixedSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMixedSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairOnlineSource(void *p);
   static void deleteArray_FairOnlineSource(void *p);
   static void destruct_FairOnlineSource(void *p);
   static void streamer_FairOnlineSource(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairOnlineSource*)
   {
      ::FairOnlineSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairOnlineSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairOnlineSource", ::FairOnlineSource::Class_Version(), "invalid", 7352,
                  typeid(::FairOnlineSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairOnlineSource::Dictionary, isa_proxy, 16,
                  sizeof(::FairOnlineSource) );
      instance.SetDelete(&delete_FairOnlineSource);
      instance.SetDeleteArray(&deleteArray_FairOnlineSource);
      instance.SetDestructor(&destruct_FairOnlineSource);
      instance.SetStreamerFunc(&streamer_FairOnlineSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairOnlineSource*)
   {
      return GenerateInitInstanceLocal((::FairOnlineSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairOnlineSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairMbsSource(void *p);
   static void deleteArray_FairMbsSource(void *p);
   static void destruct_FairMbsSource(void *p);
   static void streamer_FairMbsSource(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMbsSource*)
   {
      ::FairMbsSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMbsSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMbsSource", ::FairMbsSource::Class_Version(), "FairMbsSource.h", 25,
                  typeid(::FairMbsSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMbsSource::Dictionary, isa_proxy, 16,
                  sizeof(::FairMbsSource) );
      instance.SetDelete(&delete_FairMbsSource);
      instance.SetDeleteArray(&deleteArray_FairMbsSource);
      instance.SetDestructor(&destruct_FairMbsSource);
      instance.SetStreamerFunc(&streamer_FairMbsSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMbsSource*)
   {
      return GenerateInitInstanceLocal((::FairMbsSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMbsSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairRemoteSource(void *p);
   static void deleteArray_FairRemoteSource(void *p);
   static void destruct_FairRemoteSource(void *p);
   static void streamer_FairRemoteSource(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairRemoteSource*)
   {
      ::FairRemoteSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairRemoteSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairRemoteSource", ::FairRemoteSource::Class_Version(), "invalid", 7479,
                  typeid(::FairRemoteSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairRemoteSource::Dictionary, isa_proxy, 16,
                  sizeof(::FairRemoteSource) );
      instance.SetDelete(&delete_FairRemoteSource);
      instance.SetDeleteArray(&deleteArray_FairRemoteSource);
      instance.SetDestructor(&destruct_FairRemoteSource);
      instance.SetStreamerFunc(&streamer_FairRemoteSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairRemoteSource*)
   {
      return GenerateInitInstanceLocal((::FairRemoteSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairRemoteSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairMbsStreamSource(void *p);
   static void deleteArray_FairMbsStreamSource(void *p);
   static void destruct_FairMbsStreamSource(void *p);
   static void streamer_FairMbsStreamSource(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMbsStreamSource*)
   {
      ::FairMbsStreamSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMbsStreamSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMbsStreamSource", ::FairMbsStreamSource::Class_Version(), "invalid", 7778,
                  typeid(::FairMbsStreamSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMbsStreamSource::Dictionary, isa_proxy, 16,
                  sizeof(::FairMbsStreamSource) );
      instance.SetDelete(&delete_FairMbsStreamSource);
      instance.SetDeleteArray(&deleteArray_FairMbsStreamSource);
      instance.SetDestructor(&destruct_FairMbsStreamSource);
      instance.SetStreamerFunc(&streamer_FairMbsStreamSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMbsStreamSource*)
   {
      return GenerateInitInstanceLocal((::FairMbsStreamSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMbsStreamSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairLmdSource(void *p = 0);
   static void *newArray_FairLmdSource(Long_t size, void *p);
   static void delete_FairLmdSource(void *p);
   static void deleteArray_FairLmdSource(void *p);
   static void destruct_FairLmdSource(void *p);
   static void streamer_FairLmdSource(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairLmdSource*)
   {
      ::FairLmdSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairLmdSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairLmdSource", ::FairLmdSource::Class_Version(), "invalid", 7417,
                  typeid(::FairLmdSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairLmdSource::Dictionary, isa_proxy, 16,
                  sizeof(::FairLmdSource) );
      instance.SetNew(&new_FairLmdSource);
      instance.SetNewArray(&newArray_FairLmdSource);
      instance.SetDelete(&delete_FairLmdSource);
      instance.SetDeleteArray(&deleteArray_FairLmdSource);
      instance.SetDestructor(&destruct_FairLmdSource);
      instance.SetStreamerFunc(&streamer_FairLmdSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairLmdSource*)
   {
      return GenerateInitInstanceLocal((::FairLmdSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairLmdSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairUnpack(void *p);
   static void deleteArray_FairUnpack(void *p);
   static void destruct_FairUnpack(void *p);
   static void streamer_FairUnpack(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairUnpack*)
   {
      ::FairUnpack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairUnpack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairUnpack", ::FairUnpack::Class_Version(), "FairUnpack.h", 21,
                  typeid(::FairUnpack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairUnpack::Dictionary, isa_proxy, 16,
                  sizeof(::FairUnpack) );
      instance.SetDelete(&delete_FairUnpack);
      instance.SetDeleteArray(&deleteArray_FairUnpack);
      instance.SetDestructor(&destruct_FairUnpack);
      instance.SetStreamerFunc(&streamer_FairUnpack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairUnpack*)
   {
      return GenerateInitInstanceLocal((::FairUnpack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairUnpack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_MRevBuffer(void *p);
   static void deleteArray_MRevBuffer(void *p);
   static void destruct_MRevBuffer(void *p);
   static void streamer_MRevBuffer(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MRevBuffer*)
   {
      ::MRevBuffer *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MRevBuffer >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MRevBuffer", ::MRevBuffer::Class_Version(), "invalid", 7680,
                  typeid(::MRevBuffer), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MRevBuffer::Dictionary, isa_proxy, 16,
                  sizeof(::MRevBuffer) );
      instance.SetDelete(&delete_MRevBuffer);
      instance.SetDeleteArray(&deleteArray_MRevBuffer);
      instance.SetDestructor(&destruct_MRevBuffer);
      instance.SetStreamerFunc(&streamer_MRevBuffer);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MRevBuffer*)
   {
      return GenerateInitInstanceLocal((::MRevBuffer*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MRevBuffer*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_REvent(void *p = 0);
   static void *newArray_REvent(Long_t size, void *p);
   static void delete_REvent(void *p);
   static void deleteArray_REvent(void *p);
   static void destruct_REvent(void *p);
   static void streamer_REvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::REvent*)
   {
      ::REvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::REvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("REvent", ::REvent::Class_Version(), "invalid", 7644,
                  typeid(::REvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::REvent::Dictionary, isa_proxy, 16,
                  sizeof(::REvent) );
      instance.SetNew(&new_REvent);
      instance.SetNewArray(&newArray_REvent);
      instance.SetDelete(&delete_REvent);
      instance.SetDeleteArray(&deleteArray_REvent);
      instance.SetDestructor(&destruct_REvent);
      instance.SetStreamerFunc(&streamer_REvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::REvent*)
   {
      return GenerateInitInstanceLocal((::REvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::REvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairBaseContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairBaseContFact::Class_Name()
{
   return "FairBaseContFact";
}

//______________________________________________________________________________
const char *FairBaseContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBaseContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairBaseContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBaseContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairBaseContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBaseContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairBaseContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBaseContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairBaseParSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairBaseParSet::Class_Name()
{
   return "FairBaseParSet";
}

//______________________________________________________________________________
const char *FairBaseParSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBaseParSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairBaseParSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairBaseParSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairBaseParSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBaseParSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairBaseParSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairBaseParSet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoParSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoParSet::Class_Name()
{
   return "FairGeoParSet";
}

//______________________________________________________________________________
const char *FairGeoParSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoParSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoParSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoParSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoParSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoParSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoParSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoParSet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairDetector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairDetector::Class_Name()
{
   return "FairDetector";
}

//______________________________________________________________________________
const char *FairDetector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairDetector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairDetector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairDetector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairDetector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairDetector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairDetector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairDetector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairEventBuilder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairEventBuilder::Class_Name()
{
   return "FairEventBuilder";
}

//______________________________________________________________________________
const char *FairEventBuilder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventBuilder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairEventBuilder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventBuilder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairEventBuilder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventBuilder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairEventBuilder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventBuilder*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairEventBuilderManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairEventBuilderManager::Class_Name()
{
   return "FairEventBuilderManager";
}

//______________________________________________________________________________
const char *FairEventBuilderManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventBuilderManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairEventBuilderManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventBuilderManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairEventBuilderManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventBuilderManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairEventBuilderManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventBuilderManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairEventHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairEventHeader::Class_Name()
{
   return "FairEventHeader";
}

//______________________________________________________________________________
const char *FairEventHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairEventHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairEventHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairEventHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairEventHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairEventHeader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairFileHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairFileHeader::Class_Name()
{
   return "FairFileHeader";
}

//______________________________________________________________________________
const char *FairFileHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFileHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairFileHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFileHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairFileHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFileHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairFileHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFileHeader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeaneApplication::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeaneApplication::Class_Name()
{
   return "FairGeaneApplication";
}

//______________________________________________________________________________
const char *FairGeaneApplication::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeaneApplication*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeaneApplication::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeaneApplication*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeaneApplication::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeaneApplication*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeaneApplication::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeaneApplication*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGenerator::Class_Name()
{
   return "FairGenerator";
}

//______________________________________________________________________________
const char *FairGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairLink::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairLink::Class_Name()
{
   return "FairLink";
}

//______________________________________________________________________________
const char *FairLink::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLink*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairLink::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLink*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairLink::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLink*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairLink::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLink*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMultiLinkedData::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMultiLinkedData::Class_Name()
{
   return "FairMultiLinkedData";
}

//______________________________________________________________________________
const char *FairMultiLinkedData::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMultiLinkedData*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMultiLinkedData::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMultiLinkedData*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMultiLinkedData::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMultiLinkedData*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMultiLinkedData::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMultiLinkedData*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMultiLinkedData_Interface::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMultiLinkedData_Interface::Class_Name()
{
   return "FairMultiLinkedData_Interface";
}

//______________________________________________________________________________
const char *FairMultiLinkedData_Interface::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMultiLinkedData_Interface*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMultiLinkedData_Interface::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMultiLinkedData_Interface*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMultiLinkedData_Interface::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMultiLinkedData_Interface*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMultiLinkedData_Interface::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMultiLinkedData_Interface*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairHit::Class_Name()
{
   return "FairHit";
}

//______________________________________________________________________________
const char *FairHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairIon::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairIon::Class_Name()
{
   return "FairIon";
}

//______________________________________________________________________________
const char *FairIon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairIon*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairIon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairIon*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairIon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairIon*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairIon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairIon*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCApplication::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCApplication::Class_Name()
{
   return "FairMCApplication";
}

//______________________________________________________________________________
const char *FairMCApplication::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCApplication*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCApplication::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCApplication*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCApplication::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCApplication*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCApplication::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCApplication*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCEventHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCEventHeader::Class_Name()
{
   return "FairMCEventHeader";
}

//______________________________________________________________________________
const char *FairMCEventHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCEventHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCEventHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCEventHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCEventHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCEventHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCEventHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCEventHeader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCPoint::Class_Name()
{
   return "FairMCPoint";
}

//______________________________________________________________________________
const char *FairMCPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairModule::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairModule::Class_Name()
{
   return "FairModule";
}

//______________________________________________________________________________
const char *FairModule::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairModule*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairModule::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairModule*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairModule::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairModule*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairModule::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairModule*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairParticle::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairParticle::Class_Name()
{
   return "FairParticle";
}

//______________________________________________________________________________
const char *FairParticle::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParticle*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairParticle::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairParticle*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairParticle::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParticle*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairParticle::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairParticle*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairPrimaryGenerator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairPrimaryGenerator::Class_Name()
{
   return "FairPrimaryGenerator";
}

//______________________________________________________________________________
const char *FairPrimaryGenerator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairPrimaryGenerator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairPrimaryGenerator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairPrimaryGenerator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairPrimaryGenerator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairPrimaryGenerator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairPrimaryGenerator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairPrimaryGenerator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRecoEventHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRecoEventHeader::Class_Name()
{
   return "FairRecoEventHeader";
}

//______________________________________________________________________________
const char *FairRecoEventHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRecoEventHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRecoEventHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRecoEventHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRecoEventHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRecoEventHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRecoEventHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRecoEventHeader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRootManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRootManager::Class_Name()
{
   return "FairRootManager";
}

//______________________________________________________________________________
const char *FairRootManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRootManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRootManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRootManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRootManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRootManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRootManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRootManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRun::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRun::Class_Name()
{
   return "FairRun";
}

//______________________________________________________________________________
const char *FairRun::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRun*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRun::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRun*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRun::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRun*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRun::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRun*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRunAna::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRunAna::Class_Name()
{
   return "FairRunAna";
}

//______________________________________________________________________________
const char *FairRunAna::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunAna*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRunAna::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunAna*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRunAna::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunAna*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRunAna::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunAna*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRunAnaProof::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRunAnaProof::Class_Name()
{
   return "FairRunAnaProof";
}

//______________________________________________________________________________
const char *FairRunAnaProof::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunAnaProof*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRunAnaProof::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunAnaProof*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRunAnaProof::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunAnaProof*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRunAnaProof::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunAnaProof*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRunSim::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRunSim::Class_Name()
{
   return "FairRunSim";
}

//______________________________________________________________________________
const char *FairRunSim::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunSim*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRunSim::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunSim*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRunSim::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunSim*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRunSim::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunSim*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTrackParam::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTrackParam::Class_Name()
{
   return "FairTrackParam";
}

//______________________________________________________________________________
const char *FairTrackParam::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParam*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTrackParam::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParam*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTrackParam::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParam*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTrackParam::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrackParam*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTrajFilter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTrajFilter::Class_Name()
{
   return "FairTrajFilter";
}

//______________________________________________________________________________
const char *FairTrajFilter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrajFilter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTrajFilter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTrajFilter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTrajFilter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrajFilter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTrajFilter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTrajFilter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairVolume::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairVolume::Class_Name()
{
   return "FairVolume";
}

//______________________________________________________________________________
const char *FairVolume::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairVolume*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairVolume::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairVolume*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairVolume::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairVolume*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairVolume::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairVolume*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairVolumeList::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairVolumeList::Class_Name()
{
   return "FairVolumeList";
}

//______________________________________________________________________________
const char *FairVolumeList::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairVolumeList*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairVolumeList::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairVolumeList*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairVolumeList::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairVolumeList*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairVolumeList::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairVolumeList*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairField::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairField::Class_Name()
{
   return "FairField";
}

//______________________________________________________________________________
const char *FairField::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairField*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairField::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairField*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairField::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairField*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairField::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairField*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGenericStack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGenericStack::Class_Name()
{
   return "FairGenericStack";
}

//______________________________________________________________________________
const char *FairGenericStack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGenericStack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGenericStack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGenericStack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGenericStack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGenericStack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGenericStack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGenericStack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTask::Class_Name()
{
   return "FairTask";
}

//______________________________________________________________________________
const char *FairTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairFieldFactory::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairFieldFactory::Class_Name()
{
   return "FairFieldFactory";
}

//______________________________________________________________________________
const char *FairFieldFactory::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFieldFactory*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairFieldFactory::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFieldFactory*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairFieldFactory::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFieldFactory*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairFieldFactory::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFieldFactory*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRadLenPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRadLenPoint::Class_Name()
{
   return "FairRadLenPoint";
}

//______________________________________________________________________________
const char *FairRadLenPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadLenPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRadLenPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadLenPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRadLenPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadLenPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRadLenPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadLenPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRadLenManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRadLenManager::Class_Name()
{
   return "FairRadLenManager";
}

//______________________________________________________________________________
const char *FairRadLenManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadLenManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRadLenManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadLenManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRadLenManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadLenManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRadLenManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadLenManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRadGridManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRadGridManager::Class_Name()
{
   return "FairRadGridManager";
}

//______________________________________________________________________________
const char *FairRadGridManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadGridManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRadGridManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadGridManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRadGridManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadGridManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRadGridManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadGridManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRadMapManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRadMapManager::Class_Name()
{
   return "FairRadMapManager";
}

//______________________________________________________________________________
const char *FairRadMapManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadMapManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRadMapManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadMapManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRadMapManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadMapManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRadMapManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadMapManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMesh::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMesh::Class_Name()
{
   return "FairMesh";
}

//______________________________________________________________________________
const char *FairMesh::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMesh*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMesh::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMesh*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMesh::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMesh*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMesh::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMesh*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRKPropagator::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRKPropagator::Class_Name()
{
   return "FairRKPropagator";
}

//______________________________________________________________________________
const char *FairRKPropagator::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRKPropagator*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRKPropagator::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRKPropagator*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRKPropagator::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRKPropagator*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRKPropagator::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRKPropagator*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTimeStamp::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTimeStamp::Class_Name()
{
   return "FairTimeStamp";
}

//______________________________________________________________________________
const char *FairTimeStamp::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTimeStamp*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTimeStamp::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTimeStamp*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTimeStamp::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTimeStamp*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTimeStamp::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTimeStamp*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRadMapPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRadMapPoint::Class_Name()
{
   return "FairRadMapPoint";
}

//______________________________________________________________________________
const char *FairRadMapPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadMapPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRadMapPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRadMapPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRadMapPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadMapPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRadMapPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRadMapPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTSBufferFunctional::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTSBufferFunctional::Class_Name()
{
   return "FairTSBufferFunctional";
}

//______________________________________________________________________________
const char *FairTSBufferFunctional::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTSBufferFunctional*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTSBufferFunctional::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTSBufferFunctional*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTSBufferFunctional::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTSBufferFunctional*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTSBufferFunctional::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTSBufferFunctional*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairFileInfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairFileInfo::Class_Name()
{
   return "FairFileInfo";
}

//______________________________________________________________________________
const char *FairFileInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFileInfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairFileInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFileInfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairFileInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFileInfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairFileInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFileInfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRunInfo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRunInfo::Class_Name()
{
   return "FairRunInfo";
}

//______________________________________________________________________________
const char *FairRunInfo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunInfo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRunInfo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunInfo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRunInfo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunInfo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRunInfo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunInfo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairWriteoutBuffer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairWriteoutBuffer::Class_Name()
{
   return "FairWriteoutBuffer";
}

//______________________________________________________________________________
const char *FairWriteoutBuffer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairWriteoutBuffer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairWriteoutBuffer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairWriteoutBuffer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairWriteoutBuffer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairWriteoutBuffer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairWriteoutBuffer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairWriteoutBuffer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRingSorter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRingSorter::Class_Name()
{
   return "FairRingSorter";
}

//______________________________________________________________________________
const char *FairRingSorter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRingSorter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRingSorter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRingSorter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRingSorter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRingSorter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRingSorter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRingSorter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRingSorterTask::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRingSorterTask::Class_Name()
{
   return "FairRingSorterTask";
}

//______________________________________________________________________________
const char *FairRingSorterTask::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRingSorterTask*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRingSorterTask::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRingSorterTask*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRingSorterTask::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRingSorterTask*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRingSorterTask::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRingSorterTask*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairAnaSelector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairAnaSelector::Class_Name()
{
   return "FairAnaSelector";
}

//______________________________________________________________________________
const char *FairAnaSelector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairAnaSelector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairAnaSelector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairAnaSelector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairAnaSelector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairAnaSelector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairAnaSelector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairAnaSelector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairLinkManager::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairLinkManager::Class_Name()
{
   return "FairLinkManager";
}

//______________________________________________________________________________
const char *FairLinkManager::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLinkManager*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairLinkManager::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLinkManager*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairLinkManager::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLinkManager*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairLinkManager::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLinkManager*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRunOnline::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRunOnline::Class_Name()
{
   return "FairRunOnline";
}

//______________________________________________________________________________
const char *FairRunOnline::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunOnline*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRunOnline::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRunOnline*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRunOnline::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunOnline*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRunOnline::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRunOnline*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairSource::Class_Name()
{
   return "FairSource";
}

//______________________________________________________________________________
const char *FairSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairFileSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairFileSource::Class_Name()
{
   return "FairFileSource";
}

//______________________________________________________________________________
const char *FairFileSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFileSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairFileSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairFileSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairFileSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFileSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairFileSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairFileSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMixedSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMixedSource::Class_Name()
{
   return "FairMixedSource";
}

//______________________________________________________________________________
const char *FairMixedSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMixedSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMixedSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMixedSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMixedSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMixedSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMixedSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMixedSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairOnlineSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairOnlineSource::Class_Name()
{
   return "FairOnlineSource";
}

//______________________________________________________________________________
const char *FairOnlineSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairOnlineSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairOnlineSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairOnlineSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairOnlineSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairOnlineSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairOnlineSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairOnlineSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMbsSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMbsSource::Class_Name()
{
   return "FairMbsSource";
}

//______________________________________________________________________________
const char *FairMbsSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMbsSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMbsSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMbsSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMbsSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMbsSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMbsSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMbsSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairRemoteSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairRemoteSource::Class_Name()
{
   return "FairRemoteSource";
}

//______________________________________________________________________________
const char *FairRemoteSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRemoteSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairRemoteSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairRemoteSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairRemoteSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRemoteSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairRemoteSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairRemoteSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMbsStreamSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMbsStreamSource::Class_Name()
{
   return "FairMbsStreamSource";
}

//______________________________________________________________________________
const char *FairMbsStreamSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMbsStreamSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMbsStreamSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMbsStreamSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMbsStreamSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMbsStreamSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMbsStreamSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMbsStreamSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairLmdSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairLmdSource::Class_Name()
{
   return "FairLmdSource";
}

//______________________________________________________________________________
const char *FairLmdSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLmdSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairLmdSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairLmdSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairLmdSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLmdSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairLmdSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairLmdSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairUnpack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairUnpack::Class_Name()
{
   return "FairUnpack";
}

//______________________________________________________________________________
const char *FairUnpack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairUnpack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairUnpack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairUnpack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairUnpack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairUnpack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairUnpack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairUnpack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MRevBuffer::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MRevBuffer::Class_Name()
{
   return "MRevBuffer";
}

//______________________________________________________________________________
const char *MRevBuffer::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MRevBuffer*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MRevBuffer::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MRevBuffer*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MRevBuffer::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MRevBuffer*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MRevBuffer::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MRevBuffer*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr REvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *REvent::Class_Name()
{
   return "REvent";
}

//______________________________________________________________________________
const char *REvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::REvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int REvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::REvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *REvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::REvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *REvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::REvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairBaseContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairBaseContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairBaseContFact(void *p) {
      return  p ? new(p) ::FairBaseContFact : new ::FairBaseContFact;
   }
   static void *newArray_FairBaseContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairBaseContFact[nElements] : new ::FairBaseContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairBaseContFact(void *p) {
      delete ((::FairBaseContFact*)p);
   }
   static void deleteArray_FairBaseContFact(void *p) {
      delete [] ((::FairBaseContFact*)p);
   }
   static void destruct_FairBaseContFact(void *p) {
      typedef ::FairBaseContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairBaseContFact(TBuffer &buf, void *obj) {
      ((::FairBaseContFact*)obj)->::FairBaseContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairBaseContFact

//______________________________________________________________________________
void FairBaseParSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairBaseParSet.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fDetList;
      R__b >> fPriGen;
      R__b >> fBeamMom;
      R__b >> fContNameList;
      R__b >> fRandomSeed;
      R__b.CheckByteCount(R__s, R__c, FairBaseParSet::IsA());
   } else {
      R__c = R__b.WriteVersion(FairBaseParSet::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fDetList;
      R__b << fPriGen;
      R__b << fBeamMom;
      R__b << fContNameList;
      R__b << fRandomSeed;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairBaseParSet(void *p) {
      return  p ? new(p) ::FairBaseParSet : new ::FairBaseParSet;
   }
   static void *newArray_FairBaseParSet(Long_t nElements, void *p) {
      return p ? new(p) ::FairBaseParSet[nElements] : new ::FairBaseParSet[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairBaseParSet(void *p) {
      delete ((::FairBaseParSet*)p);
   }
   static void deleteArray_FairBaseParSet(void *p) {
      delete [] ((::FairBaseParSet*)p);
   }
   static void destruct_FairBaseParSet(void *p) {
      typedef ::FairBaseParSet current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairBaseParSet(TBuffer &buf, void *obj) {
      ((::FairBaseParSet*)obj)->::FairBaseParSet::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairBaseParSet

//______________________________________________________________________________
void FairGeoParSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoParSet.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeom;
      R__b.CheckByteCount(R__s, R__c, FairGeoParSet::IsA());
   } else {
      R__c = R__b.WriteVersion(FairGeoParSet::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeom;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoParSet(void *p) {
      return  p ? new(p) ::FairGeoParSet : new ::FairGeoParSet;
   }
   static void *newArray_FairGeoParSet(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoParSet[nElements] : new ::FairGeoParSet[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoParSet(void *p) {
      delete ((::FairGeoParSet*)p);
   }
   static void deleteArray_FairGeoParSet(void *p) {
      delete [] ((::FairGeoParSet*)p);
   }
   static void destruct_FairGeoParSet(void *p) {
      typedef ::FairGeoParSet current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoParSet(TBuffer &buf, void *obj) {
      ((::FairGeoParSet*)obj)->::FairGeoParSet::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoParSet

//______________________________________________________________________________
void FairDetector::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairDetector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairDetector::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairDetector::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairDetector(void *p) {
      delete ((::FairDetector*)p);
   }
   static void deleteArray_FairDetector(void *p) {
      delete [] ((::FairDetector*)p);
   }
   static void destruct_FairDetector(void *p) {
      typedef ::FairDetector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairDetector

//______________________________________________________________________________
void FairEventBuilder::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairEventBuilder.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairEventBuilder::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairEventBuilder::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairEventBuilder(void *p) {
      delete ((::FairEventBuilder*)p);
   }
   static void deleteArray_FairEventBuilder(void *p) {
      delete [] ((::FairEventBuilder*)p);
   }
   static void destruct_FairEventBuilder(void *p) {
      typedef ::FairEventBuilder current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairEventBuilder

//______________________________________________________________________________
void FairEventBuilderManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairEventBuilderManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairEventBuilderManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairEventBuilderManager::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairEventBuilderManager(void *p) {
      delete ((::FairEventBuilderManager*)p);
   }
   static void deleteArray_FairEventBuilderManager(void *p) {
      delete [] ((::FairEventBuilderManager*)p);
   }
   static void destruct_FairEventBuilderManager(void *p) {
      typedef ::FairEventBuilderManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairEventBuilderManager

//______________________________________________________________________________
void FairEventHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairEventHeader.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> fRunId;
      R__b >> fEventTime;
      R__b >> fInputFileId;
      R__b >> fMCEntryNo;
      R__b.CheckByteCount(R__s, R__c, FairEventHeader::IsA());
   } else {
      R__c = R__b.WriteVersion(FairEventHeader::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << fRunId;
      R__b << fEventTime;
      R__b << fInputFileId;
      R__b << fMCEntryNo;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairEventHeader(void *p) {
      return  p ? new(p) ::FairEventHeader : new ::FairEventHeader;
   }
   static void *newArray_FairEventHeader(Long_t nElements, void *p) {
      return p ? new(p) ::FairEventHeader[nElements] : new ::FairEventHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairEventHeader(void *p) {
      delete ((::FairEventHeader*)p);
   }
   static void deleteArray_FairEventHeader(void *p) {
      delete [] ((::FairEventHeader*)p);
   }
   static void destruct_FairEventHeader(void *p) {
      typedef ::FairEventHeader current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairEventHeader(TBuffer &buf, void *obj) {
      ((::FairEventHeader*)obj)->::FairEventHeader::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairEventHeader

//______________________________________________________________________________
void FairFileHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairFileHeader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairFileHeader::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairFileHeader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairFileHeader(void *p) {
      return  p ? new(p) ::FairFileHeader : new ::FairFileHeader;
   }
   static void *newArray_FairFileHeader(Long_t nElements, void *p) {
      return p ? new(p) ::FairFileHeader[nElements] : new ::FairFileHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairFileHeader(void *p) {
      delete ((::FairFileHeader*)p);
   }
   static void deleteArray_FairFileHeader(void *p) {
      delete [] ((::FairFileHeader*)p);
   }
   static void destruct_FairFileHeader(void *p) {
      typedef ::FairFileHeader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairFileHeader

//______________________________________________________________________________
void FairGeaneApplication::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeaneApplication.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGeaneApplication::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGeaneApplication::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeaneApplication(void *p) {
      return  p ? new(p) ::FairGeaneApplication : new ::FairGeaneApplication;
   }
   static void *newArray_FairGeaneApplication(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeaneApplication[nElements] : new ::FairGeaneApplication[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeaneApplication(void *p) {
      delete ((::FairGeaneApplication*)p);
   }
   static void deleteArray_FairGeaneApplication(void *p) {
      delete [] ((::FairGeaneApplication*)p);
   }
   static void destruct_FairGeaneApplication(void *p) {
      typedef ::FairGeaneApplication current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGeaneApplication

//______________________________________________________________________________
void FairGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairGenerator(void *p) {
      delete ((::FairGenerator*)p);
   }
   static void deleteArray_FairGenerator(void *p) {
      delete [] ((::FairGenerator*)p);
   }
   static void destruct_FairGenerator(void *p) {
      typedef ::FairGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGenerator

//______________________________________________________________________________
void FairLink::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairLink.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairLink::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairLink::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairLink(void *p) {
      return  p ? new(p) ::FairLink : new ::FairLink;
   }
   static void *newArray_FairLink(Long_t nElements, void *p) {
      return p ? new(p) ::FairLink[nElements] : new ::FairLink[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairLink(void *p) {
      delete ((::FairLink*)p);
   }
   static void deleteArray_FairLink(void *p) {
      delete [] ((::FairLink*)p);
   }
   static void destruct_FairLink(void *p) {
      typedef ::FairLink current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairLink

//______________________________________________________________________________
void FairMultiLinkedData::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMultiLinkedData.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMultiLinkedData::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMultiLinkedData::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMultiLinkedData(void *p) {
      return  p ? new(p) ::FairMultiLinkedData : new ::FairMultiLinkedData;
   }
   static void *newArray_FairMultiLinkedData(Long_t nElements, void *p) {
      return p ? new(p) ::FairMultiLinkedData[nElements] : new ::FairMultiLinkedData[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMultiLinkedData(void *p) {
      delete ((::FairMultiLinkedData*)p);
   }
   static void deleteArray_FairMultiLinkedData(void *p) {
      delete [] ((::FairMultiLinkedData*)p);
   }
   static void destruct_FairMultiLinkedData(void *p) {
      typedef ::FairMultiLinkedData current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMultiLinkedData

//______________________________________________________________________________
void FairMultiLinkedData_Interface::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMultiLinkedData_Interface.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMultiLinkedData_Interface::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMultiLinkedData_Interface::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMultiLinkedData_Interface(void *p) {
      return  p ? new(p) ::FairMultiLinkedData_Interface : new ::FairMultiLinkedData_Interface;
   }
   static void *newArray_FairMultiLinkedData_Interface(Long_t nElements, void *p) {
      return p ? new(p) ::FairMultiLinkedData_Interface[nElements] : new ::FairMultiLinkedData_Interface[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMultiLinkedData_Interface(void *p) {
      delete ((::FairMultiLinkedData_Interface*)p);
   }
   static void deleteArray_FairMultiLinkedData_Interface(void *p) {
      delete [] ((::FairMultiLinkedData_Interface*)p);
   }
   static void destruct_FairMultiLinkedData_Interface(void *p) {
      typedef ::FairMultiLinkedData_Interface current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMultiLinkedData_Interface

//______________________________________________________________________________
void FairHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairHit(void *p) {
      return  p ? new(p) ::FairHit : new ::FairHit;
   }
   static void *newArray_FairHit(Long_t nElements, void *p) {
      return p ? new(p) ::FairHit[nElements] : new ::FairHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairHit(void *p) {
      delete ((::FairHit*)p);
   }
   static void deleteArray_FairHit(void *p) {
      delete [] ((::FairHit*)p);
   }
   static void destruct_FairHit(void *p) {
      typedef ::FairHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairHit

//______________________________________________________________________________
void FairIon::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairIon.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairIon::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairIon::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairIon(void *p) {
      return  p ? new(p) ::FairIon : new ::FairIon;
   }
   static void *newArray_FairIon(Long_t nElements, void *p) {
      return p ? new(p) ::FairIon[nElements] : new ::FairIon[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairIon(void *p) {
      delete ((::FairIon*)p);
   }
   static void deleteArray_FairIon(void *p) {
      delete [] ((::FairIon*)p);
   }
   static void destruct_FairIon(void *p) {
      typedef ::FairIon current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairIon

//______________________________________________________________________________
void FairMCApplication::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCApplication.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCApplication::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCApplication::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCApplication(void *p) {
      return  p ? new(p) ::FairMCApplication : new ::FairMCApplication;
   }
   static void *newArray_FairMCApplication(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCApplication[nElements] : new ::FairMCApplication[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCApplication(void *p) {
      delete ((::FairMCApplication*)p);
   }
   static void deleteArray_FairMCApplication(void *p) {
      delete [] ((::FairMCApplication*)p);
   }
   static void destruct_FairMCApplication(void *p) {
      typedef ::FairMCApplication current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCApplication

//______________________________________________________________________________
void FairMCEventHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCEventHeader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCEventHeader::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCEventHeader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCEventHeader(void *p) {
      return  p ? new(p) ::FairMCEventHeader : new ::FairMCEventHeader;
   }
   static void *newArray_FairMCEventHeader(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCEventHeader[nElements] : new ::FairMCEventHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCEventHeader(void *p) {
      delete ((::FairMCEventHeader*)p);
   }
   static void deleteArray_FairMCEventHeader(void *p) {
      delete [] ((::FairMCEventHeader*)p);
   }
   static void destruct_FairMCEventHeader(void *p) {
      typedef ::FairMCEventHeader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCEventHeader

//______________________________________________________________________________
void FairMCPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCPoint(void *p) {
      return  p ? new(p) ::FairMCPoint : new ::FairMCPoint;
   }
   static void *newArray_FairMCPoint(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCPoint[nElements] : new ::FairMCPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCPoint(void *p) {
      delete ((::FairMCPoint*)p);
   }
   static void deleteArray_FairMCPoint(void *p) {
      delete [] ((::FairMCPoint*)p);
   }
   static void destruct_FairMCPoint(void *p) {
      typedef ::FairMCPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCPoint

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairModule(void *p) {
      return  p ? new(p) ::FairModule : new ::FairModule;
   }
   static void *newArray_FairModule(Long_t nElements, void *p) {
      return p ? new(p) ::FairModule[nElements] : new ::FairModule[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairModule(void *p) {
      delete ((::FairModule*)p);
   }
   static void deleteArray_FairModule(void *p) {
      delete [] ((::FairModule*)p);
   }
   static void destruct_FairModule(void *p) {
      typedef ::FairModule current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairModule(TBuffer &buf, void *obj) {
      ((::FairModule*)obj)->::FairModule::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairModule

//______________________________________________________________________________
void FairParticle::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairParticle.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairParticle::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairParticle::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairParticle(void *p) {
      return  p ? new(p) ::FairParticle : new ::FairParticle;
   }
   static void *newArray_FairParticle(Long_t nElements, void *p) {
      return p ? new(p) ::FairParticle[nElements] : new ::FairParticle[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairParticle(void *p) {
      delete ((::FairParticle*)p);
   }
   static void deleteArray_FairParticle(void *p) {
      delete [] ((::FairParticle*)p);
   }
   static void destruct_FairParticle(void *p) {
      typedef ::FairParticle current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairParticle

//______________________________________________________________________________
void FairPrimaryGenerator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairPrimaryGenerator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairPrimaryGenerator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairPrimaryGenerator::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairPrimaryGenerator(void *p) {
      return  p ? new(p) ::FairPrimaryGenerator : new ::FairPrimaryGenerator;
   }
   static void *newArray_FairPrimaryGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairPrimaryGenerator[nElements] : new ::FairPrimaryGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairPrimaryGenerator(void *p) {
      delete ((::FairPrimaryGenerator*)p);
   }
   static void deleteArray_FairPrimaryGenerator(void *p) {
      delete [] ((::FairPrimaryGenerator*)p);
   }
   static void destruct_FairPrimaryGenerator(void *p) {
      typedef ::FairPrimaryGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairPrimaryGenerator

//______________________________________________________________________________
void FairRecoEventHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRecoEventHeader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRecoEventHeader::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRecoEventHeader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRecoEventHeader(void *p) {
      return  p ? new(p) ::FairRecoEventHeader : new ::FairRecoEventHeader;
   }
   static void *newArray_FairRecoEventHeader(Long_t nElements, void *p) {
      return p ? new(p) ::FairRecoEventHeader[nElements] : new ::FairRecoEventHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRecoEventHeader(void *p) {
      delete ((::FairRecoEventHeader*)p);
   }
   static void deleteArray_FairRecoEventHeader(void *p) {
      delete [] ((::FairRecoEventHeader*)p);
   }
   static void destruct_FairRecoEventHeader(void *p) {
      typedef ::FairRecoEventHeader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRecoEventHeader

//______________________________________________________________________________
void FairRootManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRootManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRootManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRootManager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRootManager(void *p) {
      return  p ? new(p) ::FairRootManager : new ::FairRootManager;
   }
   static void *newArray_FairRootManager(Long_t nElements, void *p) {
      return p ? new(p) ::FairRootManager[nElements] : new ::FairRootManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRootManager(void *p) {
      delete ((::FairRootManager*)p);
   }
   static void deleteArray_FairRootManager(void *p) {
      delete [] ((::FairRootManager*)p);
   }
   static void destruct_FairRootManager(void *p) {
      typedef ::FairRootManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRootManager

//______________________________________________________________________________
void FairRun::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRun.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRun::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRun::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairRun(void *p) {
      delete ((::FairRun*)p);
   }
   static void deleteArray_FairRun(void *p) {
      delete [] ((::FairRun*)p);
   }
   static void destruct_FairRun(void *p) {
      typedef ::FairRun current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRun

//______________________________________________________________________________
void FairRunAna::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRunAna.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairRun::Streamer(R__b);
      R__b >> fIsInitialized;
      R__b >> fInputGeoFile;
      R__b >> fLoadGeo;
      R__b >> fField;
      R__b >> fTimeStamps;
      R__b.CheckByteCount(R__s, R__c, FairRunAna::IsA());
   } else {
      R__c = R__b.WriteVersion(FairRunAna::IsA(), kTRUE);
      FairRun::Streamer(R__b);
      R__b << fIsInitialized;
      R__b << fInputGeoFile;
      R__b << fLoadGeo;
      R__b << fField;
      R__b << fTimeStamps;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRunAna(void *p) {
      return  p ? new(p) ::FairRunAna : new ::FairRunAna;
   }
   static void *newArray_FairRunAna(Long_t nElements, void *p) {
      return p ? new(p) ::FairRunAna[nElements] : new ::FairRunAna[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRunAna(void *p) {
      delete ((::FairRunAna*)p);
   }
   static void deleteArray_FairRunAna(void *p) {
      delete [] ((::FairRunAna*)p);
   }
   static void destruct_FairRunAna(void *p) {
      typedef ::FairRunAna current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRunAna(TBuffer &buf, void *obj) {
      ((::FairRunAna*)obj)->::FairRunAna::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRunAna

//______________________________________________________________________________
void FairRunAnaProof::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRunAnaProof.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairRunAna::Streamer(R__b);
      R__b >> fProof;
      fProofOutputStatus.Streamer(R__b);
      R__b >> fProofFileSource;
      R__b.CheckByteCount(R__s, R__c, FairRunAnaProof::IsA());
   } else {
      R__c = R__b.WriteVersion(FairRunAnaProof::IsA(), kTRUE);
      FairRunAna::Streamer(R__b);
      R__b << fProof;
      fProofOutputStatus.Streamer(R__b);
      R__b << fProofFileSource;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRunAnaProof(void *p) {
      return  p ? new(p) ::FairRunAnaProof : new ::FairRunAnaProof;
   }
   static void *newArray_FairRunAnaProof(Long_t nElements, void *p) {
      return p ? new(p) ::FairRunAnaProof[nElements] : new ::FairRunAnaProof[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRunAnaProof(void *p) {
      delete ((::FairRunAnaProof*)p);
   }
   static void deleteArray_FairRunAnaProof(void *p) {
      delete [] ((::FairRunAnaProof*)p);
   }
   static void destruct_FairRunAnaProof(void *p) {
      typedef ::FairRunAnaProof current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRunAnaProof(TBuffer &buf, void *obj) {
      ((::FairRunAnaProof*)obj)->::FairRunAnaProof::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRunAnaProof

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRunIdGenerator(void *p) {
      return  p ? new(p) ::FairRunIdGenerator : new ::FairRunIdGenerator;
   }
   static void *newArray_FairRunIdGenerator(Long_t nElements, void *p) {
      return p ? new(p) ::FairRunIdGenerator[nElements] : new ::FairRunIdGenerator[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRunIdGenerator(void *p) {
      delete ((::FairRunIdGenerator*)p);
   }
   static void deleteArray_FairRunIdGenerator(void *p) {
      delete [] ((::FairRunIdGenerator*)p);
   }
   static void destruct_FairRunIdGenerator(void *p) {
      typedef ::FairRunIdGenerator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRunIdGenerator

//______________________________________________________________________________
void FairRunSim::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRunSim.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairRun::Streamer(R__b);
      R__b >> fField;
      R__b >> fUserDecay;
      R__b.CheckByteCount(R__s, R__c, FairRunSim::IsA());
   } else {
      R__c = R__b.WriteVersion(FairRunSim::IsA(), kTRUE);
      FairRun::Streamer(R__b);
      R__b << fField;
      R__b << fUserDecay;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRunSim(void *p) {
      return  p ? new(p) ::FairRunSim : new ::FairRunSim;
   }
   static void *newArray_FairRunSim(Long_t nElements, void *p) {
      return p ? new(p) ::FairRunSim[nElements] : new ::FairRunSim[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRunSim(void *p) {
      delete ((::FairRunSim*)p);
   }
   static void deleteArray_FairRunSim(void *p) {
      delete [] ((::FairRunSim*)p);
   }
   static void destruct_FairRunSim(void *p) {
      typedef ::FairRunSim current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRunSim(TBuffer &buf, void *obj) {
      ((::FairRunSim*)obj)->::FairRunSim::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRunSim

//______________________________________________________________________________
void FairTrackParam::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTrackParam.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTrackParam::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTrackParam::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTrackParam(void *p) {
      return  p ? new(p) ::FairTrackParam : new ::FairTrackParam;
   }
   static void *newArray_FairTrackParam(Long_t nElements, void *p) {
      return p ? new(p) ::FairTrackParam[nElements] : new ::FairTrackParam[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTrackParam(void *p) {
      delete ((::FairTrackParam*)p);
   }
   static void deleteArray_FairTrackParam(void *p) {
      delete [] ((::FairTrackParam*)p);
   }
   static void destruct_FairTrackParam(void *p) {
      typedef ::FairTrackParam current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTrackParam

//______________________________________________________________________________
void FairTrajFilter::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTrajFilter.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      R__b >> fVxMin;
      R__b >> fVxMax;
      R__b >> fVyMin;
      R__b >> fVyMax;
      R__b >> fVzMin;
      R__b >> fVzMax;
      R__b >> fPMin;
      R__b >> fPMax;
      R__b >> fThetaMin;
      R__b >> fThetaMax;
      R__b >> fPhiMin;
      R__b >> fPhiMax;
      R__b >> fPxMin;
      R__b >> fPxMax;
      R__b >> fPyMin;
      R__b >> fPyMax;
      R__b >> fPzMin;
      R__b >> fPzMax;
      R__b >> fPtMin;
      R__b >> fPtMax;
      R__b >> fRapidityMin;
      R__b >> fRapidityMax;
      R__b >> fKinCutType;
      R__b >> fEtotMin;
      R__b >> fEtotMax;
      R__b >> fStorePrim;
      R__b >> fStoreSec;
      R__b >> fStepSizeMin;
      fTrackCollection->Streamer(R__b);
      R__b >> fCurrentTrk;
      R__b.CheckByteCount(R__s, R__c, FairTrajFilter::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTrajFilter::IsA(), kTRUE);
      R__b << fVxMin;
      R__b << fVxMax;
      R__b << fVyMin;
      R__b << fVyMax;
      R__b << fVzMin;
      R__b << fVzMax;
      R__b << fPMin;
      R__b << fPMax;
      R__b << fThetaMin;
      R__b << fThetaMax;
      R__b << fPhiMin;
      R__b << fPhiMax;
      R__b << fPxMin;
      R__b << fPxMax;
      R__b << fPyMin;
      R__b << fPyMax;
      R__b << fPzMin;
      R__b << fPzMax;
      R__b << fPtMin;
      R__b << fPtMax;
      R__b << fRapidityMin;
      R__b << fRapidityMax;
      R__b << fKinCutType;
      R__b << fEtotMin;
      R__b << fEtotMax;
      R__b << fStorePrim;
      R__b << fStoreSec;
      R__b << fStepSizeMin;
      fTrackCollection->Streamer(R__b);
      R__b << fCurrentTrk;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTrajFilter(void *p) {
      return  p ? new(p) ::FairTrajFilter : new ::FairTrajFilter;
   }
   static void *newArray_FairTrajFilter(Long_t nElements, void *p) {
      return p ? new(p) ::FairTrajFilter[nElements] : new ::FairTrajFilter[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTrajFilter(void *p) {
      delete ((::FairTrajFilter*)p);
   }
   static void deleteArray_FairTrajFilter(void *p) {
      delete [] ((::FairTrajFilter*)p);
   }
   static void destruct_FairTrajFilter(void *p) {
      typedef ::FairTrajFilter current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTrajFilter(TBuffer &buf, void *obj) {
      ((::FairTrajFilter*)obj)->::FairTrajFilter::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTrajFilter

//______________________________________________________________________________
void FairVolume::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairVolume.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairVolume::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairVolume::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairVolume(void *p) {
      return  p ? new(p) ::FairVolume : new ::FairVolume;
   }
   static void *newArray_FairVolume(Long_t nElements, void *p) {
      return p ? new(p) ::FairVolume[nElements] : new ::FairVolume[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairVolume(void *p) {
      delete ((::FairVolume*)p);
   }
   static void deleteArray_FairVolume(void *p) {
      delete [] ((::FairVolume*)p);
   }
   static void destruct_FairVolume(void *p) {
      typedef ::FairVolume current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairVolume

//______________________________________________________________________________
void FairVolumeList::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairVolumeList.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairVolumeList::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairVolumeList::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairVolumeList(void *p) {
      return  p ? new(p) ::FairVolumeList : new ::FairVolumeList;
   }
   static void *newArray_FairVolumeList(Long_t nElements, void *p) {
      return p ? new(p) ::FairVolumeList[nElements] : new ::FairVolumeList[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairVolumeList(void *p) {
      delete ((::FairVolumeList*)p);
   }
   static void deleteArray_FairVolumeList(void *p) {
      delete [] ((::FairVolumeList*)p);
   }
   static void destruct_FairVolumeList(void *p) {
      typedef ::FairVolumeList current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairVolumeList

//______________________________________________________________________________
void FairField::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairField.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairField::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairField::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairField(void *p) {
      return  p ? new(p) ::FairField : new ::FairField;
   }
   static void *newArray_FairField(Long_t nElements, void *p) {
      return p ? new(p) ::FairField[nElements] : new ::FairField[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairField(void *p) {
      delete ((::FairField*)p);
   }
   static void deleteArray_FairField(void *p) {
      delete [] ((::FairField*)p);
   }
   static void destruct_FairField(void *p) {
      typedef ::FairField current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairField

//______________________________________________________________________________
void FairGenericStack::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGenericStack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGenericStack::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGenericStack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGenericStack(void *p) {
      return  p ? new(p) ::FairGenericStack : new ::FairGenericStack;
   }
   static void *newArray_FairGenericStack(Long_t nElements, void *p) {
      return p ? new(p) ::FairGenericStack[nElements] : new ::FairGenericStack[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGenericStack(void *p) {
      delete ((::FairGenericStack*)p);
   }
   static void deleteArray_FairGenericStack(void *p) {
      delete [] ((::FairGenericStack*)p);
   }
   static void destruct_FairGenericStack(void *p) {
      typedef ::FairGenericStack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGenericStack

//______________________________________________________________________________
void FairTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTask.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTask::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTask::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTask(void *p) {
      return  p ? new(p) ::FairTask : new ::FairTask;
   }
   static void *newArray_FairTask(Long_t nElements, void *p) {
      return p ? new(p) ::FairTask[nElements] : new ::FairTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTask(void *p) {
      delete ((::FairTask*)p);
   }
   static void deleteArray_FairTask(void *p) {
      delete [] ((::FairTask*)p);
   }
   static void destruct_FairTask(void *p) {
      typedef ::FairTask current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTask

//______________________________________________________________________________
void FairFieldFactory::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairFieldFactory.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairFieldFactory::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairFieldFactory::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairFieldFactory(void *p) {
      return  p ? new(p) ::FairFieldFactory : new ::FairFieldFactory;
   }
   static void *newArray_FairFieldFactory(Long_t nElements, void *p) {
      return p ? new(p) ::FairFieldFactory[nElements] : new ::FairFieldFactory[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairFieldFactory(void *p) {
      delete ((::FairFieldFactory*)p);
   }
   static void deleteArray_FairFieldFactory(void *p) {
      delete [] ((::FairFieldFactory*)p);
   }
   static void destruct_FairFieldFactory(void *p) {
      typedef ::FairFieldFactory current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairFieldFactory

//______________________________________________________________________________
void FairRadLenPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRadLenPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRadLenPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRadLenPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRadLenPoint(void *p) {
      return  p ? new(p) ::FairRadLenPoint : new ::FairRadLenPoint;
   }
   static void *newArray_FairRadLenPoint(Long_t nElements, void *p) {
      return p ? new(p) ::FairRadLenPoint[nElements] : new ::FairRadLenPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRadLenPoint(void *p) {
      delete ((::FairRadLenPoint*)p);
   }
   static void deleteArray_FairRadLenPoint(void *p) {
      delete [] ((::FairRadLenPoint*)p);
   }
   static void destruct_FairRadLenPoint(void *p) {
      typedef ::FairRadLenPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRadLenPoint

//______________________________________________________________________________
void FairRadLenManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRadLenManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRadLenManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRadLenManager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRadLenManager(void *p) {
      return  p ? new(p) ::FairRadLenManager : new ::FairRadLenManager;
   }
   static void *newArray_FairRadLenManager(Long_t nElements, void *p) {
      return p ? new(p) ::FairRadLenManager[nElements] : new ::FairRadLenManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRadLenManager(void *p) {
      delete ((::FairRadLenManager*)p);
   }
   static void deleteArray_FairRadLenManager(void *p) {
      delete [] ((::FairRadLenManager*)p);
   }
   static void destruct_FairRadLenManager(void *p) {
      typedef ::FairRadLenManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRadLenManager

//______________________________________________________________________________
void FairRadGridManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRadGridManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRadGridManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRadGridManager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRadGridManager(void *p) {
      return  p ? new(p) ::FairRadGridManager : new ::FairRadGridManager;
   }
   static void *newArray_FairRadGridManager(Long_t nElements, void *p) {
      return p ? new(p) ::FairRadGridManager[nElements] : new ::FairRadGridManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRadGridManager(void *p) {
      delete ((::FairRadGridManager*)p);
   }
   static void deleteArray_FairRadGridManager(void *p) {
      delete [] ((::FairRadGridManager*)p);
   }
   static void destruct_FairRadGridManager(void *p) {
      typedef ::FairRadGridManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRadGridManager

//______________________________________________________________________________
void FairRadMapManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRadMapManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRadMapManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRadMapManager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRadMapManager(void *p) {
      return  p ? new(p) ::FairRadMapManager : new ::FairRadMapManager;
   }
   static void *newArray_FairRadMapManager(Long_t nElements, void *p) {
      return p ? new(p) ::FairRadMapManager[nElements] : new ::FairRadMapManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRadMapManager(void *p) {
      delete ((::FairRadMapManager*)p);
   }
   static void deleteArray_FairRadMapManager(void *p) {
      delete [] ((::FairRadMapManager*)p);
   }
   static void destruct_FairRadMapManager(void *p) {
      typedef ::FairRadMapManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRadMapManager

//______________________________________________________________________________
void FairMesh::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMesh.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMesh::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMesh::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMesh(void *p) {
      return  p ? new(p) ::FairMesh : new ::FairMesh;
   }
   static void *newArray_FairMesh(Long_t nElements, void *p) {
      return p ? new(p) ::FairMesh[nElements] : new ::FairMesh[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMesh(void *p) {
      delete ((::FairMesh*)p);
   }
   static void deleteArray_FairMesh(void *p) {
      delete [] ((::FairMesh*)p);
   }
   static void destruct_FairMesh(void *p) {
      typedef ::FairMesh current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMesh

//______________________________________________________________________________
void FairRKPropagator::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRKPropagator.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRKPropagator::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRKPropagator::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairRKPropagator(void *p) {
      delete ((::FairRKPropagator*)p);
   }
   static void deleteArray_FairRKPropagator(void *p) {
      delete [] ((::FairRKPropagator*)p);
   }
   static void destruct_FairRKPropagator(void *p) {
      typedef ::FairRKPropagator current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRKPropagator

//______________________________________________________________________________
void FairTimeStamp::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTimeStamp.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTimeStamp::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTimeStamp::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTimeStamp(void *p) {
      return  p ? new(p) ::FairTimeStamp : new ::FairTimeStamp;
   }
   static void *newArray_FairTimeStamp(Long_t nElements, void *p) {
      return p ? new(p) ::FairTimeStamp[nElements] : new ::FairTimeStamp[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTimeStamp(void *p) {
      delete ((::FairTimeStamp*)p);
   }
   static void deleteArray_FairTimeStamp(void *p) {
      delete [] ((::FairTimeStamp*)p);
   }
   static void destruct_FairTimeStamp(void *p) {
      typedef ::FairTimeStamp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTimeStamp

//______________________________________________________________________________
void FairRadMapPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRadMapPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRadMapPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRadMapPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRadMapPoint(void *p) {
      return  p ? new(p) ::FairRadMapPoint : new ::FairRadMapPoint;
   }
   static void *newArray_FairRadMapPoint(Long_t nElements, void *p) {
      return p ? new(p) ::FairRadMapPoint[nElements] : new ::FairRadMapPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRadMapPoint(void *p) {
      delete ((::FairRadMapPoint*)p);
   }
   static void deleteArray_FairRadMapPoint(void *p) {
      delete [] ((::FairRadMapPoint*)p);
   }
   static void destruct_FairRadMapPoint(void *p) {
      typedef ::FairRadMapPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRadMapPoint

//______________________________________________________________________________
void FairTSBufferFunctional::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTSBufferFunctional.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTSBufferFunctional::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTSBufferFunctional::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairTSBufferFunctional(void *p) {
      delete ((::FairTSBufferFunctional*)p);
   }
   static void deleteArray_FairTSBufferFunctional(void *p) {
      delete [] ((::FairTSBufferFunctional*)p);
   }
   static void destruct_FairTSBufferFunctional(void *p) {
      typedef ::FairTSBufferFunctional current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTSBufferFunctional

//______________________________________________________________________________
void FairFileInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairFileInfo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairFileInfo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairFileInfo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairFileInfo(void *p) {
      return  p ? new(p) ::FairFileInfo : new ::FairFileInfo;
   }
   static void *newArray_FairFileInfo(Long_t nElements, void *p) {
      return p ? new(p) ::FairFileInfo[nElements] : new ::FairFileInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairFileInfo(void *p) {
      delete ((::FairFileInfo*)p);
   }
   static void deleteArray_FairFileInfo(void *p) {
      delete [] ((::FairFileInfo*)p);
   }
   static void destruct_FairFileInfo(void *p) {
      typedef ::FairFileInfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairFileInfo

//______________________________________________________________________________
void FairRunInfo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRunInfo.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairRunInfo::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairRunInfo::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRunInfo(void *p) {
      return  p ? new(p) ::FairRunInfo : new ::FairRunInfo;
   }
   static void *newArray_FairRunInfo(Long_t nElements, void *p) {
      return p ? new(p) ::FairRunInfo[nElements] : new ::FairRunInfo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRunInfo(void *p) {
      delete ((::FairRunInfo*)p);
   }
   static void deleteArray_FairRunInfo(void *p) {
      delete [] ((::FairRunInfo*)p);
   }
   static void destruct_FairRunInfo(void *p) {
      typedef ::FairRunInfo current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairRunInfo

//______________________________________________________________________________
void FairWriteoutBuffer::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairWriteoutBuffer.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      {
         multimap<double,pair<double,FairTimeStamp*> > &R__stl =  fStartTime_map;
         R__stl.clear();
         TClass *R__tcl2 = TBuffer::GetClass(typeid(struct std::__1::pair<double, class FairTimeStamp *>));
         if (R__tcl2==0) {
            Error("fStartTime_map streamer","Missing the TClass object for struct std::__1::pair<double, class FairTimeStamp *>!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            double R__t;
            R__b >> R__t;
            pair<double,FairTimeStamp*> R__t2;
            R__b.StreamObject(&R__t2,R__tcl2);
            typedef double Value_t;
            std::pair<Value_t const, struct std::__1::pair<double, class FairTimeStamp *> > R__t3(R__t,R__t2);
            R__stl.insert(R__t3);
         }
      }
      {
         multimap<double,FairTimeStamp*> &R__stl =  fDeadTime_map;
         R__stl.clear();
         TClass *R__tcl2 = TBuffer::GetClass(typeid(class FairTimeStamp *));
         if (R__tcl2==0) {
            Error("fDeadTime_map streamer","Missing the TClass object for class FairTimeStamp *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         for (R__i = 0; R__i < R__n; R__i++) {
            double R__t;
            R__b >> R__t;
            FairTimeStamp* R__t2;
            R__t2 = (FairTimeStamp*)R__b.ReadObjectAny(R__tcl2);
            typedef double Value_t;
            std::pair<Value_t const, class FairTimeStamp * > R__t3(R__t,R__t2);
            R__stl.insert(R__t3);
         }
      }
      fBranchName.Streamer(R__b);
      fClassName.Streamer(R__b);
      R__b >> fTreeSave;
      R__b >> fActivateBuffering;
      R__b >> fVerbose;
      R__b.CheckByteCount(R__s, R__c, FairWriteoutBuffer::IsA());
   } else {
      R__c = R__b.WriteVersion(FairWriteoutBuffer::IsA(), kTRUE);
      TObject::Streamer(R__b);
      {
         multimap<double,pair<double,FairTimeStamp*> > &R__stl =  fStartTime_map;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl2 = TBuffer::GetClass(typeid(struct std::__1::pair<double, class FairTimeStamp *>));
         if (R__tcl2==0) {
            Error("fStartTime_mapstreamer","Missing the TClass object for struct std::__1::pair<double, class FairTimeStamp *>!");
            return;
         }
            multimap<double,pair<double,FairTimeStamp*> >::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << ((*R__k).first );
            R__b.StreamObject((pair<double,FairTimeStamp*>*)&((*R__k).second),R__tcl2);
            }
         }
      }
      {
         multimap<double,FairTimeStamp*> &R__stl =  fDeadTime_map;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            multimap<double,FairTimeStamp*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << ((*R__k).first );
            R__b << ((*R__k).second);
            }
         }
      }
      fBranchName.Streamer(R__b);
      fClassName.Streamer(R__b);
      R__b << fTreeSave;
      R__b << fActivateBuffering;
      R__b << fVerbose;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairWriteoutBuffer(void *p) {
      delete ((::FairWriteoutBuffer*)p);
   }
   static void deleteArray_FairWriteoutBuffer(void *p) {
      delete [] ((::FairWriteoutBuffer*)p);
   }
   static void destruct_FairWriteoutBuffer(void *p) {
      typedef ::FairWriteoutBuffer current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairWriteoutBuffer(TBuffer &buf, void *obj) {
      ((::FairWriteoutBuffer*)obj)->::FairWriteoutBuffer::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairWriteoutBuffer

//______________________________________________________________________________
void FairRingSorter::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRingSorter.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      {
         vector<multimap<double,FairTimeStamp*> > &R__stl =  fRingBuffer;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class std::__1::multimap<double, class FairTimeStamp *, struct std::__1::less<double>, class std::__1::allocator<struct std::__1::pair<const double, class FairTimeStamp *> > >));
         if (R__tcl1==0) {
            Error("fRingBuffer streamer","Missing the TClass object for class std::__1::multimap<double, class FairTimeStamp *, struct std::__1::less<double>, class std::__1::allocator<struct std::__1::pair<const double, class FairTimeStamp *> > >!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            multimap<double,FairTimeStamp*> R__t;
            R__b.StreamObject(&R__t,R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      {
         vector<FairTimeStamp*> &R__stl =  fOutputData;
         R__stl.clear();
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class FairTimeStamp *));
         if (R__tcl1==0) {
            Error("fOutputData streamer","Missing the TClass object for class FairTimeStamp *!");
            return;
         }
         int R__i, R__n;
         R__b >> R__n;
         R__stl.reserve(R__n);
         for (R__i = 0; R__i < R__n; R__i++) {
            FairTimeStamp* R__t;
            R__t = (FairTimeStamp*)R__b.ReadObjectAny(R__tcl1);
            R__stl.push_back(R__t);
         }
      }
      R__b.StreamObject(&(fLowerBoundPointer),typeid(fLowerBoundPointer));
      R__b >> fCellWidth;
      R__b >> fVerbose;
      R__b.CheckByteCount(R__s, R__c, FairRingSorter::IsA());
   } else {
      R__c = R__b.WriteVersion(FairRingSorter::IsA(), kTRUE);
      TObject::Streamer(R__b);
      {
         vector<multimap<double,FairTimeStamp*> > &R__stl =  fRingBuffer;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
         TClass *R__tcl1 = TBuffer::GetClass(typeid(class std::__1::multimap<double, class FairTimeStamp *, struct std::__1::less<double>, class std::__1::allocator<struct std::__1::pair<const double, class FairTimeStamp *> > >));
         if (R__tcl1==0) {
            Error("fRingBuffer streamer","Missing the TClass object for class std::__1::multimap<double, class FairTimeStamp *, struct std::__1::less<double>, class std::__1::allocator<struct std::__1::pair<const double, class FairTimeStamp *> > >!");
            return;
         }
            vector<multimap<double,FairTimeStamp*> >::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b.StreamObject((multimap<double,FairTimeStamp*>*)&(*R__k),R__tcl1);
            }
         }
      }
      {
         vector<FairTimeStamp*> &R__stl =  fOutputData;
         int R__n=int(R__stl.size());
         R__b << R__n;
         if(R__n) {
            vector<FairTimeStamp*>::iterator R__k;
            for (R__k = R__stl.begin(); R__k != R__stl.end(); ++R__k) {
            R__b << (*R__k);
            }
         }
      }
      R__b.StreamObject(&(fLowerBoundPointer),typeid(fLowerBoundPointer));
      R__b << fCellWidth;
      R__b << fVerbose;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRingSorter(void *p) {
      return  p ? new(p) ::FairRingSorter : new ::FairRingSorter;
   }
   static void *newArray_FairRingSorter(Long_t nElements, void *p) {
      return p ? new(p) ::FairRingSorter[nElements] : new ::FairRingSorter[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRingSorter(void *p) {
      delete ((::FairRingSorter*)p);
   }
   static void deleteArray_FairRingSorter(void *p) {
      delete [] ((::FairRingSorter*)p);
   }
   static void destruct_FairRingSorter(void *p) {
      typedef ::FairRingSorter current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRingSorter(TBuffer &buf, void *obj) {
      ((::FairRingSorter*)obj)->::FairRingSorter::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRingSorter

//______________________________________________________________________________
void FairRingSorterTask::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRingSorterTask.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairTask::Streamer(R__b);
      R__b >> fSorter;
      R__b >> fPersistance;
      R__b >> fDigiPixelMCInfo;
      R__b >> fNumberOfCells;
      R__b >> fWidthOfCells;
      fInputBranch.Streamer(R__b);
      fInputArray->Streamer(R__b);
      fOutputBranch.Streamer(R__b);
      fFolder.Streamer(R__b);
      fOutputArray->Streamer(R__b);
      R__b >> fEntryNr;
      R__b.CheckByteCount(R__s, R__c, FairRingSorterTask::IsA());
   } else {
      R__c = R__b.WriteVersion(FairRingSorterTask::IsA(), kTRUE);
      FairTask::Streamer(R__b);
      R__b << fSorter;
      R__b << fPersistance;
      R__b << fDigiPixelMCInfo;
      R__b << fNumberOfCells;
      R__b << fWidthOfCells;
      fInputBranch.Streamer(R__b);
      fInputArray->Streamer(R__b);
      fOutputBranch.Streamer(R__b);
      fFolder.Streamer(R__b);
      fOutputArray->Streamer(R__b);
      R__b << fEntryNr;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRingSorterTask(void *p) {
      return  p ? new(p) ::FairRingSorterTask : new ::FairRingSorterTask;
   }
   static void *newArray_FairRingSorterTask(Long_t nElements, void *p) {
      return p ? new(p) ::FairRingSorterTask[nElements] : new ::FairRingSorterTask[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRingSorterTask(void *p) {
      delete ((::FairRingSorterTask*)p);
   }
   static void deleteArray_FairRingSorterTask(void *p) {
      delete [] ((::FairRingSorterTask*)p);
   }
   static void destruct_FairRingSorterTask(void *p) {
      typedef ::FairRingSorterTask current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRingSorterTask(TBuffer &buf, void *obj) {
      ((::FairRingSorterTask*)obj)->::FairRingSorterTask::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRingSorterTask

//______________________________________________________________________________
void FairAnaSelector::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairAnaSelector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairAnaSelector::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairAnaSelector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairAnaSelector(void *p) {
      return  p ? new(p) ::FairAnaSelector : new ::FairAnaSelector;
   }
   static void *newArray_FairAnaSelector(Long_t nElements, void *p) {
      return p ? new(p) ::FairAnaSelector[nElements] : new ::FairAnaSelector[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairAnaSelector(void *p) {
      delete ((::FairAnaSelector*)p);
   }
   static void deleteArray_FairAnaSelector(void *p) {
      delete [] ((::FairAnaSelector*)p);
   }
   static void destruct_FairAnaSelector(void *p) {
      typedef ::FairAnaSelector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairAnaSelector

//______________________________________________________________________________
void FairLinkManager::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairLinkManager.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairLinkManager::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairLinkManager::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairLinkManager(void *p) {
      return  p ? new(p) ::FairLinkManager : new ::FairLinkManager;
   }
   static void *newArray_FairLinkManager(Long_t nElements, void *p) {
      return p ? new(p) ::FairLinkManager[nElements] : new ::FairLinkManager[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairLinkManager(void *p) {
      delete ((::FairLinkManager*)p);
   }
   static void deleteArray_FairLinkManager(void *p) {
      delete [] ((::FairLinkManager*)p);
   }
   static void destruct_FairLinkManager(void *p) {
      typedef ::FairLinkManager current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairLinkManager

//______________________________________________________________________________
void FairRunOnline::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRunOnline.

   FairRun::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairRunOnline(void *p) {
      return  p ? new(p) ::FairRunOnline : new ::FairRunOnline;
   }
   static void *newArray_FairRunOnline(Long_t nElements, void *p) {
      return p ? new(p) ::FairRunOnline[nElements] : new ::FairRunOnline[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairRunOnline(void *p) {
      delete ((::FairRunOnline*)p);
   }
   static void deleteArray_FairRunOnline(void *p) {
      delete [] ((::FairRunOnline*)p);
   }
   static void destruct_FairRunOnline(void *p) {
      typedef ::FairRunOnline current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRunOnline(TBuffer &buf, void *obj) {
      ((::FairRunOnline*)obj)->::FairRunOnline::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRunOnline

//______________________________________________________________________________
void FairSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairSource.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> fRunId;
      R__b.CheckByteCount(R__s, R__c, FairSource::IsA());
   } else {
      R__c = R__b.WriteVersion(FairSource::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << fRunId;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairSource(void *p) {
      delete ((::FairSource*)p);
   }
   static void deleteArray_FairSource(void *p) {
      delete [] ((::FairSource*)p);
   }
   static void destruct_FairSource(void *p) {
      typedef ::FairSource current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairSource(TBuffer &buf, void *obj) {
      ((::FairSource*)obj)->::FairSource::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairSource

//______________________________________________________________________________
void FairFileSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairFileSource.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairSource::Streamer(R__b);
      fInputTitle.Streamer(R__b);
      R__b >> fRootFile;
      R__b >> fInChain;
      R__b >> fInTree;
      R__b >> fRtdb;
      R__b >> fCbmout;
      R__b >> fCbmroot;
      R__b >> fSourceIdentifier;
      R__b >> fNoOfEntries;
      R__b >> IsInitialized;
      R__b.CheckByteCount(R__s, R__c, FairFileSource::IsA());
   } else {
      R__c = R__b.WriteVersion(FairFileSource::IsA(), kTRUE);
      FairSource::Streamer(R__b);
      fInputTitle.Streamer(R__b);
      R__b << fRootFile;
      R__b << fInChain;
      R__b << fInTree;
      R__b << fRtdb;
      R__b << fCbmout;
      R__b << fCbmroot;
      R__b << fSourceIdentifier;
      R__b << fNoOfEntries;
      R__b << IsInitialized;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairFileSource(void *p) {
      delete ((::FairFileSource*)p);
   }
   static void deleteArray_FairFileSource(void *p) {
      delete [] ((::FairFileSource*)p);
   }
   static void destruct_FairFileSource(void *p) {
      typedef ::FairFileSource current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairFileSource(TBuffer &buf, void *obj) {
      ((::FairFileSource*)obj)->::FairFileSource::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairFileSource

//______________________________________________________________________________
void FairMixedSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMixedSource.

   FairSource::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairMixedSource(void *p) {
      delete ((::FairMixedSource*)p);
   }
   static void deleteArray_FairMixedSource(void *p) {
      delete [] ((::FairMixedSource*)p);
   }
   static void destruct_FairMixedSource(void *p) {
      typedef ::FairMixedSource current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairMixedSource(TBuffer &buf, void *obj) {
      ((::FairMixedSource*)obj)->::FairMixedSource::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairMixedSource

//______________________________________________________________________________
void FairOnlineSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairOnlineSource.

   FairSource::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairOnlineSource(void *p) {
      delete ((::FairOnlineSource*)p);
   }
   static void deleteArray_FairOnlineSource(void *p) {
      delete [] ((::FairOnlineSource*)p);
   }
   static void destruct_FairOnlineSource(void *p) {
      typedef ::FairOnlineSource current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairOnlineSource(TBuffer &buf, void *obj) {
      ((::FairOnlineSource*)obj)->::FairOnlineSource::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairOnlineSource

//______________________________________________________________________________
void FairMbsSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMbsSource.

   FairOnlineSource::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairMbsSource(void *p) {
      delete ((::FairMbsSource*)p);
   }
   static void deleteArray_FairMbsSource(void *p) {
      delete [] ((::FairMbsSource*)p);
   }
   static void destruct_FairMbsSource(void *p) {
      typedef ::FairMbsSource current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairMbsSource(TBuffer &buf, void *obj) {
      ((::FairMbsSource*)obj)->::FairMbsSource::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairMbsSource

//______________________________________________________________________________
void FairRemoteSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairRemoteSource.

   FairMbsSource::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairRemoteSource(void *p) {
      delete ((::FairRemoteSource*)p);
   }
   static void deleteArray_FairRemoteSource(void *p) {
      delete [] ((::FairRemoteSource*)p);
   }
   static void destruct_FairRemoteSource(void *p) {
      typedef ::FairRemoteSource current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairRemoteSource(TBuffer &buf, void *obj) {
      ((::FairRemoteSource*)obj)->::FairRemoteSource::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairRemoteSource

//______________________________________________________________________________
void FairMbsStreamSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMbsStreamSource.

   FairMbsSource::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairMbsStreamSource(void *p) {
      delete ((::FairMbsStreamSource*)p);
   }
   static void deleteArray_FairMbsStreamSource(void *p) {
      delete [] ((::FairMbsStreamSource*)p);
   }
   static void destruct_FairMbsStreamSource(void *p) {
      typedef ::FairMbsStreamSource current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairMbsStreamSource(TBuffer &buf, void *obj) {
      ((::FairMbsStreamSource*)obj)->::FairMbsStreamSource::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairMbsStreamSource

//______________________________________________________________________________
void FairLmdSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairLmdSource.

   FairMbsSource::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairLmdSource(void *p) {
      return  p ? new(p) ::FairLmdSource : new ::FairLmdSource;
   }
   static void *newArray_FairLmdSource(Long_t nElements, void *p) {
      return p ? new(p) ::FairLmdSource[nElements] : new ::FairLmdSource[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairLmdSource(void *p) {
      delete ((::FairLmdSource*)p);
   }
   static void deleteArray_FairLmdSource(void *p) {
      delete [] ((::FairLmdSource*)p);
   }
   static void destruct_FairLmdSource(void *p) {
      typedef ::FairLmdSource current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairLmdSource(TBuffer &buf, void *obj) {
      ((::FairLmdSource*)obj)->::FairLmdSource::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairLmdSource

//______________________________________________________________________________
void FairUnpack::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairUnpack.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairUnpack(void *p) {
      delete ((::FairUnpack*)p);
   }
   static void deleteArray_FairUnpack(void *p) {
      delete [] ((::FairUnpack*)p);
   }
   static void destruct_FairUnpack(void *p) {
      typedef ::FairUnpack current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairUnpack(TBuffer &buf, void *obj) {
      ((::FairUnpack*)obj)->::FairUnpack::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairUnpack

//______________________________________________________________________________
void MRevBuffer::Streamer(TBuffer &R__b)
{
   // Stream an object of class MRevBuffer.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_MRevBuffer(void *p) {
      delete ((::MRevBuffer*)p);
   }
   static void deleteArray_MRevBuffer(void *p) {
      delete [] ((::MRevBuffer*)p);
   }
   static void destruct_MRevBuffer(void *p) {
      typedef ::MRevBuffer current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_MRevBuffer(TBuffer &buf, void *obj) {
      ((::MRevBuffer*)obj)->::MRevBuffer::Streamer(buf);
   }
} // end of namespace ROOT for class ::MRevBuffer

//______________________________________________________________________________
void REvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class REvent.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_REvent(void *p) {
      return  p ? new(p) ::REvent : new ::REvent;
   }
   static void *newArray_REvent(Long_t nElements, void *p) {
      return p ? new(p) ::REvent[nElements] : new ::REvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_REvent(void *p) {
      delete ((::REvent*)p);
   }
   static void deleteArray_REvent(void *p) {
      delete [] ((::REvent*)p);
   }
   static void destruct_REvent(void *p) {
      typedef ::REvent current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_REvent(TBuffer &buf, void *obj) {
      ((::REvent*)obj)->::REvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::REvent

namespace ROOT {
   static TClass *vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR_Dictionary();
   static void vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(void *p = 0);
   static void *newArray_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(void *p);
   static void destruct_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<pair<double,FairRecoEventHeader*> > >*)
   {
      vector<vector<pair<double,FairRecoEventHeader*> > > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<pair<double,FairRecoEventHeader*> > >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<pair<double,FairRecoEventHeader*> > >", -2, "vector", 457,
                  typeid(vector<vector<pair<double,FairRecoEventHeader*> > >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<pair<double,FairRecoEventHeader*> > >) );
      instance.SetNew(&new_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<pair<double,FairRecoEventHeader*> > > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<vector<pair<double,FairRecoEventHeader*> > >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<vector<pair<double,FairRecoEventHeader*> > >*)0x0)->GetClass();
      vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<pair<double,FairRecoEventHeader*> > > : new vector<vector<pair<double,FairRecoEventHeader*> > >;
   }
   static void *newArray_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<vector<pair<double,FairRecoEventHeader*> > >[nElements] : new vector<vector<pair<double,FairRecoEventHeader*> > >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(void *p) {
      delete ((vector<vector<pair<double,FairRecoEventHeader*> > >*)p);
   }
   static void deleteArray_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(void *p) {
      delete [] ((vector<vector<pair<double,FairRecoEventHeader*> > >*)p);
   }
   static void destruct_vectorlEvectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgRsPgR(void *p) {
      typedef vector<vector<pair<double,FairRecoEventHeader*> > > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<vector<pair<double,FairRecoEventHeader*> > >

namespace ROOT {
   static TClass *vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR_Dictionary();
   static void vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(void *p = 0);
   static void *newArray_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(Long_t size, void *p);
   static void delete_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(void *p);
   static void deleteArray_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(void *p);
   static void destruct_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<pair<double,FairRecoEventHeader*> >*)
   {
      vector<pair<double,FairRecoEventHeader*> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<pair<double,FairRecoEventHeader*> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<pair<double,FairRecoEventHeader*> >", -2, "vector", 457,
                  typeid(vector<pair<double,FairRecoEventHeader*> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<pair<double,FairRecoEventHeader*> >) );
      instance.SetNew(&new_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR);
      instance.SetNewArray(&newArray_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR);
      instance.SetDelete(&delete_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR);
      instance.SetDestructor(&destruct_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<pair<double,FairRecoEventHeader*> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<pair<double,FairRecoEventHeader*> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<pair<double,FairRecoEventHeader*> >*)0x0)->GetClass();
      vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<pair<double,FairRecoEventHeader*> > : new vector<pair<double,FairRecoEventHeader*> >;
   }
   static void *newArray_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<pair<double,FairRecoEventHeader*> >[nElements] : new vector<pair<double,FairRecoEventHeader*> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(void *p) {
      delete ((vector<pair<double,FairRecoEventHeader*> >*)p);
   }
   static void deleteArray_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(void *p) {
      delete [] ((vector<pair<double,FairRecoEventHeader*> >*)p);
   }
   static void destruct_vectorlEpairlEdoublecOFairRecoEventHeadermUgRsPgR(void *p) {
      typedef vector<pair<double,FairRecoEventHeader*> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<pair<double,FairRecoEventHeader*> >

namespace ROOT {
   static TClass *vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR_Dictionary();
   static void vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(void *p = 0);
   static void *newArray_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(Long_t size, void *p);
   static void delete_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(void *p);
   static void deleteArray_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(void *p);
   static void destruct_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<multimap<double,FairTimeStamp*> >*)
   {
      vector<multimap<double,FairTimeStamp*> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<multimap<double,FairTimeStamp*> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<multimap<double,FairTimeStamp*> >", -2, "vector", 457,
                  typeid(vector<multimap<double,FairTimeStamp*> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<multimap<double,FairTimeStamp*> >) );
      instance.SetNew(&new_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR);
      instance.SetNewArray(&newArray_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR);
      instance.SetDelete(&delete_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR);
      instance.SetDestructor(&destruct_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<multimap<double,FairTimeStamp*> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<multimap<double,FairTimeStamp*> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<multimap<double,FairTimeStamp*> >*)0x0)->GetClass();
      vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<multimap<double,FairTimeStamp*> > : new vector<multimap<double,FairTimeStamp*> >;
   }
   static void *newArray_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<multimap<double,FairTimeStamp*> >[nElements] : new vector<multimap<double,FairTimeStamp*> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(void *p) {
      delete ((vector<multimap<double,FairTimeStamp*> >*)p);
   }
   static void deleteArray_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(void *p) {
      delete [] ((vector<multimap<double,FairTimeStamp*> >*)p);
   }
   static void destruct_vectorlEmultimaplEdoublecOFairTimeStampmUgRsPgR(void *p) {
      typedef vector<multimap<double,FairTimeStamp*> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<multimap<double,FairTimeStamp*> >

namespace ROOT {
   static TClass *vectorlEFairTimeStampmUgR_Dictionary();
   static void vectorlEFairTimeStampmUgR_TClassManip(TClass*);
   static void *new_vectorlEFairTimeStampmUgR(void *p = 0);
   static void *newArray_vectorlEFairTimeStampmUgR(Long_t size, void *p);
   static void delete_vectorlEFairTimeStampmUgR(void *p);
   static void deleteArray_vectorlEFairTimeStampmUgR(void *p);
   static void destruct_vectorlEFairTimeStampmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<FairTimeStamp*>*)
   {
      vector<FairTimeStamp*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<FairTimeStamp*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<FairTimeStamp*>", -2, "vector", 457,
                  typeid(vector<FairTimeStamp*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEFairTimeStampmUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<FairTimeStamp*>) );
      instance.SetNew(&new_vectorlEFairTimeStampmUgR);
      instance.SetNewArray(&newArray_vectorlEFairTimeStampmUgR);
      instance.SetDelete(&delete_vectorlEFairTimeStampmUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEFairTimeStampmUgR);
      instance.SetDestructor(&destruct_vectorlEFairTimeStampmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<FairTimeStamp*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<FairTimeStamp*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEFairTimeStampmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<FairTimeStamp*>*)0x0)->GetClass();
      vectorlEFairTimeStampmUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEFairTimeStampmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEFairTimeStampmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FairTimeStamp*> : new vector<FairTimeStamp*>;
   }
   static void *newArray_vectorlEFairTimeStampmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FairTimeStamp*>[nElements] : new vector<FairTimeStamp*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEFairTimeStampmUgR(void *p) {
      delete ((vector<FairTimeStamp*>*)p);
   }
   static void deleteArray_vectorlEFairTimeStampmUgR(void *p) {
      delete [] ((vector<FairTimeStamp*>*)p);
   }
   static void destruct_vectorlEFairTimeStampmUgR(void *p) {
      typedef vector<FairTimeStamp*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<FairTimeStamp*>

namespace ROOT {
   static TClass *vectorlEFairEventBuildermUgR_Dictionary();
   static void vectorlEFairEventBuildermUgR_TClassManip(TClass*);
   static void *new_vectorlEFairEventBuildermUgR(void *p = 0);
   static void *newArray_vectorlEFairEventBuildermUgR(Long_t size, void *p);
   static void delete_vectorlEFairEventBuildermUgR(void *p);
   static void deleteArray_vectorlEFairEventBuildermUgR(void *p);
   static void destruct_vectorlEFairEventBuildermUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<FairEventBuilder*>*)
   {
      vector<FairEventBuilder*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<FairEventBuilder*>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<FairEventBuilder*>", -2, "vector", 457,
                  typeid(vector<FairEventBuilder*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEFairEventBuildermUgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<FairEventBuilder*>) );
      instance.SetNew(&new_vectorlEFairEventBuildermUgR);
      instance.SetNewArray(&newArray_vectorlEFairEventBuildermUgR);
      instance.SetDelete(&delete_vectorlEFairEventBuildermUgR);
      instance.SetDeleteArray(&deleteArray_vectorlEFairEventBuildermUgR);
      instance.SetDestructor(&destruct_vectorlEFairEventBuildermUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<FairEventBuilder*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<FairEventBuilder*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEFairEventBuildermUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<FairEventBuilder*>*)0x0)->GetClass();
      vectorlEFairEventBuildermUgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEFairEventBuildermUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEFairEventBuildermUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FairEventBuilder*> : new vector<FairEventBuilder*>;
   }
   static void *newArray_vectorlEFairEventBuildermUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<FairEventBuilder*>[nElements] : new vector<FairEventBuilder*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEFairEventBuildermUgR(void *p) {
      delete ((vector<FairEventBuilder*>*)p);
   }
   static void deleteArray_vectorlEFairEventBuildermUgR(void *p) {
      delete [] ((vector<FairEventBuilder*>*)p);
   }
   static void destruct_vectorlEFairEventBuildermUgR(void *p) {
      typedef vector<FairEventBuilder*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<FairEventBuilder*>

namespace ROOT {
   static TClass *setlEFairLinkgR_Dictionary();
   static void setlEFairLinkgR_TClassManip(TClass*);
   static void *new_setlEFairLinkgR(void *p = 0);
   static void *newArray_setlEFairLinkgR(Long_t size, void *p);
   static void delete_setlEFairLinkgR(void *p);
   static void deleteArray_setlEFairLinkgR(void *p);
   static void destruct_setlEFairLinkgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const set<FairLink>*)
   {
      set<FairLink> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(set<FairLink>));
      static ::ROOT::TGenericClassInfo 
         instance("set<FairLink>", -2, "set", 400,
                  typeid(set<FairLink>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &setlEFairLinkgR_Dictionary, isa_proxy, 0,
                  sizeof(set<FairLink>) );
      instance.SetNew(&new_setlEFairLinkgR);
      instance.SetNewArray(&newArray_setlEFairLinkgR);
      instance.SetDelete(&delete_setlEFairLinkgR);
      instance.SetDeleteArray(&deleteArray_setlEFairLinkgR);
      instance.SetDestructor(&destruct_setlEFairLinkgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Insert< set<FairLink> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const set<FairLink>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *setlEFairLinkgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const set<FairLink>*)0x0)->GetClass();
      setlEFairLinkgR_TClassManip(theClass);
   return theClass;
   }

   static void setlEFairLinkgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_setlEFairLinkgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<FairLink> : new set<FairLink>;
   }
   static void *newArray_setlEFairLinkgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) set<FairLink>[nElements] : new set<FairLink>[nElements];
   }
   // Wrapper around operator delete
   static void delete_setlEFairLinkgR(void *p) {
      delete ((set<FairLink>*)p);
   }
   static void deleteArray_setlEFairLinkgR(void *p) {
      delete [] ((set<FairLink>*)p);
   }
   static void destruct_setlEFairLinkgR(void *p) {
      typedef set<FairLink> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class set<FairLink>

namespace ROOT {
   static TClass *multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR_Dictionary();
   static void multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR_TClassManip(TClass*);
   static void *new_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(void *p = 0);
   static void *newArray_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(Long_t size, void *p);
   static void delete_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(void *p);
   static void deleteArray_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(void *p);
   static void destruct_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const multimap<double,pair<double,FairTimeStamp*> >*)
   {
      multimap<double,pair<double,FairTimeStamp*> > *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(multimap<double,pair<double,FairTimeStamp*> >));
      static ::ROOT::TGenericClassInfo 
         instance("multimap<double,pair<double,FairTimeStamp*> >", -2, "map", 1686,
                  typeid(multimap<double,pair<double,FairTimeStamp*> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(multimap<double,pair<double,FairTimeStamp*> >) );
      instance.SetNew(&new_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR);
      instance.SetNewArray(&newArray_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR);
      instance.SetDelete(&delete_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR);
      instance.SetDeleteArray(&deleteArray_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR);
      instance.SetDestructor(&destruct_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< multimap<double,pair<double,FairTimeStamp*> > >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const multimap<double,pair<double,FairTimeStamp*> >*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const multimap<double,pair<double,FairTimeStamp*> >*)0x0)->GetClass();
      multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) multimap<double,pair<double,FairTimeStamp*> > : new multimap<double,pair<double,FairTimeStamp*> >;
   }
   static void *newArray_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) multimap<double,pair<double,FairTimeStamp*> >[nElements] : new multimap<double,pair<double,FairTimeStamp*> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(void *p) {
      delete ((multimap<double,pair<double,FairTimeStamp*> >*)p);
   }
   static void deleteArray_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(void *p) {
      delete [] ((multimap<double,pair<double,FairTimeStamp*> >*)p);
   }
   static void destruct_multimaplEdoublecOpairlEdoublecOFairTimeStampmUgRsPgR(void *p) {
      typedef multimap<double,pair<double,FairTimeStamp*> > current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class multimap<double,pair<double,FairTimeStamp*> >

namespace ROOT {
   static TClass *multimaplEdoublecOFairTimeStampmUgR_Dictionary();
   static void multimaplEdoublecOFairTimeStampmUgR_TClassManip(TClass*);
   static void *new_multimaplEdoublecOFairTimeStampmUgR(void *p = 0);
   static void *newArray_multimaplEdoublecOFairTimeStampmUgR(Long_t size, void *p);
   static void delete_multimaplEdoublecOFairTimeStampmUgR(void *p);
   static void deleteArray_multimaplEdoublecOFairTimeStampmUgR(void *p);
   static void destruct_multimaplEdoublecOFairTimeStampmUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const multimap<double,FairTimeStamp*>*)
   {
      multimap<double,FairTimeStamp*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(multimap<double,FairTimeStamp*>));
      static ::ROOT::TGenericClassInfo 
         instance("multimap<double,FairTimeStamp*>", -2, "map", 1686,
                  typeid(multimap<double,FairTimeStamp*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &multimaplEdoublecOFairTimeStampmUgR_Dictionary, isa_proxy, 0,
                  sizeof(multimap<double,FairTimeStamp*>) );
      instance.SetNew(&new_multimaplEdoublecOFairTimeStampmUgR);
      instance.SetNewArray(&newArray_multimaplEdoublecOFairTimeStampmUgR);
      instance.SetDelete(&delete_multimaplEdoublecOFairTimeStampmUgR);
      instance.SetDeleteArray(&deleteArray_multimaplEdoublecOFairTimeStampmUgR);
      instance.SetDestructor(&destruct_multimaplEdoublecOFairTimeStampmUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< multimap<double,FairTimeStamp*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const multimap<double,FairTimeStamp*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *multimaplEdoublecOFairTimeStampmUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const multimap<double,FairTimeStamp*>*)0x0)->GetClass();
      multimaplEdoublecOFairTimeStampmUgR_TClassManip(theClass);
   return theClass;
   }

   static void multimaplEdoublecOFairTimeStampmUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_multimaplEdoublecOFairTimeStampmUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) multimap<double,FairTimeStamp*> : new multimap<double,FairTimeStamp*>;
   }
   static void *newArray_multimaplEdoublecOFairTimeStampmUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) multimap<double,FairTimeStamp*>[nElements] : new multimap<double,FairTimeStamp*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_multimaplEdoublecOFairTimeStampmUgR(void *p) {
      delete ((multimap<double,FairTimeStamp*>*)p);
   }
   static void deleteArray_multimaplEdoublecOFairTimeStampmUgR(void *p) {
      delete [] ((multimap<double,FairTimeStamp*>*)p);
   }
   static void destruct_multimaplEdoublecOFairTimeStampmUgR(void *p) {
      typedef multimap<double,FairTimeStamp*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class multimap<double,FairTimeStamp*>

namespace ROOT {
   static TClass *maplETStringcOboolgR_Dictionary();
   static void maplETStringcOboolgR_TClassManip(TClass*);
   static void *new_maplETStringcOboolgR(void *p = 0);
   static void *newArray_maplETStringcOboolgR(Long_t size, void *p);
   static void delete_maplETStringcOboolgR(void *p);
   static void deleteArray_maplETStringcOboolgR(void *p);
   static void destruct_maplETStringcOboolgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,bool>*)
   {
      map<TString,bool> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,bool>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,bool>", -2, "map", 830,
                  typeid(map<TString,bool>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOboolgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,bool>) );
      instance.SetNew(&new_maplETStringcOboolgR);
      instance.SetNewArray(&newArray_maplETStringcOboolgR);
      instance.SetDelete(&delete_maplETStringcOboolgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOboolgR);
      instance.SetDestructor(&destruct_maplETStringcOboolgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,bool> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<TString,bool>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOboolgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,bool>*)0x0)->GetClass();
      maplETStringcOboolgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOboolgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOboolgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,bool> : new map<TString,bool>;
   }
   static void *newArray_maplETStringcOboolgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,bool>[nElements] : new map<TString,bool>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOboolgR(void *p) {
      delete ((map<TString,bool>*)p);
   }
   static void deleteArray_maplETStringcOboolgR(void *p) {
      delete [] ((map<TString,bool>*)p);
   }
   static void destruct_maplETStringcOboolgR(void *p) {
      typedef map<TString,bool> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,bool>

namespace ROOT {
   static TClass *maplETStringcOTClonesArraymUgR_Dictionary();
   static void maplETStringcOTClonesArraymUgR_TClassManip(TClass*);
   static void *new_maplETStringcOTClonesArraymUgR(void *p = 0);
   static void *newArray_maplETStringcOTClonesArraymUgR(Long_t size, void *p);
   static void delete_maplETStringcOTClonesArraymUgR(void *p);
   static void deleteArray_maplETStringcOTClonesArraymUgR(void *p);
   static void destruct_maplETStringcOTClonesArraymUgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const map<TString,TClonesArray*>*)
   {
      map<TString,TClonesArray*> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(map<TString,TClonesArray*>));
      static ::ROOT::TGenericClassInfo 
         instance("map<TString,TClonesArray*>", -2, "map", 830,
                  typeid(map<TString,TClonesArray*>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &maplETStringcOTClonesArraymUgR_Dictionary, isa_proxy, 0,
                  sizeof(map<TString,TClonesArray*>) );
      instance.SetNew(&new_maplETStringcOTClonesArraymUgR);
      instance.SetNewArray(&newArray_maplETStringcOTClonesArraymUgR);
      instance.SetDelete(&delete_maplETStringcOTClonesArraymUgR);
      instance.SetDeleteArray(&deleteArray_maplETStringcOTClonesArraymUgR);
      instance.SetDestructor(&destruct_maplETStringcOTClonesArraymUgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::MapInsert< map<TString,TClonesArray*> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const map<TString,TClonesArray*>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *maplETStringcOTClonesArraymUgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const map<TString,TClonesArray*>*)0x0)->GetClass();
      maplETStringcOTClonesArraymUgR_TClassManip(theClass);
   return theClass;
   }

   static void maplETStringcOTClonesArraymUgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_maplETStringcOTClonesArraymUgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TClonesArray*> : new map<TString,TClonesArray*>;
   }
   static void *newArray_maplETStringcOTClonesArraymUgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) map<TString,TClonesArray*>[nElements] : new map<TString,TClonesArray*>[nElements];
   }
   // Wrapper around operator delete
   static void delete_maplETStringcOTClonesArraymUgR(void *p) {
      delete ((map<TString,TClonesArray*>*)p);
   }
   static void deleteArray_maplETStringcOTClonesArraymUgR(void *p) {
      delete [] ((map<TString,TClonesArray*>*)p);
   }
   static void destruct_maplETStringcOTClonesArraymUgR(void *p) {
      typedef map<TString,TClonesArray*> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class map<TString,TClonesArray*>

namespace {
  void TriggerDictionaryInitialization_G__BaseDict_Impl() {
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
"/Users/turany/development/FairRoot/MbsAPI",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/base/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__BaseDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairBaseContFact;
class FairBaseParSet;
class FairGeoParSet;
class FairDetector;
class FairEventBuilder;
class FairEventBuilderManager;
class FairEventHeader;
class FairFileHeader;
class __attribute__((annotate(R"ATTRDUMP(Interface to MonteCarlo application)ATTRDUMP"))) FairGeaneApplication;
class FairGenerator;
class __attribute__((annotate("$clingAutoload$FairTimeStamp.h")))  FairLink;
class __attribute__((annotate("$clingAutoload$FairTimeStamp.h")))  FairMultiLinkedData;
class __attribute__((annotate("$clingAutoload$FairTimeStamp.h")))  FairMultiLinkedData_Interface;
class FairHit;
class __attribute__((annotate("$clingAutoload$FairIon.h")))  FairIon;
class __attribute__((annotate(R"ATTRDUMP(Interface to MonteCarlo application)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FairMCApplication.h")))  FairMCApplication;
class FairMCEventHeader;
class FairMCPoint;
class __attribute__((annotate("$clingAutoload$FairModule.h")))  FairModule;
class __attribute__((annotate(R"ATTRDUMP(Extended TParticle)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FairParticle.h")))  FairParticle;
class FairPrimaryGenerator;
class __attribute__((annotate("$clingAutoload$FairRecoEventHeader.h")))  FairRecoEventHeader;
class __attribute__((annotate(R"ATTRDUMP(Root IO manager)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FairTask.h")))  FairRootManager;
class FairRun;
class FairRunAna;
class FairRunAnaProof;
class FairRunIdGenerator;
class FairRunSim;
class FairTrackParam;
class FairTrajFilter;
class __attribute__((annotate(R"ATTRDUMP(Volume Definition)ATTRDUMP"))) FairVolume;
class __attribute__((annotate(R"ATTRDUMP(Volume List)ATTRDUMP"))) FairVolumeList;
class FairField;
class FairGenericStack;
class __attribute__((annotate("$clingAutoload$FairTask.h")))  FairTask;
class FairFieldFactory;
class FairRadLenPoint;
class FairRadLenManager;
class FairRadGridManager;
class FairRadMapManager;
class FairMesh;
class FairRKPropagator;
class __attribute__((annotate("$clingAutoload$FairTimeStamp.h")))  FairTimeStamp;
class FairRadMapPoint;
class FairTSBufferFunctional;
class FairFileInfo;
class __attribute__((annotate("$clingAutoload$FairRunInfo.h")))  FairRunInfo;
class FairWriteoutBuffer;
class FairRingSorter;
class FairRingSorterTask;
class FairAnaSelector;
class __attribute__((annotate(R"ATTRDUMP(Root IO manager)ATTRDUMP"))) FairLinkManager;
class FairRunOnline;
class __attribute__((annotate("$clingAutoload$FairTask.h")))  FairSource;
class __attribute__((annotate("$clingAutoload$FairFileSource.h")))  FairFileSource;
class FairMixedSource;
class FairOnlineSource;
class __attribute__((annotate("$clingAutoload$FairMbsSource.h")))  FairMbsSource;
class FairRemoteSource;
class FairMbsStreamSource;
class FairLmdSource;
class __attribute__((annotate("$clingAutoload$FairUnpack.h")))  FairUnpack;
class __attribute__((annotate(R"ATTRDUMP(prototype for remote event buffer)ATTRDUMP"))) MRevBuffer;
class __attribute__((annotate(R"ATTRDUMP(prototype for event)ATTRDUMP"))) REvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__BaseDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif
#ifndef BUILD_MBS
  #define BUILD_MBS 1
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
// -----            FairAnaSelector header file                        -----
// -----            Created 14/10/11  by R. Karabowicz                 -----
// -----            Updated 01/02/12  by R. Karabowicz                 -----
// -------------------------------------------------------------------------

#ifndef FAIRANASELECTOR_H
#define FAIRANASELECTOR_H

#include "TSelector.h"                  // for TSelector

#include "FairLogger.h"                 // for FairLogger, MESSAGE_ORIGIN

#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "TSelectorList.h"              // for TSelectorList
#include "TString.h"                    // for TString
#include "TTree.h"                      // for TTree

#include <stddef.h>                     // for NULL

class FairFileSource;
class FairRunAnaProof;

class TFile;
class TList;
class TObject;
class TProofOutputFile;
class TString;

class FairAnaSelector : public TSelector
{
  public :
    TProofOutputFile*     fProofFile;
    TFile*                fFile;
    TTree*                fChain;   //!pointer to the analyzed TTree or TChain
    FairRunAnaProof*      fRunAna;

    FairAnaSelector(TTree* /*tree*/ =0) : fProofFile(0), fFile(0), fChain(0), fRunAna(NULL), fLogger(FairLogger::GetLogger()), fProofSource(0), fCurrentDirectory("") { }

    virtual ~FairAnaSelector() { }
    virtual Int_t   Version() const {
      return 1;
    }
    virtual void    Begin(TTree* tree);
    virtual void    SlaveBegin(TTree* tree);
    virtual void    Init(TTree* tree);
    virtual Bool_t  Notify();
    virtual Bool_t  Process(Long64_t entry);
    virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) {
      return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0;
    }
    virtual void    SetOption(const char* option) {
      fOption = option;
    }
    virtual void    SetObject(TObject* obj) {
      fObject = obj;
    }
    virtual void    SetInputList(TList* input) {
      fInput = input;
    }
    virtual TList*  GetOutputList() const {
      return fOutput;
    }
    virtual void    SlaveTerminate();
    virtual void    Terminate();

    void SetFairRunAnaProof(FairRunAnaProof* runAna) {
      fRunAna = runAna;
    }

  protected:
    /** Fair Logger */
    FairLogger*             fLogger;//!

  private:

    FairAnaSelector(const FairAnaSelector&);
    FairAnaSelector operator=(const FairAnaSelector&);

    FairFileSource* fProofSource;

    TString fCurrentDirectory;

    ClassDef(FairAnaSelector,0);
};

#endif //FAIRANASELECTOR_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairRadGridManager source file             -----
// -----          original author                  D.Bertini           -----
// -----          adapted april 2010               O.Hartmann          -----
// -------------------------------------------------------------------------
#ifndef FAIRRADGRIDMANAGER_H
#define FAIRRADGRIDMANAGER_H 1


#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Float_t, Double_t, Int_t, etc
#include "TLorentzVector.h"             // for TLorentzVector
#include "TObjArray.h"                  // for TObjArray

#include <iostream>                     // for basic_ostream::operator<<, etc

class FairMesh;
class TClonesArray;


/**
 * @class FairRadGridManager
 */


class FairRadGridManager
{

  public:
    /**
     * Default constructor.
     * Creates the singleton object of FairRadGridManager class.
     * The pointer to this object can be reached via FairRadGridManager::Instance().
     */
    FairRadGridManager();
    /**
     * Destructor.
     */
    virtual ~FairRadGridManager();

    /**
     * Class definition.
     */
    ClassDef(FairRadGridManager,1);


  private:

    FairRadGridManager(const FairRadGridManager&);
    FairRadGridManager& operator=(const FairRadGridManager&);

    static FairRadGridManager* fgInstance;

    /**
     * collection of point
     */
    TClonesArray*  fPointCollection;
    /**track index */
    Int_t          fTrackID;           //!
    /**volume id */
    Int_t          fVolumeID;          //!
    /**  entry position in global frame*/
    TLorentzVector fPosIn;             //!
    /**  exit position in global frame*/
    TLorentzVector fPosOut;            //!
    /**  momentum in*/
    TLorentzVector fMomIn;             //!
    /**  momentum out*/
    TLorentzVector fMomOut;            //!
    /**track time */
    Double_t       fTime;              //!
    /**track length */
    Double_t       fLength;            //!
    /** energy loss */
    Double_t       fELoss;             //!
    /** mass umber*/
    Float_t        fA;
    /** atomic number*/
    Float_t        fZmat;
    /**  density */
    Float_t        fDensity;
    /**radition length */
    Float_t        fRadl;
    /**absorption length */
    Float_t        fAbsl;
    /**estimator*/
    Int_t fEstimator;
    /** the mesh */
    TObjArray* fMeshList;

    static Double_t fLtmp;
  public:

    TObjArray* GetMeshList() { return fMeshList; }
    void AddMeshList ( TObjArray* list ) {
      std::cout << " grid manag " << list->GetEntriesFast() << std::endl;
      fMeshList = list;
    }
    Bool_t  IsTrackInside(TLorentzVector& vec, FairMesh* aMesh);
    Bool_t  IsTrackEntering(TLorentzVector& vec1,TLorentzVector& vec2);
    /** fill the 2D mesh */
    void FillMeshList();
    /**initialize the manager*/
    void  Init();
    /**reset*/
    void  Reset();
    /**
     * This function is used to access the methods of the class.
     * @return Pointer to the singleton FairRadGridManager object, created
     * with FairRadGridManager::FairRadGridManager().
     */
    static FairRadGridManager* Instance();
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
// -----                      FairRadLenManager source file             -----
// -----                  Created 14/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------
#ifndef FAIRRADLENMANAGER_H
#define FAIRRADLENMANAGER_H 1


#include "Rtypes.h"                     // for Float_t, Double_t, Int_t, etc
#include "TLorentzVector.h"             // for TLorentzVector

class TClonesArray;

/**
 * @class FairRadLenManager
 */


class FairRadLenManager
{

  public:
    /**
     * Default constructor.
     * Creates the singleton object of FairRadLenManager class.
     * The pointer to this object can be reached via FairRadLenManager::Instance().
     */
    FairRadLenManager();

    /**
     * Destructor.
     */
    virtual ~FairRadLenManager();

    /**
     * Class definition.
     */
    ClassDef(FairRadLenManager,1);


  private:

    FairRadLenManager(const FairRadLenManager&);
    FairRadLenManager& operator=(const FairRadLenManager&);

    static FairRadLenManager* fgInstance;

    /**
     * collection of point
     */
    TClonesArray*  fPointCollection;
    /**track index */
    Int_t          fTrackID;           //!
    /**volume id */
    Int_t          fVolumeID;          //!
    /**  entry position in global frame*/
    TLorentzVector fPosIn;             //!
    /**  exit position in global frame*/
    TLorentzVector fPosOut;            //!
    /**  momentum in*/
    TLorentzVector fMomIn;             //!
    /**  momentum out*/
    TLorentzVector fMomOut;            //!
    /**track time */
    Double_t       fTime;                //!
    /**track length */
    Double_t       fLength;              //!
    /** energy loss */
    Double_t       fELoss;               //!
    /** mass umber*/
    Float_t        fA;
    /** atomic number*/
    Float_t        fZmat;
    /**  density */
    Float_t        fDensity;
    /**radition length */
    Float_t        fRadl;
    /**absorption length */
    Float_t        fAbsl;

  public:
    /**Add point to collection*/
    void  AddPoint(Int_t& ModuleId);
    /**initialize the manager*/
    void  Init();
    /**reset*/
    void  Reset();
    /**
     * This function is used to access the methods of the class.
     * @return Pointer to the singleton FairRadLenManager object, created
     * with FairRadLenManager::FairRadLenManager().
     */
    static FairRadLenManager* Instance();
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
// -----                      FairRadMapManager source file            -----
// -------------------------------------------------------------------------
#ifndef FAIRRADMAPMANAGER_H
#define FAIRRADMAPMANAGER_H 1

#include "Rtypes.h"                     // for Double_t, Float_t, Int_t, etc
#include "TLorentzVector.h"             // for TLorentzVector

class TClonesArray;
class TMap;

/**
 * @class FairRadMapManager
 */


class FairRadMapManager
{

  public:
    /**
     * Default constructor.
     * Creates the singleton object of FairRadMapManager class.
     * The pointer to this object can be reached via FairRadMapManager::Instance().
     */
    FairRadMapManager();

    /**
     * Destructor.
     */
    virtual ~FairRadMapManager();

    /**
     * Class definition.
     */
    ClassDef(FairRadMapManager,1);


  private:

    FairRadMapManager(const FairRadMapManager&);
    FairRadMapManager& operator=(const FairRadMapManager&);

    static FairRadMapManager* fgInstance;

    /**
     * collection of point
     */
    TClonesArray*  fPointCollection;
    /**track index */
    Int_t          fTrackID;           //!
    /**volume id */
    Int_t          fVolumeID;          //!
    /** pid */
    Int_t          fPdg;                //!
    /**  entry position in global frame*/
    TLorentzVector fPosIn;             //!
    /**  exit position in global frame*/
    TLorentzVector fPosOut;            //!
    /**  momentum in*/
    TLorentzVector fMomIn;             //!
    /**  momentum out*/
    TLorentzVector fMomOut;            //!
    /**track time */
    Double_t       fTime;                //!
    /**track length */
    Double_t       fLength;              //!
    /**track setp */
    Double_t       fStep;
    /** energy loss */
    Double_t       fELoss;               //!
    /**dose */
    Double_t        fDose;
    Double_t       fDoseSL;
    /** mass umber*/
    Float_t        fA;
    /** atomic number*/
    Float_t        fZmat;
    /** radiation length*/
    Float_t        fRadl;
    /**  density */
    Float_t        fDensity;
    /**absorption length */
    Float_t        fAbsl;
    //**volume, mass */
    Double_t       fActVol;
    Double_t       fActMass;

    TMap* fMassMap;


  public:
    /**Add point to collection*/
    void  AddPoint(Int_t& ModuleId);
    /**initialize the manager*/
    void  Init();
    /**reset*/
    void  Reset();
    /**
     * This function is used to access the methods of the class.
     * @return Pointer to the singleton FairRadMapManager object, created
     * with FairRadMapManager::FairRadMapManager().
     */
    static FairRadMapManager* Instance();
    //  void GetGeoManager();
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
 * FairRingSorter.h
 *
 *  Created on: Jul 15, 2010
 *      Author: stockman
 */

#ifndef FairRingSorter_H_
#define FairRingSorter_H_


#include "TObject.h"                    // for TObject

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for FairRingSorter::Class, etc

#include <iostream>                     // for operator<<, ostream, etc
#include <map>                          // for multimap
#include <utility>                      // for pair
#include <vector>                       // for vector

class FairTimeStamp;

class FairRingSorter : public TObject
{
  public:
    FairRingSorter(int size = 100, double width = 10)
      : TObject(), fRingBuffer(size), fOutputData(), fLowerBoundPointer(0,0),
        fCellWidth(width), fVerbose(0) {
    }

    virtual ~FairRingSorter() {};

    virtual FairTimeStamp* CreateElement(FairTimeStamp* data);

    virtual void AddElement(FairTimeStamp* digi, double timestamp);
    virtual void WriteOutElements(int index);       ///< writes out the entries from LowerBoundPointer up to index
    virtual void WriteOutElement(int index);          ///< writes out the entry at the index and clears it
    virtual void WriteOutAll() {
      WriteOutElements(fLowerBoundPointer.first);
    }
    virtual double GetBufferSize() {return fCellWidth * fRingBuffer.size();}
    virtual std::vector<FairTimeStamp*> GetOutputData() {
      return fOutputData;
    }

    virtual void DeleteOutputData() {fOutputData.clear(); }
    virtual void SetLowerBound(double timestampOfHitToWrite);

    virtual void print(std::ostream& out = std::cout) {
      out << "RingSorter: Size " << fRingBuffer.size() << " CellWidth: " << fCellWidth << std::endl;
      out << "LowerBoundPointer at index: " << fLowerBoundPointer.first << " Time: " << fLowerBoundPointer.second << std::endl;
      out << "| ";
      for (unsigned int i = 0; i < fRingBuffer.size(); i++) {
        out << fRingBuffer[i].size() << " |";
      }
      out << std::endl;
    }


  private:
    int CalcIndex(double val);
    std::vector<std::multimap<double, FairTimeStamp*> > fRingBuffer;
    std::vector<FairTimeStamp*> fOutputData;
    std::pair<int, double> fLowerBoundPointer;
    double fCellWidth;
    int fVerbose;

    ClassDef(FairRingSorter,1)

};

#endif /* FairRingSorter_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/** FairRingSorterTask.h
 **
 **/

#ifndef FairRingSorterTask_H
#define FairRingSorterTask_H

#include "FairTask.h"                   // for FairTask, InitStatus

#include "FairRingSorter.h"             // for FairRingSorter

#include "Rtypes.h"                     // for Bool_t, Int_t, kTRUE, etc
#include "TString.h"                    // for TString

class FairTimeStamp;
class TClonesArray;

class FairRingSorterTask : public FairTask
{
  public:

    /** Default constructor **/
    FairRingSorterTask():
      FairTask("SorterTask"),
      fSorter(0),
      fPersistance(kTRUE),
      fDigiPixelMCInfo(kFALSE),
      fNumberOfCells(1000),
      fWidthOfCells(10),
      fInputBranch(),
      fInputArray(0),
      fOutputBranch(),
      fFolder(),
      fOutputArray(0),
      fEntryNr(0) {
      SetVerbose(0);
    }

    /** Named constructor **/
    FairRingSorterTask(const char* name):
      FairTask(name),
      fSorter(0),
      fPersistance(kTRUE),
      fDigiPixelMCInfo(kFALSE),
      fNumberOfCells(1000),
      fWidthOfCells(10),
      fInputBranch(),
      fInputArray(0),
      fOutputBranch(),
      fFolder(),
      fOutputArray(0),
      fEntryNr(0) {
      SetVerbose(0);
    }

    FairRingSorterTask(Int_t numberOfCells, Double_t widthOfCells, TString inputBranch, TString outputBranch, TString folderName):
      FairTask("Sorter"),
      fSorter(0),
      fPersistance(kTRUE),
      fDigiPixelMCInfo(kFALSE),
      fNumberOfCells(numberOfCells),
      fWidthOfCells(widthOfCells),
      fInputBranch(inputBranch),
      fInputArray(0),
      fOutputBranch(outputBranch),
      fFolder(folderName),
      fOutputArray(0),
      fEntryNr(0) {
      SetVerbose(0);
    }

    /** Destructor **/
    virtual ~FairRingSorterTask() {
      if (fSorter!= 0) { delete fSorter; }
    }

    /** Virtual method Init **/
    virtual InitStatus Init();
    virtual InitStatus ReInit();

    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);
    virtual void FinishEvent();
    virtual void FinishTask();

    virtual void SetParContainers() {};

    void SetPersistance(Bool_t p = kTRUE) {fPersistance=p;};
    Bool_t GetPersistance() {return fPersistance;};

    virtual void AddNewDataToTClonesArray(FairTimeStamp* data);
    virtual FairRingSorter* InitSorter(Int_t numberOfCells, Double_t widthOfCells) const;

  protected:

    FairRingSorter* fSorter;
    /** switch to turn on/off storing the arrays to a file*/
    Bool_t fPersistance;
    /** switch to turn on/off storing additional MC Info of Digis*/
    Bool_t fDigiPixelMCInfo;
    Int_t fNumberOfCells;
    Double_t fWidthOfCells; // in ns
    /** Input array of PndSdsPixelDigis **/
    TString fInputBranch;
    TClonesArray* fInputArray;
    /** Output array of sorted PndSdsDigis **/
    TString fOutputBranch;
    TString fFolder;
    TClonesArray* fOutputArray;
    Int_t fEntryNr;
    FairRingSorterTask(const FairRingSorterTask&);
    FairRingSorterTask& operator=(const FairRingSorterTask&);

    ClassDef(FairRingSorterTask,2);

};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIR_ROOT_MANAGER_H
#define FAIR_ROOT_MANAGER_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Bool_t, Int_t, UInt_t, etc
#include "TChain.h"                     // for TChain
#include "TFile.h"                      // for TFile
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString, operator<
#include "TMCtls.h"                     // for multi-threading

#include <stddef.h>                     // for NULL
#include <list>                         // for list
#include <map>                          // for map, multimap, etc
#include <queue>                        // for queue
#include "FairSource.h"
class BinaryFunctor;
class FairEventHeader;
class FairFileHeader;
class FairGeoNode;
class FairLink;
class FairLogger;
class FairTSBufferFunctional;
class FairWriteoutBuffer;
class TArrayI;
class TBranch;
class TClonesArray;
class TCollection;
class TF1;
class TFolder;
class TList;
class TNamed;
class TTree;
class TRefArray;
class TIterator;

/**
 * I/O Manager class
 * @author M. Al-Turany, Denis Bertini
 * @version 0.1
 * @since 12.01.04
 */

//_____________________________________________________________________

class FairRootManager : public TObject
{
  public:
    /**ctor*/
    FairRootManager();
    /**dtor*/
    virtual ~FairRootManager();
     Bool_t             AllDataProcessed();
    /** Add a branch name to the Branchlist and give it an id*/
    Int_t AddBranchToList(const char* name);
    /**
    Check if Branch persistence or not (Memory branch)
    return value:
    1 : Branch is Persistance
    2 : Memory Branch
    0 : Branch does not exist   */
    Int_t               CheckBranch(const char* BrName);

    
    void                CloseOutFile() { if(fOutFile) { fOutFile->Close(); }}
    /**Create a new file and save the current TGeoManager object to it*/
    void                CreateGeometryFile(const char* geofile);
    void                Fill();
    void                LastFill();
    TClonesArray*       GetEmptyTClonesArray(TString branchName);
    TClonesArray*       GetTClonesArray(TString branchName);
    /**Update the list of Memory branches from the source used*/
    void                UpdateBranches();

    /**Return branch name by Id*/
    TString             GetBranchName(Int_t id);
    /**Return Id of a branch named */
    Int_t               GetBranchId(TString BrName);
    /**Return a TList of TObjString of branch names available in this session*/
    TList*              GetBranchNameList() {return fBranchNameList;}
    /** Return a pointer to the output Tree of type TTree */
    TTree*              GetOutTree() {return fOutTree;}
    /** Return a pointer to the output File of type TFile */
    TFile*              GetOutFile() {return  fOutFile;}
    /**  Get the Object (container) for the given branch name,
         this method can be used to access the data of
         a branch that was created from a different
         analysis task, and not written in the tree yet.
         the user have to cast this pointer to the right type.
         Return a pointer to the object (collection) saved in the fInChain branch named BrName*/
    TObject*            GetObject(const char* BrName);
    /** Return a pointer to the object (collection) saved in the fInTree branch named BrName*/
    Double_t            GetEventTime();
    /** Returns a clone of the data object the link is pointing to. The clone has to be deleted in the calling code! */
    TObject*      GetCloneOfLinkData(const FairLink link);
    /** Get the data of the given branch name,
     *  this method runs over multiple entries
     *  of the tree and selects the data according
     *  to the function and the parameter given.
     */

    TClonesArray* GetCloneOfTClonesArray(const FairLink link);

    void InitTSBuffer(TString branchName, BinaryFunctor* function);
    TClonesArray*     GetData(TString branchName, BinaryFunctor* function, Double_t parameter);
    TClonesArray*     GetData(TString branchName, BinaryFunctor* startFunction, Double_t startParameter, BinaryFunctor* stopFunction, Double_t stopParameter);
    void RegisterTSBuffer(TString branchName, FairTSBufferFunctional* functionalBuffer) {fTSBufferMap[branchName] = functionalBuffer;}
    void TerminateTSBuffer(TString branchName);
    void TerminateAllTSBuffer();
    FairTSBufferFunctional*   GetTSBuffer(TString branchName) {return fTSBufferMap[branchName];}

    /** static access method */
    static FairRootManager* Instance();

    TFile*            OpenOutFile(const char* fname="cbmsim.root");
    TFile*            OpenOutFile(TFile* f);
    /**Read a single entry from background chain*/
    Int_t             ReadEvent(Int_t i=0);
    /** Read a single entry from each branch that is not read via TSBuffers*/
    Int_t             ReadNonTimeBasedEventFromBranches(Int_t i=0);
    /**Read the tree entry on one branch**/
    void              ReadBranchEvent(const char* BrName);
    /**Read all entries from input tree(s) with time stamp from current time to dt (time in ns)*/

    Int_t             GetRunId();

    Bool_t            ReadNextEvent(Double_t dt);
    /**create a new branch in the output tree
     *@param name            Name of the branch to create
     *@param Foldername      Folder name containing this branch (e.g Detector name)
     *@param obj             Pointer of type TNamed (e.g. MCStack object)
     *@param toFile          if kTRUE, branch will be saved to the tree*/
    void                Register(const char* name, const char* Foldername, TNamed* obj, Bool_t toFile);
    /**create a new branch in the output tree
    *@param name            Name of the branch to create
    *@param Foldername      Folder name containing this branch (e.g Detector name)
    *@param obj             Pointer of type TCollection (e.g. TClonesArray of hits, points)
    *@param toFile          if kTRUE, branch will be saved to the tree*/
    void                Register(const char* name,const char* Foldername ,TCollection* obj, Bool_t toFile);

    TClonesArray*       Register(TString branchName, TString className, TString folderName, Bool_t toFile);
    /** Register a new FairWriteoutBuffer to the map. If a Buffer with the same map key already exists the given buffer will be deleted and the old will be returned!*/
    FairWriteoutBuffer* RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer);
    /**Update the list of time based branches in the output file*/
    void                UpdateListOfTimebasedBranches();
    /**Use time stamps to read data and not tree entries*/
    void                RunWithTimeStamps() {fTimeStamps = kTRUE;}

    /**Set the branch name list*/
    void                SetBranchNameList(TList* list);
    /** Replace the time based branch name list*/
    void SetTimeBasedBranchNameList(TList *list);
  
    void                FillEventHeader(FairEventHeader* feh) { if ( fSource ) fSource->FillEventHeader(feh); } 
   
    /**Set the output tree pointer*/
    void                SetOutTree(TTree* fTree) { fOutTree=fTree;}

    /**Enables a last Fill command after all events are processed to store any data which is still in Buffers*/
    void        SetLastFill(Bool_t val = kTRUE) { fFillLastData=val;}
    /**When creating TTree from TFolder the fullpath of the objects is used as branch names
     * this method truncate the full path from the branch names
    */
    void                TruncateBranchNames(TBranch* b, TString ffn);
    /**When creating TTree from TFolder the fullpath of the objects is used as branch names
     * this method truncate the full path from the branch names
    */
    void                TruncateBranchNames(TTree* fTree, const char* folderName);

    Int_t               Write(const char* name=0, Int_t option=0, Int_t bufsize=0);
    /** Write the current TGeoManager to file*/
    void                WriteGeometry();
    /**Write the file header object to the output file*/
    void                WriteFileHeader(FairFileHeader* f);
    /**Write the folder structure used to create the tree to the output file */
    void                WriteFolder() ;

    /**Check the maximum event number we can run to*/
    Int_t  CheckMaxEventNo(Int_t EvtEnd=0);


    void        StoreWriteoutBufferData(Double_t eventTime);
    void        StoreAllWriteoutBufferData();
    void    DeleteOldWriteoutBufferData();

    Int_t GetEntryNr() {return fEntryNr;}
    void SetEntryNr(Int_t val) {fEntryNr = val;}

    void SetUseFairLinks(Bool_t val) {fUseFairLinks = val;};
    Bool_t GetUseFairLinks() const {return fUseFairLinks;};

    /**
     * @param Status : if  true all inputs are mixed, i.e: each read event will take one entry from each input and put
     * them in one big event and send it to the next step
     */
    /* void SetMixAllInputs(Bool_t Status) { */
    /*    fMixAllInputs=kTRUE; */
    /* } */
   
    
    /** These methods have been moved to the FairFileSource */
    void   SetSource(FairSource* tempSource) { fSource = tempSource; }    
    FairSource* GetSource() { return fSource;}
    Bool_t InitSource();
    
    void                SetListOfFolders(TObjArray* ta){ fListFolder=ta; }
    TChain*             GetInChain ()                  { return fSourceChain;}
    TChain*             GetSignalChainNo(UInt_t i)     { return fSignalChainList[i]; }
    TTree*              GetInTree  ()                  { if ( fSourceChain ) return fSourceChain->GetTree(); return 0; }
    const TFile*        GetRootFile()                  { if ( fSourceChain ) return fSourceChain->GetFile(); return 0; }
    TFile*              GetInFile  ()                  { if ( fSourceChain ) return fSourceChain->GetFile(); return 0; }
    void                SetInChain (TChain* tempChain, Int_t ident=-1);
    /* /\**Set the input tree when running on PROOF worker*\/ */

    void SetFinishRun(Bool_t val = kTRUE){ fFinishRun = val;}
    Bool_t FinishRun() {return fFinishRun;}

    static char* GetTreeName();
  private:
    /**private methods*/
    FairRootManager(const FairRootManager&);
    FairRootManager& operator=(const FairRootManager&);
    /**  Set the branch address for a given branch name and return
        a TObject pointer, the user have to cast this pointer to the right type.*/
    TObject*            ActivateBranch(const char* BrName);
    void                AddFriends( );
    /**Add a branch to memory, it will not be written to the output files*/
    void                AddMemoryBranch(const char*, TObject* );
    /** Internal Check if Branch persistence or not (Memory branch)
    return value:
    1 : Branch is Persistance
    2 : Memory Branch
    0 : Branch does not exist
    */
    Int_t               CheckBranchSt(const char* BrName);
        /**Create the Map for the branch persistency status  */
    void                CreatePerMap();
    TObject*            GetMemoryBranch( const char* );
 //   void                GetRunIdInfo(TString fileName, TString inputLevel);

    FairWriteoutBuffer* GetWriteoutBuffer(TString branchName);


    Int_t       fOldEntryNr;
//_____________________________________________________________________
    /**private Members*/
    /**folder structure of output*/
    TFolder*                            fCbmout;
    /**folder structure of input*/
    TFolder*                            fCbmroot;
    /** current time in ns*/
    Double_t                            fCurrentTime;
    /**Output file */
    TFile*                              fOutFile;
    /**Output tree */
    TTree*                              fOutTree;
    TObject**                           fObj2; //!
    /** Counter for the number of branches activiated */
    Int_t                               fNObj;//!
    /** A list which hold the pointer to the branch 
     * and the name of the branch in memory, it contains all branches (TClonesArrays)
     * persistance and Memory only branches
     */
    std::map < TString , TObject* >     fMap;  //!

    /**Singleton instance*/
#if !defined(__CINT__)
    static TMCThreadLocal FairRootManager*  fgInstance;
#else
    static                FairRootManager*  fgInstance;
#endif

    /**Branch id for this run */
    Int_t                               fBranchSeqId;
    /**List of branch names as TObjString*/
    TList*                               fBranchNameList; //!
    /**List of Time based branchs names as TObjString*/
    TList*                               fTimeBasedBranchNameList; //!
    /** Internally used to compress empty slots in data buffer*/
    std::map<TString, TClonesArray*> fActiveContainer;
    /** Internally used to read time ordered data from branches*/
    std::map<TString, FairTSBufferFunctional*> fTSBufferMap; //!
    std::map<TString, FairWriteoutBuffer* > fWriteoutBufferMap; //!
    std::map<Int_t, TBranch*> fInputBranchMap; //!    //Map of input branch ID with TBranch pointer
    /**if kTRUE Read data according to time and not entries*/
    Bool_t                              fTimeStamps;
    /**Flag for creation of Map for branch persistency list  */
    Bool_t                              fBranchPerMap;
    /** Map for branch persistency list */
    std::map < TString , Int_t >        fBrPerMap; //!
    /**Iterator for the fBrPerMap  Map*/
    std::map < TString, Int_t>::iterator     fBrPerMapIter;
 
    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fCurrentEntryNo; //!
    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fTimeforEntryNo; //!
    Bool_t  fFillLastData; //!
    Int_t fEntryNr; //!

    TObjArray                           *fListFolder; //!

    FairSource                          *fSource;

    TChain                              *fSourceChain;
    std::map<UInt_t, TChain*>            fSignalChainList;//!

    FairEventHeader                     *fEventHeader;
    
    Bool_t fUseFairLinks; //!
    Bool_t fFinishRun; //!
    /** List of branches from input Chain or Tree*/
    TObjArray* fListOfBranchesFromInput; //!
    /** Iterator for the list of branches from input Chain or Tree */
    TIterator* fListOfBranchesFromInputIter;//!
    /** List of branches used with no-time stamp in time-based session */
    TRefArray* fListOfNonTimebasedBranches; //!
    /** Iterator for the list of branches used with no-time stamp in time-based session */
    TIterator* fListOfNonTimebasedBranchesIter; //!

    ClassDef(FairRootManager,11) // Root IO manager
};


#endif //FAIR_ROOT_MANAGER_H   


/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUN_H
#define FAIRRUN_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "TMCtls.h"                     // for multi-threading

class FairEventHeader;
class FairFileHeader;
class FairRootManager;
class FairRuntimeDb;
class FairTask;
class TFile;
class FairField;

/**
 * Configure the Simuation or Analysis
 * @author M. Al-Turany  D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class FairRun : public TNamed
{
  public:
    /**
     * default ctor
     */
    FairRun(Bool_t isMaster = kTRUE);
    /**
    * default dtor
    */
    virtual ~FairRun();
    /**
     * static instance
     */
    static FairRun* Instance();
    /**
     * Add a FAIRTask to the simulation or analysis
     */
    virtual void       AddTask(FairTask* t);
    virtual void       SetTask(FairTask* t);
    /**
     * Initialize the Simulation or analysis
     */
    virtual void    Init()=0;
    /*
     * Get the magnetic field *
     */
    virtual FairField*  GetField()=0;
    /**
      * run the analysis or simulation
     */
    virtual void    Run(Int_t NStart =0,Int_t NStop=0)=0;
    /**
     * Set the output file name for analysis or simulation
    */
    virtual void    SetOutputFile(const char* fname);
    /**
     * Set the output file for analysis or simulation
    */
    virtual void    SetOutputFile(TFile* f);
    /**
     *       Set the experiment dependent run header
     *       for each run
     */
    void        SetEventHeader(FairEventHeader* EvHeader)  {
      fEvtHeader=EvHeader;
    }
    /**
     * return a pointer to the RuntimeDB
     */
    FairRuntimeDb* GetRuntimeDb(void) {
      return fRtdb;
    }
    /**
     * return a pointer to the output file
     */
    TFile* GetOutputFile() {
      return fOutFile;
    }
    /**
     * return the run ID for the actul run
     */
    Int_t  GetRunId() {
      return (static_cast<Int_t>(fRunId));
    }

	/** 
     * Set the Run ID
	 */
    void SetRunId(UInt_t runId)
	{
	  fRunId = runId; 
    }    

    /**Get the detector specific run header*/
    FairEventHeader*  GetEventHeader();
    /**
    * return true for Anaylsis session
    */
    Bool_t            IsAna() {
      return fAna;
    }
    /**
    *Get task by name
    */

    FairTask* GetTask(const char* taskName);
    /**
    *Get Main Task
    */
    FairTask* GetMainTask() {
      return fTask;
    }
    /**
    * Return the number of Tasks added to this Run
    */
    Int_t     GetNTasks() {
      return fNTasks;
    }

    /**Create a new file and save the TGeoManager to it*/
    void CreateGeometryFile(const char* geofile);

    //** Set if RunInfo file should be written */
    void SetWriteRunInfoFile(Bool_t write);

    //** Set if RunInfo should be generated */
    void SetGenerateRunInfo(Bool_t write) { fGenerateRunInfo = write;}

    //** Get info if RunInfo file is written */
    Bool_t GetWriteRunInfoFile();

    //** Get info if RunInfo file is written */
    Bool_t IsRunInfoGenerated() { return fGenerateRunInfo;}

    //** Switches the use of FairLinks */
    void SetUseFairLinks(Bool_t val);

    //** Get info if run on master */
    Bool_t GetIsMaster() const { return fIsMaster;}

    //** Mark/Unmark event to be filled into output. Default is TRUE. */
    void MarkFill(Bool_t flag) { fMarkFill = flag; }


  private:
    FairRun(const FairRun& M);
    FairRun& operator= (const  FairRun&) {
      return *this;
    }
    /** Number of Tasks added*/
    Int_t fNTasks;

  protected:
    /** static pointer to this run*/
#if !defined(__CINT__)
    static TMCThreadLocal FairRun* fRunInstance;
#else
    static                FairRun* fRunInstance;
#endif
    /** RuntimeDb*/
    FairRuntimeDb*           fRtdb;
    /** Tasks used*/
    FairTask*                fTask;
    /**Output file name*/
    const char*              fOutname;
    /**IO manager */
    FairRootManager*         fRootManager;
    /**Output file*/
    TFile*                   fOutFile;
    /**Run Id*/
    UInt_t                   fRunId;//!
    /** true for Anaylsis session*/
    Bool_t                   fAna;  //!
    /** MC Event Header */
    FairEventHeader*         fEvtHeader; //!
    /** File  Header */
    FairFileHeader*          fFileHeader;
    /** true if RunInfo file should be written*/
    Bool_t                   fGenerateRunInfo;  //!
    /** true if on master*/
    Bool_t                   fIsMaster;  //!

    Bool_t                   fMarkFill; //!

    ClassDef(FairRun ,4)
};
#endif //FAIRRUN_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNANA_H
#define FAIRRUNANA_H


/**
 * Configure and manage the  Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "FairRun.h"                    // for FairRun

#include "FairRootManager.h"            // for FairRootManager
#include "FairRunInfo.h"                // for FairRunInfo

#include "Rtypes.h"                     // for Bool_t, Double_t, UInt_t, etc
#include "TString.h"                    // for TString

class FairField;
class TF1;
class TFile;
class TTree;

class FairFileSource;
class FairMixedSource;

class FairRunAna : public FairRun
{

  public:

    static FairRunAna* Instance();
    virtual ~FairRunAna();
    FairRunAna();
    /**initialize the run manager*/
    void        Init();
    /**Run from event number NStart to event number NStop */
    void        Run(Int_t NStart=0 ,Int_t NStop=0);
    /**Run over the whole input file with timpe window delta_t as unit (entry)*/
    void        Run(Double_t delta_t);
    /**Run for the given single entry*/
    void        Run(Long64_t entry);
    /**Run event reconstruction from event number NStart to event number NStop */
    void        RunEventReco(Int_t NStart ,Int_t NStop);
    /**Run over all TSBuffers until the data is processed*/
    void        RunTSBuffers();
    /** the dummy run does not check the evt header or the parameters!! */
    void        DummyRun(Int_t NStart ,Int_t NStop);
    /** This methode is only needed and used with ZeroMQ
      * it read a certain event and call the task exec, but no output is written
      * @param entry : entry number in the tree
      */
    void RunMQ(Long64_t entry);
    /** Run on a list of lmd files*/
    void        RunOnLmdFiles(UInt_t NStart=0, UInt_t NStop=0);

    void RunOnTBData();
    /** finish tasks, write output*/
    void        TerminateRun();
    /**Set the input signal file
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file
     */

    virtual void   SetSource(FairSource* tempSource) { fRootManager->SetSource(tempSource); }

    // ********************************************************* //
    // THE BELOW FUNCTIONS SHOULD BE MOVED TO FairFileSource
    /**Set the input file by name*/
    void        SetInputFile(TString fname);
    /**Add a file to input chain */
    void        AddFile(TString name);
    /** Add a friend file (input) by name)*/
    void        AddFriend(TString fName);
    // ********************************************************* //
    // THE BELOW FUNCTIONS SHOULD BE MOVED TO FairMixedSource
    void        SetSignalFile(TString name, UInt_t identifier );
    /**Add signal file to input
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file to which this signal should be added
     */
    void        AddSignalFile(TString name, UInt_t identifier );
    /**Set the input background file by name*/
    void        SetBackgroundFile(TString name);
    /**Add input background file by name*/
    void        AddBackgroundFile(TString name);
    /**Set the signal to background ratio in event units
     *@param background :  Number of background Events for one signal
     *@param Signalid :    Signal file Id, used when adding (setting) the signal file
     * here we just forward the call to the FairRootManager
     */
    void BGWindowWidthNo(UInt_t background, UInt_t Signalid);
    /**Set the signal to background rate in time units
     *@param background :  Time of background Events before one signal
     *@param Signalid :    Signal file Id, used when adding (setting) the signal file
     * here we just forward the call to the FairRootManager
     */
    void BGWindowWidthTime(Double_t background, UInt_t Signalid);
    /**
     * This method will simply forward the call to the FairRootManager, 
     * if  true all inputs are mixed, i.e: each read event will take one entry from each input and put
     * them in one big event and send it to the next step
    */
    //    void SetMixAllInputs(Bool_t Status);
    // ********************************************************* //
    // THE BELOW FUNCTIONS SHOULD BE MOVED TO FairFileSource and FairMixedSource
    /** Set the min and max limit for event time in ns */
    void SetEventTimeInterval(Double_t min, Double_t max);
    /** Set the mean time for the event in ns */
    void SetEventMeanTime(Double_t mean);
    /** Set the time intervall the beam is interacting and the gap in ns */
    void SetBeamTime(Double_t beamTime, Double_t gapTime);
    // ********************************************************* //
 
    void        Reinit(UInt_t runId);
    UInt_t      getRunId() {
      return fRunId;
    }
    /** Get the magnetic field **/
    FairField*  GetField() {
      return fField;
    }
    /** Set the magnetic Field */
    void        SetField (FairField* ffield ) {
      fField=ffield ;
    }
    /** Set external geometry file */
    void        SetGeomFile(const char* GeoFileName);
    /** Return a pointer to the geometry file */
    TFile*      GetGeoFile() {
      return fInputGeoFile;
    }
    /** Initialization of parameter container is set to static, i.e: the run id is
     *  is not checked anymore after initialization
     */

    void        SetContainerStatic(Bool_t tempBool=kTRUE);
    Bool_t      GetContainerStatic() { return fStatic; };
    void        RunWithTimeStamps();
    Bool_t      IsTimeStamp() {
      return fTimeStamps;
    }

    /** Set the flag for proccessing lmd files */
    void StopProcessingLMD( void ) {
      fFinishProcessingLMDFile = kTRUE;
    }
    /** Get the status of lmd file proccessing */
    Bool_t GetLMDProcessingStatus( void ) {
      return fFinishProcessingLMDFile;
    }

  protected:
    /**
     * Virtual function which calls the Fill function of the IOManager.
     * Allows to override the function with an experiment specific version.
    **/
    virtual void Fill();
                                               
  private:

    FairRunAna(const FairRunAna& M);
    FairRunAna& operator= (const  FairRunAna&) {
      return *this;
    }

    FairRunInfo fRunInfo;//!

  protected:
    /** This variable became true after Init is called*/
    Bool_t                                  fIsInitialized;
    TFile*                                  fInputGeoFile;
    static FairRunAna*                      fgRinstance;
    Bool_t                                  fLoadGeo;
    /** true for static initialisation of parameters */
    Bool_t                                  fStatic;//!
    FairField*                              fField;
    Bool_t                                  fTimeStamps;
    Bool_t                                  fInFileIsOpen;//!
    /** min time for one event (ns) */
    Double_t                                fEventTimeMin;  //!
    /** max time for one Event (ns) */
    Double_t                                fEventTimeMax;  //!
    /** Time of event since th start (ns) */
    Double_t                                fEventTime;     //!
    /** EventMean time used (P(t)=1/fEventMeanTime*Exp(-t/fEventMeanTime) */
    Double_t                                fEventMeanTime; //!
    /** used to generate random numbers for event time; */
    TF1*                                    fTimeProb;      //!
    /** Flag for proccessing lmd-files*/
    Bool_t                                  fFinishProcessingLMDFile;  //!

    /** Temporary member to preserve old functionality without setting source in macro */
    FairFileSource*                         fFileSource;  //! 
    /** Temporary member to preserve old functionality without setting source in macro */
    FairMixedSource*                        fMixedSource; //! 

    ClassDef(FairRunAna ,6)

};

#endif //FAIRRUNANA_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNANAPROOF_H
#define FAIRRUNANAPROOF_H

/**
 * Configure and manage the  Analysis on proof
 * @author R. Karabowicz
 * @version 0.1
 * @since 30.04.2013
 */

#include "FairRunAna.h"

#include "FairFileSource.h" // FairRunAnaProof can only accept FairFileSource as source
#include "TProof.h"

class FairRunAnaProof : public FairRunAna
{

  public:

    static FairRunAnaProof* Instance();
    virtual ~FairRunAnaProof();
    FairRunAnaProof(const char* proofName="");

    /**initialize the run manager*/
    void        Init();

    /** Init containers executed on PROOF, which is part of Init when running locally*/
    void        InitContainers();

    /**
     * Set the output file name for analysis or simulation
    */
    virtual void    SetOutputFile(const char* fname);
    /**
     * Set the output file for analysis or simulation
    */
    virtual void    SetOutputFile(TFile* f);

    /**Run from event number NStart to event number NStop */
    void        Run(Int_t NStart=0 ,Int_t NStop=0);
    /**Run for one event, used on PROOF nodes*/
    void        RunOneEvent(Long64_t entry);
    /**Run on proof from event NStart to event NStop*/
    void        RunOnProof(Int_t NStart, Int_t NStop);

    /** set the input tree of fRootManager when running on PROOF worker*/
    /* void        SetInTree (TTree* tempTree)   { */
    /*   fRootManager->SetInTree (tempTree); */
    /* } */

    /** GetProof */
    TProof* GetProof() {
      return fProof;
    }

    /** To be set to kTRUE only when running on PROOF worker, only by TSelector */
    void SetRunOnProofWorker(Bool_t tb = kTRUE) {
      fRunOnProofWorker = tb;
    }
    /** Set PROOF ARchive (PAR) file name*/
    void SetProofParName(TString parName) {
      fProofParName = parName;
    }
    /** Set directory for storing output files*/
    void SetOutputDirectory(TString dirName) {
      fOutputDirectory = dirName;
    }
    /** Set PROOF output status, possibilities: "copy","merge"*/
    void SetProofOutputStatus(TString outStat) {
      fProofOutputStatus = outStat;
    }

    virtual void   SetSource(FairSource* tempSource);

  protected:
    static FairRunAnaProof*                 fRAPInstance;

    /** PROOF **/
    TProof*                                 fProof;
    /** executing on PROOF worker*/
    Bool_t                                  fRunOnProofWorker; //!
    /** PROOF server name*/
    TString                                 fProofServerName; //!
    /** PROOF ARchive (PAR) file name*/
    TString                                 fProofParName; //!
    /** Output directory*/
    TString                                 fOutputDirectory; //!
    /** Output status indicator: "copy","merge","dataset"*/
    TString                                  fProofOutputStatus;

  private:
  
    FairRunAnaProof(const FairRunAnaProof&);
    FairRunAnaProof operator=(const FairRunAnaProof&);

    FairFileSource* fProofFileSource;
    
    ClassDef(FairRunAnaProof ,1)

};

#endif //FAIRRUNANAPROOF_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNSIM_H
#define FAIRRUNSIM_H

#include "FairRun.h"                    // for FairRun

#include "FairIon.h"                    // for FairIon
#include "FairMCApplication.h"          // for FairMCApplication
#include "FairParticle.h"               // for FairParticle

#include "Rtypes.h"                     // for Bool_t, Double_t, Int_t, etc
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString
#include "TMCtls.h"                     // for multi-threading

class FairField;
class FairMCEventHeader;
class FairMesh;
class FairModule;
class FairPrimaryGenerator;

/**
 * Configure the Simulation session
 * @author M. Al-Turany  D. Bertini
 * @version 0.1
 * @since 12.01.04
 */
class FairRunSim : public FairRun
{
  public:
    /** default ctor*/
    FairRunSim(Bool_t isMaster = kTRUE);
    /** default dtor*/
    virtual ~FairRunSim();
    /** Singelton instance*/
    static FairRunSim* Instance();
    /**
     *       Add a module to the simulation (e.g. PIPE, Magnet, ..etc)
    */
    void        AddModule  (FairModule* Mod);
    /**
     *       Add a user defined ion to the simulation
    */
    void        AddNewIon(FairIon* ion) {fIons->Add(ion);}
    /**
     *       Add a user defined ion to the simulation
    */
    void        AddNewParticle(FairParticle* Particle) {fParticles->Add(Particle);}
    /**
     *       this method is used by the FAIRMCApplication
    */
    TObjArray*  GetUserDefIons();
    /**
     *       this method is used by the FAIRMCApplication
    */
    TObjArray*  GetUserDefParticles();

    /**
    *       Initialize the Simulation
    */
    virtual void        Init();
    /**
    *       run the  simulation
    */
    virtual void    Run(Int_t NEvents =0, Int_t NotUsed=0);
    /**
    *       Set the magnetic that has to be used for simulation field
    */
    void        SetField(FairField* field);
    /**
     *       Set the event generator that has to be used for simulation field
    */
    void        SetGenerator(FairPrimaryGenerator* Gen);

    /**
     *       Set the experiment dependent event header
     *       for each Monte Carlo Event
     */
    void  SetMCEventHeader(FairMCEventHeader* McHeader) {fMCEvHead=McHeader;}

    /** Set the material file name to be used */
    void    SetMaterials(const char* MatFileName);

    /**switch On/Off the track visualisation */
    void SetStoreTraj(Bool_t storeTraj=kTRUE) {fStoreTraj = storeTraj;}

    /**switch On/Off the debug mode */
    void SetTrackingDebugMode( Bool_t set ) { if (fApp) { fApp->SetTrackingDebugMode( set ); } }

    /**Set geometry builder*/
    void SetGeoModel( char* name );

    /**return the geometry loader used in this session*/
    TString* GetGeoModel () { return fLoaderName; }

    /**Get the field used in simulation*/
    FairField*  GetField() { return fField;}

    /**Get the detector specific event header*/
    FairMCEventHeader*  GetMCEventHeader();

    /**return the full list of modules used in simulation*/
    TObjArray*        GetListOfModules() { return ListOfModules;}

    /**Get the used primary generator*/
    FairPrimaryGenerator* GetPrimaryGenerator() { return fGen;}

    /**switch On/Off external decayer (Pythia) */
    void SetPythiaDecayer(Bool_t decayer) {fPythiaDecayer = decayer;}

    /**switch On external decayer (Pythia). Config macro will be used */
    void SetPythiaDecayer(const TString& Config );

    /**switch On user defined decay, Config  macro will be called  */
    void SetUserDecay(const TString& Config);

    /**switch On/Off user defined decay if true gconfig/UserDecay.C macro will be called  */
    void SetUserDecay(Bool_t decay) {fUserDecay = decay;}

    /**Flag for external decayer*/
    Bool_t  IsExtDecayer() {return fPythiaDecayer; }

    /**Flag for User decay*/
    Bool_t  IsUserDecay() {return fUserDecay; }

    /**Switch on/off Radiation length register */
    void SetRadLenRegister(Bool_t value) {fRadLength= value;}

    void SetRadMapRegister(Bool_t value) { fRadMap=value; }

    void SetRadGridRegister(Bool_t value) {fRadGrid= value;}

    void AddMesh (FairMesh* Mesh);

    void SetUserConfig(const TString& Config) {fUserConfig = Config;}

    void SetUserCuts(const TString& Cuts) {fUserCuts= Cuts;}

    /** Set Beam energy in GeV/c */
    void SetBeamMom(Double_t BeamMom) {  fBeamMom= BeamMom; fUseBeamMom=kTRUE;}

    /** Get the Beam energy */
    Double_t GetBeamMom() {return fBeamMom;}

    /**Get beam energy flag */
    Bool_t UseBeamMom() {return fUseBeamMom;}
    void SetFieldContainer();
  private:
    FairRunSim(const FairRunSim& M);
    FairRunSim& operator= (const  FairRunSim&) {return *this;}
    void SetMCConfig();
    void CheckFlukaExec();
  protected:

    Int_t                  count;//!                               /** Internal counter*/
    FairMCApplication*     fApp;  //!                              /** Main VMC application */
    Double_t               fBeamMom; //!                           /** Beam Energy in GeV/c  */
    Bool_t                 fUseBeamMom; //!                        /** flag for use Beam Energy  */
    FairPrimaryGenerator*  fGen; //!                               /** Primary Event Generator */
    FairMCEventHeader*     fMCEvHead; //!                          /** MC Event Header */
#if !defined(__CINT__)
    static TMCThreadLocal FairRunSim*  fginstance;//!              /** Singleton Instance */
#else
    static                FairRunSim*  fginstance;//!              /** Singleton Instance */
#endif
    FairField*             fField;                                 /** Magnetic Field */
    const char*            fMapName; //!                           /** Input file name map*/
    TObjArray*             fIons; //!                              /** Array of user defined ions */
    TObjArray*             fParticles; //!                         /** Array of user defined particles*/
    TObjArray*             ListOfModules;//!                       /** Array of used modules */
    TString                MatFname; //!                           /** Material file name */
    Bool_t                 fStoreTraj;   //!                       /** Trajectory store flags */
    TString*               fLoaderName;  //!                       /** Geometry Model (TGeo or G3)*/
    Bool_t                 fPythiaDecayer;  //!                    /** flag for using Pythia decayer*/
    TString                fPythiaDecayerConfig; //!               /** Macro for Pythia decay configuration*/
    Bool_t                 fUserDecay;                             /** flag for setting user decay */
    TString                fUserDecayConfig; //!                   /** Macro for decay configuration*/
    Bool_t                 fRadLength;   //!                       /** flag for registring radiation length*/
    Bool_t                 fRadMap; //!                            /** flag for RadiationMapManager
    Bool_t                 fRadGrid;  //!
    TObjArray*             fMeshList; //!                          /** radiation grid scoring
    TString                fUserConfig; //!                        /** Macro for geant configuration*/
    TString                fUserCuts; //!                          /** Macro for geant cuts*/


    ClassDef(FairRunSim ,2)

};

#endif //FAIRRUNSIM_H





/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FairTSBufferFunctionalFunctional_H_
#define FairTSBufferFunctionalFunctional_H_

#include "FairTimeStamp.h"              // for FairTimeStamp

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, Double_t, etc
#include "TObject.h"                    // for TObject
#include "TString.h"                    // for TString

#include <functional>                   // for binary_function
#include <iostream>                     // for operator<<, basic_ostream, etc

class TBranch;
class TClonesArray;
class TTree;


/**
 * \class BinaryFunctor
 * \brief Base class for all functors which are used in the FairTSBufferFunctional
 * \see FairTSBufferFunctional
 *
 * The class is a base class to control which data is extracted by the FairTSBufferFunctional class for processing.
 * The important method to overwrite is Call. It gets the actual data which is read in from the tree and a parameter.
 * If the actual data is not anymore part of the data you want to have Call returns true to stop the reading of data.
 * Otherwise it should return false.
 * The method TimeOut is used to break the processing if for example always the same data is requested.
 */

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif

class BinaryFunctor : public std::binary_function<FairTimeStamp* ,double, bool>
{
  public :
    virtual bool operator() (FairTimeStamp* a, double b) {return Call(a,b);};
    virtual bool Call(FairTimeStamp* a, double b) = 0;
    virtual bool TimeOut() {return false;}
    virtual void ResetTimeOut() {};

    virtual ~BinaryFunctor() {};

};

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

/**
 * \class StopTime
 * Gives you all the data which is older than the given parameter StopTime.
 * It does not return the data requested before.
 */

class StopTime : public BinaryFunctor
{
  public :
    StopTime():fRequestTime(-1), fOldTime(-1), fSameTimeRequestCounter(0) {};

    /**
     * \parameter b: StopTime: All data older than StopTime is returned
     */
    bool Call(FairTimeStamp* a, double b) {
      fRequestTime = b;
      //std::cout << "StopTime: " << a->GetTimeStamp() << " > " <<  b << std::endl;
      return a->GetTimeStamp() > b;
    };

    bool TimeOut() {
      if (fRequestTime != fOldTime) {
        fOldTime = fRequestTime;
        fSameTimeRequestCounter = 0;
        //std::cout << "RequestedTime: " << fRequestTime << std::endl;
        return false;
      } else if (fRequestTime == fOldTime) {
        std::cout << "-I- FairTSBufferFunctional StopTime has requested the same data as before: " << fRequestTime << std::endl;
        fSameTimeRequestCounter++;
      } else {
        std::cout << "-E- FairTSBufferFunctional StopTime Functor has requested time " << fRequestTime << " smaller than old time " << fOldTime << std::endl;
        return true;
      }
      if (fSameTimeRequestCounter > 9) {
        return true;
      } else { return false; }
    }

    void ResetTimeOut() {fSameTimeRequestCounter = 0;}

  private :
    double fRequestTime;
    double fOldTime;
    int fSameTimeRequestCounter;
};



/**
 * \class TimeGap
 * Returns you all the data between two time gaps of a given length.
 */

class TimeGap : public BinaryFunctor
{
  public:
    TimeGap():fOldTime(-1.) {};


    /**
     * \parameter b : TimeGap: All data between two time gaps which are larger than TimeGap are returned
     */
    bool Call(FairTimeStamp* a, double b) {
      double aTime = a->GetTimeStamp();

      if (fOldTime < 0) {
        fOldTime = aTime;
        return false;
      }
      if (aTime - fOldTime > b) {
        fOldTime = aTime;
        return true;
      } else {
        fOldTime = aTime;
        return false;
      }
    };


  private:
    double fOldTime;
};

/**
 * \class FairTSBufferFunctional
 * \brief A class to access time ordered data in a root branch
 *
 * In the constructor of the class one has to give the branch name of the data, the tree the data is stored in
 * and a BinaryFunctor which contains the method how the data should be extracted. Several example functors already exists.
 * To extract the data one has to call GetData with a parameter which fits to the selected functor.
 * GetData returns a TClonesArray which contains the data.
 *
 *
 * Be careful! The buffer runs through the time ordered data in one time direction only. This means that you cannot request data which is older than the
 * data you have requested before.
 *
 * Addition: This is not true anymore. GetData(Double_t, Double_t) is able to get also data which is older but this only works if you request a fixed time
 * via StopTime functor. For other functors the behavior is unpredictable.
 *
 *  Created on: Feb 18, 201
 *      Author: stockman
 */

class FairTSBufferFunctional : public TObject
{

  public:
    FairTSBufferFunctional(TString branchName, TTree* sourceTree, BinaryFunctor* stopFunction, BinaryFunctor* startFunction = 0);

    virtual ~FairTSBufferFunctional() {};
    TClonesArray* GetData(Double_t stopParameter);
    TClonesArray* GetData(Double_t startParameter, Double_t stopParameter);
    Int_t GetBranchIndex() {return fBranchIndex;}

    void SetBranchIndex(const Int_t val) { fBranchIndex = val; }
    void SetStartFunction(BinaryFunctor* function) { fStartFunction = function;}
    void SetStopFunction(BinaryFunctor* function)  { fStopFunction  = function;}
    Bool_t AllDataProcessed();
    void Terminate(){ fTerminate = kTRUE; }

    Bool_t TimeOut() {
      Bool_t stopTimeOut = fStopFunction->TimeOut();
      Bool_t startTimeOut = kTRUE;
      if (fStartFunction != 0) {
        startTimeOut = fStartFunction->TimeOut();
//        if (startTimeOut == kTRUE && stopTimeOut == kFALSE){
//          fStartFunction->ResetTimeOut();
//        }
//        else if (startTimeOut == kFALSE && stopTimeOut == kTRUE){
//          fStopFunction->ResetTimeOut();
//        }
      }
      return (stopTimeOut && startTimeOut);
    }

    Int_t FindStartIndex(Double_t startParameter);


  private:
    void ReadInNextFilledEntry();
    Int_t ReadInPreviousFilledEntry(Int_t startEntry);
    void ReadInNextEntry();   //** used only if no function is given and input data is directly passed through to the OutputArray
    void ReadInEntry(Int_t number);
    void AbsorbDataBufferArray(); //< Absorbs the complete data from fInputArray to fBufferArray

    TClonesArray* fOutputArray;
    TClonesArray* fBufferArray;
    TClonesArray* fInputArray;

    BinaryFunctor* fStartFunction;
    BinaryFunctor* fStopFunction;

    TBranch* fBranch;
    Int_t fBranchIndex;

    Bool_t fTerminate;

    Int_t fVerbose;

    FairTSBufferFunctional(const FairTSBufferFunctional&);
    FairTSBufferFunctional& operator=(const FairTSBufferFunctional&);

    ClassDef(FairTSBufferFunctional,0);

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
// -----                      FairTask header file                      -----
// -----          Created 12/01/04  by M. Al-Turany / D. Bertini       -----
// -------------------------------------------------------------------------


/** FairTask
 * @author M. Al-Turany, Denis Bertini
 * @since 12.01.04
 **
 ** Base class for tasks in the cbmroot framework.
 ** Derived classes should implement the Exec method.
 **/

#ifndef FAIRTASK_H
#define FAIRTASK_H

#include "TTask.h"                      // for TTask

#include "FairRootManager.h"            // for FairRootManager

#include "Rtypes.h"                     // for Int_t, FairTask::Class, etc
#include "TString.h"                    // for TString

#include <map>

class FairLogger;

enum InitStatus {kSUCCESS, kERROR, kFATAL};

class FairTask : public TTask
{

  public:

    /** Default constructor **/
    FairTask();


    /** Standard constructor
    *@param name        Name of task
    *@param iVerbose    Verbosity level
    **/
    FairTask(const char* name, Int_t iVerbose = 1);


    /** Destructor **/
    virtual ~FairTask();


    /** Initialisation at begin of run. For this task and all of the
        subtasks. **/
    void InitTask();


    /** Reinitialisation. For this task and all of the subtasks. **/
    void ReInitTask();


    /** Set parameters. For this task and all of the subtasks. **/
    void SetParTask();


    /** Action at end of run. For this task and all of the subtasks. **/
    virtual void FinishTask();

    /** Action at end of event. For this task and all of the subtasks. **/
    virtual void FinishEvent();

    /** Set verbosity level. For this task and all of the subtasks. **/
    void SetVerbose(Int_t iVerbose);

    void SetInputPersistance(Bool_t val) {fInputPersistance = val;}

    void CheckInputPersistance(TString branchName) {
      FairRootManager* ioman = FairRootManager::Instance();
      fInputPersistance = ioman->CheckBranch(branchName);
    }

    virtual void  ExecuteTask(Option_t *option="0");  // *MENU*

    /** Set persistency of branch with given name true or false
     *  In case is is set to false the branch will not be written to the output.
    **/   
    void SetOutputBranchPersistent(TString, Bool_t);

    /** Check if the branch with the given name is persistent.
     *  If the branch is not in the map, the default return value is true.
    **/  
    Bool_t IsOutputBranchPersistent(TString);

  protected:

    Int_t        fVerbose;  //  Verbosity level
    Int_t        fInputPersistance; ///< Indicates if input branch is persistant
    FairLogger*  fLogger; //!

    /** Intialisation at begin of run. To be implemented in the derived class.
    *@value  Success   If not kSUCCESS, task will be set inactive.
    **/
    virtual InitStatus Init() { return kSUCCESS; };


    /** Reinitialisation. To be implemented in the derived class.
    *@value  Success   If not kSUCCESS, task will be set inactive.
    **/
    virtual InitStatus ReInit() { return kSUCCESS; };


    /** Intialise parameter containers.
        To be implemented in the derived class.
    **/
    virtual void SetParContainers() { };


    /** Action after each event. To be implemented in the derived class **/
    virtual void Finish() { };

    //  /** Action after each event. To be implemented in the derived class **/
    //  virtual void FinishTask() { };


    /** Recursive intialisation of subtasks at begin of run **/
    void InitTasks();

    /** Recursive reinitialisation of subtasks **/
    void ReInitTasks();

    virtual void  ExecuteTasks(Option_t *option);

    /** Recursive parameter initialisation for subtasks **/
    void SetParTasks();

    /** Recursive finish of subtasks **/
    void FinishTasks();

    /** Recursive FinishEvent of subtasks **/
    void FinishEvents();

  private:

    std::map<TString, Bool_t> fOutputPersistance;

    FairTask(const FairTask&);
    FairTask& operator=(const FairTask&);

    ClassDef(FairTask,3);

};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// ********************************************* //
// ***        D. Kresan   2004-Sep-14        *** //
// ***        D.Kresan@gsi.de                *** //
// ********************************************* //

#ifndef FAIR_TRAJ_FILTER_H
#define FAIR_TRAJ_FILTER_H 1

#include "Rtypes.h"                     // for Double_t, Bool_t, Int_t, etc
#include "TGeoTrack.h"                  // IWYU pragma: keep needed by cint
#include "TMath.h"                      // for Pi, TwoPi
#include "TString.h"                    // for TString

class TClonesArray;
class TParticle;

/**
 * @class FairTrajFilter
 * The filter for storing of the trajectories.
 * This singleton class controls storing of trajectories
 * in the gGeoManager list during the simulation.
 * It is created, if FairRun::SetStoreTraj(kTRUE) was called
 * in the run macro
 * before the initialisation. The cuts should be applied
 * after initialisation and before run via
 * FairTrajFilter::Instance()->Set...Cut(...) methods.
 * Three modes of momentum cut (phase space, polar and decart reference systems),
 * are self-excluded. The last that was set, is applied in the simulation.
 * All other cuts are combined together.
 * @author D. Kresan
 * @version 0.1
 * @since 2004-Sep-15
 */


class FairTrajFilter
{

  public:
    /**
     * Default constructor.
     * Creates the singleton object of FairTrajFilter class.
     * The pointer to this object can be reached via FairTrajFilter::Instance().
     */
    FairTrajFilter();

    /**
     * Destructor.
     */
    virtual ~FairTrajFilter();

    /**
     * Class definition.
     */
    ClassDef(FairTrajFilter,1);


  private:

    FairTrajFilter(const FairTrajFilter&);
    FairTrajFilter& operator=(const FairTrajFilter&);

    static FairTrajFilter* fgInstance;

    Double_t fVxMin;
    Double_t fVxMax;
    Double_t fVyMin;
    Double_t fVyMax;
    Double_t fVzMin;
    Double_t fVzMax;

    Double_t fPMin;
    Double_t fPMax;
    Double_t fThetaMin;
    Double_t fThetaMax;
    Double_t fPhiMin;
    Double_t fPhiMax;

    Double_t fPxMin;
    Double_t fPxMax;
    Double_t fPyMin;
    Double_t fPyMax;
    Double_t fPzMin;
    Double_t fPzMax;

    Double_t fPtMin;
    Double_t fPtMax;
    Double_t fRapidityMin;
    Double_t fRapidityMax;

    Int_t    fKinCutType;

    Double_t fEtotMin;
    Double_t fEtotMax;

    Bool_t fStorePrim;
    Bool_t fStoreSec;

    Double_t fStepSizeMin;

    /**
     * collection of tracks
     */
    TClonesArray* fTrackCollection;

    TGeoTrack* fCurrentTrk;

  public:
    TGeoTrack* AddTrack(Int_t trackId, Int_t pdgCode);
    TGeoTrack* AddTrack(TParticle* p);
    TGeoTrack* GetCurrentTrk() {return fCurrentTrk;}

    void Init(TString brName="GeoTracks", TString folderName="MCGeoTrack");
    void Reset();
    /**
     * This function is used to access the methods of the class.
     * @return Pointer to the singleton FairTrajFilter object, created
     * with FairTrajFilter::FairTrajFilter().
     */
    static FairTrajFilter* Instance();

    /**
     * This function applies all availible cuts on different variables.
     * @param p - pointer to the TParticle object.
     * @return kTRUE - if particle survives the cuts. Otherwise - kFALSE.
     */
    Bool_t IsAccepted(const TParticle* p) const;

    /**
     * This function enables the vertex cut.
     * Three modes of momentum cut (phase space, polar and decart reference systems),
     * are self-excluded. The last that was set, is applied in the simulation.
     * @param Box in coordinate space. Only trajectories, created inside this box
     * will be stored. Default values - the cave dimensions.
     */
    void SetVertexCut(Double_t vxMin=-2000., Double_t vyMin=-2000., Double_t vzMin=-2000.,
                      Double_t vxMax= 2000., Double_t vyMax= 2000., Double_t vzMax= 2000.);

    /**
     * This function enables the momentum cut (polar reference system).
     * Three modes of momentum cut (phase space, polar and decart reference systems),
     * are self-excluded. The last that was set, is applied in the simulation.
     * @param The region in momentum space (polar reference system). Only particles
     * inside this region will be stored.
     * Default values - whole momentum range.
     */
    void SetMomentumCutP(Double_t pMin=  0., Double_t thetaMin=0., Double_t phiMin=0.,
                         Double_t pMax=1e10, Double_t thetaMax=TMath::Pi(),
                         Double_t phiMax=TMath::TwoPi());

    /**
     * This function enables the momentum cut (decart reference system).
     * Three modes of momentum cut (phase space, polar and decart reference systems),
     * are self-excluded. The last that was set, is applied in the simulation.
     * @param The region in momentum space (decart reference system). Only particles
     * inside this region will be stored.
     * Default values - whole momentum range.
     */
    void SetMomentumCutD(Double_t pxMin=-1e10, Double_t pyMin=-1e10, Double_t pzMin=-1e10,
                         Double_t pxMax= 1e10, Double_t pyMax= 1e10, Double_t pzMax= 1e10);

    /**
     * This function enables the cut in phase space (pt-rapidity).
     * @param The region in phase space (pt-rapidity). Only particles
     * inside this region will be stored.
     * Default values - whole pt-rapidity range.
     */
    void SetPtRapidityCut(Double_t ptMin=0., Double_t ptMax=1e10,
                          Double_t rapidityMin=-1e10, Double_t rapidityMax=1e10);

    /**
     * This function enables the cut on total energy.
     * @param Total energy range. Only particles with total energy value
     * inside this range will be stored. Deafult values - whole energy range.
     */
    void SetEnergyCut(Double_t etotMin=0., Double_t etotMax=1e10);

    /**
     * This function controls the storing of primaries.
     * @param storePrim - boolean flag to control the storing of primaries.
     */
    inline void SetStorePrimaries(Bool_t storePrim=kTRUE) {fStorePrim = storePrim;};

    /**
     * This function controls the storing of secondaries.
     * @param storeSec - boolean flag to control the storing of secondaries.
     */
    inline void SetStoreSecondaries(Bool_t storeSec=kTRUE) {fStoreSec = storeSec;};

    /**
     * This function controls the process of adding the points to the trajectory.
     * @param stepSizeMin - minimum value of step size, wich will be added to
     * the trajectory.
     */
    void SetStepSizeCut(Double_t stepSizeMin=0.);

    /**
     * This is the getter for the vertex cut.
     * @param References to the variables where return values should be stored.
     */
    void GetVertexCut(Double_t& vxMin, Double_t& vyMin, Double_t& vzMin,
                      Double_t& vxMax, Double_t& vyMax, Double_t& vzMax) const;

    /**
     * This is the getter for the momentum cut (polar reference system).
     * @param References to the variables where return values should be stored.
     */
    void GetMomentumCutP(Double_t& pMin, Double_t& thetaMin, Double_t& phiMin,
                         Double_t& pMax, Double_t& thetaMax, Double_t& phiMax) const;

    /**
     * This is the getter for the momentum cut (decart reference system).
     * @param References to the variables where return values should be stored.
     */
    void GetMomentumCutD(Double_t& pxMin, Double_t& pyMin, Double_t& pzMin,
                         Double_t& pxMax, Double_t& pyMax, Double_t& pzMax) const;

    /**
     * This is the getter for the space phase cut.
     * @param References to the variables where return values should be stored.
     */
    void GetPtRapidityCut(Double_t& ptMin, Double_t& ptMax,
                          Double_t& rapidityMin, Double_t& rapidityMax) const;

    /**
     * This is the getter for the total energy cut.
     * @param References to the variables where return values should be stored.
     */
    void GetEnergyCut(Double_t& etotMin, Double_t& etotMax) const;

    /**
     * This is the getter for flag of storing of primaries.
     * @return kTRUE if primaries should be stored.
     */
    inline Bool_t IsPrimariesStored() const {return fStorePrim;};

    /**
     * This is the getter for flag of storing of secondaries.
     * @return kTRUE if secondaries should be stored.
     */
    inline Bool_t IsSecondariesStored() const {return fStoreSec;};

    /**
     * This is the getter for the step size cut.
     * @return The minimum value of the step size wich still should be
     * added to the trajectory.
     */
    inline Double_t GetStepSizeCut() const { return fStepSizeMin; };

    TGeoTrack* GetTrack(Int_t trackId);

};



#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * @class FairWriteoutBuffer
 *
 * @author Tobias Stockmanns
 * @brief A container class to store digi data during events
 *
 * The FairWriteoutBuffer class provides a container which handles the storage of data between
 * events. The data has to be given with an active time, the absolute time the data is active in the
 * detector and can influence the output of the data.
 * FillNewData is used to put new data into the container.
 * WriteOutData with a given actual time stores the data which has an active time older than the given time
 * in the corresponding TClonesArray of the FairRootManager.
 * At the end of the task WriteOutAllData has to be called to store the data which is still in the buffer.
 * If one adds data via FillNewData into the buffer which is already present in the buffer, Modify is called.
 * The standard behavior of Modify is that the new data is ignored to simulate pile-up. If a different behavior
 * is wanted one has to overwrite Modify in a derived class.
 *
 * The data which should be stored in the buffer has to be derived from FairTimeStamp.
 * It needs an operator< and a method equal if the same detector element is hit.
 *
 * To use this buffer one has to derive his own buffer class from FairWriteoutBuffer and overwrite the pure virtual functions.
 */

#ifndef FairWriteoutBuffer_H_
#define FairWriteoutBuffer_H_

#include "TObject.h"                    // for TObject

#include "FairLogger.h"                 // for FairLogger
#include "FairRootManager.h"            // for FairRootManager
#include "FairTimeStamp.h"              // for FairTimeStamp

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Bool_t, Int_t, etc
#include "TClonesArray.h"               // for TClonesArray
#include "TString.h"                    // for TString

#include <iostream>                     // for cout, ostream
#include <map>                          // for multimap
#include <utility>                      // for pair
#include <vector>                       // for vector

class FairWriteoutBuffer: public TObject
{
  public:
    FairWriteoutBuffer() : TObject(), fStartTime_map(), fDeadTime_map(), fBranchName(), fClassName(),
      fTreeSave(false), fActivateBuffering(kFALSE), fVerbose(0), fLogger(FairLogger::GetLogger()) {};
    FairWriteoutBuffer(TString branchName, TString className, TString folderName, Bool_t persistance);
    virtual ~FairWriteoutBuffer() {};

    virtual void SaveDataToTree(Bool_t val = kTRUE) {
      fTreeSave = val;   ///< If SaveDataToTree is set the data is stored at the end of the buffering into the given TClonesArray.
    }
    virtual void ActivateBuffering(Bool_t val = kTRUE) {
      fActivateBuffering=val;   ///< fActivateBuffering has to be set to kTRUE to use the buffering. Otherwise the data is directly stored in the given TClonesArray.
    }

   Bool_t IsBufferingActivated(){ return fActivateBuffering;}
  
/// Fills a pointer to a data object into the buffer. StartTime gives the time when the data can influence later data, activeTime gives the time how long the data can influence later data.
/// Both time data has to be given as an absolute time!
    virtual void FillNewData(FairTimeStamp* data, double startTime, double activeTime);

    virtual Int_t GetNData() {
      return fDeadTime_map.size();
    }
    virtual std::vector<FairTimeStamp*> GetRemoveOldData(double time);
    virtual std::vector<FairTimeStamp*> GetAllData();


    virtual void SetVerbose(Int_t val) {
      fVerbose = val;
    }

    virtual void DeleteOldData() {
      if ( fBranchName.Length() > 0 ) {
        TClonesArray* myArray = FairRootManager::Instance()->GetTClonesArray(fBranchName);
        myArray->Delete();
      }
    }

    virtual void WriteOutData(double time);
    virtual void WriteOutAllData();

  protected:

    virtual void AddNewDataToTClonesArray(FairTimeStamp* data) = 0; ///< store the data from the FairTimeStamp pointer in a TClonesArray (you have to cast it to your type of data)
    virtual double FindTimeForData(FairTimeStamp* data) = 0;  ///< if the same data object (like a pad or a pixel) is already present in the buffer, the time of this object has to be returned otherwise -1
    virtual void FillDataMap(FairTimeStamp* data, double activeTime) = 0; ///< add a new element in the search buffer
    virtual void EraseDataFromDataMap(FairTimeStamp* data) = 0; ///< delete the element from the search buffer (see PndSdsDigiPixelWriteoutBuffer)

    ///Modify defines the behavior of the buffer if data should be stored which is already in the buffer. Parameters are the old data with the active time, the new data with an active time.
    ///Modify returns than a vector with the new data which should be stored.
    virtual std::vector<std::pair<double, FairTimeStamp*> > Modify(std::pair<double, FairTimeStamp*> oldData, std::pair<double, FairTimeStamp*>) {
      std::vector<std::pair<double, FairTimeStamp*> > result;
      result.push_back(oldData);
      return result;
    }


    virtual void WriteOutDataDeadTimeMap(double time);
    virtual void MoveDataFromStartTimeMapToDeadTimeMap(double time);
    virtual void FillDataToDeadTimeMap(FairTimeStamp* data, double activeTime, double startTime);

    virtual void PrintData(FairTimeStamp* data) {
      std::cout << data->GetTimeStamp();
    }; ///< Method should be overwritten in derived classes to print the data of an object stored in the buffer
    virtual void PrintDeadTimeMap();
    virtual void PrintStartTimeMap();

    std::multimap<double, std::pair<double, FairTimeStamp*> > fStartTime_map;
    std::multimap<double, FairTimeStamp*> fDeadTime_map;

    TString fBranchName;
    TString fClassName;
    Bool_t fTreeSave;
    Bool_t fActivateBuffering;
    Int_t fVerbose;
    FairLogger* fLogger;  //! /// FairLogger

  private:
    FairWriteoutBuffer(const FairWriteoutBuffer&);
    FairWriteoutBuffer& operator=(const FairWriteoutBuffer&);

    ClassDef(FairWriteoutBuffer, 1);
};

#endif /* FairWriteoutBuffer_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNONLINE_H
#define FAIRRUNONLINE_H


/**
 * Configure and manage the Analysis
 * @author M. Al-Turany D. Bertini
 * @version 0.1
 * @since 28.02.05
 */

#include "FairRun.h"
#include "FairRootManager.h"

#include "TString.h"
#include <iostream>

class FairRuntimeDb;
class FairField;
class TFile;
class TF1;
class TTree;
class FairSource;
class TFolder;
class THttpServer;

class FairRunOnline : public FairRun
{

  public:
    static FairRunOnline* Instance();
    virtual ~FairRunOnline();
    FairRunOnline();
    FairRunOnline(FairSource* source);

    /**initialize the run manager*/
    void        Init();
    /**Run for the given number of events*/
    void        Run(Int_t Ev_start, Int_t Ev_end);
 
    void        Reinit(UInt_t runId);
    UInt_t      getRunId() { return fRunId; }
    /** Get the magnetic field **/
    FairField*  GetField() { return fField; }
    /** Set the magnetic Field */
    void        SetField (FairField* ffield) { fField = ffield; }

    /** Set if the run should be closed automatically after executing the
        run functuion
    **/
    void        SetAutoFinish(Bool_t val) { fAutomaticFinish = val; }
    /** Set the source which should be used **/
    void        SetSource(FairSource* source) { fRootManager->SetSource(source); }
    /** Return pointer to source **/
    FairSource*  GetSource() { return fRootManager->GetSource(); }


    /** Initialization of parameter container is set to static, i.e: the run id is
     *  is not checked anymore after initialization
     */

    /** Init containers executed on PROOF, which is part of Init when running locally*/
    void        InitContainers();
    void        SetContainerStatic(Bool_t tempBool=kTRUE);
    Bool_t      GetContainerStatic() { return fStatic; };

    /** Add histogram to be displayed using THttpServer.*/
    void AddObject(TObject* object);

    void SetGenerateHtml(Bool_t flag, const char* histFileName, Int_t refreshRate);

    /** Activate http server on current host port 8080. To be called before Init.
     * @param refreshRate an interval in number of events for server update.
     */
    void ActivateHttpServer(Int_t refreshRate = 10000);

    /** Register a command on the http server.
     * @param name a command name starting with /
     * @param command a call to method "/object_name/->Method()"
     */
    void RegisterHttpCommand(TString name, TString command);

    /** Write last data to file, close input and output **/
    void Finish();

  private:

    Bool_t fAutomaticFinish;

    FairRunOnline(const FairRunOnline& M);
    FairRunOnline& operator= (const  FairRunOnline&) { return *this; }

    /** Main Event loop **/
    Int_t EventLoop();

  protected:
    /** This variable became true after Init is called*/
    Bool_t                                  fIsInitialized;
    static FairRunOnline*                   fgRinstance;
    /** true for static initialisation of parameters */
    Bool_t                                  fStatic;//!
    FairField*                              fField;

    TFolder*    fFolder;       //!
    Bool_t      fGenerateHtml; //!
    TString     fHistFileName; //!
    Int_t       fRefreshRate;  //!
    Int_t       fNevents;      //!

    THttpServer* fServer;             //!
    Int_t        fServerRefreshRate;  //!

    void WriteObjects();
    void GenerateHtml();

    virtual void Fill();

    ClassDef(FairRunOnline, 0)
};

#endif //FAIRRUNONLINE_H
#ifndef FAIR_LINK_MANAGER_H
#define FAIR_LINK_MANAGER_H

#include "TObject.h"                    // for TObject
#include "TMCtls.h"                     // for multi-threading

#include "Rtypes.h"                     // for Bool_t, Int_t, UInt_t, etc
#include <set>							// for set of branch types to ignore


class FairLogger;

//_____________________________________________________________________

class FairLinkManager : public TObject
{
  public:
    /**ctor*/
    FairLinkManager();
    /**dtor*/
    virtual ~FairLinkManager();


    /** static access method */
    static FairLinkManager* Instance();
    virtual void AddIgnoreType(Int_t type);		///< Adds a BranchId (Type) to which links are not included in the link list. Either ignore types or include types can be given.
    virtual Bool_t IsIgnoreType(Int_t type) const;

    virtual void AddIncludeType(Int_t type);	///< Adds a BranchId (Type) to which links are included in the link list. Either ignore types or include types can be given (XOR).

    std::set<Int_t> GetIgnoreTypes() const {return fIgnoreTypes;}


  private:
    /**private methods*/
    FairLinkManager(const FairLinkManager&);
    FairLinkManager& operator=(const FairLinkManager&);
    /**  Set the branch address for a given branch name and return
        a TObject pointer, the user have to cast this pointer to the right type.*/

//_____________________________________________________________________
    /**private Members*/

    std::set<Int_t> fIgnoreTypes; //!
    Bool_t fIgnoreSetting;

    /**Singleton instance*/
#if !defined(__CINT__)
    static TMCThreadLocal FairLinkManager* fgInstance;
#else
    static                FairLinkManager* fgInstance;
#endif

    FairLogger*                         fLogger;//!


    ClassDef(FairLinkManager,1) // Root IO manager
};

#endif //FAIR_ROOT_MANAGER_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRBASECONTFACT_H
#define FAIRBASECONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for FairBaseContFact::Class, etc

class FairParSet;

class FairBaseContFact : public FairContFact
{
    /** Factory for all Base parameter containers */
  private:
    void setAllContainers();
  public:
    /**default ctor*/
    FairBaseContFact();
    /**default dtor*/
    ~FairBaseContFact() {}
    /** Calls the constructor of the corresponding parameter container.
     * For an actual context, which is not an empty string and not the default context
     * of this container, the name is concatinated with the context. */
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairBaseContFact,0)
};

#endif  /* !FAIRBASECONTFACT_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRBASEPARSET_H
#define FAIRBASEPARSET_H

/**
 * Parameter class for run
 * @author M. Al-Turany
 * @version 1
 * @since 12.10.04
 */
#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for Double_t, etc
#include "TGeoManager.h"                // IWYU pragma: keep needed by cint

class FairParamList;
class FairPrimaryGenerator;
class TObjArray;

class FairBaseParSet : public FairParGenericSet
{
  public:
    /**
     * constructor
     * @param name :  Parameter set name
    * @param title:  Parameter set title
    * @param context:  Parameter set context
    */


    FairBaseParSet(const char* name="FairBaseParSet",
                   const char* title="Class for base parameter io",
                   const char* context="BaseDefaultContext");
    /** dtor*/
    ~FairBaseParSet(void);
    /** clear*/
    void clear(void);
    /**
     * Fills all persistent data members into the list for write.
     * @param FairParamList : Parameter list to be filled
    */
    void putParams(FairParamList*);
    /**
     * Fills all persistent data members from the list after reading. The function
     * returns false, when a data member is not in the list.
     * @param FairParamList : Parameter list to be filled
     */

    Bool_t getParams(FairParamList*);
    /**
     * Set the detector list used in the simulation
     * @param array: TObjArray of detector
     */
    void SetDetList(TObjArray* array) {fDetList=array;}
    /**
     * Set the Generator used in the simulation
     * @param gen: Primary generator used in simulation
     */
    void SetGen(FairPrimaryGenerator* gen) {fPriGen=gen;}
    /**
     * Set the beam momentum (if any) used in the simulation
     * @param BMom: Beam Momentum in GeV/c
     */
    void SetBeamMom(Double_t  BMom) {fBeamMom = BMom;}
    /**
     * Set the list of parameter containers used in a run
     * @param array: TObjArray of containers
     */
    void SetContListStr(TObjArray* list) {fContNameList= list;}
   /**
    * Set the random seed used in a run
    * @param RndSeed: Random Seed
    */
    void SetRndSeed(UInt_t RndSeed) {fRandomSeed= RndSeed;}
    /**
     *  Get the detector list used in the simulation
     */
    TObjArray*             GetDetList() {return fDetList;}
    /**
     *  Get the Primery generator used in the simulation
     */
    FairPrimaryGenerator*   GetPriGen() {return fPriGen; }
    /**
     *  Get the Beam Momentum used in the simulation (GeV/c)
     */
    Double_t          GetBeamMom() {return fBeamMom; }
    /**
     *  Get the parameter container list used in this run
     */
    TObjArray*             GetContList() {return fContNameList;}
   /**
    *  Get the Random Seed used in this run
    */
    UInt_t  GetRndSeed() {return fRandomSeed;}
   

  protected:

    /// Detectors used in the simulation
    TObjArray*              fDetList;
    ///Generator used for simulation
    FairPrimaryGenerator*   fPriGen;
    ///Beam momentum (GeV/c)
    Double_t              fBeamMom;
    /// List of parameter container names in the RUN
    TObjArray*              fContNameList;
    /// Random Seed from gRandom
    UInt_t                 fRandomSeed;

    ClassDef(FairBaseParSet,6)

  private:
    FairBaseParSet(const FairBaseParSet& L);
    FairBaseParSet& operator= (const FairBaseParSet&) {return *this;}



};

#endif /* !FAIRBASEPARSET_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FairGeoParSet_H
#define FairGeoParSet_H

/**
 * Parameter class for Geometry stuff
 * @author M. Al-Turany
 * @version 1
 * @since 12.10.04
 */
#include "FairParGenericSet.h"          // for FairParGenericSet
#include "Rtypes.h"                     // for Double_t, etc
#include "TGeoManager.h"                // IWYU pragma: keep needed by cint

class FairParamList;
class TObjArray;

class FairGeoParSet : public FairParGenericSet
{
  public:
    /**
     * constructor
     * @param name :  Parameter set name
    * @param title:  Parameter set title
    * @param context:  Parameter set context
    */


    FairGeoParSet(const char* name="FairGeoParSet",
                  const char* title="Class for base parameter io",
                  const char* context="BaseDefaultContext");
    /** dtor*/
    ~FairGeoParSet(void);
    /** clear*/
    void clear(void);
    /**
     * Fills all persistent data members into the list for write.
     * @param FairParamList : Parameter list to be filled
    */
    void putParams(FairParamList*);
    /**
     * Fills all persistent data members from the list after reading. The function
     * returns false, when a data member is not in the list.
     * @param FairParamList : Parameter list to be filled
     */

    Bool_t getParams(FairParamList*);
    /**
     * Set the Geometry node list used in the simulation
     * @param array: TObjArray of Geometry nodes
     */
    void SetGeoNodes(TObjArray* array) {fGeoNodes=array;}
    /**
     * Set the Geometry (TGeoManager) used in the simulation
     * @param Geom: TGeoManager of the full geometry
     */
    void SetGeometry(TGeoManager* Geom) {fGeom=Geom;}
    /**
    *  Get the Geometry Nodes list used in the simulation
    */
    TObjArray*             GetGeoNodes() {return fGeoNodes;}
    /**
     *  Get the geometry (TGeoManager) used in the simulation
     */
    TGeoManager*           GetGeometry() {return fGeom;}

  protected:

    /// List of FairGeoNodes for sensitive volumes
    TObjArray*              fGeoNodes; //!
    /// Full Geometry
    TGeoManager*            fGeom;
    ClassDef(FairGeoParSet,1)

  private:
    FairGeoParSet(const FairGeoParSet& L);
    FairGeoParSet& operator= (const FairGeoParSet&) {return *this;}



};

#endif /* !FairGeoParSet_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDETECTOR_H
#define FAIRDETECTOR_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for Int_t, Bool_t, etc

class FairLogger;
class FairVolume;
class TClonesArray;

/**
 * Base class for constructing detecors
 * @author M. Al-Turany, Denis Bertini
 * @version 0.1
 * @since 12.01.04
 */
class FairDetector : public FairModule
{

  public:

    /**
      constructor
      Name :  Detector Name
      Active: kTRUE for active detectors  (ProcessHits() will be called)
              kFALSE for inactive detectors
    */
    FairDetector(const char* Name, Bool_t Active, Int_t DetId=0);
    /**
      default constructor
    */
    FairDetector();
    /**
      destructor
    */
    virtual ~FairDetector();
    /**
      Initialization of the detector is done here
    */
    virtual void   Initialize();
    /**
      this method is called for each step during simulation (see FairMCApplication::Stepping())
    */
    virtual Bool_t ProcessHits( FairVolume* v=0)=0;
    /**
      this is called at the end of an event
    */
    virtual void   EndOfEvent() {
      ;
    }
    /**
      Registers the produced collections in FAIRRootManager.
    */
    virtual void   Register()=0;

    /** Gets the produced collections **/
    virtual TClonesArray* GetCollection(Int_t iColl) const = 0;

    /**
      has to be called after each event to reset the containers
    */
    virtual void   Reset()=0;

    virtual void   CopyClones( TClonesArray*,  TClonesArray*, Int_t) {
      ;
    }

    virtual void   FinishPrimary() {
      ;
    }
    virtual void   FinishRun() {
      ;
    }
    virtual void   BeginPrimary() {
      ;
    }
    virtual void   PostTrack() {
      ;
    }
    virtual void   PreTrack() {
      ;
    }
    virtual void   BeginEvent() {
      ;
    }
    virtual void   FinishEvent() {
      ;
    }
    virtual void   SetSpecialPhysicsCuts() {
      ;
    }
    void SaveGeoParams();
    Int_t  GetDetId() {
      return fDetId;
    }

  protected:
    /** Copy constructor */
    FairDetector(const FairDetector&);
    /** Assignment operator */
    FairDetector& operator= (const FairDetector&);

    Int_t fDetId; // Detector Id has to be set from ctr.
    FairLogger* fLogger;  //! /// FairLogger

    ClassDef(FairDetector,1)

};
#endif //FAIRDETECTOR_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----               FairGeaneApplication header file                   -----
// -----            Created 10/11/10  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#ifndef FAIR_GEANE_APPLICATION_H
#define FAIR_GEANE_APPLICATION_H

#include "TVirtualMCApplication.h"      // for TVirtualMCApplication

#include "RVersion.h"                   // for ROOT_VERSION_CODE
#include "Rtypes.h"                     // for Bool_t, etc
#include "TLorentzVector.h"             // for TLorentzVector

class FairField;

/**
 * The Main Application for GEANE
 * @author M. Al-Turany
 * @version 0.1
 * @since 10.11.10
 */

class FairGeaneApplication : public TVirtualMCApplication
{
  public:
    /** default constructor */
    FairGeaneApplication();
    /** Special constructor, used for initializing G3 for Geane track propagation
    *@param Debug    true to print step info*/
    FairGeaneApplication(Bool_t Debug);
    /** default destructor */
    virtual ~FairGeaneApplication();
#if ROOT_VERSION_CODE < 333824
    /** Calculate user field  b at point x */
    void          Field(const Double_t* x, Double_t* b) const;      // MC Application
#endif
    /** Return Field used in simulation*/
    FairField*             GetField() {return fxField;}
    /** Initialize MC engine */
    void                  InitMC(const char* setup,  const char* cuts);
    /**
    * Set the magnetic field for simulation or Geane
    * @param field: magnetic field
    */
    void                   SetField(FairField* field);
    /** Define action at each step, dispatch the action to the corresponding detectors */
    void          GeaneStepping();                           // MC Application
    void ConstructGeometry();
    /** Singelton instance
     */
    static FairGeaneApplication* Instance();

    /**pure virtual functions that hasve to be implimented */

    void InitGeometry() {;}
    void GeneratePrimaries() {;}
    void BeginEvent() {;}
    void BeginPrimary() {;}
    void PreTrack() {;}
    void PostTrack() {;}
    void FinishPrimary() {;}
    void FinishEvent() {;}
    void Stepping() {;}
    void StopRun() {;}


  private:
    // data members
    /**Magnetic Field Pointer*/
    FairField*            fxField; //
    /**MC Engine 1= Geant3, 2 = Geant4*/
    Int_t                fMcVersion;     // mc Version
    /** Debug flag*/
    Bool_t               fDebug;//!
    TLorentzVector fTrkPos; //!

    ClassDef(FairGeaneApplication,1)  //Interface to MonteCarlo application
  private:
    FairGeaneApplication(const FairGeaneApplication&);
    FairGeaneApplication& operator=(const FairGeaneApplication&);
};

// inline functions

inline FairGeaneApplication* FairGeaneApplication::Instance()
{ return static_cast<FairGeaneApplication*>(TVirtualMCApplication::Instance());}

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                    FairGenerator header file                   -----
// -----          Created 09/06/04  by D. Bertini / V. Friese          -----
// -------------------------------------------------------------------------


/** FairGenerator.h
 *@author D.Bertini <d.bertini@gsi.de>
 *@author V.Friese  <v.friese@gsi.de>
 *
The FairGenerator is the abtract base class for the generators used to
generate input for the transport simulation.Each concrete generator class
derived from this one must implement the abtract method ReadEvent,
which has to use the method FairPrimaryGenerator::AddTrack.
**/


#ifndef FAIRGENERATOR_H
#define FAIRGENERATOR_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Bool_t, etc

class FairPrimaryGenerator;

class FairGenerator : public TNamed
{

  public:

    /** Default constructor. **/
    FairGenerator();


    /** Constructor with name and title **/
    FairGenerator(const char* name, const char* title="FAIR Generator");


    /** Destructor. **/
    virtual ~FairGenerator();


    /** Abstract method ReadEvent must be implemented by any derived class.
        It has to handle the generation of input tracks (reading from input
        file) and the handing of the tracks to the FairPrimaryGenerator. I
        t is called from FairMCApplication.
        *@param pStack The stack
        *@return kTRUE if successful, kFALSE if not
    **/
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen) = 0;


    /**Initialize the generator if needed */
    virtual Bool_t Init() { return kTRUE;}

    /** Clone this object (used in MT mode only) */
    virtual FairGenerator* CloneGenerator() const;

  protected:
    /** Copy constructor */
    FairGenerator(const FairGenerator&);
    /** Assignment operator */
    FairGenerator& operator= (const FairGenerator&);

    ClassDef(FairGenerator,1);
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
// -----                       FairStack header file                    -----
// -----           Created 10/08/04  by D. Bertini                     -----
// -------------------------------------------------------------------------


/** FairStack.h
 *@author D.Bertini <d.bertini@gsi.de>
 * Generic MC stack class
 **/


#ifndef FAIRGENERICSTACK_H
#define FAIRGENERICSTACK_H

#include "TClonesArray.h" 
#include "TVirtualMCStack.h"            // for TVirtualMCStack

#include "Rtypes.h"                     // for Double_t, Int_t, etc
#include "TMCProcess.h"                 // for TMCProcess

#include <stddef.h>                     // for NULL

class FairLogger;
class TParticle;
class TRefArray;
class TIterator;


class FairGenericStack : public TVirtualMCStack
{

  public:

    /** Default constructor  **/
    FairGenericStack();


    /** Destructor with estimated array size  **/
    FairGenericStack(Int_t size);


    /** Destructor  **/
    virtual ~FairGenericStack();

    /** Virtual method PushTrack.
     ** Add a TParticle to the stack.
     *@param toBeDone  Flag for tracking
     *@param parentID  Index of mother particle
     *@param pdgCode   Particle type (PDG encoding)
     *@param px,py,pz  Momentum components at start vertex [GeV]
     *@param e         Total energy at start vertex [GeV]
     *@param vx,vy,vz  Coordinates of start vertex [cm]
     *@param time      Start time of track [s]
     *@param polx,poly,polz Polarisation vector
     *@param proc      Production mechanism (VMC encoding)
     *@param ntr       Track number (filled by the stack)
     *@param weight    Particle weight
     *@param is        Generation status code (whatever that means)
     **/
    virtual void PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                           Double_t px, Double_t py, Double_t pz,
                           Double_t e, Double_t vx, Double_t vy,
                           Double_t vz, Double_t time, Double_t polx,
                           Double_t poly, Double_t polz, TMCProcess proc,
                           Int_t& ntr, Double_t weight, Int_t is);

    /** Virtual method PushTrack.
     ** Add a TParticle to the stack.
     *@param toBeDone         Flag for tracking
     *@param parentID         Index of mother particle
     *@param pdgCode          Particle type (PDG encoding)
     *@param px,py,pz         Momentum components at start vertex [GeV]
     *@param e                Total energy at start vertex [GeV]
     *@param vx,vy,vz         Coordinates of start vertex [cm]
     *@param time             Start time of track [s]
     *@param polx,poly,polz   Polarisation vector
     *@param proc             Production mechanism (VMC encoding)
     *@param ntr              Track number (filled by the stack)
     *@param weight           Particle weight
     *@param is               Generation status code (whatever that means)
     *@param secondparentID   used fot the index of mother of primery in the list
     **/

    virtual void PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                           Double_t px, Double_t py, Double_t pz,
                           Double_t e, Double_t vx, Double_t vy,
                           Double_t vz, Double_t time, Double_t polx,
                           Double_t poly, Double_t polz, TMCProcess proc,
                           Int_t& ntr, Double_t weight, Int_t is, Int_t secondparentID);


    /** Virtual method PopNextTrack.
     ** Gets next particle for tracking from the stack.
     *@param  iTrack  index of popped track
     *@return Pointer to the TParticle of the track
     **/
    virtual TParticle* PopNextTrack(Int_t& iTrack);


    /** Virtual method PopPrimaryForTracking.
     ** Gets primary particle by index for tracking from stack.
     *@param  iPrim   index of primary particle
     *@return Pointer to the TParticle of the track
     **/
    virtual TParticle* PopPrimaryForTracking(Int_t iPrim);


    /** Add a TParticle to the fParticles array **/
    void AddParticle(TParticle* part);


    /** Fill the MCTrack output array, applying filter criteria **/
    virtual void FillTrackArray();


    /** Update the track index in the MCTracks and MCPoints **/
    virtual void UpdateTrackIndex(TRefArray* detArray=0);


    /** Set the list of detectors to be used for filltering the stack*/
    void SetDetArrayList(TRefArray* detArray);

    /** Resets arrays and stack and deletes particles and tracks **/
    virtual void Reset();


    /** Register the MCTrack array to the Root Manager  **/
    virtual void Register();


    /** Output to screen
     **@param iVerbose: 0=events summary, 1=track info
     **/
    virtual void Print(Option_t* option="") const;


    /** Modifiers  **/
    virtual void SetCurrentTrack(Int_t iTrack);

    /** Accessors **/
    virtual Int_t GetNtrack() const;   // Total number of tracks
    virtual Int_t GetNprimary() const; // Number of primaries
    virtual TParticle* GetCurrentTrack() const;
    virtual Int_t GetCurrentTrackNumber() const;
    virtual Int_t GetCurrentParentTrackNumber() const;
    virtual TParticle* GetParticle(Int_t) const { return NULL; }

    virtual TClonesArray* GetListOfParticles() { return NULL; } 

    /** Clone this object (used in MT mode only) */
    virtual FairGenericStack* CloneStack() const;

  protected:
    /** Copy constructor */
    FairGenericStack(const FairGenericStack&);
    /** Assignment operator */
    FairGenericStack& operator=(const FairGenericStack&);

    /** Fair Logger */
    FairLogger*            fLogger;//!

    /** List of detectors registering hits in the simulation */
    TRefArray*  fDetList;  //!

    /** Iterator for the detector list*/
    TIterator* fDetIter;

    /**Verbosity level*/
    Int_t fVerbose;

    ClassDef(FairGenericStack,1)


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
// -----                       FairIon header file                      -----
// -----          Created 27/08/04  by V. Friese / D.Bertini           -----
// -------------------------------------------------------------------------

/** FairIon.h
 *@author V.Friese <v.friese@gsi.de>
 *@author D.Bertini <d.bertini@gsi.de>
 **
 ** A class for the user definition of an ion. It will be instantiated
 ** from the constructor of the FairIonGenerator.
 **/


#ifndef FAIRION_H
#define FAIRION_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Int_t, Double_t, etc

class FairLogger;

class FairIon: public TNamed
{
  public:

    /** Default constructor **/
    FairIon();


    /** Standard constructor
     *@param name  name
     *@param z     atomic number
     *@param a     atomic mass
     *@param q     electric charge
     *@param e     excitation energy
     *@param m     mass [GeV]
     ** If mass is not given, it will be set to a times the proton mass.
     **/

    FairIon(const char* name, Int_t z, Int_t a, Int_t q, Double_t e=0., Double_t m=0.);
    void SetParams( const char* name, Int_t z, Int_t a,
                    Int_t q, Double_t e=0., Double_t m=0.) {
      SetName(name);
      fZ=z;
      fA=a;
      fQ=q;
      fExcEnergy=e;
      fMass=m;
    }
    /** Destructor **/
    virtual ~FairIon();


    /** Accessors **/
    /**
    * Return the atomic number
    */
    Int_t GetZ()            const { return fZ; }
    /**
     * Return the atomic mass
    */
    Int_t GetA()            const { return fA; }
    /**
     * Return the charge
    */
    Int_t GetQ()            const { return fQ; }
    /**
    * Return the  excitation energy
    */
    Double_t GetExcEnergy() const { return fExcEnergy; }
    /**
    * Return the mass in GeV
    */
    Double_t GetMass()      const { return fMass; }

    /** Modifiers **/
    /**
    * Set the  excitation energy
    */
    void SetExcEnergy(Double_t eExc) { fExcEnergy = eExc; }
    /**
    * Set the mass in GeV
    */
    void SetMass(Double_t mass)      { fMass = mass*amu; }


  private:

    /** Data members **/

    static Int_t fgNIon;  //! /// Number of ions instantiated. One per generator.
    Int_t    fZ;          /// Atomic number
    Int_t    fA;          /// Atomic mass
    Int_t    fQ;          /// Electric charge
    Double_t fExcEnergy;  /// Excitation energy [GeV]
    Double_t fMass;       /// Mass [GeV]
    FairLogger* fLogger;  //! /// FairLogger
    static const Double_t amu; ///  .931494028 Gev/c**2

    FairIon(const FairIon&);
    FairIon& operator=(const FairIon&);

    ClassDef(FairIon,2);

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
// -----               FairMCApplication header file                   -----
// -----            Created 06/01/04  by M. Al-Turany                  -----
// -------------------------------------------------------------------------

#ifndef FAIR_MC_APPLICATION_H
#define FAIR_MC_APPLICATION_H

#include "TVirtualMCApplication.h"      // for TVirtualMCApplication

#include "FairRunInfo.h"                // for FairRunInfo

#include "RVersion.h"                   // for ROOT_VERSION_CODE
#include "Rtypes.h"                     // for Int_t, Bool_t, Double_t, etc
#include "TLorentzVector.h"             // for TLorentzVector
#include "TString.h"                    // for TString

#include <map>                           // for map, multimap, etc
#include <list>                           // for list

class FairDetector;
class FairEventHeader;
class FairField;
class FairGenericStack;
class FairMCEventHeader;
class FairPrimaryGenerator;
class FairRadGridManager;
class FairRadLenManager;
class FairRadMapManager;
class FairRootManager;
class FairTask;
class FairTrajFilter;
class FairVolume;
class TChain;
class TIterator;
class TObjArray;
class TRefArray;
class TTask;

/**
 * The Main Application ( Interface to MonteCarlo application )
 * @author M. Al-Turany, D. Bertini
 * @version 0.1
 * @since 12.01.04
 */

class FairMCApplication : public TVirtualMCApplication
{
  public:
    /** Standard constructor
    *@param name      name
    *@param title     title
    *@param ModList  a TObjArray containing all detectors and modules used in this simulation
    *@param MatName  material file name
    */
    FairMCApplication(const char* name,   const char* title, TObjArray* ModList, const char* MatName);
    /** default constructor
    */
    FairMCApplication();
    /** default destructor
    */
    virtual ~FairMCApplication();
    /** Singelton instance
    */
    static FairMCApplication* Instance();
    virtual void          AddDecayModes();
    /**  Add user defined particles (optional) */
    virtual void          AddParticles();                                   // MC Application
    /** Add user defined ions (optional) */
    virtual void          AddIons();                                        // MC Application
    /**
    *Add user defined Tasks to be executed after each event (optional)
    * @param fTask: Task that has to be excuted during simulation
    */
    void                  AddTask(TTask* fTask);
    /** Define actions at the beginning of the event */
    virtual void          BeginEvent();                                     // MC Application
    /** Define actions at the beginning of primary track */
    virtual void          BeginPrimary();                                   // MC Application
    /** Construct user geometry */
    virtual void          ConstructGeometry();                              // MC Application
    /** Define parameters for optical processes (optional) */
    virtual void          ConstructOpGeometry();                            // MC Application
#if ROOT_VERSION_CODE < 333824
    /** Calculate user field  b at point x */
    virtual void          Field(const Double_t* x, Double_t* b) const;      // MC Application
#endif
    /** Define actions at the end of event */
    virtual void          FinishEvent();                                    // MC Application
    /** Define actions at the end of primary track */
    virtual void          FinishPrimary();                                  // MC Application
    /** Define actions at the end of run */
    void                  FinishRun();
    /** Generate primary particles */
    virtual void          GeneratePrimaries();                              // MC Application
    /** Return detector by name  */
    FairDetector*          GetDetector(const char* DetName);
    /** Return Field used in simulation*/
    FairField*             GetField() {return fxField;}
    /**Return primary generator*/
    FairPrimaryGenerator*  GetGenerator();
    /**Return list of tasks*/
    TTask*                GetListOfTasks();
    FairGenericStack*      GetStack();
    TChain*               GetChain();
    /** Initialize geometry */
    virtual void          InitGeometry();                                   // MC Application
    /** Initialize MC engine */
    void                  InitMC(const char* setup,  const char* cuts);
    /** Initialize Tasks if any*/
    void                  InitTasks();
    /**Define actions at the end of each track */
    virtual void          PostTrack();                                      // MC Application
    /** Define actions at the beginning of each track*/
    virtual void          PreTrack();                                       // MC Application

    /** Clone for worker (used in MT mode only) */
    virtual TVirtualMCApplication* CloneForWorker() const;

    /** Init worker run (used in MT mode only) */
    virtual void InitForWorker() const;

    /** Finish worker run (used in MT mode only) */
    virtual void FinishWorkerRun() const;

    /** Run the MC engine
     * @param nofEvents : number of events to simulate
     */
    void                  RunMC(Int_t nofEvents);
    /**
    * Set the magnetic field for simulation
    * @param field: magnetic field
    */
    void                  SetField(FairField* field);
    /**
     * Set the event generator  for simulation
     * @param fxGenerator: Event generator(s)
     */
    void                  SetGenerator(FairPrimaryGenerator* fxGenerator);
    /**
     * Set the parameter containers needed by Tasks(if any)
     */
    void                  SetParTask();
    /**
     * Switch for using Pythia as external decayer
     * @param decayer: if TRUE pythia will decay particles specifid in the Decay Config macro (see SetPythiaDecayerConfig)
     */
    void                  SetPythiaDecayer(Bool_t decayer) {fPythiaDecayer=decayer;}
    /**
    * set the decay configuration macro to be used by Pythia
    */
    void                  SetPythiaDecayerConfig(const TString decayerConf) {fPythiaDecayerConfig=decayerConf;}
    /**
    * Switch for using the radiation length manager
    */
    void                  SetRadiationLengthReg(Bool_t RadLen);
    /**
    * Switch for using the radiation map manager
    */
    void                  SetRadiationMapReg(Bool_t RadMap);
    /**
    * Switch for debuging the tracking
    */
    void                  SetTrackingDebugMode( Bool_t set ) {fDebug = set;}
    /**
    * Switch for using 2 or 3 body phase-space decay
    * @param  decay: if TRUE 2/3 body phase space decay will be used for particle specified in the User Decay Config macro (see SetUserDecayConfig)
    */
    void                  SetUserDecay(Bool_t decay) {fUserDecay= decay;}
    /**
    * set the decay configuration macro to be used by user decay
    */
    void                  SetUserDecayConfig(const TString decayerConf) {fUserDecayConfig= decayerConf;}
    /** Define action at each step, dispatch the action to the corresponding detectors */
    virtual void          Stepping();                                       // MC Application
    /** Stop the run*/
    virtual void          StopRun();
    /**Define maximum radius for tracking (optional) */
    virtual Double_t      TrackingRmax() const;                             // MC Application
    /** Define maximum z for tracking (optional) */
    virtual Double_t      TrackingZmax() const;                              // MC Application

    void AddMeshList ( TObjArray* meshList );

  private:
    // methods
    void RegisterStack();

    Int_t GetIonPdg(Int_t z, Int_t a) const;

    void UndoGeometryModifications();

    // data members
    /**List of active detector */
    TRefArray*           fActiveDetectors;
    /**List of FairTask*/
    FairTask*             fFairTaskList;//!
    /**detector list (Passive and Active)*/
    TRefArray*           fDetectors;
    /**Map used for dispatcher*/
    TRefArray*           fDetMap;
    /**Iterator for Module list*/
    TIterator*           fModIter; //!
    /**Module list in simulation*/
    TObjArray*           fModules;
    /**Number of sensetive volumes in simulation session*/
    Int_t                fNoSenVolumes; //!
    /**flag for using Pythia as external decayer */
    Bool_t               fPythiaDecayer;
    /** Pythia decay config macro*/
    TString               fPythiaDecayerConfig; //!
    /** Simulation Stack  */
    FairGenericStack*     fStack; //!
    /**Pointer to thr I/O Manager */
    FairRootManager*      fRootManager; //!
    /**List of sensetive volumes in all detectors*/
    TRefArray*           fSenVolumes; //!
    /**Magnetic Field Pointer*/
    FairField*            fxField; //
    /**Primary generator*/
    FairPrimaryGenerator* fEvGen; //
    /**MC Engine 1= Geant3, 2 = Geant4*/
    Int_t                fMcVersion;     // mc Version
    /** Track visualization manager */
    FairTrajFilter*       fTrajFilter; //!
    /**Flag for accepted tracks for visualization*/
    Bool_t               fTrajAccepted; //!
    /**Flag for using user decay*/
    Bool_t               fUserDecay;
    /**User decay config macro*/
    TString               fUserDecayConfig; //!
    /** Debug flag*/
    Bool_t               fDebug;//!
    /**dispatcher internal use */
    FairVolume*          fDisVol;
    /**dispatcher internal use */
    FairDetector*         fDisDet;
    /**dispatcher internal use */
    std::multimap <Int_t, FairVolume* > fVolMap;//!
    /**dispatcher internal use */
    std::multimap <Int_t, FairVolume* >::iterator fVolIter; //!
    /** Track position*/
    /**dispatcher internal use RadLeng*/
    std::map <Int_t, Int_t > fModVolMap;//!
    /**dispatcher internal use RadLen*/
    std::map <Int_t, Int_t >::iterator fModVolIter; //!
    TLorentzVector fTrkPos; //!
    /** Flag for Radiation length register mode  */
    Bool_t   fRadLength;  //!

    /**Radiation length Manager*/
    FairRadLenManager*  fRadLenMan; //!
    /** Flag for Radiation map register mode  */
    Bool_t   fRadMap;     //!
    /**Radiation Map Manager*/
    FairRadMapManager*  fRadMapMan; //!
    /**Radiation map Grid Manager*/
    FairRadGridManager* fRadGridMan; //!

    FairEventHeader*    fEventHeader; //!

    FairMCEventHeader*  fMCEventHeader; //!
    /** list of senstive detectors used in the simuation session*/
    std::list <FairDetector *> listActiveDetectors; //!
    /** list of all detectors used in the simuation session*/
    std::list <FairDetector *> listDetectors;  //!

    
    ClassDef(FairMCApplication,4)  //Interface to MonteCarlo application

  private:
    /** Protected copy constructor */
    FairMCApplication(const FairMCApplication&);
    /** Protected assignment operator */
    FairMCApplication& operator=(const FairMCApplication&);

    FairRunInfo fRunInfo;//!
    Bool_t      fGeometryIsInitialized;
};

// inline functions

inline FairMCApplication* FairMCApplication::Instance()
{ return static_cast<FairMCApplication*>(TVirtualMCApplication::Instance());}

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMODULE_H
#define FAIRMODULE_H

#include "TNamed.h"                     // for TNamed

#include "FairGeoInterface.h"           // for FairGeoInterface
#include "FairGeoLoader.h"              // for FairGeoLoader
#include "FairGeoNode.h"                // for FairGeoNode
#include "FairGeoVolume.h"              // for FairGeoVolume
#include "FairLogger.h"                 // for FairLogLevel::INFO, etc
#include "FairRun.h"                    // for FairRun
#include "FairRuntimeDb.h"              // for FairRuntimeDb

#include "Rtypes.h"                     // for Bool_t, Int_t, etc
#include "TList.h"                      // for TList (ptr only), TListIter
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString, operator!=

#include <stddef.h>                     // for NULL
#include <string>                       // for string

class FairVolumeList;
class FairVolume;
class TArrayI;
class TGeoMatrix;
class TGeoNode;
class TGeoVolume;
class TGeoMedium;
class TRefArray;

/**
 * Base class for constructing all detecors and passive volumes
 * @author M. Al-Turany, Denis Bertini
 * @version 1.0
 * @since 01.04.08 M.Al-Turany
 * Add methods to construct geometry via ROOT files
 * Add some documentation
 *
 * Changelog: 29.02.2012 [O.Merle] Fixed missing material assignment for top volume.
 *                                 ... and please - add some documentation to your code.
 */
class FairModule:  public TNamed
{
  public:
    /**default ctor*/
    FairModule();
    /**Standard ctor*/
    FairModule(const char* Name, const char* title, Bool_t Active=kFALSE);
    /**default dtor*/
    virtual  ~FairModule();
    /**Print method should be implemented in detector or module*/
    virtual void        Print(Option_t*) const {;}
    /**Set the geometry file name o be used*/
    virtual void        SetGeometryFileName(TString fname, TString geoVer="0");
    /**Get the Geometry file name*/
    virtual TString     GetGeometryFileName() {return  fgeoName ;}
    /**Get the geometry file version if used*/
    virtual TString     GetGeometryFileVer() {return   fgeoVer ;}
    /**method called from the MC application to construct the geometry, has to be implimented by user*/
    virtual void        ConstructGeometry();
    /**method called from the MC application to set optical geometry properties*/
    virtual void        ConstructOpGeometry();
    /**construct geometry from root files (TGeo)*/
    virtual void        ConstructRootGeometry();
    /**construct geometry from standard ASSCII files (Hades Format)*/
    virtual void        ConstructASCIIGeometry();
    /** Modify the geometry for the simulation run using methods of the Root geometry package */
    virtual void        ModifyGeometry() {;}
    /**construct geometry from GDML files*/
    virtual void        ConstructGDMLGeometry(TGeoMatrix*);
    /** Clone this object (used in MT mode only)*/
    virtual FairModule* CloneModule() const;
    /** Init worker run (used in MT mode only) */
    virtual void BeginWorkerRun() const {;}
    /** Finish worker run (used in MT mode only) */
    virtual void FinishWorkerRun() const {;}

    /**template function to construct geometry. to be used in derived classes.*/
    template<class T, class U>
    void ConstructASCIIGeometry(T dataType1, TString containerName="", U datatype2 = NULL);

    /**Set the sensitivity flag for volumes, called from ConstructASCIIRootGeometry(), and has to be implimented for detectors
     * which use ConstructASCIIRootGeometry() to build the geometry */
    virtual Bool_t      CheckIfSensitive(std::string name);
    /**called from ConstructRootGeometry()*/
    virtual void        ExpandNode(TGeoNode* Node);
    /**called from ConstructGDMLGeometry()*/
    virtual void        ExpandNodeForGDML(TGeoNode*);
    /**return the MC id of a volume named vname*/
    virtual Int_t       getVolId( const TString& ) const {return 0;}
    /**return the detector/Module id (which was set in the sim macro for the detector)*/
    Int_t               GetModId() {return fModId;}
    /**Set the verbose level in this detector*/
    void                SetVerboseLevel(Int_t level) {fVerboseLevel=level;}
    /**return the detector status */
    Bool_t              IsActive() {return fActive;}
    /**set the detector/module id*/
    void                SetModId(Int_t id) {fModId=id;}
    /** Set the name of the mother volume to which a new geometry is added.
     ** This function is needed for geometries which are defined as ROOT geometry manager.
     **/
    void                SetMotherVolume(TString volName) {fMotherVolumeName=volName;}
    /**called from ConstuctASCIIGeometry*/
    void   ProcessNodes ( TList* aList );
    /**Set the parameter containers*/
    virtual  void       SetParContainers() {;}
    /** Initialize everything which has to be done before the construction and modification
     ** of the geometry. Mostly this is needed to read data from the parameter containers.*/
    virtual  void       InitParContainers() {;}
    /**return the geo parameter of this detector/module*/
    TList* GetListOfGeoPar() { return flGeoPar;}

    /**list of volumes in a simulation session*/
    static              FairVolumeList*   vList; //!
    /**total number of volumes in a simulaion session*/
    static Int_t        fNbOfVolumes;  //!
    /**list of all sensitive volumes in  a simulaion session*/
    static TRefArray*   svList;   //!

    static TArrayI*     volNumber; //!
    TString             fMotherVolumeName; //!
    FairVolume*   getFairVolume(FairGeoNode* fNode);
    void    AddSensitiveVolume(TGeoVolume* v);
  private:
    /** Re-implimented from ROOT:  TGeoMatrix::SetDefaultName()  */
    void SetDefaultMatrixName(TGeoMatrix* matrix);
    void AssignMediumAtImport(TGeoVolume* v);  // O.Merle, 29.02.2012 - see impl.

    /**called from ConstructGDMLGeometry. Changes default ID created by TGDMLParse*/
    void ReAssignMediaId();
    void swap(FairModule& other) throw();

  protected:
    FairModule(const FairModule&);
    FairModule& operator=(const FairModule&);
    TString             fgeoVer;
    TString             fgeoName;
    Int_t               fModId;
    Bool_t              fActive;
    Int_t               fNbOfSensitiveVol; //!
    Int_t               fVerboseLevel;
    TList*              flGeoPar; //!  list of Detector Geometry parameters
    Bool_t              kGeoSaved; //! flag for initialisation

    ClassDef( FairModule,4)
};

template<class T, class U>
void FairModule::ConstructASCIIGeometry(T dataType1, TString containerName, U)
{
  FairGeoLoader* loader=FairGeoLoader::Instance();
  FairGeoInterface* GeoInterface =loader->getGeoInterface();
  T* MGeo=new T();
  MGeo->print();
  MGeo->setGeomFile(GetGeometryFileName());
  GeoInterface->addGeoModule(MGeo);
  Bool_t rc = GeoInterface->readSet(MGeo);
  if ( rc ) { MGeo->create(loader->getGeoBuilder()); }

  TList* volList = MGeo->getListOfVolumes();
  // store geo parameter
  FairRun* fRun = FairRun::Instance();
  FairRuntimeDb* rtdb= FairRun::Instance()->GetRuntimeDb();

  dataType1 = *MGeo;

  if ( "" != containerName) {
    LOG(INFO) << "Add GeoNodes for "<< MGeo->getDescription()
              << " to container " << containerName << FairLogger::endl;

    //    U par=(U)(rtdb->getContainer(containerName));
    U*      par=static_cast<U*>(rtdb->getContainer(containerName));
    TObjArray* fSensNodes = par->GetGeoSensitiveNodes();
    TObjArray* fPassNodes = par->GetGeoPassiveNodes();

    TListIter iter(volList);
    FairGeoNode* node   = NULL;
    FairGeoVolume* aVol=NULL;

    while( (node = static_cast<FairGeoNode*>(iter.Next())) ) {
      aVol = dynamic_cast<FairGeoVolume*> ( node );
      if ( node->isSensitive()  ) {
        fSensNodes->AddLast( aVol );
      } else {
        fPassNodes->AddLast( aVol );
      }
    }
    ProcessNodes( volList );
    par->setChanged();
    par->setInputVersion(fRun->GetRunId(),1);

  }
}


#endif //FAIRMODULE_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/// Class FAIRParticle
/// ------------------
/// Extended TParticle with persistent pointers to mother and daughters
/// particles  (Ivana Hrivnacova, 5.4.2002)
/// Used to define particles which will be added to Geant3/4 (M. Al-Turany)

#ifndef FAIR_PARTICLE_H
#define FAIR_PARTICLE_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Int_t, Double_t, Bool_t, etc
#include "TMCParticleType.h"            // for TMCParticleType
#include "TRef.h"                       // for TRef
#include "TRefArray.h"                  // for TRefArray
#include "TString.h"                    // for TString

class TParticle;

class FairParticle : public TObject
{
  public:
    FairParticle(Int_t id, TParticle* particle);
    FairParticle(Int_t id, TParticle* particle, FairParticle* mother);
    FairParticle(const char* name, Int_t z, Int_t a, Int_t s,Double_t mass , Int_t q, Bool_t stable, Double_t decaytime);
    FairParticle(const char* name, Int_t z, Int_t a, Double_t mass , Int_t q, Bool_t stable, Double_t decaytime);
    FairParticle( Int_t pdg , const TString name, TMCParticleType mcType, Double_t mass, Double_t charge,
                  Double_t lifetime, const TString pType="Ion",  Double_t width=0, Int_t iSpin=0, Int_t iParity=0,
                  Int_t iConjugation=0, Int_t iIsospin=0, Int_t iIsospinZ=0, Int_t gParity=0, Int_t lepton=0,
                  Int_t baryon=0,Bool_t stable=kFALSE);

    FairParticle();

    virtual ~FairParticle();

    // methods
    void SetMother(FairParticle* particle);
    void AddDaughter(FairParticle* particle);
    virtual void  Print(Option_t* option = "") const;
    void PrintDaughters() const;

    // get methods
    Int_t            GetPDG() const;
    TParticle*       GetParticle() const;
    FairParticle*     GetMother() const;
    Int_t            GetNofDaughters() const;
    FairParticle*     GetDaughter(Int_t i) const;
    virtual const char* GetName() const {return fname.Data();}
    TMCParticleType  GetMCType()  {return fmcType;}
    Double_t         GetMass()          {return fmass;}
    Double_t         GetCharge()        {return fcharge;}
    Double_t         GetDecayTime()     {return fDecayTime;}
    const TString&   GetPType()         {return fpType;}
    Double_t         GetWidth()         {return fwidth;}
    Int_t            GetSpin()          {return fiSpin;}
    Int_t            GetiParity()        {return fiParity;}
    Int_t            GetConjugation()   {return fiConjugation;}
    Int_t            GetIsospin()       {return fiIsospin;}
    Int_t            GetIsospinZ()      {return fiIsospinZ;}
    Int_t            GetgParity()        {return fgParity;}
    Int_t            GetLepton()        {return flepton;}
    Int_t            GetBaryon()        {return fbaryon;}
    Bool_t           IsStable()         {return fstable;}

  private:

    FairParticle(const FairParticle& P);
    FairParticle& operator= (const  FairParticle&) {return *this;}
    // data members
    Int_t     fpdg;
    TParticle*    fParticle;
    TRef          fMother;
    TRefArray     fDaughters;
    const TString            fname;
    TMCParticleType   fmcType;
    Double_t    fmass;
    Double_t    fcharge;
    Double_t    fDecayTime;
    const TString   fpType;
    Double_t    fwidth;
    Int_t     fiSpin;
    Int_t     fiParity;
    Int_t     fiConjugation;
    Int_t     fiIsospin;
    Int_t     fiIsospinZ;
    Int_t     fgParity;
    Int_t     flepton;
    Int_t     fbaryon;
    Bool_t    fstable;

    ClassDef(FairParticle,3) // Extended TParticle
};

#endif //FAIR_PARTICLE_H   


/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH *
 *                                                                              *
 *              This software is distributed under the terms of the *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3, *
 *                  copied verbatim in the file "LICENSE" *
 ********************************************************************************/

/** FairPrimaryGenerator.h
 *@author V.Friese  <v.friese@gsi.de>
 *
The FairPrimaryGenerator is responsible for the handling of the MC input.
Several input generators can be registered to it; these have to be
derived from the FairGenerator class. The FairPrimaryGenerator defines
position and (optionally) smearing of the primary vertex.
This class should be instantised only once.

Modified 05.06.07:  add a method DoTracking(Bool_t) to be able to switch on/off
the tracking from the macro (M. Al-Turany)

**/

#ifndef FAIRPRIMARYGENERATOR_H
#define FAIRPRIMARYGENERATOR_H

#include "TNamed.h" // for TNamed

#include "FairGenerator.h" // for FairGenerator

#include "Riosfwd.h"   // for ostream
#include "Rtypes.h"    // for Double_t, Bool_t, Int_t, etc
#include "TObjArray.h" // for TObjArray
#include "TVector3.h"  // for TVector3

#include <iostream> // for operator<<, basic_ostream, etc

class FairGenericStack;
class FairMCEventHeader;
class TF1;
class TIterator;

class FairPrimaryGenerator : public TNamed {

public:
  /** Default constructor. **/
  FairPrimaryGenerator();

  /** Constructor with name and title **/
  FairPrimaryGenerator(const char *name, const char *title = "FAIR Generator");

  /** Destructor. **/
  virtual ~FairPrimaryGenerator();

  /** Initialize the generater (if needed!)*/
  virtual Bool_t Init();

  /** Register a generator derived from FairGenerator.  **/
  void AddGenerator(FairGenerator *generator) {
    if (!fGenList) {
      std::cout << "Empty fGenList pointer ! " << std::endl;
      return;
    }
    fGenList->Add(generator);
  }

  /** Public method GenerateEvent
      To be called at the beginning of each event from FairMCApplication.
      Generates an event vertex and calls the ReadEvent methods from the
      registered generators.
      *@param pStack The particle stack
      *@return kTRUE if successful, kFALSE if not
      **/
  virtual Bool_t GenerateEvent(FairGenericStack *pStack);

  /** Public method AddTrack
      Adding a track to the MC stack. To be called within the ReadEvent
      methods of the registered generators.
      *@param pdgid Particle ID (PDG code)
      *@param px,py,pz Momentum coordinates [GeV]
      *@param vx,vy,vz Track origin relative to event vertex
      **/
  virtual void AddTrack(Int_t pdgid, Double_t px, Double_t py, Double_t pz,
                        Double_t vx, Double_t vy, Double_t vz,
                        Int_t parent = -1, Bool_t wanttracking = true,
                        Double_t e = -9e9, Double_t tof = 0.,
                        Double_t weight = 0.);

  /** Clone this object (used in MT mode only) */
  virtual FairPrimaryGenerator* ClonePrimaryGenerator() const;

  /** Set beam position and widths.
   *@param beamX0      mean x position of beam at target
   *@param beamY0      mean y position of beam at target
   *@param beamSigmaX  Gaussian beam width in x
   *@param beamSigmaY  Gaussian beam width in y
   **/
  void SetBeam(Double_t beamX0, Double_t beamY0, Double_t beamSigmaX,
               Double_t beamSigmaY);

  /** Set nominal beam angle and angle widths.
   *@param beamAngleX0      mean x angle of beam at target
   *@param beamAngleY0      mean y angle of beam at target
   *@param beamAngleSigmaX  Gaussian beam angle width in x
   *@param beamAngleSigmaY  Gaussian beam angle width in y
   **/
  void SetBeamAngle(Double_t beamAngleX0, Double_t beamAngleY0,
                    Double_t beamAngleSigmaX, Double_t beamAngleSigmaY);

  /** Public method SetEventPlane
   **@param phiMin   Lower limit for event plane angle [rad]
   **@param phiMax   Upper limit for event plane angle [rad]
   **If set, an event plane angle will be generated with flat
   **distrtibution between phiMin and phiMax.
   **/
  void SetEventPlane(Double_t phiMin, Double_t phiMax);

  /** Set target position and thickness.
   *@param targetZ   z position of target center
   *@param targetDz  full target thickness
   **/
  void SetTarget(Double_t targetZ, Double_t targetDz);

  /** Set target position for multiple tagets. The thickness
   * is the same for all targets.
   *@param nroftargets   number of targets
   *@param *targetZ      z positions of target center
   *@param targetDz      full target thickness
   **/
  void SetMultTarget(Int_t nroftargets, Double_t *targetZ, Double_t targetDz);

  /** Enable vertex smearing in z and/or xy direction **/
  void SmearVertexZ(Bool_t flag);
  void SmearGausVertexZ(Bool_t flag);
  void SmearVertexXY(Bool_t flag);
  void SmearGausVertexXY(Bool_t flag);

  TObjArray *GetListOfGenerators() { return fGenList; }

  /** Set the pointer to the MCEvent **/
  void SetEvent(FairMCEventHeader *event) {
    fEvent = event;
  };

  /** Accessor to the MCEvent **/
  FairMCEventHeader *GetEvent() {
    return fEvent;
  };

  /** Swich on/off the tracking of a particle*/

  void DoTracking(Bool_t doTracking = kTRUE) { fdoTracking = doTracking; }

  Int_t GetTotPrimary() { return fTotPrim; }

protected:
  /**  Copy constructor */
  FairPrimaryGenerator(const FairPrimaryGenerator&);
  /**  Assignment operator */
  FairPrimaryGenerator &operator=(const FairPrimaryGenerator&);

  /**  Nominal beam position at target in x [cm] */
  Double_t fBeamX0;
  /** Nominal beam position at target in y [cm]*/
  Double_t fBeamY0;
  /** Beam width (Gaussian) in x [cm]*/
  Double_t fBeamSigmaX;
  /**  Beam width (Gaussian) in y [cm]*/
  Double_t fBeamSigmaY;

  /**  Nominal beam angle at target in x [rad] */
  Double_t fBeamAngleX0;
  /**  Nominal beam angle at target in y [rad] */
  Double_t fBeamAngleY0;
  /**  Actual beam angle at target in x [rad] */
  Double_t fBeamAngleX;
  /**  Actual beam angle at target in y [rad] */
  Double_t fBeamAngleY;
  /** Beam angle width (Gaussian) in x [rad]*/
  Double_t fBeamAngleSigmaX;
  /** Beam angle width (Gaussian) in y [rad]*/
  Double_t fBeamAngleSigmaY;
  /** Actual beam direction at the vertex */
  TVector3 fBeamDirection;

  /** Lower limit for the event plane rotation angle [rad] */
  Double_t fPhiMin;
  /** Upper limit for the event plane rotation angle [rad] */
  Double_t fPhiMax;
  /** Actual event plane rotation angle [rad] */
  Double_t fPhi;

  /**  Nominal z position of center of targets [cm]*/
  Double_t *fTargetZ; //!
  /**  Number of targets;*/
  Int_t fNrTargets;
  /**  Full target thickness [cm]*/
  Double_t fTargetDz;

  /** Vertex position of current event [cm]*/
  TVector3 fVertex;

  /** Number of primary tracks in current event*/
  Int_t fNTracks;

  /**  Flag for uniform vertex smearing in z*/
  Bool_t fSmearVertexZ;
  /**  Flag for gaus vertex smearing in z*/
  Bool_t fSmearGausVertexZ;
  /**  Flag for vertex smearing in xy*/
  Bool_t fSmearVertexXY;
  /**  Flag for gaus vertex smearing in xy*/
  Bool_t fSmearGausVertexXY;
  /**  Flag for beam gradient calculation*/
  Bool_t fBeamAngle;
  /**  Flag for event plane rotation*/
  Bool_t fEventPlane;

  /**  Pointer to MC stack*/
  FairGenericStack *fStack; //!
  /**  List of registered generators */
  TObjArray *fGenList;
  /**  Iterator over generator list */
  TIterator *fListIter; //!
  /**  Pointer to MCEventHeader */
  FairMCEventHeader *fEvent; //!
  /** go to tracking  */
  Bool_t fdoTracking; //!
  /** Number of MC tracks before a Generator is called, needed for MC index
   * update */
  Int_t fMCIndexOffset; //!
  /** Number of all primaries of this run*/
  static Int_t fTotPrim; //!
  /** Event number (Set by the primary generator if not set already by one of
      the specific generators
   **/
  Int_t fEventNr;

  /** Private method MakeVertex. If vertex smearing in xy is switched on,
      the event vertex is smeared Gaussianlike in x and y direction
      according to the mean beam positions and widths set by the
      SetBeam method. If vertex smearing in z is switched on, the z
      coordinate of the event vertex is flatly distributed over the
      extension of the target.
      To be called at the beginning of the event from the
      GenerateEvent method.
  **/
  void MakeVertex();

  /** Private method MakeBeamAngle. If beam angle smearing in xy
  is switched on, all tracks in an event are rotated by a Gaussianlike
  angle distribution around the x and y axis according to the mean
  beam angle and angle widths set by the SetBeamAngle method.
  To be called at the beginning of the event from the GenerateEvent
  method.
  **/
  void MakeBeamAngle();

  /** Private method MakeEventPlane. If the rotation of the event around the
      z-axis by a random angle is switched on, the complete event is rotated
      by the chosen angle. This function is called at the beginning of the
      event from the GenerateEvent method. The function pick a random
      rotation angle between fPhiMin and fPhiMax which are set using the
      function SetEventPlane.
  **/
  void MakeEventPlane();

  ClassDef(FairPrimaryGenerator, 5);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNIDGENERATOR_H
#define FAIRRUNIDGENERATOR_H

#include <time.h>               // IWYU pragma: keep for timespec
// IWYU pragma: no_include <sys/_structs.h>

typedef unsigned char      uint8_t;
typedef unsigned short int uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned char      uuid_t[16];

class FairRunIdGenerator
{
    struct uuid {
      uint32_t time_low;
      uint16_t time_mid;
      uint16_t time_hi_and_version;
      uint16_t clock_seq;
      uint8_t node[6];
    };

    struct timespec fTimeSpec;

    int get_random_fd(void);
    void get_random_bytes(void*, int);
    int get_node_id(unsigned char*);
    int get_clock(uint32_t*, uint32_t*, uint16_t*);
    void uuid_generate_time(uuid_t);
    void uuid_generate_random(uuid_t);
    void uuid_generate(uuid_t);
    void uuid_pack(const struct uuid*, uuid_t);
    void uuid_unpack(const uuid_t, struct uuid*);
  public:
    struct timespec getTimeSpec() {return fTimeSpec;}
    struct timespec getTimeSpecFromTID( unsigned  int ms);
    unsigned  int getTID();

  public:
    FairRunIdGenerator() : fTimeSpec() {}
    ~FairRunIdGenerator() {}
    unsigned int generateId(void);



};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIR_VOLUME_H
#define FAIR_VOLUME_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Int_t, FairVolume::Class, etc
#include "TString.h"                    // for TString
#include "FairModule.h"
#include "FairDetector.h"
class FairGeoNode;

/**
 * This Object is only used for internal book keeping!
 * @author M. Al-Turany, D. Bertini
 * @version 0.1
 * @since 12.01.04
 */


class FairVolume : public TNamed
{

  public:

    FairVolume();
    FairVolume(TString name, Int_t id=0, Int_t detid=0,FairModule* fMod=0);
    virtual ~FairVolume();

    //    const char*  GetName() { return fName.Data();}
    //    TString getName() { return fName;}

    void setRealName( TString name ) { fRealName = name;}
    const char* getRealName() { return fRealName.Data();}
    Int_t getVolumeId() { return fVolumeId;}
    Int_t getModId() { return  fModId;}
    void  setModId(Int_t id) { fModId=id;}
    void  setCopyNo(Int_t id) { fCopyNo=id;}
    void  setVolumeId ( Int_t id ) {fVolumeId= id;}
    void  setGeoNode(FairGeoNode* d) {fNode=d;}
    void  setMotherId(Int_t fM) {fMotherId=fM;}
    void  setMotherCopyNo(Int_t CopyNo) {fMotherCopyNo=CopyNo;}

    FairModule*   GetModule()     {return fModule;}
    FairDetector* GetDetector() { return fDetector;}
    void SetModule(FairModule* mod) {
        fModule=mod;
        if (mod->InheritsFrom("FairDetector")){
           fDetector=dynamic_cast<FairDetector *>(mod);
        }
    }

    Int_t getMCid() {return fMCid;}
    Int_t getCopyNo() { return fCopyNo;}
    void  setMCid(Int_t id) {fMCid=id;}
    FairGeoNode* getGeoNode() {return fNode;}
    Int_t getMotherId() { return fMotherId;}
    Int_t getMotherCopyNo() {return fMotherCopyNo;}


  private:
    FairVolume(const FairVolume&);
    FairVolume& operator=(const FairVolume&);

    //    TString fName;   /**Volume Name in MC*/
    TString fRealName; /**Volume Name in ASCII file*/
    Int_t fVolumeId;       /**Volume Id in GeoManager*/
    Int_t fModId;          /**Module Id in which this volume exist*/
    Int_t fMCid;   /**Volume Id in MC*/
    Int_t fCopyNo;         /**Volume Copy No*/
    Int_t fMotherId; /**Mother Volume Id*/
    Int_t fMotherCopyNo;   /**Mother Volume Copy No*/
    FairDetector* fDetector; /** The Detector which will proccess the hits for this volume*/
    FairModule*   fModule;    /**The Module in which the volume is */
    FairGeoNode*  fNode;     /**Node corresponding to this volume*/
    

    ClassDef(FairVolume,2) // Volume Definition

};

#endif //
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIR_VOLUMELIST_H
#define FAIR_VOLUMELIST_H

#include "TObject.h"                    // for TObject

#include "FairVolume.h"

#include "Rtypes.h"                     // for Int_t, etc
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString

//class FairVolume;

/**
* This Object is only used for internal book keeping!
* @author M. Al-Turany, D. Bertini
* @version 0.1
* @since 12.01.04
*/

class FairVolumeList : public TObject
{
  private:
    TObjArray* fData;
    FairVolumeList(const FairVolumeList&);
    FairVolumeList& operator=(const FairVolumeList&);

  public:
    FairVolumeList();
    virtual ~FairVolumeList();

    FairVolume* getVolume( TString* name );
    Int_t getVolumeId( TString* name );

    FairVolume* findObject( TString name );
    void addVolume( FairVolume* elem);

    Int_t getEntries () { return fData->GetEntries();}
    FairVolume* At(Int_t pos ) { return ( dynamic_cast<FairVolume*>(fData->At(pos))); }

    ClassDef(FairVolumeList,1) // Volume List
};

#endif //FAIR_VOLUMELIST_H


/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//* $Id: */

// -------------------------------------------------------------------------
// -----                     FairEventBuilder header file                -----
// -----                  Created 23/09/2013 by R. Karabowicz          -----
// -------------------------------------------------------------------------


/** FairEventBuilder
 *@author Radoslaw Karabowicz <r.karabowicz@gsi.de>
 *@since 23/09/2013
 *@version 1.0
 **
 ** FairRoot base task for the event buffers.
 ** The tasks may:
 ** 1. analyze data to reconstruct event times or other characteristics
 **    in the function TClonesArray* FindEvents(), that returns
 **    TClonesArray of FairRecoEvents
 ** 2. identify the data that could belong to event in the
 **    function and insert this identified data to the output TClonesArrays
 **    in the function StoreEventData(event)
 ** The implementations may be using any or both of the above functions.
 **/


#ifndef FAIREVENTBUILDER_H
#define FAIREVENTBUILDER_H 1

#include "FairWriteoutBuffer.h"
#include "FairRecoEventHeader.h"

#include "TStopwatch.h"
#include "TString.h"

#include <map>
#include <set>
#include <vector>

class TClonesArray;
//class FairRecoEventHeader;

class FairEventBuilder : public FairWriteoutBuffer
{


  public :

    /** Default constructor **/
    FairEventBuilder();


    /** Constructor with task name **/
    FairEventBuilder(TString branchName, TString className, TString folderName, Bool_t persistance);


    /** Destructor **/
    virtual ~FairEventBuilder();

    virtual void WriteOutAllDeadTimeData();

    virtual std::vector<std::pair<double, FairRecoEventHeader*> > FindEvents() = 0;
    virtual void          StoreEventData(FairRecoEventHeader* /*recoEvent*/) = 0;

    void  SetIdentifier(Int_t ident) {
      fIdentifier=ident;
    }
    Int_t GetIdentifier() {
      return fIdentifier;
    }

    virtual Bool_t Init() = 0;

    virtual void Print(Option_t *option="") const = 0;

    /** Finish at the end of each event **/
    virtual void Finish();

    Double_t AllowedTime() {
      return fMaxAllowedEventCreationTime;
    };
    void SetMaxAllowedTime(Double_t td) {
      fMaxAllowedEventCreationTime = td;
    };

    void    SetBuilderName(const char* name) {
      fBuilderName=name;
    }
    TString GetBuilderName() {
      return fBuilderName;
    }

  private:

    TString    fBuilderName;

    TStopwatch fTimer;
    Double_t   fExecTime;

    Int_t      fIdentifier;
    Double_t   fMaxAllowedEventCreationTime;

    ClassDef(FairEventBuilder,1);

};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//* $Id: */

// -------------------------------------------------------------------------
// -----                     FairEventBuilderManager header file              -----
// -----                  Created 20/09/2013 by R. Karabowicz          -----
// -------------------------------------------------------------------------


/** FairEventBuilderManager
 *@author Radoslaw Karabowicz <r.karabowicz@gsi.de>
 *@since 20/09/2013
 *@version 1.0
 **
 ** FairRoot general task for recreating events in Time-Based reconstruction mode.
 ** Various experiments should implement their own version of Event Builder.
 ** The main member of the task is vector of reconstructed events fRecoEvents.
 ** It also contains a vector of implementations of FairEventBuilders, that are
 ** responsible for feeding fRecoEvents vector via FindEvents() function.
 **
 ** The heart of the experiment-specific implemenations is
 ** the AnalyzeAndExtractEvents() function, which should interpret
 ** the experimental data to reconstruct events.
 **/


#ifndef FAIREVENTBUILDERMANAGER_H
#define FAIREVENTBUILDERMANAGER_H 1

#include "FairTask.h"
#include "FairEventBuilder.h"

#include "TStopwatch.h"

#include <map>
#include <set>
#include <vector>

class TClonesArray;

class FairEventBuilderManager : public FairTask
{


  public :

    /** Default constructor **/
    FairEventBuilderManager();


    /** Constructor with task name **/
    FairEventBuilderManager(const char* name, Int_t iVerbose=1);


    /** Destructor **/
    virtual ~FairEventBuilderManager();


    /** Execution **/
    virtual void Exec(Option_t* opt);


    /** Adding FairEventBuilder **/
    virtual void AddEventBuilder(FairEventBuilder* eventBuilder);

  protected:

    std::vector<FairEventBuilder*> fEventBuilders;
    std::vector<std::vector<std::pair<double,FairRecoEventHeader*> > >  fPossibleEvents;


    /** Fill events from various builders **/
    virtual Double_t FillEventVectors();


    /** Analyze and extract events - experiment specific **/
    virtual void AnalyzeAndExtractEvents(Double_t maxEventTimeAllowed) = 0;


    /** Create output tree structure **/
    virtual void CreateAndFillEvent(FairRecoEventHeader* recoEvent);

  private:

    /** Get parameter containers **/
    virtual void SetParContainers();


    /** Intialisation **/
    virtual InitStatus Init();


    /** Reinitialisation **/
    virtual InitStatus ReInit();


    /** Finish at the end of each event **/
    virtual void Finish();


    ClassDef(FairEventBuilderManager,1);

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
// -----                       FairEventHeader header file                      -----
// -----          Created 08/09/04                 D.Bertini           -----
// -------------------------------------------------------------------------

#ifndef FAIREVENTHEADER_H
#define FAIREVENTHEADER_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Int_t, Double_t, UInt_t, etc

/**
 *  Event Header Class
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairEventHeader : public TNamed
{

  public:

    /** Default constructor */
    FairEventHeader();

    /** Get the run ID for this run*/
    UInt_t GetRunId() {return fRunId;}

    /** Get the MC time for this event*/
    Double_t GetEventTime() {return fEventTime;}

    /** Get the MC input file Id for this event*/
    Int_t GetInputFileId() {return fInputFileId;}

    /**The entry number in the original MC chain */
    Int_t GetMCEntryNumber() {return fMCEntryNo;}

    /** Set the run ID for this run
    * @param runid : unique run id
    */
    void SetRunId(UInt_t runid) {fRunId=runid;}

    /** Set the MC time for this event
     * @param time : time in ns
     */
    void SetEventTime(Double_t time) {fEventTime=time;}

    /** Set the Signal file Id for this event*/
    void SetInputFileId(Int_t id) {fInputFileId=id;}

    /**The entry number in the original MC chain */
    void SetMCEntryNumber(Int_t id) {fMCEntryNo=id;}

    /**
     * Destructor
     */
    virtual ~FairEventHeader();
    virtual void Register();
  protected:

    /** Run Id */
    UInt_t fRunId;
    /** Event Time **/
    Double_t  fEventTime;
    /** Input file identifier, the file description is in the File header*/
    Int_t     fInputFileId;
    /**MC entry number from input chain*/
    Int_t     fMCEntryNo;


    ClassDef(FairEventHeader,3)

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
// -----                         FairFileHeader source file           -----
// -----            Created 20/04/11                 M.Al-Turany        -----
// -------------------------------------------------------------------------

#ifndef FAIRFILEHEADER_H
#define FAIRFILEHEADER_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for UInt_t, etc
#include "TString.h"                    // for TString

class FairFileInfo;
class TFile;
class TList;

/**
 *  File Header Class
   **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairFileHeader : public TNamed
{

  public:

    /** Default constructor */
    FairFileHeader();

    /**Add a class name of a task*/
    void AddTaskClassName(TString taskname);

    /** Set the run ID for this run
       * @param runid : unique run id
       */
    void SetRunId(UInt_t runid) {fRunId=runid;}

    /** Get the run ID for this run*/
    UInt_t GetRunId() {return fRunId;}

    /** Return the list of tasks class names */
    TList* GetListOfTasks() {return fTaskList;}

    void AddInputFile(TFile* f, UInt_t id, UInt_t ChId);

    /**
     * Destructor
     */
    virtual ~FairFileHeader();


    FairFileInfo* GetFileInfo(UInt_t id, UInt_t ChId);




  protected:
    /** Run Id */
    UInt_t fRunId;

    /**list of TObjStrings presenting the class names of tasks used to produce this file */
    TList* fTaskList;

    /**list of TObjStrings presenting the input files used to produce this file*/
    TList* fFileList;

  private:
    FairFileHeader(const FairFileHeader&);
    FairFileHeader& operator=(const FairFileHeader&);


    ClassDef(FairFileHeader,2)

};
#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//  FairFileInfo.h
//  Created by Mohammad Al-Turany on 6/21/11.
//
#ifndef FAIRFILEINFO_H
#define FAIRFILEINFO_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for UInt_t, FairFileInfo::Class, etc
#include "TString.h"                    // for TString

class TFile;

class FairFileInfo : public TNamed
{
  public:

    FairFileInfo();
    FairFileInfo(TFile* file, UInt_t id,  UInt_t ChId);
    virtual  ~FairFileInfo();


    TString     GetPath()          {return fPath;}
    UInt_t      GetSize()          {return fSize;}
    UInt_t      GetIdentifier()    {return fIdentifier;}
    UInt_t      GetOrderInChain()  {return fInChainId;}

    void        Print(Option_t* option="") const;

    void        SetPath(TString path) {fPath = path;}
    void        SetSize(UInt_t  size) {fSize =size;}
    void        SetIdentifier(UInt_t  id) {fIdentifier =id;}
    void        SetOrderInChain(UInt_t id) {fInChainId =id;}



  protected:
    /** Full path of file*/
    TString fPath;
    /** size of file in bytes*/
    UInt_t  fSize;
    /** Signal file identifier used*/
    UInt_t  fIdentifier;
    /** file order in the chain*/
    UInt_t  fInChainId;

  private:
    FairFileInfo(const FairFileInfo&);
    FairFileInfo& operator=(const FairFileInfo&);

    ClassDef(FairFileInfo,1)
};

#endif //FAIRFILEINFO_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRHIT_H
#define FAIRHIT_H

#include "FairTimeStamp.h"              // for FairTimeStamp

#include "Rtypes.h"                     // for Double_t, Int_t, Double32_t, etc
#include "TVector3.h"                   // for TVector3

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

/**
 * Abstract base class for reconstructed hits in the FAIR detectors.
  **@author V.Friese <v.friese@gsi.de>
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairHit : public FairTimeStamp
{

  public:

    /** Default constructor **/
    FairHit();


    /** Constructor with hit parameters **/
    FairHit(Int_t detID, TVector3& pos, TVector3& dpos, Int_t index);

    /** Destructor **/
    virtual ~FairHit();


    /** Accessors **/
    Double_t GetDx()            const { return fDx;                     };
    Double_t GetDy()            const { return fDy;                     };
    Double_t GetDz()            const { return fDz;                     };
    Int_t    GetRefIndex()      const { return fRefIndex;               };
    void PositionError(TVector3& dpos) const;
    Int_t    GetDetectorID()    const { return fDetectorID;             };
    Double_t GetX()             const { return fX;                      };
    Double_t GetY()             const { return fY;                      };
    Double_t GetZ()             const { return fZ;                      };
    void Position(TVector3& pos)       const;



    /** Modifiers **/
    void SetDx(Double_t dx) { fDx = dx; }
    void SetDy(Double_t dy) { fDy = dy; }
    void SetDz(Double_t dz) { fDz = dz; }
    void SetDxyz(Double_t dx, Double_t dy, Double_t dz);
    void SetPositionError(const TVector3& dpos);
    void SetRefIndex(Int_t index)   { fRefIndex = index; }
    void SetDetectorID(Int_t detID) { fDetectorID = detID; }
    void SetX(Double_t x) { fX = x; }
    void SetY(Double_t y) { fY = y; }
    void SetZ(Double_t z) { fZ = z; }
    void SetXYZ(Double_t x, Double_t y, Double_t z);
    void SetPosition(const TVector3& pos);


    /*** Output to screen */
    virtual void Print(const Option_t*) const {;}

    template<class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        ar& boost::serialization::base_object<FairTimeStamp>(*this);
        ar& fDetectorID;
        ar& fRefIndex;
        ar& fX;
        ar& fY;
        ar& fZ;
        ar& fDx;
        ar& fDy;
        ar& fDz;
    }

  protected:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    Double32_t fDx, fDy, fDz;   ///< Errors of position [cm]
    Int_t      fRefIndex;       ///< Index of FairMCPoint for this hit
    Int_t      fDetectorID;     ///< Detector unique identifier
    Double32_t fX, fY, fZ;      ///< Position of hit [cm]

    ClassDef(FairHit,3);
};


inline void FairHit::PositionError(TVector3& dpos) const
{
  dpos.SetXYZ(fDx, fDy, fDz);
}


inline void FairHit::SetDxyz(Double_t dx, Double_t dy, Double_t dz)
{
  fDx = dx;
  fDy = dy;
  fDz = dz;
}


inline void FairHit::SetPositionError(const TVector3& dpos)
{
  fDx = dpos.X();
  fDy = dpos.Y();
  fDz = dpos.Z();
}

inline void FairHit::Position(TVector3& pos) const
{
  pos.SetXYZ(fX, fY, fZ);
}


inline void FairHit::SetXYZ(Double_t x, Double_t y, Double_t z)
{
  fX = x;
  fY = y;
  fZ = z;
}


inline void FairHit::SetPosition(const TVector3& pos)
{
  fX = pos.X();
  fY = pos.Y();
  fZ = pos.Z();
}

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * FairLink.h
 *
 *  Created on: Dec 23, 2009
 *      Author: stockman
 */

#ifndef FAIRLINK_H_
#define FAIRLINK_H_

#include "TObject.h"                    // for TObject

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Float_t, etc
#include "TString.h"                    // for TString

#include <iostream>                     // for ostream, cout

class FairLink : public TObject
{
  public:
    FairLink();
    FairLink(Int_t type, Int_t index, Float_t weight = 1.);
    FairLink(TString branchName, Int_t index, Float_t weight = 1.);
    FairLink(Int_t file, Int_t entry, Int_t type, Int_t index, Float_t weight = 1.);
    FairLink(Int_t file, Int_t entry, TString branchName, Int_t index, Float_t weight = 1.);
    virtual ~FairLink();

    void SetLink(Int_t file, Int_t entry, Int_t type, Int_t index, Float_t weight = 1.) {
      fFile = file;
      fEntry = entry;
      fType = type;
      fIndex = index;
      fWeight = weight;
    };
    void SetLink(Int_t type, Int_t index, Float_t weight = 1.) {
      fFile = -1;
      fEntry = -1;
      fType = type;
      fIndex = index;
      fWeight = weight;
    };
    Int_t GetFile() const {return fFile;}
    Int_t GetEntry() const {return fEntry;}
    Int_t GetType() const {return fType;}
    Int_t GetIndex() const {return fIndex;}
    Float_t GetWeight() const {return fWeight;}

    void SetWeight(Float_t weight) {fWeight = weight;}
    void AddWeight(Float_t weight) {fWeight += weight;}

    virtual void PrintLinkInfo(std::ostream& out = std::cout) const;

    virtual bool operator==(const FairLink& link) const {
      if ((fFile == link.GetFile() || link.GetFile() == -1) && (fEntry == link.GetEntry() || link.GetEntry() == -1) && fType == link.GetType() && fIndex == link.GetIndex()) {
        return true;
      } else {
        return false;
      }
    }

    virtual bool operator<(const FairLink& link) const {
	if (fFile != -1 && link.GetFile() != -1){
		if (fFile < link.GetFile()) 		return true;
		else if (link.GetFile() < fFile) 	return false;
	}
	if (fEntry != -1 && link.GetEntry() != -1){
		if(fEntry < link.GetEntry())		return true;
		else if (link.GetEntry() < fEntry)	return false;
	}
	if (fType < link.GetType())				return true;
	else if (link.GetType() < fType)		return false;
	if (fIndex < link.GetIndex())			return true;
	else if (link.GetIndex() < fIndex)		return false;

	return false;
//      if (fFile != -1 && fFile < link.GetFile()) {
//        return true;
//      } else if ((fFile == link.GetFile() || link.GetFile() == -1) && fEntry < link.GetEntry()) {
//        return true;
//      } else if ((fFile == link.GetFile() || link.GetFile() == -1)  && (fEntry == link.GetEntry() || link.GetEntry() == -1) && fType < link.GetType()) {
//        return true;
//      } else if ((fFile == link.GetFile() || link.GetFile() == -1)  && (fEntry == link.GetEntry() || link.GetEntry() == -1) && fType == link.GetType() && fIndex < link.GetIndex()) {
//        return true;
//      } else {
//        return false;
//      }
    }

    friend std::ostream& operator<< (std::ostream& out, const FairLink& link) {
      link.PrintLinkInfo(out);
      return out;
    }

    ClassDef(FairLink, 3);


  private:
    Int_t fFile;
    Int_t fEntry;
    Int_t fType;
    Int_t fIndex;
    Float_t fWeight;

};

#endif /* FAIRLINK_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/** FairMCEventHeader.h
 *@author V.Friese <v.friese@gsi.de>
 ** Data class (level MC) containing information about the input event.
 ** 15.05.2008 change the event time to ns (M. Al-Turany)
 **/


#ifndef FAIRMCEVENTHEADER_H
#define FAIRMCEVENTHEADER_H 1

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Double_t, UInt_t, etc
#include "TVector3.h"                   // for TVector3

class FairMCEventHeader : public TNamed
{

  public:

    /** Default constructor **/
    FairMCEventHeader();


    /** Constructor with all members
     **
     *@param iEvent   event identifier
     *@param x,y,z    vertex oordinates [cm]
     *@param t        event time [ns]
     *@param b        impact parameter [fm] (if relevant)
     *@param nPrim    number of input tracks
     **/
    FairMCEventHeader(Int_t iEvent, Double_t x, Double_t y, Double_t z,
                      Double_t t, Double_t b, Int_t nPrim);


    /** Standard constructor with run identifier **/
    FairMCEventHeader(UInt_t runId);


    /** Destructor **/
    virtual ~FairMCEventHeader();


    /** Accessors **/
    UInt_t GetRunID()   const { return fRunId; }     /// run identifier
    UInt_t GetEventID() const { return fEventId; }   /// event identifier
    Double_t GetX()     const { return fX; }         /// vertex x [cm]
    Double_t GetY()     const { return fY; }         /// vertex y [cm]
    Double_t GetZ()     const { return fZ; }         /// vertex z [cm]
    Double_t GetT()     const { return fT; }         /// event time [ns]
    Double_t GetB()     const { return fB; }         /// impact parameter [fm]
    Int_t GetNPrim()    const { return fNPrim; }     /// number of input tracks
    Bool_t IsSet()      const { return fIsSet; }     /// Flag
    Double_t GetRotX()     const { return fRotX; } /// rot. around x-axis [rad]
    Double_t GetRotY()     const { return fRotY; } /// rot. around y-axis [rad]
    Double_t GetRotZ()     const { return fRotZ; } /// rot. around z-axis [rad]

    void GetVertex(TVector3& vertex) { vertex.SetXYZ(fX, fY, fZ); }


    /** Modifiers **/
    void SetEventID(UInt_t eventId) { fEventId = eventId; }
    void SetRunID(UInt_t runId) { fRunId = runId; }
    void SetTime(Double_t t)       { fT = t; }
    void SetB(Double_t b)          { fB = b; }
    void SetNPrim(Int_t nPrim)     { fNPrim = nPrim; }
    void MarkSet(Bool_t isSet)     { fIsSet = isSet; }
    void SetVertex(Double_t x, Double_t y, Double_t z);
    void SetVertex(const TVector3& vertex);
    void SetRotX(Double_t rotx) { fRotX = rotx; }
    void SetRotY(Double_t roty) { fRotY = roty; }
    void SetRotZ(Double_t rotz) { fRotZ = rotz; }

    /** Reset all members **/
    void Reset();

    /** Register the class as data branch to the output */
    virtual void Register();

  protected:


    UInt_t     fRunId;       ///  Run identifier
    UInt_t     fEventId;     ///  Event identifier
    Double32_t fX;           ///  Primary vertex x [cm]
    Double32_t fY;           ///  Primary vertex y [cm]
    Double32_t fZ;           ///  Primary vertex z [cm]
    Double32_t fT;           ///  Event time [s]
    Double32_t fB;           ///  Impact parameter [fm] (if relevant)
    Int_t      fNPrim;       ///  Number of input tracks
    Bool_t     fIsSet;       ///  Flag whether variables are filled
    Double32_t fRotX;        ///  Rotation around x-axis (beam tilt) [rad]
    Double32_t fRotY;        ///  Rotation around y-axis (beam tilt) [rad]
    Double32_t fRotZ;        ///  Rotation around z-axis (event plane) [rad]


    ClassDef(FairMCEventHeader,2);

};


inline void FairMCEventHeader::SetVertex(Double_t x, Double_t y,
    Double_t z)
{
  fX = x;
  fY = y;
  fZ = z;
}


inline void FairMCEventHeader::SetVertex(const TVector3& vertex)
{
  fX = vertex.X();
  fY = vertex.Y();
  fZ = vertex.Z();
}


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**  FairMCPoint.h
 * This is the base class for all MC Points generated by the transport of
 * tracks through active detectors.
 **/



#ifndef FAIRMCPOINT_H
#define FAIRMCPOINT_H

#include "FairMultiLinkedData_Interface.h"        // for FairMultiLinkedData

#include "Rtypes.h"                     // for Double_t, Double32_t, Int_t, etc
#include "TVector3.h"                   // for TVector3


#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class FairMCPoint : public FairMultiLinkedData_Interface
{

  public:

    /** Default constructor **/
    FairMCPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Point coordinates [cm]
     *@param mom      Momentum of track at MCPoint [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     *@param EventId  MC event id
     **/
    FairMCPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                Double_t tof, Double_t length, Double_t eLoss, UInt_t EventId=0);
    
    /** Destructor **/
    virtual ~FairMCPoint();


    /** Accessors */
    UInt_t   GetEventID()    const { return fEventId; }        /// event identifier
    Int_t    GetTrackID()    const { return fTrackID; }
    Double_t GetPx()         const { return fPx; }
    Double_t GetPy()         const { return fPy; }
    Double_t GetPz()         const { return fPz; }
    Double_t GetTime()       const { return fTime; }
    Double_t GetLength()     const { return fLength; }
    Double_t GetEnergyLoss() const { return fELoss; }
    void Momentum(TVector3& mom) const { mom.SetXYZ(fPx, fPy, fPz); }
    Int_t    GetDetectorID()   const { return fDetectorID;             };
    Double_t GetX()             const { return fX;                      };
    Double_t GetY()             const { return fY;                      };
    Double_t GetZ()             const { return fZ;                      };
    void Position(TVector3& pos) const { pos.SetXYZ(fX, fY, fZ); }




    /** Modifiers **/
    void SetEventID(UInt_t eventId) { fEventId = eventId; }
    virtual void SetTrackID(Int_t id) { fTrackID = id;}
    void SetTime(Double_t time)        { fTime = time; }
    void SetLength(Double_t length)    { fLength = length; }
    void SetEnergyLoss(Double_t eLoss) { fELoss = eLoss; }
    void SetMomentum(const TVector3& mom);
    void SetDetectorID(Int_t detID) { fDetectorID = detID; }
    void SetX(Double_t x) { fX = x; }
    void SetY(Double_t y) { fY = y; }
    void SetZ(Double_t z) { fZ = z; }
    void SetXYZ(Double_t x, Double_t y, Double_t z);
    void SetPosition(const TVector3& pos);


    /** Output to screen **/
    virtual void Print(const Option_t* opt = 0) const;


    
    template<class Archive>
    void serialize(Archive & ar, const unsigned int) 
    {
        //ar & boost::serialization::base_object<FairMultiLinkedData>(*this);
        ar & fTrackID;
        ar & fEventId;
        ar & fDetectorID; 
        ar & fX;
        ar & fY;
        ar & fZ;
        ar & fPx;
        ar & fPy;
        ar & fPz; 
        ar & fTime; 
        ar & fLength; 
        ar & fELoss; 
    }

  protected:

    #ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;

    #endif // for BOOST serialization
    
    Int_t fTrackID;               ///< Track index
    UInt_t fEventId;              ///< MC Event id
    Double32_t fPx, fPy, fPz;     ///< Momentum components [GeV]
    Double32_t fTime;             ///< Time since event start [ns]
    Double32_t fLength;           ///< Track length since creation [cm]
    Double32_t fELoss;            ///< Energy loss at this point [GeV]
    Int_t      fDetectorID;       ///< Detector unique identifier
    Double32_t fX, fY, fZ;        ///< Position of hit [cm]


    ClassDef(FairMCPoint,5)

};


inline void FairMCPoint::SetMomentum(const TVector3& mom)
{
  fPx = mom.Px();
  fPy = mom.Py();
  fPz = mom.Pz();
}


inline void FairMCPoint::SetXYZ(Double_t x, Double_t y, Double_t z)
{
  fX = x;
  fY = y;
  fZ = z;
}


inline void FairMCPoint::SetPosition(const TVector3& pos)
{
  fX = pos.X();
  fY = pos.Y();
  fZ = pos.Z();
}



#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                       FairMesh header file                    -----
// -----          original author                  D.Bertini           -----
// -----          adapted april 2010               O.Hartmann          -----
// -------------------------------------------------------------------------

#ifndef FAIRMESH_H
#define FAIRMESH_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Double_t, Int_t, etc
#include "TH2.h"                        // for TH2D
#include "TString.h"                    // for TString

/**
 * Abstract base class for Mesh Objects.
  **@author D.Bertini <d.bertini@gsi.de>
 */
class FairMesh : public TObject
{

  public:

    /** Default constructor **/
    FairMesh();
    FairMesh(const char*);


    /** Destructor **/
    virtual ~FairMesh();


    /** Accessors **/
    Double_t GetXmin()  const { return fXmin;  };
    Double_t GetYmin()  const { return fYmin;  };
    Double_t GetZmin()  const { return fZmin;  };

    Double_t GetXmax()  const { return fXmax;  };
    Double_t GetYmax()  const { return fYmax;  };
    Double_t GetZmax()  const { return fZmax;  };


    /** Modifiers **/
    void SetX(Double_t xmin,Double_t xmax, Int_t nbin ) {
      fXmin = xmin;
      fXmax = xmax;
      NXbin = nbin;
    }
    void SetY(Double_t ymin,Double_t ymax, Int_t nbin ) {
      fYmin = ymin;
      fYmax = ymax;
      NYbin = nbin;
    }
    void SetZ(Double_t zmin,Double_t zmax, Int_t nbin ) {
      fZmin = zmin;
      fZmax = zmax;
      NZbin = nbin;
    }

    TH2D* GetMeshTid() { return fMeshTid; }
    TH2D* GetMeshFlu() { return fMeshFlu; }
    TH2D* GetMeshSEU() { return fMeshSEU; }
    /*** Output to screen */
// virtual void Print(const Option_t* opt = 0) const {;}

    Double_t GetDiag() { return fDiag; }
    Double_t GetBinVolume() { return fBinVolume; }

    void fillTID(Double_t x , Double_t y , Double_t we ) {
      fMeshTid->Fill(x,y,we);
    }
    void fillFluence(Double_t x , Double_t y , Double_t we ) {
      fMeshFlu->Fill(x,y,we);

    }
    void fillSEU(Double_t x , Double_t y , Double_t we ) {
      fMeshSEU->Fill(x,y,we);

    }
    void Scale(Double_t fac ) {
      fMeshTid->Scale(fac);
      fMeshFlu->Scale(fac);
      fMeshSEU->Scale(fac);
    }

    void calculate();


    void print();
  protected:

    Double_t  fXmin, fYmin, fZmin;
    Double_t  fXmax, fYmax, fZmax;
    Int_t     NXbin, NYbin, NZbin;
    Double_t fBinVolume;
    Double_t fDiag;
    TH2D* fMeshTid; // !mesh
    TH2D* fMeshFlu; // !mesh
    TH2D* fMeshSEU; // !mesh
    TString fhname; // !mesh

  private:
    FairMesh(const FairMesh&);
    FairMesh& operator=(const FairMesh&);

    ClassDef(FairMesh,1);

};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * FairMultiLinkedData.h
 *
 * \date Dec 7, 2009
 * \author T.Stockmanns <t.stockmanns@fz-juelich.de>
 */

#ifndef FAIRMULTILINKEDDATA_H_
#define FAIRMULTILINKEDDATA_H_

#include "TObject.h"                    // for TObject

#include "FairLink.h"                   // for FairLink

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, kFALSE, etc
#include "TString.h"                    // for TString

#include <iostream>                     // for operator<<, ostream, cout
#include <set>                          // for set
#include <vector>                       // for vector

class FairMultiLinkedData : public  TObject
{
  public:
    FairMultiLinkedData();///< Default constructor
    FairMultiLinkedData(std::set<FairLink> links, Bool_t persistanceCheck = kTRUE);///< Constructor
    FairMultiLinkedData(TString dataType, std::vector<Int_t> links, Int_t fileId = -1, Int_t evtId = -1,Bool_t persistanceCheck = kTRUE, Bool_t bypass = kFALSE, Float_t mult = 1.0);///< Constructor
    FairMultiLinkedData(Int_t dataType, std::vector<Int_t> links, Int_t fileId = -1, Int_t evtId = -1, Bool_t persistanceCheck = kTRUE, Bool_t bypass = kFALSE, Float_t mult = 1.0);///< Constructor

    virtual ~FairMultiLinkedData() {};

    virtual std::set<FairLink>    GetLinks() const {    return fLinks;}           ///< returns stored links as FairLinks
    virtual FairLink		GetEntryNr() const { return fEntryNr;}				///< gives back the entryNr
    virtual Int_t           GetNLinks() const { return fLinks.size(); }       ///< returns the number of stored links
    virtual FairLink        GetLink(Int_t pos) const;                 ///< returns the FairLink at the given position
    virtual FairMultiLinkedData   GetLinksWithType(Int_t type) const;             ///< Gives you a list of links which contain the given type
    virtual std::vector<FairLink> GetSortedMCTracks();				///< Gives you a list of all FairLinks pointing to a "MCTrack" sorted by their weight
    TObject*         GetData(FairLink& myLink);                  ///< Get the TObject the Link is pointing to
    virtual Int_t GetDefaultType() { return fDefaultType;}
    Bool_t              GetPersistanceCheck() {return fPersistanceCheck;}     ///< Returns the value of PersistanceCheck
    Int_t             GetVerbose() {return fVerbose;}             ///< Returns the verbosity level
    virtual void SetDefaultType(Int_t type) {  fDefaultType = type;}
    virtual void SetPersistanceCheck(Bool_t check) {fPersistanceCheck = check;}       ///< Controls if a persistance check of a link is done or not
    virtual void SetVerbose(Int_t level) {fVerbose = level;}                ///< Sets the verbosity level
    virtual void SetInsertHistory(Bool_t val){ fInsertHistory = val;}		///< Toggles if history of a link is inserted or not

    virtual void SetEntryNr(FairLink entry){ fEntryNr = entry;}
    virtual void SetLinks(FairMultiLinkedData links, Float_t mult = 1.0);           ///< Sets the links as vector of FairLink
    virtual void SetLink(FairLink link, Bool_t bypass = kFALSE, Float_t mult = 1.0);      ///< Sets the Links with a single FairLink

    virtual void AddLinks(FairMultiLinkedData links, Float_t mult = 1.0);           ///< Adds a List of FairLinks (FairMultiLinkedData) to fLinks
    virtual void AddLink(FairLink link, Bool_t bypass = kFALSE, Float_t mult = 1.0);      ///< Adds a FairLink link at the end of fLinks. If multi is kTRUE a link is allowed more than once otherwise it is stored only once

    virtual void InsertLink(FairLink link);                         ///< Inserts a link into the list of links without persistance checking
    virtual void InsertHistory(FairLink link);                      ///< Adds the FairLinks of the inserted link to the set of links of this object


    virtual void AddAllWeights(Double_t weight);                        ///< Adds weight to all Links
    virtual void SetAllWeights(Double_t weight);                        ///< Sets a common weight for Links
    virtual void MultiplyAllWeights(Double_t weight);                   ///<Multiplies all Links with weight


    virtual Bool_t IsLinkInList(FairLink link)    {return IsLinkInList(link.GetType(), link.GetIndex());}   ///< Test if a given link is in fLinks
    virtual Bool_t IsLinkInList(Int_t type, Int_t index);                             ///< Same as IsLinkInList(FairLink) just with type and index given separately
    virtual Int_t LinkPosInList(FairLink link)  {return LinkPosInList(link.GetType(), link.GetIndex());}    ///< returns position of link in fLinks. If it is not in the list -1 is returned
    virtual Int_t LinkPosInList(Int_t type, Int_t index);                             ///< Same as LinkPosInList(FairLink)

    virtual void DeleteLink(FairLink link)    {DeleteLink(link.GetType(), link.GetIndex());}          ///< Deletes a link ouf of fLinks
    virtual void DeleteLink(Int_t type, Int_t index);                               ///< Deletes a link ouf of fLinks

    virtual void Reset() {ResetLinks();}
    virtual void ResetLinks() {fLinks.clear();}                                    ///< Clears fLinks


    std::ostream& PrintLinkInfo(std::ostream& out = std::cout) const
    {
      out << GetEntryNr() << " -> [";
      for (Int_t i = 0; i < GetNLinks(); i++) {
        GetLink(i).PrintLinkInfo(out);
        out << " ";
      }
      out << "]";
      return out;
    }                                                     ///< Output

    friend std::ostream& operator<< (std::ostream& out, const FairMultiLinkedData& data) {
      data.PrintLinkInfo(out);
      return out;
    }                                                     ///< Output

  protected:
    std::set<FairLink> fLinks;
    FairLink fEntryNr;
    Bool_t fPersistanceCheck; //!
    Bool_t fInsertHistory; //!
    Int_t fVerbose; //!

    virtual void SimpleAddLinks(Int_t fileId, Int_t evtId, Int_t dataType, std::vector<Int_t> links, Bool_t, Float_t) {
      for (UInt_t i = 0; i < links.size(); i++) {
        fLinks.insert(FairLink(fileId, evtId, dataType, links[i]));
      }
    }
    Int_t fDefaultType;


    ClassDef(FairMultiLinkedData, 4);
};

/**\fn virtual void FairMultiLinkedData::SetLinks(Int_t type, std::vector<Int_t> links)
 * \param type as Int_t gives one type of source data for all indices
 * \param links as vector<Int_t> gives the vector of indices at which position in the TClonesArray the source data is stored
 */

/**\fn virtual void FairMultiLinkedData::SetLinks(std::vector<Int_t> type, std::vector<Int_t> links)
 * \param type as vector<Int_t> gives the type of source data (TClonesArray)
 * \param links as vector<Int_t> gives the vector of indices at which position in the TClonesArray the source data is stored
 */


#endif /* FAIRMULTILinkedData_H_ */
/**
 * FairMultiLinkedData_Interface.h
 *
 * \date Dec 7, 2009
 * \author T.Stockmanns <t.stockmanns@fz-juelich.de>
 */

#ifndef FairMultiLinkedData_Interface_H_
#define FairMultiLinkedData_Interface_H_

#include "TObject.h"                    // for TObject

#include "FairLink.h"                   // for FairLink
#include "FairMultiLinkedData.h"
#include "FairRootManager.h"

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Int_t, Bool_t, kFALSE, etc
#include "TString.h"                    // for TString
#include "TRef.h"

#include <iostream>                     // for operator<<, ostream, cout
#include <set>                          // for set
#include <vector>                       // for vector


class FairMultiLinkedData_Interface : public  TObject
{
  public:
    FairMultiLinkedData_Interface();///< Default constructor
    FairMultiLinkedData_Interface(FairMultiLinkedData& links, Bool_t persistanceCheck = kTRUE);///< Constructor
    FairMultiLinkedData_Interface(TString dataType, std::vector<Int_t> links, Int_t fileId = -1, Int_t evtId = -1,Bool_t persistanceCheck = kTRUE, Bool_t bypass = kFALSE, Float_t mult = 1.0);///< Constructor
    FairMultiLinkedData_Interface(Int_t dataType, std::vector<Int_t> links, Int_t fileId = -1, Int_t evtId = -1, Bool_t persistanceCheck = kTRUE, Bool_t bypass = kFALSE, Float_t mult = 1.0);///< Constructor
    FairMultiLinkedData_Interface(const FairMultiLinkedData_Interface& toCopy);

    virtual ~FairMultiLinkedData_Interface() {
    	delete(fLink);
    };

    FairMultiLinkedData_Interface& operator=(const FairMultiLinkedData_Interface& rhs);

    virtual std::set<FairLink>  GetLinks() const;           		///< returns stored links as FairLinks
    virtual Int_t           	GetNLinks() const;                	///< returns the number of stored links
    virtual FairLink        	GetLink(Int_t pos) const;         	///< returns the FairLink at the given position
    virtual FairMultiLinkedData GetLinksWithType(Int_t type) const; ///< returns all FairLinks with the corresponding type
    virtual FairLink            GetEntryNr() const;
    virtual FairMultiLinkedData* 		GetPointerToLinks() const {	return fLink;}

    virtual std::vector<FairLink> GetSortedMCTracks();

    virtual void SetLinks(FairMultiLinkedData links);           ///< Sets the links as vector of FairLink
    virtual void SetLink(FairLink link);      					///< Sets the Links with a single FairLink
    virtual void SetInsertHistory(Bool_t val);
    virtual void SetEntryNr(FairLink val);
    virtual void SetPointerToLinks(FairMultiLinkedData* links) {fLink = links;}

    virtual void AddLinks(FairMultiLinkedData links, Float_t mult = 1.0);		///< Adds a List of FairLinks (FairMultiLinkedData_Interface) to fLinks
    virtual void AddLink(FairLink link);      									///< Adds a FairLink link at the end of fLinks. If multi is kTRUE a link is allowed more than once otherwise
    virtual void AddInterfaceData(FairMultiLinkedData_Interface* data);



    virtual void ResetLinks();


    std::ostream& PrintLinkInfo(std::ostream& out = std::cout) const {

		if (GetPointerToLinks() != 0)
			GetPointerToLinks()->PrintLinkInfo(out);
		return out;
    }                                                     ///< Output

    friend std::ostream& operator<< (std::ostream& out, FairMultiLinkedData_Interface& data) {
      data.PrintLinkInfo(out);
      return out;
    }                                                     ///< Output

  protected:

    Int_t fVerbose; //!
    Bool_t fInsertHistory; //!
    FairMultiLinkedData* fLink;

    FairMultiLinkedData* CreateFairMultiLinkedData();

    ClassDef(FairMultiLinkedData_Interface, 5);
};

/**\fn virtual void FairMultiLinkedData_Interface::SetLinks(Int_t type, std::vector<Int_t> links)
 * \param type as Int_t gives one type of source data for all indices
 * \param links as vector<Int_t> gives the vector of indices at which position in the TClonesArray the source data is stored
 */

/**\fn virtual void FairMultiLinkedData_Interface::SetLinks(std::vector<Int_t> type, std::vector<Int_t> links)
 * \param type as vector<Int_t> gives the type of source data (TClonesArray)
 * \param links as vector<Int_t> gives the vector of indices at which position in the TClonesArray the source data is stored
 */


#endif /* FairMultiLinkedData_Interface_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -------------------------------------------------------------------------
// -----                      FairRadLenPoint header file               -----
// -----                  Created 14/01/08  by M. Al-Turany            -----
// -------------------------------------------------------------------------


/**  FairRadLenPoint.h
 *@author M. Al-Turany
 *
 */

#ifndef FAIRRADLENPOINT_H
#define FAIRRADLENPOINT_H

#include "FairMCPoint.h"                // for FairMCPoint

#include "Rtypes.h"                     // for Double_t, Float_t, etc
#include "TVector3.h"                   // for TVector3

class FairRadLenPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairRadLenPoint();

    FairRadLenPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                    Double_t tof, Double_t length, Double_t eLoss, TVector3 posOut, TVector3 momOut,
                    Float_t  fA, Float_t fZ,  Float_t  fDensity, Float_t  fRadLen);


    /** Destructor **/
    virtual ~FairRadLenPoint();


    /** Accessors **/
    Float_t GetA()              { return fA; }
    Float_t GetZm()              { return fZmat; }
    Float_t GetRadLength()      { return fRadLen;}
    Float_t GetDensity()        { return fDensity ; }


    /** Modifiers **/
    void SetA(Double_t A)              { fA = A; }
    void SetZm(Double_t Z)              { fZmat = Z; }
    void SetRadLength(Double_t length) { fRadLen = length;}
    void SetDensity (Double_t Density) { fDensity = Density; }

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

    Double_t GetXOut() const { return fXOut;};
    Double_t GetYOut() const { return fYOut;};
    Double_t GetZOut() const { return fZOut;};

    Double_t GetPxOut() const { return fPxOut; }
    Double_t GetPyOut() const { return fPyOut; }
    Double_t GetPzOut() const { return fPzOut; }

    TVector3 GetPosition() const { return TVector3(fX, fY, fZ);}
    TVector3 GetPositionOut() const { return TVector3(fXOut, fYOut, fZOut);}

    void PositionOut(TVector3& pos) const { pos.SetXYZ(fXOut, fYOut, fZOut);};
    void MomentumOut(TVector3& mom) const { mom.SetXYZ(fPxOut,fPyOut,fPzOut); }


  protected:

    Float_t        fA;          // A of material
    Float_t        fZmat;       // Z of material
    Float_t        fDensity;    // density of material
    Float_t        fRadLen;     // radiation length

    Double_t fXOut, fYOut, fZOut;
    Double_t fPxOut, fPyOut, fPzOut;


    ClassDef(FairRadLenPoint,1)

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
// -----                     FairRadMapPoint header file               -----
// -------------------------------------------------------------------------


/**  FairRadMapPoint.h
 *@author O.N. Hartmann
 *
 */

#ifndef FAIRRADMAPPOINT_H
#define FAIRRADMAPPOINT_H

#include "FairMCPoint.h"                // for FairMCPoint

#include "Rtypes.h"                     // for Double_t, Float_t, Int_t, etc
#include "TVector3.h"                   // for TVector3

class FairRadMapPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairRadMapPoint();

    FairRadMapPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                    Double_t tof, Double_t length, Double_t eLoss,
                    TVector3 posOut, TVector3 momOut,
                    Float_t  fA, Float_t fZ,  Float_t  fDensity, Double_t fVolMass,
                    Double_t fStep, Double_t fDose, Double_t fDoseSL, Int_t fPdg );


    /** Destructor **/
    virtual ~FairRadMapPoint();


    /** Accessors **/
    Float_t GetA()              { return fA; }
    Float_t GetZm()             { return fZmat; }
    Float_t GetMass()           { return fVolMass;}
    Float_t GetDensity()        { return fDensity ; }

    /** Modifiers **/
    void SetA(Double_t A)              { fA = A; }
    void SetZm(Double_t Z)             { fZmat = Z; }
    void SetMass(Double_t vmass)       { fVolMass = vmass;}
    void SetDensity (Double_t Density) { fDensity = Density; }

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

    Int_t GetPdg() const { return fPdg;};

    Double_t GetXOut() const { return fXOut;};
    Double_t GetYOut() const { return fYOut;};
    Double_t GetZOut() const { return fZOut;};

    Double_t GetPxOut() const { return fPxOut; }
    Double_t GetPyOut() const { return fPyOut; }
    Double_t GetPzOut() const { return fPzOut; }

    Double_t GetDose() const { return fDose;}
    Double_t GetDoseSL() const { return fDoseSL;}

    TVector3 GetPosition() const { return TVector3(fX, fY, fZ);}
    TVector3 GetPositionOut() const { return TVector3(fXOut, fYOut, fZOut);}

    void PositionOut(TVector3& pos) const { pos.SetXYZ(fXOut, fYOut, fZOut);};
    void MomentumOut(TVector3& mom) const { mom.SetXYZ(fPxOut,fPyOut,fPzOut); }



  protected:

    //  Int_t          detID;       // detector ID or volume ID
    Int_t          fPdg;        // track PID
    Float_t        fA;          // A of material
    Float_t        fZmat;       // Z of material
    Float_t        fDensity;    // density of material
    Double_t       fVolMass;     // radiation length

    Double_t fStep, fDose, fDoseSL;
    Double_t fXOut, fYOut, fZOut;
    Double_t fPxOut, fPyOut, fPzOut;


    ClassDef(FairRadMapPoint,3)

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
// -----          FairRecoEventHeader header file                      -----
// -----          Created 20/09/13                 R.Karabowicz        -----
// -------------------------------------------------------------------------

#ifndef FAIRRECOEVENTHEADER_H
#define FAIRRECOEVENTHEADER_H


#include "TNamed.h"

/**
 *  Event Header Class
  **@author D.Bertini <d.bertini@gsi.de>
  **@author M.Al-Turany <m.al-turany@gsi.de>
  **@author R.Karabowicz <r.karabowicz@gsi.de>
 */
class FairRecoEventHeader : public TNamed
{

  public:

    /** Default constructor */
    FairRecoEventHeader();

    /** Get the run ID for this run*/
    UInt_t GetRunId() const {
      return fRunId;
    }

    /** Get the MC time for this event*/
    Double_t GetEventTime() const {
      return fEventTime;
    }

    /** Get the error of MC time for this event*/
    Double_t GetEventTimeError() const {
      return fEventTimeError;
    }

    /** Get identifier*/
    Int_t GetIdentifier() const {
      return fIdentifier;
    }

    /** Set the run ID for this run
    * @param runid : unique run id
    */
    void SetRunId(UInt_t runid) {
      fRunId=runid;
    }

    /** Set the MC time for this event
     * @param time : time in ns
     * @param terr : time error in ns
     */
    void SetEventTime(Double_t time, Double_t terr) {
      fEventTime=time;
      fEventTimeError=terr;
    }

    /** Set the run ID for this run
    * @param ident : identifier
    */
    void SetIdentifier(Int_t ident) {
      fIdentifier=ident;
    }

    virtual bool operator<(const FairRecoEventHeader& tempObj) const {
      if (fEventTime < tempObj.GetEventTime()) { return true; }
      else if (fEventTime > tempObj.GetEventTime()) { return false; }
      return false;
    }

    virtual bool operator>(const FairRecoEventHeader& tempObj) const {
      if (fEventTime > tempObj.GetEventTime()) { return true; }
      else if (fEventTime < tempObj.GetEventTime()) { return false; }
      return false;
    }

    virtual bool operator==(const FairRecoEventHeader& tempObj) const {
      if   (fEventTime == tempObj.GetEventTime() ) {
        return true;
      }
      return false;
    }

    /**
     * Destructor
     */
    virtual ~FairRecoEventHeader();

  protected:

    /** Run Id */
    UInt_t fRunId;
    /** Identifier */
    Int_t     fIdentifier;
    /** Event Time **/
    Double_t  fEventTime;
    /** Event Time Error **/
    Double_t  fEventTimeError;

    ClassDef(FairRecoEventHeader,1)

};
#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRRUNINFO_H
#define FAIRRUNINFO_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Double_t, Long_t, etc
#include "TSystem.h"                    // for CpuInfo_t, MemInfo_t, etc
#include "TTimeStamp.h"                 // for TTimeStamp

#include <vector>                       // for vector

class FairLogger;
class TList;

class FairRunInfo : public TObject
{

  public:

    FairRunInfo();

    ~FairRunInfo();

    void StoreInfo();

    void WriteInfo();

    void Reset();

  private:

    TTimeStamp  fTimeStamp;//!
    CpuInfo_t   fCpuInfo;//!
    MemInfo_t   fMemInfo;//!
    ProcInfo_t  fProcInfo;//!
    std::vector<Double_t> fTimeDiff;//!
    std::vector<Double_t> fTime;//!
    std::vector<Long_t> fResidentMemory;//!
    std::vector<Long_t> fVirtualMemory;//!
    FairLogger* fLogger;

    void CalculateTimeDifference();

    void PrintInfo();

    void GetInfo();

    void CreateAndFillHistograms(TList* histoList);

    void WriteHistosToFile(TList* histoList);

    FairRunInfo(const FairRunInfo&);
    FairRunInfo& operator=(const FairRunInfo&);

    ClassDef(FairRunInfo,1)

};
#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTIMESTAMP_H
#define FAIRTIMESTAMP_H

#include "FairMultiLinkedData_Interface.h"        // for FairMultiLinkedData

#include "FairLink.h"                   // for FairLink

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Double_t, etc

#include <iostream>                     // for ostream, cout

#ifndef __CINT__ // for BOOST serialization
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class TObject;

/**
 * Base class for Time stamp information
 ** Aug. 2010
 **@author M.Al-Turany <m.al-turany@gsi.de>
 */
class FairTimeStamp : public FairMultiLinkedData_Interface
{
  public:
    /** Default constructor **/
    FairTimeStamp();
    /** Constructor with time **/
    FairTimeStamp(Double_t time);
    /** Constructor with time and time error **/
    FairTimeStamp(Double_t time, Double_t timeerror);

    /** Destructor **/
    virtual ~FairTimeStamp();
    /** Accessors **/
    virtual Double_t GetTimeStamp()             const { return fTimeStamp; };
    virtual Double_t GetTimeStampError()     const { return fTimeStampError;};
    virtual FairLink GetEntryNr() const {return fEntryNr;}
    /** Modifiers **/
    virtual void SetTimeStamp(Double_t t) { fTimeStamp = t; }
    virtual void SetTimeStampError(Double_t t) {fTimeStampError = t;}
    virtual void SetEntryNr(FairLink entry) {fEntryNr = entry;}
    virtual Int_t Compare(const TObject* obj) const {
      if (this == obj) { return 0; }
      FairTimeStamp* tsobj = static_cast<FairTimeStamp*>(const_cast<TObject*>(obj));
      Double_t ts = tsobj->GetTimeStamp();
      Double_t tserror = tsobj->GetTimeStampError();
      if (fTimeStamp < ts) { return -1; }
      else if (fTimeStamp == ts && fTimeStampError < tserror) { return -1; }
      else if (fTimeStamp == ts && fTimeStampError == tserror) { return 0; }
      else { return 1; }
    }


    virtual std::ostream& PrintTimeInfo(std::ostream& out = std::cout) const;
    virtual Bool_t IsSortable() const { return kTRUE;};


    virtual bool equal(FairTimeStamp* data) {
      return (fTimeStamp == data->GetTimeStamp() && fTimeStampError == data->GetTimeStampError());
    }

    friend std::ostream& operator<< (std::ostream& out, const FairTimeStamp& link) {
      link.PrintTimeInfo(out);
      return out;
    }

    virtual bool operator< (const FairTimeStamp* rValue) const {
    	if (GetTimeStamp() < rValue->GetTimeStamp())
    		return true;
    	else
    		return false;
    }

    template<class Archive>
    void serialize(Archive& ar, const unsigned int)
    {
        // ar & boost::serialization::base_object<FairMultiLinkedData>(*this);
        ar& fTimeStamp;
        ar& fTimeStampError;
    }

  protected:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    Double_t fTimeStamp;        /** Time of digit or Hit  [ns] */
    Double_t fTimeStampError;     /** Error on time stamp */
    FairLink fEntryNr; //!  indicates where the data is stored in the branch

    ClassDef(FairTimeStamp,3);
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
// -----                     FairTrackParam header file                 -----
// -----                  Created 27/01/05  by V. Friese               -----
// -------------------------------------------------------------------------


/**  FairTrackParam.h
 *@author V.Friese <v.friese@gsi.de>
 **
 ** Parameters (x, y, tx, ty, q/p) of a track
 ** resulting from the track fit. The z coordinate is not a parameter.
 ** The 5x5 covariance matrix can be set and accessed by either an array
 ** of size 15, the TMatrixFSym class or elementwise. Note that TMatrixFSym
 ** should not be used when performance is an issue.
 ** The internal representation of the covariance matrix elements is
 ** an array of double.
 **/


#ifndef FAIRSTSTRACKPARAM
#define FAIRSTSTRACKPARAM 1

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Double_t, Double32_t, Int_t, etc
#include "TMatrixFSymfwd.h"             // for TMatrixFSym
#include "TVector3.h"                   // for TVector3

class FairTrackParam : public TObject
{

  public:

    /** Constructor **/
    FairTrackParam();


    /** Constructor with all variables **/
    FairTrackParam(Double_t x,  Double_t y,  Double_t z,
                   Double_t tx, Double_t ty, Double_t qp,
                   const TMatrixFSym& covMat);


    /** Copy constructor **/
    FairTrackParam(const FairTrackParam& param);


    /** Destructor **/
    virtual ~FairTrackParam();


    /** Output to screen **/
    void  Print(Option_t* option = "") const;

    /** Accessors **/
    Double_t GetX()  const { return fX; };
    Double_t GetY()  const { return fY; };
    Double_t GetZ()  const { return fZ; };
    Double_t GetTx() const { return fTx; };
    Double_t GetTy() const { return fTy; };
    Double_t GetQp() const { return fQp; };
    void Position(TVector3& pos) const { pos.SetXYZ(fX, fY, fZ); };
    void Momentum(TVector3& mom) const;
    void CovMatrix(Double_t cov[]) const;
    void CovMatrix(TMatrixFSym& covMat) const;
    Double_t GetCovariance(Int_t i, Int_t j) const;


    /** Modifiers **/
    void SetX(Double_t x)   { fX  = x;  };
    void SetY(Double_t y)   { fY  = y;  };
    void SetZ(Double_t z)   { fZ  = z;  };
    void SetTx(Double_t tx) { fTx = tx; };
    void SetTy(Double_t ty) { fTy = ty; };
    void SetQp(Double_t qp) { fQp = qp; };
    void SetPosition(const TVector3& pos);
    void SetCovMatrix(Double_t cov[]);
    void SetCovMatrix(const TMatrixFSym& covMat);
    void SetCovariance(Int_t i, Int_t j, Double_t val);


    /** Assignment operator  **/
    FairTrackParam& operator=(const FairTrackParam& par );



  private:

    /** Position of track at given z [cm] **/
    Double32_t fX, fY, fZ;

    /** Direction of track tx = dx/dz; ty = dy/dz **/
    Double32_t fTx, fTy;

    /** Charge over momentum [1/GeV] **/
    Double32_t fQp;

    /** Covariance matrix for the variables x, y, tx, ty, q/p
     ** The 15 elements of the upper triangle of the symmetric matrix
     ** are stored in an array of floats. The sequence of the array is
     ** a[0,0..4], a[1,1..4], a[2,2..4], a[3,3..4], a[4,4].
     **/

    Double32_t fCovMatrix[15];


    ClassDef(FairTrackParam,1);

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
// -----                      FairField header file                     -----
// -----                Created 06/01/04  by M. Al-Turany              -----
// -----                Redesign 13/02/06  by V. Friese                -----
// -----                Redesign 04/08/06  by M. Al-Turany               -----
// -------------------------------------------------------------------------


/** FairField.h
 ** @author M.Al-Turany <m.al/turany@gsi.de>
 ** @author V.Friese <v.friese@gsi.de>
 ** @since 06.01.2004
 ** @version1.0
 **
 ** Abstract base class for magnetic fields in FAIR
 ** Concrete field should implement the pure virtual methods
 ** GetBx, GetBy and GetBz and/or  GetBxyz
 **
 ** Note: Field values should be returned in kG (thanks to GEANT3)
 **/

#ifndef FAIRFIELD_H
#define FAIRFIELD_H 1

#include "RVersion.h"                   // for ROOT_VERSION_CODE
#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Double_t, Bool_t, etc

#if ROOT_VERSION_CODE < 333824

#ifndef ROOT_TVirtualMagField
#define ROOT_TVirtualMagField
// copied from ROOT for backward compatibility with ROOT versions before 5.24
#include "TNamed.h"

class TVirtualMagField : public TNamed
{
  public:
    TVirtualMagField()                 : TNamed() {}
    TVirtualMagField(const char* name) : TNamed(name,"") {}
    virtual ~TVirtualMagField() {}
    virtual void Field(const Double_t* x, Double_t* B) = 0;
    ClassDef(TVirtualMagField, 1)              // Abstract base field class
};
ClassImp(TVirtualMagField)
#endif


#else

#include "TVirtualMagField.h"

#endif

#include <stdio.h>                      // for printf
#include <iostream>                     // for operator<<, basic_ostream, etc

#include "FairLogger.h"


class FairField : public TVirtualMagField
{

  public:

    /** Default constructor **/
    FairField();


    /** Constructor with name and title **/
    FairField(const char* name, const char* title = "FAIR Magnetic Field");

    FairField& operator=(const FairField&) {return *this;}

    /** Destructor **/
    virtual ~FairField();


    /** Intialisation. E.g. read in the field map. If needed, to be
     ** implemented in the concrete class.
     **/
    virtual void Init() { };

    /** Test whether field type is Constant **/
    Bool_t IsConst();


    /** Test whether field typ is Map **/
    Bool_t IsMap();


    /** Field type ( 0=constant, 1=map, 2=map sym2, 3 = map sym3 ) **/
    Int_t GetType() const { return fType; }


    /** Get x component of magnetic field [kG]
     ** @param x,y,z    Position [cm]
     **/
    virtual Double_t GetBx(Double_t, Double_t, Double_t) {LOG(WARNING)<<"FairField::GetBx Should be implemented in User class"<<FairLogger::endl; return 0;}


    /** Get y component of magnetic field [kG]
     ** @param x,y,z    Position [cm]
     **/
    virtual Double_t GetBy(Double_t, Double_t, Double_t) {LOG(WARNING)<<"FairField::GetBy Should be implemented in User class"<<FairLogger::endl; return 0;}

    /** Get z component of magnetic field [kG]
     ** @param x,y,z    Position [cm]
     **/
    virtual Double_t GetBz(Double_t, Double_t, Double_t) {LOG(WARNING)<<"FairField::GetBz Should be implemented in User class"<<FairLogger::endl; return 0;}


    /** Get magnetic field. For use of GEANT3
     ** @param point            Coordinates [cm]
     ** @param bField (return)  Field components [kG]
     **/
    virtual void GetFieldValue(const Double_t point[3], Double_t* bField);


    void Field(const Double_t point[3], Double_t* B) {GetFieldValue(point,B);}


    /** Screen output. To be implemented in the concrete class. **/
    virtual void  Print(Option_t*) const {;}
    virtual void GetBxyz(const Double_t[3], Double_t*) {LOG(WARNING)<<"FairField::GetBxyz Should be implemented in User class"<<FairLogger::endl;}



    /**Fill Paramater*/

    virtual void FillParContainer() {LOG(WARNING)<<"FairField::FillParContainer Should be implemented in User class"<<FairLogger::endl;}
  protected:

    /** Field type. 1 = constant field, 2 = field map. **/
    Int_t fType;

  private:
    FairField(const FairField&);
    //    FairField& operator=(const FairField&);
    //TODO: Check why the htrack needs this
    ClassDef(FairField,4);

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
// -----                    FairFieldFactory header file                  -----
// -----                Created 15/01/07  by M. Al-Turany              -----
// -------------------------------------------------------------------------


#ifndef FAIRFIELDFACTORY_H
#define FAIRFIELDFACTORY_H

#include "Rtypes.h"                     // for FairFieldFactory::Class, etc

class FairField;

class FairFieldFactory
{

  public:
    static FairFieldFactory* Instance();
    FairFieldFactory();
    virtual ~FairFieldFactory();
    virtual FairField* createFairField() {
      FairField* field=0;
      if(fCreator) { field= fCreator->createFairField(); }
      return field;
    };
    virtual void SetParm() {
      if(fCreator) { fCreator->SetParm(); }
    }

  protected:
    FairFieldFactory* fCreator;
    static FairFieldFactory*  fgRinstance;

    ClassDef(FairFieldFactory,1)
  private:
    FairFieldFactory(const FairFieldFactory& M);
    FairFieldFactory& operator= (const  FairFieldFactory&) {return *this;}

};
#endif //FAIRFIELDFACTORY_H







/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
* Runge-Kutte Track propagator
* @author M. Al-Turany
* @version 0.1
* @since 22.1.10
*/

#ifndef RKPropagator
#define RKPropagator

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Double_t, etc

class FairField;

class FairRKPropagator : public TObject
{

  private:
    FairRKPropagator(const FairRKPropagator&);            // Not implemented
    FairRKPropagator& operator=(const FairRKPropagator&); // Not implemented
    Double_t fMaxStep;
    FairField*              fMagField;
  public:
    void Step(Double_t Charge, Double_t* vecRKIn, Double_t* vecOut);
    void OneStepRungeKutta(Double_t charge, Double_t step, Double_t* vect, Double_t* vout);
    FairRKPropagator(FairField* field);
    /**Propagate to closest approach of a point
    @CHARGE    Particle charge
    @STEP      maximum Step size
    @vecRKIn   Initial co-ords,direction cosines,momentum
    @vecOut    Output co-ords,direction cosines,momentum
    */
    void Propagat(Double_t Charge, Double_t* vecRKIn, Double_t* Pos);

    /**Propagate to closest approach of a plane
    @CHARGE    Particle charge
    @vecRKIn   Initial co-ords,direction cosines,momentum
    @vec1      vector on the plane
    @vec2      vector on the plane
    @vec3      point on the plane
    @vecOut    Output co-ords,direction cosines,momentum
    */

    void PropagatToPlane(Double_t Charge, Double_t* vecRKIn, Double_t* vec1, Double_t* vec2, Double_t* vec3, Double_t* vecOut);

    virtual ~FairRKPropagator();
    ClassDef(FairRKPropagator, 1);

};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSource                            -----
// -----                    Created 01.11.2013 by F. Uhlig                 -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef FAIRSOURCE_H
#define FAIRSOURCE_H

#include "TObject.h"

#include <iostream>

class FairEventHeader;

enum Source_Type {kONLINE, kFILE};

class FairSource : public TObject
{
  public:
    FairSource();
    FairSource(const FairSource& source);
    virtual ~FairSource();

    virtual Bool_t Init() = 0;
    virtual Int_t ReadEvent(UInt_t=0) = 0;
    virtual void Close() = 0;

    virtual void Reset() = 0;

    virtual Bool_t   ActivateObject(TObject**, const char*)  { return kFALSE; }

    virtual Source_Type GetSourceType() = 0;

    virtual void SetParUnpackers() = 0;

    virtual Bool_t InitUnpackers() = 0;

    virtual Bool_t ReInitUnpackers() = 0;

    /**Check the maximum event number we can run to*/
    virtual Int_t  CheckMaxEventNo(Int_t=0) {return -1;}
    /**Read the tree entry on one branch**/
    virtual void   ReadBranchEvent(const char*) {return;}
    virtual void   ReadBranchEvent(const char*, Int_t) {return;}
    virtual void FillEventHeader(FairEventHeader* feh);

    void SetRunId(Int_t runId) { fRunId = runId; }
    Int_t GetRunId() const     { return fRunId;  }

  protected:
    Int_t fRunId;

  public:
    ClassDef(FairSource, 2)
};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//
//  FairFileSource.h
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//

#ifndef __FAIRROOT__FairFileSource__
#define __FAIRROOT__FairFileSource__

#include "FairSource.h"
#include <list>    
#include "TChain.h"
#include "TFile.h"
#include "TFolder.h"
#include "TF1.h"
class FairEventHeader;
class FairFileHeader;
class FairMCEventHeader;
class TString;
class FairLogger;
class FairRuntimeDb;

class FairFileSource : public FairSource
{
public:
    FairFileSource(TFile *f, const char* Title="InputRootFile", UInt_t identifier=0);
    FairFileSource(const TString* RootFileName, const char* Title="InputRootFile", UInt_t identifier=0);
    FairFileSource(const TString RootFileName, const char* Title="InputRootFile", UInt_t identifier=0);
  //  FairFileSource(const FairFileSource& file);
    virtual ~FairFileSource();
    
    Bool_t              Init();
    Int_t               ReadEvent(UInt_t i=0);
    void                Close();
    void                Reset();

    virtual Source_Type GetSourceType() { return kFILE; }

    virtual void SetParUnpackers() {}

    virtual Bool_t InitUnpackers() { return kTRUE; }

    virtual Bool_t ReInitUnpackers() { return kTRUE; }

    /**Check the maximum event number we can run to*/
    virtual Int_t  CheckMaxEventNo(Int_t EvtEnd=0);
    /**Read the tree entry on one branch**/
    virtual void   ReadBranchEvent(const char* BrName);
    /**Read specific tree entry on one branch**/
    virtual void   ReadBranchEvent(const char* BrName, Int_t Entry);
    virtual void FillEventHeader(FairEventHeader* feh);

    const TFile*        GetRootFile(){return fRootFile;}
    /** Add a friend file (input) by name)*/
    void                AddFriend(TString FileName);
    /**Add ROOT file to input, the file will be chained to already added files*/
    void                AddFile(TString FileName);
    void                AddFriendsToChain();
    void                PrintFriendList();
    Bool_t              CompareBranchList(TFile* fileHandle, TString inputLevel);
    void                CheckFriendChains();
    void                CreateNewFriendChain(TString inputFile, TString inputLevel);
    TTree*              GetInTree() {return fInChain->GetTree();}
    TChain*             GetInChain() {return fInChain;}
    TFile*              GetInFile() {return  fRootFile;}
    void                CloseInFile() { if(fRootFile) { fRootFile->Close(); }}
    /**Set the input tree when running on PROOF worker*/
    void                SetInTree (TTree*  tempTree);
    TObjArray*          GetListOfFolders(){return fListFolder;}
    TFolder*            GetBranchDescriptionFolder(){return fCbmroot;}
    UInt_t              GetEntries(){return fNoOfEntries; }

    //    TList*              GetBranchNameList() {return fBranchNameList;}

    void                SetInputFile(TString name);

    /** Set the repetition time of the beam when it can interact (beamTime) and when no interaction happen (gapTime). The total repetition time is beamTime + gapTime */
    void                SetBeamTime(Double_t beamTime, Double_t gapTime);
    /** Set the min and max limit for event time in ns */
    void                SetEventTimeInterval(Double_t min, Double_t max);
    /** Set the mean time for the event in ns */
    void                SetEventMeanTime(Double_t mean);
    void                SetEventTime();
    Double_t		GetDeltaEventTime();
    void                SetFileHeader(FairFileHeader* f) {fFileHeader =f;}
    Double_t            GetEventTime();

    //    virtual Bool_t   SetObject(TObject* obj, const char* ObjType);
    //    virtual void     SetObjectName(const char* ObjName, const char* ObjType);

    virtual Bool_t   ActivateObject(TObject** obj, const char* BrName);

    /**Set the status of the EvtHeader
     *@param Status:  True: The header was creatged in this session and has to be filled
              FALSE: We use an existing header from previous data level
     */
    void                SetEvtHeaderNew(Bool_t Status) {fEvtHeaderIsNew = Status;}
    Bool_t              IsEvtHeaderNew() {return fEvtHeaderIsNew;}

    /** Allow to disable the testing the file layout when adding files to a chain.
     */
    void                SetCheckFileLayout(Bool_t enable) {fCheckFileLayout = enable;}

private:
    /** Title of input source, could be input, background or signal*/
    TString                           fInputTitle;
    /**ROOT file*/
    TFile*                            fRootFile;
    /** Current Entry number */
    Int_t                             fCurrentEntryNr;  //!
    /** List of all files added with AddFriend */
    std::list<TString>                fFriendFileList; //!
    std::list<TString>                fInputChainList;//!
    std::map<TString, TChain*>          fFriendTypeList;//!
    std::map<TString, std::list<TString>* > fCheckInputBranches; //!
    std::list<TString>                      fInputLevel; //!
    std::map<TString, std::multimap<TString, TArrayI> > fRunIdInfoAll; //!
    /**Input Chain */
    TChain*                             fInChain;
    /**Input Tree */
    TTree*                              fInTree;
    /** list of folders from all input (and friends) files*/
    TObjArray                           *fListFolder; //!
    /** RuntimeDb*/
    FairRuntimeDb*           fRtdb;
    /**folder structure of output*/
    TFolder*                            fCbmout;
    /**folder structure of input*/
    TFolder*                            fCbmroot;
    /***/
    UInt_t                              fSourceIdentifier;
    /**No of Entries in this source*/
    UInt_t                              fNoOfEntries;
    /**Initialization flag, true if initialized*/
    Bool_t                              IsInitialized;
    
    FairFileSource(const FairFileSource&);
    FairFileSource operator=(const FairFileSource&);

    /** MC Event header */
    FairMCEventHeader*                      fMCHeader; //!

    /**Event Header*/
    FairEventHeader*                        fEvtHeader; //!

    /**File Header*/
    FairFileHeader*                        fFileHeader; //!

    /** This is true if the event time used, came from simulation*/
    Bool_t                                  fEventTimeInMCHeader; //!
    /**This flag is true if the event header was created in this session
    * otherwise it is false which means the header was created in a previous data
    * level and used here (e.g. in the digi)
    */
    Bool_t      fEvtHeaderIsNew; //!

    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fCurrentEntryNo; //!
    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fTimeforEntryNo; //!

    /** min time for one event (ns) */
    Double_t                                fEventTimeMin;  //!
    /** max time for one Event (ns) */
    Double_t                                fEventTimeMax;  //!
    /** Time of event since th start (ns) */
    Double_t                                fEventTime;     //!
    /** Time of particles in beam (ns) */
    Double_t                                fBeamTime; //!
    /** Time without particles in beam (gap) (ns) */
    Double_t                                fGapTime; //!
    /** EventMean time used (P(t)=1/fEventMeanTime*Exp(-t/fEventMeanTime) */
    Double_t                                fEventMeanTime; //!
    /** used to generate random numbers for event time; */
    TF1*                                    fTimeProb;      //!
    /** True if the file layout should be checked when adding files to a chain.
     *  Default value is true.
     */
     Bool_t                                 fCheckFileLayout; //!

    ClassDef(FairFileSource, 3)
};


#endif /* defined(__FAIRROOT__FairFileSource__) */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//
//  FairMixedSource.h
//  FAIRROOT
//
//  Created by Mohammad Al-Turany on 08/02/14.
//
//

#ifndef __FAIRROOT__FairMixedSource__
#define __FAIRROOT__FairMixedSource__

#include "FairSource.h"
#include <list>    
#include "TChain.h"
#include "TFile.h"
#include "TF1.h"

class FairEventHeader;
class FairFileHeader;
class FairMCEventHeader;
class TString;
class FairLogger;
class FairRuntimeDb;
class TFolder;

class FairRootManager;

class FairMixedSource : public FairSource
{
public:
    FairMixedSource(TFile *f, const char* Title="InputRootFile", UInt_t identifier=0);
    FairMixedSource(const TString* RootFileName, const char* Title="InputRootFile", UInt_t identifier=0);
    FairMixedSource(const TString RootFileName, const Int_t signalId, const char* Title="InputRootFile", UInt_t identifier=0);
  //  FairMixedSource(const FairMixedSource& file);
    virtual ~FairMixedSource();
    
    Bool_t              Init();
    Int_t               ReadEvent(UInt_t i=0);
    void                Close();
    void                Reset();

    virtual Source_Type GetSourceType() { return kFILE; }

    virtual void SetParUnpackers() {}

    virtual Bool_t InitUnpackers() { return kTRUE; }

    virtual Bool_t ReInitUnpackers() { return kTRUE; }

    /**Check the maximum event number we can run to*/
    virtual Int_t  CheckMaxEventNo(Int_t EvtEnd=0);
    /**Read the tree entry on one branch**/
    void             ReadBranchEvent(const char* BrName);
    /** Read specific tree entry on one branch**/
    void             ReadBranchEvent(const char* BrName, Int_t Entry);

    void                FillEventHeader(FairEventHeader* feh);

    const TFile*        GetRootFile(){return fRootFile;}
    /** Add a friend file (input) by name)*/

    virtual Bool_t   ActivateObject(TObject** obj, const char* BrName);

    void             ReadBKEvent(UInt_t i=0);

    /**Set the input signal file
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file
     */
    void                  SetSignalFile(TString name, UInt_t identifier );
    /**Set the input background file by name*/
    void                  SetBackgroundFile(TString name);
    /**Add signal file to input
     *@param name :        signal file name
     *@param identifier :  Unsigned integer which identify the signal file to which this signal should be added
     */
    void                  AddSignalFile(TString name, UInt_t identifier );
    void                  AddBackgroundFile(TString name);

    TChain*             GetBGChain() { return  fBackgroundChain;}
    TChain*             GetSignalChainNo(UInt_t i);

    Bool_t            OpenBackgroundChain();
    Bool_t            OpenSignalChain();

    /**Set the signal to background ratio in event units
    *@param background :  Number of background Events for one signal
    *@param Signalid :    Signal file Id, used when adding (setting) the signal file
    */
    void BGWindowWidthNo(UInt_t background, UInt_t Signalid);
    /**Set the signal to background rate in time units
    *@param background :  Time of background Events before one signal
    *@param Signalid :    Signal file Id, used when adding (setting) the signal file
    */
    void BGWindowWidthTime(Double_t background, UInt_t Signalid);

    /** Set the min and max limit for event time in ns */
    void                SetEventTimeInterval(Double_t min, Double_t max);
    /** Set the mean time for the event in ns */
    void                SetEventMeanTime(Double_t mean);
    /** Set the repetition time of the beam when it can interact (beamTime) and when no interaction happen (gapTime). The total repetition time is beamTime + gapTime */
    void                SetBeamTime(Double_t beamTime, Double_t gapTime);
    void                SetEventTime();
    Double_t		GetDeltaEventTime();
    void                SetFileHeader(FairFileHeader* f) {fFileHeader =f;}
    Double_t            GetEventTime();

    /**Add ROOT file to input, the file will be chained to already added files*/
    Bool_t              CompareBranchList(TFile* fileHandle, TString inputLevel);
    /**Set the input tree when running on PROOF worker*/
    TObjArray*          GetListOfFolders(){return fListFolder;}
    TFolder*            GetBranchDescriptionFolder(){return fCbmroot;}
    UInt_t              GetEntries(){return fNoOfEntries; }

    /**Set the status of the EvtHeader
     *@param Status:  True: The header was creatged in this session and has to be filled
              FALSE: We use an existing header from previous data level
     */
    void                SetEvtHeaderNew(Bool_t Status) {fEvtHeaderIsNew = Status;}
    Bool_t              IsEvtHeaderNew() {return fEvtHeaderIsNew;}

private:
    /**IO manager */
    FairRootManager*         fRootManager;

    /** Title of input source, could be input, background or signal*/
    TString                           fInputTitle;
    /**ROOT file*/
    TFile*                            fRootFile;
    /** List of all files added with AddFriend */
    std::list<TString>                fFriendFileList; //!
    std::list<TString>                fInputChainList;//!
    std::map<TString, TChain*>          fFriendTypeList;//!
    std::map<TString, std::list<TString>* > fCheckInputBranches; //!
    std::list<TString>                      fInputLevel; //!
    std::map<TString, std::multimap<TString, TArrayI> > fRunIdInfoAll; //!
    /** list of folders from all input (and friends) files*/
    TObjArray                           *fListFolder; //!
    /** RuntimeDb*/
    FairRuntimeDb*           fRtdb;
    /**folder structure of output*/
    TFolder*                            fCbmout;
    /**folder structure of input*/
    TFolder*                            fCbmroot;
    /***/
    UInt_t                              fSourceIdentifier;
    /**No of Entries in this source*/
    UInt_t                              fNoOfEntries;
    /**Initialization flag, true if initialized*/
    Bool_t                              IsInitialized;

    /** MC Event header */
    FairMCEventHeader*                      fMCHeader; //!

    /**Event Header*/
    FairEventHeader*                        fEvtHeader; //!

    /**Output Event Header*/
    FairEventHeader*                        fOutHeader; //!

    /**File Header*/
    FairFileHeader*                        fFileHeader; //!

    /** This is true if the event time used, came from simulation*/
    Bool_t                                  fEventTimeInMCHeader; //!
    /**This flag is true if the event header was created in this session
    * otherwise it is false which means the header was created in a previous data
    * level and used here (e.g. in the digi)
    */
    Bool_t      fEvtHeaderIsNew; //!

    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fCurrentEntryNo; //!
    /** for internal use, to return the same event time for the same entry*/
    UInt_t                                  fTimeforEntryNo; //!
    /* /\**No of entries in BG Chain*\/ */
    UInt_t                                  fNoOfBGEntries; //!
    /* /\**Hold the current entry for each input chain*\/ */
    std::map<UInt_t, UInt_t>                fCurrentEntry; //! 

    /** min time for one event (ns) */
    Double_t                                fEventTimeMin;  //!
    /** max time for one Event (ns) */
    Double_t                                fEventTimeMax;  //!
    /** Time of event since th start (ns) */
    Double_t                                fEventTime;     //!
    /** Time of particles in beam (ns) */
    Double_t                                fBeamTime; //!
    /** Time without particles in beam (gap) (ns) */
    Double_t                                fGapTime; //!
    /** EventMean time used (P(t)=1/fEventMeanTime*Exp(-t/fEventMeanTime) */
    Double_t                                fEventMeanTime; //!
    /** used to generate random numbers for event time; */
    TF1*                                    fTimeProb;      //!

    /**holds the SB ratio by number*/
    std::map<UInt_t, Double_t>              fSignalBGN;//! 
    /* /\**True for background window in entry units*\/ */
    Bool_t                                  fSBRatiobyN;  //! 
    /* /\**True for background window in time units (ns) *\/ */
    Bool_t                                  fSBRatiobyT;  //!

    /**Actual identifier of the added signals, this is used to identify how many signals are added*/
    UInt_t                              fActualSignalIdentifier; //!
    /** Total number of signals added (Types and not files!)*/
    UInt_t                              fNoOfSignals; //!
    /** list of chains which has to be created for the different signals*/
    std::list<TString>*                  fSignalChainList; //!
    /**Chain containing the background*/
    TChain*                              fBackgroundChain; //!
    std::map<UInt_t, TChain*>            fSignalTypeList;//!

    FairMixedSource(const FairMixedSource&);
    FairMixedSource& operator=(const FairMixedSource&);
    
public:
    ClassDef(FairMixedSource, 0)
};


#endif /* defined(__FAIRROOT__FairMixedSource__) */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairMbsSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----              Copied from FairSource 01.11.2013 by F.Uhlig         -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef FAIRONLINESOURCE_H
#define FAIRONLINESOURCE_H

#include "FairSource.h"
#include "TObjArray.h"

#include "FairUnpack.h"


class FairOnlineSource : public FairSource
{
  public:
    FairOnlineSource();
    FairOnlineSource(const FairOnlineSource& source);
    virtual ~FairOnlineSource();

    inline void AddUnpacker(FairUnpack* unpacker) { fUnpackers->Add(unpacker); }
    inline const TObjArray* GetUnpackers() const { return fUnpackers; }

    virtual Bool_t Init() = 0;
    virtual Int_t ReadEvent(UInt_t=0) = 0;
    virtual void Close() = 0;

    virtual void SetParUnpackers();

    virtual Bool_t InitUnpackers();

    virtual Bool_t ReInitUnpackers();

    void Reset();

    virtual Source_Type GetSourceType() { return kONLINE; }

  protected:
    TObjArray* fUnpackers;

  private:
    ClassDef(FairOnlineSource, 0)
};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                           FairLmdSource                           -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRLMDSOURCE_H
#define FAIRLMDSOURCE_H

extern "C"
{
#include "f_evt.h"
#include "s_filhe_swap.h"
#include "s_bufhe_swap.h"
}

#include "TString.h"

#include "FairMbsSource.h"


class TList;


class FairLmdSource : public FairMbsSource
{
  public:
    FairLmdSource();
    FairLmdSource(const FairLmdSource& source);
    virtual ~FairLmdSource();

    void AddFile(TString fileName);
    void AddPath(TString dir, TString wildCard);
    inline Int_t GetCurrentFile() const { return fCurrentFile; }
    inline const TList* GetFileNames() const { return fFileNames; }

    virtual Bool_t Init();
    virtual Int_t ReadEvent(UInt_t=0);
    virtual void Close();

  protected:
    Bool_t OpenNextFile(TString fileName);

    Int_t fCurrentFile;
	Int_t fNEvent;
	Int_t fCurrentEvent;
    TList* fFileNames;
    s_evt_channel* fxInputChannel;
    s_ve10_1* fxEvent;
    s_bufhe* fxBuffer;
    Int_t* fxEventData;
    s_ves10_1* fxSubEvent;
	s_filhe* fxInfoHeader;

    FairLmdSource& operator=(const FairLmdSource&);

    ClassDef(FairLmdSource, 0)
};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                          FairRemoteSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRREMOTESOURCE_H
#define FAIRREMOTESOURCE_H

#include "FairMbsSource.h"


class TSocket;
class MRevBuffer;
class REvent;


class FairRemoteSource : public FairMbsSource
{
  public:
    FairRemoteSource(char* node);
    FairRemoteSource(const FairRemoteSource& source);
    virtual ~FairRemoteSource();

    virtual Bool_t Init();
    virtual Int_t ReadEvent(UInt_t=0);
    virtual void Close();

    inline const char* GetNode() const { return fNode; }

  private:
    char* fNode;
    TSocket* fSocket;
    MRevBuffer* fBuffer;
    REvent* fREvent;

    FairRemoteSource& operator=(const FairRemoteSource&);
    
  public:
    ClassDef(FairRemoteSource, 0)
};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairMbsSource                         -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----              Copied from FairSource 01.11.2013 by F.Uhlig         -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef FAIRMBSSOURCE_H
#define FAIRMBSSOURCE_H

#include "FairOnlineSource.h"
#include "TObjArray.h"

#include "FairUnpack.h"


class FairMbsSource : public FairOnlineSource
{
  public:
    FairMbsSource();
    FairMbsSource(const FairMbsSource& source);
    virtual ~FairMbsSource();

    virtual Bool_t Init() = 0;
    virtual Int_t ReadEvent(UInt_t=0) = 0;
    virtual void Close() = 0;

  protected:
    Bool_t Unpack(Int_t* data, Int_t size,
                  Short_t type, Short_t subType,
                  Short_t procId, Short_t subCrate, Short_t control);

    ClassDef(FairMbsSource, 0)
};


#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairUnpack                            -----
// -----                    Created 12.04.2013 by D.Kresan                 -----
// -----------------------------------------------------------------------------

#ifndef FAIRUNPACK_H
#define FAIRUNPACK_H

#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "TObject.h"


class FairUnpack : public TObject
{
  public:
    FairUnpack(Short_t type, Short_t subType,
               Short_t procId, Short_t subCrate, Short_t control);
    virtual ~FairUnpack();

    virtual Bool_t Init() = 0;
    virtual Bool_t ReInit() { return kTRUE; }
    virtual Bool_t DoUnpack(Int_t* data, Int_t size) = 0;
    virtual void   Reset() = 0;
    virtual void   SetParContainers() {  };

    inline Short_t GetType()    const { return fType;     }
    inline Short_t GetSubType() const { return fSubType;  }
    inline Short_t GetProcId()  const { return fProcId;   }
    inline Short_t GetSubCrate() const { return fSubCrate; }
    inline Short_t GetControl()  const { return fControl;  }

  private:
    Short_t fType;
    Short_t fSubType;
    Short_t fProcId;
    Short_t fSubCrate;
    Short_t fControl;

  protected:
    virtual void Register() = 0;

  public:
    ClassDef(FairUnpack, 0)
};


#endif



/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//////////////////////////////////////////////////////////////////////
// Copyright:
//   GSI, Gesellschaft fuer Schwerionenforschung mbH
//   Planckstr. 1
//   D-64291 Darmstadt
//   Germany
// created 16. 2.1999 by Horst Goeringer
//////////////////////////////////////////////////////////////////////
// MRevBuffer.h
//   description of class MRevBuffer
//   ROOT client package for multithreaded remote event server (MBS)
//////////////////////////////////////////////////////////////////////
// 20. 8.1999, H.G.: MRevBuffer::RevGetI added
//  6. 3.2000, H.G.: new member function RevStatus
//////////////////////////////////////////////////////////////////////

#ifndef MRevBuffer_H
#define MRevBuffer_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Int_t, ClassDef, etc

class TSocket;

class REvent : public TObject
{
  private:
    Int_t  iSize;              // event size (byte)
    Int_t  iNumb;              // event number
    Int_t*  piData;            // event parameter

    REvent(const REvent&);
    REvent& operator=(const REvent&);

  public:
    REvent();                  // constructor
    ~REvent();                 // destructor

    void ReFillHead(Int_t* pHead);   // unpack and fill event header
    void ReFillData(Int_t* pData);   // unpack and fill event data

    Int_t ReGetNumb();               // get event number
    Int_t ReGetSize();               // get event size
    Int_t ReGetData(Int_t ichan);    // get event parameter ichan
    Int_t* GetData() { return piData; }

    Int_t nSubEvt;
    Int_t subEvtSize[100];
    Short_t subEvtType[100];
    Short_t subEvtSubType[100];
    Short_t subEvtProcId[100];
    Short_t subEvtSubCrate[100];
    Short_t subEvtControl[100];
    Int_t* pSubEvt[100];

    ClassDef(REvent, 0)           // prototype for event
};

//////////////////////////////////////////////////////////////////////

class MRevBuffer : public TObject
{
  private:
    TSocket* pTSocket;     // ptr socket of channel to event server
    Int_t  iSocket;        // socket id of channel to event server
    Int_t  iBufNo1;        // first buffer no. received (test)
    Int_t  iBufNo2;        // last buffer no. received (test)
    Int_t  iDebug;         // verbosity level (test)
    Int_t  iSwap;          // > 0: swap event data
    Int_t  iStatus;        // current status of server

    Int_t  iBufSizeAlloc;  // allocated buffer size
    Int_t  iBufSize;       // size current buffer
    Int_t  iBufNo;         // current buffer no.
    Int_t  iFragBegin;     // > 0: last buffer ended with fragment
    Int_t  iFragConc;      // no. of concatenated fragments
    Int_t  iFragBeginIgn;  // no. of ignored fragment begins
    Int_t  iFragEndIgn;    // no. of ignored fragment ends

    Int_t  iHeadPar;       // no. of (4 byte) parms buffer header
    Int_t  iEvtMax;        // no. of events requested
    Int_t  iEvtNo;         // last event no. handled
    Int_t  iEvtRel;        // rel. event no. in buffer
    Int_t  iEvtBuf;        // no. of events in current buffer
    Int_t  iEvtPar;        // no. of parameters in event (incl. len)
    Int_t*  piBuf;         // ptr event buffer
    Int_t*  piNextEvt;     // ptr first element next event
    REvent* pEvt;          // ptr event class

    MRevBuffer(const MRevBuffer&);
    MRevBuffer& operator=(const MRevBuffer&);

  public:
    MRevBuffer( Int_t iMode); // constructor
    ~MRevBuffer();            // destructor

    TSocket* RevOpen( char* pNode, Int_t iPort, Int_t iEvent);
    // input: node name and port number server, req. no. of events
    // returns Socket ptr of server connection

    Int_t* RevGetI( TSocket* pSocket, Int_t iFlush);
    // get next event (pointer) from buffer, input:
    // Socket ptr,
    // iFlush = 1: skip current buffer (not impl)

    REvent* RevGet( TSocket* pSocket, Int_t iFlush, Int_t iSkip);
    // get next event (pointer) from buffer, input:
    // Socket ptr,
    // iFlush = 1: skip current buffer (not impl)
    // iSkip > 0: take only each iSkip event (not impl)

    Int_t RevStatus(Int_t iOut);
    // get status information (iOut = 1: also message to stdout)
    // = 0: last event request successfull
    // = 1: server not yet connected
    // = 2: server connected, but still no request for events
    // = 3: server connection okay, but currently no DAQ events
    // = 4: connection to server closed
    // = 5: connection to server closed after user break (CTL C)
    // = 6: connection to server closed after failure

    void RevBufWait(Int_t iWait);
    // wait for iWait seconds

    Int_t RevBufsize();
    // get size of current buffer (byte)

    void  RevClose( TSocket* pSocket );           // input Socket ptr

    ClassDef(MRevBuffer, 0)        // prototype for remote event buffer
};

#endif     // !MRevBuffer_H 
// -----------------------------------------------------------------------------
// ----- FairMbsStreamSource header file                                   -----
// -----                                                                   -----
// ----- created by C. Simon on 2014-09-12                                 -----
// -----                                                                   -----
// ----- based on FairLmdSource by D. Kresan                               -----
// -----                                                                   -----
// ----- revision 23363, 2013-12-26                                        -----
// -----------------------------------------------------------------------------

#ifndef FAIRMBSSTREAMSOURCE_H
#define FAIRMBSSTREAMSOURCE_H

extern "C"
{
#include "f_evt.h"
#include "s_filhe_swap.h"
#include "s_bufhe_swap.h"
}

#include "TString.h"

#include "FairMbsSource.h"

class FairMbsStreamSource : public FairMbsSource
{
  public:
    FairMbsStreamSource(TString tServerName);
    FairMbsStreamSource(const FairMbsStreamSource& source);
    virtual ~FairMbsStreamSource();

    virtual Bool_t Init();
    virtual Int_t ReadEvent(UInt_t=0);
    virtual void Close();

    const char* GetServerName() const {return fServerName.Data();};

  private:
    Bool_t ConnectToServer();

    TString fServerName;

    s_evt_channel* fxInputChannel;
    s_ve10_1* fxEvent;
    s_bufhe* fxBuffer;
    Int_t* fxEventData;
    s_ves10_1* fxSubEvent;

    FairMbsStreamSource& operator=(const FairMbsStreamSource&);


  public:
    ClassDef(FairMbsStreamSource, 0)
};


#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairAnaSelector", payloadCode, "@",
"FairBaseContFact", payloadCode, "@",
"FairBaseParSet", payloadCode, "@",
"FairDetector", payloadCode, "@",
"FairEventBuilder", payloadCode, "@",
"FairEventBuilderManager", payloadCode, "@",
"FairEventHeader", payloadCode, "@",
"FairField", payloadCode, "@",
"FairFieldFactory", payloadCode, "@",
"FairFileHeader", payloadCode, "@",
"FairFileInfo", payloadCode, "@",
"FairFileSource", payloadCode, "@",
"FairGeaneApplication", payloadCode, "@",
"FairGenerator", payloadCode, "@",
"FairGenericStack", payloadCode, "@",
"FairGeoParSet", payloadCode, "@",
"FairHit", payloadCode, "@",
"FairIon", payloadCode, "@",
"FairLink", payloadCode, "@",
"FairLinkManager", payloadCode, "@",
"FairLmdSource", payloadCode, "@",
"FairMCApplication", payloadCode, "@",
"FairMCEventHeader", payloadCode, "@",
"FairMCPoint", payloadCode, "@",
"FairMbsSource", payloadCode, "@",
"FairMbsStreamSource", payloadCode, "@",
"FairMesh", payloadCode, "@",
"FairMixedSource", payloadCode, "@",
"FairModule", payloadCode, "@",
"FairMultiLinkedData", payloadCode, "@",
"FairMultiLinkedData_Interface", payloadCode, "@",
"FairOnlineSource", payloadCode, "@",
"FairParticle", payloadCode, "@",
"FairPrimaryGenerator", payloadCode, "@",
"FairRKPropagator", payloadCode, "@",
"FairRadGridManager", payloadCode, "@",
"FairRadLenManager", payloadCode, "@",
"FairRadLenPoint", payloadCode, "@",
"FairRadMapManager", payloadCode, "@",
"FairRadMapPoint", payloadCode, "@",
"FairRecoEventHeader", payloadCode, "@",
"FairRemoteSource", payloadCode, "@",
"FairRingSorter", payloadCode, "@",
"FairRingSorterTask", payloadCode, "@",
"FairRootManager", payloadCode, "@",
"FairRun", payloadCode, "@",
"FairRunAna", payloadCode, "@",
"FairRunAnaProof", payloadCode, "@",
"FairRunIdGenerator", payloadCode, "@",
"FairRunInfo", payloadCode, "@",
"FairRunOnline", payloadCode, "@",
"FairRunSim", payloadCode, "@",
"FairSource", payloadCode, "@",
"FairTSBufferFunctional", payloadCode, "@",
"FairTask", payloadCode, "@",
"FairTimeStamp", payloadCode, "@",
"FairTrackParam", payloadCode, "@",
"FairTrajFilter", payloadCode, "@",
"FairUnpack", payloadCode, "@",
"FairVolume", payloadCode, "@",
"FairVolumeList", payloadCode, "@",
"FairWriteoutBuffer", payloadCode, "@",
"MRevBuffer", payloadCode, "@",
"REvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__BaseDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__BaseDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__BaseDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__BaseDict() {
  TriggerDictionaryInitialization_G__BaseDict_Impl();
}

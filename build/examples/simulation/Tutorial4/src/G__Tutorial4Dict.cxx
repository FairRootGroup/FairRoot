// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIsimulationdITutorial4dIsrcdIG__Tutorial4Dict

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
#include "mc/FairTutorialDet4.h"
#include "mc/FairTutorialDet4Geo.h"
#include "param/FairTutorialDet4ContFact.h"
#include "param/FairTutorialDet4GeoPar.h"
#include "param/FairTutorialDet4MisalignPar.h"
#include "data/FairTutorialDet4Point.h"
#include "data/FairTutorialDet4Hit.h"
#include "reco/FairTutorialDet4HitProducerIdealMisalign.h"
#include "reco/FairTutorialDet4StraightLineFitter.h"
#include "reco/FairTutorialDet4MilleWriter.h"
#include "tools/FairTutorialDet4GeoHandler.h"
#include "display/FairTutorialDet4PointDraw.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairTutorialDet4ContFact(void *p = 0);
   static void *newArray_FairTutorialDet4ContFact(Long_t size, void *p);
   static void delete_FairTutorialDet4ContFact(void *p);
   static void deleteArray_FairTutorialDet4ContFact(void *p);
   static void destruct_FairTutorialDet4ContFact(void *p);
   static void streamer_FairTutorialDet4ContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4ContFact*)
   {
      ::FairTutorialDet4ContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4ContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4ContFact", ::FairTutorialDet4ContFact::Class_Version(), "invalid", 212,
                  typeid(::FairTutorialDet4ContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4ContFact::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet4ContFact) );
      instance.SetNew(&new_FairTutorialDet4ContFact);
      instance.SetNewArray(&newArray_FairTutorialDet4ContFact);
      instance.SetDelete(&delete_FairTutorialDet4ContFact);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4ContFact);
      instance.SetDestructor(&destruct_FairTutorialDet4ContFact);
      instance.SetStreamerFunc(&streamer_FairTutorialDet4ContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4ContFact*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4ContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4ContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4Geo(void *p = 0);
   static void *newArray_FairTutorialDet4Geo(Long_t size, void *p);
   static void delete_FairTutorialDet4Geo(void *p);
   static void deleteArray_FairTutorialDet4Geo(void *p);
   static void destruct_FairTutorialDet4Geo(void *p);
   static void streamer_FairTutorialDet4Geo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4Geo*)
   {
      ::FairTutorialDet4Geo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4Geo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4Geo", ::FairTutorialDet4Geo::Class_Version(), "invalid", 169,
                  typeid(::FairTutorialDet4Geo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4Geo::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet4Geo) );
      instance.SetNew(&new_FairTutorialDet4Geo);
      instance.SetNewArray(&newArray_FairTutorialDet4Geo);
      instance.SetDelete(&delete_FairTutorialDet4Geo);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4Geo);
      instance.SetDestructor(&destruct_FairTutorialDet4Geo);
      instance.SetStreamerFunc(&streamer_FairTutorialDet4Geo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4Geo*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4Geo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4Geo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4GeoPar(void *p = 0);
   static void *newArray_FairTutorialDet4GeoPar(Long_t size, void *p);
   static void delete_FairTutorialDet4GeoPar(void *p);
   static void deleteArray_FairTutorialDet4GeoPar(void *p);
   static void destruct_FairTutorialDet4GeoPar(void *p);
   static void streamer_FairTutorialDet4GeoPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4GeoPar*)
   {
      ::FairTutorialDet4GeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4GeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4GeoPar", ::FairTutorialDet4GeoPar::Class_Version(), "invalid", 242,
                  typeid(::FairTutorialDet4GeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4GeoPar::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet4GeoPar) );
      instance.SetNew(&new_FairTutorialDet4GeoPar);
      instance.SetNewArray(&newArray_FairTutorialDet4GeoPar);
      instance.SetDelete(&delete_FairTutorialDet4GeoPar);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4GeoPar);
      instance.SetDestructor(&destruct_FairTutorialDet4GeoPar);
      instance.SetStreamerFunc(&streamer_FairTutorialDet4GeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4GeoPar*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4GeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4GeoPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4MisalignPar(void *p = 0);
   static void *newArray_FairTutorialDet4MisalignPar(Long_t size, void *p);
   static void delete_FairTutorialDet4MisalignPar(void *p);
   static void deleteArray_FairTutorialDet4MisalignPar(void *p);
   static void destruct_FairTutorialDet4MisalignPar(void *p);
   static void streamer_FairTutorialDet4MisalignPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4MisalignPar*)
   {
      ::FairTutorialDet4MisalignPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4MisalignPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4MisalignPar", ::FairTutorialDet4MisalignPar::Class_Version(), "invalid", 295,
                  typeid(::FairTutorialDet4MisalignPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4MisalignPar::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet4MisalignPar) );
      instance.SetNew(&new_FairTutorialDet4MisalignPar);
      instance.SetNewArray(&newArray_FairTutorialDet4MisalignPar);
      instance.SetDelete(&delete_FairTutorialDet4MisalignPar);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4MisalignPar);
      instance.SetDestructor(&destruct_FairTutorialDet4MisalignPar);
      instance.SetStreamerFunc(&streamer_FairTutorialDet4MisalignPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4MisalignPar*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4MisalignPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4MisalignPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4(void *p = 0);
   static void *newArray_FairTutorialDet4(Long_t size, void *p);
   static void delete_FairTutorialDet4(void *p);
   static void deleteArray_FairTutorialDet4(void *p);
   static void destruct_FairTutorialDet4(void *p);
   static void streamer_FairTutorialDet4(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4*)
   {
      ::FairTutorialDet4 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4", ::FairTutorialDet4::Class_Version(), "invalid", 32,
                  typeid(::FairTutorialDet4), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet4) );
      instance.SetNew(&new_FairTutorialDet4);
      instance.SetNewArray(&newArray_FairTutorialDet4);
      instance.SetDelete(&delete_FairTutorialDet4);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4);
      instance.SetDestructor(&destruct_FairTutorialDet4);
      instance.SetStreamerFunc(&streamer_FairTutorialDet4);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4Point(void *p = 0);
   static void *newArray_FairTutorialDet4Point(Long_t size, void *p);
   static void delete_FairTutorialDet4Point(void *p);
   static void deleteArray_FairTutorialDet4Point(void *p);
   static void destruct_FairTutorialDet4Point(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4Point*)
   {
      ::FairTutorialDet4Point *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4Point >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4Point", ::FairTutorialDet4Point::Class_Version(), "invalid", 348,
                  typeid(::FairTutorialDet4Point), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4Point::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet4Point) );
      instance.SetNew(&new_FairTutorialDet4Point);
      instance.SetNewArray(&newArray_FairTutorialDet4Point);
      instance.SetDelete(&delete_FairTutorialDet4Point);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4Point);
      instance.SetDestructor(&destruct_FairTutorialDet4Point);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4Point*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4Point*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4Point*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4Hit(void *p = 0);
   static void *newArray_FairTutorialDet4Hit(Long_t size, void *p);
   static void delete_FairTutorialDet4Hit(void *p);
   static void deleteArray_FairTutorialDet4Hit(void *p);
   static void destruct_FairTutorialDet4Hit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4Hit*)
   {
      ::FairTutorialDet4Hit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4Hit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4Hit", ::FairTutorialDet4Hit::Class_Version(), "invalid", 403,
                  typeid(::FairTutorialDet4Hit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4Hit::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet4Hit) );
      instance.SetNew(&new_FairTutorialDet4Hit);
      instance.SetNewArray(&newArray_FairTutorialDet4Hit);
      instance.SetDelete(&delete_FairTutorialDet4Hit);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4Hit);
      instance.SetDestructor(&destruct_FairTutorialDet4Hit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4Hit*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4Hit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4Hit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4HitProducerIdealMisalign(void *p = 0);
   static void *newArray_FairTutorialDet4HitProducerIdealMisalign(Long_t size, void *p);
   static void delete_FairTutorialDet4HitProducerIdealMisalign(void *p);
   static void deleteArray_FairTutorialDet4HitProducerIdealMisalign(void *p);
   static void destruct_FairTutorialDet4HitProducerIdealMisalign(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4HitProducerIdealMisalign*)
   {
      ::FairTutorialDet4HitProducerIdealMisalign *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4HitProducerIdealMisalign >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4HitProducerIdealMisalign", ::FairTutorialDet4HitProducerIdealMisalign::Class_Version(), "invalid", 463,
                  typeid(::FairTutorialDet4HitProducerIdealMisalign), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4HitProducerIdealMisalign::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet4HitProducerIdealMisalign) );
      instance.SetNew(&new_FairTutorialDet4HitProducerIdealMisalign);
      instance.SetNewArray(&newArray_FairTutorialDet4HitProducerIdealMisalign);
      instance.SetDelete(&delete_FairTutorialDet4HitProducerIdealMisalign);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4HitProducerIdealMisalign);
      instance.SetDestructor(&destruct_FairTutorialDet4HitProducerIdealMisalign);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4HitProducerIdealMisalign*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4HitProducerIdealMisalign*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4HitProducerIdealMisalign*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4GeoHandler(void *p = 0);
   static void *newArray_FairTutorialDet4GeoHandler(Long_t size, void *p);
   static void delete_FairTutorialDet4GeoHandler(void *p);
   static void deleteArray_FairTutorialDet4GeoHandler(void *p);
   static void destruct_FairTutorialDet4GeoHandler(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4GeoHandler*)
   {
      ::FairTutorialDet4GeoHandler *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4GeoHandler >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4GeoHandler", ::FairTutorialDet4GeoHandler::Class_Version(), "invalid", 712,
                  typeid(::FairTutorialDet4GeoHandler), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4GeoHandler::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet4GeoHandler) );
      instance.SetNew(&new_FairTutorialDet4GeoHandler);
      instance.SetNewArray(&newArray_FairTutorialDet4GeoHandler);
      instance.SetDelete(&delete_FairTutorialDet4GeoHandler);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4GeoHandler);
      instance.SetDestructor(&destruct_FairTutorialDet4GeoHandler);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4GeoHandler*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4GeoHandler*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4GeoHandler*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4StraightLineFitter(void *p = 0);
   static void *newArray_FairTutorialDet4StraightLineFitter(Long_t size, void *p);
   static void delete_FairTutorialDet4StraightLineFitter(void *p);
   static void deleteArray_FairTutorialDet4StraightLineFitter(void *p);
   static void destruct_FairTutorialDet4StraightLineFitter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4StraightLineFitter*)
   {
      ::FairTutorialDet4StraightLineFitter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4StraightLineFitter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4StraightLineFitter", ::FairTutorialDet4StraightLineFitter::Class_Version(), "invalid", 539,
                  typeid(::FairTutorialDet4StraightLineFitter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4StraightLineFitter::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet4StraightLineFitter) );
      instance.SetNew(&new_FairTutorialDet4StraightLineFitter);
      instance.SetNewArray(&newArray_FairTutorialDet4StraightLineFitter);
      instance.SetDelete(&delete_FairTutorialDet4StraightLineFitter);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4StraightLineFitter);
      instance.SetDestructor(&destruct_FairTutorialDet4StraightLineFitter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4StraightLineFitter*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4StraightLineFitter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4StraightLineFitter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4MilleWriter(void *p = 0);
   static void *newArray_FairTutorialDet4MilleWriter(Long_t size, void *p);
   static void delete_FairTutorialDet4MilleWriter(void *p);
   static void deleteArray_FairTutorialDet4MilleWriter(void *p);
   static void destruct_FairTutorialDet4MilleWriter(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4MilleWriter*)
   {
      ::FairTutorialDet4MilleWriter *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4MilleWriter >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4MilleWriter", ::FairTutorialDet4MilleWriter::Class_Version(), "invalid", 610,
                  typeid(::FairTutorialDet4MilleWriter), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4MilleWriter::Dictionary, isa_proxy, 4,
                  sizeof(::FairTutorialDet4MilleWriter) );
      instance.SetNew(&new_FairTutorialDet4MilleWriter);
      instance.SetNewArray(&newArray_FairTutorialDet4MilleWriter);
      instance.SetDelete(&delete_FairTutorialDet4MilleWriter);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4MilleWriter);
      instance.SetDestructor(&destruct_FairTutorialDet4MilleWriter);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4MilleWriter*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4MilleWriter*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4MilleWriter*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTutorialDet4PointDraw(void *p = 0);
   static void *newArray_FairTutorialDet4PointDraw(Long_t size, void *p);
   static void delete_FairTutorialDet4PointDraw(void *p);
   static void deleteArray_FairTutorialDet4PointDraw(void *p);
   static void destruct_FairTutorialDet4PointDraw(void *p);
   static void streamer_FairTutorialDet4PointDraw(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTutorialDet4PointDraw*)
   {
      ::FairTutorialDet4PointDraw *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTutorialDet4PointDraw >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTutorialDet4PointDraw", ::FairTutorialDet4PointDraw::Class_Version(), "invalid", 800,
                  typeid(::FairTutorialDet4PointDraw), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTutorialDet4PointDraw::Dictionary, isa_proxy, 16,
                  sizeof(::FairTutorialDet4PointDraw) );
      instance.SetNew(&new_FairTutorialDet4PointDraw);
      instance.SetNewArray(&newArray_FairTutorialDet4PointDraw);
      instance.SetDelete(&delete_FairTutorialDet4PointDraw);
      instance.SetDeleteArray(&deleteArray_FairTutorialDet4PointDraw);
      instance.SetDestructor(&destruct_FairTutorialDet4PointDraw);
      instance.SetStreamerFunc(&streamer_FairTutorialDet4PointDraw);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTutorialDet4PointDraw*)
   {
      return GenerateInitInstanceLocal((::FairTutorialDet4PointDraw*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTutorialDet4PointDraw*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4ContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4ContFact::Class_Name()
{
   return "FairTutorialDet4ContFact";
}

//______________________________________________________________________________
const char *FairTutorialDet4ContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4ContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4ContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4ContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4ContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4ContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4ContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4ContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4Geo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4Geo::Class_Name()
{
   return "FairTutorialDet4Geo";
}

//______________________________________________________________________________
const char *FairTutorialDet4Geo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Geo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4Geo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Geo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4Geo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Geo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4Geo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Geo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4GeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4GeoPar::Class_Name()
{
   return "FairTutorialDet4GeoPar";
}

//______________________________________________________________________________
const char *FairTutorialDet4GeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4GeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4GeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4GeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4GeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4GeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4GeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4GeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4MisalignPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4MisalignPar::Class_Name()
{
   return "FairTutorialDet4MisalignPar";
}

//______________________________________________________________________________
const char *FairTutorialDet4MisalignPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4MisalignPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4MisalignPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4MisalignPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4MisalignPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4MisalignPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4MisalignPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4MisalignPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4::Class_Name()
{
   return "FairTutorialDet4";
}

//______________________________________________________________________________
const char *FairTutorialDet4::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4Point::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4Point::Class_Name()
{
   return "FairTutorialDet4Point";
}

//______________________________________________________________________________
const char *FairTutorialDet4Point::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Point*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4Point::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Point*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4Point::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Point*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4Point::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Point*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4Hit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4Hit::Class_Name()
{
   return "FairTutorialDet4Hit";
}

//______________________________________________________________________________
const char *FairTutorialDet4Hit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Hit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4Hit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Hit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4Hit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Hit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4Hit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4Hit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4HitProducerIdealMisalign::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4HitProducerIdealMisalign::Class_Name()
{
   return "FairTutorialDet4HitProducerIdealMisalign";
}

//______________________________________________________________________________
const char *FairTutorialDet4HitProducerIdealMisalign::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4HitProducerIdealMisalign*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4HitProducerIdealMisalign::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4HitProducerIdealMisalign*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4HitProducerIdealMisalign::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4HitProducerIdealMisalign*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4HitProducerIdealMisalign::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4HitProducerIdealMisalign*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4GeoHandler::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4GeoHandler::Class_Name()
{
   return "FairTutorialDet4GeoHandler";
}

//______________________________________________________________________________
const char *FairTutorialDet4GeoHandler::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4GeoHandler*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4GeoHandler::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4GeoHandler*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4GeoHandler::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4GeoHandler*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4GeoHandler::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4GeoHandler*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4StraightLineFitter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4StraightLineFitter::Class_Name()
{
   return "FairTutorialDet4StraightLineFitter";
}

//______________________________________________________________________________
const char *FairTutorialDet4StraightLineFitter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4StraightLineFitter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4StraightLineFitter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4StraightLineFitter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4StraightLineFitter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4StraightLineFitter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4StraightLineFitter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4StraightLineFitter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4MilleWriter::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4MilleWriter::Class_Name()
{
   return "FairTutorialDet4MilleWriter";
}

//______________________________________________________________________________
const char *FairTutorialDet4MilleWriter::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4MilleWriter*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4MilleWriter::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4MilleWriter*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4MilleWriter::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4MilleWriter*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4MilleWriter::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4MilleWriter*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTutorialDet4PointDraw::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTutorialDet4PointDraw::Class_Name()
{
   return "FairTutorialDet4PointDraw";
}

//______________________________________________________________________________
const char *FairTutorialDet4PointDraw::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4PointDraw*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTutorialDet4PointDraw::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4PointDraw*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTutorialDet4PointDraw::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4PointDraw*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTutorialDet4PointDraw::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTutorialDet4PointDraw*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairTutorialDet4ContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4ContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4ContFact(void *p) {
      return  p ? new(p) ::FairTutorialDet4ContFact : new ::FairTutorialDet4ContFact;
   }
   static void *newArray_FairTutorialDet4ContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4ContFact[nElements] : new ::FairTutorialDet4ContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4ContFact(void *p) {
      delete ((::FairTutorialDet4ContFact*)p);
   }
   static void deleteArray_FairTutorialDet4ContFact(void *p) {
      delete [] ((::FairTutorialDet4ContFact*)p);
   }
   static void destruct_FairTutorialDet4ContFact(void *p) {
      typedef ::FairTutorialDet4ContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet4ContFact(TBuffer &buf, void *obj) {
      ((::FairTutorialDet4ContFact*)obj)->::FairTutorialDet4ContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet4ContFact

//______________________________________________________________________________
void FairTutorialDet4Geo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4Geo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoSet::Streamer(R__b);
      R__b.ReadStaticArray((char*)modName);
      R__b.ReadStaticArray((char*)eleName);
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet4Geo::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet4Geo::IsA(), kTRUE);
      FairGeoSet::Streamer(R__b);
      R__b.WriteArray(modName, 20);
      R__b.WriteArray(eleName, 20);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4Geo(void *p) {
      return  p ? new(p) ::FairTutorialDet4Geo : new ::FairTutorialDet4Geo;
   }
   static void *newArray_FairTutorialDet4Geo(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4Geo[nElements] : new ::FairTutorialDet4Geo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4Geo(void *p) {
      delete ((::FairTutorialDet4Geo*)p);
   }
   static void deleteArray_FairTutorialDet4Geo(void *p) {
      delete [] ((::FairTutorialDet4Geo*)p);
   }
   static void destruct_FairTutorialDet4Geo(void *p) {
      typedef ::FairTutorialDet4Geo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet4Geo(TBuffer &buf, void *obj) {
      ((::FairTutorialDet4Geo*)obj)->::FairTutorialDet4Geo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet4Geo

//______________________________________________________________________________
void FairTutorialDet4GeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4GeoPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b >> fGlobalCoordinates;
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet4GeoPar::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet4GeoPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b << fGlobalCoordinates;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4GeoPar(void *p) {
      return  p ? new(p) ::FairTutorialDet4GeoPar : new ::FairTutorialDet4GeoPar;
   }
   static void *newArray_FairTutorialDet4GeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4GeoPar[nElements] : new ::FairTutorialDet4GeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4GeoPar(void *p) {
      delete ((::FairTutorialDet4GeoPar*)p);
   }
   static void deleteArray_FairTutorialDet4GeoPar(void *p) {
      delete [] ((::FairTutorialDet4GeoPar*)p);
   }
   static void destruct_FairTutorialDet4GeoPar(void *p) {
      typedef ::FairTutorialDet4GeoPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet4GeoPar(TBuffer &buf, void *obj) {
      ((::FairTutorialDet4GeoPar*)obj)->::FairTutorialDet4GeoPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet4GeoPar

//______________________________________________________________________________
void FairTutorialDet4MisalignPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4MisalignPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      fShiftX.Streamer(R__b);
      fShiftY.Streamer(R__b);
      fShiftZ.Streamer(R__b);
      fRotX.Streamer(R__b);
      fRotY.Streamer(R__b);
      fRotZ.Streamer(R__b);
      R__b >> fNrOfDetectors;
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet4MisalignPar::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet4MisalignPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      fShiftX.Streamer(R__b);
      fShiftY.Streamer(R__b);
      fShiftZ.Streamer(R__b);
      fRotX.Streamer(R__b);
      fRotY.Streamer(R__b);
      fRotZ.Streamer(R__b);
      R__b << fNrOfDetectors;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4MisalignPar(void *p) {
      return  p ? new(p) ::FairTutorialDet4MisalignPar : new ::FairTutorialDet4MisalignPar;
   }
   static void *newArray_FairTutorialDet4MisalignPar(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4MisalignPar[nElements] : new ::FairTutorialDet4MisalignPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4MisalignPar(void *p) {
      delete ((::FairTutorialDet4MisalignPar*)p);
   }
   static void deleteArray_FairTutorialDet4MisalignPar(void *p) {
      delete [] ((::FairTutorialDet4MisalignPar*)p);
   }
   static void destruct_FairTutorialDet4MisalignPar(void *p) {
      typedef ::FairTutorialDet4MisalignPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet4MisalignPar(TBuffer &buf, void *obj) {
      ((::FairTutorialDet4MisalignPar*)obj)->::FairTutorialDet4MisalignPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet4MisalignPar

//______________________________________________________________________________
void FairTutorialDet4::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairDetector::Streamer(R__b);
      fFairTutorialDet4PointCollection->Streamer(R__b);
      R__b >> fGeoHandler;
      R__b >> fMisalignPar;
      R__b >> fNrOfDetectors;
      fShiftX.Streamer(R__b);
      fShiftY.Streamer(R__b);
      fShiftZ.Streamer(R__b);
      fRotX.Streamer(R__b);
      fRotY.Streamer(R__b);
      fRotZ.Streamer(R__b);
      R__b >> fModifyGeometry;
      R__b >> fGlobalCoordinates;
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet4::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet4::IsA(), kTRUE);
      FairDetector::Streamer(R__b);
      fFairTutorialDet4PointCollection->Streamer(R__b);
      R__b << fGeoHandler;
      R__b << fMisalignPar;
      R__b << fNrOfDetectors;
      fShiftX.Streamer(R__b);
      fShiftY.Streamer(R__b);
      fShiftZ.Streamer(R__b);
      fRotX.Streamer(R__b);
      fRotY.Streamer(R__b);
      fRotZ.Streamer(R__b);
      R__b << fModifyGeometry;
      R__b << fGlobalCoordinates;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4(void *p) {
      return  p ? new(p) ::FairTutorialDet4 : new ::FairTutorialDet4;
   }
   static void *newArray_FairTutorialDet4(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4[nElements] : new ::FairTutorialDet4[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4(void *p) {
      delete ((::FairTutorialDet4*)p);
   }
   static void deleteArray_FairTutorialDet4(void *p) {
      delete [] ((::FairTutorialDet4*)p);
   }
   static void destruct_FairTutorialDet4(void *p) {
      typedef ::FairTutorialDet4 current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet4(TBuffer &buf, void *obj) {
      ((::FairTutorialDet4*)obj)->::FairTutorialDet4::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet4

//______________________________________________________________________________
void FairTutorialDet4Point::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4Point.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet4Point::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet4Point::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4Point(void *p) {
      return  p ? new(p) ::FairTutorialDet4Point : new ::FairTutorialDet4Point;
   }
   static void *newArray_FairTutorialDet4Point(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4Point[nElements] : new ::FairTutorialDet4Point[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4Point(void *p) {
      delete ((::FairTutorialDet4Point*)p);
   }
   static void deleteArray_FairTutorialDet4Point(void *p) {
      delete [] ((::FairTutorialDet4Point*)p);
   }
   static void destruct_FairTutorialDet4Point(void *p) {
      typedef ::FairTutorialDet4Point current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet4Point

//______________________________________________________________________________
void FairTutorialDet4Hit::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4Hit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet4Hit::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet4Hit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4Hit(void *p) {
      return  p ? new(p) ::FairTutorialDet4Hit : new ::FairTutorialDet4Hit;
   }
   static void *newArray_FairTutorialDet4Hit(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4Hit[nElements] : new ::FairTutorialDet4Hit[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4Hit(void *p) {
      delete ((::FairTutorialDet4Hit*)p);
   }
   static void deleteArray_FairTutorialDet4Hit(void *p) {
      delete [] ((::FairTutorialDet4Hit*)p);
   }
   static void destruct_FairTutorialDet4Hit(void *p) {
      typedef ::FairTutorialDet4Hit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet4Hit

//______________________________________________________________________________
void FairTutorialDet4HitProducerIdealMisalign::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4HitProducerIdealMisalign.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet4HitProducerIdealMisalign::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet4HitProducerIdealMisalign::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4HitProducerIdealMisalign(void *p) {
      return  p ? new(p) ::FairTutorialDet4HitProducerIdealMisalign : new ::FairTutorialDet4HitProducerIdealMisalign;
   }
   static void *newArray_FairTutorialDet4HitProducerIdealMisalign(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4HitProducerIdealMisalign[nElements] : new ::FairTutorialDet4HitProducerIdealMisalign[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4HitProducerIdealMisalign(void *p) {
      delete ((::FairTutorialDet4HitProducerIdealMisalign*)p);
   }
   static void deleteArray_FairTutorialDet4HitProducerIdealMisalign(void *p) {
      delete [] ((::FairTutorialDet4HitProducerIdealMisalign*)p);
   }
   static void destruct_FairTutorialDet4HitProducerIdealMisalign(void *p) {
      typedef ::FairTutorialDet4HitProducerIdealMisalign current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet4HitProducerIdealMisalign

//______________________________________________________________________________
void FairTutorialDet4GeoHandler::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4GeoHandler.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet4GeoHandler::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet4GeoHandler::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4GeoHandler(void *p) {
      return  p ? new(p) ::FairTutorialDet4GeoHandler : new ::FairTutorialDet4GeoHandler;
   }
   static void *newArray_FairTutorialDet4GeoHandler(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4GeoHandler[nElements] : new ::FairTutorialDet4GeoHandler[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4GeoHandler(void *p) {
      delete ((::FairTutorialDet4GeoHandler*)p);
   }
   static void deleteArray_FairTutorialDet4GeoHandler(void *p) {
      delete [] ((::FairTutorialDet4GeoHandler*)p);
   }
   static void destruct_FairTutorialDet4GeoHandler(void *p) {
      typedef ::FairTutorialDet4GeoHandler current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet4GeoHandler

//______________________________________________________________________________
void FairTutorialDet4StraightLineFitter::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4StraightLineFitter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet4StraightLineFitter::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet4StraightLineFitter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4StraightLineFitter(void *p) {
      return  p ? new(p) ::FairTutorialDet4StraightLineFitter : new ::FairTutorialDet4StraightLineFitter;
   }
   static void *newArray_FairTutorialDet4StraightLineFitter(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4StraightLineFitter[nElements] : new ::FairTutorialDet4StraightLineFitter[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4StraightLineFitter(void *p) {
      delete ((::FairTutorialDet4StraightLineFitter*)p);
   }
   static void deleteArray_FairTutorialDet4StraightLineFitter(void *p) {
      delete [] ((::FairTutorialDet4StraightLineFitter*)p);
   }
   static void destruct_FairTutorialDet4StraightLineFitter(void *p) {
      typedef ::FairTutorialDet4StraightLineFitter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet4StraightLineFitter

//______________________________________________________________________________
void FairTutorialDet4MilleWriter::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4MilleWriter.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTutorialDet4MilleWriter::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTutorialDet4MilleWriter::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4MilleWriter(void *p) {
      return  p ? new(p) ::FairTutorialDet4MilleWriter : new ::FairTutorialDet4MilleWriter;
   }
   static void *newArray_FairTutorialDet4MilleWriter(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4MilleWriter[nElements] : new ::FairTutorialDet4MilleWriter[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4MilleWriter(void *p) {
      delete ((::FairTutorialDet4MilleWriter*)p);
   }
   static void deleteArray_FairTutorialDet4MilleWriter(void *p) {
      delete [] ((::FairTutorialDet4MilleWriter*)p);
   }
   static void destruct_FairTutorialDet4MilleWriter(void *p) {
      typedef ::FairTutorialDet4MilleWriter current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTutorialDet4MilleWriter

//______________________________________________________________________________
void FairTutorialDet4PointDraw::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTutorialDet4PointDraw.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairTask::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, FairTutorialDet4PointDraw::IsA());
   } else {
      R__c = R__b.WriteVersion(FairTutorialDet4PointDraw::IsA(), kTRUE);
      FairTask::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTutorialDet4PointDraw(void *p) {
      return  p ? new(p) ::FairTutorialDet4PointDraw : new ::FairTutorialDet4PointDraw;
   }
   static void *newArray_FairTutorialDet4PointDraw(Long_t nElements, void *p) {
      return p ? new(p) ::FairTutorialDet4PointDraw[nElements] : new ::FairTutorialDet4PointDraw[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTutorialDet4PointDraw(void *p) {
      delete ((::FairTutorialDet4PointDraw*)p);
   }
   static void deleteArray_FairTutorialDet4PointDraw(void *p) {
      delete [] ((::FairTutorialDet4PointDraw*)p);
   }
   static void destruct_FairTutorialDet4PointDraw(void *p) {
      typedef ::FairTutorialDet4PointDraw current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairTutorialDet4PointDraw(TBuffer &buf, void *obj) {
      ((::FairTutorialDet4PointDraw*)obj)->::FairTutorialDet4PointDraw::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairTutorialDet4PointDraw

namespace {
  void TriggerDictionaryInitialization_G__Tutorial4Dict_Impl() {
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
"/Users/turany/development/FairRoot/eventdisplay",
"/Users/turany/development/FairRoot/examples/simulation/Tutorial4/src",
"/Users/turany/development/FairRoot/examples/simulation/Tutorial4/src/mc",
"/Users/turany/development/FairRoot/examples/simulation/Tutorial4/src/param",
"/Users/turany/development/FairRoot/examples/simulation/Tutorial4/src/data",
"/Users/turany/development/FairRoot/examples/simulation/Tutorial4/src/reco",
"/Users/turany/development/FairRoot/examples/simulation/Tutorial4/src/tools",
"/Users/turany/development/FairRoot/examples/common/mcstack",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/simulation/Tutorial4/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__Tutorial4Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Factory for all MyDet parameter containers)ATTRDUMP"))) FairTutorialDet4ContFact;
class FairTutorialDet4Geo;
class FairTutorialDet4GeoPar;
class FairTutorialDet4MisalignPar;
class FairTutorialDet4;
class FairTutorialDet4Point;
class FairTutorialDet4Hit;
class FairTutorialDet4HitProducerIdealMisalign;
class FairTutorialDet4GeoHandler;
class FairTutorialDet4StraightLineFitter;
class FairTutorialDet4MilleWriter;
class FairTutorialDet4PointDraw;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__Tutorial4Dict dictionary payload"

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
#ifndef FAIRTUTORIALDET4_H
#define FAIRTUTORIALDET4_H

#include "FairDetector.h"               // for FairDetector

#include "Rtypes.h"                     // for Int_t, Bool_t, Double32_t, etc
#include "TArrayD.h"                    // for TArrayD
#include "TLorentzVector.h"             // for TLorentzVector
#include "TClonesArray.h"
#include "TVector3.h"                   // for TVector3

#include <string>                       // for string

class FairTutorialDet4Point;
class FairTutorialDet4GeoHandler;
class FairTutorialDet4MisalignPar;
class FairVolume;
class TClonesArray;

class FairTutorialDet4: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    FairTutorialDet4(const char* Name, Bool_t Active);

    /**      default constructor    */
    FairTutorialDet4();

    /**       destructor     */
    virtual ~FairTutorialDet4();

    /**      Initialization of the detector is done here    */
    virtual void   Initialize();

    /**      Init parameter containers    */
    virtual void   InitParContainers();

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

    /**      Misalign the detector geometry        */
    void ModifyGeometry();

    void SetParContainers();

    /**      This method is an example of how to add your own point
     *       of type FairTutorialDet4Point to the clones array
    */
    FairTutorialDet4Point* AddHit(Int_t trackID, Int_t detID,
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

    void SetModifyGeometry(Bool_t val) { fModifyGeometry=val; }
    void SetGlobalCoordinates(Bool_t val) { fGlobalCoordinates=val; }

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

    TClonesArray*  fFairTutorialDet4PointCollection;

    FairTutorialDet4GeoHandler* fGeoHandler;

    FairTutorialDet4MisalignPar* fMisalignPar;

    Int_t fNrOfDetectors;
    TArrayD fShiftX;
    TArrayD fShiftY;
    TArrayD fShiftZ;
    TArrayD fRotX;
    TArrayD fRotY;
    TArrayD fRotZ;

    Bool_t fModifyGeometry;

    Bool_t fGlobalCoordinates;
    /** Method to construct the ascii geometry
     **
     **/
    void ConstructASCIIGeometry();

    Bool_t CheckIfSensitive(std::string name);

    void ModifyGeometryBySymlink();
    void ModifyGeometryByFullPath();


    FairTutorialDet4(const FairTutorialDet4&);
    FairTutorialDet4& operator=(const FairTutorialDet4&);

    ClassDef(FairTutorialDet4,2)
};

#endif //FAIRTUTORIALDET_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4GEO_H
#define FAIRTUTORIALDET4GEO_H

#include "FairGeoSet.h"                 // for FairGeoSet

#include "Rtypes.h"                     // for Int_t, etc
#include "TString.h"                    // for TString

class  FairTutorialDet4Geo : public FairGeoSet
{

  protected:
    char modName[20];  // name of module
    char eleName[20];  // substring for elements in module
  public:
    FairTutorialDet4Geo();
    ~FairTutorialDet4Geo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(FairTutorialDet4Geo,1)
};

inline Int_t FairTutorialDet4Geo::getModNumInMod(const TString& name)
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
#ifndef FAIRTUTORIALDET4CONTFACT_H
#define FAIRTUTORIALDET4CONTFACT_H

#include "FairContFact.h"               // for FairContFact, etc

#include "Rtypes.h"                     // for ClassDef

class FairParSet;

class FairTutorialDet4ContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    FairTutorialDet4ContFact();
    ~FairTutorialDet4ContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( FairTutorialDet4ContFact,0) // Factory for all MyDet parameter containers
};

#endif  /* !FAIRTUTORIALDETCONTFACT_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4GEOPAR_H
#define FAIRTUTORIALDET4GEOPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef 

class TObjArray;
class FairParamList;

class FairTutorialDet4GeoPar       : public FairParGenericSet
{
  public:

    FairTutorialDet4GeoPar(const char* name="FairTutorialDet4GeoPar",
                           const char* title="FairTutorialDet4 Geometry Parameters",
                           const char* context="TestDefaultContext");
    ~FairTutorialDet4GeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}
    Bool_t IsGlobalCoordinateSystem() {return fGlobalCoordinates;}
    void SetGlobalCoordinates(Bool_t globalCoordinates) {
      fGlobalCoordinates = globalCoordinates;
    }

  private:
    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    Bool_t          fGlobalCoordinates;

    FairTutorialDet4GeoPar(const FairTutorialDet4GeoPar&);
    FairTutorialDet4GeoPar& operator=(const FairTutorialDet4GeoPar&);

    ClassDef(FairTutorialDet4GeoPar,2)
};

#endif /* FAIRTUTORIALDETGEOPAR_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4MISSALLIGNPAR_H
#define FAIRTUTORIALDET4MISSALLIGNPAR_H

#include "FairParGenericSet.h"          // for FairParGenericSet

#include "Rtypes.h"                     // for ClassDef

#include "TArrayD.h"                    // for TArrayD

class FairParamList;

class FairTutorialDet4MisalignPar : public FairParGenericSet
{
  public:

    FairTutorialDet4MisalignPar(const char* name="FairTutorialDet4MissallignPar",
                                const char* title="Missalignment parameter for FairTutorialDet4HitProducerIdealMissallign Parameters",
                                const char* context="TestDefaultContext");
    ~FairTutorialDet4MisalignPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);

    TArrayD GetShiftX() {return fShiftX;}
    TArrayD GetShiftY() {return fShiftY;}
    TArrayD GetShiftZ() {return fShiftZ;}
    TArrayD GetRotX() {return fRotX;}
    TArrayD GetRotY() {return fRotY;}
    TArrayD GetRotZ() {return fRotZ;}
    Int_t GetNrOfDetectors() {return fNrOfDetectors;}

  private:

    TArrayD fShiftX; // Array to hold the misalignment in x-direction
    TArrayD fShiftY; // Array to hold the misalignment in y-direction
    TArrayD fShiftZ; // Array to hold the misalignment in z-direction
    TArrayD fRotX; // Array to hold the rotation in x-direction
    TArrayD fRotY; // Array to hold the rotation in y-direction
    TArrayD fRotZ; // Array to hold the rotation in z-direction
    Int_t fNrOfDetectors; // Total number of detectors

    FairTutorialDet4MisalignPar(const FairTutorialDet4MisalignPar&);
    FairTutorialDet4MisalignPar& operator=(const FairTutorialDet4MisalignPar&);

    ClassDef(FairTutorialDet4MisalignPar,1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4POINT_H
#define FAIRTUTORIALDET4POINT_H 1

#include "FairMCPoint.h"                // for FairMCPoint

#include "Rtypes.h"                     // for Double_t, etc
#include "TVector3.h"                   // for TVector3

class FairTutorialDet4Point : public FairMCPoint
{

  public:

    /** Default constructor **/
    FairTutorialDet4Point();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    FairTutorialDet4Point(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                          Double_t tof, Double_t length, Double_t eLoss);


    /** Copy constructor **/
    //    FairTutorialDet4Point(const FairTutorialDet4Point& point) { *this = point; };


    /** Destructor **/
    virtual ~FairTutorialDet4Point();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;


    ClassDef(FairTutorialDet4Point,1)

};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDERT4HIT_H
#define FAIRTUTORIALDET4HIT_H 1

#include "FairHit.h"                    // for FairHit

#include "Rtypes.h"                     // for FairTutorialDet4Hit::Class, etc

class TVector3;

class FairTutorialDet4Hit : public FairHit
{

  public:

    /** Default constructor **/
    FairTutorialDet4Hit();
    FairTutorialDet4Hit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);

    /** Destructor **/
    virtual ~FairTutorialDet4Hit();

  private:

    FairTutorialDet4Hit(const FairTutorialDet4Hit&);
    FairTutorialDet4Hit operator=(const FairTutorialDet4Hit&);

    ClassDef(FairTutorialDet4Hit,1);

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
// -----    FairTutorialDet4HitProducerIdealMissallign header file      -----
// -----                  Created 11.02.13 by F. Uhlig                 -----
// -------------------------------------------------------------------------


/** FairTutorialDet4HitProducerIdealMissallign.h
 *@author Florian Uhlig <f.uhlig@gsi.de>
 **
 ** The ideal hit producer produces hits of type CbmTutorialDetHit
 ** by copying the MCPoint position. At the same time it will shift
 ** the hit position by a given offset in x- and y-direction. This
 ** shift should mimic a missalignment of the detector due to inaccurate
 ** measurement of the detector positions.
 ** The position error is set to 1 mm.
 **/


#ifndef FAIRTUTORIALDET4HITPRODUCERIDEALMISSALLIGN_H
#define FAIRTUTORIALDET4HITPRODUCERIDEALMISSALLIGN_H 1

#include "FairTask.h"                   // for InitStatus, FairTask

#include "Rtypes.h"                     // for Bool_t, Double_t, etc
#include "TArrayD.h"                    // for TArrayD

class FairTutorialDet4MisalignPar;
class FairTutorialDet4GeoPar;
class FairTutorialDet4GeoHandler;
class TClonesArray;

class FairTutorialDet4HitProducerIdealMisalign : public FairTask
{

  public:

    /** Default constructor **/
    FairTutorialDet4HitProducerIdealMisalign();


    /** Destructor **/
    ~FairTutorialDet4HitProducerIdealMisalign();


    /** Virtual method Init **/
    virtual InitStatus Init();

    /** Virtual method ReInit **/
    virtual InitStatus ReInit();

    virtual void SetParContainers();


    /** Virtual method Exec **/
    virtual void Exec(Option_t* opt);

    void DoMisalignment(Bool_t val) {fDoMisalignment=val;}

  private:

    /** Input array of CbmTofPoints **/
    TClonesArray* fPointArray; //!

    /** Output array of CbmTofHits **/
    TClonesArray* fHitArray;  //!

    TArrayD fShiftX;
    TArrayD fShiftY;
    TArrayD fShiftZ;
    TArrayD fRotX;
    TArrayD fRotY;
    TArrayD fRotZ;

    FairTutorialDet4MisalignPar* fDigiPar;
    FairTutorialDet4GeoHandler* fGeoHandler;
    FairTutorialDet4GeoPar* fGeoPar;

    Bool_t fDoMisalignment;
  private:

    Double_t GetHitErr(Double_t sigma);

    FairTutorialDet4HitProducerIdealMisalign(const FairTutorialDet4HitProducerIdealMisalign&);
    FairTutorialDet4HitProducerIdealMisalign& operator=(const FairTutorialDet4HitProducerIdealMisalign&);

    ClassDef(FairTutorialDet4HitProducerIdealMisalign,1);

};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4STRAIGHTLINEFITTER_H
#define FAIRTUTORIALDET4STRAIGHTLINEFITTER_H

#include "FairTask.h"                   // for InitStatus, FairTask

#include "Rtypes.h"                     // for ClassDef

class TClonesArray;

class FairTutorialDet4StraightLineFitter : public FairTask
{
  public:

    /** Default constructor **/
    FairTutorialDet4StraightLineFitter();

    /** Constructor with parameters (Optional) **/
    //  FairTutorialDet4StraightLineFitter(Int_t verbose);


    /** Destructor **/
    ~FairTutorialDet4StraightLineFitter();


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

    void SetVersion(Int_t val) {fVersion = val;}

  private:

    /** Input array from previous already existing data level **/
    TClonesArray* fHits;

    /** Output array to  new data level**/
    TClonesArray* fTracks;

    Int_t fVersion;

    Bool_t IsGoodEvent();

    FairTutorialDet4StraightLineFitter(const FairTutorialDet4StraightLineFitter&);
    FairTutorialDet4StraightLineFitter operator=(const FairTutorialDet4StraightLineFitter&);

    ClassDef(FairTutorialDet4StraightLineFitter,1);
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTUTORIALDET4MILLEWRITER_H
#define FAIRTUTORIALDET4MILLEWRITER_H

#include "FairTask.h"                   // for InitStatus, FairTask

#include "TString.h"
#include "Rtypes.h"                     // for Option_t, Bool_t, etc

class Mille;
class TClonesArray;

class FairTutorialDet4MilleWriter : public FairTask
{
  public:

    /** Default constructor **/
    FairTutorialDet4MilleWriter();

    /** Constructor with parameters (Optional) **/
    //  FairTutorialDet4MilleWriter(Int_t verbose);


    /** Destructor **/
    ~FairTutorialDet4MilleWriter();


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

    void SetWriteAscii(Bool_t val) {fWriteAscii = val;}

    void SetVersion(Int_t val) {fVersion = val;}

    void SetFileName(TString val) {fFileName = val;}

  private:

    void ExecVersion1(Option_t* opt);
    void StraightLineShiftX();
    void StraightLineShiftXY();

    Bool_t IsGoodEvent();

    /** Input array from previous already existing data level **/
    TClonesArray* fTracks;

    /** Input array from previous already existing data level **/
    TClonesArray* fHits;

    Mille* fMille;

    Bool_t fWriteAscii;

    Int_t fVersion;

    TString fFileName;
    
    /** Output array to  new data level**/
    //  TClonesArray* <OutputDataLevel>;

    FairTutorialDet4MilleWriter(const FairTutorialDet4MilleWriter&);
    FairTutorialDet4MilleWriter operator=(const FairTutorialDet4MilleWriter&);

    ClassDef(FairTutorialDet4MilleWriter,1);
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
// -----                 FairTutorialDet4GeoHandler header file                  -----
// -----                 Created 20/11/12  by F. Uhlig                 -----
// -------------------------------------------------------------------------


/** FairTutorialDet4GeoHandler.h
 ** Helper class to extract information from the GeoManager which is
 ** needed in many other TOF classes. This helper class should be a
 ** single place to hold all these functions.
 ** @author F. Uhlig <f.uhlig@gsi.de>
 **/

#ifndef FAIRTUTORIALDET4GEOHANDLER_H
#define FAIRTUTORIALDET4GEOHANDLER_H 1

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Int_t, Double_t, Bool_t, etc
#include "TString.h"                    // for TString

class TGeoBBox;
class TGeoVolume;
class TGeoHMatrix;

class FairTutorialDet4GeoHandler : public TObject
{
  public:

    /** Constructor **/
    FairTutorialDet4GeoHandler();


    /** Destructor **/
    ~FairTutorialDet4GeoHandler() {};

    Int_t GetUniqueDetectorId();
    Int_t GetUniqueDetectorId(TString volName);

//  Int_t GetDetectorId(Int_t uniqueId);

    Int_t Init(Bool_t isSimulation=kFALSE);

    void FillDetectorInfoArray(Int_t uniqueId);
    void NavigateTo(TString volName);

    // Implement Interface functions to the TGeoManager to be
    // the same as for the VMC
    Int_t CurrentVolOffID(Int_t off, Int_t& copy) const;
    Int_t CurrentVolID(Int_t& copy) const;
    Int_t VolId(const Text_t* name) const;
    Int_t VolIdGeo(const char* name) const;
    const char* CurrentVolName() const;
    const char* CurrentVolOffName(Int_t off) const;

    void LocalToGlobal(Double_t* local, Double_t* global, Int_t detID);

//  Int_t CheckGeometryVersion();

  private:

    Bool_t fIsSimulation; //!

    Int_t fLastUsedDetectorID;  //!

    UInt_t fGeoPathHash;        //!
    TGeoVolume* fCurrentVolume; //!
    TGeoBBox* fVolumeShape;     //!
    Double_t fGlobal[3];        //! Global centre of volume
    TGeoHMatrix* fGlobalMatrix; //!


    TString ConstructFullPathFromDetID(Int_t detID);

    FairTutorialDet4GeoHandler(const FairTutorialDet4GeoHandler&);
    FairTutorialDet4GeoHandler operator=(const FairTutorialDet4GeoHandler&);

    ClassDef(FairTutorialDet4GeoHandler,1)

};


#endif //FAIRTUTORIALDETGEOHANDLER_H

// -------------------------------------------------------------------------
// -----        FairTutorialDet4PointDraw header file                  -----
// -----            Created 02.03.16  by F. Uhlig                      -----
// -------------------------------------------------------------------------


/** FairTutorialDet4PointDraw
 * @author F. Uhlig
 * @since 02.03.16
 *   Task to display FairTutorialDet4Points stored in local
 *   or global coordinates.
 **
 **/

#ifndef FAIRTUTORIALDET4POINTDRAW_H
#define FAIRTUTORIALDET4POINTDRAW_H

#include "FairTask.h"                   // for FairTask, InitStatus
#include "Rtypes.h"                     // for Bool_t, Int_t, etc

class FairTutorialDet4GeoPar;
class FairTutorialDet4DigiPar;
class FairEventManager;
class FairTutorialDet4GeoHandler;

class TClonesArray;
class TEvePointSet;

class FairTutorialDet4PointDraw : public FairTask {

 public:

  /** Default constructor **/
  FairTutorialDet4PointDraw();

  /** Standard constructor
  *@param name        Name of task
  *@param iVerbose    Verbosity level
  **/
  FairTutorialDet4PointDraw(const char* name, Color_t color ,
			    Style_t mstyle);

  /** Destructor **/
  virtual ~FairTutorialDet4PointDraw();

   /** Executed task **/
  virtual void Exec(Option_t* option);
  void Reset();

  virtual void SetParContainers() ;
  virtual InitStatus Init();
  /** Action after each event**/

  virtual void Finish() ;

private:

  TClonesArray *fPointList; //!
  FairTutorialDet4GeoPar *fGeoPar; //!
  FairEventManager *fEventManager;   //!
  TEvePointSet* fq;    //!
  Color_t fColor; //!
  Style_t fStyle; //!
  Bool_t fGlobalCoordinates; //!
  FairTutorialDet4GeoHandler* fGeoHandler; //!

  FairTutorialDet4PointDraw(const FairTutorialDet4PointDraw&);
  FairTutorialDet4PointDraw& operator=(const FairTutorialDet4PointDraw&);

  ClassDef(FairTutorialDet4PointDraw,1);

};


#endif



#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairTutorialDet4", payloadCode, "@",
"FairTutorialDet4ContFact", payloadCode, "@",
"FairTutorialDet4Geo", payloadCode, "@",
"FairTutorialDet4GeoHandler", payloadCode, "@",
"FairTutorialDet4GeoPar", payloadCode, "@",
"FairTutorialDet4Hit", payloadCode, "@",
"FairTutorialDet4HitProducerIdealMisalign", payloadCode, "@",
"FairTutorialDet4MilleWriter", payloadCode, "@",
"FairTutorialDet4MisalignPar", payloadCode, "@",
"FairTutorialDet4Point", payloadCode, "@",
"FairTutorialDet4PointDraw", payloadCode, "@",
"FairTutorialDet4StraightLineFitter", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__Tutorial4Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__Tutorial4Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__Tutorial4Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__Tutorial4Dict() {
  TriggerDictionaryInitialization_G__Tutorial4Dict_Impl();
}

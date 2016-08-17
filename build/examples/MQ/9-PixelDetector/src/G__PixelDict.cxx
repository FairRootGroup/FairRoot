// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIMQdI9mIPixelDetectordIsrcdIG__PixelDict

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
#include "Pixel.h"
#include "PixelContFact.h"
#include "PixelDigitize.h"
#include "PixelDigiPar.h"
#include "PixelDigiSource.h"
#include "PixelDigiBinSource.h"
#include "PixelDigiWriteToFile.h"
#include "PixelDigiWriteToBinFile.h"
#include "PixelFindHits.h"
#include "PixelFindTracks.h"
#include "PixelFitTracks.h"
#include "PixelGeo.h"
#include "PixelGeoPar.h"
#include "PixelEventHeader.h"
#include "PixelPoint.h"
#include "PixelDigi.h"
#include "PixelHit.h"
#include "PixelTrack.h"
#include "PixelPayload.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Pixel(void *p = 0);
   static void *newArray_Pixel(Long_t size, void *p);
   static void delete_Pixel(void *p);
   static void deleteArray_Pixel(void *p);
   static void destruct_Pixel(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Pixel*)
   {
      ::Pixel *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Pixel >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Pixel", ::Pixel::Class_Version(), "invalid", 25,
                  typeid(::Pixel), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Pixel::Dictionary, isa_proxy, 4,
                  sizeof(::Pixel) );
      instance.SetNew(&new_Pixel);
      instance.SetNewArray(&newArray_Pixel);
      instance.SetDelete(&delete_Pixel);
      instance.SetDeleteArray(&deleteArray_Pixel);
      instance.SetDestructor(&destruct_Pixel);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Pixel*)
   {
      return GenerateInitInstanceLocal((::Pixel*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::Pixel*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelContFact(void *p = 0);
   static void *newArray_PixelContFact(Long_t size, void *p);
   static void delete_PixelContFact(void *p);
   static void deleteArray_PixelContFact(void *p);
   static void destruct_PixelContFact(void *p);
   static void streamer_PixelContFact(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelContFact*)
   {
      ::PixelContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelContFact", ::PixelContFact::Class_Version(), "invalid", 131,
                  typeid(::PixelContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelContFact::Dictionary, isa_proxy, 16,
                  sizeof(::PixelContFact) );
      instance.SetNew(&new_PixelContFact);
      instance.SetNewArray(&newArray_PixelContFact);
      instance.SetDelete(&delete_PixelContFact);
      instance.SetDeleteArray(&deleteArray_PixelContFact);
      instance.SetDestructor(&destruct_PixelContFact);
      instance.SetStreamerFunc(&streamer_PixelContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelContFact*)
   {
      return GenerateInitInstanceLocal((::PixelContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelDigitize(void *p = 0);
   static void *newArray_PixelDigitize(Long_t size, void *p);
   static void delete_PixelDigitize(void *p);
   static void deleteArray_PixelDigitize(void *p);
   static void destruct_PixelDigitize(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelDigitize*)
   {
      ::PixelDigitize *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelDigitize >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelDigitize", ::PixelDigitize::Class_Version(), "invalid", 171,
                  typeid(::PixelDigitize), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelDigitize::Dictionary, isa_proxy, 4,
                  sizeof(::PixelDigitize) );
      instance.SetNew(&new_PixelDigitize);
      instance.SetNewArray(&newArray_PixelDigitize);
      instance.SetDelete(&delete_PixelDigitize);
      instance.SetDeleteArray(&deleteArray_PixelDigitize);
      instance.SetDestructor(&destruct_PixelDigitize);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelDigitize*)
   {
      return GenerateInitInstanceLocal((::PixelDigitize*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelDigitize*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelDigiPar(void *p = 0);
   static void *newArray_PixelDigiPar(Long_t size, void *p);
   static void delete_PixelDigiPar(void *p);
   static void deleteArray_PixelDigiPar(void *p);
   static void destruct_PixelDigiPar(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelDigiPar*)
   {
      ::PixelDigiPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelDigiPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelDigiPar", ::PixelDigiPar::Class_Version(), "invalid", 273,
                  typeid(::PixelDigiPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelDigiPar::Dictionary, isa_proxy, 4,
                  sizeof(::PixelDigiPar) );
      instance.SetNew(&new_PixelDigiPar);
      instance.SetNewArray(&newArray_PixelDigiPar);
      instance.SetDelete(&delete_PixelDigiPar);
      instance.SetDeleteArray(&deleteArray_PixelDigiPar);
      instance.SetDestructor(&destruct_PixelDigiPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelDigiPar*)
   {
      return GenerateInitInstanceLocal((::PixelDigiPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelDigiPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelDigiSource(void *p = 0);
   static void *newArray_PixelDigiSource(Long_t size, void *p);
   static void delete_PixelDigiSource(void *p);
   static void deleteArray_PixelDigiSource(void *p);
   static void destruct_PixelDigiSource(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelDigiSource*)
   {
      ::PixelDigiSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelDigiSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelDigiSource", ::PixelDigiSource::Class_Version(), "invalid", 368,
                  typeid(::PixelDigiSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelDigiSource::Dictionary, isa_proxy, 4,
                  sizeof(::PixelDigiSource) );
      instance.SetNew(&new_PixelDigiSource);
      instance.SetNewArray(&newArray_PixelDigiSource);
      instance.SetDelete(&delete_PixelDigiSource);
      instance.SetDeleteArray(&deleteArray_PixelDigiSource);
      instance.SetDestructor(&destruct_PixelDigiSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelDigiSource*)
   {
      return GenerateInitInstanceLocal((::PixelDigiSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelDigiSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelDigiBinSource(void *p = 0);
   static void *newArray_PixelDigiBinSource(Long_t size, void *p);
   static void delete_PixelDigiBinSource(void *p);
   static void deleteArray_PixelDigiBinSource(void *p);
   static void destruct_PixelDigiBinSource(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelDigiBinSource*)
   {
      ::PixelDigiBinSource *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelDigiBinSource >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelDigiBinSource", ::PixelDigiBinSource::Class_Version(), "invalid", 454,
                  typeid(::PixelDigiBinSource), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelDigiBinSource::Dictionary, isa_proxy, 4,
                  sizeof(::PixelDigiBinSource) );
      instance.SetNew(&new_PixelDigiBinSource);
      instance.SetNewArray(&newArray_PixelDigiBinSource);
      instance.SetDelete(&delete_PixelDigiBinSource);
      instance.SetDeleteArray(&deleteArray_PixelDigiBinSource);
      instance.SetDestructor(&destruct_PixelDigiBinSource);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelDigiBinSource*)
   {
      return GenerateInitInstanceLocal((::PixelDigiBinSource*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelDigiBinSource*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelDigiWriteToFile(void *p = 0);
   static void *newArray_PixelDigiWriteToFile(Long_t size, void *p);
   static void delete_PixelDigiWriteToFile(void *p);
   static void deleteArray_PixelDigiWriteToFile(void *p);
   static void destruct_PixelDigiWriteToFile(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelDigiWriteToFile*)
   {
      ::PixelDigiWriteToFile *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelDigiWriteToFile >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelDigiWriteToFile", ::PixelDigiWriteToFile::Class_Version(), "invalid", 536,
                  typeid(::PixelDigiWriteToFile), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelDigiWriteToFile::Dictionary, isa_proxy, 4,
                  sizeof(::PixelDigiWriteToFile) );
      instance.SetNew(&new_PixelDigiWriteToFile);
      instance.SetNewArray(&newArray_PixelDigiWriteToFile);
      instance.SetDelete(&delete_PixelDigiWriteToFile);
      instance.SetDeleteArray(&deleteArray_PixelDigiWriteToFile);
      instance.SetDestructor(&destruct_PixelDigiWriteToFile);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelDigiWriteToFile*)
   {
      return GenerateInitInstanceLocal((::PixelDigiWriteToFile*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelDigiWriteToFile*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelDigiWriteToBinFile(void *p = 0);
   static void *newArray_PixelDigiWriteToBinFile(Long_t size, void *p);
   static void delete_PixelDigiWriteToBinFile(void *p);
   static void deleteArray_PixelDigiWriteToBinFile(void *p);
   static void destruct_PixelDigiWriteToBinFile(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelDigiWriteToBinFile*)
   {
      ::PixelDigiWriteToBinFile *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelDigiWriteToBinFile >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelDigiWriteToBinFile", ::PixelDigiWriteToBinFile::Class_Version(), "invalid", 634,
                  typeid(::PixelDigiWriteToBinFile), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelDigiWriteToBinFile::Dictionary, isa_proxy, 4,
                  sizeof(::PixelDigiWriteToBinFile) );
      instance.SetNew(&new_PixelDigiWriteToBinFile);
      instance.SetNewArray(&newArray_PixelDigiWriteToBinFile);
      instance.SetDelete(&delete_PixelDigiWriteToBinFile);
      instance.SetDeleteArray(&deleteArray_PixelDigiWriteToBinFile);
      instance.SetDestructor(&destruct_PixelDigiWriteToBinFile);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelDigiWriteToBinFile*)
   {
      return GenerateInitInstanceLocal((::PixelDigiWriteToBinFile*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelDigiWriteToBinFile*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelFindHits(void *p = 0);
   static void *newArray_PixelFindHits(Long_t size, void *p);
   static void delete_PixelFindHits(void *p);
   static void deleteArray_PixelFindHits(void *p);
   static void destruct_PixelFindHits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelFindHits*)
   {
      ::PixelFindHits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelFindHits >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelFindHits", ::PixelFindHits::Class_Version(), "invalid", 735,
                  typeid(::PixelFindHits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelFindHits::Dictionary, isa_proxy, 4,
                  sizeof(::PixelFindHits) );
      instance.SetNew(&new_PixelFindHits);
      instance.SetNewArray(&newArray_PixelFindHits);
      instance.SetDelete(&delete_PixelFindHits);
      instance.SetDeleteArray(&deleteArray_PixelFindHits);
      instance.SetDestructor(&destruct_PixelFindHits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelFindHits*)
   {
      return GenerateInitInstanceLocal((::PixelFindHits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelFindHits*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelFindTracks(void *p = 0);
   static void *newArray_PixelFindTracks(Long_t size, void *p);
   static void delete_PixelFindTracks(void *p);
   static void deleteArray_PixelFindTracks(void *p);
   static void destruct_PixelFindTracks(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelFindTracks*)
   {
      ::PixelFindTracks *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelFindTracks >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelFindTracks", ::PixelFindTracks::Class_Version(), "invalid", 849,
                  typeid(::PixelFindTracks), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelFindTracks::Dictionary, isa_proxy, 4,
                  sizeof(::PixelFindTracks) );
      instance.SetNew(&new_PixelFindTracks);
      instance.SetNewArray(&newArray_PixelFindTracks);
      instance.SetDelete(&delete_PixelFindTracks);
      instance.SetDeleteArray(&deleteArray_PixelFindTracks);
      instance.SetDestructor(&destruct_PixelFindTracks);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelFindTracks*)
   {
      return GenerateInitInstanceLocal((::PixelFindTracks*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelFindTracks*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelFitTracks(void *p = 0);
   static void *newArray_PixelFitTracks(Long_t size, void *p);
   static void delete_PixelFitTracks(void *p);
   static void deleteArray_PixelFitTracks(void *p);
   static void destruct_PixelFitTracks(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelFitTracks*)
   {
      ::PixelFitTracks *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelFitTracks >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelFitTracks", ::PixelFitTracks::Class_Version(), "invalid", 952,
                  typeid(::PixelFitTracks), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelFitTracks::Dictionary, isa_proxy, 4,
                  sizeof(::PixelFitTracks) );
      instance.SetNew(&new_PixelFitTracks);
      instance.SetNewArray(&newArray_PixelFitTracks);
      instance.SetDelete(&delete_PixelFitTracks);
      instance.SetDeleteArray(&deleteArray_PixelFitTracks);
      instance.SetDestructor(&destruct_PixelFitTracks);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelFitTracks*)
   {
      return GenerateInitInstanceLocal((::PixelFitTracks*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelFitTracks*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelGeo(void *p = 0);
   static void *newArray_PixelGeo(Long_t size, void *p);
   static void delete_PixelGeo(void *p);
   static void deleteArray_PixelGeo(void *p);
   static void destruct_PixelGeo(void *p);
   static void streamer_PixelGeo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelGeo*)
   {
      ::PixelGeo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelGeo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelGeo", ::PixelGeo::Class_Version(), "invalid", 1048,
                  typeid(::PixelGeo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelGeo::Dictionary, isa_proxy, 16,
                  sizeof(::PixelGeo) );
      instance.SetNew(&new_PixelGeo);
      instance.SetNewArray(&newArray_PixelGeo);
      instance.SetDelete(&delete_PixelGeo);
      instance.SetDeleteArray(&deleteArray_PixelGeo);
      instance.SetDestructor(&destruct_PixelGeo);
      instance.SetStreamerFunc(&streamer_PixelGeo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelGeo*)
   {
      return GenerateInitInstanceLocal((::PixelGeo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelGeo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelGeoPar(void *p = 0);
   static void *newArray_PixelGeoPar(Long_t size, void *p);
   static void delete_PixelGeoPar(void *p);
   static void deleteArray_PixelGeoPar(void *p);
   static void destruct_PixelGeoPar(void *p);
   static void streamer_PixelGeoPar(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelGeoPar*)
   {
      ::PixelGeoPar *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelGeoPar >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelGeoPar", ::PixelGeoPar::Class_Version(), "invalid", 1090,
                  typeid(::PixelGeoPar), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelGeoPar::Dictionary, isa_proxy, 16,
                  sizeof(::PixelGeoPar) );
      instance.SetNew(&new_PixelGeoPar);
      instance.SetNewArray(&newArray_PixelGeoPar);
      instance.SetDelete(&delete_PixelGeoPar);
      instance.SetDeleteArray(&deleteArray_PixelGeoPar);
      instance.SetDestructor(&destruct_PixelGeoPar);
      instance.SetStreamerFunc(&streamer_PixelGeoPar);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelGeoPar*)
   {
      return GenerateInitInstanceLocal((::PixelGeoPar*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelGeoPar*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelEventHeader(void *p = 0);
   static void *newArray_PixelEventHeader(Long_t size, void *p);
   static void delete_PixelEventHeader(void *p);
   static void deleteArray_PixelEventHeader(void *p);
   static void destruct_PixelEventHeader(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelEventHeader*)
   {
      ::PixelEventHeader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelEventHeader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelEventHeader", ::PixelEventHeader::Class_Version(), "invalid", 1143,
                  typeid(::PixelEventHeader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelEventHeader::Dictionary, isa_proxy, 4,
                  sizeof(::PixelEventHeader) );
      instance.SetNew(&new_PixelEventHeader);
      instance.SetNewArray(&newArray_PixelEventHeader);
      instance.SetDelete(&delete_PixelEventHeader);
      instance.SetDeleteArray(&deleteArray_PixelEventHeader);
      instance.SetDestructor(&destruct_PixelEventHeader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelEventHeader*)
   {
      return GenerateInitInstanceLocal((::PixelEventHeader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelEventHeader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelPoint(void *p = 0);
   static void *newArray_PixelPoint(Long_t size, void *p);
   static void delete_PixelPoint(void *p);
   static void deleteArray_PixelPoint(void *p);
   static void destruct_PixelPoint(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelPoint*)
   {
      ::PixelPoint *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelPoint >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelPoint", ::PixelPoint::Class_Version(), "PixelPoint.h", 17,
                  typeid(::PixelPoint), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelPoint::Dictionary, isa_proxy, 4,
                  sizeof(::PixelPoint) );
      instance.SetNew(&new_PixelPoint);
      instance.SetNewArray(&newArray_PixelPoint);
      instance.SetDelete(&delete_PixelPoint);
      instance.SetDeleteArray(&deleteArray_PixelPoint);
      instance.SetDestructor(&destruct_PixelPoint);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelPoint*)
   {
      return GenerateInitInstanceLocal((::PixelPoint*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelPoint*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelDigi(void *p = 0);
   static void *newArray_PixelDigi(Long_t size, void *p);
   static void delete_PixelDigi(void *p);
   static void deleteArray_PixelDigi(void *p);
   static void destruct_PixelDigi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelDigi*)
   {
      ::PixelDigi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelDigi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelDigi", ::PixelDigi::Class_Version(), "PixelDigi.h", 22,
                  typeid(::PixelDigi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelDigi::Dictionary, isa_proxy, 4,
                  sizeof(::PixelDigi) );
      instance.SetNew(&new_PixelDigi);
      instance.SetNewArray(&newArray_PixelDigi);
      instance.SetDelete(&delete_PixelDigi);
      instance.SetDeleteArray(&deleteArray_PixelDigi);
      instance.SetDestructor(&destruct_PixelDigi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelDigi*)
   {
      return GenerateInitInstanceLocal((::PixelDigi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelDigi*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelHit(void *p = 0);
   static void *newArray_PixelHit(Long_t size, void *p);
   static void delete_PixelHit(void *p);
   static void deleteArray_PixelHit(void *p);
   static void destruct_PixelHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelHit*)
   {
      ::PixelHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelHit", ::PixelHit::Class_Version(), "PixelHit.h", 29,
                  typeid(::PixelHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelHit::Dictionary, isa_proxy, 4,
                  sizeof(::PixelHit) );
      instance.SetNew(&new_PixelHit);
      instance.SetNewArray(&newArray_PixelHit);
      instance.SetDelete(&delete_PixelHit);
      instance.SetDeleteArray(&deleteArray_PixelHit);
      instance.SetDestructor(&destruct_PixelHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelHit*)
   {
      return GenerateInitInstanceLocal((::PixelHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_PixelTrack(void *p = 0);
   static void *newArray_PixelTrack(Long_t size, void *p);
   static void delete_PixelTrack(void *p);
   static void deleteArray_PixelTrack(void *p);
   static void destruct_PixelTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::PixelTrack*)
   {
      ::PixelTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::PixelTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("PixelTrack", ::PixelTrack::Class_Version(), "PixelTrack.h", 27,
                  typeid(::PixelTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::PixelTrack::Dictionary, isa_proxy, 4,
                  sizeof(::PixelTrack) );
      instance.SetNew(&new_PixelTrack);
      instance.SetNewArray(&newArray_PixelTrack);
      instance.SetDelete(&delete_PixelTrack);
      instance.SetDeleteArray(&deleteArray_PixelTrack);
      instance.SetDestructor(&destruct_PixelTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::PixelTrack*)
   {
      return GenerateInitInstanceLocal((::PixelTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::PixelTrack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Pixel::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Pixel::Class_Name()
{
   return "Pixel";
}

//______________________________________________________________________________
const char *Pixel::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Pixel*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Pixel::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Pixel*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Pixel::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Pixel*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Pixel::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Pixel*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelContFact::Class_Name()
{
   return "PixelContFact";
}

//______________________________________________________________________________
const char *PixelContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelDigitize::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelDigitize::Class_Name()
{
   return "PixelDigitize";
}

//______________________________________________________________________________
const char *PixelDigitize::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigitize*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelDigitize::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigitize*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelDigitize::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigitize*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelDigitize::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigitize*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelDigiPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelDigiPar::Class_Name()
{
   return "PixelDigiPar";
}

//______________________________________________________________________________
const char *PixelDigiPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelDigiPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelDigiPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelDigiPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelDigiSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelDigiSource::Class_Name()
{
   return "PixelDigiSource";
}

//______________________________________________________________________________
const char *PixelDigiSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelDigiSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelDigiSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelDigiSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelDigiBinSource::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelDigiBinSource::Class_Name()
{
   return "PixelDigiBinSource";
}

//______________________________________________________________________________
const char *PixelDigiBinSource::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiBinSource*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelDigiBinSource::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiBinSource*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelDigiBinSource::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiBinSource*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelDigiBinSource::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiBinSource*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelDigiWriteToFile::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelDigiWriteToFile::Class_Name()
{
   return "PixelDigiWriteToFile";
}

//______________________________________________________________________________
const char *PixelDigiWriteToFile::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiWriteToFile*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelDigiWriteToFile::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiWriteToFile*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelDigiWriteToFile::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiWriteToFile*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelDigiWriteToFile::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiWriteToFile*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelDigiWriteToBinFile::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelDigiWriteToBinFile::Class_Name()
{
   return "PixelDigiWriteToBinFile";
}

//______________________________________________________________________________
const char *PixelDigiWriteToBinFile::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiWriteToBinFile*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelDigiWriteToBinFile::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiWriteToBinFile*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelDigiWriteToBinFile::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiWriteToBinFile*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelDigiWriteToBinFile::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigiWriteToBinFile*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelFindHits::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelFindHits::Class_Name()
{
   return "PixelFindHits";
}

//______________________________________________________________________________
const char *PixelFindHits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelFindHits*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelFindHits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelFindHits*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelFindHits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelFindHits*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelFindHits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelFindHits*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelFindTracks::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelFindTracks::Class_Name()
{
   return "PixelFindTracks";
}

//______________________________________________________________________________
const char *PixelFindTracks::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelFindTracks*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelFindTracks::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelFindTracks*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelFindTracks::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelFindTracks*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelFindTracks::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelFindTracks*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelFitTracks::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelFitTracks::Class_Name()
{
   return "PixelFitTracks";
}

//______________________________________________________________________________
const char *PixelFitTracks::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelFitTracks*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelFitTracks::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelFitTracks*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelFitTracks::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelFitTracks*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelFitTracks::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelFitTracks*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelGeo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelGeo::Class_Name()
{
   return "PixelGeo";
}

//______________________________________________________________________________
const char *PixelGeo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelGeo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelGeo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelGeo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelGeo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelGeo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelGeo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelGeo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelGeoPar::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelGeoPar::Class_Name()
{
   return "PixelGeoPar";
}

//______________________________________________________________________________
const char *PixelGeoPar::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelGeoPar*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelGeoPar::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelGeoPar*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelGeoPar::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelGeoPar*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelGeoPar::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelGeoPar*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelEventHeader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelEventHeader::Class_Name()
{
   return "PixelEventHeader";
}

//______________________________________________________________________________
const char *PixelEventHeader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelEventHeader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelEventHeader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelEventHeader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelEventHeader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelEventHeader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelEventHeader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelEventHeader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelPoint::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelPoint::Class_Name()
{
   return "PixelPoint";
}

//______________________________________________________________________________
const char *PixelPoint::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelPoint*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelPoint::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelPoint*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelPoint::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelPoint*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelPoint::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelPoint*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelDigi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelDigi::Class_Name()
{
   return "PixelDigi";
}

//______________________________________________________________________________
const char *PixelDigi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelDigi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelDigi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelDigi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelDigi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelDigi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelHit::Class_Name()
{
   return "PixelHit";
}

//______________________________________________________________________________
const char *PixelHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr PixelTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *PixelTrack::Class_Name()
{
   return "PixelTrack";
}

//______________________________________________________________________________
const char *PixelTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int PixelTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::PixelTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *PixelTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *PixelTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::PixelTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Pixel::Streamer(TBuffer &R__b)
{
   // Stream an object of class Pixel.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Pixel::Class(),this);
   } else {
      R__b.WriteClassBuffer(Pixel::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Pixel(void *p) {
      return  p ? new(p) ::Pixel : new ::Pixel;
   }
   static void *newArray_Pixel(Long_t nElements, void *p) {
      return p ? new(p) ::Pixel[nElements] : new ::Pixel[nElements];
   }
   // Wrapper around operator delete
   static void delete_Pixel(void *p) {
      delete ((::Pixel*)p);
   }
   static void deleteArray_Pixel(void *p) {
      delete [] ((::Pixel*)p);
   }
   static void destruct_Pixel(void *p) {
      typedef ::Pixel current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Pixel

//______________________________________________________________________________
void PixelContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelContFact.

   FairContFact::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelContFact(void *p) {
      return  p ? new(p) ::PixelContFact : new ::PixelContFact;
   }
   static void *newArray_PixelContFact(Long_t nElements, void *p) {
      return p ? new(p) ::PixelContFact[nElements] : new ::PixelContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelContFact(void *p) {
      delete ((::PixelContFact*)p);
   }
   static void deleteArray_PixelContFact(void *p) {
      delete [] ((::PixelContFact*)p);
   }
   static void destruct_PixelContFact(void *p) {
      typedef ::PixelContFact current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_PixelContFact(TBuffer &buf, void *obj) {
      ((::PixelContFact*)obj)->::PixelContFact::Streamer(buf);
   }
} // end of namespace ROOT for class ::PixelContFact

//______________________________________________________________________________
void PixelDigitize::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelDigitize.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelDigitize::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelDigitize::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelDigitize(void *p) {
      return  p ? new(p) ::PixelDigitize : new ::PixelDigitize;
   }
   static void *newArray_PixelDigitize(Long_t nElements, void *p) {
      return p ? new(p) ::PixelDigitize[nElements] : new ::PixelDigitize[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelDigitize(void *p) {
      delete ((::PixelDigitize*)p);
   }
   static void deleteArray_PixelDigitize(void *p) {
      delete [] ((::PixelDigitize*)p);
   }
   static void destruct_PixelDigitize(void *p) {
      typedef ::PixelDigitize current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelDigitize

//______________________________________________________________________________
void PixelDigiPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelDigiPar.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelDigiPar::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelDigiPar::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelDigiPar(void *p) {
      return  p ? new(p) ::PixelDigiPar : new ::PixelDigiPar;
   }
   static void *newArray_PixelDigiPar(Long_t nElements, void *p) {
      return p ? new(p) ::PixelDigiPar[nElements] : new ::PixelDigiPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelDigiPar(void *p) {
      delete ((::PixelDigiPar*)p);
   }
   static void deleteArray_PixelDigiPar(void *p) {
      delete [] ((::PixelDigiPar*)p);
   }
   static void destruct_PixelDigiPar(void *p) {
      typedef ::PixelDigiPar current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelDigiPar

//______________________________________________________________________________
void PixelDigiSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelDigiSource.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelDigiSource::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelDigiSource::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelDigiSource(void *p) {
      return  p ? new(p) ::PixelDigiSource : new ::PixelDigiSource;
   }
   static void *newArray_PixelDigiSource(Long_t nElements, void *p) {
      return p ? new(p) ::PixelDigiSource[nElements] : new ::PixelDigiSource[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelDigiSource(void *p) {
      delete ((::PixelDigiSource*)p);
   }
   static void deleteArray_PixelDigiSource(void *p) {
      delete [] ((::PixelDigiSource*)p);
   }
   static void destruct_PixelDigiSource(void *p) {
      typedef ::PixelDigiSource current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelDigiSource

//______________________________________________________________________________
void PixelDigiBinSource::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelDigiBinSource.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelDigiBinSource::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelDigiBinSource::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelDigiBinSource(void *p) {
      return  p ? new(p) ::PixelDigiBinSource : new ::PixelDigiBinSource;
   }
   static void *newArray_PixelDigiBinSource(Long_t nElements, void *p) {
      return p ? new(p) ::PixelDigiBinSource[nElements] : new ::PixelDigiBinSource[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelDigiBinSource(void *p) {
      delete ((::PixelDigiBinSource*)p);
   }
   static void deleteArray_PixelDigiBinSource(void *p) {
      delete [] ((::PixelDigiBinSource*)p);
   }
   static void destruct_PixelDigiBinSource(void *p) {
      typedef ::PixelDigiBinSource current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelDigiBinSource

//______________________________________________________________________________
void PixelDigiWriteToFile::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelDigiWriteToFile.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelDigiWriteToFile::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelDigiWriteToFile::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelDigiWriteToFile(void *p) {
      return  p ? new(p) ::PixelDigiWriteToFile : new ::PixelDigiWriteToFile;
   }
   static void *newArray_PixelDigiWriteToFile(Long_t nElements, void *p) {
      return p ? new(p) ::PixelDigiWriteToFile[nElements] : new ::PixelDigiWriteToFile[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelDigiWriteToFile(void *p) {
      delete ((::PixelDigiWriteToFile*)p);
   }
   static void deleteArray_PixelDigiWriteToFile(void *p) {
      delete [] ((::PixelDigiWriteToFile*)p);
   }
   static void destruct_PixelDigiWriteToFile(void *p) {
      typedef ::PixelDigiWriteToFile current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelDigiWriteToFile

//______________________________________________________________________________
void PixelDigiWriteToBinFile::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelDigiWriteToBinFile.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelDigiWriteToBinFile::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelDigiWriteToBinFile::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelDigiWriteToBinFile(void *p) {
      return  p ? new(p) ::PixelDigiWriteToBinFile : new ::PixelDigiWriteToBinFile;
   }
   static void *newArray_PixelDigiWriteToBinFile(Long_t nElements, void *p) {
      return p ? new(p) ::PixelDigiWriteToBinFile[nElements] : new ::PixelDigiWriteToBinFile[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelDigiWriteToBinFile(void *p) {
      delete ((::PixelDigiWriteToBinFile*)p);
   }
   static void deleteArray_PixelDigiWriteToBinFile(void *p) {
      delete [] ((::PixelDigiWriteToBinFile*)p);
   }
   static void destruct_PixelDigiWriteToBinFile(void *p) {
      typedef ::PixelDigiWriteToBinFile current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelDigiWriteToBinFile

//______________________________________________________________________________
void PixelFindHits::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelFindHits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelFindHits::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelFindHits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelFindHits(void *p) {
      return  p ? new(p) ::PixelFindHits : new ::PixelFindHits;
   }
   static void *newArray_PixelFindHits(Long_t nElements, void *p) {
      return p ? new(p) ::PixelFindHits[nElements] : new ::PixelFindHits[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelFindHits(void *p) {
      delete ((::PixelFindHits*)p);
   }
   static void deleteArray_PixelFindHits(void *p) {
      delete [] ((::PixelFindHits*)p);
   }
   static void destruct_PixelFindHits(void *p) {
      typedef ::PixelFindHits current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelFindHits

//______________________________________________________________________________
void PixelFindTracks::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelFindTracks.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelFindTracks::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelFindTracks::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelFindTracks(void *p) {
      return  p ? new(p) ::PixelFindTracks : new ::PixelFindTracks;
   }
   static void *newArray_PixelFindTracks(Long_t nElements, void *p) {
      return p ? new(p) ::PixelFindTracks[nElements] : new ::PixelFindTracks[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelFindTracks(void *p) {
      delete ((::PixelFindTracks*)p);
   }
   static void deleteArray_PixelFindTracks(void *p) {
      delete [] ((::PixelFindTracks*)p);
   }
   static void destruct_PixelFindTracks(void *p) {
      typedef ::PixelFindTracks current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelFindTracks

//______________________________________________________________________________
void PixelFitTracks::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelFitTracks.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelFitTracks::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelFitTracks::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelFitTracks(void *p) {
      return  p ? new(p) ::PixelFitTracks : new ::PixelFitTracks;
   }
   static void *newArray_PixelFitTracks(Long_t nElements, void *p) {
      return p ? new(p) ::PixelFitTracks[nElements] : new ::PixelFitTracks[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelFitTracks(void *p) {
      delete ((::PixelFitTracks*)p);
   }
   static void deleteArray_PixelFitTracks(void *p) {
      delete [] ((::PixelFitTracks*)p);
   }
   static void destruct_PixelFitTracks(void *p) {
      typedef ::PixelFitTracks current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelFitTracks

//______________________________________________________________________________
void PixelGeo::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelGeo.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoSet::Streamer(R__b);
      R__b.ReadStaticArray((char*)modName);
      R__b.ReadStaticArray((char*)eleName);
      R__b.CheckByteCount(R__s, R__c, PixelGeo::IsA());
   } else {
      R__c = R__b.WriteVersion(PixelGeo::IsA(), kTRUE);
      FairGeoSet::Streamer(R__b);
      R__b.WriteArray(modName, 20);
      R__b.WriteArray(eleName, 20);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelGeo(void *p) {
      return  p ? new(p) ::PixelGeo : new ::PixelGeo;
   }
   static void *newArray_PixelGeo(Long_t nElements, void *p) {
      return p ? new(p) ::PixelGeo[nElements] : new ::PixelGeo[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelGeo(void *p) {
      delete ((::PixelGeo*)p);
   }
   static void deleteArray_PixelGeo(void *p) {
      delete [] ((::PixelGeo*)p);
   }
   static void destruct_PixelGeo(void *p) {
      typedef ::PixelGeo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_PixelGeo(TBuffer &buf, void *obj) {
      ((::PixelGeo*)obj)->::PixelGeo::Streamer(buf);
   }
} // end of namespace ROOT for class ::PixelGeo

//______________________________________________________________________________
void PixelGeoPar::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelGeoPar.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairParGenericSet::Streamer(R__b);
      R__b >> fGeoSensNodes;
      R__b >> fGeoPassNodes;
      R__b.CheckByteCount(R__s, R__c, PixelGeoPar::IsA());
   } else {
      R__c = R__b.WriteVersion(PixelGeoPar::IsA(), kTRUE);
      FairParGenericSet::Streamer(R__b);
      R__b << fGeoSensNodes;
      R__b << fGeoPassNodes;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelGeoPar(void *p) {
      return  p ? new(p) ::PixelGeoPar : new ::PixelGeoPar;
   }
   static void *newArray_PixelGeoPar(Long_t nElements, void *p) {
      return p ? new(p) ::PixelGeoPar[nElements] : new ::PixelGeoPar[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelGeoPar(void *p) {
      delete ((::PixelGeoPar*)p);
   }
   static void deleteArray_PixelGeoPar(void *p) {
      delete [] ((::PixelGeoPar*)p);
   }
   static void destruct_PixelGeoPar(void *p) {
      typedef ::PixelGeoPar current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_PixelGeoPar(TBuffer &buf, void *obj) {
      ((::PixelGeoPar*)obj)->::PixelGeoPar::Streamer(buf);
   }
} // end of namespace ROOT for class ::PixelGeoPar

//______________________________________________________________________________
void PixelEventHeader::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelEventHeader.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelEventHeader::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelEventHeader::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelEventHeader(void *p) {
      return  p ? new(p) ::PixelEventHeader : new ::PixelEventHeader;
   }
   static void *newArray_PixelEventHeader(Long_t nElements, void *p) {
      return p ? new(p) ::PixelEventHeader[nElements] : new ::PixelEventHeader[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelEventHeader(void *p) {
      delete ((::PixelEventHeader*)p);
   }
   static void deleteArray_PixelEventHeader(void *p) {
      delete [] ((::PixelEventHeader*)p);
   }
   static void destruct_PixelEventHeader(void *p) {
      typedef ::PixelEventHeader current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelEventHeader

//______________________________________________________________________________
void PixelPoint::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelPoint.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelPoint::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelPoint::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelPoint(void *p) {
      return  p ? new(p) ::PixelPoint : new ::PixelPoint;
   }
   static void *newArray_PixelPoint(Long_t nElements, void *p) {
      return p ? new(p) ::PixelPoint[nElements] : new ::PixelPoint[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelPoint(void *p) {
      delete ((::PixelPoint*)p);
   }
   static void deleteArray_PixelPoint(void *p) {
      delete [] ((::PixelPoint*)p);
   }
   static void destruct_PixelPoint(void *p) {
      typedef ::PixelPoint current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelPoint

//______________________________________________________________________________
void PixelDigi::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelDigi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelDigi::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelDigi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelDigi(void *p) {
      return  p ? new(p) ::PixelDigi : new ::PixelDigi;
   }
   static void *newArray_PixelDigi(Long_t nElements, void *p) {
      return p ? new(p) ::PixelDigi[nElements] : new ::PixelDigi[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelDigi(void *p) {
      delete ((::PixelDigi*)p);
   }
   static void deleteArray_PixelDigi(void *p) {
      delete [] ((::PixelDigi*)p);
   }
   static void destruct_PixelDigi(void *p) {
      typedef ::PixelDigi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelDigi

//______________________________________________________________________________
void PixelHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelHit(void *p) {
      return  p ? new(p) ::PixelHit : new ::PixelHit;
   }
   static void *newArray_PixelHit(Long_t nElements, void *p) {
      return p ? new(p) ::PixelHit[nElements] : new ::PixelHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelHit(void *p) {
      delete ((::PixelHit*)p);
   }
   static void deleteArray_PixelHit(void *p) {
      delete [] ((::PixelHit*)p);
   }
   static void destruct_PixelHit(void *p) {
      typedef ::PixelHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelHit

//______________________________________________________________________________
void PixelTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class PixelTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(PixelTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(PixelTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_PixelTrack(void *p) {
      return  p ? new(p) ::PixelTrack : new ::PixelTrack;
   }
   static void *newArray_PixelTrack(Long_t nElements, void *p) {
      return p ? new(p) ::PixelTrack[nElements] : new ::PixelTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_PixelTrack(void *p) {
      delete ((::PixelTrack*)p);
   }
   static void deleteArray_PixelTrack(void *p) {
      delete [] ((::PixelTrack*)p);
   }
   static void destruct_PixelTrack(void *p) {
      typedef ::PixelTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::PixelTrack

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

namespace {
  void TriggerDictionaryInitialization_G__PixelDict_Impl() {
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
"/Users/turany/development/FairRoot/base/MQ/policies/Serialization",
"/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src",
"/Users/turany/development/FairRoot/examples/MQ/9-PixelDetector/src/devices",
"/Users/turany/development/FairRoot/examples/common/mcstack",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/MQ/9-PixelDetector/src/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__PixelDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class Pixel;
class __attribute__((annotate(R"ATTRDUMP(Factory for all Pixel parameter containers)ATTRDUMP"))) PixelContFact;
class PixelDigitize;
class PixelDigiPar;
class PixelDigiSource;
class PixelDigiBinSource;
class PixelDigiWriteToFile;
class PixelDigiWriteToBinFile;
class PixelFindHits;
class PixelFindTracks;
class PixelFitTracks;
class PixelGeo;
class PixelGeoPar;
class PixelEventHeader;
class __attribute__((annotate("$clingAutoload$PixelPoint.h")))  PixelPoint;
class __attribute__((annotate("$clingAutoload$PixelDigi.h")))  PixelDigi;
class __attribute__((annotate("$clingAutoload$PixelHit.h")))  PixelHit;
class __attribute__((annotate("$clingAutoload$PixelTrack.h")))  PixelTrack;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__PixelDict dictionary payload"

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
#ifndef PIXEL_H
#define PIXEL_H

#include "FairDetector.h"               // for FairDetector

#include "Rtypes.h"                     // for Int_t, Double32_t, Double_t, etc
#include "TLorentzVector.h"             // for TLorentzVector
#include "TVector3.h"                   // for TVector3
class PixelPoint;
class FairVolume;
class TClonesArray;

class Pixel: public FairDetector
{

  public:

    /**      Name :  Detector Name
     *       Active: kTRUE for active detectors (ProcessHits() will be called)
     *               kFALSE for inactive detectors
    */
    Pixel(const char* Name, Bool_t Active);

    /**      default constructor    */
    Pixel();

    /**       destructor     */
    virtual ~Pixel();

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

    /**      Misalign the detector geometry        */
    void ModifyGeometry();
    void SetMisalignDetector(Bool_t tb=kTRUE) { fMisalignDetector = tb; }

    /**      This method is an example of how to add your own point
     *       of type PixelPoint to the clones array
    */
    PixelPoint* AddHit(Int_t trackID, Int_t detID,
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

    Bool_t         fMisalignDetector;
    TClonesArray*  fPixelPointCollection;

    Pixel(const Pixel&);
    Pixel& operator=(const Pixel&);

    ClassDef(Pixel,1)
};

#endif //PIXEL_H
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELCONTFACT_H
#define PIXELCONTFACT_H

#include "FairContFact.h"
#include "FairContFact.h"  // for FairContFact, FairContainer (ptr only)
#include "Rtypes.h"        // for PixelContFact::Class, ClassDef, PixelContF...
class FairParSet;

class PixelContFact : public FairContFact
{
  private:
    void setAllContainers();
  public:
    PixelContFact();
    ~PixelContFact() {}
    FairParSet* createContainer(FairContainer*);
    ClassDef( PixelContFact,0) // Factory for all Pixel parameter containers
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
 * PixelHit.h
 *
 *  Created on: 16.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGITIZE_H
#define PIXELDIGITIZE_H 1

#include "FairTask.h"

#include "PixelPoint.h"

#include <list>
#include <map>

class TClonesArray;
class PixelDigiPar;

class PixelDigitize : public FairTask
{

 public:

  /** Default constructor **/
  PixelDigitize();


  /** Standard constructor **/
  PixelDigitize(Int_t iVerbose);


  /** Constructor with name **/
  PixelDigitize(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelDigitize();


  /** Execution **/
  virtual void Exec(Option_t* opt);


 private:

  PixelDigiPar*     fDigiPar;

  TClonesArray*     fPoints;       /** Input array of PixelPoint **/
  TClonesArray*     fDigis;        /** Output array of PixelDigi **/

  Int_t             fNPoints;
  Int_t             fNDigis;

  Int_t             fTNofEvents;
  Int_t             fTNofPoints;
  Int_t             fTNofDigis;

  Int_t fFeCols;            // Colums read per Frontend 
  Int_t fFeRows;            // Rows read per Frontend
  Int_t fMaxFEperCol;       // max number of Frontend elemens per column
  Double_t fPitchX;         // Pixel cell size X
  Double_t fPitchY;         // Pixel cell size Y
  
  /** Activate pixel **/
  void ActivatePixel(Int_t index, Int_t detId, Int_t feId, Int_t col, Int_t row, Double_t charge, Double_t timestamp);


  /** Get parameter containers **/
  virtual void SetParContainers();


  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Reset eventwise counters **/
  void Reset();


  /** Finish at the end of each event **/
  virtual void Finish();

  PixelDigitize(const PixelDigitize&);
  PixelDigitize& operator=(const PixelDigitize&);

  ClassDef(PixelDigitize,1);

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
 * PixelHit.h
 *
 *  Created on: 17.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGIPAR_H
#define PIXELDIGIPAR_H


#include "FairParGenericSet.h"  // for FairParGenericSet
#include "Rtypes.h"             // for PixelDigiPar::Class, ClassDef, PixelD...
class FairParamList;

//! Digitization Parameter Class for Pixel detector
class PixelDigiPar : public FairParGenericSet
{
 public :
  PixelDigiPar (const char* name="PixelDigiParameters",
		const char* title="Pixel digi parameters",
		const char* context="TestDefaultContext");
  ~PixelDigiPar(void);
  void clear(void){};
  void putParams(FairParamList* list);
  Bool_t getParams(FairParamList* list);
  
  void Print(Option_t*) const;
  
    Double_t GetXPitch()        const {return fDimX;}
    Double_t GetYPitch()        const {return fDimY;}
    Double_t GetThreshold()     const {return fThreshold;}
    Double_t GetNoise()         const {return fNoise;}
    Double_t GetQCloudSigma()   const {return fCSigma;}
    Int_t GetFECols()           const {return fFeCols;}
    Int_t GetFERows()           const {return fFeRows;}
    Int_t GetMaxFEperCol()      const {return fMaxFEperCol;}
    Double_t GetClustRadius()   const {return fRadius;}
    Double_t GetFeBusClock()    const {return fFeBusClock;}
    Double_t GetTimeStep()		const {return (1./fFeBusClock * 1000.);} ///< Time step of one clock cycle in ns
    Int_t GetChargeConvMethod() const  {return fChargeConvMethod;}
    Double_t GetPixelSorterCellWidth() const {return fPixelSorterCellWidth;}
    Int_t GetPixelSorterNumberOfCells() const {return fPixelSorterNumberOfCells;}
    
    void SetXPitch(Double_t x)        {fDimX = x;}
    void SetYPitch(Double_t x)        {fDimY = x;}
    void SetThreshold(Double_t x)     {fThreshold = x;}
    void SetNoise(Double_t x)         {fNoise = x;}
    void SetQCloudSigma(Double_t x)   {fCSigma = x;}
    void SetFECols(Int_t x)           {fFeCols = x;}
    void SetFERows(Int_t x)           {fFeRows = x;}
    void SetMaxFEperCol(Int_t x)      {fMaxFEperCol = x;}
    void SetClustRadius(Double_t x)   {fRadius=x;}
    void SetFeBusClock(Double_t x)      {fFeBusClock = x;}
    void SetChargeConvMethod(Int_t x) {fChargeConvMethod = x;}
    void SetPixelSorterCellWidth(Double_t x) {fPixelSorterCellWidth = x;}
    void SetPixelSorterNumberOfCells(Int_t x) {fPixelSorterNumberOfCells=x;}
    
  private:
    // Pixel Parameters
    Int_t fFeCols;            // Colums read per Frontend 
    Int_t fFeRows;            // Rows read per Frontend
    Int_t fMaxFEperCol;       // max number of Frontend elemens per column
    Double_t fDimX;           // Pixel cell size X
    Double_t fDimY;           // Pixel cell size Y
    Double_t fRadius;         // Clusterfinder search radius (channel numbers)
    Double_t fThreshold;      // Discriminator Threshold (electrons)
    Double_t fNoise;          // Gaussian electronics noise including threshold dispersion (electrons)
    Double_t fCSigma;         // Gaussian charge cloud smearing
    Double_t fFeBusClock;   // Frontend bus clock to determin noise rate
    Int_t fChargeConvMethod;	// 0: ideal conversion; 1: TOT calculation
    Double_t fPixelSorterCellWidth;	// Parameter for TimeStamp Sorter
    Int_t fPixelSorterNumberOfCells; // Parameter for TimeStamp Sorter

    
    ClassDef(PixelDigiPar,1);
};

#endif /*!PIXELDIGIPAR_H*/
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//
//  PixelDigiSource.h
// 
//
//  Created by Radoslaw Karabowicz on 19.02.2016Mohammad Al-Turany on 08/02/14.
//
//

#ifndef PIXELDIGISOURCE_H_
#define PIXELDIGISOURCE_H_

#include "FairSource.h"

#include "TString.h"

#include <list>  
#include <fstream>
  
class TClonesArray;

class FairLogger;
class FairRuntimeDb;
class PixelEventHeader;

class PixelDigiSource : public FairSource
{
public:
  PixelDigiSource(TString inputFileName="test.dat");
  virtual ~PixelDigiSource();
  
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

  virtual void FillEventHeader(FairEventHeader* feh);
    
  void SetInputFileName(TString tstr) {fInputFileName = tstr;};

  virtual Bool_t  ActivateObject(TObject** obj, const char* BrName);

private:
  PixelEventHeader* fEventHeader;
  TClonesArray*     fDigis;        /** Output array of PixelDigi **/
  Int_t             fNDigis;
  
  Int_t             fTNofEvents;
  Int_t             fTNofDigis;

  TString  fInputFileName;
  std::ifstream fInputFile;

  Int_t    fCurrentEntryNo;

  Int_t    fRunId;
  Int_t    fMCEntryNo;
  Int_t    fPartNo;

  PixelDigiSource(const PixelDigiSource&);
  PixelDigiSource& operator=(const PixelDigiSource&);

  ClassDef(PixelDigiSource, 1)
};


#endif /* defined(PIXELDIGISOURCE_H_) */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
//
//  PixelDigiBinSource.h
// 
//
//  Created by Radoslaw Karabowicz on 19.02.2016Mohammad Al-Turany on 08/02/14.
//
//

#ifndef PIXELDIGIBINSOURCE_H_
#define PIXELDIGIBINSOURCE_H_

#include "FairSource.h"

#include "TString.h"

#include <list>  
#include <fstream>
  
class TClonesArray;

class FairLogger;
class FairRuntimeDb;
class PixelEventHeader;

class PixelDigiBinSource : public FairSource
{
public:
  PixelDigiBinSource(TString inputFileName="test.dat");
  virtual ~PixelDigiBinSource();
  
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

  virtual void FillEventHeader(FairEventHeader* feh);
    
  void SetInputFileName(TString tstr) {fInputFileName = tstr;};

  virtual Bool_t  ActivateObject(TObject** obj, const char* BrName);

private:
  PixelEventHeader* fEventHeader;
  TClonesArray*     fDigis;        /** Output array of PixelDigi **/
  Int_t             fNDigis;
  
  Int_t             fTNofEvents;
  Int_t             fTNofDigis;

  TString  fInputFileName;
  std::ifstream fInputFile;

  Int_t    fCurrentEntryNo;

  Int_t    fRunId;
  Int_t    fMCEntryNo;
  Int_t    fPartNo;

  PixelDigiBinSource(const PixelDigiBinSource&);
  PixelDigiBinSource& operator=(const PixelDigiBinSource&);

  ClassDef(PixelDigiBinSource, 1)
};


#endif /* defined(PIXELDIGISOURCE_H_) */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelWriteToFile.h
 *
 *  Created on: 19.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGIWRITETOFILE_H
#define PIXELDIGIWRITETOFILE_H 1

#include "FairTask.h"

#include "PixelDigi.h"

class TString;

#include <list>
#include <map>
#include <fstream>

class PixelDigiWriteToFile : public FairTask
{

 public:

  /** Default constructor **/
  PixelDigiWriteToFile();


  /** Standard constructor **/
  PixelDigiWriteToFile(Int_t iVerbose);


  /** Constructor with name **/
  PixelDigiWriteToFile(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelDigiWriteToFile();


  /** Execution **/
  virtual void Exec(Option_t* opt);

  void SetOutputFileName(TString tstr) {fOutputFileName = tstr;};

  void SetDivideLevel(Int_t idiv) { fDivideLevel = idiv; } // 0 - event, 1 - station, 2 - sensor

 private:

  TClonesArray*     fDigis;        /** Input array of PixelDigi **/

  TString  fOutputFileName;
  Int_t fNofOutputFiles;
  std::ofstream fOutputFiles[12]; // no more than 12 output files....

  /** Get parameter containers **/
  virtual void SetParContainers();
  
  Int_t fDivideLevel;
  
  Int_t fRunId;
  Int_t fMCEntryNo;
  Int_t fPartNo;

  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Reset eventwise counters **/
  void Reset();


  /** Finish at the end of each event **/
  virtual void Finish();

  PixelDigiWriteToFile(const PixelDigiWriteToFile&);
  PixelDigiWriteToFile& operator=(const PixelDigiWriteToFile&);

  ClassDef(PixelDigiWriteToFile,1);

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
 * PixelWriteToFile.h
 *
 *  Created on: 19.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELDIGIWRITETOBINFILE_H
#define PIXELDIGIWRITETOBINFILE_H 1

#include "FairTask.h"

#include "PixelDigi.h"

class TString;

#include <list>
#include <map>
#include <fstream>

class PixelDigiWriteToBinFile : public FairTask
{

 public:

  /** Default constructor **/
  PixelDigiWriteToBinFile();


  /** Standard constructor **/
  PixelDigiWriteToBinFile(Int_t iVerbose);


  /** Constructor with name **/
  PixelDigiWriteToBinFile(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelDigiWriteToBinFile();


  /** Execution **/
  virtual void Exec(Option_t* opt);

  void SetOutputFileName(TString tstr) {fOutputFileName = tstr;};

  void SetDivideLevel(Int_t idiv) { fDivideLevel = idiv; } // 0 - event, 1 - station, 2 - sensor

 private:

  TClonesArray*     fDigis;        /** Input array of PixelDigi **/

  TString  fOutputFileName;
  Int_t fNofOutputFiles;
  std::ofstream fOutputFiles[12]; // no more than 12 output files....

  /** Get parameter containers **/
  virtual void SetParContainers();
  
  Int_t fDivideLevel;
  
  Int_t fRunId;
  Int_t fMCEntryNo;
  Int_t fPartNo;

  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Reset eventwise counters **/
  void Reset();


  /** Finish at the end of each event **/
  virtual void Finish();

  PixelDigiWriteToBinFile(const PixelDigiWriteToBinFile&);
  PixelDigiWriteToBinFile& operator=(const PixelDigiWriteToBinFile&);

  ClassDef(PixelDigiWriteToBinFile,1);

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
 * PixelFindHits.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELFINDHITS_H
#define PIXELFINDHITS_H 1

#include "FairTask.h"

#include "PixelPoint.h"

#include <list>
#include <map>
#include <string>

class TClonesArray;
class PixelDigiPar;
class FairGeoParSet;


class PixelFindHits : public FairTask
{

 public:

  /** Default constructor **/
  PixelFindHits();


  /** Standard constructor **/
  PixelFindHits(Int_t iVerbose);


  /** Constructor with name **/
  PixelFindHits(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelFindHits();


  /** Execution **/
  virtual void Exec(Option_t* opt);

  virtual void GetParList(TList* tempList);
  virtual void InitMQ    (TList* tempList);
  virtual void ExecMQ    (TList* inputList,TList* outputList);

// MQ
  void ExecMQ(Option_t* opt);
  TClonesArray* ExecMQ(TClonesArray* digis);
  void InitMQ(const std::string& root_file, const std::string& ascii_file);
  void UpdateParameter(PixelDigiPar* digipar, FairGeoParSet* geopar);

 private:

  PixelDigiPar*     fDigiPar;
  FairGeoParSet* fGeoParSet;


  TClonesArray*     fDigis;        /** Input array of PixelDigi **/
  TClonesArray*     fHits;         /** Output array of PixelHit **/

  Int_t             fNDigis;
  Int_t             fNHits;

  Int_t             fTNofEvents;
  Int_t             fTNofDigis;
  Int_t             fTNofHits;

  Int_t fFeCols;            // Colums read per Frontend 
  Int_t fFeRows;            // Rows read per Frontend
  Int_t fMaxFEperCol;       // max number of Frontend elemens per column
  Double_t fPitchX;         // Pixel cell size X
  Double_t fPitchY;         // Pixel cell size Y
  
  /** Get parameter containers **/
  virtual void SetParContainers();


  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Reset eventwise counters **/
  void Reset();


  /** Finish at the end of each event **/
  virtual void Finish();

  PixelFindHits(const PixelFindHits&);
  PixelFindHits& operator=(const PixelFindHits&);

  ClassDef(PixelFindHits,1);

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
 * PixelFindTracks.h
 *
 *  Created on: 23.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELFINDTRACKS_H
#define PIXELFINDTRACKS_H 1

#include "FairTask.h"

#include "PixelHit.h"

#include <list>
#include <map>

class TClonesArray;
class TH2F;
class PixelDigiPar;

class PixelFindTracks : public FairTask
{

 public:

  /** Default constructor **/
  PixelFindTracks();


  /** Standard constructor **/
  PixelFindTracks(Int_t iVerbose);


  /** Constructor with name **/
  PixelFindTracks(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelFindTracks();


  /** Execution **/
  virtual void Exec(Option_t* opt);

  virtual void GetParList(TList* tempList);
  virtual void InitMQ    (TList* tempList);
  virtual void ExecMQ    (TList* inputList,TList* outputList);


 private:

  PixelDigiPar*     fDigiPar;

  TClonesArray*     fHits;         /** Input array of PixelHit **/
  TClonesArray*     fTracks;       /** Output array of PixelTrack **/

  Int_t             fTNofEvents;

  Int_t             fNHits;
  Int_t             fTNofHits;

  Int_t             fNTracks;
  Int_t             fTNofTracks;

  TH2F*             fhDist2D;

  /** Get parameter containers **/
  virtual void SetParContainers();


  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Reset eventwise counters **/
  void Reset();


  /** Finish at the end of each event **/
  virtual void Finish();

  PixelFindTracks(const PixelFindTracks&);
  PixelFindTracks& operator=(const PixelFindTracks&);

  ClassDef(PixelFindTracks,1);

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
 * PixelFitTracks.h
 *
 *  Created on: 25.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELFITTRACKS_H
#define PIXELFITTRACKS_H 1

#include "FairTask.h"

#include "PixelTrack.h"

#include <list>
#include <map>

class TClonesArray;
class PixelDigiPar;

class PixelFitTracks : public FairTask
{

 public:

  /** Default constructor **/
  PixelFitTracks();


  /** Standard constructor **/
  PixelFitTracks(Int_t iVerbose);


  /** Constructor with name **/
  PixelFitTracks(const char* name, Int_t iVerbose);


  /** Destructor **/
  virtual ~PixelFitTracks();


  /** Execution **/
  virtual void Exec(Option_t* opt);

  virtual void GetParList(TList* tempList);
  virtual void InitMQ    (TList* tempList);
  virtual void ExecMQ    (TList* inputList,TList* outputList);

 private:

  PixelDigiPar*     fDigiPar;

  TClonesArray*     fHits;          /** Input array of PixelHit **/
  TClonesArray*     fTracks;        /** Input array of PixelTrack **/
  TClonesArray*     fFitTracks;     /** Output array of PixelTrack **/

  Int_t             fTNofEvents;

  Int_t             fNHits;

  Int_t             fNTracks;
  Int_t             fTNofTracks;

  Int_t             fNFitTracks;
  Int_t             fTNofFitTracks;


  Double_t LinearRegression(Int_t nval, Double_t xval[], Double_t yval[], 
			    Double_t& valA0, Double_t& errA0,
			    Double_t& valA1, Double_t& errA1 );


  /** Get parameter containers **/
  virtual void SetParContainers();


  /** Intialisation **/
  virtual InitStatus Init();


  /** Reinitialisation **/
  virtual InitStatus ReInit();


  /** Reset eventwise counters **/
  void Reset();


  /** Finish at the end of each event **/
  virtual void Finish();

  PixelFitTracks(const PixelFitTracks&);
  PixelFitTracks& operator=(const PixelFitTracks&);

  ClassDef(PixelFitTracks,1);

};

#endif


/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELGEO_H
#define PIXELGEO_H

#include "FairGeoSet.h"  // for FairGeoSet
#include "Rtypes.h"      // for PixelGeo::Class, ClassDef, PixelGeo::Streamer
#include "TString.h"     // for TString

class  PixelGeo : public FairGeoSet
{

  protected:
    char modName[20];  // name of module
    char eleName[20];  // substring for elements in module
  public:
    PixelGeo();
    ~PixelGeo() {}
    const char* getModuleName(Int_t);
    const char* getEleName(Int_t);
    inline Int_t getModNumInMod(const TString&);
    ClassDef(PixelGeo,1)
};

inline Int_t PixelGeo::getModNumInMod(const TString& name)
{
  /** returns the module index from module name
   ?? in name[??] has to be the length of the detector name in the
   .geo file. For example if all nodes in this file starts with
   newdetector ?? has to be 11.
  */
  return static_cast<Int_t>((name[5]-'0')-1); //
}

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELGEOPAR_H
#define PIXELGEOPAR_H

#include "FairParGenericSet.h"  // for FairParGenericSet
#include "Rtypes.h"             // for PixelGeoPar::Class, ClassDef, PixelGe...
class FairParamList;  // lines 14-14
class TObjArray;  // lines 13-13

class PixelGeoPar       : public FairParGenericSet
{
  public:

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoSensNodes;

    /** List of FairGeoNodes for sensitive  volumes */
    TObjArray*      fGeoPassNodes;

    PixelGeoPar(const char* name="PixelGeoPar",
                      const char* title="Pixel Geometry Parameters",
                      const char* context="TestDefaultContext");
    ~PixelGeoPar(void);
    void clear(void);
    void putParams(FairParamList*);
    Bool_t getParams(FairParamList*);
    TObjArray* GetGeoSensitiveNodes() {return fGeoSensNodes;}
    TObjArray* GetGeoPassiveNodes()   {return fGeoPassNodes;}

  private:
    PixelGeoPar(const PixelGeoPar&);
    PixelGeoPar& operator=(const PixelGeoPar&);

    ClassDef(PixelGeoPar,1)
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
 * PixelEventHeader.h
 *
 *  Created on: 18.03.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELEVENTHEADER_H_
#define PIXELEVENTHEADER_H_

#include "FairEventHeader.h"     // for FairEventHeader

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class PixelEventHeader : public FairEventHeader
{
  public:
    /** Default constructor **/
    PixelEventHeader();

    /** Destructor **/
    virtual ~PixelEventHeader();

    void  SetPartNo(Int_t ipart) { fPartNo = ipart;}
    Int_t GetPartNo()            { return fPartNo; }

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairEventHeader>(*this);
    }

  private:
    Int_t fPartNo;

#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    ClassDef(PixelEventHeader, 1);
};

#endif /* PIXELEVENTHEADER_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef PIXELPOINT_H
#define PIXELPOINT_H 1


#include "FairMCPoint.h"

#include "TObject.h"
#include "TVector3.h"

class PixelPoint : public FairMCPoint
{

  public:

    /** Default constructor **/
    PixelPoint();


    /** Constructor with arguments
     *@param trackID  Index of MCTrack
     *@param detID    Detector ID
     *@param pos      Ccoordinates at entrance to active volume [cm]
     *@param mom      Momentum of track at entrance [GeV]
     *@param tof      Time since event start [ns]
     *@param length   Track length since creation [cm]
     *@param eLoss    Energy deposit [GeV]
     **/
    PixelPoint(Int_t trackID, Int_t detID, TVector3 pos, TVector3 mom,
                     Double_t tof, Double_t length, Double_t eLoss);




    /** Destructor **/
    virtual ~PixelPoint();

    /** Output to screen **/
    virtual void Print(const Option_t* opt) const;

  private:
    /** Copy constructor **/
    PixelPoint(const PixelPoint& point);
    PixelPoint operator=(const PixelPoint& point);

    ClassDef(PixelPoint,1)

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
 * PixelDigi.h
 *
 *  Created on: 10.02.2016
 *      Author: M. Al-Turany
 */

#ifndef PixelDigi_H_
#define PixelDigi_H_

#include "FairTimeStamp.h"  // for FairTimeStamp
#include "Rtypes.h"         // for PixelDigi::Class, ClassDef, PixelDigi::St...


class PixelDigi : public FairTimeStamp
{
 public:
    PixelDigi();
    /**
     *\param index position of PixelPoint in TClonesArray
     *\param detID detector ID (from/for PixelPoint/Hit)
     *\param SensorID Sensor ID from digitization scheme
     *\param feID front end ID
     *\param charge deposited charge in electrons
    **/
    
    PixelDigi(Int_t index, Int_t detID, Int_t feID, Int_t col, Int_t row, Double_t charge, Double_t timestamp = -1);
    virtual ~PixelDigi();
    
    void SetIndex(Int_t in){fPointIndex = in;};
    void SetDetectorID(Int_t det){fDetectorID=det;};
    void SetFeID(Int_t fe){fFeID=fe;};
    void SetCharge(Double_t ch){fCharge = ch;};
    void SetCol(Int_t col){fCol = col;};
    void SetRow(Int_t row){fRow = row;};              

    Int_t GetIndex(){return fPointIndex;};
    Int_t GetDetectorID(){return fDetectorID;};
    Int_t GetFeID(){return fFeID;};
    Double_t GetCharge(){return fCharge;};
    Int_t GetCol(){return fCol;};
    Int_t GetRow(){return fRow;};    

  private:
    Int_t fPointIndex;
    Int_t fDetectorID;
    Int_t fFeID;
    Double_t fCharge;
    Int_t fCol;
    Int_t fRow;              
              
    ClassDef(PixelDigi, 1);
};

#endif /* PixelDigi_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelHit.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELHIT_H_
#define PIXELHIT_H_

#include "FairHit.h"     // for FairHit
#include "Rtypes.h"      // for PixelHit::Class, ClassDef, PixelHit::Streamer
class TVector3;  // lines 27-27

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class TVector3;

class PixelHit : public FairHit
{
  public:
    /** Default constructor **/
    PixelHit();

    /** Constructor **/
    PixelHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);

    /** Destructor **/
    virtual ~PixelHit();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    ClassDef(PixelHit, 1);
};

#endif /* PIXELHIT_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * PixelTrack.h
 *
 *  Created on: 18.02.2016
 *      Author: R. Karabowicz
 */

#ifndef PIXELTRACK_H_
#define PIXELTRACK_H_

#include "FairTimeStamp.h"  // for FairTimeStamp
#include "Rtypes.h"         // for PixelTrack::Class, ClassDef, PixelTrack::...

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__


class PixelTrack : public FairTimeStamp
{
  public:
    /** Default constructor **/
    PixelTrack();

    /** Constructor **/
    PixelTrack(Double_t x0 , Double_t ax , Double_t y0 , Double_t ay ,
	       Double_t x0e, Double_t axe, Double_t y0e, Double_t aye);


    void SetX0   (Double_t x0)  {fX0 = x0;};
    void SetAX   (Double_t ax)  {fAX = ax;};
    void SetY0   (Double_t y0)  {fY0 = y0;};
    void SetAY   (Double_t ay)  {fAY = ay;};
    void SetX0Err(Double_t x0e) {fX0Err = x0e;};
    void SetAXErr(Double_t axe) {fAXErr = axe;};
    void SetY0Err(Double_t y0e) {fY0Err = y0e;};
    void SetAYERr(Double_t aye) {fAYErr = aye;};

    Double_t GetX0   () {return fX0;};
    Double_t GetAX   () {return fAX;};
    Double_t GetY0   () {return fY0;};
    Double_t GetAY   () {return fAY;};
    Double_t GetX0Err() {return fX0Err;};
    Double_t GetAXErr() {return fAXErr;};
    Double_t GetY0Err() {return fY0Err;};
    Double_t GetAYErr() {return fAYErr;};

    void  AddHitIndex(Int_t hitIndex) {fHitIndices.push_back(hitIndex);};
    Int_t GetNofHits ()               {return fHitIndices.size();};
    Int_t GetHitIndex(Int_t ihit)     {return fHitIndices.at(ihit);};

    /** Destructor **/
    virtual ~PixelTrack();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairTimeStamp>(*this);
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;
#endif // for BOOST serialization

    Double_t fX0;
    Double_t fAX;
    Double_t fY0;
    Double_t fAY;
    Double_t fX0Err;
    Double_t fAXErr;
    Double_t fY0Err;
    Double_t fAYErr;

    std::vector<Int_t> fHitIndices;

    ClassDef(PixelTrack, 1);
};

#endif /* PIXELTRACK_H_ */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * PixelPayload.h
 *
 *  @since 2013-04-22
 *  @author A. Rybalchenko
 */

#ifndef PIXELPAYLOAD_H_
#define PIXELPAYLOAD_H_

#include <string>

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif
namespace PixelPayload
{
    class EventHeader
    {
      public:
        Int_t fRunId;
        Int_t fMCEntryNo;
        Int_t fPartNo;
    };

    class Digi
    {
      public:
        Int_t    fDetectorID;
        Int_t    fFeID;
        Double_t fCharge;
        Int_t    fCol;
        Int_t    fRow;              
    };

    class Hit
    {
      public:
        Int_t    fDetectorID;
        Double_t posX;
        Double_t posY;
        Double_t posZ;
        Double_t dposX;
        Double_t dposY;
        Double_t dposZ;
    };

    class Track
    {
      public:
        Double_t fX0;
        Double_t fAX;
        Double_t fY0;
        Double_t fAY;
        Double_t fX0Err;
        Double_t fAXErr;
        Double_t fY0Err;
        Double_t fAYErr;
    };
}
#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#define BIGBUFFERSIZE 1000000

#endif /* PIXELPAYLOAD_H_ */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"Pixel", payloadCode, "@",
"PixelContFact", payloadCode, "@",
"PixelDigi", payloadCode, "@",
"PixelDigiBinSource", payloadCode, "@",
"PixelDigiPar", payloadCode, "@",
"PixelDigiSource", payloadCode, "@",
"PixelDigiWriteToBinFile", payloadCode, "@",
"PixelDigiWriteToFile", payloadCode, "@",
"PixelDigitize", payloadCode, "@",
"PixelEventHeader", payloadCode, "@",
"PixelFindHits", payloadCode, "@",
"PixelFindTracks", payloadCode, "@",
"PixelFitTracks", payloadCode, "@",
"PixelGeo", payloadCode, "@",
"PixelGeoPar", payloadCode, "@",
"PixelHit", payloadCode, "@",
"PixelPoint", payloadCode, "@",
"PixelTrack", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__PixelDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__PixelDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__PixelDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__PixelDict() {
  TriggerDictionaryInitialization_G__PixelDict_Impl();
}

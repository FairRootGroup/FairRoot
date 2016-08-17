// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIgeobasedIG__GeoBaseDict

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
#include "FairGeoAssembly.h"
#include "FairGeoCone.h"
#include "FairGeoCons.h"
#include "FairGeoEltu.h"
#include "FairGeoBuilder.h"
#include "FairGeoInterface.h"
#include "FairGeoIo.h"
#include "FairGeoLoader.h"
#include "FairGeoMatrix.h"
#include "FairGeoMedia.h"
#include "FairGeoMedium.h"
#include "FairGeoNode.h"
#include "FairGeoOldAsciiIo.h"
#include "FairGeoPcon.h"
#include "FairGeoPgon.h"
#include "FairGeoRootBuilder.h"
#include "FairGeoRotation.h"
#include "FairGeoSet.h"
#include "FairGeoShapes.h"
#include "FairGeoSphe.h"
#include "FairGeoTransform.h"
#include "FairGeoTrap.h"
#include "FairGeoTrd1.h"
#include "FairGeoTube.h"
#include "FairGeoTubs.h"
#include "FairGeoTorus.h"
#include "FairGeoVector.h"
#include "FairGeoVolume.h"
#include "FairGeoCompositeVolume.h"
#include "FairGeoAsciiIo.h"
#include "FairGeoBrik.h"
#include "FairGeoBasicShape.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairGeoAssembly(void *p = 0);
   static void *newArray_FairGeoAssembly(Long_t size, void *p);
   static void delete_FairGeoAssembly(void *p);
   static void deleteArray_FairGeoAssembly(void *p);
   static void destruct_FairGeoAssembly(void *p);
   static void streamer_FairGeoAssembly(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoAssembly*)
   {
      ::FairGeoAssembly *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoAssembly >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoAssembly", ::FairGeoAssembly::Class_Version(), "invalid", 27,
                  typeid(::FairGeoAssembly), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoAssembly::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoAssembly) );
      instance.SetNew(&new_FairGeoAssembly);
      instance.SetNewArray(&newArray_FairGeoAssembly);
      instance.SetDelete(&delete_FairGeoAssembly);
      instance.SetDeleteArray(&deleteArray_FairGeoAssembly);
      instance.SetDestructor(&destruct_FairGeoAssembly);
      instance.SetStreamerFunc(&streamer_FairGeoAssembly);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoAssembly*)
   {
      return GenerateInitInstanceLocal((::FairGeoAssembly*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoAssembly*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoMedium(void *p = 0);
   static void *newArray_FairGeoMedium(Long_t size, void *p);
   static void delete_FairGeoMedium(void *p);
   static void deleteArray_FairGeoMedium(void *p);
   static void destruct_FairGeoMedium(void *p);
   static void streamer_FairGeoMedium(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoMedium*)
   {
      ::FairGeoMedium *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoMedium >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoMedium", ::FairGeoMedium::Class_Version(), "invalid", 516,
                  typeid(::FairGeoMedium), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoMedium::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoMedium) );
      instance.SetNew(&new_FairGeoMedium);
      instance.SetNewArray(&newArray_FairGeoMedium);
      instance.SetDelete(&delete_FairGeoMedium);
      instance.SetDeleteArray(&deleteArray_FairGeoMedium);
      instance.SetDestructor(&destruct_FairGeoMedium);
      instance.SetStreamerFunc(&streamer_FairGeoMedium);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoMedium*)
   {
      return GenerateInitInstanceLocal((::FairGeoMedium*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoMedium*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoTransform(void *p = 0);
   static void *newArray_FairGeoTransform(Long_t size, void *p);
   static void delete_FairGeoTransform(void *p);
   static void deleteArray_FairGeoTransform(void *p);
   static void destruct_FairGeoTransform(void *p);
   static void streamer_FairGeoTransform(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoTransform*)
   {
      ::FairGeoTransform *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoTransform >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoTransform", ::FairGeoTransform::Class_Version(), "FairGeoTransform.h", 21,
                  typeid(::FairGeoTransform), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoTransform::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoTransform) );
      instance.SetNew(&new_FairGeoTransform);
      instance.SetNewArray(&newArray_FairGeoTransform);
      instance.SetDelete(&delete_FairGeoTransform);
      instance.SetDeleteArray(&deleteArray_FairGeoTransform);
      instance.SetDestructor(&destruct_FairGeoTransform);
      instance.SetStreamerFunc(&streamer_FairGeoTransform);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoTransform*)
   {
      return GenerateInitInstanceLocal((::FairGeoTransform*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoTransform*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoRotation(void *p = 0);
   static void *newArray_FairGeoRotation(Long_t size, void *p);
   static void delete_FairGeoRotation(void *p);
   static void deleteArray_FairGeoRotation(void *p);
   static void destruct_FairGeoRotation(void *p);
   static void streamer_FairGeoRotation(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoRotation*)
   {
      ::FairGeoRotation *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoRotation >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoRotation", ::FairGeoRotation::Class_Version(), "FairGeoRotation.h", 26,
                  typeid(::FairGeoRotation), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoRotation::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoRotation) );
      instance.SetNew(&new_FairGeoRotation);
      instance.SetNewArray(&newArray_FairGeoRotation);
      instance.SetDelete(&delete_FairGeoRotation);
      instance.SetDeleteArray(&deleteArray_FairGeoRotation);
      instance.SetDestructor(&destruct_FairGeoRotation);
      instance.SetStreamerFunc(&streamer_FairGeoRotation);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoRotation*)
   {
      return GenerateInitInstanceLocal((::FairGeoRotation*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoRotation*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoVector(void *p = 0);
   static void *newArray_FairGeoVector(Long_t size, void *p);
   static void delete_FairGeoVector(void *p);
   static void deleteArray_FairGeoVector(void *p);
   static void destruct_FairGeoVector(void *p);
   static void streamer_FairGeoVector(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoVector*)
   {
      ::FairGeoVector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoVector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoVector", ::FairGeoVector::Class_Version(), "FairGeoVector.h", 21,
                  typeid(::FairGeoVector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoVector::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoVector) );
      instance.SetNew(&new_FairGeoVector);
      instance.SetNewArray(&newArray_FairGeoVector);
      instance.SetDelete(&delete_FairGeoVector);
      instance.SetDeleteArray(&deleteArray_FairGeoVector);
      instance.SetDestructor(&destruct_FairGeoVector);
      instance.SetStreamerFunc(&streamer_FairGeoVector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoVector*)
   {
      return GenerateInitInstanceLocal((::FairGeoVector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoVector*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoMatrix(void *p = 0);
   static void *newArray_FairGeoMatrix(Long_t size, void *p);
   static void delete_FairGeoMatrix(void *p);
   static void deleteArray_FairGeoMatrix(void *p);
   static void destruct_FairGeoMatrix(void *p);
   static void streamer_FairGeoMatrix(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoMatrix*)
   {
      ::FairGeoMatrix *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoMatrix >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoMatrix", ::FairGeoMatrix::Class_Version(), "invalid", 422,
                  typeid(::FairGeoMatrix), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoMatrix::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoMatrix) );
      instance.SetNew(&new_FairGeoMatrix);
      instance.SetNewArray(&newArray_FairGeoMatrix);
      instance.SetDelete(&delete_FairGeoMatrix);
      instance.SetDeleteArray(&deleteArray_FairGeoMatrix);
      instance.SetDestructor(&destruct_FairGeoMatrix);
      instance.SetStreamerFunc(&streamer_FairGeoMatrix);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoMatrix*)
   {
      return GenerateInitInstanceLocal((::FairGeoMatrix*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoMatrix*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoShapes(void *p = 0);
   static void *newArray_FairGeoShapes(Long_t size, void *p);
   static void delete_FairGeoShapes(void *p);
   static void deleteArray_FairGeoShapes(void *p);
   static void destruct_FairGeoShapes(void *p);
   static void streamer_FairGeoShapes(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoShapes*)
   {
      ::FairGeoShapes *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoShapes >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoShapes", ::FairGeoShapes::Class_Version(), "invalid", 1276,
                  typeid(::FairGeoShapes), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoShapes::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoShapes) );
      instance.SetNew(&new_FairGeoShapes);
      instance.SetNewArray(&newArray_FairGeoShapes);
      instance.SetDelete(&delete_FairGeoShapes);
      instance.SetDeleteArray(&deleteArray_FairGeoShapes);
      instance.SetDestructor(&destruct_FairGeoShapes);
      instance.SetStreamerFunc(&streamer_FairGeoShapes);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoShapes*)
   {
      return GenerateInitInstanceLocal((::FairGeoShapes*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoShapes*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoBasicShape(void *p = 0);
   static void *newArray_FairGeoBasicShape(Long_t size, void *p);
   static void delete_FairGeoBasicShape(void *p);
   static void deleteArray_FairGeoBasicShape(void *p);
   static void destruct_FairGeoBasicShape(void *p);
   static void streamer_FairGeoBasicShape(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoBasicShape*)
   {
      ::FairGeoBasicShape *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoBasicShape >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoBasicShape", ::FairGeoBasicShape::Class_Version(), "FairGeoBasicShape.h", 25,
                  typeid(::FairGeoBasicShape), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoBasicShape::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoBasicShape) );
      instance.SetNew(&new_FairGeoBasicShape);
      instance.SetNewArray(&newArray_FairGeoBasicShape);
      instance.SetDelete(&delete_FairGeoBasicShape);
      instance.SetDeleteArray(&deleteArray_FairGeoBasicShape);
      instance.SetDestructor(&destruct_FairGeoBasicShape);
      instance.SetStreamerFunc(&streamer_FairGeoBasicShape);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoBasicShape*)
   {
      return GenerateInitInstanceLocal((::FairGeoBasicShape*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoBasicShape*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoBrik(void *p = 0);
   static void *newArray_FairGeoBrik(Long_t size, void *p);
   static void delete_FairGeoBrik(void *p);
   static void deleteArray_FairGeoBrik(void *p);
   static void destruct_FairGeoBrik(void *p);
   static void streamer_FairGeoBrik(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoBrik*)
   {
      ::FairGeoBrik *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoBrik >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoBrik", ::FairGeoBrik::Class_Version(), "invalid", 2114,
                  typeid(::FairGeoBrik), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoBrik::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoBrik) );
      instance.SetNew(&new_FairGeoBrik);
      instance.SetNewArray(&newArray_FairGeoBrik);
      instance.SetDelete(&delete_FairGeoBrik);
      instance.SetDeleteArray(&deleteArray_FairGeoBrik);
      instance.SetDestructor(&destruct_FairGeoBrik);
      instance.SetStreamerFunc(&streamer_FairGeoBrik);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoBrik*)
   {
      return GenerateInitInstanceLocal((::FairGeoBrik*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoBrik*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoTrap(void *p = 0);
   static void *newArray_FairGeoTrap(Long_t size, void *p);
   static void delete_FairGeoTrap(void *p);
   static void deleteArray_FairGeoTrap(void *p);
   static void destruct_FairGeoTrap(void *p);
   static void streamer_FairGeoTrap(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoTrap*)
   {
      ::FairGeoTrap *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoTrap >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoTrap", ::FairGeoTrap::Class_Version(), "invalid", 1433,
                  typeid(::FairGeoTrap), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoTrap::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoTrap) );
      instance.SetNew(&new_FairGeoTrap);
      instance.SetNewArray(&newArray_FairGeoTrap);
      instance.SetDelete(&delete_FairGeoTrap);
      instance.SetDeleteArray(&deleteArray_FairGeoTrap);
      instance.SetDestructor(&destruct_FairGeoTrap);
      instance.SetStreamerFunc(&streamer_FairGeoTrap);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoTrap*)
   {
      return GenerateInitInstanceLocal((::FairGeoTrap*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoTrap*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoTrd1(void *p = 0);
   static void *newArray_FairGeoTrd1(Long_t size, void *p);
   static void delete_FairGeoTrd1(void *p);
   static void deleteArray_FairGeoTrd1(void *p);
   static void destruct_FairGeoTrd1(void *p);
   static void streamer_FairGeoTrd1(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoTrd1*)
   {
      ::FairGeoTrd1 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoTrd1 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoTrd1", ::FairGeoTrd1::Class_Version(), "invalid", 1468,
                  typeid(::FairGeoTrd1), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoTrd1::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoTrd1) );
      instance.SetNew(&new_FairGeoTrd1);
      instance.SetNewArray(&newArray_FairGeoTrd1);
      instance.SetDelete(&delete_FairGeoTrd1);
      instance.SetDeleteArray(&deleteArray_FairGeoTrd1);
      instance.SetDestructor(&destruct_FairGeoTrd1);
      instance.SetStreamerFunc(&streamer_FairGeoTrd1);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoTrd1*)
   {
      return GenerateInitInstanceLocal((::FairGeoTrd1*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoTrd1*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoPgon(void *p = 0);
   static void *newArray_FairGeoPgon(Long_t size, void *p);
   static void delete_FairGeoPgon(void *p);
   static void deleteArray_FairGeoPgon(void *p);
   static void destruct_FairGeoPgon(void *p);
   static void streamer_FairGeoPgon(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoPgon*)
   {
      ::FairGeoPgon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoPgon >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoPgon", ::FairGeoPgon::Class_Version(), "invalid", 870,
                  typeid(::FairGeoPgon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoPgon::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoPgon) );
      instance.SetNew(&new_FairGeoPgon);
      instance.SetNewArray(&newArray_FairGeoPgon);
      instance.SetDelete(&delete_FairGeoPgon);
      instance.SetDeleteArray(&deleteArray_FairGeoPgon);
      instance.SetDestructor(&destruct_FairGeoPgon);
      instance.SetStreamerFunc(&streamer_FairGeoPgon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoPgon*)
   {
      return GenerateInitInstanceLocal((::FairGeoPgon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoPgon*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoPcon(void *p = 0);
   static void *newArray_FairGeoPcon(Long_t size, void *p);
   static void delete_FairGeoPcon(void *p);
   static void deleteArray_FairGeoPcon(void *p);
   static void destruct_FairGeoPcon(void *p);
   static void streamer_FairGeoPcon(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoPcon*)
   {
      ::FairGeoPcon *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoPcon >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoPcon", ::FairGeoPcon::Class_Version(), "invalid", 829,
                  typeid(::FairGeoPcon), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoPcon::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoPcon) );
      instance.SetNew(&new_FairGeoPcon);
      instance.SetNewArray(&newArray_FairGeoPcon);
      instance.SetDelete(&delete_FairGeoPcon);
      instance.SetDeleteArray(&deleteArray_FairGeoPcon);
      instance.SetDestructor(&destruct_FairGeoPcon);
      instance.SetStreamerFunc(&streamer_FairGeoPcon);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoPcon*)
   {
      return GenerateInitInstanceLocal((::FairGeoPcon*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoPcon*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoTube(void *p = 0);
   static void *newArray_FairGeoTube(Long_t size, void *p);
   static void delete_FairGeoTube(void *p);
   static void deleteArray_FairGeoTube(void *p);
   static void destruct_FairGeoTube(void *p);
   static void streamer_FairGeoTube(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoTube*)
   {
      ::FairGeoTube *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoTube >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoTube", ::FairGeoTube::Class_Version(), "invalid", 1504,
                  typeid(::FairGeoTube), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoTube::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoTube) );
      instance.SetNew(&new_FairGeoTube);
      instance.SetNewArray(&newArray_FairGeoTube);
      instance.SetDelete(&delete_FairGeoTube);
      instance.SetDeleteArray(&deleteArray_FairGeoTube);
      instance.SetDestructor(&destruct_FairGeoTube);
      instance.SetStreamerFunc(&streamer_FairGeoTube);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoTube*)
   {
      return GenerateInitInstanceLocal((::FairGeoTube*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoTube*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoTubs(void *p = 0);
   static void *newArray_FairGeoTubs(Long_t size, void *p);
   static void delete_FairGeoTubs(void *p);
   static void deleteArray_FairGeoTubs(void *p);
   static void destruct_FairGeoTubs(void *p);
   static void streamer_FairGeoTubs(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoTubs*)
   {
      ::FairGeoTubs *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoTubs >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoTubs", ::FairGeoTubs::Class_Version(), "invalid", 1541,
                  typeid(::FairGeoTubs), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoTubs::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoTubs) );
      instance.SetNew(&new_FairGeoTubs);
      instance.SetNewArray(&newArray_FairGeoTubs);
      instance.SetDelete(&delete_FairGeoTubs);
      instance.SetDeleteArray(&deleteArray_FairGeoTubs);
      instance.SetDestructor(&destruct_FairGeoTubs);
      instance.SetStreamerFunc(&streamer_FairGeoTubs);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoTubs*)
   {
      return GenerateInitInstanceLocal((::FairGeoTubs*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoTubs*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoCone(void *p = 0);
   static void *newArray_FairGeoCone(Long_t size, void *p);
   static void delete_FairGeoCone(void *p);
   static void deleteArray_FairGeoCone(void *p);
   static void destruct_FairGeoCone(void *p);
   static void streamer_FairGeoCone(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoCone*)
   {
      ::FairGeoCone *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoCone >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoCone", ::FairGeoCone::Class_Version(), "invalid", 71,
                  typeid(::FairGeoCone), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoCone::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoCone) );
      instance.SetNew(&new_FairGeoCone);
      instance.SetNewArray(&newArray_FairGeoCone);
      instance.SetDelete(&delete_FairGeoCone);
      instance.SetDeleteArray(&deleteArray_FairGeoCone);
      instance.SetDestructor(&destruct_FairGeoCone);
      instance.SetStreamerFunc(&streamer_FairGeoCone);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoCone*)
   {
      return GenerateInitInstanceLocal((::FairGeoCone*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoCone*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoCons(void *p = 0);
   static void *newArray_FairGeoCons(Long_t size, void *p);
   static void delete_FairGeoCons(void *p);
   static void deleteArray_FairGeoCons(void *p);
   static void destruct_FairGeoCons(void *p);
   static void streamer_FairGeoCons(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoCons*)
   {
      ::FairGeoCons *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoCons >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoCons", ::FairGeoCons::Class_Version(), "invalid", 111,
                  typeid(::FairGeoCons), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoCons::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoCons) );
      instance.SetNew(&new_FairGeoCons);
      instance.SetNewArray(&newArray_FairGeoCons);
      instance.SetDelete(&delete_FairGeoCons);
      instance.SetDeleteArray(&deleteArray_FairGeoCons);
      instance.SetDestructor(&destruct_FairGeoCons);
      instance.SetStreamerFunc(&streamer_FairGeoCons);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoCons*)
   {
      return GenerateInitInstanceLocal((::FairGeoCons*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoCons*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoSphe(void *p = 0);
   static void *newArray_FairGeoSphe(Long_t size, void *p);
   static void delete_FairGeoSphe(void *p);
   static void deleteArray_FairGeoSphe(void *p);
   static void destruct_FairGeoSphe(void *p);
   static void streamer_FairGeoSphe(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoSphe*)
   {
      ::FairGeoSphe *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoSphe >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoSphe", ::FairGeoSphe::Class_Version(), "invalid", 1321,
                  typeid(::FairGeoSphe), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoSphe::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoSphe) );
      instance.SetNew(&new_FairGeoSphe);
      instance.SetNewArray(&newArray_FairGeoSphe);
      instance.SetDelete(&delete_FairGeoSphe);
      instance.SetDeleteArray(&deleteArray_FairGeoSphe);
      instance.SetDestructor(&destruct_FairGeoSphe);
      instance.SetStreamerFunc(&streamer_FairGeoSphe);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoSphe*)
   {
      return GenerateInitInstanceLocal((::FairGeoSphe*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoSphe*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoEltu(void *p = 0);
   static void *newArray_FairGeoEltu(Long_t size, void *p);
   static void delete_FairGeoEltu(void *p);
   static void deleteArray_FairGeoEltu(void *p);
   static void destruct_FairGeoEltu(void *p);
   static void streamer_FairGeoEltu(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoEltu*)
   {
      ::FairGeoEltu *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoEltu >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoEltu", ::FairGeoEltu::Class_Version(), "invalid", 152,
                  typeid(::FairGeoEltu), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoEltu::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoEltu) );
      instance.SetNew(&new_FairGeoEltu);
      instance.SetNewArray(&newArray_FairGeoEltu);
      instance.SetDelete(&delete_FairGeoEltu);
      instance.SetDeleteArray(&deleteArray_FairGeoEltu);
      instance.SetDestructor(&destruct_FairGeoEltu);
      instance.SetStreamerFunc(&streamer_FairGeoEltu);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoEltu*)
   {
      return GenerateInitInstanceLocal((::FairGeoEltu*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoEltu*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoTorus(void *p = 0);
   static void *newArray_FairGeoTorus(Long_t size, void *p);
   static void delete_FairGeoTorus(void *p);
   static void deleteArray_FairGeoTorus(void *p);
   static void destruct_FairGeoTorus(void *p);
   static void streamer_FairGeoTorus(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoTorus*)
   {
      ::FairGeoTorus *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoTorus >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoTorus", ::FairGeoTorus::Class_Version(), "invalid", 1578,
                  typeid(::FairGeoTorus), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoTorus::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoTorus) );
      instance.SetNew(&new_FairGeoTorus);
      instance.SetNewArray(&newArray_FairGeoTorus);
      instance.SetDelete(&delete_FairGeoTorus);
      instance.SetDeleteArray(&deleteArray_FairGeoTorus);
      instance.SetDestructor(&destruct_FairGeoTorus);
      instance.SetStreamerFunc(&streamer_FairGeoTorus);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoTorus*)
   {
      return GenerateInitInstanceLocal((::FairGeoTorus*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoTorus*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoVolume(void *p = 0);
   static void *newArray_FairGeoVolume(Long_t size, void *p);
   static void delete_FairGeoVolume(void *p);
   static void deleteArray_FairGeoVolume(void *p);
   static void destruct_FairGeoVolume(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoVolume*)
   {
      ::FairGeoVolume *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoVolume >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoVolume", ::FairGeoVolume::Class_Version(), "FairGeoVolume.h", 27,
                  typeid(::FairGeoVolume), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoVolume::Dictionary, isa_proxy, 4,
                  sizeof(::FairGeoVolume) );
      instance.SetNew(&new_FairGeoVolume);
      instance.SetNewArray(&newArray_FairGeoVolume);
      instance.SetDelete(&delete_FairGeoVolume);
      instance.SetDeleteArray(&deleteArray_FairGeoVolume);
      instance.SetDestructor(&destruct_FairGeoVolume);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoVolume*)
   {
      return GenerateInitInstanceLocal((::FairGeoVolume*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoVolume*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoCompositeVolume(void *p = 0);
   static void *newArray_FairGeoCompositeVolume(Long_t size, void *p);
   static void delete_FairGeoCompositeVolume(void *p);
   static void deleteArray_FairGeoCompositeVolume(void *p);
   static void destruct_FairGeoCompositeVolume(void *p);
   static void streamer_FairGeoCompositeVolume(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoCompositeVolume*)
   {
      ::FairGeoCompositeVolume *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoCompositeVolume >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoCompositeVolume", ::FairGeoCompositeVolume::Class_Version(), "invalid", 2014,
                  typeid(::FairGeoCompositeVolume), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoCompositeVolume::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoCompositeVolume) );
      instance.SetNew(&new_FairGeoCompositeVolume);
      instance.SetNewArray(&newArray_FairGeoCompositeVolume);
      instance.SetDelete(&delete_FairGeoCompositeVolume);
      instance.SetDeleteArray(&deleteArray_FairGeoCompositeVolume);
      instance.SetDestructor(&destruct_FairGeoCompositeVolume);
      instance.SetStreamerFunc(&streamer_FairGeoCompositeVolume);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoCompositeVolume*)
   {
      return GenerateInitInstanceLocal((::FairGeoCompositeVolume*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoCompositeVolume*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoNode(void *p = 0);
   static void *newArray_FairGeoNode(Long_t size, void *p);
   static void delete_FairGeoNode(void *p);
   static void deleteArray_FairGeoNode(void *p);
   static void destruct_FairGeoNode(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoNode*)
   {
      ::FairGeoNode *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoNode >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoNode", ::FairGeoNode::Class_Version(), "invalid", 632,
                  typeid(::FairGeoNode), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoNode::Dictionary, isa_proxy, 4,
                  sizeof(::FairGeoNode) );
      instance.SetNew(&new_FairGeoNode);
      instance.SetNewArray(&newArray_FairGeoNode);
      instance.SetDelete(&delete_FairGeoNode);
      instance.SetDeleteArray(&deleteArray_FairGeoNode);
      instance.SetDestructor(&destruct_FairGeoNode);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoNode*)
   {
      return GenerateInitInstanceLocal((::FairGeoNode*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoNode*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairGeoSet(void *p);
   static void deleteArray_FairGeoSet(void *p);
   static void destruct_FairGeoSet(void *p);
   static void streamer_FairGeoSet(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoSet*)
   {
      ::FairGeoSet *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoSet >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoSet", ::FairGeoSet::Class_Version(), "invalid", 1173,
                  typeid(::FairGeoSet), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoSet::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoSet) );
      instance.SetDelete(&delete_FairGeoSet);
      instance.SetDeleteArray(&deleteArray_FairGeoSet);
      instance.SetDestructor(&destruct_FairGeoSet);
      instance.SetStreamerFunc(&streamer_FairGeoSet);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoSet*)
   {
      return GenerateInitInstanceLocal((::FairGeoSet*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoSet*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoInterface(void *p = 0);
   static void *newArray_FairGeoInterface(Long_t size, void *p);
   static void delete_FairGeoInterface(void *p);
   static void deleteArray_FairGeoInterface(void *p);
   static void destruct_FairGeoInterface(void *p);
   static void streamer_FairGeoInterface(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoInterface*)
   {
      ::FairGeoInterface *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoInterface >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoInterface", ::FairGeoInterface::Class_Version(), "invalid", 250,
                  typeid(::FairGeoInterface), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoInterface::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoInterface) );
      instance.SetNew(&new_FairGeoInterface);
      instance.SetNewArray(&newArray_FairGeoInterface);
      instance.SetDelete(&delete_FairGeoInterface);
      instance.SetDeleteArray(&deleteArray_FairGeoInterface);
      instance.SetDestructor(&destruct_FairGeoInterface);
      instance.SetStreamerFunc(&streamer_FairGeoInterface);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoInterface*)
   {
      return GenerateInitInstanceLocal((::FairGeoInterface*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoInterface*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairGeoBuilder(void *p);
   static void deleteArray_FairGeoBuilder(void *p);
   static void destruct_FairGeoBuilder(void *p);
   static void streamer_FairGeoBuilder(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoBuilder*)
   {
      ::FairGeoBuilder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoBuilder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoBuilder", ::FairGeoBuilder::Class_Version(), "invalid", 189,
                  typeid(::FairGeoBuilder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoBuilder::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoBuilder) );
      instance.SetDelete(&delete_FairGeoBuilder);
      instance.SetDeleteArray(&deleteArray_FairGeoBuilder);
      instance.SetDestructor(&destruct_FairGeoBuilder);
      instance.SetStreamerFunc(&streamer_FairGeoBuilder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoBuilder*)
   {
      return GenerateInitInstanceLocal((::FairGeoBuilder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoBuilder*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoRootBuilder(void *p = 0);
   static void *newArray_FairGeoRootBuilder(Long_t size, void *p);
   static void delete_FairGeoRootBuilder(void *p);
   static void deleteArray_FairGeoRootBuilder(void *p);
   static void destruct_FairGeoRootBuilder(void *p);
   static void streamer_FairGeoRootBuilder(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoRootBuilder*)
   {
      ::FairGeoRootBuilder *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoRootBuilder >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoRootBuilder", ::FairGeoRootBuilder::Class_Version(), "invalid", 908,
                  typeid(::FairGeoRootBuilder), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoRootBuilder::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoRootBuilder) );
      instance.SetNew(&new_FairGeoRootBuilder);
      instance.SetNewArray(&newArray_FairGeoRootBuilder);
      instance.SetDelete(&delete_FairGeoRootBuilder);
      instance.SetDeleteArray(&deleteArray_FairGeoRootBuilder);
      instance.SetDestructor(&destruct_FairGeoRootBuilder);
      instance.SetStreamerFunc(&streamer_FairGeoRootBuilder);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoRootBuilder*)
   {
      return GenerateInitInstanceLocal((::FairGeoRootBuilder*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoRootBuilder*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairGeoIo(void *p);
   static void deleteArray_FairGeoIo(void *p);
   static void destruct_FairGeoIo(void *p);
   static void streamer_FairGeoIo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoIo*)
   {
      ::FairGeoIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoIo", ::FairGeoIo::Class_Version(), "invalid", 330,
                  typeid(::FairGeoIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoIo::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoIo) );
      instance.SetDelete(&delete_FairGeoIo);
      instance.SetDeleteArray(&deleteArray_FairGeoIo);
      instance.SetDestructor(&destruct_FairGeoIo);
      instance.SetStreamerFunc(&streamer_FairGeoIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoIo*)
   {
      return GenerateInitInstanceLocal((::FairGeoIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoAsciiIo(void *p = 0);
   static void *newArray_FairGeoAsciiIo(Long_t size, void *p);
   static void delete_FairGeoAsciiIo(void *p);
   static void deleteArray_FairGeoAsciiIo(void *p);
   static void destruct_FairGeoAsciiIo(void *p);
   static void streamer_FairGeoAsciiIo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoAsciiIo*)
   {
      ::FairGeoAsciiIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoAsciiIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoAsciiIo", ::FairGeoAsciiIo::Class_Version(), "invalid", 2062,
                  typeid(::FairGeoAsciiIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoAsciiIo::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoAsciiIo) );
      instance.SetNew(&new_FairGeoAsciiIo);
      instance.SetNewArray(&newArray_FairGeoAsciiIo);
      instance.SetDelete(&delete_FairGeoAsciiIo);
      instance.SetDeleteArray(&deleteArray_FairGeoAsciiIo);
      instance.SetDestructor(&destruct_FairGeoAsciiIo);
      instance.SetStreamerFunc(&streamer_FairGeoAsciiIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoAsciiIo*)
   {
      return GenerateInitInstanceLocal((::FairGeoAsciiIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoAsciiIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoOldAsciiIo(void *p = 0);
   static void *newArray_FairGeoOldAsciiIo(Long_t size, void *p);
   static void delete_FairGeoOldAsciiIo(void *p);
   static void deleteArray_FairGeoOldAsciiIo(void *p);
   static void destruct_FairGeoOldAsciiIo(void *p);
   static void streamer_FairGeoOldAsciiIo(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoOldAsciiIo*)
   {
      ::FairGeoOldAsciiIo *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoOldAsciiIo >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoOldAsciiIo", ::FairGeoOldAsciiIo::Class_Version(), "invalid", 769,
                  typeid(::FairGeoOldAsciiIo), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoOldAsciiIo::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoOldAsciiIo) );
      instance.SetNew(&new_FairGeoOldAsciiIo);
      instance.SetNewArray(&newArray_FairGeoOldAsciiIo);
      instance.SetDelete(&delete_FairGeoOldAsciiIo);
      instance.SetDeleteArray(&deleteArray_FairGeoOldAsciiIo);
      instance.SetDestructor(&destruct_FairGeoOldAsciiIo);
      instance.SetStreamerFunc(&streamer_FairGeoOldAsciiIo);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoOldAsciiIo*)
   {
      return GenerateInitInstanceLocal((::FairGeoOldAsciiIo*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoOldAsciiIo*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoMedia(void *p = 0);
   static void *newArray_FairGeoMedia(Long_t size, void *p);
   static void delete_FairGeoMedia(void *p);
   static void deleteArray_FairGeoMedia(void *p);
   static void destruct_FairGeoMedia(void *p);
   static void streamer_FairGeoMedia(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoMedia*)
   {
      ::FairGeoMedia *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoMedia >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoMedia", ::FairGeoMedia::Class_Version(), "invalid", 463,
                  typeid(::FairGeoMedia), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoMedia::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoMedia) );
      instance.SetNew(&new_FairGeoMedia);
      instance.SetNewArray(&newArray_FairGeoMedia);
      instance.SetDelete(&delete_FairGeoMedia);
      instance.SetDeleteArray(&deleteArray_FairGeoMedia);
      instance.SetDestructor(&destruct_FairGeoMedia);
      instance.SetStreamerFunc(&streamer_FairGeoMedia);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoMedia*)
   {
      return GenerateInitInstanceLocal((::FairGeoMedia*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoMedia*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairGeoLoader(void *p = 0);
   static void *newArray_FairGeoLoader(Long_t size, void *p);
   static void delete_FairGeoLoader(void *p);
   static void deleteArray_FairGeoLoader(void *p);
   static void destruct_FairGeoLoader(void *p);
   static void streamer_FairGeoLoader(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairGeoLoader*)
   {
      ::FairGeoLoader *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairGeoLoader >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairGeoLoader", ::FairGeoLoader::Class_Version(), "invalid", 380,
                  typeid(::FairGeoLoader), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairGeoLoader::Dictionary, isa_proxy, 16,
                  sizeof(::FairGeoLoader) );
      instance.SetNew(&new_FairGeoLoader);
      instance.SetNewArray(&newArray_FairGeoLoader);
      instance.SetDelete(&delete_FairGeoLoader);
      instance.SetDeleteArray(&deleteArray_FairGeoLoader);
      instance.SetDestructor(&destruct_FairGeoLoader);
      instance.SetStreamerFunc(&streamer_FairGeoLoader);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairGeoLoader*)
   {
      return GenerateInitInstanceLocal((::FairGeoLoader*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairGeoLoader*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairGeoAssembly::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoAssembly::Class_Name()
{
   return "FairGeoAssembly";
}

//______________________________________________________________________________
const char *FairGeoAssembly::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoAssembly*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoAssembly::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoAssembly*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoAssembly::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoAssembly*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoAssembly::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoAssembly*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoMedium::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoMedium::Class_Name()
{
   return "FairGeoMedium";
}

//______________________________________________________________________________
const char *FairGeoMedium::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMedium*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoMedium::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMedium*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoMedium::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMedium*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoMedium::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMedium*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoTransform::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoTransform::Class_Name()
{
   return "FairGeoTransform";
}

//______________________________________________________________________________
const char *FairGeoTransform::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTransform*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoTransform::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTransform*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoTransform::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTransform*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoTransform::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTransform*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoRotation::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoRotation::Class_Name()
{
   return "FairGeoRotation";
}

//______________________________________________________________________________
const char *FairGeoRotation::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoRotation*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoRotation::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoRotation*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoRotation::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoRotation*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoRotation::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoRotation*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoVector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoVector::Class_Name()
{
   return "FairGeoVector";
}

//______________________________________________________________________________
const char *FairGeoVector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoVector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoVector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoVector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoVector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoVector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoVector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoVector*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoMatrix::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoMatrix::Class_Name()
{
   return "FairGeoMatrix";
}

//______________________________________________________________________________
const char *FairGeoMatrix::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMatrix*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoMatrix::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMatrix*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoMatrix::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMatrix*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoMatrix::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMatrix*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoShapes::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoShapes::Class_Name()
{
   return "FairGeoShapes";
}

//______________________________________________________________________________
const char *FairGeoShapes::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoShapes*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoShapes::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoShapes*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoShapes::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoShapes*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoShapes::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoShapes*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoBasicShape::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoBasicShape::Class_Name()
{
   return "FairGeoBasicShape";
}

//______________________________________________________________________________
const char *FairGeoBasicShape::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBasicShape*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoBasicShape::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBasicShape*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoBasicShape::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBasicShape*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoBasicShape::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBasicShape*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoBrik::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoBrik::Class_Name()
{
   return "FairGeoBrik";
}

//______________________________________________________________________________
const char *FairGeoBrik::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBrik*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoBrik::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBrik*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoBrik::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBrik*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoBrik::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBrik*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoTrap::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoTrap::Class_Name()
{
   return "FairGeoTrap";
}

//______________________________________________________________________________
const char *FairGeoTrap::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTrap*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoTrap::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTrap*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoTrap::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTrap*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoTrap::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTrap*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoTrd1::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoTrd1::Class_Name()
{
   return "FairGeoTrd1";
}

//______________________________________________________________________________
const char *FairGeoTrd1::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTrd1*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoTrd1::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTrd1*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoTrd1::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTrd1*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoTrd1::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTrd1*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoPgon::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoPgon::Class_Name()
{
   return "FairGeoPgon";
}

//______________________________________________________________________________
const char *FairGeoPgon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPgon*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoPgon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPgon*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoPgon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPgon*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoPgon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPgon*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoPcon::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoPcon::Class_Name()
{
   return "FairGeoPcon";
}

//______________________________________________________________________________
const char *FairGeoPcon::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPcon*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoPcon::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPcon*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoPcon::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPcon*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoPcon::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoPcon*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoTube::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoTube::Class_Name()
{
   return "FairGeoTube";
}

//______________________________________________________________________________
const char *FairGeoTube::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTube*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoTube::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTube*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoTube::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTube*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoTube::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTube*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoTubs::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoTubs::Class_Name()
{
   return "FairGeoTubs";
}

//______________________________________________________________________________
const char *FairGeoTubs::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTubs*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoTubs::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTubs*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoTubs::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTubs*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoTubs::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTubs*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoCone::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoCone::Class_Name()
{
   return "FairGeoCone";
}

//______________________________________________________________________________
const char *FairGeoCone::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCone*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoCone::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCone*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoCone::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCone*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoCone::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCone*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoCons::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoCons::Class_Name()
{
   return "FairGeoCons";
}

//______________________________________________________________________________
const char *FairGeoCons::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCons*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoCons::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCons*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoCons::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCons*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoCons::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCons*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoSphe::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoSphe::Class_Name()
{
   return "FairGeoSphe";
}

//______________________________________________________________________________
const char *FairGeoSphe::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoSphe*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoSphe::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoSphe*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoSphe::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoSphe*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoSphe::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoSphe*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoEltu::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoEltu::Class_Name()
{
   return "FairGeoEltu";
}

//______________________________________________________________________________
const char *FairGeoEltu::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoEltu*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoEltu::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoEltu*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoEltu::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoEltu*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoEltu::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoEltu*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoTorus::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoTorus::Class_Name()
{
   return "FairGeoTorus";
}

//______________________________________________________________________________
const char *FairGeoTorus::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTorus*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoTorus::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTorus*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoTorus::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTorus*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoTorus::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoTorus*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoVolume::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoVolume::Class_Name()
{
   return "FairGeoVolume";
}

//______________________________________________________________________________
const char *FairGeoVolume::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoVolume*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoVolume::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoVolume*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoVolume::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoVolume*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoVolume::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoVolume*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoCompositeVolume::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoCompositeVolume::Class_Name()
{
   return "FairGeoCompositeVolume";
}

//______________________________________________________________________________
const char *FairGeoCompositeVolume::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCompositeVolume*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoCompositeVolume::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCompositeVolume*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoCompositeVolume::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCompositeVolume*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoCompositeVolume::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoCompositeVolume*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoNode::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoNode::Class_Name()
{
   return "FairGeoNode";
}

//______________________________________________________________________________
const char *FairGeoNode::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoNode*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoNode::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoNode*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoNode::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoNode*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoNode::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoNode*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoSet::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoSet::Class_Name()
{
   return "FairGeoSet";
}

//______________________________________________________________________________
const char *FairGeoSet::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoSet*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoSet::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoSet*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoSet::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoSet*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoSet::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoSet*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoInterface::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoInterface::Class_Name()
{
   return "FairGeoInterface";
}

//______________________________________________________________________________
const char *FairGeoInterface::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoInterface*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoInterface::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoInterface*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoInterface::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoInterface*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoInterface::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoInterface*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoBuilder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoBuilder::Class_Name()
{
   return "FairGeoBuilder";
}

//______________________________________________________________________________
const char *FairGeoBuilder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBuilder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoBuilder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBuilder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoBuilder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBuilder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoBuilder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoBuilder*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoRootBuilder::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoRootBuilder::Class_Name()
{
   return "FairGeoRootBuilder";
}

//______________________________________________________________________________
const char *FairGeoRootBuilder::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoRootBuilder*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoRootBuilder::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoRootBuilder*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoRootBuilder::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoRootBuilder*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoRootBuilder::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoRootBuilder*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoIo::Class_Name()
{
   return "FairGeoIo";
}

//______________________________________________________________________________
const char *FairGeoIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoAsciiIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoAsciiIo::Class_Name()
{
   return "FairGeoAsciiIo";
}

//______________________________________________________________________________
const char *FairGeoAsciiIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoAsciiIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoAsciiIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoAsciiIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoAsciiIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoAsciiIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoAsciiIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoAsciiIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoOldAsciiIo::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoOldAsciiIo::Class_Name()
{
   return "FairGeoOldAsciiIo";
}

//______________________________________________________________________________
const char *FairGeoOldAsciiIo::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoOldAsciiIo*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoOldAsciiIo::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoOldAsciiIo*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoOldAsciiIo::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoOldAsciiIo*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoOldAsciiIo::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoOldAsciiIo*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoMedia::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoMedia::Class_Name()
{
   return "FairGeoMedia";
}

//______________________________________________________________________________
const char *FairGeoMedia::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMedia*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoMedia::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMedia*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoMedia::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMedia*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoMedia::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoMedia*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairGeoLoader::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairGeoLoader::Class_Name()
{
   return "FairGeoLoader";
}

//______________________________________________________________________________
const char *FairGeoLoader::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoLoader*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairGeoLoader::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairGeoLoader*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairGeoLoader::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoLoader*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairGeoLoader::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairGeoLoader*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairGeoAssembly::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoAssembly.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoAssembly(void *p) {
      return  p ? new(p) ::FairGeoAssembly : new ::FairGeoAssembly;
   }
   static void *newArray_FairGeoAssembly(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoAssembly[nElements] : new ::FairGeoAssembly[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoAssembly(void *p) {
      delete ((::FairGeoAssembly*)p);
   }
   static void deleteArray_FairGeoAssembly(void *p) {
      delete [] ((::FairGeoAssembly*)p);
   }
   static void destruct_FairGeoAssembly(void *p) {
      typedef ::FairGeoAssembly current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoAssembly(TBuffer &buf, void *obj) {
      ((::FairGeoAssembly*)obj)->::FairGeoAssembly::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoAssembly

//______________________________________________________________________________
void FairGeoMedium::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoMedium.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b >> medId;
      R__b >> autoflag;
      R__b >> nComponents;
      R__b >> weightFac;
      delete [] ca;
      ca = new Double_t[nComponents];
      R__b.ReadFastArray(ca,nComponents);
      delete [] cz;
      cz = new Double_t[nComponents];
      R__b.ReadFastArray(cz,nComponents);
      delete [] cw;
      cw = new Double_t[nComponents];
      R__b.ReadFastArray(cw,nComponents);
      R__b >> density;
      R__b >> radLen;
      R__b >> sensFlag;
      R__b >> fldFlag;
      R__b >> fld;
      R__b >> epsil;
      R__b >> madfld;
      R__b >> maxstep;
      R__b >> maxde;
      R__b >> minstep;
      R__b >> npckov;
      delete [] ppckov;
      ppckov = new Double_t[npckov];
      R__b.ReadFastArray(ppckov,npckov);
      delete [] absco;
      absco = new Double_t[npckov];
      R__b.ReadFastArray(absco,npckov);
      delete [] effic;
      effic = new Double_t[npckov];
      R__b.ReadFastArray(effic,npckov);
      delete [] rindex;
      rindex = new Double_t[npckov];
      R__b.ReadFastArray(rindex,npckov);
      R__b.CheckByteCount(R__s, R__c, FairGeoMedium::IsA());
   } else {
      R__c = R__b.WriteVersion(FairGeoMedium::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b << medId;
      R__b << autoflag;
      R__b << nComponents;
      R__b << weightFac;
      R__b.WriteFastArray(ca,nComponents);
      R__b.WriteFastArray(cz,nComponents);
      R__b.WriteFastArray(cw,nComponents);
      R__b << density;
      R__b << radLen;
      R__b << sensFlag;
      R__b << fldFlag;
      R__b << fld;
      R__b << epsil;
      R__b << madfld;
      R__b << maxstep;
      R__b << maxde;
      R__b << minstep;
      R__b << npckov;
      R__b.WriteFastArray(ppckov,npckov);
      R__b.WriteFastArray(absco,npckov);
      R__b.WriteFastArray(effic,npckov);
      R__b.WriteFastArray(rindex,npckov);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoMedium(void *p) {
      return  p ? new(p) ::FairGeoMedium : new ::FairGeoMedium;
   }
   static void *newArray_FairGeoMedium(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoMedium[nElements] : new ::FairGeoMedium[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoMedium(void *p) {
      delete ((::FairGeoMedium*)p);
   }
   static void deleteArray_FairGeoMedium(void *p) {
      delete [] ((::FairGeoMedium*)p);
   }
   static void destruct_FairGeoMedium(void *p) {
      typedef ::FairGeoMedium current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoMedium(TBuffer &buf, void *obj) {
      ((::FairGeoMedium*)obj)->::FairGeoMedium::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoMedium

//______________________________________________________________________________
void FairGeoTransform::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoTransform.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      rot.Streamer(R__b);
      trans.Streamer(R__b);
      trans_cm.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, FairGeoTransform::IsA());
   } else {
      R__c = R__b.WriteVersion(FairGeoTransform::IsA(), kTRUE);
      TObject::Streamer(R__b);
      rot.Streamer(R__b);
      trans.Streamer(R__b);
      trans_cm.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoTransform(void *p) {
      return  p ? new(p) ::FairGeoTransform : new ::FairGeoTransform;
   }
   static void *newArray_FairGeoTransform(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoTransform[nElements] : new ::FairGeoTransform[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoTransform(void *p) {
      delete ((::FairGeoTransform*)p);
   }
   static void deleteArray_FairGeoTransform(void *p) {
      delete [] ((::FairGeoTransform*)p);
   }
   static void destruct_FairGeoTransform(void *p) {
      typedef ::FairGeoTransform current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoTransform(TBuffer &buf, void *obj) {
      ((::FairGeoTransform*)obj)->::FairGeoTransform::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoTransform

//______________________________________________________________________________
void FairGeoRotation::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoRotation.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b.ReadStaticArray((double*)rot);
      R__b.CheckByteCount(R__s, R__c, FairGeoRotation::IsA());
   } else {
      R__c = R__b.WriteVersion(FairGeoRotation::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b.WriteArray(rot, 9);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoRotation(void *p) {
      return  p ? new(p) ::FairGeoRotation : new ::FairGeoRotation;
   }
   static void *newArray_FairGeoRotation(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoRotation[nElements] : new ::FairGeoRotation[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoRotation(void *p) {
      delete ((::FairGeoRotation*)p);
   }
   static void deleteArray_FairGeoRotation(void *p) {
      delete [] ((::FairGeoRotation*)p);
   }
   static void destruct_FairGeoRotation(void *p) {
      typedef ::FairGeoRotation current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoRotation(TBuffer &buf, void *obj) {
      ((::FairGeoRotation*)obj)->::FairGeoRotation::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoRotation

//______________________________________________________________________________
void FairGeoVector::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoVector.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> x;
      R__b >> y;
      R__b >> z;
      R__b.CheckByteCount(R__s, R__c, FairGeoVector::IsA());
   } else {
      R__c = R__b.WriteVersion(FairGeoVector::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << x;
      R__b << y;
      R__b << z;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoVector(void *p) {
      return  p ? new(p) ::FairGeoVector : new ::FairGeoVector;
   }
   static void *newArray_FairGeoVector(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoVector[nElements] : new ::FairGeoVector[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoVector(void *p) {
      delete ((::FairGeoVector*)p);
   }
   static void deleteArray_FairGeoVector(void *p) {
      delete [] ((::FairGeoVector*)p);
   }
   static void destruct_FairGeoVector(void *p) {
      typedef ::FairGeoVector current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoVector(TBuffer &buf, void *obj) {
      ((::FairGeoVector*)obj)->::FairGeoVector::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoVector

//______________________________________________________________________________
void FairGeoMatrix::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoMatrix.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoMatrix(void *p) {
      return  p ? new(p) ::FairGeoMatrix : new ::FairGeoMatrix;
   }
   static void *newArray_FairGeoMatrix(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoMatrix[nElements] : new ::FairGeoMatrix[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoMatrix(void *p) {
      delete ((::FairGeoMatrix*)p);
   }
   static void deleteArray_FairGeoMatrix(void *p) {
      delete [] ((::FairGeoMatrix*)p);
   }
   static void destruct_FairGeoMatrix(void *p) {
      typedef ::FairGeoMatrix current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoMatrix(TBuffer &buf, void *obj) {
      ((::FairGeoMatrix*)obj)->::FairGeoMatrix::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoMatrix

//______________________________________________________________________________
void FairGeoShapes::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoShapes.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoShapes(void *p) {
      return  p ? new(p) ::FairGeoShapes : new ::FairGeoShapes;
   }
   static void *newArray_FairGeoShapes(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoShapes[nElements] : new ::FairGeoShapes[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoShapes(void *p) {
      delete ((::FairGeoShapes*)p);
   }
   static void deleteArray_FairGeoShapes(void *p) {
      delete [] ((::FairGeoShapes*)p);
   }
   static void destruct_FairGeoShapes(void *p) {
      typedef ::FairGeoShapes current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoShapes(TBuffer &buf, void *obj) {
      ((::FairGeoShapes*)obj)->::FairGeoShapes::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoShapes

//______________________________________________________________________________
void FairGeoBasicShape::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoBasicShape.

   TNamed::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoBasicShape(void *p) {
      return  p ? new(p) ::FairGeoBasicShape : new ::FairGeoBasicShape;
   }
   static void *newArray_FairGeoBasicShape(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoBasicShape[nElements] : new ::FairGeoBasicShape[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoBasicShape(void *p) {
      delete ((::FairGeoBasicShape*)p);
   }
   static void deleteArray_FairGeoBasicShape(void *p) {
      delete [] ((::FairGeoBasicShape*)p);
   }
   static void destruct_FairGeoBasicShape(void *p) {
      typedef ::FairGeoBasicShape current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoBasicShape(TBuffer &buf, void *obj) {
      ((::FairGeoBasicShape*)obj)->::FairGeoBasicShape::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoBasicShape

//______________________________________________________________________________
void FairGeoBrik::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoBrik.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoBrik(void *p) {
      return  p ? new(p) ::FairGeoBrik : new ::FairGeoBrik;
   }
   static void *newArray_FairGeoBrik(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoBrik[nElements] : new ::FairGeoBrik[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoBrik(void *p) {
      delete ((::FairGeoBrik*)p);
   }
   static void deleteArray_FairGeoBrik(void *p) {
      delete [] ((::FairGeoBrik*)p);
   }
   static void destruct_FairGeoBrik(void *p) {
      typedef ::FairGeoBrik current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoBrik(TBuffer &buf, void *obj) {
      ((::FairGeoBrik*)obj)->::FairGeoBrik::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoBrik

//______________________________________________________________________________
void FairGeoTrap::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoTrap.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoTrap(void *p) {
      return  p ? new(p) ::FairGeoTrap : new ::FairGeoTrap;
   }
   static void *newArray_FairGeoTrap(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoTrap[nElements] : new ::FairGeoTrap[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoTrap(void *p) {
      delete ((::FairGeoTrap*)p);
   }
   static void deleteArray_FairGeoTrap(void *p) {
      delete [] ((::FairGeoTrap*)p);
   }
   static void destruct_FairGeoTrap(void *p) {
      typedef ::FairGeoTrap current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoTrap(TBuffer &buf, void *obj) {
      ((::FairGeoTrap*)obj)->::FairGeoTrap::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoTrap

//______________________________________________________________________________
void FairGeoTrd1::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoTrd1.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoTrd1(void *p) {
      return  p ? new(p) ::FairGeoTrd1 : new ::FairGeoTrd1;
   }
   static void *newArray_FairGeoTrd1(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoTrd1[nElements] : new ::FairGeoTrd1[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoTrd1(void *p) {
      delete ((::FairGeoTrd1*)p);
   }
   static void deleteArray_FairGeoTrd1(void *p) {
      delete [] ((::FairGeoTrd1*)p);
   }
   static void destruct_FairGeoTrd1(void *p) {
      typedef ::FairGeoTrd1 current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoTrd1(TBuffer &buf, void *obj) {
      ((::FairGeoTrd1*)obj)->::FairGeoTrd1::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoTrd1

//______________________________________________________________________________
void FairGeoPgon::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoPgon.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoPgon(void *p) {
      return  p ? new(p) ::FairGeoPgon : new ::FairGeoPgon;
   }
   static void *newArray_FairGeoPgon(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoPgon[nElements] : new ::FairGeoPgon[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoPgon(void *p) {
      delete ((::FairGeoPgon*)p);
   }
   static void deleteArray_FairGeoPgon(void *p) {
      delete [] ((::FairGeoPgon*)p);
   }
   static void destruct_FairGeoPgon(void *p) {
      typedef ::FairGeoPgon current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoPgon(TBuffer &buf, void *obj) {
      ((::FairGeoPgon*)obj)->::FairGeoPgon::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoPgon

//______________________________________________________________________________
void FairGeoPcon::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoPcon.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoPcon(void *p) {
      return  p ? new(p) ::FairGeoPcon : new ::FairGeoPcon;
   }
   static void *newArray_FairGeoPcon(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoPcon[nElements] : new ::FairGeoPcon[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoPcon(void *p) {
      delete ((::FairGeoPcon*)p);
   }
   static void deleteArray_FairGeoPcon(void *p) {
      delete [] ((::FairGeoPcon*)p);
   }
   static void destruct_FairGeoPcon(void *p) {
      typedef ::FairGeoPcon current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoPcon(TBuffer &buf, void *obj) {
      ((::FairGeoPcon*)obj)->::FairGeoPcon::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoPcon

//______________________________________________________________________________
void FairGeoTube::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoTube.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoTube(void *p) {
      return  p ? new(p) ::FairGeoTube : new ::FairGeoTube;
   }
   static void *newArray_FairGeoTube(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoTube[nElements] : new ::FairGeoTube[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoTube(void *p) {
      delete ((::FairGeoTube*)p);
   }
   static void deleteArray_FairGeoTube(void *p) {
      delete [] ((::FairGeoTube*)p);
   }
   static void destruct_FairGeoTube(void *p) {
      typedef ::FairGeoTube current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoTube(TBuffer &buf, void *obj) {
      ((::FairGeoTube*)obj)->::FairGeoTube::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoTube

//______________________________________________________________________________
void FairGeoTubs::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoTubs.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoTubs(void *p) {
      return  p ? new(p) ::FairGeoTubs : new ::FairGeoTubs;
   }
   static void *newArray_FairGeoTubs(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoTubs[nElements] : new ::FairGeoTubs[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoTubs(void *p) {
      delete ((::FairGeoTubs*)p);
   }
   static void deleteArray_FairGeoTubs(void *p) {
      delete [] ((::FairGeoTubs*)p);
   }
   static void destruct_FairGeoTubs(void *p) {
      typedef ::FairGeoTubs current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoTubs(TBuffer &buf, void *obj) {
      ((::FairGeoTubs*)obj)->::FairGeoTubs::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoTubs

//______________________________________________________________________________
void FairGeoCone::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoCone.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoCone(void *p) {
      return  p ? new(p) ::FairGeoCone : new ::FairGeoCone;
   }
   static void *newArray_FairGeoCone(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoCone[nElements] : new ::FairGeoCone[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoCone(void *p) {
      delete ((::FairGeoCone*)p);
   }
   static void deleteArray_FairGeoCone(void *p) {
      delete [] ((::FairGeoCone*)p);
   }
   static void destruct_FairGeoCone(void *p) {
      typedef ::FairGeoCone current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoCone(TBuffer &buf, void *obj) {
      ((::FairGeoCone*)obj)->::FairGeoCone::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoCone

//______________________________________________________________________________
void FairGeoCons::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoCons.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoCons(void *p) {
      return  p ? new(p) ::FairGeoCons : new ::FairGeoCons;
   }
   static void *newArray_FairGeoCons(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoCons[nElements] : new ::FairGeoCons[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoCons(void *p) {
      delete ((::FairGeoCons*)p);
   }
   static void deleteArray_FairGeoCons(void *p) {
      delete [] ((::FairGeoCons*)p);
   }
   static void destruct_FairGeoCons(void *p) {
      typedef ::FairGeoCons current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoCons(TBuffer &buf, void *obj) {
      ((::FairGeoCons*)obj)->::FairGeoCons::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoCons

//______________________________________________________________________________
void FairGeoSphe::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoSphe.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoSphe(void *p) {
      return  p ? new(p) ::FairGeoSphe : new ::FairGeoSphe;
   }
   static void *newArray_FairGeoSphe(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoSphe[nElements] : new ::FairGeoSphe[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoSphe(void *p) {
      delete ((::FairGeoSphe*)p);
   }
   static void deleteArray_FairGeoSphe(void *p) {
      delete [] ((::FairGeoSphe*)p);
   }
   static void destruct_FairGeoSphe(void *p) {
      typedef ::FairGeoSphe current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoSphe(TBuffer &buf, void *obj) {
      ((::FairGeoSphe*)obj)->::FairGeoSphe::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoSphe

//______________________________________________________________________________
void FairGeoEltu::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoEltu.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoEltu(void *p) {
      return  p ? new(p) ::FairGeoEltu : new ::FairGeoEltu;
   }
   static void *newArray_FairGeoEltu(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoEltu[nElements] : new ::FairGeoEltu[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoEltu(void *p) {
      delete ((::FairGeoEltu*)p);
   }
   static void deleteArray_FairGeoEltu(void *p) {
      delete [] ((::FairGeoEltu*)p);
   }
   static void destruct_FairGeoEltu(void *p) {
      typedef ::FairGeoEltu current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoEltu(TBuffer &buf, void *obj) {
      ((::FairGeoEltu*)obj)->::FairGeoEltu::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoEltu

//______________________________________________________________________________
void FairGeoTorus::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoTorus.

   FairGeoBasicShape::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoTorus(void *p) {
      return  p ? new(p) ::FairGeoTorus : new ::FairGeoTorus;
   }
   static void *newArray_FairGeoTorus(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoTorus[nElements] : new ::FairGeoTorus[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoTorus(void *p) {
      delete ((::FairGeoTorus*)p);
   }
   static void deleteArray_FairGeoTorus(void *p) {
      delete [] ((::FairGeoTorus*)p);
   }
   static void destruct_FairGeoTorus(void *p) {
      typedef ::FairGeoTorus current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoTorus(TBuffer &buf, void *obj) {
      ((::FairGeoTorus*)obj)->::FairGeoTorus::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoTorus

//______________________________________________________________________________
void FairGeoVolume::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoVolume.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGeoVolume::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGeoVolume::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoVolume(void *p) {
      return  p ? new(p) ::FairGeoVolume : new ::FairGeoVolume;
   }
   static void *newArray_FairGeoVolume(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoVolume[nElements] : new ::FairGeoVolume[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoVolume(void *p) {
      delete ((::FairGeoVolume*)p);
   }
   static void deleteArray_FairGeoVolume(void *p) {
      delete [] ((::FairGeoVolume*)p);
   }
   static void destruct_FairGeoVolume(void *p) {
      typedef ::FairGeoVolume current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGeoVolume

//______________________________________________________________________________
void FairGeoCompositeVolume::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoCompositeVolume.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      FairGeoVolume::Streamer(R__b);
      R__b >> components;
      R__b.CheckByteCount(R__s, R__c, FairGeoCompositeVolume::IsA());
   } else {
      R__c = R__b.WriteVersion(FairGeoCompositeVolume::IsA(), kTRUE);
      FairGeoVolume::Streamer(R__b);
      R__b << components;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoCompositeVolume(void *p) {
      return  p ? new(p) ::FairGeoCompositeVolume : new ::FairGeoCompositeVolume;
   }
   static void *newArray_FairGeoCompositeVolume(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoCompositeVolume[nElements] : new ::FairGeoCompositeVolume[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoCompositeVolume(void *p) {
      delete ((::FairGeoCompositeVolume*)p);
   }
   static void deleteArray_FairGeoCompositeVolume(void *p) {
      delete [] ((::FairGeoCompositeVolume*)p);
   }
   static void destruct_FairGeoCompositeVolume(void *p) {
      typedef ::FairGeoCompositeVolume current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoCompositeVolume(TBuffer &buf, void *obj) {
      ((::FairGeoCompositeVolume*)obj)->::FairGeoCompositeVolume::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoCompositeVolume

//______________________________________________________________________________
void FairGeoNode::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoNode.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairGeoNode::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairGeoNode::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoNode(void *p) {
      return  p ? new(p) ::FairGeoNode : new ::FairGeoNode;
   }
   static void *newArray_FairGeoNode(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoNode[nElements] : new ::FairGeoNode[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoNode(void *p) {
      delete ((::FairGeoNode*)p);
   }
   static void deleteArray_FairGeoNode(void *p) {
      delete [] ((::FairGeoNode*)p);
   }
   static void destruct_FairGeoNode(void *p) {
      typedef ::FairGeoNode current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairGeoNode

//______________________________________________________________________________
void FairGeoSet::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoSet.

   TNamed::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairGeoSet(void *p) {
      delete ((::FairGeoSet*)p);
   }
   static void deleteArray_FairGeoSet(void *p) {
      delete [] ((::FairGeoSet*)p);
   }
   static void destruct_FairGeoSet(void *p) {
      typedef ::FairGeoSet current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoSet(TBuffer &buf, void *obj) {
      ((::FairGeoSet*)obj)->::FairGeoSet::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoSet

//______________________________________________________________________________
void FairGeoInterface::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoInterface.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoInterface(void *p) {
      return  p ? new(p) ::FairGeoInterface : new ::FairGeoInterface;
   }
   static void *newArray_FairGeoInterface(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoInterface[nElements] : new ::FairGeoInterface[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoInterface(void *p) {
      delete ((::FairGeoInterface*)p);
   }
   static void deleteArray_FairGeoInterface(void *p) {
      delete [] ((::FairGeoInterface*)p);
   }
   static void destruct_FairGeoInterface(void *p) {
      typedef ::FairGeoInterface current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoInterface(TBuffer &buf, void *obj) {
      ((::FairGeoInterface*)obj)->::FairGeoInterface::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoInterface

//______________________________________________________________________________
void FairGeoBuilder::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoBuilder.

   TNamed::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairGeoBuilder(void *p) {
      delete ((::FairGeoBuilder*)p);
   }
   static void deleteArray_FairGeoBuilder(void *p) {
      delete [] ((::FairGeoBuilder*)p);
   }
   static void destruct_FairGeoBuilder(void *p) {
      typedef ::FairGeoBuilder current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoBuilder(TBuffer &buf, void *obj) {
      ((::FairGeoBuilder*)obj)->::FairGeoBuilder::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoBuilder

//______________________________________________________________________________
void FairGeoRootBuilder::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoRootBuilder.

   FairGeoBuilder::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoRootBuilder(void *p) {
      return  p ? new(p) ::FairGeoRootBuilder : new ::FairGeoRootBuilder;
   }
   static void *newArray_FairGeoRootBuilder(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoRootBuilder[nElements] : new ::FairGeoRootBuilder[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoRootBuilder(void *p) {
      delete ((::FairGeoRootBuilder*)p);
   }
   static void deleteArray_FairGeoRootBuilder(void *p) {
      delete [] ((::FairGeoRootBuilder*)p);
   }
   static void destruct_FairGeoRootBuilder(void *p) {
      typedef ::FairGeoRootBuilder current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoRootBuilder(TBuffer &buf, void *obj) {
      ((::FairGeoRootBuilder*)obj)->::FairGeoRootBuilder::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoRootBuilder

//______________________________________________________________________________
void FairGeoIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoIo.

   TObject::Streamer(R__b);
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairGeoIo(void *p) {
      delete ((::FairGeoIo*)p);
   }
   static void deleteArray_FairGeoIo(void *p) {
      delete [] ((::FairGeoIo*)p);
   }
   static void destruct_FairGeoIo(void *p) {
      typedef ::FairGeoIo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoIo(TBuffer &buf, void *obj) {
      ((::FairGeoIo*)obj)->::FairGeoIo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoIo

//______________________________________________________________________________
void FairGeoAsciiIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoAsciiIo.

   FairGeoIo::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoAsciiIo(void *p) {
      return  p ? new(p) ::FairGeoAsciiIo : new ::FairGeoAsciiIo;
   }
   static void *newArray_FairGeoAsciiIo(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoAsciiIo[nElements] : new ::FairGeoAsciiIo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoAsciiIo(void *p) {
      delete ((::FairGeoAsciiIo*)p);
   }
   static void deleteArray_FairGeoAsciiIo(void *p) {
      delete [] ((::FairGeoAsciiIo*)p);
   }
   static void destruct_FairGeoAsciiIo(void *p) {
      typedef ::FairGeoAsciiIo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoAsciiIo(TBuffer &buf, void *obj) {
      ((::FairGeoAsciiIo*)obj)->::FairGeoAsciiIo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoAsciiIo

//______________________________________________________________________________
void FairGeoOldAsciiIo::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoOldAsciiIo.

   FairGeoIo::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoOldAsciiIo(void *p) {
      return  p ? new(p) ::FairGeoOldAsciiIo : new ::FairGeoOldAsciiIo;
   }
   static void *newArray_FairGeoOldAsciiIo(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoOldAsciiIo[nElements] : new ::FairGeoOldAsciiIo[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoOldAsciiIo(void *p) {
      delete ((::FairGeoOldAsciiIo*)p);
   }
   static void deleteArray_FairGeoOldAsciiIo(void *p) {
      delete [] ((::FairGeoOldAsciiIo*)p);
   }
   static void destruct_FairGeoOldAsciiIo(void *p) {
      typedef ::FairGeoOldAsciiIo current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoOldAsciiIo(TBuffer &buf, void *obj) {
      ((::FairGeoOldAsciiIo*)obj)->::FairGeoOldAsciiIo::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoOldAsciiIo

//______________________________________________________________________________
void FairGeoMedia::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoMedia.

   TNamed::Streamer(R__b);
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoMedia(void *p) {
      return  p ? new(p) ::FairGeoMedia : new ::FairGeoMedia;
   }
   static void *newArray_FairGeoMedia(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoMedia[nElements] : new ::FairGeoMedia[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoMedia(void *p) {
      delete ((::FairGeoMedia*)p);
   }
   static void deleteArray_FairGeoMedia(void *p) {
      delete [] ((::FairGeoMedia*)p);
   }
   static void destruct_FairGeoMedia(void *p) {
      typedef ::FairGeoMedia current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoMedia(TBuffer &buf, void *obj) {
      ((::FairGeoMedia*)obj)->::FairGeoMedia::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoMedia

//______________________________________________________________________________
void FairGeoLoader::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairGeoLoader.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TNamed::Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, FairGeoLoader::IsA());
   } else {
      R__c = R__b.WriteVersion(FairGeoLoader::IsA(), kTRUE);
      TNamed::Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairGeoLoader(void *p) {
      return  p ? new(p) ::FairGeoLoader : new ::FairGeoLoader;
   }
   static void *newArray_FairGeoLoader(Long_t nElements, void *p) {
      return p ? new(p) ::FairGeoLoader[nElements] : new ::FairGeoLoader[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairGeoLoader(void *p) {
      delete ((::FairGeoLoader*)p);
   }
   static void deleteArray_FairGeoLoader(void *p) {
      delete [] ((::FairGeoLoader*)p);
   }
   static void destruct_FairGeoLoader(void *p) {
      typedef ::FairGeoLoader current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_FairGeoLoader(TBuffer &buf, void *obj) {
      ((::FairGeoLoader*)obj)->::FairGeoLoader::Streamer(buf);
   }
} // end of namespace ROOT for class ::FairGeoLoader

namespace {
  void TriggerDictionaryInitialization_G__GeoBaseDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/Users/turany/development/FairRoot/fairtools",
"/Users/turany/development/FairRoot/geobase",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/geobase/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__GeoBaseDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(class for geometry shape ASSEMBLY)ATTRDUMP"))) FairGeoAssembly;
class FairGeoMedium;
class __attribute__((annotate("$clingAutoload$FairGeoVolume.h")))  FairGeoTransform;
class __attribute__((annotate("$clingAutoload$FairGeoVolume.h")))  FairGeoRotation;
class __attribute__((annotate(R"ATTRDUMP(vector with 3 components)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FairGeoVector.h")))  FairGeoVector;
class FairGeoMatrix;
class FairGeoShapes;
class __attribute__((annotate(R"ATTRDUMP(base class for all shapes)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$FairGeoBasicShape.h")))  FairGeoBasicShape;
class __attribute__((annotate(R"ATTRDUMP(class for geometry shape BOX or BRIK)ATTRDUMP"))) FairGeoBrik;
class __attribute__((annotate(R"ATTRDUMP(class for geometry shape TRAP)ATTRDUMP"))) FairGeoTrap;
class __attribute__((annotate(R"ATTRDUMP(class for geometry shape TRD1)ATTRDUMP"))) FairGeoTrd1;
class FairGeoPgon;
class FairGeoPcon;
class __attribute__((annotate(R"ATTRDUMP(class for geometry shape TUBE)ATTRDUMP"))) FairGeoTube;
class __attribute__((annotate(R"ATTRDUMP(class for geometry shape TUBS)ATTRDUMP"))) FairGeoTubs;
class FairGeoCone;
class FairGeoCons;
class FairGeoSphe;
class FairGeoEltu;
class __attribute__((annotate(R"ATTRDUMP(class for geometry shape TORUS)ATTRDUMP"))) FairGeoTorus;
class __attribute__((annotate("$clingAutoload$FairGeoVolume.h")))  FairGeoVolume;
class FairGeoCompositeVolume;
class FairGeoNode;
class FairGeoSet;
class FairGeoInterface;
class FairGeoBuilder;
class FairGeoRootBuilder;
class FairGeoIo;
class __attribute__((annotate(R"ATTRDUMP(Class for geometry I/O from ASCII file)ATTRDUMP"))) FairGeoAsciiIo;
class FairGeoOldAsciiIo;
class FairGeoMedia;
class FairGeoLoader;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__GeoBaseDict dictionary payload"

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
#ifndef FAIRGEOASSEMBLY_H
#define FAIRGEOASSEMBLY_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoAssembly::Class, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

class FairGeoAssembly : public FairGeoBasicShape
{
  public:
    FairGeoAssembly();
    ~FairGeoAssembly();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream* pFile,FairGeoVolume* volu);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);

    ClassDef(FairGeoAssembly,0) // class for geometry shape ASSEMBLY
};

#endif  /* !FAIRGEOASSEMBLY_H */


/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOCONE_H
#define FAIRGEOCONE_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoCone::Class, Bool_t, etc

#include <iosfwd>                       // for fstream


class FairGeoTransform;
class FairGeoVolume;
class TArrayD;
/**
 * class for geometry shape CONE
 * @author ilse koenig
 */
class FairGeoCone : public FairGeoBasicShape
{
  public:
    FairGeoCone();
    ~FairGeoCone();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoCone,0) //
};

#endif  /* !FAIRGEOCONE_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOCONS_H
#define FAIRGEOCONS_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoCons::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;
/**
 * class for geometry shape CONS
 * @author ilse koenig
 */
class FairGeoCons : public FairGeoBasicShape
{
  public:
    FairGeoCons();
    ~FairGeoCons();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoCons,0) //
};

#endif  /* !FAIRGEOCONS_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOELTU_H
#define FAIRGEOELTU_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoEltu::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

/**
 * class for geometry shape ELTU
 * @author Ilse  koenig
 */
class FairGeoEltu : public FairGeoBasicShape
{
  public:
    FairGeoEltu();
    ~FairGeoEltu();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoEltu,0) //
};

#endif  /* !FAIRGEOELTU_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOBUILDER_H
#define FAIRGEOBUILDER_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for Int_t, etc

class FairGeoNode;
class FairGeoMedium;

/**
 * abstract base class for geometry builders
 * @author ilse koenig
 */
class FairGeoBuilder : public TNamed
{
  protected:
    Int_t nRot;  // number of defined rotations
    Int_t nMed;  // number of defined media

    FairGeoBuilder();
    FairGeoBuilder(const char* name,const char* title);
  public:
    virtual ~FairGeoBuilder() {}
    virtual Bool_t createNode(FairGeoNode*, Int_t hadFormat =0)=0;
    virtual Int_t createMedium(FairGeoMedium*)=0;
    virtual void finalize() {}
    inline const Int_t& GetNMedia() const { return nMed; }
    inline void SetNMedia(const Int_t& nmed) { nMed = nmed; }
    ClassDef(FairGeoBuilder,0)
};

#endif /* !FAIRGEOBUILDER_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOINTERFACE_H
#define FAIRGEOINTERFACE_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Bool_t, kFALSE, Int_t, etc
#include "TString.h"                    // for TString

class FairGeoIo;
class FairGeoSet;
class FairGeoMedia;
class FairGeoShapes;
class FairGeoBuilder;
class TObjArray;
class TList;

enum EHGeoDetPart {
  kFairGeoCave   =  0,
  kFairGeoPipe   =  1,
  kFairGeoTarget =  2,
  kFairGeoMagnet =  3,
  kFairGeoRich   =  4,
  kFairGeoSts    =  5,
  kFairGeoTrd    =  6,
  kFairGeoTof    =  7,
  kFairGeoEcal   =  8
};


/**
 * Class to manage geometry for simulations
 * @author Ilse koenig
 * @author M. Al-Turany
 */
class FairGeoInterface : public TObject
{
    FairGeoIo*      fileInput;   /** ASCII file I/O */
    FairGeoIo*      oraInput;    /** Oracle input */
    FairGeoIo*      output;      /** Oracle output */
    Int_t         nSets;       /** number of geometry sets (detector parts) */
    Int_t         nActualSets; /** number of set in actual geometry */
    TObjArray*    sets;        /** array of geometry  sets */
    FairGeoMedia*   media;       /** list of media */
    FairGeoShapes*  shapes;      /** list of shapes */
    TList*        masterNodes; /** list of mother nodes used by several sets */
    TString       setupFile;   /** file with detector setups (subsets) */
    FairGeoBuilder* geoBuilder;  /** actually used geometry builder */
  public:
    FairGeoInterface();
    ~FairGeoInterface();
    void setOracleInput(FairGeoIo* p) {oraInput=p;}
    void setOutput(FairGeoIo* p) {output=p;}
    void setGeomBuilder(FairGeoBuilder* p) {geoBuilder=p;}
    FairGeoIo* getFileInput() { return fileInput; }
    FairGeoIo* getOraInput() { return oraInput; }
    FairGeoIo* getOutput() { return output; }
    FairGeoShapes* getShapes() { return shapes; }
    FairGeoMedia* getMedia() { return media; }
    TList* getMasterNodes() { return masterNodes; }
    void addInputFile(const char*);
    void addGeoModule(FairGeoSet*);
    void setMediaFile(const char* file);
    FairGeoSet* findSet(const char*);
    Bool_t readSet(FairGeoSet*);
    Bool_t writeSet(FairGeoSet*);
    Bool_t writeSet(FairGeoSet*,const char*);
    Bool_t createSet(FairGeoSet*);
    void deleteSet(FairGeoSet* pSet);
    Bool_t readMedia();
    Bool_t writeMedia();
    Bool_t writeMedia(const char*);
    Bool_t readAll();
    Bool_t writeAll();
    Bool_t createAll(Bool_t withCleanup=kFALSE);
    Bool_t createGeometry(Bool_t withCleanup=kFALSE);
    Bool_t readGeomConfig(const char*);
    void addSetupFile(const char* f) {setupFile=f;}
    Bool_t readSetupFile();
    void print();
    void SetNoOfSets(Int_t n) {nSets=n;} //
  private:
    FairGeoInterface(const FairGeoInterface&);
    FairGeoInterface& operator=(const FairGeoInterface&);

    FairGeoIo* connectInput(const char*);
    Bool_t connectOutput(const char*);

    ClassDef(FairGeoInterface,0) //
};

#endif /* !FAIRGEOINTERFACE_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOIO_H
#define FAIRGEOIO_H

#include "TObject.h"                    // for TObject

#include "Rtypes.h"                     // for Bool_t, FairGeoIo::Class, etc

class FairGeoMedia;
class FairGeoSet;
class FairGeoInterface;

/**
 * Abstract base class for geometry I/O
 * @author Ilse Koenig
 */
class FairGeoIo : public TObject
{
  public:
    virtual Bool_t open(const char*,const Text_t* status="in")=0;
    virtual void close()=0;
    virtual void print()=0;
    virtual Bool_t isOpen()=0;
    virtual Bool_t isWritable()=0;
    virtual Bool_t read(FairGeoMedia*)=0;
    virtual Bool_t read(FairGeoSet*,FairGeoMedia*)=0;
    virtual Bool_t write(FairGeoMedia*)=0;
    virtual Bool_t write(FairGeoSet*)=0;
    virtual Bool_t readGeomConfig(FairGeoInterface*)=0;
    virtual Bool_t setSimulRefRun(const char*)=0;
    virtual Bool_t setHistoryDate(const char*)=0;
  private:
    ClassDef(FairGeoIo,0) //
};

#endif  /* !FAIRGEOIO_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/***************************************************************************
                          FairGeoLoader.h  -  description
                             -------------------
    begin                : Thu Jun 17 2004
    copyright            : (C) 2004 by turany
    email                : m.al-turany@gsi.de
 ***************************************************************************/


#ifndef FairGeoLOADER_H
#define FairGeoLOADER_H

#include "TNamed.h"                     // for TNamed

#include "Rtypes.h"                     // for FairGeoLoader::Class, etc

class FairGeoInterface;
class FairGeoBuilder;
/**New Geometry Loader, this loader handel the Hades geometry description
 * @author Ilse koenig
 * @author M. Al-Turany*/

class FairGeoLoader : public TNamed
{
  public:
    FairGeoLoader(const char* Name, const char* title);
    FairGeoLoader();
    virtual ~FairGeoLoader();
    FairGeoInterface* getGeoInterface() {return fInterface;}
    FairGeoBuilder*   getGeoBuilder() {return   fGeoBuilder; }
    /** static access method*/
    static FairGeoLoader* Instance();

  private:
    FairGeoLoader(const FairGeoLoader&);
    FairGeoLoader& operator=(const FairGeoLoader&);
    static FairGeoLoader*  fgInstance;//!  /**Singleton instance*/
    FairGeoInterface*    fInterface; //!  /** Hades Geometry Interface*/
    FairGeoBuilder*    fGeoBuilder; //!   /**Geometry builder*/
    ClassDef(FairGeoLoader,1)

};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOMATRIX_H
#define FAIRGEOMATRIX_H

#include "TObject.h"                    // for TObject

#include "FairGeoVector.h"              // for FairGeoVector

#include "Rtypes.h"                     // for Double_t, etc

/**
 * @author Ilse koenig
 */
class FairGeoMatrix : public TObject
{
  protected:
    Double_t fM[9];
  public:
    FairGeoMatrix(void);
    ~FairGeoMatrix(void);
    Double_t& operator()(Int_t i,Int_t j) { return fM[i*3+j]; }
    Double_t det(void);
    FairGeoVector operator*(FairGeoVector& v);
    FairGeoMatrix& operator/=(Double_t d);
    ClassDef(FairGeoMatrix,0)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOMEDIA_H
#define FAIRGEOMEDIA_H

#include "TNamed.h"                     // for TNamed

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoMedia::Class, etc
#include "TString.h"                    // for TString

#include <iosfwd>                       // for fstream

class FairGeoMedium;
class TList;

/**
 * Class for materials and media
 * @author Ilse koenig
 */
class FairGeoMedia : public TNamed
{
  private:
    TList* media;           /** list of media */
    TString inputFile;      /** name of input file or Oracle */
    TString author;         /** author of the media version */
    TString description;    /** description of the version */
  public:
    FairGeoMedia();
    ~FairGeoMedia();
    void setInputFile(const char* file) { inputFile=file; }
    const char* getInputFile() { return inputFile; }
    void addMedium(FairGeoMedium* m);
    FairGeoMedium* getMedium(const char*);
    TList* getListOfMedia() {return media;}
    void read(std::fstream&);
    void print();
    void list();
    void write(std::fstream&);
    void setAuthor(TString& s) {author=s;}
    void setDescription(TString& s) {description=s;}
    TString& getAuthor() {return author;}
    TString& getDescription() {return description;}
  private:
    FairGeoMedia(const FairGeoMedia&);
    FairGeoMedia& operator=(const FairGeoMedia&);

    ClassDef(FairGeoMedia,0) //
};

#endif /* !FAIRGEOMEDIA_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOMEDIUM_H
#define FAIRGEOMEDIUM_H

#include "TNamed.h"                     // for TNamed

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Double_t, Int_t, Bool_t, etc

#include <fstream>                      // for fstream

/**
 * Class for tracking medium
 * @author ilse koenig
 */
class FairGeoMedium  : public TNamed
{
  private:
    Int_t     medId;       /** Unique number for the material and the medium */
    Int_t     autoflag;    /** Flag for default values of madfld .. minstep*/
    Int_t     nComponents; /** Number of material components */
    Int_t     weightFac;   /** Factor for weights (1: relative w., -1: w. by number of atoms)*/
    Double_t* ca;         //[nComponents] /** Atomic weights for the components*/
    Double_t* cz;         //[nComponents] /** Atomic numbers for the components*/
    Double_t* cw;         //[nComponents] /** Weights of the components in a mixture*/
    Double_t  density;     /** Density in g cm(**-3)*/
    Double_t  radLen;      /** Radiation lenght*/
    Int_t     sensFlag;    /** Sensitivity flag*/
    Int_t     fldFlag;     /** Field flag*/
    Double_t  fld;         /** Maximum field value in kilogauss*/
    Double_t  epsil;       /** Boundary crossing precision*/
    Double_t  madfld;      /** Maximum angular deviation due to field*/
    Double_t  maxstep;     /** Maximum step permitted*/
    Double_t  maxde;       /** Maximum fractional energy loss*/
    Double_t  minstep;     /** Minimum value for step*/
    Int_t     npckov;      /** Number of optical parameters for Cerenkov*/
    Double_t* ppckov;     //[npckov]  /** Photon momentum*/
    Double_t* absco;      //[npckov] /** Absoption length*/
    Double_t* effic;      //[npckov] /** Detection efficiency*/
    Double_t* rindex;     //[npckov] /** Refraction index*/
  public:
    FairGeoMedium(const char* name="");
    FairGeoMedium& operator=(const FairGeoMedium&) {return *this;}
    ~FairGeoMedium();
    void setMediumIndex(Int_t i) {medId=i;}
    Int_t getMediumIndex() {return medId;}
    void setAutoFlag(Int_t i) {autoflag=i;}
    Int_t getAutoFlag() {return autoflag;}
    void setNComponents(Int_t);
    Int_t getNComponents() {return nComponents;}
    Bool_t setComponent(Int_t,Double_t,Double_t,Double_t w=1.);
    void getComponent(Int_t,Double_t*);
    Int_t getWeightFac() {return weightFac;}
    void setDensity(Double_t d) {density=d;}
    Double_t getDensity() {return density;}
    void setRadiationLength(Double_t l) {radLen=l;}
    Double_t getRadiationLength() {return radLen;}
    void setNpckov(Int_t);
    Int_t getNpckov() {return npckov;}
    Bool_t setCerenkovPar(Int_t,Double_t,Double_t,Double_t,Double_t);
    void getCerenkovPar(Int_t,Double_t*);
    void setMediumPar(Int_t,Int_t,Double_t,Double_t,Double_t maxDeviation=-1.,
                      Double_t maxStep=-1.,Double_t maxDE=-1.,
                      Double_t minStepDouble_t=-1.);
    void getMediumPar(Double_t*);
    inline Bool_t isSensitive();
    Int_t getSensitivityFlag() { return sensFlag;}
    Int_t getFieldFlag() {return fldFlag;}
    Double_t getField() {return fld;}
    Double_t getEpsil() {return epsil;}
    void read(std::fstream&, Int_t autoflag );
    void print();
    void write (std::fstream&);
    Bool_t calcRadiationLength();
  private:
    FairGeoMedium(const FairGeoMedium&);
    //TODO: correct copy constructor for FairGeoMedium
    //    FairGeoMedium& operator=(const FairGeoMedium&);

    ClassDef(FairGeoMedium,1) //
};

inline Bool_t FairGeoMedium::isSensitive()
{
  if (sensFlag) { return kTRUE; }
  else { return kFALSE; }
}

#endif /* !FAIRGEOMEDIUM_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEONODE_H
#define FAIRGEONODE_H

#include "FairGeoVolume.h"              // for FairGeoVolume

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape
#include "FairGeoMedium.h"              // for FairGeoMedium
#include "FairGeoTransform.h"           // for FairGeoTransform

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Bool_t, FairGeoNode::Class, etc
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString

#include <iosfwd>                       // for fstream

class FairGeoVector;
class TArrayD;
class TGeoVolume;
class TList;

enum EFairGeoNodeType {
  kFairGeoElement = 0,
  kFairGeoKeepin  = 1,
  kFairGeoModule  = 2,
  kFairGeoTopNode = 3,
  kFairGeoRefNode = 4
};


/**
 * basic geometry parameters of a volume
 * @author Ilse koenig
 */
class FairGeoNode : public FairGeoVolume
{
  private:
    FairGeoNode(const FairGeoNode&);
    FairGeoNode& operator=(const FairGeoNode&);
  protected:
    Bool_t active;                /** in/out flag for creation */
    FairGeoTransform center;        /** position of the GEANT/ROOT center */
    EFairGeoNodeType volumeType;    /** type of volume */
    Bool_t created;               /** Flag set kTRUE after creation of volume */
    FairGeoNode* copyNode;         /** pointer to the reference volume for a copy */
    TGeoVolume* rootVolume;       /** pointer to the ROOT node */
    FairGeoBasicShape*  pShape;       /** pointer to the shape */
    FairGeoNode* pMother;        //!    /** pointer to the mother volume */
    FairGeoMedium* medium;           /** pointer to medium */
    FairGeoTransform* labTransform; /** Transformation to the LAB system */
    TObjArray* fDaughterList; /** List of daughter Nodes  */
    //const char*   fTruncName;    //
    TString   fTruncName;
  public:
    FairGeoNode();
    FairGeoNode(FairGeoNode&);
    virtual ~FairGeoNode();
    void AddDaughter(FairGeoNode* fNode) {fDaughterList->AddLast(fNode);}
    TObjArray* GetListOfDaughters() {return fDaughterList;}
    EFairGeoNodeType getVolumeType() { return volumeType; }
    Bool_t isTopNode() { return static_cast<Bool_t>((volumeType == kFairGeoTopNode));}
    Bool_t isRefNode() { return static_cast<Bool_t>((volumeType == kFairGeoRefNode));}
    Bool_t isKeepin()  { return static_cast<Bool_t>((volumeType == kFairGeoKeepin));}
    Bool_t isModule()  { return static_cast<Bool_t>((volumeType == kFairGeoModule));}
    Int_t getCopyNo();
    FairGeoBasicShape* getShapePointer() { return pShape; }
    FairGeoNode* getMotherNode() {return pMother;}
    FairGeoMedium* getMedium() {return medium;}
    Bool_t isActive() {return active;}
    FairGeoTransform& getCenterPosition() {return center;}
    TArrayD* getParameters();
    FairGeoTransform* getPosition();
    FairGeoTransform* getLabTransform();
    FairGeoNode* getCopyNode() {return copyNode;}
    TGeoVolume* getRootVolume() {return rootVolume;}
    TList* getTree();
    Bool_t isSensitive();
    Bool_t isCreated() {return created;}
    void setCreated() {created=kTRUE;}
    void setName(const Text_t* s);
    void setVolumeType(EFairGeoNodeType t) {volumeType=t;}
    void setVolumePar(FairGeoNode&);
    void setShape(FairGeoBasicShape* s);
    void setMother(FairGeoNode* s);
    void setMedium(FairGeoMedium* med) {medium=med; }
    void setActive(Bool_t a=kTRUE) {active=a;}
    void setCenterPosition(const FairGeoTransform& t) {center=t;}
    void setCopyNode(FairGeoNode* p) {copyNode=p;}
    void setRootVolume(TGeoVolume* p) {rootVolume=p;}
    FairGeoTransform* calcLabTransform();
    void setLabTransform(FairGeoTransform&);
    Bool_t calcModuleTransform(FairGeoTransform&);
    Bool_t calcRefPos(FairGeoVector&);
    void clear();
    void print();
    Bool_t write(std::fstream&);
    Int_t compare(FairGeoNode&);


    void setTruncName( const char* aName ) { fTruncName = aName;}
    const char* getTruncName() {
      if (fTruncName.Length()>0) { return fTruncName.Data(); }
      else { return GetName(); }
    }

    ClassDef(FairGeoNode,1) //
};

// -------------------- inlines --------------------------

inline void FairGeoNode::setName(const Text_t* s)
{
  // Sets the name of the volume
  fName=s;
  fName.ToUpper();
}

inline void FairGeoNode::setShape(FairGeoBasicShape* s)
{
  // Sets the shape of the volume
  if (s) {
    pShape=s;
    shape=pShape->GetName();
  }
}

inline void FairGeoNode::setMother(FairGeoNode* moth)
{
  // Sets the mother of the volume
  if (moth) {
    pMother=moth;
    mother=pMother->GetName();
    pMother->AddDaughter(this);
  }
}

inline Bool_t FairGeoNode::isSensitive()
{
  if (medium) { return medium->isSensitive(); }
  else { return kFALSE; }
}

#endif /* !FAIRGEONODE_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOOLDASCIIIO_H
#define FAIRGEOOLDASCIIIO_H

#include "FairGeoIo.h"                  // for FairGeoIo

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Bool_t, kFALSE, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairGeoInterface;
class FairGeoMedia;
class FairGeoNode;
class FairGeoSet;

/**
 * Class for geometry I/O from ASCII file in FAIR format
 * @author Ilse koenig
 */
class FairGeoOldAsciiIo: public FairGeoIo
{
    TString  filename;
    TString  filedir;
    Bool_t   writable;
    std::fstream* file;
  public:
    FairGeoOldAsciiIo();
    ~FairGeoOldAsciiIo();
    void setDirectory(const char* fDir) {filedir=fDir;}
    const char* getDirectory() {return filedir.Data();}
    const char* getFilename() {return filename.Data();}
    Bool_t open(const char*,const Text_t* status="in");
    Bool_t isOpen();
    Bool_t isWritable();
    void close();
    void print();
    Bool_t read(FairGeoMedia*) {return kFALSE;}
    Bool_t read(FairGeoSet*,FairGeoMedia*);
    Bool_t write(FairGeoMedia*) {return kFALSE;}
    Bool_t write(FairGeoSet*) {return kFALSE;}
    Bool_t readGeomConfig(FairGeoInterface*) {return kFALSE;}
    Bool_t readDetectorSetup(FairGeoInterface*) {return kFALSE;}
    Bool_t setSimulRefRun(const char*) {return kTRUE;}
    Bool_t setHistoryDate(const char*) {return kTRUE;}
  private:
    Bool_t calculateShapePoints(Double_t*,FairGeoNode*);
    FairGeoOldAsciiIo(const FairGeoOldAsciiIo&);
    FairGeoOldAsciiIo& operator=(const FairGeoOldAsciiIo&);

    ClassDef(FairGeoOldAsciiIo,0) //
};

#endif  /* !FAIRGEOOLDASCIIIO_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOPCON_H
#define FAIRGEOPCON_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

/**
 * class for geometry shape PCON
 * @author Ilse koenig
 */
class FairGeoPcon : public FairGeoBasicShape
{
  public:
    FairGeoPcon();
    ~FairGeoPcon();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoPcon,0) //
};

#endif  /* !FAIRGEOPCON_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOPGON_H
#define FAIRGEOPGON_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

/**
 * class for geometry shape PGON
 * @author Ilse koenig
 */
class FairGeoPgon : public FairGeoBasicShape
{
  public:
    FairGeoPgon();
    ~FairGeoPgon();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoPgon,0) //
};

#endif  /* !FAIRGEOPGON_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOROOTBUILDER_H
#define FAIRGEOROOTBUILDER_H

#include "FairGeoBuilder.h"             // for FairGeoBuilder

#include "Rtypes.h"                     // for FairGeoRootBuilder::Class, etc

class FairGeoMedium;
class FairGeoNode;
class TGeoManager;

/**
 * class to create geometry in ROOT
 * @author M. Al-Turany
 */
class FairGeoRootBuilder : public FairGeoBuilder
{
  private:
    FairGeoRootBuilder(const FairGeoRootBuilder&);
    FairGeoRootBuilder& operator=(const FairGeoRootBuilder&);
  protected:
    TGeoManager* geoManager; // ROOT geometry manager
  public:
    FairGeoRootBuilder();
    FairGeoRootBuilder(const char*,const char*);
    ~FairGeoRootBuilder() {}
    void setGeoManager(TGeoManager* me) {geoManager=me;}
    Bool_t createNode(FairGeoNode*, Int_t hadFormat=0);
    Int_t createMedium(FairGeoMedium*);
    void finalize();
    void checkOverlaps(Double_t ovlp=0.0001);
    ClassDef(FairGeoRootBuilder,0) //
};

#endif /* !FAIRGEOROOTBUILDER_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOROTATION_H
#define FAIRGEOROTATION_H

#include "TObject.h"                    // for TObject

#include "FairGeoVector.h"              // for FairGeoVector

#include "Riosfwd.h"                    // for ostream
#include "Rtypes.h"                     // for Double_t, Int_t, Bool_t, etc

#include <iostream>                     // for operator<<, cout, ostream, etc

class TRotMatrix;

/**
 * rotation matrix
 * @author Ilse koenig
 */
class FairGeoRotation : public TObject
{
  protected:
    Double_t rot[9];
  public:
    inline FairGeoRotation();
    inline FairGeoRotation(const FairGeoRotation&);
    inline FairGeoRotation(const Double_t*);
    FairGeoRotation(const Double_t,const Double_t,const Double_t);
    ~FairGeoRotation() {}
    inline void setMatrix(const Double_t*);
    inline void setMatrix(const Float_t*);
    void setEulerAngles(const Double_t,const Double_t,const Double_t);
    inline void setElement(const Double_t,const Int_t);
    inline Double_t operator () (Int_t) const;
    inline FairGeoRotation& operator = (const FairGeoRotation&);
    inline Bool_t operator == (const FairGeoRotation&);
    inline Bool_t operator != (const FairGeoRotation&);
    inline FairGeoVector operator * (const FairGeoVector&) const;
    inline FairGeoRotation operator * (const FairGeoRotation&) const;
    inline FairGeoRotation& operator *= (const FairGeoRotation&);
    inline FairGeoRotation& transform(const FairGeoRotation&);
    inline Bool_t isUnitMatrix();
    inline FairGeoRotation inverse() const;
    inline FairGeoRotation& invert();
    inline Double_t determinant() const;
    Double_t diff2(const FairGeoRotation&) const;
    inline Double_t getElement(Int_t i,Int_t j) const;
    inline void setUnitMatrix();
    inline void setZero();
    inline void print() const;
    TRotMatrix* createTRotMatrix(const Text_t* name="",const Text_t* title="");

    ClassDef(FairGeoRotation,1) //
};

// -------------------- inlines ---------------------------

inline FairGeoRotation::FairGeoRotation()
  :TObject()
{
  rot[0]=rot[4]=rot[8]=1.;
  rot[1]=rot[2]=rot[3]=rot[5]=rot[6]=rot[7]=0.;
}

inline Double_t FairGeoRotation::operator () (Int_t i) const
{
  if (i>=0 && i<9) { return rot[i]; }
  Error("operator()","bad index");
  return 0;
}

inline FairGeoRotation::FairGeoRotation(const FairGeoRotation& r)
  :TObject(r)
{
  for(Int_t i=0; i<9; i++) { rot[i]=r(i); }
}

inline FairGeoRotation::FairGeoRotation(const Double_t* a)
  :TObject()
{
  for(Int_t i=0; i<9; i++) { rot[i]=a[i]; }
}

inline void FairGeoRotation::setMatrix(const Double_t* a)
{
  for(Int_t i=0; i<9; i++) { rot[i]=a[i]; }
}

inline void FairGeoRotation::setMatrix(const Float_t* a)
{
  for(Int_t i=0; i<9; i++) { rot[i]=a[i]; }
}

inline void FairGeoRotation::setElement(const Double_t a, const Int_t i)
{
  if (i<9) { rot[i]=a; }
}

inline Double_t FairGeoRotation::getElement(Int_t i,Int_t j) const
{
  return rot[i*3+j];
}

inline FairGeoRotation& FairGeoRotation::operator = (const FairGeoRotation& r)
{
  for(Int_t i=0; i<9; i++) { rot[i]=r(i); }
  return *this;
}

inline Bool_t FairGeoRotation::operator == (const FairGeoRotation& r)
{
  Int_t i=0;
  while (i<9) {
    if (rot[i]!=r(i)) { return kFALSE; }
    i++;
  }
  return kTRUE;
}

inline Bool_t FairGeoRotation::operator != (const FairGeoRotation& r)
{
  Int_t i=0;
  while (i<9) {
    if (rot[i]!=r(i)) { return kTRUE; }
    i++;
  }
  return kFALSE;
}

inline FairGeoVector FairGeoRotation::operator * (const FairGeoVector& v) const
{
  return FairGeoVector(rot[0]*v(0)+rot[1]*v(1)+rot[2]*v(2),
                       rot[3]*v(0)+rot[4]*v(1)+rot[5]*v(2),
                       rot[6]*v(0)+rot[7]*v(1)+rot[8]*v(2));
}

inline FairGeoRotation FairGeoRotation::operator * (const FairGeoRotation& r) const
{
  Double_t a[9];
  for(Int_t kk=0; kk<9; kk++) { a[kk]=0; }
  for(Int_t i=0; i<3; i++) {
    for(Int_t j=0; j<3; j++) {
      Int_t n=3*i+j;
      for(Int_t k=0; k<3; k++) { a[n]+=rot[3*i+k]*r(3*k+j); }
    }
  }
  return FairGeoRotation(&a[0]);
}

inline FairGeoRotation& FairGeoRotation::operator *= (const FairGeoRotation& r)
{
  return *this=operator * (r);
}

inline   FairGeoRotation& FairGeoRotation::transform(const FairGeoRotation& r)
{
  return *this=r*(*this);
}

inline Bool_t FairGeoRotation::isUnitMatrix()
{
  return (rot[0]==1. && rot[1]==0. && rot[2]==0. &&
          rot[3]==0. && rot[4]==1. && rot[5]==0. &&
          rot[6]==0. && rot[7]==0. && rot[8]==1.)  ? kTRUE : kFALSE;
}

inline FairGeoRotation FairGeoRotation::inverse() const
{
  Double_t a[9];
  for(Int_t i=0; i<3; i++) {
    for(Int_t j=0; j<3; j++) { a[j+3*i]=rot[i+3*j]; }
  }
  return FairGeoRotation(a);
}

inline FairGeoRotation& FairGeoRotation::invert()
{
  return *this=inverse();
}

inline Double_t FairGeoRotation::determinant() const
{
  return rot[0]*(rot[4]*rot[8]-rot[7]*rot[5])
         -rot[3]*(rot[1]*rot[8]-rot[7]*rot[2])
         +rot[6]*(rot[1]*rot[5]-rot[4]*rot[2]);
}

inline void FairGeoRotation::setUnitMatrix()
{
  rot[0]=rot[4]=rot[8]=1.;
  rot[1]=rot[2]=rot[3]=rot[5]=rot[6]=rot[7]=0.;
}

inline void FairGeoRotation::setZero()
{
  for(Int_t i=0; i<9; i++) { rot[i]=0.; }
}

inline void FairGeoRotation::print() const
{
  for(Int_t i=0; i<9; i++) { std::cout<<rot[i]<<"  "; }
  std::cout<<'\n';
}

#endif /* !FAIRGEOROTATION_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOSET_H
#define FAIRGEOSET_H

#include "TNamed.h"                     // for TNamed

#include "FairGeoNode.h"

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Int_t, Bool_t, etc
#include "TList.h"                      // for TList
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

//class FairGeoNode;
class FairGeoShapes;
class FairGeoMedia;
class FairGeoBuilder;
class FairGeoTransform;
class TArrayI;

/**
 * Base class for geometry of detector parts
 * @author Ilse koenig
 */
class  FairGeoSet : public TNamed
{

  protected:
    Int_t hadesGeo;

    class FairGeoCopyNode : public TNamed
    {
      public:
        FairGeoNode* pNode;
        FairGeoCopyNode(const char* name,FairGeoNode* node)
          : TNamed(name,""), pNode(node) {}
        //          SetName(name);
        //
        //        }
        ~FairGeoCopyNode() {}
      private:
        FairGeoCopyNode(const FairGeoCopyNode&);
        FairGeoCopyNode& operator=(const FairGeoCopyNode&);

    };
    TList* volumes;         /** list of volumes */
    TList* masterNodes;     /** pointer to list of mother volumes from other detector parts*/
    Int_t maxSectors;       /** maximum number of sectors (-1 for detectors outside any sector)*/
    Int_t maxKeepinVolumes; /** maximum number of keepin volumes per sector*/
    Int_t maxModules;       /** maximum number of modules per sector*/
    TArrayI* modules;       /** Module's array.*/
    FairGeoShapes* pShapes;  /** pointer to the class FairGeoShapes*/
    TString geoFile;        /** name of geometry input file or Oracle*/
    TString author;         /** author of the media version*/
    TString description;    /** description of the version*/

    FairGeoSet();
    void readInout(std::fstream&);
    void readTransform(std::fstream&,FairGeoTransform&);
    Bool_t readVolumeParams(std::fstream&,FairGeoMedia*,FairGeoNode*,TList* l=0);
    Bool_t readKeepIn(std::fstream&,FairGeoMedia*,TString&);
    Bool_t readModule(std::fstream&,FairGeoMedia*,TString&,TString&,Bool_t a=kFALSE);
  public :
    virtual ~FairGeoSet();
    void setShapes(FairGeoShapes* s) {pShapes=s;}
    void setMasterNodes(TList* m) {masterNodes=m;}
    void setGeomFile(const char* filename) {geoFile=filename;}
    const char* getGeomFile() { return geoFile.Data(); }
    Int_t getMaxSectors(void) {return maxSectors;}
    Int_t getMaxModules(void) {return maxModules;}
    Int_t getMaxKeepinVolumes(void) {return maxKeepinVolumes;}
    void setModules(Int_t,Int_t*);
    Int_t* getModules(void);
    Int_t getModule(Int_t,Int_t);
    FairGeoNode* getVolume(const char* name) {return dynamic_cast<FairGeoNode*>(volumes->FindObject(name));}
    FairGeoNode* getMasterNode(const char* name) {return dynamic_cast<FairGeoNode*>(masterNodes->FindObject(name));}
    TList* getListOfVolumes() {return volumes;}
    FairGeoShapes* getShapes() {return pShapes;}
    void setAuthor(TString& s) {author=s;}
    void setDescription(TString& s) {description=s;}
    TString& getAuthor() {return author;}
    TString& getDescription() {return description;}
    virtual const char* getKeepinName(Int_t,Int_t) {return 0;}
    virtual const char* getModuleName(Int_t) {return 0;}
    virtual const char* getEleName(Int_t) {return 0;}
    virtual Int_t getSecNumInMod(const TString&) {return -1;}
    virtual Int_t getModNumInMod(const TString&) {return 0;}
    virtual Bool_t read(std::fstream&,FairGeoMedia*);
    virtual void addRefNodes() {}
    virtual void write(std::fstream&);
    virtual void print();
    virtual Bool_t create(FairGeoBuilder*);
    void compare(FairGeoSet&);
    ClassDef(FairGeoSet,0) //
  private:
    FairGeoSet(const FairGeoSet&);
    FairGeoSet& operator=(const FairGeoSet&);
};


#endif  /* !FAIRGEOSET_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOSHAPES_H
#define FAIRGEOSHAPES_H

#include "TObject.h"                    // for TObject

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoShapes::Class, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairGeoVolume;
class FairGeoBasicShape;
class TList;
/**
 * manager class for geometry shapes
 * @author Ilse koenig
 */
class  FairGeoShapes : public TObject
{
  private:
    FairGeoShapes(const FairGeoShapes&);
    FairGeoShapes& operator=(const FairGeoShapes&);
  protected:
    TList* shapes;  // list of already created shape classes
  public :
    FairGeoShapes();
    ~FairGeoShapes();
    FairGeoBasicShape* selectShape(FairGeoVolume*);
    FairGeoBasicShape* selectShape(const TString&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoShapes,0) //
};

#endif  /* !FAIRGEOSHAPES_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOSPHE_H
#define FAIRGEOSPHE_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

/**
 * class for geometry shape SPHE
 * @author Ilse koenig
 */
class FairGeoSphe : public FairGeoBasicShape
{
  public:
    FairGeoSphe();
    ~FairGeoSphe();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoSphe,0) //
};

#endif  /* !FAIRGEOSPHE_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTRANSFORM_H
#define FAIRGEOTRANSFORM_H

#include "TObject.h"                    // for TObject

#include "FairGeoRotation.h"            // for FairGeoRotation
#include "FairGeoVector.h"              // for FairGeoVector

#include "Rtypes.h"                     // for Double_t, etc

/**
 * basic geometry transformation class
 * @author Ilse koenig*/
class FairGeoTransform : public TObject
{
  protected:
    FairGeoRotation rot;   /** rotation matrix, describing the orientation*/
    FairGeoVector trans;   /** translation vector, describing the position*/
    FairGeoVector trans_cm;   /** translation vector, describing the position in cm*/
  public:
    FairGeoTransform();
    inline FairGeoTransform(const FairGeoTransform& t);
    ~FairGeoTransform() {}
    FairGeoTransform& operator=(const FairGeoTransform& t);
    const FairGeoRotation& getRotMatrix() const { return rot; }
    const FairGeoVector& getTransVector() const { return trans; }
    void setRotMatrix(const FairGeoRotation& r) { rot=r; }
    void setRotMatrix(const Double_t* a) { rot.setMatrix(a); }
    void setRotMatrix(const Float_t* a) { rot.setMatrix(a); }
    void setTransVector(const FairGeoVector& t) { trans=t; }
    void setTransVector(const Double_t* a) { trans.setVector(a); }
    void setTransVector(const Float_t* a) { trans.setVector(a); }
    FairGeoVector transFrom(const FairGeoVector& p) const;
    FairGeoVector transTo(const FairGeoVector& p) const;
    void transFrom(const FairGeoTransform&);
    void transTo(const FairGeoTransform&);
    void invert(void);
    void clear();
    void print();
    const FairGeoVector& getTranslation()   {
      const double fac = 10.;
      trans_cm=trans;
      return (trans_cm/=fac);
    }

    const FairGeoRotation& getRotation() const { return rot; }

    inline void setTransform(const FairGeoTransform& t);
    ClassDef(FairGeoTransform,1) //
};

inline FairGeoTransform::FairGeoTransform(const FairGeoTransform& t)
  : TObject(t),
    rot(t.getRotMatrix()),
    trans(t.getTransVector()),
    trans_cm(FairGeoVector(0,0,0))
{

}


inline void FairGeoTransform::setTransform(const FairGeoTransform& t)
{
  rot=t.getRotMatrix();
  trans=t.getTransVector();
}

#endif /* !FAIRGEOTRANSFORM_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTRAP_H
#define FAIRGEOTRAP_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "FairGeoRotation.h"            // for FairGeoRotation

#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

class FairGeoTrap : public FairGeoBasicShape
{
  private:
    FairGeoRotation intrinsicRot;
  public:
    FairGeoTrap();
    ~FairGeoTrap();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    ClassDef(FairGeoTrap,0) // class for geometry shape TRAP
};

#endif  /* !FAIRGEOTRAP_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTRD1_H
#define FAIRGEOTRD1_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "FairGeoRotation.h"            // for FairGeoRotation

#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

class FairGeoTrd1 : public FairGeoBasicShape
{
  private:
    FairGeoRotation intrinsicRot;
  public:
    FairGeoTrd1();
    ~FairGeoTrd1();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    ClassDef(FairGeoTrd1,0) // class for geometry shape TRD1
};

#endif  /* !FAIRGEOTRD1_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTUBE_H
#define FAIRGEOTUBE_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

class FairGeoTube : public FairGeoBasicShape
{
  public:
    FairGeoTube();
    ~FairGeoTube();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoTube,0) // class for geometry shape TUBE
};

#endif  /* !FAIRGEOTUBE_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTUBS_H
#define FAIRGEOTUBS_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

class FairGeoTubs : public FairGeoBasicShape
{
  public:
    FairGeoTubs();
    ~FairGeoTubs();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream*,FairGeoVolume*);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);
    ClassDef(FairGeoTubs,0) // class for geometry shape TUBS
};

#endif  /* !FAIRGEOTUBS_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOTORUS_H
#define FAIRGEOTORUS_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for FairGeoPcon::Class, Bool_t, etc

#include <iosfwd>                       // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

class FairGeoTorus : public FairGeoBasicShape
{
  public:
    FairGeoTorus();
    ~FairGeoTorus();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    Int_t readPoints(std::fstream* pFile,FairGeoVolume* volu);
    Bool_t writePoints(std::fstream*,FairGeoVolume*);
    void printPoints(FairGeoVolume* volu);

    ClassDef(FairGeoTorus,0) // class for geometry shape TORUS
};

#endif  /* !FAIRGEOTORUS_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOVECTOR_H
#define FAIRGEOVECTOR_H

#include "TObject.h"                    // for TObject

#include "Riosfwd.h"                    // for ostream, istream
#include "Rtypes.h"                     // for Double_t, Bool_t, Int_t, etc
#include "TMath.h"                      // for pow, floor, sqrt
#include "TMathBase.h"                  // for Abs

#include <stdio.h>                      // for printf
#include <iostream>                     // for operator<<, ostream, etc

class FairGeoVector : public TObject
{
  protected:
    Double_t x;
    Double_t y;
    Double_t z;
    inline void round(Double_t d,Int_t n);
  public:
    FairGeoVector(Double_t dx=0,Double_t dy=0,Double_t dz=0)
      : TObject(),x(dx),y(dy),z(dz) {}
    FairGeoVector(const FairGeoVector& v)
      : TObject(v),x(v.getX()), y(v.getY()), z(v.getZ()) {}
    ~FairGeoVector() {}
    Double_t& X() {return x;}
    Double_t& Y() {return y;}
    Double_t& Z() {return z;}
    Double_t getX() const {return x;}
    Double_t getY() const {return y;}
    Double_t getZ() const {return z;}

    Double_t getValues(Int_t i ) {
      if ( i<0 || i>2 ) {
        std::cout << " -E- Vector index  is 0 1 2 only ! " << std::endl;
      }
      if ( i == 0 ) { return x; }
      if ( i == 1 ) { return y; }
      if ( i == 2 ) { return z; }
      return -1;
    }

    void setXYZ(const Double_t xx,const Double_t yy,const Double_t zz) {
      x=xx;
      y=yy;
      z=zz;
    }
    void setX(const Double_t a) {x=a;}
    void setY(const Double_t a) {y=a;}
    void setZ(const Double_t a) {z=a;}
    inline void setVector(const Double_t* a);
    inline void setVector(const Float_t* a);
    inline Double_t operator() (const Int_t i) const;
    inline FairGeoVector operator - () const;
    inline FairGeoVector& operator = (const FairGeoVector& v);
    inline Bool_t operator == (const FairGeoVector& v) const;
    inline Bool_t operator != (const FairGeoVector& v) const;
    inline Bool_t operator < (const Double_t a);
    inline Bool_t operator <= (const Double_t a);
    inline Bool_t operator > (const Double_t a);
    inline Bool_t operator >= (const Double_t a);
    inline FairGeoVector& operator += (const Double_t a);
    inline FairGeoVector& operator -= (const Double_t a);
    inline FairGeoVector& operator *= (const Double_t a);
    inline FairGeoVector& operator /= (const Double_t a);
    inline FairGeoVector& operator += (const FairGeoVector& v);
    inline FairGeoVector& operator -= (const FairGeoVector& v);
    inline FairGeoVector operator + (const FairGeoVector& v) const;
    inline FairGeoVector operator - (const FairGeoVector& v) const;
    inline FairGeoVector& abs();
    inline Double_t scalarProduct(const FairGeoVector& v) const;
    inline FairGeoVector vectorProduct(const FairGeoVector& v) const;
    Double_t length() const {return sqrt(x*x+y*y+z*z);}
    void clear() {x=y=z=0.;}
    void print() const {printf("%10.3f%10.3f%10.3f\n",x,y,z);}
    inline void round(Int_t n);
    inline friend std::ostream& operator << (std::ostream& put,const FairGeoVector& v);
    inline friend std::istream& operator >> (std::istream& get,FairGeoVector& v);
    ClassDef(FairGeoVector,1) // vector with 3 components
};

// -------------------- inlines ---------------------------

inline void FairGeoVector::setVector(const Double_t* a)
{
  x=a[0];
  y=a[1];
  z=a[2];
}

inline void FairGeoVector::setVector(const Float_t* a)
{
  x=a[0];
  y=a[1];
  z=a[2];
}

inline Double_t FairGeoVector::operator() (const Int_t i) const
{
  switch (i) {
  case 0:
    return x;
  case 1:
    return y;
  case 2:
    return z;
  default:
    Error("operator()","bad index");
  }
  return 0;
}

inline FairGeoVector FairGeoVector::operator - () const
{
  FairGeoVector p(-x,-y,-z);
  return p;
}

inline FairGeoVector& FairGeoVector::operator = (const FairGeoVector& v)
{
  x=v.getX();
  y=v.getY();
  z=v.getZ();
  return *this;
}

inline Bool_t FairGeoVector::operator == (const FairGeoVector& v) const
{
  return ((v.getX()!=x || v.getY()!=y || v.getZ()!=z) ? kFALSE : kTRUE);
}

inline  Bool_t FairGeoVector::operator != (const FairGeoVector& v) const
{
  return (v.getX()!=x || v.getY()!=y || v.getZ()!=z)  ? kTRUE : kFALSE;
}
/// check with ilse
inline Bool_t FairGeoVector::operator < (const Double_t a)
{
  return (x>=a || y>=a || z>=a) ? kFALSE : kTRUE;
}

inline Bool_t FairGeoVector::operator <= (const Double_t a)
{
  return (x>a || y>a || z>a) ? kFALSE : kTRUE;
}

inline Bool_t FairGeoVector::operator > (const Double_t a)
{
  return (x<=a || y<=a || z<=a) ? kFALSE : kTRUE;
}

inline Bool_t FairGeoVector::operator >= (const Double_t a)
{
  return (x<a || y<a || z<a) ? kFALSE : kTRUE;
}

inline FairGeoVector& FairGeoVector::operator += (const Double_t a)
{
  x+=a;
  y+=a;
  z+=a;
  return *this;
}

inline FairGeoVector& FairGeoVector::operator -= (const Double_t a)
{
  x-=a;
  y-=a;
  z-=a;
  return *this;
}

inline FairGeoVector& FairGeoVector::operator *= (const Double_t a)
{
  x*=a;
  y*=a;
  z*=a;
  return *this;
}

inline FairGeoVector& FairGeoVector::operator /= (const Double_t a)
{
  x/=a;
  y/=a;
  z/=a;
  return *this;
}

inline FairGeoVector& FairGeoVector::operator += (const FairGeoVector& v)
{
  x+=v.getX();
  y+=v.getY();
  z+=v.getZ();
  return *this;
}

inline FairGeoVector& FairGeoVector::operator -= (const FairGeoVector& v)
{
  x-=v.getX();
  y-=v.getY();
  z-=v.getZ();
  return *this;
}

inline FairGeoVector FairGeoVector::operator + (const FairGeoVector& v) const
{
  FairGeoVector p(*this);
  return p+=v;
}

inline FairGeoVector FairGeoVector::operator - (const FairGeoVector& v) const
{
  FairGeoVector p(*this);
  return p-=v;
}

inline FairGeoVector& FairGeoVector::abs()
{
  x=TMath::Abs(x);
  y=TMath::Abs(y);
  z=TMath::Abs(z);
  return *this;
}

inline Double_t FairGeoVector::scalarProduct(const FairGeoVector& v) const
{
  return (x*v.getX()+y*v.getY()+z*v.getZ());
}

inline FairGeoVector FairGeoVector::vectorProduct(const FairGeoVector& v) const
{
  FairGeoVector p(y*v.getZ()-z*v.getY(),z*v.getX()-x*v.getZ(),
                  x*v.getY()-y*v.getX());
  return p;
}

inline void FairGeoVector::round(Double_t d,Int_t n)
{
  // rounds d to a precision with n digits
  if(d>0) { d=floor(d*pow(10.,n)+0.5)/pow(10.,n); }
  else { d=-floor((-d)*pow(10.,n)+0.5)/pow(10.,n); }
}

inline void FairGeoVector::round(Int_t n)
{
  // rounds every component to a precision with n digits
  round(x,n);
  round(y,n);
  round(z,n);
}

inline std::ostream& operator << (std::ostream& put,const FairGeoVector& v)
{
  return put<<v(0)<<"  "<<v(1)<<"  "<<v(2)<<'\n';
}

inline std::istream& operator >> (std::istream& get,FairGeoVector& v)
{
  Double_t x[3];
  get>>x[0]>>x[1]>>x[2];
  v.setVector(x);
  return get;
}

#endif /* !FAIRGEOVECTOR_H */













/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOVOLUME_H
#define FAIRGEOVOLUME_H

#include "TNamed.h"                     // for TNamed

#include "FairGeoMedium.h"              // for FairGeoMedium
#include "FairGeoTransform.h"           // for FairGeoTransform
#include "FairGeoVector.h"              // for FairGeoVector

#include "Rtypes.h"                     // for Int_t, Text_t, Double_t, etc
#include "TObjArray.h"                  // for TObjArray
#include "TString.h"                    // for TString

#include <stddef.h>                     // for NULL

/**
 * basic geometry parameters of a volume
 * @author Ilse koenig
 */
class FairGeoVolume : public TNamed
{
  private:
    FairGeoVolume& operator=(const  FairGeoVolume&);
  protected:
    TString shape;              /**eant shape of the volume*/
    TString mother;            /** Name of the mother volume*/
    TObjArray* points;        /** array of points (type FairGeoVector)*/
    FairGeoTransform transform; /** transformation relative to the mother system */
    FairGeoTransform fLabTransform; /** transformation to the LAB system; */
    FairGeoMedium   fMedium;    /** medium properties */
    Int_t nPoints;             /** number of points */
    Int_t fHadFormat; //
    Int_t fgMCid;     /** Volume Id given by MC*/

  public:
    inline FairGeoVolume();
    FairGeoVolume(FairGeoVolume&);
    virtual ~FairGeoVolume();
    const TString& getName() const { return fName; }
    const TString& getShape() const { return shape; }
    const TString& getMother() const { return mother; }
    FairGeoTransform& getTransform() { return transform; }
    FairGeoTransform& getLabTransform() { return fLabTransform;}
    FairGeoMedium&    getMedium() { return fMedium;}
    Int_t getNumPoints() { return nPoints;}
    inline FairGeoVector* getPoint(const Int_t n);
    inline void setName(const Text_t* s);
    void setVolumePar(FairGeoVolume&);
    inline void setShape(const Text_t* s);
    inline void setMother(const Text_t* s);
    void createPoints(const Int_t);
    void setPoint(const Int_t,const Double_t,const Double_t,const Double_t);
    void setPoint(const Int_t,const FairGeoVector&);
    virtual void clear();
    virtual void print();
    virtual void setHadFormat( Int_t i ) { fHadFormat=i;}
    Double_t getVolParameter( Int_t nPoint, Int_t pos );
    Int_t getMCid() {return fgMCid;}
    void setMCid(Int_t MCid) {fgMCid=MCid;}

    ClassDef(FairGeoVolume,1) //
};

// -------------------- inlines --------------------------

inline FairGeoVolume::FairGeoVolume()
  :TNamed(),
   shape(""),
   mother(""),
   points(NULL),
   transform(FairGeoTransform()),
   fLabTransform(FairGeoTransform()),
   fMedium(0),
   nPoints(0),
   fHadFormat(0),
   fgMCid(0)
{
}


inline FairGeoVector* FairGeoVolume::getPoint(const Int_t n)
{
  if (points && n<nPoints) { return static_cast<FairGeoVector*>(points->At(n)); }
  else { return 0; }
}

inline void FairGeoVolume::setName(const Text_t* s)
{
  fName=s;
  fName.ToUpper();
}

inline void FairGeoVolume::setShape(const Text_t* s)
{
  shape=s;
  shape.ToUpper();
}

inline void FairGeoVolume::setMother(const Text_t* s)
{
  mother=s;
  mother.ToUpper();
}

#endif /* !FAIRGEOVOLUME_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOCOMPOSITEVOLUME_H
#define FAIRGEOCOMPOSITEVOLUME_H

#include "FairGeoVolume.h"              // for FairGeoVolume

#include "Rtypes.h"                     // for Int_t, etc

class TObjArray;
/**
 * basic geometry of a volume with components
 * @author Ilse koenig
 */
class FairGeoCompositeVolume : public FairGeoVolume
{
  protected:
    TObjArray* components;    // array of components (type FairGeoVolume)
  public:
    FairGeoCompositeVolume(Int_t nComp=0);
    ~FairGeoCompositeVolume();
    Int_t getNumComponents();
    FairGeoVolume* getComponent(const Int_t);
    void createComponents(const Int_t);
    void setComponent(FairGeoVolume*,const Int_t);
    void clear();
    void print();
    ClassDef(FairGeoCompositeVolume,1)
  private:
    FairGeoCompositeVolume(const FairGeoCompositeVolume& );
    FairGeoCompositeVolume& operator=(const FairGeoCompositeVolume&);

};

#endif /* !FAIRGEOCOMPOSITEVOLUME_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOASCIIIO_H
#define FAIRGEOASCIIIO_H

#include "FairGeoIo.h"                  // for FairGeoIo

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Bool_t, etc
#include "TString.h"                    // for TString

#include <fstream>                      // for fstream

class FairGeoSet;
class FairGeoMedia;
class FairGeoInterface;

/**
 * Class for geometry I/O from ASCII file
 * @author Ilse Koenig
 */
class FairGeoAsciiIo: public FairGeoIo
{
    TString  filename;
    TString  filedir;
    Bool_t   writable;
    std::fstream* file;
  public:
    FairGeoAsciiIo();
    virtual ~FairGeoAsciiIo();
    void setDirectory(const char* fDir) {filedir=fDir;}
    const char* getDirectory() {return filedir.Data();}
    const char* getFilename() {return filename.Data();}
    Bool_t open(const char*,const Text_t* status="in");
    Bool_t isOpen();
    Bool_t isWritable();
    void close();
    void print();
    Bool_t read(FairGeoMedia*);
    Bool_t read(FairGeoSet*,FairGeoMedia*);
    Bool_t write(FairGeoMedia*);
    Bool_t write(FairGeoSet* set);
    Bool_t readGeomConfig(FairGeoInterface*);
    Bool_t readDetectorSetup(FairGeoInterface*);
    Bool_t setSimulRefRun(const char*) {return kTRUE;}
    Bool_t setHistoryDate(const char*) {return kTRUE;}
  private:
    FairGeoAsciiIo(const FairGeoAsciiIo&);
    FairGeoAsciiIo& operator=(const FairGeoAsciiIo&);
    ClassDef(FairGeoAsciiIo,0) // Class for geometry I/O from ASCII file
};

#endif  /* !FAIRGEOASCIIIO_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOBRIK_H
#define FAIRGEOBRIK_H

#include "FairGeoBasicShape.h"          // for FairGeoBasicShape

#include "Rtypes.h"                     // for FairGeoBrik::Class, etc


class FairGeoTransform;
class FairGeoVolume;
class TArrayD;

class FairGeoBrik : public FairGeoBasicShape
{
  public:
    FairGeoBrik();
    ~FairGeoBrik();
    TArrayD* calcVoluParam(FairGeoVolume*);
    void calcVoluPosition(FairGeoVolume*,
                          const FairGeoTransform&,const FairGeoTransform&);
    ClassDef(FairGeoBrik,0) // class for geometry shape BOX or BRIK
};

#endif  /* !FAIRGEOBRIK_H */
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRGEOBASICSHAPE_H
#define FAIRGEOBASICSHAPE_H

#include "TNamed.h"                     // for TNamed

#include "Riosfwd.h"                    // for fstream
#include "Rtypes.h"                     // for Int_t, etc

#include <fstream>                      // for fstream

class FairGeoTransform;
class FairGeoVolume;
class TArrayD;
/**
 * base class for all shapes
 * @author Ilse koenig
 */
class FairGeoBasicShape : public TNamed
{
  protected:
    Int_t nPoints;            // number of points describing the shape
    Int_t nParam;             // number of parameters needed to create the ROOT shape
    TArrayD* param;           // parameters needed to create the ROOT shape
    FairGeoTransform* center;   // position of the volume center in the technical KS
    FairGeoTransform* position; // position of the ROOT volume in its ROOT mother
  public:
    FairGeoBasicShape();
    virtual ~FairGeoBasicShape();
    Int_t getNumPoints() {return nPoints;}
    Int_t getNumParam() {return nParam;}
    TArrayD* getParam() {return param;}
    FairGeoTransform* getCenterPosition() {return center;}
    FairGeoTransform* getVoluPosition() {return position;}
    virtual Int_t readPoints(std::fstream*,FairGeoVolume*);
    virtual Bool_t writePoints(std::fstream*,FairGeoVolume*);
    virtual void printPoints(FairGeoVolume* volu);
    virtual TArrayD* calcVoluParam(FairGeoVolume*) {return 0;}
    virtual void calcVoluPosition(FairGeoVolume*,const FairGeoTransform&);
    virtual void calcVoluPosition(FairGeoVolume*,const FairGeoTransform&,
                                  const FairGeoTransform&) {return;}
    void printParam();
  protected:
    void posInMother(const FairGeoTransform&,const FairGeoTransform&);
    ClassDef(FairGeoBasicShape,0) // base class for all shapes
  private:
    FairGeoBasicShape(const FairGeoBasicShape&);
    FairGeoBasicShape& operator=(const FairGeoBasicShape&);

};

#endif  /* !FAIRGEOBASICSHAPE_H */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairGeoAsciiIo", payloadCode, "@",
"FairGeoAssembly", payloadCode, "@",
"FairGeoBasicShape", payloadCode, "@",
"FairGeoBrik", payloadCode, "@",
"FairGeoBuilder", payloadCode, "@",
"FairGeoCompositeVolume", payloadCode, "@",
"FairGeoCone", payloadCode, "@",
"FairGeoCons", payloadCode, "@",
"FairGeoEltu", payloadCode, "@",
"FairGeoInterface", payloadCode, "@",
"FairGeoIo", payloadCode, "@",
"FairGeoLoader", payloadCode, "@",
"FairGeoMatrix", payloadCode, "@",
"FairGeoMedia", payloadCode, "@",
"FairGeoMedium", payloadCode, "@",
"FairGeoNode", payloadCode, "@",
"FairGeoOldAsciiIo", payloadCode, "@",
"FairGeoPcon", payloadCode, "@",
"FairGeoPgon", payloadCode, "@",
"FairGeoRootBuilder", payloadCode, "@",
"FairGeoRotation", payloadCode, "@",
"FairGeoSet", payloadCode, "@",
"FairGeoShapes", payloadCode, "@",
"FairGeoSphe", payloadCode, "@",
"FairGeoTorus", payloadCode, "@",
"FairGeoTransform", payloadCode, "@",
"FairGeoTrap", payloadCode, "@",
"FairGeoTrd1", payloadCode, "@",
"FairGeoTube", payloadCode, "@",
"FairGeoTubs", payloadCode, "@",
"FairGeoVector", payloadCode, "@",
"FairGeoVolume", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__GeoBaseDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__GeoBaseDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__GeoBaseDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__GeoBaseDict() {
  TriggerDictionaryInitialization_G__GeoBaseDict_Impl();
}

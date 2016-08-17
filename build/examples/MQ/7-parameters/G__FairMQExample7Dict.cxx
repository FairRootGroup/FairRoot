// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIMQdI7mIparametersdIG__FairMQExample7Dict

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
#include "FairMQExample7ParOne.h"
#include "FairMQExample7ContFact.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairMQExample7ContFact(void *p = 0);
   static void *newArray_FairMQExample7ContFact(Long_t size, void *p);
   static void delete_FairMQExample7ContFact(void *p);
   static void deleteArray_FairMQExample7ContFact(void *p);
   static void destruct_FairMQExample7ContFact(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMQExample7ContFact*)
   {
      ::FairMQExample7ContFact *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMQExample7ContFact >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMQExample7ContFact", ::FairMQExample7ContFact::Class_Version(), "invalid", 68,
                  typeid(::FairMQExample7ContFact), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMQExample7ContFact::Dictionary, isa_proxy, 4,
                  sizeof(::FairMQExample7ContFact) );
      instance.SetNew(&new_FairMQExample7ContFact);
      instance.SetNewArray(&newArray_FairMQExample7ContFact);
      instance.SetDelete(&delete_FairMQExample7ContFact);
      instance.SetDeleteArray(&deleteArray_FairMQExample7ContFact);
      instance.SetDestructor(&destruct_FairMQExample7ContFact);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMQExample7ContFact*)
   {
      return GenerateInitInstanceLocal((::FairMQExample7ContFact*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMQExample7ContFact*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMQExample7ParOne(void *p = 0);
   static void *newArray_FairMQExample7ParOne(Long_t size, void *p);
   static void delete_FairMQExample7ParOne(void *p);
   static void deleteArray_FairMQExample7ParOne(void *p);
   static void destruct_FairMQExample7ParOne(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMQExample7ParOne*)
   {
      ::FairMQExample7ParOne *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMQExample7ParOne >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMQExample7ParOne", ::FairMQExample7ParOne::Class_Version(), "invalid", 22,
                  typeid(::FairMQExample7ParOne), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMQExample7ParOne::Dictionary, isa_proxy, 4,
                  sizeof(::FairMQExample7ParOne) );
      instance.SetNew(&new_FairMQExample7ParOne);
      instance.SetNewArray(&newArray_FairMQExample7ParOne);
      instance.SetDelete(&delete_FairMQExample7ParOne);
      instance.SetDeleteArray(&deleteArray_FairMQExample7ParOne);
      instance.SetDestructor(&destruct_FairMQExample7ParOne);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMQExample7ParOne*)
   {
      return GenerateInitInstanceLocal((::FairMQExample7ParOne*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMQExample7ParOne*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairMQExample7ContFact::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMQExample7ContFact::Class_Name()
{
   return "FairMQExample7ContFact";
}

//______________________________________________________________________________
const char *FairMQExample7ContFact::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMQExample7ContFact*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMQExample7ContFact::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMQExample7ContFact*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMQExample7ContFact::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMQExample7ContFact*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMQExample7ContFact::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMQExample7ContFact*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMQExample7ParOne::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMQExample7ParOne::Class_Name()
{
   return "FairMQExample7ParOne";
}

//______________________________________________________________________________
const char *FairMQExample7ParOne::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMQExample7ParOne*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMQExample7ParOne::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMQExample7ParOne*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMQExample7ParOne::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMQExample7ParOne*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMQExample7ParOne::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMQExample7ParOne*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairMQExample7ContFact::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMQExample7ContFact.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMQExample7ContFact::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMQExample7ContFact::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMQExample7ContFact(void *p) {
      return  p ? new(p) ::FairMQExample7ContFact : new ::FairMQExample7ContFact;
   }
   static void *newArray_FairMQExample7ContFact(Long_t nElements, void *p) {
      return p ? new(p) ::FairMQExample7ContFact[nElements] : new ::FairMQExample7ContFact[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMQExample7ContFact(void *p) {
      delete ((::FairMQExample7ContFact*)p);
   }
   static void deleteArray_FairMQExample7ContFact(void *p) {
      delete [] ((::FairMQExample7ContFact*)p);
   }
   static void destruct_FairMQExample7ContFact(void *p) {
      typedef ::FairMQExample7ContFact current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMQExample7ContFact

//______________________________________________________________________________
void FairMQExample7ParOne::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMQExample7ParOne.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMQExample7ParOne::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMQExample7ParOne::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMQExample7ParOne(void *p) {
      return  p ? new(p) ::FairMQExample7ParOne : new ::FairMQExample7ParOne;
   }
   static void *newArray_FairMQExample7ParOne(Long_t nElements, void *p) {
      return p ? new(p) ::FairMQExample7ParOne[nElements] : new ::FairMQExample7ParOne[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMQExample7ParOne(void *p) {
      delete ((::FairMQExample7ParOne*)p);
   }
   static void deleteArray_FairMQExample7ParOne(void *p) {
      delete [] ((::FairMQExample7ParOne*)p);
   }
   static void destruct_FairMQExample7ParOne(void *p) {
      typedef ::FairMQExample7ParOne current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMQExample7ParOne

namespace {
  void TriggerDictionaryInitialization_G__FairMQExample7Dict_Impl() {
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
"/Users/turany/development/FairRoot/examples/MQ/7-parameters",
"/Users/turany/development/FairRoot/build/examples/MQ/7-parameters",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/MQ/7-parameters/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__FairMQExample7Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairMQExample7ContFact;
class FairMQExample7ParOne;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__FairMQExample7Dict dictionary payload"

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
#ifndef FAIRMQEXAMPLE7PARONE_H_
#define FAIRMQEXAMPLE7PARONE_H_

#include "FairParGenericSet.h"

#include "TObject.h"

class FairParamList;

class FairMQExample7ParOne : public FairParGenericSet
{
  public:
    /** Standard constructor **/
    FairMQExample7ParOne(const char* name    = "FairMQExample7ParOne",
                         const char* title   = "FairMQ Example 7 Parameter One",
                         const char* context = "Default");

    /** Destructor **/
    virtual ~FairMQExample7ParOne();

    virtual void print();

    /** Reset all parameters **/
    virtual void clear();

    void putParams(FairParamList* list);
    Bool_t getParams(FairParamList* list);

    inline void SetValue(const Int_t& val) { fParameterValue = val; }

  private:
    Int_t fParameterValue; //

    FairMQExample7ParOne(const FairMQExample7ParOne&);
    FairMQExample7ParOne& operator=(const FairMQExample7ParOne&);

    ClassDef(FairMQExample7ParOne,1);
};

#endif // FAIRMQEXAMPLE7PARONE_H_
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRMQEXAMPLE7CONTFACT_H_
#define FAIRMQEXAMPLE7CONTFACT_H_

#include "FairContFact.h"

class FairContainer;

class FairMQExample7ContFact : public FairContFact
{
  private:
    void setAllContainers();

  public:
    FairMQExample7ContFact();
    ~FairMQExample7ContFact() {}

    FairParSet* createContainer(FairContainer*);
    ClassDef(FairMQExample7ContFact,0)
};

#endif  /* FAIRMQEXAMPLE7CONTFACT_H_ */

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairMQExample7ContFact", payloadCode, "@",
"FairMQExample7ParOne", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__FairMQExample7Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__FairMQExample7Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__FairMQExample7Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__FairMQExample7Dict() {
  TriggerDictionaryInitialization_G__FairMQExample7Dict_Impl();
}

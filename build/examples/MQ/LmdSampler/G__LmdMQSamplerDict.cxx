// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIMQdILmdSamplerdIG__LmdMQSamplerDict

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
#include "unpacker/FairTut8Unpacker.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairTut8Unpacker(void *p = 0);
   static void *newArray_FairTut8Unpacker(Long_t size, void *p);
   static void delete_FairTut8Unpacker(void *p);
   static void deleteArray_FairTut8Unpacker(void *p);
   static void destruct_FairTut8Unpacker(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTut8Unpacker*)
   {
      ::FairTut8Unpacker *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTut8Unpacker >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTut8Unpacker", ::FairTut8Unpacker::Class_Version(), "invalid", 24,
                  typeid(::FairTut8Unpacker), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTut8Unpacker::Dictionary, isa_proxy, 4,
                  sizeof(::FairTut8Unpacker) );
      instance.SetNew(&new_FairTut8Unpacker);
      instance.SetNewArray(&newArray_FairTut8Unpacker);
      instance.SetDelete(&delete_FairTut8Unpacker);
      instance.SetDeleteArray(&deleteArray_FairTut8Unpacker);
      instance.SetDestructor(&destruct_FairTut8Unpacker);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTut8Unpacker*)
   {
      return GenerateInitInstanceLocal((::FairTut8Unpacker*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTut8Unpacker*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairTut8Unpacker::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTut8Unpacker::Class_Name()
{
   return "FairTut8Unpacker";
}

//______________________________________________________________________________
const char *FairTut8Unpacker::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Unpacker*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTut8Unpacker::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Unpacker*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTut8Unpacker::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Unpacker*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTut8Unpacker::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Unpacker*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairTut8Unpacker::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTut8Unpacker.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTut8Unpacker::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTut8Unpacker::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTut8Unpacker(void *p) {
      return  p ? new(p) ::FairTut8Unpacker : new ::FairTut8Unpacker;
   }
   static void *newArray_FairTut8Unpacker(Long_t nElements, void *p) {
      return p ? new(p) ::FairTut8Unpacker[nElements] : new ::FairTut8Unpacker[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTut8Unpacker(void *p) {
      delete ((::FairTut8Unpacker*)p);
   }
   static void deleteArray_FairTut8Unpacker(void *p) {
      delete [] ((::FairTut8Unpacker*)p);
   }
   static void destruct_FairTut8Unpacker(void *p) {
      typedef ::FairTut8Unpacker current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTut8Unpacker

namespace {
  void TriggerDictionaryInitialization_G__LmdMQSamplerDict_Impl() {
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
"/Users/turany/development/FairRoot/fairmq/options",
"/Users/turany/development/FairRoot/fairmq/tools",
"/Users/turany/development/FairRoot/fairmq/nanomsg",
"/Users/turany/development/FairRoot/fairmq/zeromq",
"/Users/turany/development/FairRoot/base/MQ/devices",
"/Users/turany/development/FairRoot/base/MQ/hosts",
"/Users/turany/development/FairRoot/base/MQ/policies/Serialization",
"/Users/turany/development/FairRoot/base/MQ/policies/Storage",
"/Users/turany/development/FairRoot/base/MQ/baseMQtools",
"/Users/turany/development/FairRoot/examples/MQ/LmdSampler",
"/Users/turany/development/FairRoot/examples/MQ/LmdSampler/devices",
"/Users/turany/development/FairRoot/examples/MQ/LmdSampler/unpacker",
"/Users/turany/development/FairRoot/MbsAPI",
"/Users/turany/development/FairRoot/examples/advanced/MbsTutorial/src",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/MQ/LmdSampler/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__LmdMQSamplerDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairTut8Unpacker;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__LmdMQSamplerDict dictionary payload"

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

#ifndef FAIRTUT8UNPACKER_H
#define FAIRTUT8UNPACKER_H

#include "FairUnpack.h"

class TClonesArray;

/**
 * An example unpacker of MBS data.
 */
class FairTut8Unpacker : public FairUnpack
{
  public:
    /** Standard Constructor. Input - MBS parameters of the detector. */
    FairTut8Unpacker(Short_t type = 94,
                   Short_t subType = 9400,
                   Short_t procId = 10,
                   Short_t subCrate = 1,
                   Short_t control = 3);

    /** Destructor. */
    virtual ~FairTut8Unpacker();

    /** Initialization. Called once, before the event loop. */
    virtual Bool_t Init();

    /** Process an MBS sub-event. */
    virtual Bool_t DoUnpack(Int_t* data, Int_t size);

    /** Clear the output structures. */
    virtual void Reset();

    /** Method for controling the functionality. */
    inline Int_t GetNHitsTotal()
    {
        return fNHitsTotal;
    }

    TClonesArray* GetOutputData()
    {
        return fRawData;
    }

  protected:
    /** Register the output structures. */
    virtual void Register(){}

  private:
    TClonesArray* fRawData; /**< Array of output raw items. */
    Int_t fNHits;           /**< Number of raw items in current event. */
    Int_t fNHitsTotal;      /**< Total number of raw items. */

    /// Copy Constructor
    FairTut8Unpacker(const FairTut8Unpacker&);
    FairTut8Unpacker operator=(const FairTut8Unpacker&);

  public:
    // Class definition
    ClassDef(FairTut8Unpacker, 1)
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairTut8Unpacker", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__LmdMQSamplerDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__LmdMQSamplerDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__LmdMQSamplerDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__LmdMQSamplerDict() {
  TriggerDictionaryInitialization_G__LmdMQSamplerDict_Impl();
}

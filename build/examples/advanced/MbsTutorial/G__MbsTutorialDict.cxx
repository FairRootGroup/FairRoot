// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIadvanceddIMbsTutorialdIG__MbsTutorialDict

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
#include "src/FairTut8Unpack.h"
#include "src/FairTut8RawItem.h"
#include "src/FairTut8Task.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairTut8Unpack(void *p = 0);
   static void *newArray_FairTut8Unpack(Long_t size, void *p);
   static void delete_FairTut8Unpack(void *p);
   static void deleteArray_FairTut8Unpack(void *p);
   static void destruct_FairTut8Unpack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTut8Unpack*)
   {
      ::FairTut8Unpack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTut8Unpack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTut8Unpack", ::FairTut8Unpack::Class_Version(), "invalid", 24,
                  typeid(::FairTut8Unpack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTut8Unpack::Dictionary, isa_proxy, 4,
                  sizeof(::FairTut8Unpack) );
      instance.SetNew(&new_FairTut8Unpack);
      instance.SetNewArray(&newArray_FairTut8Unpack);
      instance.SetDelete(&delete_FairTut8Unpack);
      instance.SetDeleteArray(&deleteArray_FairTut8Unpack);
      instance.SetDestructor(&destruct_FairTut8Unpack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTut8Unpack*)
   {
      return GenerateInitInstanceLocal((::FairTut8Unpack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTut8Unpack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairTut8RawItem(void *p = 0);
   static void *newArray_FairTut8RawItem(Long_t size, void *p);
   static void delete_FairTut8RawItem(void *p);
   static void deleteArray_FairTut8RawItem(void *p);
   static void destruct_FairTut8RawItem(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTut8RawItem*)
   {
      ::FairTut8RawItem *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTut8RawItem >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTut8RawItem", ::FairTut8RawItem::Class_Version(), "invalid", 86,
                  typeid(::FairTut8RawItem), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTut8RawItem::Dictionary, isa_proxy, 4,
                  sizeof(::FairTut8RawItem) );
      instance.SetNew(&new_FairTut8RawItem);
      instance.SetNewArray(&newArray_FairTut8RawItem);
      instance.SetDelete(&delete_FairTut8RawItem);
      instance.SetDeleteArray(&deleteArray_FairTut8RawItem);
      instance.SetDestructor(&destruct_FairTut8RawItem);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTut8RawItem*)
   {
      return GenerateInitInstanceLocal((::FairTut8RawItem*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTut8RawItem*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void delete_FairTut8Task(void *p);
   static void deleteArray_FairTut8Task(void *p);
   static void destruct_FairTut8Task(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairTut8Task*)
   {
      ::FairTut8Task *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairTut8Task >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairTut8Task", ::FairTut8Task::Class_Version(), "invalid", 187,
                  typeid(::FairTut8Task), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairTut8Task::Dictionary, isa_proxy, 4,
                  sizeof(::FairTut8Task) );
      instance.SetDelete(&delete_FairTut8Task);
      instance.SetDeleteArray(&deleteArray_FairTut8Task);
      instance.SetDestructor(&destruct_FairTut8Task);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairTut8Task*)
   {
      return GenerateInitInstanceLocal((::FairTut8Task*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairTut8Task*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairTut8Unpack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTut8Unpack::Class_Name()
{
   return "FairTut8Unpack";
}

//______________________________________________________________________________
const char *FairTut8Unpack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Unpack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTut8Unpack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Unpack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTut8Unpack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Unpack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTut8Unpack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Unpack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTut8RawItem::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTut8RawItem::Class_Name()
{
   return "FairTut8RawItem";
}

//______________________________________________________________________________
const char *FairTut8RawItem::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTut8RawItem*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTut8RawItem::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTut8RawItem*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTut8RawItem::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTut8RawItem*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTut8RawItem::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTut8RawItem*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairTut8Task::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairTut8Task::Class_Name()
{
   return "FairTut8Task";
}

//______________________________________________________________________________
const char *FairTut8Task::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Task*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairTut8Task::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Task*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairTut8Task::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Task*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairTut8Task::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairTut8Task*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairTut8Unpack::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTut8Unpack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTut8Unpack::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTut8Unpack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTut8Unpack(void *p) {
      return  p ? new(p) ::FairTut8Unpack : new ::FairTut8Unpack;
   }
   static void *newArray_FairTut8Unpack(Long_t nElements, void *p) {
      return p ? new(p) ::FairTut8Unpack[nElements] : new ::FairTut8Unpack[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTut8Unpack(void *p) {
      delete ((::FairTut8Unpack*)p);
   }
   static void deleteArray_FairTut8Unpack(void *p) {
      delete [] ((::FairTut8Unpack*)p);
   }
   static void destruct_FairTut8Unpack(void *p) {
      typedef ::FairTut8Unpack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTut8Unpack

//______________________________________________________________________________
void FairTut8RawItem::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTut8RawItem.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTut8RawItem::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTut8RawItem::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairTut8RawItem(void *p) {
      return  p ? new(p) ::FairTut8RawItem : new ::FairTut8RawItem;
   }
   static void *newArray_FairTut8RawItem(Long_t nElements, void *p) {
      return p ? new(p) ::FairTut8RawItem[nElements] : new ::FairTut8RawItem[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairTut8RawItem(void *p) {
      delete ((::FairTut8RawItem*)p);
   }
   static void deleteArray_FairTut8RawItem(void *p) {
      delete [] ((::FairTut8RawItem*)p);
   }
   static void destruct_FairTut8RawItem(void *p) {
      typedef ::FairTut8RawItem current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTut8RawItem

//______________________________________________________________________________
void FairTut8Task::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairTut8Task.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairTut8Task::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairTut8Task::Class(),this);
   }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_FairTut8Task(void *p) {
      delete ((::FairTut8Task*)p);
   }
   static void deleteArray_FairTut8Task(void *p) {
      delete [] ((::FairTut8Task*)p);
   }
   static void destruct_FairTut8Task(void *p) {
      typedef ::FairTut8Task current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairTut8Task

namespace {
  void TriggerDictionaryInitialization_G__MbsTutorialDict_Impl() {
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
"/Users/turany/development/FairRoot/base/source",
"/Users/turany/development/FairRoot/examples/advanced/MbsTutorial",
"/Users/turany/development/FairRoot/examples/advanced/MbsTutorial/src",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/advanced/MbsTutorial/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__MbsTutorialDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairTut8Unpack;
class FairTut8RawItem;
class FairTut8Task;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__MbsTutorialDict dictionary payload"

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

#ifndef FAIRTUT8UNPACK_H
#define FAIRTUT8UNPACK_H

#include "FairUnpack.h"

class TClonesArray;

/**
 * An example unpacker of MBS data.
 */
class FairTut8Unpack : public FairUnpack
{
  public:
    /** Standard Constructor. Input - MBS parameters of the detector. */
    FairTut8Unpack(Short_t type = 94,
                   Short_t subType = 9400,
                   Short_t procId = 10,
                   Short_t subCrate = 1,
                   Short_t control = 3);

    /** Destructor. */
    virtual ~FairTut8Unpack();

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

  protected:
    /** Register the output structures. */
    virtual void Register();

  private:
    TClonesArray* fRawData; /**< Array of output raw items. */
    Int_t fNHits;           /**< Number of raw items in current event. */
    Int_t fNHitsTotal;      /**< Total number of raw items. */

    FairTut8Unpack(const FairTut8Unpack&);
    FairTut8Unpack& operator=(const FairTut8Unpack&);
  public:
    // Class definition
    ClassDef(FairTut8Unpack, 1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRTUT8RAWITEM_H
#define FAIRTUT8RAWITEM_H

#include "TObject.h"

/**
 * An example class for raw data object of a detector.
 */
class FairTut8RawItem : public TObject
{
  public:
    /** Default Constructor. */
    FairTut8RawItem();

    /** Standard Constructor.
     * @param sam        a SAM value
     * @param gtb        a GTB value
     * @param tacAddr    TAC module address
     * @param tacCh      TAC channel number
     * @param cal        calibration bit
     * @param clock      clock data
     * @param tacData    TAC data
     * @param qdcData    QDC data
     **/
    FairTut8RawItem(UShort_t sam,
                    UShort_t gtb,
                    UShort_t tacAddr,
                    UShort_t tacCh,
                    UShort_t cal,
                    UShort_t clock,
                    UShort_t tacData,
                    UShort_t qdcData);

    FairTut8RawItem(const FairTut8RawItem&);

    /** Destructor. */
    virtual ~FairTut8RawItem()
    {
    }

    inline const UShort_t& GetSam() const
    {
        return fSam;
    }
    inline const UShort_t& GetGtb() const
    {
        return fGtb;
    }
    inline const UShort_t& GetTacCh() const
    {
        return fTacCh;
    }
    inline const UShort_t& GetTacAddr() const
    {
        return fTacAddr;
    }
    inline const UShort_t& GetCal() const
    {
        return fCal;
    }
    inline const UShort_t& GetClock() const
    {
        return fClock;
    }
    inline const UShort_t& GetTacData() const
    {
        return fTacData;
    }
    inline const UShort_t& GetQdcData() const
    {
        return fQdcData;
    }

  protected:
    UShort_t fSam;     /**< SAM value. */
    UShort_t fGtb;     /**< GTB value. */
    UShort_t fTacAddr; /**< TAC module address. */
    UShort_t fTacCh;   /**< TAC channel number. */
    UShort_t fCal;     /**< Calibration bit. */
    UShort_t fClock;   /**< Clock data. */
    UShort_t fTacData; /**< TAC data. */
    UShort_t fQdcData; /**< QDC data. */

  public:
    ClassDef(FairTut8RawItem, 1)
};

#endif
/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef _FAIRTUT8_TASK_
#define _FAIRTUT8_TASK_

#include "FairTask.h"

class TClonesArray;
class TH1F;

/**
 * An example analysis task for demonstartion of THttpServer usage.
 * Loops over detector raw items in an event and fills the histogram.
 */
class FairTut8Task : public FairTask
{
  public:
    /** Standard Constructor. */
    FairTut8Task(const char* name, Int_t iVerbose);
    
    /** Destructor. */
    virtual ~FairTut8Task();

    /** Initialization of the task. */
    virtual InitStatus Init();

    /** Process an event. */
    virtual void Exec(Option_t*);

    /** Called at the end of each event. */
    virtual void FinishEvent();

    /** Called at the end of task. */
    virtual void FinishTask();

  private:
    TClonesArray* fRawData; /**< Array with input data. */
    TH1F* fhQdc;            /**< Histogram object which is registered on http server. */
    TH1F* fhTac;
    TH1F* fhClock;
    TH1F* fhTacCh;

    FairTut8Task(const FairTut8Task&);
    FairTut8Task& operator=(const FairTut8Task&);

  public:
    ClassDef(FairTut8Task, 1)
};

#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairTut8RawItem", payloadCode, "@",
"FairTut8Task", payloadCode, "@",
"FairTut8Unpack", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__MbsTutorialDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__MbsTutorialDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__MbsTutorialDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__MbsTutorialDict() {
  TriggerDictionaryInitialization_G__MbsTutorialDict_Impl();
}

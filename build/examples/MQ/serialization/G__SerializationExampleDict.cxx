// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIMQdIserializationdIG__SerializationExampleDict

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
#include "data_struct/MyDigi.h"
#include "data_struct/MyHit.h"
#include "data_struct/MyPodData.h"

// Header files passed via #pragma extra_include

namespace MyPodData {
   namespace ROOT {
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance();
      static TClass *MyPodData_Dictionary();

      // Function generating the singleton type initializer
      inline ::ROOT::TGenericClassInfo *GenerateInitInstance()
      {
         static ::ROOT::TGenericClassInfo 
            instance("MyPodData", 0 /*version*/, "invalid", 247,
                     ::ROOT::Internal::DefineBehavior((void*)0,(void*)0),
                     &MyPodData_Dictionary, 0);
         return &instance;
      }
      // Insure that the inline function is _not_ optimized away by the compiler
      ::ROOT::TGenericClassInfo *(*_R__UNIQUE_(InitFunctionKeeper))() = &GenerateInitInstance;  
      // Static variable to force the class initialization
      static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstance(); R__UseDummy(_R__UNIQUE_(Init));

      // Dictionary for non-ClassDef classes
      static TClass *MyPodData_Dictionary() {
         return GenerateInitInstance()->GetClass();
      }

   }
}

namespace ROOT {
   static void *new_MyDigi(void *p = 0);
   static void *newArray_MyDigi(Long_t size, void *p);
   static void delete_MyDigi(void *p);
   static void deleteArray_MyDigi(void *p);
   static void destruct_MyDigi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyDigi*)
   {
      ::MyDigi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyDigi >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyDigi", ::MyDigi::Class_Version(), "invalid", 36,
                  typeid(::MyDigi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MyDigi::Dictionary, isa_proxy, 4,
                  sizeof(::MyDigi) );
      instance.SetNew(&new_MyDigi);
      instance.SetNewArray(&newArray_MyDigi);
      instance.SetDelete(&delete_MyDigi);
      instance.SetDeleteArray(&deleteArray_MyDigi);
      instance.SetDestructor(&destruct_MyDigi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyDigi*)
   {
      return GenerateInitInstanceLocal((::MyDigi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyDigi*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_MyHit(void *p = 0);
   static void *newArray_MyHit(Long_t size, void *p);
   static void delete_MyHit(void *p);
   static void deleteArray_MyHit(void *p);
   static void destruct_MyHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyHit*)
   {
      ::MyHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyHit", ::MyHit::Class_Version(), "invalid", 182,
                  typeid(::MyHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MyHit::Dictionary, isa_proxy, 4,
                  sizeof(::MyHit) );
      instance.SetNew(&new_MyHit);
      instance.SetNewArray(&newArray_MyHit);
      instance.SetDelete(&delete_MyHit);
      instance.SetDeleteArray(&deleteArray_MyHit);
      instance.SetDestructor(&destruct_MyHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyHit*)
   {
      return GenerateInitInstanceLocal((::MyHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static TClass *MyPodDatacLcLTimeStamp_Dictionary();
   static void MyPodDatacLcLTimeStamp_TClassManip(TClass*);
   static void *new_MyPodDatacLcLTimeStamp(void *p = 0);
   static void *newArray_MyPodDatacLcLTimeStamp(Long_t size, void *p);
   static void delete_MyPodDatacLcLTimeStamp(void *p);
   static void deleteArray_MyPodDatacLcLTimeStamp(void *p);
   static void destruct_MyPodDatacLcLTimeStamp(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyPodData::TimeStamp*)
   {
      ::MyPodData::TimeStamp *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyPodData::TimeStamp));
      static ::ROOT::TGenericClassInfo 
         instance("MyPodData::TimeStamp", "invalid", 250,
                  typeid(::MyPodData::TimeStamp), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyPodDatacLcLTimeStamp_Dictionary, isa_proxy, 4,
                  sizeof(::MyPodData::TimeStamp) );
      instance.SetNew(&new_MyPodDatacLcLTimeStamp);
      instance.SetNewArray(&newArray_MyPodDatacLcLTimeStamp);
      instance.SetDelete(&delete_MyPodDatacLcLTimeStamp);
      instance.SetDeleteArray(&deleteArray_MyPodDatacLcLTimeStamp);
      instance.SetDestructor(&destruct_MyPodDatacLcLTimeStamp);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyPodData::TimeStamp*)
   {
      return GenerateInitInstanceLocal((::MyPodData::TimeStamp*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyPodData::TimeStamp*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyPodDatacLcLTimeStamp_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyPodData::TimeStamp*)0x0)->GetClass();
      MyPodDatacLcLTimeStamp_TClassManip(theClass);
   return theClass;
   }

   static void MyPodDatacLcLTimeStamp_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyPodDatacLcLDigi_Dictionary();
   static void MyPodDatacLcLDigi_TClassManip(TClass*);
   static void *new_MyPodDatacLcLDigi(void *p = 0);
   static void *newArray_MyPodDatacLcLDigi(Long_t size, void *p);
   static void delete_MyPodDatacLcLDigi(void *p);
   static void deleteArray_MyPodDatacLcLDigi(void *p);
   static void destruct_MyPodDatacLcLDigi(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyPodData::Digi*)
   {
      ::MyPodData::Digi *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyPodData::Digi));
      static ::ROOT::TGenericClassInfo 
         instance("MyPodData::Digi", "invalid", 269,
                  typeid(::MyPodData::Digi), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyPodDatacLcLDigi_Dictionary, isa_proxy, 4,
                  sizeof(::MyPodData::Digi) );
      instance.SetNew(&new_MyPodDatacLcLDigi);
      instance.SetNewArray(&newArray_MyPodDatacLcLDigi);
      instance.SetDelete(&delete_MyPodDatacLcLDigi);
      instance.SetDeleteArray(&deleteArray_MyPodDatacLcLDigi);
      instance.SetDestructor(&destruct_MyPodDatacLcLDigi);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyPodData::Digi*)
   {
      return GenerateInitInstanceLocal((::MyPodData::Digi*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyPodData::Digi*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyPodDatacLcLDigi_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyPodData::Digi*)0x0)->GetClass();
      MyPodDatacLcLDigi_TClassManip(theClass);
   return theClass;
   }

   static void MyPodDatacLcLDigi_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *MyPodDatacLcLHit_Dictionary();
   static void MyPodDatacLcLHit_TClassManip(TClass*);
   static void *new_MyPodDatacLcLHit(void *p = 0);
   static void *newArray_MyPodDatacLcLHit(Long_t size, void *p);
   static void delete_MyPodDatacLcLHit(void *p);
   static void deleteArray_MyPodDatacLcLHit(void *p);
   static void destruct_MyPodDatacLcLHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyPodData::Hit*)
   {
      ::MyPodData::Hit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::MyPodData::Hit));
      static ::ROOT::TGenericClassInfo 
         instance("MyPodData::Hit", "invalid", 291,
                  typeid(::MyPodData::Hit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &MyPodDatacLcLHit_Dictionary, isa_proxy, 4,
                  sizeof(::MyPodData::Hit) );
      instance.SetNew(&new_MyPodDatacLcLHit);
      instance.SetNewArray(&newArray_MyPodDatacLcLHit);
      instance.SetDelete(&delete_MyPodDatacLcLHit);
      instance.SetDeleteArray(&deleteArray_MyPodDatacLcLHit);
      instance.SetDestructor(&destruct_MyPodDatacLcLHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyPodData::Hit*)
   {
      return GenerateInitInstanceLocal((::MyPodData::Hit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyPodData::Hit*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *MyPodDatacLcLHit_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::MyPodData::Hit*)0x0)->GetClass();
      MyPodDatacLcLHit_TClassManip(theClass);
   return theClass;
   }

   static void MyPodDatacLcLHit_TClassManip(TClass* ){
   }

} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr MyDigi::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyDigi::Class_Name()
{
   return "MyDigi";
}

//______________________________________________________________________________
const char *MyDigi::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyDigi*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyDigi::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyDigi*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyDigi::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyDigi*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyDigi::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyDigi*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr MyHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyHit::Class_Name()
{
   return "MyHit";
}

//______________________________________________________________________________
const char *MyHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void MyDigi::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyDigi.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyDigi::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyDigi::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyDigi(void *p) {
      return  p ? new(p) ::MyDigi : new ::MyDigi;
   }
   static void *newArray_MyDigi(Long_t nElements, void *p) {
      return p ? new(p) ::MyDigi[nElements] : new ::MyDigi[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyDigi(void *p) {
      delete ((::MyDigi*)p);
   }
   static void deleteArray_MyDigi(void *p) {
      delete [] ((::MyDigi*)p);
   }
   static void destruct_MyDigi(void *p) {
      typedef ::MyDigi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyDigi

//______________________________________________________________________________
void MyHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(MyHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(MyHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyHit(void *p) {
      return  p ? new(p) ::MyHit : new ::MyHit;
   }
   static void *newArray_MyHit(Long_t nElements, void *p) {
      return p ? new(p) ::MyHit[nElements] : new ::MyHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyHit(void *p) {
      delete ((::MyHit*)p);
   }
   static void deleteArray_MyHit(void *p) {
      delete [] ((::MyHit*)p);
   }
   static void destruct_MyHit(void *p) {
      typedef ::MyHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyHit

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyPodDatacLcLTimeStamp(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::MyPodData::TimeStamp : new ::MyPodData::TimeStamp;
   }
   static void *newArray_MyPodDatacLcLTimeStamp(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::MyPodData::TimeStamp[nElements] : new ::MyPodData::TimeStamp[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyPodDatacLcLTimeStamp(void *p) {
      delete ((::MyPodData::TimeStamp*)p);
   }
   static void deleteArray_MyPodDatacLcLTimeStamp(void *p) {
      delete [] ((::MyPodData::TimeStamp*)p);
   }
   static void destruct_MyPodDatacLcLTimeStamp(void *p) {
      typedef ::MyPodData::TimeStamp current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyPodData::TimeStamp

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyPodDatacLcLDigi(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::MyPodData::Digi : new ::MyPodData::Digi;
   }
   static void *newArray_MyPodDatacLcLDigi(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::MyPodData::Digi[nElements] : new ::MyPodData::Digi[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyPodDatacLcLDigi(void *p) {
      delete ((::MyPodData::Digi*)p);
   }
   static void deleteArray_MyPodDatacLcLDigi(void *p) {
      delete [] ((::MyPodData::Digi*)p);
   }
   static void destruct_MyPodDatacLcLDigi(void *p) {
      typedef ::MyPodData::Digi current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyPodData::Digi

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyPodDatacLcLHit(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::MyPodData::Hit : new ::MyPodData::Hit;
   }
   static void *newArray_MyPodDatacLcLHit(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::MyPodData::Hit[nElements] : new ::MyPodData::Hit[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyPodDatacLcLHit(void *p) {
      delete ((::MyPodData::Hit*)p);
   }
   static void deleteArray_MyPodDatacLcLHit(void *p) {
      delete [] ((::MyPodData::Hit*)p);
   }
   static void destruct_MyPodDatacLcLHit(void *p) {
      typedef ::MyPodData::Hit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::MyPodData::Hit

namespace {
  void TriggerDictionaryInitialization_G__SerializationExampleDict_Impl() {
    static const char* headers[] = {
0    };
    static const char* includePaths[] = {
"/Users/turany/development/FairRoot/build/examples/MQ/serialization",
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
"/Users/turany/development/FairRoot/fairmq/devices",
"/Users/turany/development/FairRoot/fairmq/options",
"/Users/turany/development/FairRoot/fairmq/tools",
"/Users/turany/development/FairRoot/fairmq/nanomsg",
"/Users/turany/development/FairRoot/fairmq/zeromq",
"/Users/turany/development/FairRoot/base/MQ",
"/Users/turany/development/FairRoot/base/MQ/devices",
"/Users/turany/development/FairRoot/base/MQ/policies/Sampler",
"/Users/turany/development/FairRoot/base/MQ/policies/Serialization",
"/Users/turany/development/FairRoot/base/MQ/policies/Storage",
"/Users/turany/development/FairRoot/base/MQ/baseMQtools",
"/Users/turany/development/FairRoot/examples/MQ/serialization",
"/Users/turany/development/FairRoot/examples/MQ/serialization/data_generator",
"/Users/turany/development/FairRoot/examples/MQ/serialization/data_struct",
"/Users/turany/development/FairRoot/examples/MQ/serialization/src/1-simple/devices",
"/Users/turany/development/FairRoot/examples/MQ/serialization/src/2-multi-part/devices",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/MQ/serialization/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__SerializationExampleDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class MyDigi;
class MyHit;
namespace MyPodData{class TimeStamp;}
namespace MyPodData{class Digi;}
namespace MyPodData{class Hit;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__SerializationExampleDict dictionary payload"

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
 * File:   MyDigi.h
 * Author: winckler
 *
 * Created on November 24, 2014, 1:31 PM
 */

#ifndef MYDIGIDATA_H
#define	MYDIGIDATA_H

#include "FairTimeStamp.h" // for FairTimeStamp

#include "Riosfwd.h" // for ostream
#include "Rtypes.h"  // for Int_t, etc

#include <iostream> // for operator<<, basic_ostream, etc

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class MyDigi : public FairTimeStamp
{
  public:
    MyDigi();
    MyDigi(Int_t x, Int_t y, Int_t z, Double_t timeStamp, Double_t timeStampError=0.0);
    virtual ~MyDigi();

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
        MyDigi* myDigi = dynamic_cast<MyDigi*>(data);
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

    virtual bool operator<(const MyDigi& myDigi) const
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

    friend std::ostream& operator<<(std::ostream& out, MyDigi& digi)
    {
        out << "MyDigi at:"
            << " (" << digi.GetX() << "/" << digi.GetY() << "/" << digi.GetZ() << ") "
            << " with TimeStamp: " << digi.GetTimeStamp() << std::endl;
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

    ClassDef(MyDigi, 1);
};

#endif	/* MYDIGIDATA_H */

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   MyHit.h
 * Author: winckler
 *
 * Created on November 24, 2014, 1:40 PM
 */

#ifndef MYHITDATA_H
#define	MYHITDATA_H

#include "FairHit.h" // for FairHit

#include "Rtypes.h" // for MyHit::Class, etc

#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

class TVector3;

class MyHit : public FairHit
{
  public:
    /** Default constructor **/
    MyHit();

    /** Constructor **/
    MyHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos);
    MyHit(Int_t detID, Int_t mcindex, TVector3& pos, TVector3& dpos, Double_t timeStamp, Double_t timeStampError);

    /** Destructor **/
    virtual ~MyHit();

    template <class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar& boost::serialization::base_object<FairHit>(*this);
    }

  private:
#ifndef __CINT__ // for BOOST serialization
    friend class boost::serialization::access;

#endif // for BOOST serialization

    ClassDef(MyHit, 1);
};


#endif	/* MYHITDATA_H */

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   MyPodData.h
 * Author: winckler
 *
 * Created on November 24, 2014, 1:46 PM
 */

#ifndef MYPODDATA_H
#define	MYPODDATA_H

// for root types
#include "Riosfwd.h"
#include "Rtypes.h" 

// for boost serialization (must be hidden from CINT)
#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif

namespace MyPodData
{

    class TimeStamp
    {
      public:
        Double_t fTimeStamp;
        Double_t fTimeStampError;
        
        // method to use boost serialization
        #ifndef __CINT__
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/) 
        {
            ar & fTimeStamp;
            ar & fTimeStampError;
        }
        friend class boost::serialization::access;
        #endif //__CINT__
        
    };

    class Digi : public TimeStamp
    {
      public:
        Int_t fX;
        Int_t fY;
        Int_t fZ;
        
        // method to use boost serialization
        #ifndef __CINT__
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/) 
        {
            ar & boost::serialization::base_object<TimeStamp>(*this);
            ar & fX;
            ar & fY;
            ar & fZ;
        }
        friend class boost::serialization::access;
        #endif //__CINT__
        
    };

    class Hit : public TimeStamp
    {
      public:
        Int_t detID;
        Int_t mcindex;
        Double_t posX;
        Double_t posY;
        Double_t posZ;
        Double_t dposX;
        Double_t dposY;
        Double_t dposZ;
        
        // method to use boost serialization
        #ifndef __CINT__
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/) 
        {
            ar & boost::serialization::base_object<TimeStamp>(*this);
            ar & detID;
            ar & mcindex;
            ar & posX;
            ar & posY;
            ar & posZ;
            ar & dposX;
            ar & dposY;
            ar & dposZ;
        }
        friend class boost::serialization::access;
        #endif //__CINT__
    };
}

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#endif	/* MYPODDATA_H */


#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"MyDigi", payloadCode, "@",
"MyHit", payloadCode, "@",
"MyPodData::Digi", payloadCode, "@",
"MyPodData::Hit", payloadCode, "@",
"MyPodData::TimeStamp", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__SerializationExampleDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__SerializationExampleDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__SerializationExampleDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__SerializationExampleDict() {
  TriggerDictionaryInitialization_G__SerializationExampleDict_Impl();
}

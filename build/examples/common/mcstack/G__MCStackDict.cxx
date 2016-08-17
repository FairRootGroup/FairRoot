// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIUsersdIturanydIdevelopmentdIFairRootdIbuilddIexamplesdIcommondImcstackdIG__MCStackDict

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
#include "FairStack.h"
#include "FairMCTrack.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_FairStack(void *p = 0);
   static void *newArray_FairStack(Long_t size, void *p);
   static void delete_FairStack(void *p);
   static void deleteArray_FairStack(void *p);
   static void destruct_FairStack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairStack*)
   {
      ::FairStack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairStack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairStack", ::FairStack::Class_Version(), "invalid", 60,
                  typeid(::FairStack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairStack::Dictionary, isa_proxy, 4,
                  sizeof(::FairStack) );
      instance.SetNew(&new_FairStack);
      instance.SetNewArray(&newArray_FairStack);
      instance.SetDelete(&delete_FairStack);
      instance.SetDeleteArray(&deleteArray_FairStack);
      instance.SetDestructor(&destruct_FairStack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairStack*)
   {
      return GenerateInitInstanceLocal((::FairStack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairStack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FairMCTrack(void *p = 0);
   static void *newArray_FairMCTrack(Long_t size, void *p);
   static void delete_FairMCTrack(void *p);
   static void deleteArray_FairMCTrack(void *p);
   static void destruct_FairMCTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FairMCTrack*)
   {
      ::FairMCTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FairMCTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("FairMCTrack", ::FairMCTrack::Class_Version(), "invalid", 313,
                  typeid(::FairMCTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FairMCTrack::Dictionary, isa_proxy, 4,
                  sizeof(::FairMCTrack) );
      instance.SetNew(&new_FairMCTrack);
      instance.SetNewArray(&newArray_FairMCTrack);
      instance.SetDelete(&delete_FairMCTrack);
      instance.SetDeleteArray(&deleteArray_FairMCTrack);
      instance.SetDestructor(&destruct_FairMCTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FairMCTrack*)
   {
      return GenerateInitInstanceLocal((::FairMCTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::FairMCTrack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FairStack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairStack::Class_Name()
{
   return "FairStack";
}

//______________________________________________________________________________
const char *FairStack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairStack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairStack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairStack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairStack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairStack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairStack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairStack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FairMCTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *FairMCTrack::Class_Name()
{
   return "FairMCTrack";
}

//______________________________________________________________________________
const char *FairMCTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int FairMCTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FairMCTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FairMCTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FairMCTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FairMCTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FairStack::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairStack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairStack::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairStack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairStack(void *p) {
      return  p ? new(p) ::FairStack : new ::FairStack;
   }
   static void *newArray_FairStack(Long_t nElements, void *p) {
      return p ? new(p) ::FairStack[nElements] : new ::FairStack[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairStack(void *p) {
      delete ((::FairStack*)p);
   }
   static void deleteArray_FairStack(void *p) {
      delete [] ((::FairStack*)p);
   }
   static void destruct_FairStack(void *p) {
      typedef ::FairStack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairStack

//______________________________________________________________________________
void FairMCTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class FairMCTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FairMCTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(FairMCTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FairMCTrack(void *p) {
      return  p ? new(p) ::FairMCTrack : new ::FairMCTrack;
   }
   static void *newArray_FairMCTrack(Long_t nElements, void *p) {
      return p ? new(p) ::FairMCTrack[nElements] : new ::FairMCTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_FairMCTrack(void *p) {
      delete ((::FairMCTrack*)p);
   }
   static void deleteArray_FairMCTrack(void *p) {
      delete [] ((::FairMCTrack*)p);
   }
   static void destruct_FairMCTrack(void *p) {
      typedef ::FairMCTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::FairMCTrack

namespace {
  void TriggerDictionaryInitialization_G__MCStackDict_Impl() {
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
"/Users/turany/development/FairRoot/examples/common/mcstack",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/install/RC_may16_R6/include",
"/Users/turany/development/install/RC_may16_R6/include/root",
"/Users/turany/development/FairRoot/build/examples/common/mcstack/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "G__MCStackDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class FairStack;
class FairMCTrack;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "G__MCStackDict dictionary payload"

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
// -------------------------------------------------------------------------
// -----                       FairStack header file                    -----
// -----           Created 10/08/04  by D. Bertini / V. Friese         -----
// -------------------------------------------------------------------------


/** FairStack.h
 *@author D.Bertini <d.bertini@gsi.de>
 *@author V.Friese <v.friese@gsi.de>
 **
 ** Version 14/06/07 by V. Friese
 **
 ** This class handles the particle stack for the transport simulation.
 ** For the stack FILO functunality, it uses the STL stack. To store
 ** the tracks during transport, a TParticle arry is used.
 ** At the end of the event, tracks satisfying the filter criteria
 ** are copied to a FairMCTrack array, which is stored in the output.
 **
 ** The filtering criteria for the output tracks are:
 ** - primary tracks are stored in any case.
 ** - secondary tracks are stored if they have a minimal number of
 **   points (sum of all detectors) and a minimal energy, or are the
 **
 ** The storage of secondaries can be switched off.
 ** The storage of all mothers can be switched off.
 ** By default, the minimal number of points is 1 and the energy cut is 0.
 **/


#ifndef FAIRSTACK_H
#define FAIRSTACK_H

#include "FairGenericStack.h"           // for FairGenericStack

#include "FairDetectorList.h"           // for DetectorId

#include "Rtypes.h"                     // for Int_t, Double_t, Bool_t, etc
#include "TMCProcess.h"                 // for TMCProcess

#include <map>                          // for map, map<>::iterator
#include <stack>                        // for stack
#include <utility>                      // for pair

class TClonesArray;
class TParticle;
class TRefArray;

class FairStack : public FairGenericStack
{

  public:

    /** Default constructor
     *param size  Estimated track number
     **/
    FairStack(Int_t size = 100);


    /** Destructor  **/
    virtual ~FairStack();


    /** Add a TParticle to the stack.
     ** Declared in TVirtualMCStack
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

    virtual void PushTrack(Int_t toBeDone, Int_t parentID, Int_t pdgCode,
                           Double_t px, Double_t py, Double_t pz,
                           Double_t e, Double_t vx, Double_t vy,
                           Double_t vz, Double_t time, Double_t polx,
                           Double_t poly, Double_t polz, TMCProcess proc,
                           Int_t& ntr, Double_t weight, Int_t is,Int_t secondParentId);




    /** Get next particle for tracking from the stack.
     ** Declared in TVirtualMCStack
     *@param  iTrack  index of popped track (return)
     *@return Pointer to the TParticle of the track
     **/
    virtual TParticle* PopNextTrack(Int_t& iTrack);


    /** Get primary particle by index for tracking from stack
     ** Declared in TVirtualMCStack
     *@param  iPrim   index of primary particle
     *@return Pointer to the TParticle of the track
     **/
    virtual TParticle* PopPrimaryForTracking(Int_t iPrim);


    /** Set the current track number
     ** Declared in TVirtualMCStack
     *@param iTrack  track number
     **/
    virtual void SetCurrentTrack(Int_t iTrack)   { fCurrentTrack     = iTrack; }


    /** Get total number of tracks
     ** Declared in TVirtualMCStack
     **/
    virtual Int_t GetNtrack() const { return fNParticles; }


    /** Get number of primary tracks
     ** Declared in TVirtualMCStack
     **/
    virtual Int_t GetNprimary() const { return fNPrimaries; }


    /** Get the current track's particle
     ** Declared in TVirtualMCStack
     **/
    virtual TParticle* GetCurrentTrack() const;


    /** Get the number of the current track
     ** Declared in TVirtualMCStack
     **/
    virtual Int_t GetCurrentTrackNumber() const { return fCurrentTrack; }


    /** Get the track number of the parent of the current track
     ** Declared in TVirtualMCStack
     **/
    virtual Int_t GetCurrentParentTrackNumber() const;


    /** Add a TParticle to the fParticles array **/
    virtual void AddParticle(TParticle* part);


    /** Fill the MCTrack output array, applying filter criteria **/
    virtual void FillTrackArray();


    /** Update the track index in the MCTracks and MCPoints **/
    virtual void UpdateTrackIndex(TRefArray* detArray=0);


    /** Resets arrays and stack and deletes particles and tracks **/
    virtual void Reset();


    /** Register the MCTrack array to the Root Manager  **/
    virtual void Register();


    /** Output to screen
     **@param iVerbose: 0=events summary, 1=track info
     **/
    virtual void Print(Option_t*) const;


    /** Modifiers  **/
    void StoreSecondaries(Bool_t choice = kTRUE) { fStoreSecondaries = choice; }
    void SetMinPoints(Int_t min)                 { fMinPoints        = min;    }
    void SetEnergyCut(Double_t eMin)             { fEnergyCut        = eMin;   }
    void StoreMothers(Bool_t choice = kTRUE)     { fStoreMothers     = choice; }


    /** Increment number of points for the current track in a given detector
     *@param iDet  Detector unique identifier
     **/
    void AddPoint(DetectorId iDet);


    /** Increment number of points for an arbitrary track in a given detector
     *@param iDet    Detector unique identifier
     *@param iTrack  Track number
     **/
    void AddPoint(DetectorId iDet, Int_t iTrack);


    /** Accessors **/
    TParticle* GetParticle(Int_t trackId) const;
    TClonesArray* GetListOfParticles() { return fParticles; }

    /** Clone this object (used in MT mode only) */
    virtual FairGenericStack* CloneStack() const { return new FairStack(); }

  private:
    /** STL stack (FILO) used to handle the TParticles for tracking **/
    std::stack<TParticle*>  fStack;           //!


    /** Array of TParticles (contains all TParticles put into or created
     ** by the transport
     **/
    TClonesArray* fParticles;            //!


    /** Array of FairMCTracks containg the tracks written to the output **/
    TClonesArray* fTracks;


    /** STL map from particle index to storage flag  **/
    std::map<Int_t, Bool_t>           fStoreMap;        //!
    std::map<Int_t, Bool_t>::iterator fStoreIter;       //!


    /** STL map from particle index to track index  **/
    std::map<Int_t, Int_t>            fIndexMap;        //!
    std::map<Int_t, Int_t>::iterator  fIndexIter;       //!


    /** STL map from track index and detector ID to number of MCPoints **/
    std::map<std::pair<Int_t, Int_t>, Int_t> fPointsMap;     //!


    /** Some indizes and counters **/
    Int_t fCurrentTrack;  //! Index of current track
    Int_t fNPrimaries;    //! Number of primary particles
    Int_t fNParticles;    //! Number of entries in fParticles
    Int_t fNTracks;       //! Number of entries in fTracks
    Int_t fIndex;         //! Used for merging


    /** Variables defining the criteria for output selection **/
    Bool_t     fStoreSecondaries;
    Int_t      fMinPoints;
    Double32_t fEnergyCut;
    Bool_t     fStoreMothers;


    /** Mark tracks for output using selection criteria  **/
    void SelectTracks();

    FairStack(const FairStack&);
    FairStack& operator=(const FairStack&);

    ClassDef(FairStack,1)


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
// -----                      FairMCTrack header file                   -----
// -----                  Created 03/08/04  by V. Friese               -----
// -------------------------------------------------------------------------


/** FairMCTrack.h
 *@author V.Friese <v.friese@gsi.de>
 **
 ** Data class for storing Monte Carlo tracks processed by the FairStack.
 ** A MCTrack can be a primary track put into the simulation or a
 ** secondary one produced by the transport through decay or interaction.
 **
 ** Redesign 13/06/07 by V. Friese
 **/


#ifndef FAIRMCTRACK_H
#define FAIRMCTRACK_H 1

#include "TObject.h"                    // for TObject

#include "FairDetectorList.h"           // for DetectorId

#include "Rtypes.h"                     // for Double_t, Int_t, Double32_t, etc
#include "TLorentzVector.h"             // for TLorentzVector
#include "TMath.h"                      // for Sqrt
#include "TVector3.h"                   // for TVector3

class TParticle;

class FairMCTrack : public TObject
{

  public:


    /**  Default constructor  **/
    FairMCTrack();


    /**  Standard constructor  **/
    FairMCTrack(Int_t pdgCode, Int_t motherID, Double_t px, Double_t py,
                Double_t pz, Double_t x, Double_t y, Double_t z,
                Double_t t, Int_t nPoints);

    /**  Copy constructor  **/
    FairMCTrack(const FairMCTrack& track);


    /**  Constructor from TParticle  **/
    FairMCTrack(TParticle* particle);


    /**  Destructor  **/
    virtual ~FairMCTrack();


#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Woverloaded-virtual"
#endif
    /**  Output to screen  **/
    virtual void Print(Int_t iTrack) const;
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
    /**  Accessors  **/
    Int_t    GetPdgCode()  const { return fPdgCode; }
    Int_t    GetMotherId() const { return fMotherId; }
    Double_t GetPx()       const { return fPx; }
    Double_t GetPy()       const { return fPy; }
    Double_t GetPz()       const { return fPz; }
    Double_t GetStartX()   const { return fStartX; }
    Double_t GetStartY()   const { return fStartY; }
    Double_t GetStartZ()   const { return fStartZ; }
    Double_t GetStartT()   const { return fStartT; }
    Double_t GetMass()     const;
    Double_t GetEnergy()   const;
    Double_t GetPt()       const { return TMath::Sqrt(fPx*fPx+fPy*fPy); }
    Double_t GetP() const { return TMath::Sqrt(fPx*fPx+fPy*fPy+fPz*fPz); }
    Double_t GetRapidity() const;
    void GetMomentum(TVector3& momentum);
    void Get4Momentum(TLorentzVector& momentum);
    void GetStartVertex(TVector3& vertex);


    /** Accessors to the number of MCPoints in the detectors **/
    Int_t GetNPoints(DetectorId detId)  const;


    /**  Modifiers  **/
    void SetMotherId(Int_t id) { fMotherId = id; }
    void SetNPoints(Int_t iDet, Int_t np);



  private:

    /**  PDG particle code  **/
    Int_t  fPdgCode;

    /**  Index of mother track. -1 for primary particles.  **/
    Int_t  fMotherId;

    /** Momentum components at start vertex [GeV]  **/
    Double32_t fPx, fPy, fPz;

    /** Coordinates of start vertex [cm, ns]  **/
    Double32_t fStartX, fStartY, fStartZ, fStartT;

    /**  Bitvector representing the number of MCPoints for this track in
     **  each subdetector. The detectors are represented by
     **  REF:         Bit  0      (1 bit,  max. value  1)
     **  MVD:         Bit  1 -  3 (3 bits, max. value  7)
     **  STS:         Bit  4 -  8 (5 bits, max. value 31)
     **  RICH:        Bit  9      (1 bit,  max. value  1)
     **  MUCH:        Bit 10 - 14 (5 bits, max. value 31)
     **  TRD:         Bit 15 - 19 (5 bits, max. value 31)
     **  TOF:         Bit 20 - 23 (4 bits, max. value 15)
     **  ECAL:        Bit 24      (1 bit,  max. value  1)
     **  ZDC:         Bit 25      (1 bit,  max. value  1)
     **  The respective point numbers can be accessed and modified
     **  with the inline functions.
     **  Bits 26-31 are spare for potential additional detectors.
     **/
    Int_t fNPoints;


    ClassDef(FairMCTrack,2);

};



// ==========   Inline functions   ========================================

inline Double_t FairMCTrack::GetEnergy() const
{
  Double_t mass = GetMass();
  return TMath::Sqrt(mass*mass + fPx*fPx + fPy*fPy + fPz*fPz );
}


inline void FairMCTrack::GetMomentum(TVector3& momentum)
{
  momentum.SetXYZ(fPx,fPy,fPz);
}


inline void FairMCTrack::Get4Momentum(TLorentzVector& momentum)
{
  momentum.SetXYZT(fPx,fPy,fPz,GetEnergy());
}


inline void FairMCTrack::GetStartVertex(TVector3& vertex)
{
  vertex.SetXYZ(fStartX,fStartY,fStartZ);
}





#endif

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"FairMCTrack", payloadCode, "@",
"FairStack", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("G__MCStackDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_G__MCStackDict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_G__MCStackDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_G__MCStackDict() {
  TriggerDictionaryInitialization_G__MCStackDict_Impl();
}

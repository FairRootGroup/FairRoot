/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

//------------------------------------------------
// The Geant4 Virtual Monte Carlo package
// Copyright (C) 2013, 2014 Ivana Hrivnacova
// All rights reserved.
//
// For the licensing terms see geant4_vmc/LICENSE.
// Contact: root-vmc@cern.ch
//-------------------------------------------------

/// \file FairGenericRootManager.h
/// \brief Definition of the FairGenericRootManager class
///
/// TVirtualMCRootManager class adapted for FairRoot.
///
/// \author I. Hrivnacova; IPN Orsay

#ifndef ROOT_FairGenericRootManager
#define ROOT_FairGenericRootManager

#include "TObject.h"
#include "TMCtls.h"

class FairWriteoutBuffer;
class FairRootManager;
class TClonesArray; 

/// \brief The interface to the Root IO manager for FairRoot multi-threaded applications.
///
/// Implemented according to TVirtualMCRootManager from Geant4 VMC.

class FairGenericRootManager : public TObject
{
  public:
    FairGenericRootManager();
    virtual ~FairGenericRootManager();     
  
    // static access method
    static FairGenericRootManager* Instance(); 
    
    // static method for activating debug mode
    static void SetDebug(Bool_t debug); 
    static Bool_t GetDebug();

    // methods
    virtual void                Register(const char* name, const char* folderName, TNamed* obj, Bool_t toFile) = 0;
    virtual void                Register(const char* name,const char* folderName ,TCollection* obj, Bool_t toFile) = 0;
    virtual void                RegisterInputObject(const char* name, TObject* obj) = 0;
    virtual TClonesArray*       Register(TString branchName, TString className, TString folderName, Bool_t toFile) = 0;
    virtual FairWriteoutBuffer* RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer) = 0;

    virtual void  Fill() = 0;
    virtual void  Write() = 0;
    virtual void  CloseOutFile() = 0;
    // virtual void  WriteAndClose() = 0;

    // access to the implementation class
    virtual FairRootManager*    GetFairRootManager() const = 0;
    virtual Int_t  GetId() const = 0;
    
    // static data members
    static  Bool_t  fgDebug; // Option to activate debug printings

  private:
    // not implemented
    FairGenericRootManager(const FairGenericRootManager& rhs);
    FairGenericRootManager& operator=(const FairGenericRootManager& rhs);
    
#if !defined(__CINT__)
    static  TMCThreadLocal FairGenericRootManager* fgInstance; // singleton instance
#else
    static                 FairGenericRootManager* fgInstance; // singleton instance
#endif 
};

// inline functions

inline void FairGenericRootManager::SetDebug(Bool_t debug) {
  fgDebug = debug;
}  
  
inline Bool_t FairGenericRootManager::GetDebug() {
  return fgDebug;
}  

#endif //ROOT_FairGenericRootManager

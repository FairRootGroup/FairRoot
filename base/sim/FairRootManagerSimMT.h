/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *             GNU Lesser General Public Licence (LGPL) version 3,              *  
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

/// \file FairRootManagerSimMT.h
/// \brief Definition of the FairRootManagerSimMT class
///
/// TMCRootManagerMT class adapted for FairRoot.
///
/// \author I. Hrivnacova; IPN Orsay

#ifndef ROOT_FairRootManagerSimMT
#define ROOT_FairRootManagerSimMT

#include "FairGenericRootManager.h"

#include <vector>

class FairRootManager;
class FairWriteoutBuffer;
class TClonesArray; 

/// \brief The Root IO manager for VMC examples for multi-threaded applications.
///
/// Implemented according to TMCRootManager from Geant4 VMC.
/// It implements the FairGenericRootManager interface.

class FairRootManagerSimMT : public FairGenericRootManager
{
  public:
    FairRootManagerSimMT();
    virtual ~FairRootManagerSimMT();     
  
    // methods
    // virtual void  Register(const char* name, const char* className, void* objAddress);
    // virtual void  Register(const char* name, const char* className, const void* objAddress);
    virtual void                Register(const char* name, const char* folderName, TNamed* obj, Bool_t toFile);
    virtual void                Register(const char* name,const char* folderName ,TCollection* obj, Bool_t toFile);
    virtual void                RegisterInputObject(const char* name, TObject* obj);
    virtual TClonesArray*       Register(TString branchName, TString className, TString folderName, Bool_t toFile);
    virtual FairWriteoutBuffer* RegisterWriteoutBuffer(TString branchName, FairWriteoutBuffer* buffer);

    virtual void  Fill();
    virtual void  Write();
    virtual void  CloseOutFile();

    virtual Int_t GetBranchId(TString const &BrName);

    virtual FairRootManager*    GetFairRootManager() const { return fRootManager; }
    virtual Int_t  GetId() const { return fId; }

  private:
    // not implemented
    FairRootManagerSimMT(const FairRootManagerSimMT& rhs);
    FairRootManagerSimMT& operator=(const FairRootManagerSimMT& rhs);
    
    // methods
    void  LogMessage(const TString& message);
    void  FillWithLock();
    void  FillWithTmpLock();
    void  FillWithoutLock();

    // global static data members
    static  Int_t    fgCounter;         // The counter of instances
    static  Bool_t   fgIsFillLock;      // The if the Fill should be locked 
    static  std::vector<Bool_t>* fgIsFillLocks; // The info per thread if the Fill should be locked

    // data members 
    Int_t             fId;           // This manager ID 
    FairRootManager*  fRootManager;  // The Root manager
};

#endif //ROOT_FairRootManagerSimMT

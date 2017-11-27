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

/// \file FairRootManagerSim.h
/// \brief Definition of the FairRootManagerSim class
///
/// TMCRootManager class adapted for FairRoot.
///
/// \author I. Hrivnacova; IPN Orsay

#ifndef ROOT_FairRootManagerSim
#define ROOT_FairRootManagerSim

#include "FairGenericRootManager.h"

#include <vector>

class FairRootManager;
class FairWriteoutBuffer;
class TClonesArray; 

/// \brief The Root IO manager for FairRoot multi-threaded applications.
///
/// Implemented according to TMCRootManager from Geant4 VMC.
/// It implements the FairGenericRootManager interface.

class FairRootManagerSim : public FairGenericRootManager
{
  public:
    FairRootManagerSim();
    virtual ~FairRootManagerSim();     
  
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
    virtual Int_t  GetId() const { return 0; }

  private:
    // not implemented
    FairRootManagerSim(const FairRootManagerSim& rhs);
    FairRootManagerSim& operator=(const FairRootManagerSim& rhs);

    // data members 
    FairRootManager*  fRootManager;  // The Root manager
};

#endif //ROOT_FairRootManagerSim

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
// -----------------------------------------------------------------------------
// -----                                                                   -----
// -----                             FairSink                            -----
// -----                    Created 01.11.2013 by F. Uhlig                 -----
// -----                                                                   -----
// -----------------------------------------------------------------------------

#ifndef FAIRSINK_H
#define FAIRSINK_H

#include "TFolder.h"
#include "TObject.h"
#include "TTree.h"

#include <iostream>

enum Sink_Type {kONLINESINK, kFILESINK};

class FairSink : public TObject
{
  public:
    FairSink();
    FairSink(const FairSink& sink);
    virtual ~FairSink();

    virtual Bool_t Init() = 0;
    virtual void Close() = 0;

    virtual void Reset() = 0;

    virtual Sink_Type GetSinkType() = 0;

    void  SetRunId(Int_t runId) { fRunId = runId; }
    Int_t GetRunId() const      { return fRunId;  }

    virtual void        SetOutTree(TTree* fTree) = 0;

    virtual void        Fill() = 0;

    virtual Int_t       Write(const char* name=0, Int_t option=0, Int_t bufsize=0) = 0;

    virtual void RegisterImpl(const char* , const char* , void* ) = 0;
    virtual void RegisterAny(const char* brname, const std::type_info &oi, const std::type_info &pi, void* obj) = 0;

    virtual void WriteFolder() = 0;
    virtual bool CreatePersistentBranchesAny() = 0;

    virtual void WriteObject(TObject* f, const char*, Int_t option = 0) = 0;
    virtual void WriteGeometry() = 0;

  protected:
    struct TypeAddressPair {
    TypeAddressPair(const std::type_info &oi, const std::type_info &pi, void* a) : origtypeinfo(oi), persistenttypeinfo(pi), ptraddr(a) {}
      const std::type_info &origtypeinfo; // type_info of type addr points to
      const std::type_info &persistenttypeinfo; // type_info of ROOT persistent branch (drops pointers)
      void *ptraddr; // address of a pointer (pointing to origtypeinfo);
    };

    Int_t fRunId;

    /**folder structure of output*/
    TFolder*                            fOutFolder;
    /// A map of branchnames to typeinformation + memory address;
    /// used for branches registered to bes stored; use of ptr here
    /// since type_info cannot be copied
    std::map<std::string, std::unique_ptr<TypeAddressPair const>> fPersistentBranchesMap; //!

  public:
    ClassDef(FairSink, 1)
};


#endif

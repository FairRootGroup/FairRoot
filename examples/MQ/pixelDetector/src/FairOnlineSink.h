/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/**
 * FairOnlineSink.h
 *
 * @since 2018-02-01
 * @author R. Karabowicz
 */

#ifndef FAIRONLINESINK_H_
#define FAIRONLINESINK_H_

#include "FairSink.h"

#include <Rtypes.h>
#include <string>
#include <typeinfo>

class FairEventHeader;
class FairMQRunDevice;
class TObject;
class TTree;

class FairOnlineSink : public FairSink
{
  public:
    FairOnlineSink();
    virtual ~FairOnlineSink() {}

    virtual Bool_t InitSink() { return kTRUE; }
    virtual void Close() {}
    virtual void Reset() {}

    virtual Sink_Type GetSinkType() { return kONLINESINK; }

    virtual void FillEventHeader(FairEventHeader* /* feh */) {}

    virtual void SetOutTree(TTree* /* fTree */) { return; }

    virtual void Fill();

    virtual Int_t Write(const char* /* name=0 */, Int_t /* option=0 */, Int_t /* bufsize=0 */) { return -1; }

    virtual void RegisterImpl(const char*, const char*, void*);
    virtual void RegisterAny(const char* brname, const std::type_info& oi, const std::type_info& pi, void* obj);

    virtual void WriteFolder() {}
    virtual bool CreatePersistentBranchesAny() { return false; }

    virtual void WriteObject(TObject* /* f */, const char*, Int_t /* option = 0 */) {}
    virtual void WriteGeometry() {}

    virtual void SetMQRunDevice(FairMQRunDevice* mrs) { fMQRunDevice = mrs; }
    virtual FairMQRunDevice* GetMQRunDevice() { return fMQRunDevice; }

    virtual FairSink* CloneSink();

    bool IsPersistentBranchAny(const char* name);

    /* /// Returns a default object for a branch or looks it up when it exists already. */
    /* /// Returns nullptr when the branch does not exist or looking up with wrong type. */
    /* /// The returned default object will be filled with data by the framework. */
    template<typename T>
    T GetPersistentBranchAny(const char* name) const;

  private:
    FairMQRunDevice* fMQRunDevice;

    // private helper function to emit a warning
    void EmitPersistentBranchWrongTypeWarning(const char* brname, const char* typen1, const char* typen2) const;

    FairOnlineSink(const FairOnlineSink&);
    FairOnlineSink& operator=(const FairOnlineSink&);
};

// try to retrieve an object address from the registered branches/names
template<typename T>
T FairOnlineSink::GetPersistentBranchAny(const char* brname) const
{
    static_assert(std::is_pointer<T>::value, "Return type of GetPersistentBranchAny has to be a pointer");
    using P = typename std::remove_pointer<T>::type;
    auto iter = fPersistentBranchesMap.find(brname);
    if (iter != fPersistentBranchesMap.end()) {
        // verify type consistency
        if (typeid(P).hash_code() != iter->second->origtypeinfo.hash_code()) {
            EmitPersistentBranchWrongTypeWarning(brname, typeid(P).name(), iter->second->origtypeinfo.name());
            return nullptr;
        }
        return static_cast<T>(iter->second->ptraddr);
    }
    return nullptr;
}

#endif /* FAIRONLINESIK_H_ */

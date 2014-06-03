/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRREGISTRY_H
#define FAIRREGISTRY_H

#include <TNamed.h>                     // for TNamed

#include "Riosfwd.h"                    // for ostream, istream
#include "Rtypeinfo.h"                  // for type_info
#include "Rtypes.h"                     // for FairRegistry::Class, etc

#include <iostream>                     // for ostream, istream
#include <map>                          // for map, map<>::iterator, etc
#include <string>                       // for string, operator<
#include <typeinfo>                     // for type_info

class FairRegistryElement;
class TBrowser;

class FairRegistry : public TNamed
{
  public:
    typedef std::map<std::string,FairRegistryElement*> tRegMap;
    typedef void (*ErrorHandler)(void);

    explicit FairRegistry(bool readonly = true);
    FairRegistry(const FairRegistry& rhs);

    virtual ~FairRegistry();

    FairRegistry& operator=(const FairRegistry& rhs);

    void Merge(const FairRegistry& rhs);

    unsigned int Size() const { return fMap.size(); }

    bool KeyExists(const char* key) const;
    void RemoveKey(const char* key);

    void Clear(Option_t* option="");
    void Dump(void) const;


    virtual std::ostream& PrintStream(std::ostream& os) const;
    virtual std::istream& ReadStream(std::istream& is);

    virtual void Print(Option_t* option="") const; //*MENU*
    virtual std::ostream& PrettyPrint(std::ostream& os) const;


    virtual void Browse(TBrowser*) {}


    virtual bool ValuesLocked(void) const { return fValuesLocked; }
    virtual void LockValues(void) { fValuesLocked = true; }
    virtual void UnLockValues(void) { fValuesLocked = false; }

    virtual bool KeysLocked(void) const { return fKeysLocked; }
    virtual void LockKeys(void) { fKeysLocked = true; }
    virtual void UnLockKeys(void) { fKeysLocked = false; }

    void SetDirty(bool is_dirty = true) { fDirty = is_dirty; }
    bool IsDirty() { return fDirty; }


    void SetErrorHandler(ErrorHandler eh) { fErrorHandler = eh; }

    bool Get(const char* key, char& c) const;
    bool Get(const char* key, const char*& s) const;
    bool Get(const char* key, int& i) const;
    bool Get(const char* key, double& d) const;
    bool Get(const char* key, FairRegistry& r) const;

    const type_info& GetType(const char* key) const;

    std::string GetTypeAsString(const char* key) const;

    std::string GetValueAsString(const char* key) const;



    char        GetChar(const char* key) const;
    const char* GetCharString(const char* key) const;
    int         GetInt(const char* key) const;
    double      GetDouble(const char* key) const;
    FairRegistry    GetFairRegistry(const char* key) const;


    bool Set(const char* key, char c);
    bool Set(const char* key, const char* s);
    bool Set(const char* key, int i);
    bool Set(const char* key, double d);
    bool Set(const char* key, FairRegistry r);

    class FairRegistryKey
    {

      public:
        FairRegistryKey();
        FairRegistryKey(const FairRegistry* r);
        FairRegistryKey(const FairRegistryKey&);
        virtual ~FairRegistryKey();

        const char* operator()(void);

      private:

        const FairRegistry* fReg;
        std::map<std::string,FairRegistryElement*>::iterator fIt;

        //     FairRegistryKey(const FairRegistryKey&);
        FairRegistryKey operator=(const FairRegistryKey&);

    };                              // class FairRegistryKey

    FairRegistryKey Key(void) const;

  private:
    bool fValuesLocked;
    bool fKeysLocked;
    ErrorHandler fErrorHandler;  //!
#ifndef __CINT__
    friend class FairRegistryKey;
    tRegMap fMap;
#endif
    bool fDirty;

    ClassDef(FairRegistry,1)
};                              // class FairRegistry

inline std::ostream& operator<<(std::ostream& os, const FairRegistry& r) { return r.PrintStream(os); }

#endif  // FAIRREGISTRY_H

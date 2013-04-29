
#ifndef FAIRREGISTRY_H
#define FAIRREGISTRY_H

#include <iostream>
#include <map>
#include <string>

#include <TNamed.h>

class FairRegistryItem;
//class type_info;

class FairRegistry : public TNamed
{
  public:
    typedef std::map<std::string,FairRegistryItem*> tRegMap;
    typedef void (*ErrorHandler)(void);

    /// Create a Registry.  If readonly is false, any key's value can
    /// be set multiple times, o.w. only the first setting is allowed.
    /// See methods below regarding locking of keys and values.
    explicit FairRegistry(bool readonly = true);

    /// Deep copy constructor.
    FairRegistry(const FairRegistry& rhs);

    virtual ~FairRegistry();

    /// Deep assignment.
    FairRegistry& operator=(const FairRegistry& rhs);

    /// Copy rhs into this, respects this's locks.
    void Merge(const FairRegistry& rhs);

    /// Return number of entries.
    unsigned int Size() const { return fMap.size(); }

    /// Check if key exists.
    bool KeyExists(const char* key) const;
    void RemoveKey(const char* key);

    /// Clear Registry - deletes all items.
    void Clear(Option_t* option=""); //*MENU*

    /// Dump to cerr.
    void Dump(void) const;      //*MENU*

    /// Print to cout (without extraneous bits of Dump()).
    virtual std::ostream& PrintStream(std::ostream& os) const;
    virtual std::istream& ReadStream(std::istream& is);

    // TObject::Print().
    virtual void Print(Option_t* option="") const; //*MENU*
    virtual std::ostream& PrettyPrint(std::ostream& os) const;

    // TObject::Browse()
    // The default implementation crashes TBrowser, doing nothing is better.
    virtual void Browse(TBrowser*) {}

    /// Control if an existing value can be set.
    virtual bool ValuesLocked(void) const { return fValuesLocked; }
    virtual void LockValues(void) { fValuesLocked = true; } //*MENU*
    virtual void UnLockValues(void) { fValuesLocked = false; } //*MENU*

    /// Control if new key/value pairs can be added.
    virtual bool KeysLocked(void) const { return fKeysLocked; }
    virtual void LockKeys(void) { fKeysLocked = true; } //*MENU*
    virtual void UnLockKeys(void) { fKeysLocked = false; } //*MENU*

    /// Access an internal "dirty" flag Registry maintains (but does
    /// not use) It will be set any time a non-const method is
    /// accessed, or explicitly via SetDirty().  Initially a Registry
    /// is dirty (original sin?).
    void SetDirty(bool is_dirty = true) { fDirty = is_dirty; }
    bool IsDirty() { return fDirty; }


    void SetErrorHandler(ErrorHandler eh) { fErrorHandler = eh; }


    /// Access a value.  Return true and set second argument if key is
    /// found, else returns false.
//    bool Get(const char* key, bool& b) const;
    bool Get(const char* key, char& c) const;
    bool Get(const char* key, const char*& s) const;
    bool Get(const char* key, int& i) const;
    bool Get(const char* key, double& d) const;
    bool Get(const char* key, FairRegistry& r) const;

    /// Return the type_info of the value corresponding to the given
    /// key.  If key doesn't exist, type_info for type void is returned.
    const type_info& GetType(const char* key) const;
    /// Return "int", "double", "char", "string", "Registry" or "void"
    std::string GetTypeAsString(const char* key) const;
    /// see format.txt
    std::string GetValueAsString(const char* key) const;


    /// Access a value.  Returns value if key lookup succeeds, else
    /// prints warning message.  Use above Get() methods for a safer
    /// access method.
//    bool        GetBool(const char* key) const;
    char        GetChar(const char* key) const;
    const char* GetCharString(const char* key) const;
    int         GetInt(const char* key) const;
    double      GetDouble(const char* key) const;
    FairRegistry    GetFairRegistry(const char* key) const;

    /// Set the value associated with the given key.  Return false if
    /// locks prevent setting or if type mismatch.
//    bool Set(const char* key, bool b);
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
        std::map<std::string,FairRegistryItem*>::iterator fIt;

        //     FairRegistryKey(const FairRegistryKey&);
        FairRegistryKey operator=(const FairRegistryKey&);

    };                              // end of class RegistryKey

    FairRegistryKey Key(void) const;

  private:
    bool fValuesLocked;
    bool fKeysLocked;
    ErrorHandler fErrorHandler;  //! not written out
#ifndef __CINT__
    friend class FairRegistryKey;
    tRegMap fMap;
#endif
    bool fDirty;

    ClassDef(FairRegistry,1)
};                              // end of class Registry

inline std::ostream& operator<<(std::ostream& os, const FairRegistry& r) { return r.PrintStream(os); }


#include "FairRegistryItemXxx.h"

#endif  // FAIRREGISTRY_H

#ifndef FAIR_LINK_MANAGER_H
#define FAIR_LINK_MANAGER_H

#include <Rtypes.h>      // for THashConsistencyHolder, ClassDef
#include <TMCtls.h>      // for TMCThreadLocal
#include <TObject.h>     // for TObject
#include <RtypesCore.h>  // for Int_t, Bool_t
#include <set>           // for set

class FairLogger;
class TBuffer;
class TClass;
class TMemberInspector;

class FairLinkManager : public TObject
{
  public:
    /**ctor*/
    FairLinkManager();
    /**dtor*/
    virtual ~FairLinkManager();

    /** static access method */
    static FairLinkManager* Instance();
    virtual void AddIgnoreType(Int_t type);   ///< Adds a BranchId (Type) to which links are not included in the link
                                              ///< list. Either ignore types or include types can be given.
    virtual Bool_t IsIgnoreType(Int_t type) const;

    virtual void AddIncludeType(Int_t type);   ///< Adds a BranchId (Type) to which links are included in the link list.
                                               ///< Either ignore types or include types can be given (XOR).

    std::set<Int_t> GetIgnoreTypes() const { return fIgnoreTypes; }

  private:
    /**private methods*/
    FairLinkManager(const FairLinkManager&);
    FairLinkManager& operator=(const FairLinkManager&);
    /**  Set the branch address for a given branch name and return
        a TObject pointer, the user have to cast this pointer to the right type.*/

    std::set<Int_t> fIgnoreTypes;   //!
    Bool_t fIgnoreSetting;

    /**Singleton instance*/
    static TMCThreadLocal FairLinkManager* fgInstance;

    FairLogger* fLogger;   //!

    ClassDef(FairLinkManager, 1);
};

#endif   // FAIR_ROOT_MANAGER_H

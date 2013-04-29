
#ifndef FAIRDBSIMFLAGASSOCIATION
#define FAIRDBSIMFLAGASSOCIATION


#include <iosfwd>
using std::ostream;
#include <list>
using std::list;
#include <map>
using std::map;

#include "SimFlag.h"

class FairDbSimFlagAssociation;
class FairRegistry;

ostream& operator<<(ostream& s, const FairDbSimFlagAssociation& simFlagAss);

class FairDbSimFlagAssociation
{


  public:

// Typedefs for tired fingers.
    typedef list<SimFlag::SimFlag_t>           SimList_t;
    typedef map<SimFlag::SimFlag_t,SimList_t > SimMap_t;

// Constructors and destructors.
    FairDbSimFlagAssociation();
    virtual ~FairDbSimFlagAssociation();

// State testing member functions

    SimList_t Get(const SimFlag::SimFlag_t value)const;
    void Print(ostream& s)const;
    void Show();

///  Get access to the one and only instance.
    static const FairDbSimFlagAssociation& Instance();

// State changing member functions.

    void Clear() { fAssociations.clear(); }
    void Set(const SimFlag::SimFlag_t value, SimList_t list) {
      fAssociations[value] = list;
    }
    void Set(FairRegistry& reg);

  private:

///  The one and only instance (owned by FairDbTableProxyFairRegistry).
    static const FairDbSimFlagAssociation* fgInstance;

// Data members

    SimMap_t fAssociations;

    ClassDef(FairDbSimFlagAssociation,0)  // Association between SimFlag types.

};


#endif // FAIRDBSIMFLAGASSOCIATION

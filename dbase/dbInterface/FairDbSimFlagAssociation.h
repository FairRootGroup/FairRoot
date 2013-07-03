
#ifndef FAIRDBSIMFLAGASSOCIATION
#define FAIRDBSIMFLAGASSOCIATION

#include "SimFlag.h"                    // for SimFlag_t

#include "Rtypes.h"

#include <iosfwd>                       // for ostream
#include <list>                         // for list
#include <map>                          // for map, map<>::mapped_type, etc

class FairRegistry;


class FairDbSimFlagAssociation
{
  public:

    typedef std::list<SimFlag::SimFlag_t>           SimList_t;
    typedef std::map<SimFlag::SimFlag_t,SimList_t > SimMap_t;

    FairDbSimFlagAssociation();
    virtual ~FairDbSimFlagAssociation();

    SimList_t Get(const SimFlag::SimFlag_t value)const;
    void Print(std::ostream& s)const;
    void Show();

    static const FairDbSimFlagAssociation& Instance();

    void Clear() { fAssociations.clear(); }
    void Set(const SimFlag::SimFlag_t value, SimList_t list) {
      fAssociations[value] = list;
    }
    void Set(FairRegistry& reg);

  private:

    static const FairDbSimFlagAssociation* fgInstance;

// Data members

    SimMap_t fAssociations;

    ClassDef(FairDbSimFlagAssociation,0)  // Association between SimFlag types.

};

std::ostream& operator<<(std::ostream& s, const FairDbSimFlagAssociation& simFlagAss);

#endif // FAIRDBSIMFLAGASSOCIATION

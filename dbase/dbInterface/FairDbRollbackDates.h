#ifndef FAIRDBROLLBACKDATES_H
#define FAIRDBROLLBACKDATES_H

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for FairDbRollbackDates::Class, etc
#endif
#endif

#include <map>                          // for map, map<>::value_compare
#include <string>                       // for string, operator<

class FairRegistry;

class FairDbRollbackDates
{

  public:

    typedef std::map<std::string,std::string> name_map_t;

    FairDbRollbackDates();
    virtual ~FairDbRollbackDates();

    const std::string& GetDate(const std::string& tableName) const;
    const std::string& GetType(const std::string& tableName) const;
    void Show() const;

    void Clear() {fTableToDate.clear(); fTableToType.clear();}
    void Set(FairRegistry& reg);

  private:

    name_map_t fTableToDate;
    name_map_t fTableToType;

    ClassDef(FairDbRollbackDates,0)   // Rollback dates using table name.

};


#endif  // FAIRDBROLLBACKDATES_H

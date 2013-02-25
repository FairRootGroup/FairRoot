#ifndef FAIRDBROLLBACKDATES_H
#define FAIRDBROLLBACKDATES_H

#include <map>
#include <string>

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif

class FairRegistry;

class FairDbRollbackDates
{

  public:

    typedef std::map<std::string,std::string> name_map_t;

// Constructors and destructors.
    FairDbRollbackDates();
    virtual ~FairDbRollbackDates();

// State testing member functions

    const std::string& GetDate(const std::string& tableName) const;
    const std::string& GetType(const std::string& tableName) const;
    void Show() const;

// State changing member functions

    void Clear() {fTableToDate.clear(); fTableToType.clear();}
    void Set(FairRegistry& reg);  //Modifies Registry

  private:

// Data members

/// Look-up table name -> date string
    name_map_t fTableToDate;
/// Look-up table name -> time type (either "INSERTDATE" [default] or "CREATIONDATE")
    name_map_t fTableToType;

    ClassDef(FairDbRollbackDates,0)   // Rollback dates by table name.

};


#endif  // FAIRDBROLLBACKDATES_H

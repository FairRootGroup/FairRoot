/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBROLLBACKTIMES_H
#define FAIRDBROLLBACKTIMES_H

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"                     // for FairDbRollbackTimes::Class, etc
#endif
#endif

#include <map>                          // for map, map<>::value_compare
#include <string>                       // for string, operator<

class FairRegistry;

class FairDbRollbackTimes
{

  public:

    typedef std::map<std::string,std::string> name_map_t;

    FairDbRollbackTimes();
    virtual ~FairDbRollbackTimes();

    const std::string& GetDate(const std::string& tableName) const;
    const std::string& GetType(const std::string& tableName) const;
    void Show() const;

    void Clear() {fTableToDate.clear(); fTableToType.clear();}
    void Set(FairRegistry& reg);

  private:

    name_map_t fTableToDate;
    name_map_t fTableToType;

    ClassDef(FairDbRollbackTimes,0)   // Rollback times using table name.

};


#endif  // FAIRDBROLLBACKTIMES_H

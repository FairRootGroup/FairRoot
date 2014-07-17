/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRDBCONFIG_H
#define FAIRDBCONFIG_H
#ifndef STRING
# include <string>
# define STRING
#endif
class FairRegistry;

class FairDbConfig
{
  public:
    static void RegistryToString(std::string& s, const FairRegistry& r);
    static void StringToRegistry(FairRegistry& r,    const char* s);
  private:
    FairDbConfig();
    ~FairDbConfig() {;}
};

#endif // FAIRDBCONFIG_H


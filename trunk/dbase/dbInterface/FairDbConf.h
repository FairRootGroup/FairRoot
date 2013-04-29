#ifndef FAIRDBCONF_H
#define FAIRDBCONF_H
#ifndef STRING
# include <string>
# define STRING
#endif
#ifndef REGISTRY_H
# include "FairRegistry.h"
#endif
#include <cstdlib>

class FairDbConf
{
  public:
    static void RegistryToString(std::string& s, const FairRegistry& r);
    static void StringToRegistry(FairRegistry& r,    const char* s);
  private:
    FairDbConf();
    ~FairDbConf() {;}
};

#endif // FAIRDBCONF_H


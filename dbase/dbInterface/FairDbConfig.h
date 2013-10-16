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


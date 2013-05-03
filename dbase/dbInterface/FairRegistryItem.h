
#ifndef FAIRREGISTRYITEM_H
#define FAIRREGISTRYITEM_H

#include <TObject.h>

#include "Riosfwd.h"                    // for istream, ostream
#include "Rtypeinfo.h"                  // for type_info
#include "Rtypes.h"                     // for FairRegistryItem::Class, etc

#include <iosfwd>                       // for istream, ostream
#include <typeinfo>                     // for type_info

class FairRegistryItem : public TObject
{

  public:

    FairRegistryItem();
    virtual ~FairRegistryItem();
    virtual FairRegistryItem* Dup(void) const = 0;

    virtual std::ostream& PrintStream(std::ostream& os) const = 0;
    virtual std::istream& ReadStream(std::istream& is) = 0;
    virtual void Print(Option_t* option="") const = 0;

    virtual const type_info& GetType() const = 0;
    virtual const char* GetTypeAsString() const = 0;


    ClassDef(FairRegistryItem,1)
};                              // end of class FairRegistryItem


#endif  // FAIRREGISTRYITEM_H

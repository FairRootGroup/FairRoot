/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRREGISTRYELEMENT_H
#define FAIRREGISTRYELEMENT_H

#include <TObject.h>

#include "Riosfwd.h"                    // for istream, ostream
#include "Rtypeinfo.h"                  // for type_info
#include "Rtypes.h"                     // for FairRegistryElement::Class, etc

#include <iosfwd>                       // for istream, ostream
#include <typeinfo>                     // for type_info

class FairRegistryElement : public TObject
{

  public:

    FairRegistryElement();
    virtual ~FairRegistryElement();
    virtual FairRegistryElement* Dup(void) const = 0;

    virtual std::ostream& PrintStream(std::ostream& os) const = 0;
    virtual std::istream& ReadStream(std::istream& is) = 0;
    virtual void Print(Option_t* option="") const = 0;

    virtual const type_info& GetType() const = 0;
    virtual const char* GetTypeAsString() const = 0;


    ClassDef(FairRegistryElement,1)  // class FairRegistryElement
};


#endif  // FAIRREGISTRYELEMENT_H

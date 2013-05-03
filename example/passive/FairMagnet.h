#ifndef MAGNET_H
#define MAGNET_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairMagnet::Class, Bool_t, etc

#include <string>                       // for string

class FairMagnet : public FairModule
{
  public:
    FairMagnet(const char* name, const char* Title="PND Magnet");
    FairMagnet();
    virtual ~FairMagnet();
    void ConstructGeometry();
    void ConstructASCIIGeometry();
    Bool_t CheckIfSensitive(std::string name);
    ClassDef(FairMagnet,1)

};

#endif //MAGNET_H


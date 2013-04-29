#ifndef MAGNET_H
#define MAGNET_H

#include "TNamed.h"
#include "TArrayI.h"
#include "TClonesArray.h"
#include "FairDetector.h"
#include "FairModule.h"


class FairMagnet : public FairModule
{
  public:
    FairMagnet(const char* name, const char* Title="PND Magnet");
    FairMagnet();
    virtual ~FairMagnet();
    void ConstructGeometry();
    void ConstructASCIIGeometry();
    Bool_t CheckIfSensitive(std::string name);
    ClassDef(FairMagnet,1) //PNDMagnet

};

#endif //MAGNET_H


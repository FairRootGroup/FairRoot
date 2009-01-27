#ifndef MAGNET_H
#define MAGNET_H

#include "TNamed.h"
#include "TArrayI.h"
#include "TClonesArray.h"
#include "CbmDetector.h"
#include "CbmModule.h"


class PndMagnet : public CbmModule {
  public:
    PndMagnet(const char * name, const char *Title="PND Magnet");
    PndMagnet();
    virtual ~PndMagnet();
    void ConstructGeometry();
    void ConstructASCIIGeometry();
    Bool_t CheckIfSensitive(std::string name);
    ClassDef(PndMagnet,1) //PNDMagnet

};

#endif //MAGNET_H


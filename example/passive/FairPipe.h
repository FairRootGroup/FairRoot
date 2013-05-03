#ifndef PIPE_H
#define PIPE_H

#include "FairModule.h"                 // for FairModule

#include "Rtypes.h"                     // for FairPipe::Class, ClassDef, etc

class FairPipe : public FairModule
{
  public:
    FairPipe(const char* name, const char* Title="PND Pipe");
    FairPipe();

    virtual ~FairPipe();
    virtual void ConstructGeometry();

    ClassDef(FairPipe,1) //PNDPIPE

};

#endif //PIPE_H


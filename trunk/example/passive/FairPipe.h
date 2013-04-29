#ifndef PIPE_H
#define PIPE_H

#include "TNamed.h"
#include "TArrayI.h"
#include "TClonesArray.h"
#include "FairDetector.h"
#include "FairModule.h"


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


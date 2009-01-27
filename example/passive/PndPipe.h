#ifndef PIPE_H
#define PIPE_H

#include "TNamed.h"
#include "TArrayI.h"
#include "TClonesArray.h"
#include "CbmDetector.h"
#include "CbmModule.h"


class PndPipe : public CbmModule {
  public:
    PndPipe(const char * name, const char *Title="PND Pipe");
    PndPipe();

    virtual ~PndPipe();
    virtual void ConstructGeometry();
   
  ClassDef(PndPipe,1) //PNDPIPE

};

#endif //PIPE_H


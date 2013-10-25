/*
 * FairMQFileSink.h
 *
 *  Created on: 2013-06-05
 *      Author: A. Rybalchenko
 */

#ifndef FAIRMQFILESINK_H_
#define FAIRMQFILESINK_H_

#include "Rtypes.h"

#include "FairMQDevice.h"
#include "FairTestDetectorPayload.h"

class TVector3;
class TFile;
class TTree;
class TClonesArray;

class FairMQFileSink: public FairMQDevice
{
  public:
    FairMQFileSink();
    virtual ~FairMQFileSink();
    virtual void InitOutputFile(TString defaultId = "100");
  protected:
    virtual void Run();
  private:
    TFile* fOutFile;
    TTree* fTree;
    TClonesArray* fOutput;
};

#endif /* FAIRMQFILESINK_H_ */

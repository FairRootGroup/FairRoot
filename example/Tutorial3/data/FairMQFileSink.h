/**
 * FairMQFileSink.h
 *
 * @since 2013-06-05
 * @author A. Rybalchenko
 */

#ifndef FAIRMQFILESINK_H_
#define FAIRMQFILESINK_H_

#include "Rtypes.h"
#include "TString.h"

#include "FairMQDevice.h"

class TVector3;
class TFile;
class TTree;
class TClonesArray;

template <typename T1, typename T2>
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

#include "FairMQFileSink.tpl"

#endif /* FAIRMQFILESINK_H_ */

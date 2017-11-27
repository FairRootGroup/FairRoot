/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *             GNU Lesser General Public Licence (LGPL) version 3,              *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQEXAMPLE9aTASKPROCESSORBIN_H_
#define FAIRMQEXAMPLE9aTASKPROCESSORBIN_H_ 
#include <string>

#include "FairEventHeader.h"
#include "FairGeoParSet.h"
#include "FairParGenericSet.h"

#include "FairMQDevice.h"
#include "FairMQParts.h"

#include "TClonesArray.h"
#include "TList.h"
#include "TMessage.h"

#include "PixelPayload.h"
#include "PixelDigi.h"

template<typename T>
class FairMQEx9aTaskProcessorBin : public FairMQDevice
{
  public:
    FairMQEx9aTaskProcessorBin();
    virtual ~FairMQEx9aTaskProcessorBin();

    void SetDataToKeep(std::string tStr) { fDataToKeep = tStr;}

    void SetInputChannelName (std::string tstr) {fInputChannelName = tstr;}
    void SetOutputChannelName(std::string tstr) {fOutputChannelName = tstr;}
    void SetParamChannelName (std::string tstr) {fParamChannelName  = tstr;}

  protected:
    bool ProcessData(FairMQParts&, int);
    virtual void Init();
    virtual void PostRun();

 private:
    std::string     fInputChannelName;
    std::string     fOutputChannelName;
    std::string     fParamChannelName;

    void UpdateParameters();
    FairParGenericSet* UpdateParameter(FairParGenericSet* thisPar);

    static void CustomCleanup(void *data, void *hint);

    FairEventHeader* fEventHeader;

    int fNewRunId;
    int fCurrentRunId;

    std::string fDataToKeep;

    int fReceivedMsgs = 0;
    int fSentMsgs = 0;

    T* fFairTask;
    TList* fParCList;
    FairGeoParSet* fGeoPar;

    FairMQEx9aTaskProcessorBin(const FairMQEx9aTaskProcessorBin&);    
    FairMQEx9aTaskProcessorBin& operator=(const FairMQEx9aTaskProcessorBin&);    
};

// Template implementation is in FairMQEx9aTaskProcessorBin.tpl :
#include "FairMQEx9aTaskProcessorBin.tpl"

#endif /* FAIRMQEXAMPLE9aTASKPROCESSOR_H_ */

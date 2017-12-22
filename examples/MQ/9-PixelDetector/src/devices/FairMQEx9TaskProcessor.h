/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQEXAMPLE9TASKPROCESSOR_H_
#define FAIRMQEXAMPLE9TASKPROCESSOR_H_

#include <string>

#include "FairEventHeader.h"
#include "FairGeoParSet.h"
#include "FairParGenericSet.h"

#include "FairMQDevice.h"
#include "FairMQParts.h"

#include "TClonesArray.h"
#include "TList.h"
#include "TMessage.h"

template<typename T>
class FairMQEx9TaskProcessor : public FairMQDevice
{
  public:
    FairMQEx9TaskProcessor();
    virtual ~FairMQEx9TaskProcessor();

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

    FairEventHeader* fEventHeader;
    TList*           fInput;
    TList*           fOutput;

    int fNewRunId;
    int fCurrentRunId;

    std::string fDataToKeep;

    int fReceivedMsgs = 0;
    int fSentMsgs = 0;

    T* fFairTask;
    TList* fParCList;
    FairGeoParSet* fGeoPar;

    FairMQEx9TaskProcessor(const FairMQEx9TaskProcessor&);
    FairMQEx9TaskProcessor& operator=(const FairMQEx9TaskProcessor&);
};

// Template implementation is in FairMQEx9TaskProcessor.tpl :
#include "FairMQEx9TaskProcessor.tpl"

#endif /* FAIRMQEXAMPLE9TASKPROCESSOR_H_ */

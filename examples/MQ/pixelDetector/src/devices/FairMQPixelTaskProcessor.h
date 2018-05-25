/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQPIXELTASKPROCESSOR_H_
#define FAIRMQPIXELTASKPROCESSOR_H_

#include <string>

#include "FairEventHeader.h"
#include "FairMCEventHeader.h"
#include "FairGeoParSet.h"
#include "FairParGenericSet.h"

#include "FairMQDevice.h"
#include "FairMQParts.h"

#include "TClonesArray.h"
#include "TList.h"
#include "TMessage.h"

template<typename T>
class FairMQPixelTaskProcessor : public FairMQDevice
{
  public:
    FairMQPixelTaskProcessor();
    virtual ~FairMQPixelTaskProcessor();

    void SetDataToKeep(std::string tStr) { fDataToKeep = tStr;}

    void SetInputChannelName (std::string tstr) {fInputChannelName = tstr;}
    void SetOutputChannelName(std::string tstr) {fOutputChannelName = tstr;}
    void SetParamChannelName (std::string tstr) {fParamChannelName  = tstr;}

    void SetStaticParameters (bool tbool)       {fStaticParameters = tbool;}

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

    FairEventHeader*   fEventHeader;
    FairMCEventHeader* fMCEventHeader;
    TList*             fInput;
    TList*             fOutput;

    bool fStaticParameters;
    int fNewRunId;
    int fCurrentRunId;

    std::string fDataToKeep;

    int fReceivedMsgs = 0;
    int fSentMsgs = 0;

    T* fFairTask;
    TList* fParCList;
    FairGeoParSet* fGeoPar;

    FairMQPixelTaskProcessor(const FairMQPixelTaskProcessor&);
    FairMQPixelTaskProcessor& operator=(const FairMQPixelTaskProcessor&);
};

// Template implementation is in FairMQPixelTaskProcessor.tpl :
#include "FairMQPixelTaskProcessor.tpl"

#endif /* FAIRMQPIXELTASKPROCESSOR_H_ */

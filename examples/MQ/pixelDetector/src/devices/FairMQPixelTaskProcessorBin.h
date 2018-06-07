/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQPIXELTASKPROCESSORBIN_H_
#define FAIRMQPIXELTASKPROCESSORBIN_H_

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
class FairMQPixelTaskProcessorBin : public FairMQDevice
{
  public:
    FairMQPixelTaskProcessorBin();
    virtual ~FairMQPixelTaskProcessorBin();

    void SetDataToKeep(std::string str) { fDataToKeep = str; }

    void SetInputChannelName (std::string str) { fInputChannelName = str; }
    void SetOutputChannelName(std::string str) { fOutputChannelName = str; }
    void SetParamChannelName (std::string str) { fParamChannelName  = str; }

    void SetStaticParameters (bool tbool)       {fStaticParameters = tbool;}

  protected:
    bool ProcessData(FairMQParts&, int);
    virtual void Init();
    virtual void PostRun();

 private:
    std::string fInputChannelName;
    std::string fOutputChannelName;
    std::string fParamChannelName;

    void UpdateParameters();
    FairParGenericSet* UpdateParameter(FairParGenericSet* thisPar);

    FairEventHeader* fEventHeader;
    TList*           fInput;
    TList*           fOutput;

    TClonesArray* fInputArray;
    TClonesArray* fOutputArray;

    bool fStaticParameters;
    int fNewRunId;
    int fCurrentRunId;

    std::string fDataToKeep;

    int fReceivedMsgs = 0;
    int fSentMsgs = 0;

    T* fFairTask;
    TList* fParCList;
    FairGeoParSet* fGeoPar;

    FairMQPixelTaskProcessorBin(const FairMQPixelTaskProcessorBin&);
    FairMQPixelTaskProcessorBin& operator=(const FairMQPixelTaskProcessorBin&);
};

// Template implementation is in FairMQPixelTaskProcessorBin.tpl :
#include "FairMQPixelTaskProcessorBin.tpl"

#endif /* FAIRMQPIXELTASKPROCESSOR_H_ */

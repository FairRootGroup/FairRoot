/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRMQPIXALTTASKPROCESSORBIN_H_
#define FAIRMQPIXALTTASKPROCESSORBIN_H_ 
#include <string>

#include "FairEventHeader.h"
#include "FairGeoParSet.h"
#include "FairParGenericSet.h"

#include "FairMQDevice.h"
#include "FairMQParts.h"

#include "TClonesArray.h"
#include "TList.h"
#include "RootSerializer.h"

#include "PixelPayload.h"
#include "PixelDigi.h"

template<typename T>
class FairMQPixAltTaskProcessorBin : public FairMQDevice
{
  public:
    FairMQPixAltTaskProcessorBin();
    virtual ~FairMQPixAltTaskProcessorBin();

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

    FairMQPixAltTaskProcessorBin(const FairMQPixAltTaskProcessorBin&);    
    FairMQPixAltTaskProcessorBin& operator=(const FairMQPixAltTaskProcessorBin&);    
};

// Template implementation is in FairMQPixAltTaskProcessorBin.tpl :
#include "FairMQPixAltTaskProcessorBin.tpl"

#endif /* FAIRMQPIXALTTASKPROCESSOR_H_ */

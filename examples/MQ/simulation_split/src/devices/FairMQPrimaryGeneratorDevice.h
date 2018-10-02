/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/**
 * FairMQPrimaryGeneratorDevice.h
 *
 * @since 2018-08-31
 * @author R. Karabowicz
 */

#ifndef FAIRMQPRIMARYGENERATORDEVICE_H_
#define FAIRMQPRIMARYGENERATORDEVICE_H_

#include <string>
#include "TString.h"

#include "FairMQDevice.h"

class FairMCEventHeader;
class FairRunSim;
class FairField;
class FairParIo;
class FairPrimaryGenerator;
class TObject;
class TObjArray;
class FairSink;
class FairStack;

class FairMQPrimaryGeneratorDevice : public FairMQDevice
{
 public:
    FairMQPrimaryGeneratorDevice();
    virtual ~FairMQPrimaryGeneratorDevice();

    virtual void        SendPrimaries();

    void SetNofEvents       (int64_t nofev)                 { fNofEvents = nofev;};
    void SetGenerator       (FairPrimaryGenerator* primGen) { fPrimaryGenerator = primGen;};

    void SetChunkSize(int64_t ti)    { fChunkSize = ti;};

    void RunInPushMode(bool tb=true) { fRunConditional = tb; };
    void RunInRepMode (bool tb=true) { fRunConditional = !tb; };

 protected:
    bool Reply(FairMQMessagePtr&, int);
    virtual void InitTask();
    virtual void PreRun();
    virtual void PostRun();
    virtual bool ConditionalRun();

 private:
    std::string fGeneratorChannelName;

    bool                     fRunConditional; // if true run ConditionalRun, if false run Reply

    FairPrimaryGenerator*    fPrimaryGenerator;
    FairMCEventHeader*       fMCEventHeader;
    FairStack*               fStack;
    int64_t                  fNofEvents;
    int64_t                  fEventCounter;

    int64_t                  fChunkSize;    // to set the maximal number of primaries sent in one bunch
    int64_t                  fChunkPointer; // to set the first primary to be sent

    bool GenerateAndSendData();
    void SendObject(TObject* obj, std::string chan);

    FairMQPrimaryGeneratorDevice(const FairMQPrimaryGeneratorDevice&);
    FairMQPrimaryGeneratorDevice& operator=(const FairMQPrimaryGeneratorDevice&);
};

#endif /* FAIRMQPRIMARYGENERATORDEVICE_H_ */

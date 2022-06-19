/********************************************************************************
 * Copyright (C) 2017-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/**
 * FairMQRunDevice.h
 *
 * @since 2018-02-01
 * @author R. Karabowicz
 */

#ifndef FAIRMQRUNDEVICE_H_
#define FAIRMQRUNDEVICE_H_

#include "FairMQ.h"   // for fair::mq::Device
#include "FairRun.h"

#include <TObject.h>
#include <string>

class FairOnlineSink;

class FairMQRunDevice : public fair::mq::Device
{
  public:
    FairMQRunDevice();
    FairMQRunDevice(const FairMQRunDevice&) = delete;
    FairMQRunDevice& operator=(const FairMQRunDevice&) = delete;
    ~FairMQRunDevice() override;

    virtual void SendBranches(FairOnlineSink& sink);

    void SetSink(std::unique_ptr<FairOnlineSink> sink);

  protected:
    void SendObject(TObject* obj, const std::string& chan);
    /**
     * Setup the run's Sink from the sink from SetSink()
     */
    void SetupRunSink(FairRun& run);

  private:
    /**
     * Handle ownership for the sink correctly
     */
    std::unique_ptr<FairOnlineSink> fSink;
};

#endif /* FAIRMQRUNDEVICE_H_ */

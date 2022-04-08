/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * File:   FairTestDetectorDigiLoader.h
 * @since 2014-02-08
 * @author: A. Rybalchenko, N. Winckler
 */

#ifndef FAIRTESTDETECTORDIGILOADER_H
#define FAIRTESTDETECTORDIGILOADER_H

#include "FairMQSamplerTask.h"
#include "FairTestDetectorDigi.h"
#include "FairTestDetectorPayload.h"

#include <array>
#include <fairlogger/Logger.h>
#include <iostream>

template<typename TOut, typename TPayloadOut>
class FairTestDetectorDigiLoader : public FairMQSamplerTask
{
  public:
    FairTestDetectorDigiLoader()
        : FairMQSamplerTask("Load class TOut")
    {}

    virtual void Exec(Option_t* opt);
};

// Template implementation is in FairTestDetectorDigiLoader.tpl :
#include "FairTestDetectorDigiLoaderBin.tpl"
#include "FairTestDetectorDigiLoaderBoost.tpl"
#include "FairTestDetectorDigiLoaderFlatBuffers.tpl"
#include "FairTestDetectorDigiLoaderMsgpack.tpl"
#include "FairTestDetectorDigiLoaderProtobuf.tpl"
#include "FairTestDetectorDigiLoaderTMessage.tpl"

#endif /* FAIRTESTDETECTORDIGILOADER_H */

/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_TESTDETECTOR_DIGILOADER_H
#define FAIR_TESTDETECTOR_DIGILOADER_H

// this example
#include "FairTestDetectorDigi.h"
#include "Payload.h"
#include "SamplerTask.h"

// logger
#include <fairlogger/Logger.h>

template<typename T>
class DigiLoader : public SamplerTask
{
  public:
    DigiLoader()
        : SamplerTask("Load class TOut")
    {}

    void Exec(Option_t* opt) override;
};

#endif /* FAIR_TESTDETECTOR_DIGILOADER_H */

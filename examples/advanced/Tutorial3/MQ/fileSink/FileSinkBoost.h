/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of FileSink::Run() with Boost transport data format

#ifndef FAIR_TESTDETECTOR_FILESINK_BOOST_H
#define FAIR_TESTDETECTOR_FILESINK_BOOST_H

#include "BoostSerializer.h"
#include "Payload.h"

template<>
void FileSink<TestDetectorBoost>::InitTask()
{
    OnData(fInChannelName, [this](fair::mq::MessagePtr& msg, int /*index*/) {
        ++fReceivedMsgs;

        BoostSerializer<FairTestDetectorHit>().Deserialize(*msg, fOutput);

        if (fOutput->IsEmpty()) {
            LOG(error) << "FileSink::Run(): No Output array!";
        }

        fTree.Fill();

        if (fMaxMsgs != 0) {
            if (fReceivedMsgs == fMaxMsgs) {
                return false;
            }
        }

        return true;
    });
}

#endif   // FAIR_TESTDETECTOR_FILESINK_BOOST_H

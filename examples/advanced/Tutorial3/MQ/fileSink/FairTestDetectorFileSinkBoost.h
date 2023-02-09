/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/*
 * File:   FairTestDetectorFileSink.h
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with Boost transport data format

#include "BoostSerializer.h"

// example TIn: FairTestDetectorHit
// example TPayloadIn: boost::archive::binary_iarchive
template<typename TIn, typename TPayloadIn>
void FairTestDetectorFileSink<TIn, TPayloadIn>::InitTask()
{
    OnData(fInChannelName, [this](fair::mq::MessagePtr& msg, int /*index*/) {
        ++fReceivedMsgs;

        BoostSerializer<TIn>().Deserialize(*msg, fOutput);

        if (fOutput->IsEmpty()) {
            LOG(error) << "FairTestDetectorFileSink::Run(): No Output array!";
        }

        auto ack(NewMessage());
        Send(ack, fAckChannelName);

        fTree.Fill();

        return true;
    });
}

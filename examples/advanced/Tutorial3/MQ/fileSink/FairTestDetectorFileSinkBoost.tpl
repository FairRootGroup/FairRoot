/*
 * File:   FairTestDetectorFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with Boost transport data format

#include "BoostSerializer.h"

// example TIn: FairTestDetectorHit
// example TPayloadIn: boost::archive::binary_iarchive
template <typename TIn, typename TPayloadIn>
void FairTestDetectorFileSink<TIn, TPayloadIn>::InitTask()
{
    OnData(fInChannelName, [this](FairMQMessagePtr& msg, int /*index*/) {
        ++fReceivedMsgs;

        Deserialize<BoostSerializer<TIn>>(*msg, fOutput);

        if (fOutput->IsEmpty()) {
            LOG(error) << "FairTestDetectorFileSink::Run(): No Output array!";
        }

        FairMQMessagePtr ack(NewMessage());
        Send(ack, fAckChannelName);

        fTree.Fill();

        return true;
    });
}

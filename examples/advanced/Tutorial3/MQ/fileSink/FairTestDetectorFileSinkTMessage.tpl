/*
 * File:   FairTestDetectorFileSink.tpl
 * Author: winckler, A. Rybalchenko
 *
 * Created on March 11, 2014, 12:12 PM
 */

// Implementation of FairTestDetectorFileSink::Run() with Root TMessage transport data format

#include "RootSerializer.h"

template <>
void FairTestDetectorFileSink<FairTestDetectorHit, TMessage>::InitTask()
{
    OnData(fInChannelName, [this](FairMQMessagePtr& msg, int /*index*/)
    {
        ++fReceivedMsgs;

        RootSerializer().Deserialize(*msg, fOutput);

        fTree.SetBranchAddress("Output", &fOutput);

        FairMQMessagePtr ack(fTransportFactory->CreateMessage());
        fChannels.at(fAckChannelName).at(0).Send(ack);

        fTree.Fill();

        return true;
    });
}

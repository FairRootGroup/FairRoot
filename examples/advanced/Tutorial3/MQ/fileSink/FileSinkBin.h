/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of FileSink::Run() with pure binary transport data format

#ifndef FAIR_TESTDETECTOR_FILESINK_BIN_H
#define FAIR_TESTDETECTOR_FILESINK_BIN_H

#include "Payload.h"

template<>
void FileSink<TestDetectorBin>::InitTask()
{
    OnData(fInChannelName, [this](fair::mq::MessagePtr& msg, int /*index*/) {
        ++fReceivedMsgs;
        fOutput->Delete();

        int numEntries = msg->GetSize() / sizeof(Payload::Hit);

        Payload::Hit* input = static_cast<Payload::Hit*>(msg->GetData());

        for (int i = 0; i < numEntries; ++i) {
            TVector3 pos(input[i].posX, input[i].posY, input[i].posZ);
            TVector3 dpos(input[i].dposX, input[i].dposY, input[i].dposZ);
            new ((*fOutput)[i]) FairTestDetectorHit(input[i].detID, input[i].mcindex, pos, dpos);
        }

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

#endif   // FAIR_TESTDETECTOR_FILESINK_BIN_H

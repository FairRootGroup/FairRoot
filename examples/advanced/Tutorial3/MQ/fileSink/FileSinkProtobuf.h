/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of FileSink::Run() with Google Protocol Buffers transport data format

#ifdef PROTOBUF

#include "Payload.h"
#include "Payload.pb.h"

template<>
void FileSink<TestDetectorProtobuf>::InitTask()
{
    OnData(fInChannelName, [this](fair::mq::MessagePtr& msg, int /*index*/) {
        ++fReceivedMsgs;
        fOutput->Delete();

        TestDetectorProto::HitPayload hp;
        hp.ParseFromArray(msg->GetData(), msg->GetSize());

        int numEntries = hp.hit_size();

        for (int i = 0; i < numEntries; ++i) {
            const TestDetectorProto::Hit& hit = hp.hit(i);
            TVector3 pos(hit.posx(), hit.posy(), hit.posz());
            TVector3 dpos(hit.dposx(), hit.dposy(), hit.dposz());
            new ((*fOutput)[i]) FairTestDetectorHit(hit.detid(), hit.mcindex(), pos, dpos);
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

#endif /* PROTOBUF */

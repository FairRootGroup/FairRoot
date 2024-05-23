/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

// Implementation of DigiLoader::Exec() with Google Protocol Buffers transport data format

#ifndef FAIR_TESTDETECTOR_DIGILOADER_PROTOBUF_H
#define FAIR_TESTDETECTOR_DIGILOADER_PROTOBUF_H

#ifdef PROTOBUF

#include "Payload.h"
#include "Payload.pb.h"

template<>
void DigiLoader<TestDetectorProtobuf>::Exec(Option_t* /*opt*/)
{
    int nDigis = fInput->GetEntriesFast();

    TestDetectorProto::DigiPayload dp;

    for (int i = 0; i < nDigis; ++i) {
        FairTestDetectorDigi* digi = static_cast<FairTestDetectorDigi*>(fInput->At(i));
        if (!digi) {
            continue;
        }
        TestDetectorProto::Digi* d = dp.add_digi();
        d->set_fx(digi->GetX());
        d->set_fy(digi->GetY());
        d->set_fz(digi->GetZ());
        d->set_ftimestamp(digi->GetTimeStamp());
        d->set_ftimestamperror(digi->GetTimeStampError());
    }

    std::string* str = new std::string();
    dp.SerializeToString(str);

    fPayload = fTransportFactory->CreateMessage(
        const_cast<char*>(str->c_str()),
        str->length(),
        [](void* /* data */, void* obj) { delete static_cast<std::string*>(obj); },
        str);
}

#endif   // PROTOBUF

#endif   // FAIR_TESTDETECTOR_DIGILOADER_PROTOBUF_H

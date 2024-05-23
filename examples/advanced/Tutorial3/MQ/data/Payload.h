/********************************************************************************
 * Copyright (C) 2014-2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_TESTDETECTOR_PAYLOAD_H
#define FAIR_TESTDETECTOR_PAYLOAD_H

namespace Payload {

class TimeStamp
{
  public:
    Double_t fTimeStamp;
    Double_t fTimeStampError;
};

class Digi : public TimeStamp
{
  public:
    Int_t fX;
    Int_t fY;
    Int_t fZ;
};

class Hit : public TimeStamp
{
  public:
    Int_t detID;
    Int_t mcindex;
    Double_t posX;
    Double_t posY;
    Double_t posZ;
    Double_t dposX;
    Double_t dposY;
    Double_t dposZ;
};

// serialization types tags

}   // namespace Payload

struct TestDetectorBin;
struct TestDetectorBoost;
struct TestDetectorFlatBuffers;
struct TestDetectorProtobuf;
struct TestDetectorTMessage;

#endif /* FAIR_TESTDETECTOR_PAYLOAD_H */

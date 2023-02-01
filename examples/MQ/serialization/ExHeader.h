/********************************************************************************
 * Copyright (C) 2023 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH       *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef EXHEADER_H
#define EXHEADER_H

#include "FairMQ.h"   // for fair::mq::Message

namespace boost::serialization {
class access;
}

struct ExHeader
{
    int eventNumber = 0;
    int detectorId = 0;
};

namespace boost::serialization {

template<class Archive>
void serialize(Archive& ar, ExHeader& header, const unsigned int /*version*/)
{
    ar& header.eventNumber;
    ar& header.detectorId;
}

}   // namespace boost::serialization

#endif

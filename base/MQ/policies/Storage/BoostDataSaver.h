/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   BoostDataSaver.h
 * Author: winckler
 *
 * Created on October 22, 2014, 5:16 PM
 */

#ifndef BOOSTDATASAVER_H
#define BOOSTDATASAVER_H

// FairRoot
#include "FairMQ.h"   // for fair::mq::Message

// std
#include <fstream>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

// boost
namespace boost {
namespace serialization {
class access;
}
}   // namespace boost
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <fairlogger/Logger.h>

template<typename TPayload,
         typename TArchiveIn = boost::archive::binary_iarchive,
         typename TArchiveOut = boost::archive::binary_oarchive>
class BoostDataSaver
{
  public:
    BoostDataSaver() {}
    virtual ~BoostDataSaver() {}

    virtual void InitOutputFile() {}

    void Write(std::ofstream& outfile, TPayload* objArr, long sizeArr = 1)
    {
        std::vector<TPayload> dataVector(objArr, objArr + sizeArr);
        TArchiveOut outArchive(outfile);
        outArchive << dataVector;
    }

    void Write(std::ofstream& outfile, std::vector<TPayload> dataVector)
    {
        TArchiveOut outArchive(outfile);
        outArchive << dataVector;
    }

    void Write(std::ofstream& outfile, fair::mq::Message* msg)
    {
        std::vector<TPayload> objArr;
        std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
        std::istringstream ibuffer(msgStr);
        TArchiveIn inputArchive(ibuffer);
        try {
            inputArchive >> objArr;
        } catch (boost::archive::archive_exception& e) {
            LOG(error) << e.what();
        }
        TArchiveOut outArchive(outfile);
        outArchive << objArr;
    }

    std::vector<std::vector<TPayload>> Read(std::ifstream& infile)
    {
        std::vector<std::vector<TPayload>> dataContainer;
        while (infile.peek() != EOF && !infile.eof()) {
            TArchiveIn inArchive(infile);
            std::vector<TPayload> temp;
            inArchive >> temp;
            dataContainer.push_back(temp);
        }
        return dataContainer;
    }
};

#endif /* BOOSTDATASAVER_H */

/********************************************************************************
 * Copyright (C) 2014-2022 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH  *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   BinaryOutFileManager.h
 * Author: winckler
 *
 * Created on October 15, 2014, 11:36 AM
 */

#ifndef BINARYOUTFILEMANAGER_H
#define BINARYOUTFILEMANAGER_H

// std
#include <fstream>
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

// FairRoot
#include "BoostDataSaver.h"
#include "FairMQ.h"   // for fair::mq::Message
#include "TriviallyCopyableDataSaver.h"
#include "baseMQtools.h"

#define GET_POLICY_ID(Policy) #Policy

using BinArchive = boost::archive::binary_oarchive;

template<typename T, typename BoostArchive>
using BoostSerializable = baseMQ::tools::resolve::has_BoostSerialization<T, void(BoostArchive&, const unsigned int)>;

template<typename TPayload, typename TStoragePolicy = TriviallyCopyableDataSaver<TPayload>>
class BinaryOutFileManager : public TStoragePolicy
{
  public:
    using TStoragePolicy::Read;
    using TStoragePolicy::Write;

    BinaryOutFileManager()
        : TStoragePolicy()
        , fFileName("test.dat")
    {
        ;
    }
    virtual ~BinaryOutFileManager() { fOutfile.close(); }

    std::string GetPolicyID()
    {
        std::string str(GET_POLICY_ID(TStoragePolicy));
        return str;
    }

    void SetFileProperties(const std::string& filename) { fFileName = filename; }

    void AddToFile(fair::mq::Message* msg) { TStoragePolicy::Write(fOutfile, msg); }

    void AddToFile(TPayload* objArr, long size) { AppendObjArray<TPayload>(fOutfile, objArr, size); }

    template<typename T>
    void AppendObjArray(std::ofstream& outfile, T* objArr, long size)
    {
        TStoragePolicy::Write(outfile, objArr, size);
    }

    std::vector<std::vector<TPayload>> GetAllObj(const std::string& filename)
    {
        std::ifstream infile;
        infile = std::ifstream(filename);
        std::vector<std::vector<TPayload>> vec = TStoragePolicy::Read(infile);

        return vec;
    }

    virtual void InitOutputFile()
    {
        fOutfile = std::ofstream(fFileName, std::ios::out | std::ios::binary | std::ios::app);
    }

  protected:
    std::string fFileName;
    std::ofstream fOutfile;
};

#endif /* BINARYOUTFILEMANAGER_H */

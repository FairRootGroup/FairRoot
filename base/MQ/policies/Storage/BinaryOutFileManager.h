/* 
 * File:   BinaryOutFileManager.h
 * Author: winckler
 *
 * Created on October 15, 2014, 11:36 AM
 */

#ifndef BINARYOUTFILEMANAGER_H
#define	BINARYOUTFILEMANAGER_H

// std
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <type_traits>

// boost
#include <boost/serialization/access.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>

// ROOT
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"

// FairRoot
#include "FairMQLogger.h"
#include "FairMQMessage.h"
#include "TriviallyCopyableDataSaver.h"
#include "BoostDataSaver.h"
#include "baseMQtools.h"

#define GET_POLICY_ID(Policy) #Policy

using BinArchive = boost::archive::binary_oarchive;

template <typename T, typename BoostArchive>
using BoostSerializable = baseMQ::tools::resolve::has_BoostSerialization<T, void(BoostArchive&, const unsigned int)>;

template <typename TPayload, typename TStoragePolicy = TriviallyCopyableDataSaver<TPayload>>
class BinaryOutFileManager : public TStoragePolicy
{
  public:
    using TStoragePolicy::Write;
    using TStoragePolicy::Read;

    BinaryOutFileManager() : TStoragePolicy(), fFileName("test.dat") {;}
    virtual ~BinaryOutFileManager()
    {
        fOutfile.close();
    }

    std::string GetPolicyID()
    {
        std::string str(GET_POLICY_ID(TStoragePolicy));
        return str;
    }

    void SetFileProperties(const std::string &filename)
    {
        fFileName = filename;
    }

    void AddToFile(FairMQMessage* msg)
    {
        TStoragePolicy::Write(fOutfile, msg);
    }

    void AddToFile(TPayload* objArr, long size)
    {
        AppendObjArray<TPayload>(fOutfile, objArr, size);
    }

    template<typename T>
    void AppendObjArray(std::ofstream& outfile, T* objArr, long size)
    {
        TStoragePolicy::Write(outfile, objArr, size);
    }

    std::vector<std::vector<TPayload> > GetAllObj(const std::string &filename)
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

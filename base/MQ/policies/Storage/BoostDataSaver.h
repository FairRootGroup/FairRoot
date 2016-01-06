/* 
 * File:   BoostDataSaver.h
 * Author: winckler
 *
 * Created on October 22, 2014, 5:16 PM
 */

#ifndef BOOSTDATASAVER_H
#define	BOOSTDATASAVER_H

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

// FairRoot
#include "FairMQMessage.h"

typedef boost::archive::binary_iarchive TBoostIn;
typedef boost::archive::binary_oarchive TBoostOut;

template <typename TPayload, typename TArchiveIn=TBoostIn, typename TArchiveOut=TBoostOut>
class BoostDataSaver
{
  public:
    typedef std::vector<TPayload> TObjArray;
    typedef std::vector<TObjArray> TObjArrContainer;

    BoostDataSaver() {}
    virtual ~BoostDataSaver() {}

    virtual void InitOutputFile(){}

    void Write(std::ofstream& outfile, TPayload* ObjArr, long sizeArr=1)
    {
        TObjArray DataVector(ObjArr, ObjArr +sizeArr);
        TArchiveOut OutArchive(outfile);
        OutArchive << DataVector;
    }

    void Write(std::ofstream& outfile, TObjArray DataVector)
    {
        TArchiveOut OutArchive(outfile);
        OutArchive << DataVector;
    }

    void Write(std::ofstream& outfile, FairMQMessage* msg)
    {
        //std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
        //outfile<<msgStr;
        //outfile<<msg->GetData();
        TObjArray objarr;
        std::string msgStr(static_cast<char*>(msg->GetData()), msg->GetSize());
        std::istringstream ibuffer(msgStr);
        TArchiveIn InputArchive(ibuffer);
        try
        {
            InputArchive >> objarr; // get input Archive
        }
        catch (boost::archive::archive_exception& e)
        {
            MQLOG(ERROR) << e.what();
        }
        TArchiveOut OutArchive(outfile);
        OutArchive << objarr;
    }

    TObjArrContainer Read(std::ifstream& infile)
    {
        TObjArrContainer DataContainer;
        while(infile.peek()!= EOF && !infile.eof())
        {
            TArchiveIn InArchive(infile);
            TObjArray temp;
            InArchive >> temp;
            DataContainer.push_back(temp);
        }
        return DataContainer;
    }
};

#endif /* BOOSTDATASAVER_H */

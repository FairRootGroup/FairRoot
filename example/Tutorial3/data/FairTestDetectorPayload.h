/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * TestDetectorPayload.h
 *
 *  @since 2013-04-22
 *  @author A. Rybalchenko
 */

#ifndef TESTDETECTORPAYLOAD_H_
#define TESTDETECTORPAYLOAD_H_

#include <string>
#include "FairTestDetectorDigi.h"
#include "TString.h"


// for boost serialization (must be hidden from CINT)
#ifndef __CINT__
#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>
#endif //__CINT__

namespace TestDetectorPayload
{
    class TimeStamp
    {
      public:
        Double_t fTimeStamp;
        Double_t fTimeStampError;
        
        // method to use boost serialization
        #ifndef __CINT__
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version) 
        {
            ar & fTimeStamp;
            ar & fTimeStampError;
        }
        friend class boost::serialization::access;
        #endif //__CINT__
        
    };

    class Digi : public TimeStamp
    {
      public:
        Int_t fX;
        Int_t fY;
        Int_t fZ;
        
        // method to use boost serialization
        #ifndef __CINT__
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version) 
        {
            ar & boost::serialization::base_object<TimeStamp>(*this);
            ar & fX;
            ar & fY;
            ar & fZ;
        }
        friend class boost::serialization::access;
        #endif //__CINT__
        
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
        
        // method to use boost serialization
        #ifndef __CINT__
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version) 
        {
            ar & boost::serialization::base_object<TimeStamp>(*this);
            ar & detID;
            ar & mcindex;
            ar & posX;
            ar & posY;
            ar & posZ;
            ar & dposX;
            ar & dposY;
            ar & dposZ;
        }
        friend class boost::serialization::access;
        #endif //__CINT__
    };
}

#endif /* TESTDETECTORPAYLOAD_H_ */

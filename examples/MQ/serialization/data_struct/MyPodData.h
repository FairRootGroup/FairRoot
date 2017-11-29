/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

/*
 * File:   MyPodData.h
 * Author: winckler
 *
 * Created on November 24, 2014, 1:46 PM
 */

#ifndef MYPODDATA_H
#define	MYPODDATA_H

// for root types
#include <iosfwd>   
#include "Rtypes.h" 

#include <boost/serialization/access.hpp>
#include <boost/serialization/base_object.hpp>

namespace MyPodData
{

    class TimeStamp
    {
      public:
        Double_t fTimeStamp;
        Double_t fTimeStampError;
        
        // method to use boost serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/) 
        {
            ar & fTimeStamp;
            ar & fTimeStampError;
        }
        friend class boost::serialization::access;
        
    };

    class Digi : public TimeStamp
    {
      public:
        Int_t fX;
        Int_t fY;
        Int_t fZ;
        
        // method to use boost serialization
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/) 
        {
            ar & boost::serialization::base_object<TimeStamp>(*this);
            ar & fX;
            ar & fY;
            ar & fZ;
        }
        friend class boost::serialization::access;
        
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
        template<class Archive>
        void serialize(Archive & ar, const unsigned int /*version*/) 
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
    };
}

#endif	/* MYPODDATA_H */


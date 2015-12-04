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

namespace TestDetectorPayload
{
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
}

#define BIGBUFFERSIZE 1000000

#endif /* TESTDETECTORPAYLOAD_H_ */

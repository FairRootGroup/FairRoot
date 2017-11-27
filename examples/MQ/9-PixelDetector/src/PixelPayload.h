/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
/**
 * PixelPayload.h
 *
 *  @since 2013-04-22
 *  @author A. Rybalchenko
 */

#ifndef PIXELPAYLOAD_H_
#define PIXELPAYLOAD_H_

#include <string>

namespace PixelPayload
{
    class EventHeader
    {
      public:
        int fRunId;
        int fMCEntryNo;
        int fPartNo;
    };

    class Digi
    {
      public:
        int    fDetectorID;
        int    fFeID;
        double fCharge;
        int    fCol;
        int    fRow;
    };

    class Hit
    {
      public:
        int    fDetectorID;
        double posX;
        double posY;
        double posZ;
        double dposX;
        double dposY;
        double dposZ;
    };

    class Track
    {
      public:
        double fX0;
        double fAX;
        double fY0;
        double fAY;
        double fX0Err;
        double fAXErr;
        double fY0Err;
        double fAYErr;
    };
}

#define BIGBUFFERSIZE 1000000

#endif /* PIXELPAYLOAD_H_ */

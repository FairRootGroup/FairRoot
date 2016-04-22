/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
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

#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#endif
namespace PixelPayload
{
    class EventHeader
    {
      public:
        Int_t fRunId;
        Int_t fMCEntryNo;
        Int_t fPartNo;
    };

    class Digi
    {
      public:
        Int_t    fDetectorID;
        Int_t    fFeID;
        Double_t fCharge;
        Int_t    fCol;
        Int_t    fRow;              
    };

    class Hit
    {
      public:
        Int_t    fDetectorID;
        Double_t posX;
        Double_t posY;
        Double_t posZ;
        Double_t dposX;
        Double_t dposY;
        Double_t dposZ;
    };

    class Track
    {
      public:
        Double_t fX0;
        Double_t fAX;
        Double_t fY0;
        Double_t fAY;
        Double_t fX0Err;
        Double_t fAXErr;
        Double_t fY0Err;
        Double_t fAYErr;
    };
}
#if defined(__GNUC__) || defined(__GNUG__)
#pragma GCC diagnostic pop
#endif

#define BIGBUFFERSIZE 1000000

#endif /* PIXELPAYLOAD_H_ */

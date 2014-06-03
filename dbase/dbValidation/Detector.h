/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
////////////////////////////////////////////////////////////////////////////
// Detector
//
// Detector defines Detector_t which is an enumeration of the
// legal detector configurations
//
////////////////////////////////////////////////////////////////////////////

// try the input file
#include "db_detector_def.h"

// or the default one ...
#ifndef DETECTOR_H
#define DETECTOR_H

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif

#include "TString.h"

class Detector
{
  public:
    typedef enum EDetector {
      kUnknown          = 0x00,
      kCal              = 0x01,
      kCalCrystal       = 0x02,
      kDch              = 0x04,
      kGfi              = 0x08,
      kLand             = 0x10,
      kMtof             = 0x12,
      kTof              = 0x14,
      kTracker          = 0x16,
    } Detector_t;

    static Int_t       FullMask() {
      return kCal|kCalCrystal|kDch|kGfi|kLand|kMtof|kTof|kTracker;
    }


    static const Char_t*  AsString(Detector_t detector) {
      switch (detector) {
      case kUnknown:
        return "Unknown";
        break;
      case kCal:
        return "Califa";
        break;
      case kCalCrystal:
        return "CrystalBall";
        break;
      case kDch:
        return "Dch";
        break;
      case kGfi:
        return "Gfi";
        break;
      case kLand:
        return "Land";
        break;
      case kMtof:
        return "Mtof";
        break;
      case kTof:
        return "Tof";
        break;
      case kTracker:
        return "Tracker";
        break;
      default:
        return "?Unknown?";
        break;
      }
    }

    static Detector::Detector_t   CharToEnum(Char_t c) {
      switch(c) {
      case 'C':
      case '1':
      case 0x01:
        return kCal;
      case 'c':
      case '2':
      case 0x02:
        return kCalCrystal;
      case 'D':
      case 'd':
      case '4':
      case 0x04:
        return kDch;
      case 'G':
      case 'g':
      case '8':
      case 0x08:
        return kGfi;
      case 'L':
      case 'l':
      case 0x10:
        return kLand;
      case 'M':
      case 'm':
      case 0x12:
        return kMtof;
      case 't':
      case 0x14:
        return kTof;
      case 'T':
      case 0x16:
        return kTracker;
      default:
        return kUnknown;
      }
    }

    static Char_t*  MaskToString(Int_t mask) {

      static Char_t newstring[255] = "";
      Char_t* ptr = newstring;
      *ptr = 0; // start with nothing
      Int_t fullmask = Detector::FullMask();

      for (Int_t i=0; i<32; i++) {
        Detector::Detector_t adet = (Detector::Detector_t)(1<<i);
        if (mask & adet & fullmask) {
          const Char_t* toadd = Detector::AsString(adet);
          if (ptr != newstring) { *ptr++ = ','; }
          strcpy(ptr,toadd);
          ptr += strlen(toadd);
        }
      }
      *ptr++ = 0;

      return newstring;
    }


    static Int_t  StringToMask(const Char_t* chars, Int_t maxChar=0) {
      Int_t mask  = 0;

      TString thestring(chars);
      if (maxChar>0 && maxChar<thestring.Length()) { thestring.Resize(maxChar); }

      thestring.ToLower();
      if (thestring.Contains("C")) { mask |= kCal; }
      if (thestring.Contains("c")) { mask |= kCalCrystal; }
      if (thestring.Contains("D")) { mask |= kDch; }
      if (thestring.Contains("G")) { mask |= kGfi; }
      if (thestring.Contains("L")) { mask |= kLand; }
      if (thestring.Contains("M")) { mask |= kMtof; }
      if (thestring.Contains("t")) { mask |= kTof; }
      if (thestring.Contains("T")) { mask |= kTracker; }

      return mask;
    }


    static Detector::Detector_t  StringToEnum(const Char_t* chars, Int_t maxChar=0) {

      Int_t mask = Detector::StringToMask(chars,maxChar);

      switch (mask) {
      case kUnknown:
        return kUnknown;
        break;
      case kCal:
        return kCal;
        break;
      case kCalCrystal:
        return kCalCrystal;
        break;
      case kDch:
        return kDch;
        break;
      case kGfi:
        return kGfi;
        break;
      case kLand:
        return kLand;
        break;
      case kMtof:
        return kMtof;
        break;
      case kTof:
        return kTof;
        break;
      case kTracker:
        return kTracker;
        break;
      default:
        return kUnknown;
        break;
      }

    }


};


#endif // DETECTOR_H




////////////////////////////////////////////////////////////////////////////
// Detector
//
// Detector defines Detector_t which is an enumeration of the
// legal detector configurations
//
////////////////////////////////////////////////////////////////////////////

#ifndef DETECTOR_H
#define DETECTOR_H

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif


namespace Detector
{

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


Int_t       FullMask();

// Translation enum to/from character strings

const Char_t*          AsString(Detector_t detector);
Detector::Detector_t   CharToEnum(Char_t c);
Char_t*                MaskToString(Int_t mask);
Detector::Detector_t   StringToEnum(const Char_t* chars, Int_t maxChar=0);
Int_t                  StringToMask(const Char_t* chars, Int_t maxChar=0);

}

// make "DetectorType" a synonym for "Detector"
namespace DetectorType = Detector;

#endif // DETECTOR_H

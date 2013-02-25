#include "Detector.h"
#include "TString.h"


Int_t Detector::FullMask()
{
  return kCal|kCalCrystal|kDch|kGfi|kLand|kMtof|kTof|kTracker;
}

const Char_t* Detector::AsString(Detector_t detector)
{
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


Detector::Detector_t Detector::CharToEnum(Char_t c)
{
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


Char_t* Detector::MaskToString(Int_t mask)
{
  // Return a mask of Detector as a string
  //
  // Result is a pointer to a statically allocated string.
  // User should copy this into their own buffer before calling
  // this method again.

  static Char_t newstring[255] = "";

  Char_t* ptr = newstring;  // start at the beginning

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
  *ptr++ = 0; // ensure trailing 0

  return newstring;
}


Detector::Detector_t Detector::StringToEnum(const Char_t* chars, Int_t maxChar)
{
  // convert a set of chars to a valid enum

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


Int_t Detector::StringToMask(const Char_t* chars, Int_t maxChar)
{
  // convert a set of chars to a mask of enum's
  // simple tests for unique characters: {n,f,c,t,m}

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




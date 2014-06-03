/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "Experiment.h"

#include "TString.h"                    // for TString

#include <string.h>                     // for strcpy, strlen


Int_t Experiment::FullMask()
{
  return kS001|kS002|kS003|kS004|kS005|kS006;
}

const Char_t* Experiment::AsString(Experiment_t exp)
{
  switch (exp) {
  case kS001:
    return "S001";
    break;
  case kS002:
    return "S002";
    break;
  case kS003:
    return "S003";
    break;
  case kS004:
    return "S004";
    break;
  case kS005:
    return "S005";
    break;
  case kS006:
    return "S006";
    break;
  default:
    return "?Unknown?";
    break;
  }
}


Experiment::Experiment_t Experiment::CharToEnum(Char_t c)
{
  switch(c) {
  case 'N':
  case 'n':
  case '1':
  case 0x01:
    return kS001;
  case 'F':
  case 'f':
  case '2':
  case 0x02:
    return kS002;
  case 'C':
  case 'c':
  case '4':
  case 0x04:
    return kS003;
  case 'T':
  case 't':
  case '8':
  case 0x08:
    return kS004;
  case 'M':
  case 'm':
  case 0x10:
    return kS005;
  default:
    return kUnknown;
  }
}


Char_t* Experiment::MaskToString(Int_t mask)
{
  static Char_t newstring[255] = "";
  Char_t* ptr = newstring;
  *ptr = 0;
  Int_t fullmask = Experiment::FullMask();

  for (Int_t i=0; i<32; i++) {
    Experiment::Experiment_t adet = (Experiment::Experiment_t)(1<<i);
    if (mask & adet & fullmask) {
      const Char_t* toadd = Experiment::AsString(adet);
      if (ptr != newstring) { *ptr++ = ','; }
      strcpy(ptr,toadd);
      ptr += strlen(toadd);
    }
  }
  *ptr++ = 0;

  return newstring;
}


Experiment::Experiment_t Experiment::StringToEnum(const Char_t* chars, Int_t maxChar)
{
  Int_t mask = Experiment::StringToMask(chars,maxChar);

  switch (mask) {
  case kS001:
    return kS001;
    break;
  case kS002:
    return kS002;
    break;
  case kS003:
    return kS003;
    break;
  case kS004:
    return kS004;
    break;
  case kS005:
    return kS005;
    break;
  case kS006:
    return kS006;
    break;
  default:
    return kUnknown;
    break;
  }

}


Int_t Experiment::StringToMask(const Char_t* chars, Int_t maxChar)
{
  Int_t mask  = 0;

  TString thestring(chars);
  if (maxChar>0 && maxChar<thestring.Length()) { thestring.Resize(maxChar); }

  thestring.ToLower();
  if (thestring.Contains("S1")) { mask |= kS001; }
  if (thestring.Contains("S2")) { mask |= kS002; }
  if (thestring.Contains("S3")) { mask |= kS003; }
  if (thestring.Contains("S4")) { mask |= kS004; }
  if (thestring.Contains("S5")) { mask |= kS005; }



  return mask;
}


/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "DataType.h"

#include "TString.h"

#include <string.h>                     // for strcpy, strlen



Int_t DataType::FullMask()
{
  return kData|kDaqData|kMC;
}

const Char_t* DataType::AsString(DataType_t dataType)
{
  switch (dataType) {
  case kUnknown:
    return "Unknown";
    break;
  case kData:
    return "Data";
    break;
  case kDaqData:
    return "DaqData";
    break;
  case kMC:
    return "MC";
    break;
  default:
    return "?Data?";
    break;
  }
}


const Char_t* DataType::MaskToString(Int_t mask)
{
  static Char_t newstring[255] = "";

  Char_t* ptr = newstring;  // start at the beginning

  *ptr = 0; // start with nothing
  Int_t fullmask = DataType::FullMask();

  for (Int_t i=0; i<32; i++) {
    DataType::DataType_t flag = (DataType::DataType_t)(1<<i);
    if (mask & flag & fullmask) {
      const Char_t* toadd = DataType::AsString(flag);
      if (ptr != newstring) { *ptr++ = ','; }
      strcpy(ptr,toadd);
      ptr += strlen(toadd);
    }
  }
  *ptr++ = 0; // ensure trailing 0

  return newstring;
}

DataType::DataType_t DataType::StringToEnum(const Char_t* chars, Int_t maxChar)
{

  Int_t mask = DataType::StringToMask(chars,maxChar);

  switch (mask) {
  case kUnknown:
    return kUnknown;
    break;
  case kData:
    return kData;
    break;
  case kDaqData:
    return kDaqData;
    break;
  case kMC:
    return kMC;
    break;
  default:
    return kUnknown;
    break;
  }

}


Int_t DataType::StringToMask(const Char_t* chars, Int_t maxChar)
{
  // convert a set of chars to a mask of enum's
  // simple tests for unique characters: {d,s,m,r}

  Int_t mask  = 0;

  TString thestring(chars);
  if (maxChar>0 && maxChar<thestring.Length()) { thestring.Resize(maxChar); }

  thestring.ToLower();
  if (thestring.Contains("d")) { mask |= kData; }
  if (thestring.Contains("s")) { mask |= kDaqData; }
  if (thestring.Contains("m")) { mask |= kMC; }

  return mask;
}

//_____________________________________________________________________________

Int_t DataType::Compact(DataType_t dataType)
{

  switch (dataType) {
  case kUnknown:
    return -1;
    break;
  case kData:
    return  0;
    break;
  case kDaqData:
    return  1;
    break;
  case kMC:
    return  2;
    break;
  default:
    return -1;
    break;
  }

}

DataType::DataType_t DataType::Expand(Int_t compactDataType)
{

  switch (compactDataType) {
  case  0:
    return kData;
    break;
  case  1:
    return kDaqData;
    break;
  case  2:
    return kMC;
    break;
  default:
    return kUnknown;
    break;
  }
}


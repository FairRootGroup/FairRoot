/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "ValCondition.h"

#include <stdio.h>                      // for sprintf, printf

ClassImp(ValCondition)


ValCondition::ValCondition()
  :  fDetector(Detector::kUnknown),
     fDataType(DataType::kUnknown),
     fTimeStamp()
{
  // Default all is unKnown
}

ValCondition::~ValCondition() { ; }



std::ostream& operator<<(std::ostream& os, const ValCondition& vldc)
{
  if (os.good()) {
    if (os.tie()) { os.tie()->flush(); }
    os << vldc.AsString();
  }

  if (os.flags() & std::ios::unitbuf) { os.flush(); }
  return os;
}


ValCondition::ValCondition(const Detector::Detector_t& detector,
                           const DataType::DataType_t mcFlag,
                           const ValTimeStamp& tstamp)
  : TObject(),
    fDetector(detector),
    fDataType(mcFlag),
    fTimeStamp(tstamp)
{
  // normal constructor
}


const char* ValCondition::AsString(Option_t* option) const
{
  static char newstring[80] = " ";

  switch (option[0]) {
  case 'c':
  case 'C':
    sprintf(newstring,"[%c%c %s]",
            Detector::AsString(GetDetector())[0],
            DataType::AsString(GetDataType())[0],
            fTimeStamp.AsString("c"));
    break;
  default:
    sprintf(newstring,"[%6.6s|%6.6s|%s]",
            Detector::AsString(GetDetector()),
            DataType::AsString(GetDataType()),
            fTimeStamp.AsString("c"));
  }

  return newstring;
}


void ValCondition::Print(Option_t* option) const
{
  printf("%s\n",AsString(option));
}


Bool_t ValCondition::IsNull() const
{
  return fDetector==Detector::kUnknown && fDataType == DataType::kUnknown;
}




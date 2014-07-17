/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef DATATYPE_H
#define DATATYPE_H

#ifndef ROOT_Rtypes
#if !defined(__CINT__) || defined(__MAKECINT__)
#include "Rtypes.h"
#endif
#endif


namespace DataType
{

typedef enum EDataType {
  kUnknown      = 0x00,
  kData         = 0x01,
  kDaqData      = 0x02,
  kMC           = 0x04,
} DataType_t;

Int_t       FullMask();


const Char_t*       AsString(DataType_t detector);
const Char_t*       MaskToString(Int_t mask);
DataType::DataType_t  StringToEnum(const Char_t* chars, Int_t maxChar=0);
Int_t               StringToMask(const Char_t* chars, Int_t maxChar=0);

Int_t               Compact(DataType_t dataType);
DataType::DataType_t  Expand(Int_t compactDataType);

}

#endif // DATATYPE_H

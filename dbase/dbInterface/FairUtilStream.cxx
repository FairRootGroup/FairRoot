/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairUtilStream.h"

#include <ctype.h>                      // for isspace

using namespace std;

void Util::eat_whitespace(std::istream& is)
{
  char c;
  while (is.get(c)) {
    if (!isspace(c)) {
      is.putback(c);
      break;
    }
  }
}

std::string Util::read_quoted_string(std::istream& is)
{
  eat_whitespace(is);

  char c;

  if (!is.get(c)) { return ""; }
  if (c == '\'') {
    string stot;
    while (is.get(c)) {
      if (c == '\'') { break; }
      stot += c;
    }
    return stot;
  } else {
    is.putback(c);
    return "";
  }
}


// ------------------------------------------------------------------
/*!
    Convert a block of data to a hex string
*/
void Util::BinToHex(
  void* const data,                   //!< Data to convert
  const size_t dataLength,            //!< Length of the data to convert
  std::string& dest                   //!< Destination string
)
{
  unsigned char*       byteData = reinterpret_cast<unsigned char*>(data);
  std::stringstream   hexStringStream;

  hexStringStream << std::hex << std::setfill('0');
  for(size_t index = 0; index < dataLength; ++index) {
    hexStringStream << std::setw(2) << static_cast<int>(byteData[index]);
  }
  dest = hexStringStream.str();
}


// ------------------------------------------------------------------
/*!
    Convert a hex string to a block of data
*/
void Util::BinFromHex(
  const std::string& in,              //!< Input hex string
  void* const data                    //!< Data store
)
{
  size_t          length      = in.length();
  unsigned char*   byteData   = reinterpret_cast<unsigned char*>(data);

  std::stringstream hexStringStream;
  hexStringStream >> std::hex;
  for(size_t strIndex = 0, dataIndex = 0; strIndex < length; ++dataIndex) {
    // Read out and convert the string two characters at a time
    const char tmpStr[3] = { in[strIndex], in[strIndex+1], 0 };
    strIndex += 2;

    // Reset and fill the string stream
    hexStringStream.clear();
    hexStringStream.str(tmpStr);

    // Do the conversion
    int tmpValue = 0;
    hexStringStream >> tmpValue;
    byteData[dataIndex] = static_cast<unsigned char>(tmpValue);
  }
}

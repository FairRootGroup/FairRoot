/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIRUTILSTREAM_H
#define FAIRUTILSTREAM_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace Util
{

// Some string functions
void eat_whitespace(std::istream& is);
std::string read_quoted_string(std::istream& is);

// Binary Strings
void BinToHex(void* const data,  const size_t dataLength, std::string& dest);
void BinFromHex(const std::string& in, void* const data );

}

#endif  // FAIRUTILSTREAM_H

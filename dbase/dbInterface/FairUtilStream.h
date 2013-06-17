
#ifndef FAIRUTILSTREAM_H
#define FAIRUTILSTREAM_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace Util
{

/// discard all whitespace chars until hitting a non-whitespace
void eat_whitespace(std::istream& is);

/// return a string of words.  Strings are delimited by single quotes.
/// any leading white space is eaten.
std::string read_quoted_string(std::istream& is);
void  string_to_binary(const std::string source,  char* destination,  int length);
void  binary_to_string(const  char* source,  int length, std::string& destination);

void BinToHex(void* const data,  const size_t dataLength, std::string& dest);
void BinFromHex(const std::string& in, void* const data );


}

#endif  // FAIRUTILSTREAM_H

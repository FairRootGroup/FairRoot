
#ifndef FAIRUTILSTREAM_H
#define FAIRUTILSTREAM_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

namespace Util
{

void eat_whitespace(std::istream& is);
std::string read_quoted_string(std::istream& is);

// Binary Strings
void BinToHex(void* const data,  const size_t dataLength, std::string& dest);
void BinFromHex(const std::string& in, void* const data );

}

#endif  // FAIRUTILSTREAM_H

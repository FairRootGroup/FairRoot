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

/*
void Util::string_to_binary(const std::string source,  char* destination,  int length)
{
  int effective_length = min(length, ( int) source.length() / 2);
  for( int b = 0; b < effective_length; b++) {
    sscanf(source.data() + (b * 2), "%02x", ( int*) &destination[b]);
  }
}

void Util::binary_to_string(const  char* source,  int length, std::string& destination)
{
  destination.clear();
  for( int i = 0; i < length; i++) {
    char digit[3];
    sprintf(digit, "%02x", source[i]);
    destination.append(digit);
  }
}
*/



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
    const char tmpStr[3] = { in[strIndex++], in[strIndex++], 0 };

    // Reset and fill the string stream
    hexStringStream.clear();
    hexStringStream.str(tmpStr);

    // Do the conversion
    int tmpValue = 0;
    hexStringStream >> tmpValue;
    byteData[dataIndex] = static_cast<unsigned char>(tmpValue);
  }
}

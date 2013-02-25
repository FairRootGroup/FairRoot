
#ifndef FAIRUTILSTREAM_H
#define FAIRUTILSTREAM_H

#include <iostream>
#include <string>

namespace Util
{

/// discard all whitespace chars until hitting a non-whitespace
void eat_whitespace(std::istream& is);

/// return a string of words.  Strings are delimited by single quotes.
/// any leading white space is eaten.
std::string read_quoted_string(std::istream& is);
}

#endif  // FAIRUTILSTREAM_H

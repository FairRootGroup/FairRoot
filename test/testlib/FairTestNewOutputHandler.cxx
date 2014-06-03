/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestNewOutputHandler.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>


FairTestNewOutputHandler::FairTestNewOutputHandler( bool captureStdErr, bool captureStdOut )
  : old_cout(std::cout.rdbuf()),  // backup orig cout streambuf in any case
    old_cerr(std::cerr.rdbuf()),  // backup orig cout streambuf in any case
    output(),
    fLineVector(),
    fCaptureEnded(false),
    fCaptureStdOut(captureStdOut),
    fCaptureStdErr(captureStdErr)
{
  if (fCaptureStdOut) {
    std::cout.rdbuf(output.rdbuf());  // assign boost test streambuf to cout
  }
  if (fCaptureStdErr) {
    std::cerr.rdbuf(output.rdbuf());  // assign boost test streambuf to cout
  }

}

FairTestNewOutputHandler::~FairTestNewOutputHandler()
{
  std::cout.rdbuf(old_cout);         // reset original cout streambuf
  std::cerr.rdbuf(old_cerr);         // reset original cerr streambuf
}

std::string FairTestNewOutputHandler::GetCaptureLine(int line)
{
  Split();
  return fLineVector[line];
}

int FairTestNewOutputHandler::GetNumberOfLines()
{
  Split();
  return fLineVector.size()-1;
}

void FairTestNewOutputHandler::Split()
{
  if (!fCaptureEnded) {
    std::cout.rdbuf(old_cout); // when capturing cout and cerr is finished
    std::cerr.rdbuf(old_cerr); // reset original setting

    // split the string buffer on new lines
    std::string s = output.str();
    boost::split(fLineVector, s, boost::algorithm::is_any_of("\n"));
    fCaptureEnded=true;
  }
}

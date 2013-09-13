#include "FairTestNewOutputHandler.h"

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>


FairTestNewOutputHandler::FairTestNewOutputHandler( bool captureStdErr, bool captureStdOut )
  : old_cout(std::cout.rdbuf()),
    old_cerr(std::cerr.rdbuf()),
    //    fCout(),
    //    fCerr(),
    output(),
    fLineVector(),
    fCaptureEnded(false),
    fCaptureStdOut(captureStdOut),
    fCaptureStdErr(captureStdErr)
{
  if (fCaptureStdOut) {
    //    fCout.Set(output.rdbuf());
    std::cout.rdbuf(output.rdbuf());         // assign streambuf to cerr
  }
  if (fCaptureStdErr) {
    //    fCerr.Set(output.rdbuf());
    std::cerr.rdbuf(output.rdbuf());         // assign streambuf to cerr
  }

}

FairTestNewOutputHandler::~FairTestNewOutputHandler()
{
  std::cout.rdbuf(old_cout);         // assign streambuf to cerr
  std::cerr.rdbuf(old_cerr);         // assign streambuf to cerr
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
    //   fCout.Reset();
    //    fCerr.Reset();
    std::cout.rdbuf(old_cout);         // assign streambuf to cerr
    std::cerr.rdbuf(old_cerr);         // assign streambuf to cerr
    std::string s = output.str();

    boost::split(fLineVector, s, boost::algorithm::is_any_of("\n"));
    fCaptureEnded=true;
  }
}

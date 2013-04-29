#ifndef FAIRCAPTUREOUTPUT_H_
#define FAIRCAPTUREOUTPUT_H_
#pragma once

#include "FairTestOutputHandler.h"

#include <cstring>
#include <fstream>
#include <vector>

class FairCaptureOutput
{
  public:

    FairCaptureOutput( bool captureStdErr = true, bool captureStdOut = false );
    ~FairCaptureOutput();

    void BeginCapture();
    void EndCapture();

    std::string GetCaptureLine(int line) const
    { return fOutputHandler->GetCaptureLine(line);}
    int GetNumberOfLines() const
    { return fOutputHandler->GetNumberOfLines();}

    void CaptureStdOut(bool capture = false) { fCaptureStdOut = capture; }
    void CaptureStdErr(bool capture = false) { fCaptureStdErr = capture; }

  private:

    FILE* fTempStdOut;
    FILE* fTempStdErr;
    FILE* fOutputFile;
    char fFileName[25];
    char* fFileNamePtr;
    bool fCaptureEnded;
    bool fCaptureStdOut;
    bool fCaptureStdErr;
    FairTestOutputHandler* fOutputHandler;
};
#endif



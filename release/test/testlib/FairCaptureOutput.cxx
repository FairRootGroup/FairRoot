#include "FairCaptureOutput.h"

#include <iostream>

FairCaptureOutput::FairCaptureOutput(bool captureStdErr, bool captureStdOut)
  : fTempStdOut(),
    fTempStdErr(),
    fOutputFile(NULL),
    fFileName(),
    fFileNamePtr(NULL),
    fCaptureEnded(true),
    fCaptureStdOut(captureStdOut),
    fCaptureStdErr(captureStdErr),
    fOutputHandler(new FairTestOutputHandler())
{
}

FairCaptureOutput::~FairCaptureOutput()
{
  // close all files and remove the temporary file
  remove(fFileName);
}

void FairCaptureOutput::BeginCapture()
{
  //  if (fCaptureEnded) {
  // save stderr and stdout file pointer to restore the old behavior
  if (fCaptureStdErr) {
    fTempStdErr = stderr;
  }
  if (fCaptureStdOut) {
    fTempStdOut = stdout;
  }

  // create a temporary file
  fFileNamePtr = tmpnam(fFileName);
  fOutputHandler->SetFileName(fFileName);

  // redirect output from stdout and stderr to the file

  if (fCaptureStdErr) {
    fOutputFile = freopen(fFileNamePtr, "a", stderr);
  }
  if (fCaptureStdOut) {
    if (!fCaptureStdErr) {
      fOutputFile = freopen(fFileNamePtr, "a", stdout);
    } else {
      freopen(fFileNamePtr, "a", stdout);
    }
  }
  //    fCaptureEnded = false;
  //  } else {
  //  }
}

void FairCaptureOutput::EndCapture()
{
  fclose(fOutputFile);
  if (fCaptureStdErr) {
    stderr = fTempStdErr;
    freopen("/dev/tty", "w", stderr);
  }
  if (fCaptureStdOut) {
    stdout = fTempStdOut;
    freopen("/dev/tty", "w", stdout);
  }
}





/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *              GNU Lesser General Public Licence (LGPL) version 3,             *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairCaptureOutputNew.h"

#include "gtest/gtest.h"

#include <iostream>

FairCaptureOutputNew::FairCaptureOutputNew( bool captureStdErr, bool captureStdOut )
  : fLineVector(),
    fCaptureStdOut(captureStdOut),
    fCaptureStdErr(captureStdErr)
{
}

FairCaptureOutputNew::~FairCaptureOutputNew()
{
}

void FairCaptureOutputNew::BeginCapture()
{
  if (fCaptureStdOut && fCaptureStdErr) {
    std::cout << "Can't capture stdout and stderr at the same time." << std::endl;
    exit(1);
  }
  if (fCaptureStdOut) {
    testing::internal::CaptureStdout();
  }
  if (fCaptureStdErr) {
    testing::internal::CaptureStderr();
  }
}

void FairCaptureOutputNew::EndCapture()
{
  std::string tmpOutput;
  if (fCaptureStdOut) {
    tmpOutput = testing::internal::GetCapturedStdout();
  }
  if (fCaptureStdErr) {
    tmpOutput = testing::internal::GetCapturedStderr();
  }

  const std::string& sep = "\n";
  std::size_t start = 0, end = 0;
  while ((end = tmpOutput.find(sep, start)) != std::string::npos) {
    fLineVector.push_back(tmpOutput.substr(start, end - start));
    start = end + 1;
  }
}

std::string FairCaptureOutputNew::GetCaptureLine(int line)
{
  return fLineVector[line];
}

int FairCaptureOutputNew::GetNumberOfLines()
{
  return fLineVector.size();
}

/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRCAPTUREOUTPUTNEW_H_
#define FAIRCAPTUREOUTPUTNEW_H_
#pragma once

#include <string>
#include <vector>

class FairCaptureOutputNew
{
  public:
    FairCaptureOutputNew(bool captureStdErr = false, bool captureStdOut = true);
    ~FairCaptureOutputNew();

    void BeginCapture();
    void EndCapture();

    std::string GetCaptureLine(int line);
    int GetNumberOfLines();

  private:
    std::vector <std::string> fLineVector;

    bool fCaptureStdOut;
    bool fCaptureStdErr;

    void Split();
};
#endif

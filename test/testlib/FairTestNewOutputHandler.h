/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTNEWOUTPUTHANDLER_H_
#define FAIRTESTNEWOUTPUTHANDLER_H_
#pragma once

#include <boost/test/output_test_stream.hpp>
#include <iostream>
#include <vector>

class FairTestNewOutputHandler
{
  public:

    FairTestNewOutputHandler( bool captureStdErr = true, bool captureStdOut = false );
    ~FairTestNewOutputHandler();


    std::string GetCaptureLine(int line);
    int GetNumberOfLines();

  private:

    std::streambuf* old_cout;
    std::streambuf* old_cerr;

    boost::test_tools::output_test_stream output;

    std::vector < std::string > fLineVector;

    bool fCaptureEnded;
    bool fCaptureStdOut;
    bool fCaptureStdErr;

    void Split();

};
#endif

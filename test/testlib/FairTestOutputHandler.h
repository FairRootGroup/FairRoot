/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#ifndef FAIRTESTOUTPUTHANDLER_H_
#define FAIRTESTOUTPUTHANDLER_H_
#pragma once

#include <string>
#include <vector>

class FairTestOutputHandler
{
  public:
    FairTestOutputHandler(const std::string& filename);
    FairTestOutputHandler();
    ~FairTestOutputHandler();

    std::string GetCaptureLine(int line);
    int GetNumberOfLines();

    void SetFileName(const std::string& filename);

  private:
    void ReadContentFromFile();

    std::string fFileName;
    std::vector<std::string> fFileContent;
    std::vector<std::string>::iterator fFileContentIterator;
    int fNumberOfLines;
    bool fFileAlreadyRead;
};

#endif

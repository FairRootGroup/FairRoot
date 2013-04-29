#ifndef FAIRTESTOUTPUTHANDLER_H_
#define FAIRTESTOUTPUTHANDLER_H_
#pragma once

#include <string> //?? why not cstring
#include <vector>

class FairTestOutputHandler
{
  public:
    FairTestOutputHandler(std::string filename);
    FairTestOutputHandler();
    ~FairTestOutputHandler();

    std::string GetCaptureLine(int line);
    int GetNumberOfLines();

    void SetFileName(std::string filename);

  private:

    void ReadContentFromFile();

    std::string fFileName;
    std::vector<std::string> fFileContent;
    std::vector<std::string>::iterator fFileContentIterator;
    int fNumberOfLines;
    bool fFileAlreadyRead;
};

#endif

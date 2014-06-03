/********************************************************************************
 *    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             * 
 *         GNU Lesser General Public Licence version 3 (LGPL) version 3,        *  
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/
#include "FairTestOutputHandler.h"

#include <fstream>

FairTestOutputHandler::FairTestOutputHandler(std::string filename)
  : fFileName(filename),
    fFileContent(),
    fFileContentIterator(),
    fNumberOfLines(0),
    fFileAlreadyRead(false)
{
}

FairTestOutputHandler::FairTestOutputHandler()
  : fFileName(),
    fFileContent(),
    fFileContentIterator(),
    fNumberOfLines(0),
    fFileAlreadyRead(false)
{
}

FairTestOutputHandler::~FairTestOutputHandler()
{
  remove(fFileName.c_str());
}

void FairTestOutputHandler::SetFileName(std::string filename)
{
  fFileName = filename;
  fFileContent.clear();
  fNumberOfLines = 0;
  fFileAlreadyRead =false;
}

int FairTestOutputHandler::GetNumberOfLines()
{
  ReadContentFromFile();
  return fNumberOfLines;
}

void FairTestOutputHandler::ReadContentFromFile()
{
  if ( !fFileAlreadyRead ) {
    fFileContent.clear();
    fNumberOfLines = 0;

    std::ifstream ifs(fFileName.c_str());
    std::string line;

    while( getline( ifs, line ) ) {
      fFileContent.push_back( line );
      ++fNumberOfLines;
    }
    fFileAlreadyRead = true;
  }
}

std::string FairTestOutputHandler::GetCaptureLine(int line)
{

  ReadContentFromFile();

  return fFileContent[line];

}

